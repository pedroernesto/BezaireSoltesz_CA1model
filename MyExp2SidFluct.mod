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

ENDCOMMENT

NEURON {
  POINT_PROCESS MyExp2SidFluct
  RANGE tau1, tau2, e, i, sid, cid
  NONSPECIFIC_CURRENT i

  RANGE g
  GLOBAL total

  RANGE std_A, std_B, exp_A, exp_B, amp_A, amp_B

  : THREADSAFE : only true if every instance has its own distinct Random
  POINTER donotuse2
}

UNITS {
  (nA) = (nanoamp)
  (mV) = (millivolt)
  (uS) = (microsiemens)
}

PARAMETER {
  dt (ms)
	tau1=.1 (ms) <1e-9,1e9>
	tau2 = 10 (ms) <1e-9,1e9>
	e=0	(mV)
	sid = -1 (1) : synapse id, from cell template
	cid = -1 (1) : id of cell to which this synapse is attached

  std_A	= 0.0030 (uS)	: standard dev of A
	std_B	= 0.0030 (uS)	: standard dev of B
}

ASSIGNED {
	v (mV)
	i (nA)
	g (uS)
	factor
	total (uS)

	exp_A
	exp_B
	amp_A	(uS)
	amp_B	(uS)

  A (uS)
	B (uS)
  donotuse2
}

INITIAL {
	LOCAL tp
	total = 0
	if (tau1/tau2 > .9999) {
		tau1 = .9999*tau2
	}
	A = 0
	B = 0
	tp = (tau1*tau2)/(tau2 - tau1) * log(tau2/tau1)
	factor = -exp(-tp/tau1) + exp(-tp/tau2)
	factor = 1/factor
}

BEFORE BREAKPOINT { : use grand()
  if(tau1!=0) {
    exp_A = exp(-dt/tau1)
    amp_A = std_A * sqrt( 1-exp(-2*dt/tau1) )
    A =  A * exp_A + amp_A * normrand(0,1) : grand()
  }else{
    A = std_A * normrand(0,1) : grand()
  }

  if(tau2!=0) {
    exp_B = exp(-dt/tau2)
    amp_B = std_B * sqrt( 1-exp(-2*dt/tau2) )
    B = B * exp_B + amp_B * normrand(0,1) : grand()
  }else{
    B = std_B * normrand(0,1) : grand()
  }
}

AFTER SOLVE {
  g = B - A
  if (g < 0) { g = 0 }
	i = g*(v - e)
}

NET_RECEIVE(weight (uS)) {
  LOCAL srcid, w
	if (weight > 999) {
		srcid = floor(weight/1000) - 1
		w = weight - (srcid+1)*1000
	}else{
		w = weight
	}
	A = A + w*factor
  B = B + w*factor
  total = total+w
}

PROCEDURE print_vars() {
  VERBATIM
    printf("MyExp2SidFluct %f, %f, %1.20f", A, B, g);
  ENDVERBATIM
}

FUNCTION name() {
  VERBATIM
    return 2;
  ENDVERBATIM
}

COMMENT
VERBATIM
double nrn_random_pick(void* r);
void* nrn_random_arg(int argpos);
ENDVERBATIM

FUNCTION grand() {
  VERBATIM
  if (_p_donotuse2) {
      /*
       : Supports separate independent but reproducible streams for
       : each instance. However, the corresponding hoc Random
       : distribution MUST be set to Random.normal(0,1)
       */
      _lgrand = nrn_random_pick(_p_donotuse2);
  }else{
      /* only can be used in main thread */
      if (_nt != nrn_threads) {
        hoc_execerror("Random object ref not set correctly for donotuse2"," only via hoc Random");
      }
  }
  ENDVERBATIM
}

PROCEDURE noiseFromRandom() {
  VERBATIM
  void** pv = (void**)(&_p_donotuse2);
  if (ifarg(1)) {
      *pv = nrn_random_arg(1);
  }else{
      *pv = (void*)0;
  }
  ENDVERBATIM
}
ENDCOMMENT
