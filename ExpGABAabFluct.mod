COMMENT
Two state kinetic scheme synapse described by rise time tau1,
and decay time constant tau2. The normalized peak condunductance is 1.
Decay time MUST be greater than rise time.

The solution of A->G->bath with rate constants 1/tau1 and 1/tau2 is
 A = a*exp(-t/tau1) and
 G = a*tau2/(tau2-tau1)*(-exp(-t/tau1) + exp(-t/tau2))
	where tau1 < tau2

If tau2-tau1 -> 0 then we have a alphasynapse.
and if tau1 -> 0 then we have just single exponential decay.

The factor is evaluated in the
initial block such that an event of weight 1 generates a
peak conductance of 1.

Because the solution is a sum of exponentials, the
coupled equations can be solved as a pair of independent equations
by the more efficient cnexp method.

ENDCOMMENT

NEURON {
	POINT_PROCESS ExpGABAabFluct
	RANGE tau1a, tau2a, tau1b, tau2b, ea, eb, i, sid, cid
	NONSPECIFIC_CURRENT i

	RANGE ga, gb
	GLOBAL totala, totalb

  RANGE std_Aa, std_Ba, std_Ab, std_Bb

  THREADSAFE : true only if every instance has its own distinct Random
  POINTER donotuse
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
}

PARAMETER {
  dt (ms)
	tau1a=.1 (ms) <1e-9,1e9>
	tau2a = 10 (ms) <1e-9,1e9>
	ea=0	(mV)
	tau1b=.1 (ms) <1e-9,1e9>
	tau2b = 10 (ms) <1e-9,1e9>
	eb=0	(mV)
	sid = -1 (1) : synapse id, from cell template
	cid = -1 (1) : id of cell to which this synapse is attached

  std_Aa	= 0.0030 (umho)	: standard dev of Aa
  std_Ba	= 0.0030 (umho)	: standard dev of Ba
  std_Ab	= 0.0030 (umho)	: standard dev of Ab
  std_Bb	= 0.0030 (umho)	: standard dev of Bb
}

ASSIGNED {
	v (mV)
	i (nA)
	ga (uS)
	factora
	totala (uS)
	gb (uS)
	factorb
	totalb (uS)

	exp_Aa
	exp_Ba
	amp_Aa	(umho)
	amp_Ba	(umho)
	Aa (uS)
	Ba (uS)

  exp_Ab
	exp_Bb
	amp_Ab	(umho)
	amp_Bb	(umho)
	Ab (uS)
	Bb (uS)

  donotuse
}

INITIAL {
	LOCAL tpa, tpb
	totala = 0
	totalb = 0
	if (tau1a/tau2a > .9999) {
		tau1a = .9999*tau2a
	}
	if (tau1b/tau2b > .9999) {
		tau1b = .9999*tau2b
	}
	Aa = 0
	Ba = 0
	Ab = 0
	Bb = 0
	tpa = (tau1a*tau2a)/(tau2a - tau1a) * log(tau2a/tau1a)
	factora = -exp(-tpa/tau1a) + exp(-tpa/tau2a)
	factora = 1/factora
	tpb = (tau1b*tau2b)/(tau2b - tau1b) * log(tau2b/tau1b)
	factorb = -exp(-tpb/tau1b) + exp(-tpb/tau2b)
	factorb = 1/factorb

  if(tau1a!=0) {
    exp_Aa = exp(-dt/tau1a)
    amp_Aa = std_Aa * sqrt( 1-exp(-2*dt/tau1a) )
  }
  if(tau2a!=0) {
    exp_Ba = exp(-dt/tau2a)
    amp_Ba = std_Ba * sqrt( 1-exp(-2*dt/tau2a) )
  }
  if(tau1b!=0) {
    exp_Ab = exp(-dt/tau1b)
    amp_Ab = std_Ab * sqrt( 1-exp(-2*dt/tau1b) )
  }
  if(tau2b!=0) {
    exp_Bb = exp(-dt/tau2b)
    amp_Bb = std_Bb * sqrt( 1-exp(-2*dt/tau2b) )
  }
}

BEFORE BREAKPOINT { : use grand()
  if(tau1a!=0) {
    Aa =  Aa * exp_Aa + amp_Aa * grand()
  }
  if(tau2a!=0) {
    Ba =  Ba * exp_Ba + amp_Ba * grand()
  }
  if(tau1b!=0) {
    Ab =  Ab * exp_Ab + amp_Ab * grand()
  }
  if(tau2b!=0) {
    Bb =  Bb * exp_Bb + amp_Bb * grand()
  }
}

AFTER SOLVE {
  if(tau1a==0) {
    Aa =  std_Aa * grand()
  }
  if(tau2a==0) {
    Ba =  std_Ba * grand()
  }
  ga = Ba - Aa
  if (ga < 0) { ga = 0 }

  if(tau1b==0) {
    Ab =  std_Ab * grand()
  }
  if(tau2b==0) {
    Bb =  std_Bb * grand()
  }
	gb = Bb - Ab
  if (gb < 0) { gb = 0 }

	i = ga*(v - ea) + gb*(v - eb)
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
         : distribution MUST be set to Random.normal(0,1)
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

PROCEDURE new_seed(seed) {		: procedure to set the seed
	set_seed(seed)
	VERBATIM
	  printf("Setting random generator with seed = %g\n", _lseed);
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

NET_RECEIVE(weight (uS)) {
	LOCAL srcid, w
	if (weight > 999) {
		srcid = floor(weight/1000) - 1
		w = weight - (srcid+1)*1000
	}else{
		w = weight
	}
	Aa = Aa + w*factora
	Ba = Ba + w*factora
	totala = totala+w
	Ab = Ab + w*factorb/3.37
	Bb = Bb + w*factorb/3.37
	totalb = totalb+w/3.37
}
