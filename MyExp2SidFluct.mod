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

  RANGE seed, set_std
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
}

PARAMETER {
	tau1=.1 (ms) <1e-9,1e9>
	tau2 = 10 (ms) <1e-9,1e9>
	e=0	(mV)
	sid = -1 (1) : synapse id, from cell template
	cid = -1 (1) : id of cell to which this synapse is attached

  std_B = 0.0030 (uS)	: standard dev of B
  dt (ms)
}

ASSIGNED {
	v (mV)
	i (nA)
	g (uS)
	factor
	total (uS)

  gB_n (uS)
}

STATE {
  A (uS)
  B (uS)
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

  gB_n = 0
}

PROCEDURE seed(a) {
	set_seed(a)
}

FUNCTION set_std(std (uS)) {
	std_B = std
}

BREAKPOINT {
	SOLVE state METHOD cnexp
	g = B - A + gB_n
  if (g<=0) {g = B-A}
  i = g*(v - e)
}

DERIVATIVE state {
  A' = -A/tau1
  B' = -B/tau2
}

AFTER SOLVE {
  if(tau2!=0) {
    gB_n = std_B * sqrt(2/tau2) * normrand(0,sqrt(dt))
  }else{
    gB_n = std_B * normrand(0,sqrt(dt))
  }
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
