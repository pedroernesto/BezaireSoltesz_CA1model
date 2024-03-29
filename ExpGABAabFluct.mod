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
	POINT_PROCESS ExpGABAabFluct
	RANGE tau1a, tau2a, tau1b, tau2b, ea, eb, i, sid, cid
	NONSPECIFIC_CURRENT i

	RANGE ga, gb
	GLOBAL totala, totalb

  RANGE seed, set_std, set_GABAa, is_GABA
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
}

PARAMETER {
	tau1a=.1 (ms) <1e-9,1e9>
	tau2a = 10 (ms) <1e-9,1e9>
	ea=0	(mV)
	tau1b=.1 (ms) <1e-9,1e9>
	tau2b = 10 (ms) <1e-9,1e9>
	eb=0	(mV)
	sid = -1 (1) : synapse id, from cell template
	cid = -1 (1) : id of cell to which this synapse is attached

  std_Ba	= 0.00001 (uS)	: standard dev of Ba
  std_Bb	= 0.00001 (uS)	: standard dev of Bb

  is_GABA = 1 (1)
  FrGABAa = 0.5 (1)    : fraction of GABAa maximal conductance
  dt (ms)
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

  gBa_n (uS)
  gBb_n (uS)
}

STATE {
	Aa (uS)
	Ab (uS)
  Ba (uS)
  Bb (uS)
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

  gBa_n = 0
  gBb_n = 0
}

PROCEDURE seed(a) {
	set_seed(a)
}

PROCEDURE set_std(std (uS)) {
  std_Ba = std
  std_Bb = std
}

PROCEDURE set_GABAa(frac (1)) {
  FrGABAa = frac
}

BREAKPOINT {
	SOLVE state METHOD cnexp
	ga = Ba - Aa + gBa_n
  if (ga <= 0) {ga = Ba - Aa}
  ga = FrGABAa*ga

	gb = Bb - Ab + gBb_n
  if (gb <= 0) {gb = Bb - Ab}
	i = ga*(v - ea) + gb*(v - eb)
}

DERIVATIVE state {
	Aa' = -Aa/tau1a
	Ab' = -Ab/tau1b
  Ba' = -Ba/tau2a
  Bb' = -Bb/tau2b
}

AFTER SOLVE {
  if(tau2a!=0) {
    gBa_n = std_Ba * sqrt(2/tau2a) * normrand(0,sqrt(dt))
  }else{
    gBa_n = std_Ba * normrand(0,sqrt(dt))
  }

  if(tau2b!=0) {
    gBa_n = std_Bb * sqrt(2/tau2b) * normrand(0,sqrt(dt))
  }else{
    gBb_n = std_Bb * normrand(0,sqrt(dt))
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
	Aa = Aa + w*factora
	Ba = Ba + w*factora
	totala = totala+w
	Ab = Ab + w*factorb/3.37
	Bb = Bb + w*factorb/3.37
	totalb = totalb+w/3.37
}
