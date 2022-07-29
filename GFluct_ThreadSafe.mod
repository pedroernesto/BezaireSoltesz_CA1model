INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}

NEURON {
	POINT_PROCESS Gfluct_rand
	RANGE g_e, g_i, E_e, E_i, g_e0, g_i0, g_e1, g_i1
	RANGE std_e, std_i, tau_e, tau_i, D_e, D_i
	RANGE new_seed
	NONSPECIFIC_CURRENT i
	THREADSAFE : only true if every instance has its own distinct Random
  POINTER donotuse
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(umho) = (micromho)
}

PARAMETER {
	dt		(ms)

	E_e	= 0 	(mV)	: reversal potential of excitatory conductance
	E_i	= -75 	(mV)	: reversal potential of inhibitory conductance

	g_e0	= 0.0121 (umho)	: average excitatory conductance
	g_i0	= 0.0573 (umho)	: average inhibitory conductance

	std_e	= 0.0030 (umho)	: standard dev of excitatory conductance
	std_i	= 0.0066 (umho)	: standard dev of inhibitory conductance

	tau_e	= 2.728	(ms)	: time constant of excitatory conductance
	tau_i	= 10.49	(ms)	: time constant of inhibitory conductance
}

ASSIGNED {
	v	(mV)		: membrane voltage
	i 	(nA)		: fluctuating current
	g_e	(umho)		: total excitatory conductance
	g_i	(umho)		: total inhibitory conductance
	g_e1	(umho)		: fluctuating excitatory conductance
	g_i1	(umho)		: fluctuating inhibitory conductance
	D_e	(umho umho /ms) : excitatory diffusion coefficient
	D_i	(umho umho /ms) : inhibitory diffusion coefficient
	exp_e
	exp_i
	amp_e	(umho)
	amp_i	(umho)
  donotuse
}

INITIAL {
	g_e1 = 0
	g_i1 = 0
	if(tau_e != 0) {
		D_e = 2 * std_e * std_e / tau_e
		exp_e = exp(-dt/tau_e)
		amp_e = std_e * sqrt( (1-exp(-2*dt/tau_e)) )
	}
	if(tau_i != 0) {
		D_i = 2 * std_i * std_i / tau_i
		exp_i = exp(-dt/tau_i)
		amp_i = std_i * sqrt( (1-exp(-2*dt/tau_i)) )
	}
}

BREAKPOINT {
	SOLVE oup
	if(tau_e==0) {
	   g_e = std_e * grand()
	}
	if(tau_i==0) {
	   g_i = std_i * grand()
	}
	g_e = g_e0 + g_e1
	if(g_e < 0) { g_e = 0 }
	g_i = g_i0 + g_i1
	if(g_i < 0) { g_i = 0 }
	i = g_e * (v - E_e) + g_i * (v - E_i)
}


PROCEDURE oup() {		: use grand()
   if(tau_e!=0) {
	g_e1 =  exp_e * g_e1 + amp_e * grand()
   }
   if(tau_i!=0) {
	g_i1 =  exp_i * g_i1 + amp_i * grand()
   }
}

PROCEDURE new_seed(seed) {		: procedure to set the seed
	set_seed(seed)
	VERBATIM
	  printf("Setting random generator with seed = %g\n", _lseed);
	ENDVERBATIM
}

VERBATIM
double nrn_random_pick(void* r);
void* nrn_random_arg(int argpos);
ENDVERBATIM

FUNCTION grand() {
VERBATIM
    if (_p_donotuse) {
        /*
         : Supports separate independent but reproducible streams for
         : each instance. However, the corresponding hoc Random
         : distribution MUST be set to Random.uniform(0,1)
         */
        _lgrand = nrn_random_pick(_p_donotuse);
    }else{
        /* only can be used in main thread */
        if (_nt != nrn_threads) {
hoc_execerror("multithread random in InUnif"," only via hoc Random");
        }
ENDVERBATIM
        : the old standby. Cannot use if reproducible parallel sim
        : independent of nhost or which host this instance is on
        : is desired, since each instance on this cpu draws from
        : the same stream
        grand = normrand(0,1)
VERBATIM
    }
ENDVERBATIM
}

PROCEDURE noiseFromRandom() {
VERBATIM
 {
    void** pv = (void**)(&_p_donotuse);
    if (ifarg(1)) {
        *pv = nrn_random_arg(1);
    }else{
        *pv = (void*)0;
    }
 }
ENDVERBATIM
}
