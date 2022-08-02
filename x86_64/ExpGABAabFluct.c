/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__ExpGABAabFluct
#define _nrn_initial _nrn_initial__ExpGABAabFluct
#define nrn_cur _nrn_cur__ExpGABAabFluct
#define _nrn_current _nrn_current__ExpGABAabFluct
#define nrn_jacob _nrn_jacob__ExpGABAabFluct
#define nrn_state _nrn_state__ExpGABAabFluct
#define _net_receive _net_receive__ExpGABAabFluct 
#define noiseFromRandom noiseFromRandom__ExpGABAabFluct 
#define new_seed new_seed__ExpGABAabFluct 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define tau1a _p[0]
#define tau2a _p[1]
#define ea _p[2]
#define tau1b _p[3]
#define tau2b _p[4]
#define eb _p[5]
#define sid _p[6]
#define cid _p[7]
#define std_Aa _p[8]
#define std_Ba _p[9]
#define std_Ab _p[10]
#define std_Bb _p[11]
#define i _p[12]
#define ga _p[13]
#define gb _p[14]
#define factora _p[15]
#define factorb _p[16]
#define exp_Aa _p[17]
#define exp_Ba _p[18]
#define amp_Aa _p[19]
#define amp_Ba _p[20]
#define Aa _p[21]
#define Ba _p[22]
#define exp_Ab _p[23]
#define exp_Bb _p[24]
#define amp_Ab _p[25]
#define amp_Bb _p[26]
#define Ab _p[27]
#define Bb _p[28]
#define v _p[29]
#define _tsav _p[30]
#define _nd_area  *_ppvar[0]._pval
#define donotuse	*_ppvar[2]._pval
#define _p_donotuse	_ppvar[2]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  2;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 /* declaration of user functions */
 static double _hoc_grand();
 static double _hoc_noiseFromRandom();
 static double _hoc_new_seed();
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "grand", _hoc_grand,
 "noiseFromRandom", _hoc_noiseFromRandom,
 "new_seed", _hoc_new_seed,
 0, 0
};
#define grand grand_ExpGABAabFluct
 extern double grand( _threadargsproto_ );
 /* declare global and static user variables */
 static int _thread1data_inuse = 0;
static double _thread1data[2];
#define _gth 0
#define totalb_ExpGABAabFluct _thread1data[0]
#define totalb _thread[_gth]._pval[0]
#define totala_ExpGABAabFluct _thread1data[1]
#define totala _thread[_gth]._pval[1]
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "tau2b", 1e-09, 1e+09,
 "tau1b", 1e-09, 1e+09,
 "tau2a", 1e-09, 1e+09,
 "tau1a", 1e-09, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "totala_ExpGABAabFluct", "uS",
 "totalb_ExpGABAabFluct", "uS",
 "tau1a", "ms",
 "tau2a", "ms",
 "ea", "mV",
 "tau1b", "ms",
 "tau2b", "ms",
 "eb", "mV",
 "sid", "1",
 "cid", "1",
 "std_Aa", "umho",
 "std_Ba", "umho",
 "std_Ab", "umho",
 "std_Bb", "umho",
 "i", "nA",
 "ga", "uS",
 "gb", "uS",
 0,0
};
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "totala_ExpGABAabFluct", &totala_ExpGABAabFluct,
 "totalb_ExpGABAabFluct", &totalb_ExpGABAabFluct,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void _ba1() , _ba2() ;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"ExpGABAabFluct",
 "tau1a",
 "tau2a",
 "ea",
 "tau1b",
 "tau2b",
 "eb",
 "sid",
 "cid",
 "std_Aa",
 "std_Ba",
 "std_Ab",
 "std_Bb",
 0,
 "i",
 "ga",
 "gb",
 0,
 0,
 "donotuse",
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 31, _prop);
 	/*initialize range parameters*/
 	tau1a = 0.1;
 	tau2a = 10;
 	ea = 0;
 	tau1b = 0.1;
 	tau2b = 10;
 	eb = 0;
 	sid = -1;
 	cid = -1;
 	std_Aa = 0.003;
 	std_Ba = 0.003;
 	std_Ab = 0.003;
 	std_Bb = 0.003;
  }
 	_prop->param = _p;
 	_prop->param_size = 31;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 static void _net_receive(Point_process*, double*, double);
 static void _thread_mem_init(Datum*);
 static void _thread_cleanup(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _ExpGABAabFluct_reg() {
	int _vectorized = 1;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,(void*)0, (void*)0, (void*)0, nrn_init,
	 hoc_nrnpointerindex, 2,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
  _extcall_thread = (Datum*)ecalloc(1, sizeof(Datum));
  _thread_mem_init(_extcall_thread);
  _thread1data_inuse = 0;
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 1, _thread_mem_init);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 31, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "pointer");
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_reg_ba(_mechtype, _ba1, 11);
 	hoc_reg_ba(_mechtype, _ba2, 22);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 ExpGABAabFluct /home/pedroernesto/Documents/Project/Code/Models_Validation/Models_to_test/Hippocampus/BezaireSoltesz_CA1model/modeldbca1/ExpGABAabFluct.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int noiseFromRandom(_threadargsproto_);
static int new_seed(_threadargsprotocomma_ double);
 /* BEFORE BREAKPOINT */
 static void _ba1(Node*_nd, double* _pp, Datum* _ppd, Datum* _thread, _NrnThread* _nt)  {
   double* _p; Datum* _ppvar; _p = _pp; _ppvar = _ppd;
  v = NODEV(_nd);
 if ( tau1a  != 0.0 ) {
     Aa = Aa * exp_Aa + amp_Aa * grand ( _threadargs_ ) ;
     }
   if ( tau2a  != 0.0 ) {
     Ba = Ba * exp_Ba + amp_Ba * grand ( _threadargs_ ) ;
     }
   if ( tau1b  != 0.0 ) {
     Ab = Ab * exp_Ab + amp_Ab * grand ( _threadargs_ ) ;
     }
   if ( tau2b  != 0.0 ) {
     Bb = Bb * exp_Bb + amp_Bb * grand ( _threadargs_ ) ;
     }
   }
 /* AFTER SOLVE */
 static void _ba2(Node*_nd, double* _pp, Datum* _ppd, Datum* _thread, _NrnThread* _nt)  {
   double* _p; Datum* _ppvar; _p = _pp; _ppvar = _ppd;
  v = NODEV(_nd);
 if ( tau1a  == 0.0 ) {
     Aa = std_Aa * grand ( _threadargs_ ) ;
     }
   if ( tau2a  == 0.0 ) {
     Ba = std_Ba * grand ( _threadargs_ ) ;
     }
   ga = Ba - Aa ;
   if ( ga < 0.0 ) {
     ga = 0.0 ;
     }
   if ( tau1b  == 0.0 ) {
     Ab = std_Ab * grand ( _threadargs_ ) ;
     }
   if ( tau2b  == 0.0 ) {
     Bb = std_Bb * grand ( _threadargs_ ) ;
     }
   gb = Bb - Ab ;
   if ( gb < 0.0 ) {
     gb = 0.0 ;
     }
   i = ga * ( v - ea ) + gb * ( v - eb ) ;
   }
 
/*VERBATIM*/
double nrn_random_pick(void* r);
void* nrn_random_arg(int argpos);
 
double grand ( _threadargsproto_ ) {
   double _lgrand;
 
/*VERBATIM*/
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
 _lgrand = normrand ( 0.0 , 1.0 ) ;
   
/*VERBATIM*/
    }
 
return _lgrand;
 }
 
static double _hoc_grand(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  grand ( _p, _ppvar, _thread, _nt );
 return(_r);
}
 
static int  new_seed ( _threadargsprotocomma_ double _lseed ) {
   set_seed ( _lseed ) ;
   
/*VERBATIM*/
	  printf("Setting random generator with seed = %g\n", _lseed);
  return 0; }
 
static double _hoc_new_seed(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r = 1.;
 new_seed ( _p, _ppvar, _thread, _nt, *getarg(1) );
 return(_r);
}
 
static int  noiseFromRandom ( _threadargsproto_ ) {
   
/*VERBATIM*/
 {
    void** pv = (void**)(&_p_donotuse);
    if (ifarg(1)) {
        *pv = nrn_random_arg(1);
    }else{
        *pv = (void*)0;
    }
 }
  return 0; }
 
static double _hoc_noiseFromRandom(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r = 1.;
 noiseFromRandom ( _p, _ppvar, _thread, _nt );
 return(_r);
}
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{  double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _thread = (Datum*)0; _nt = (_NrnThread*)_pnt->_vnt;   _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t; {
   double _lsrcid , _lw ;
 if ( _args[0] > 999.0 ) {
     _lsrcid = floor ( _args[0] / 1000.0 ) - 1.0 ;
     _lw = _args[0] - ( _lsrcid + 1.0 ) * 1000.0 ;
     }
   else {
     _lw = _args[0] ;
     }
   Aa = Aa + _lw * factora ;
   Ba = Ba + _lw * factora ;
   totala = totala + _lw ;
   Ab = Ab + _lw * factorb / 3.37 ;
   Bb = Bb + _lw * factorb / 3.37 ;
   totalb = totalb + _lw / 3.37 ;
   } }
 
static void _thread_mem_init(Datum* _thread) {
  if (_thread1data_inuse) {_thread[_gth]._pval = (double*)ecalloc(2, sizeof(double));
 }else{
 _thread[_gth]._pval = _thread1data; _thread1data_inuse = 1;
 }
 }
 
static void _thread_cleanup(Datum* _thread) {
  if (_thread[_gth]._pval == _thread1data) {
   _thread1data_inuse = 0;
  }else{
   free((void*)_thread[_gth]._pval);
  }
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
 {
   double _ltpa , _ltpb ;
 totala = 0.0 ;
   totalb = 0.0 ;
   if ( tau1a / tau2a > .9999 ) {
     tau1a = .9999 * tau2a ;
     }
   if ( tau1b / tau2b > .9999 ) {
     tau1b = .9999 * tau2b ;
     }
   Aa = 0.0 ;
   Ba = 0.0 ;
   Ab = 0.0 ;
   Bb = 0.0 ;
   _ltpa = ( tau1a * tau2a ) / ( tau2a - tau1a ) * log ( tau2a / tau1a ) ;
   factora = - exp ( - _ltpa / tau1a ) + exp ( - _ltpa / tau2a ) ;
   factora = 1.0 / factora ;
   _ltpb = ( tau1b * tau2b ) / ( tau2b - tau1b ) * log ( tau2b / tau1b ) ;
   factorb = - exp ( - _ltpb / tau1b ) + exp ( - _ltpb / tau2b ) ;
   factorb = 1.0 / factorb ;
   if ( tau1a  != 0.0 ) {
     exp_Aa = exp ( - dt / tau1a ) ;
     amp_Aa = std_Aa * sqrt ( 1.0 - exp ( - 2.0 * dt / tau1a ) ) ;
     }
   if ( tau2a  != 0.0 ) {
     exp_Ba = exp ( - dt / tau2a ) ;
     amp_Ba = std_Ba * sqrt ( 1.0 - exp ( - 2.0 * dt / tau2a ) ) ;
     }
   if ( tau1b  != 0.0 ) {
     exp_Ab = exp ( - dt / tau1b ) ;
     amp_Ab = std_Ab * sqrt ( 1.0 - exp ( - 2.0 * dt / tau1b ) ) ;
     }
   if ( tau2b  != 0.0 ) {
     exp_Bb = exp ( - dt / tau2b ) ;
     amp_Bb = std_Bb * sqrt ( 1.0 - exp ( - 2.0 * dt / tau2b ) ) ;
     }
   }

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _tsav = -1e20;
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ _current += i;

} return _current;
}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type) {

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/pedroernesto/Documents/Project/Code/Models_Validation/Models_to_test/Hippocampus/BezaireSoltesz_CA1model/modeldbca1/ExpGABAabFluct.mod";
static const char* nmodl_file_text = 
  "COMMENT\n"
  "Two state kinetic scheme synapse described by rise time tau1,\n"
  "and decay time constant tau2. The normalized peak condunductance is 1.\n"
  "Decay time MUST be greater than rise time.\n"
  "\n"
  "The solution of A->G->bath with rate constants 1/tau1 and 1/tau2 is\n"
  " A = a*exp(-t/tau1) and\n"
  " G = a*tau2/(tau2-tau1)*(-exp(-t/tau1) + exp(-t/tau2))\n"
  "	where tau1 < tau2\n"
  "\n"
  "If tau2-tau1 -> 0 then we have a alphasynapse.\n"
  "and if tau1 -> 0 then we have just single exponential decay.\n"
  "\n"
  "The factor is evaluated in the\n"
  "initial block such that an event of weight 1 generates a\n"
  "peak conductance of 1.\n"
  "\n"
  "Because the solution is a sum of exponentials, the\n"
  "coupled equations can be solved as a pair of independent equations\n"
  "by the more efficient cnexp method.\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON {\n"
  "	POINT_PROCESS ExpGABAabFluct\n"
  "	RANGE tau1a, tau2a, tau1b, tau2b, ea, eb, i, sid, cid\n"
  "	NONSPECIFIC_CURRENT i\n"
  "\n"
  "	RANGE ga, gb\n"
  "	GLOBAL totala, totalb\n"
  "\n"
  "  RANGE std_Aa, std_Ba, std_Ab, std_Bb\n"
  "\n"
  "  THREADSAFE : true only if every instance has its own distinct Random\n"
  "  POINTER donotuse\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(nA) = (nanoamp)\n"
  "	(mV) = (millivolt)\n"
  "	(uS) = (microsiemens)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "  dt (ms)\n"
  "	tau1a=.1 (ms) <1e-9,1e9>\n"
  "	tau2a = 10 (ms) <1e-9,1e9>\n"
  "	ea=0	(mV)\n"
  "	tau1b=.1 (ms) <1e-9,1e9>\n"
  "	tau2b = 10 (ms) <1e-9,1e9>\n"
  "	eb=0	(mV)\n"
  "	sid = -1 (1) : synapse id, from cell template\n"
  "	cid = -1 (1) : id of cell to which this synapse is attached\n"
  "\n"
  "  std_Aa	= 0.0030 (umho)	: standard dev of Aa\n"
  "  std_Ba	= 0.0030 (umho)	: standard dev of Ba\n"
  "  std_Ab	= 0.0030 (umho)	: standard dev of Ab\n"
  "  std_Bb	= 0.0030 (umho)	: standard dev of Bb\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	v (mV)\n"
  "	i (nA)\n"
  "	ga (uS)\n"
  "	factora\n"
  "	totala (uS)\n"
  "	gb (uS)\n"
  "	factorb\n"
  "	totalb (uS)\n"
  "\n"
  "	exp_Aa\n"
  "	exp_Ba\n"
  "	amp_Aa	(umho)\n"
  "	amp_Ba	(umho)\n"
  "	Aa (uS)\n"
  "	Ba (uS)\n"
  "\n"
  "  exp_Ab\n"
  "	exp_Bb\n"
  "	amp_Ab	(umho)\n"
  "	amp_Bb	(umho)\n"
  "	Ab (uS)\n"
  "	Bb (uS)\n"
  "\n"
  "  donotuse\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	LOCAL tpa, tpb\n"
  "	totala = 0\n"
  "	totalb = 0\n"
  "	if (tau1a/tau2a > .9999) {\n"
  "		tau1a = .9999*tau2a\n"
  "	}\n"
  "	if (tau1b/tau2b > .9999) {\n"
  "		tau1b = .9999*tau2b\n"
  "	}\n"
  "	Aa = 0\n"
  "	Ba = 0\n"
  "	Ab = 0\n"
  "	Bb = 0\n"
  "	tpa = (tau1a*tau2a)/(tau2a - tau1a) * log(tau2a/tau1a)\n"
  "	factora = -exp(-tpa/tau1a) + exp(-tpa/tau2a)\n"
  "	factora = 1/factora\n"
  "	tpb = (tau1b*tau2b)/(tau2b - tau1b) * log(tau2b/tau1b)\n"
  "	factorb = -exp(-tpb/tau1b) + exp(-tpb/tau2b)\n"
  "	factorb = 1/factorb\n"
  "\n"
  "  if(tau1a!=0) {\n"
  "    exp_Aa = exp(-dt/tau1a)\n"
  "    amp_Aa = std_Aa * sqrt( 1-exp(-2*dt/tau1a) )\n"
  "  }\n"
  "  if(tau2a!=0) {\n"
  "    exp_Ba = exp(-dt/tau2a)\n"
  "    amp_Ba = std_Ba * sqrt( 1-exp(-2*dt/tau2a) )\n"
  "  }\n"
  "  if(tau1b!=0) {\n"
  "    exp_Ab = exp(-dt/tau1b)\n"
  "    amp_Ab = std_Ab * sqrt( 1-exp(-2*dt/tau1b) )\n"
  "  }\n"
  "  if(tau2b!=0) {\n"
  "    exp_Bb = exp(-dt/tau2b)\n"
  "    amp_Bb = std_Bb * sqrt( 1-exp(-2*dt/tau2b) )\n"
  "  }\n"
  "}\n"
  "\n"
  "BEFORE BREAKPOINT { : use grand()\n"
  "  if(tau1a!=0) {\n"
  "    Aa =  Aa * exp_Aa + amp_Aa * grand()\n"
  "  }\n"
  "  if(tau2a!=0) {\n"
  "    Ba =  Ba * exp_Ba + amp_Ba * grand()\n"
  "  }\n"
  "  if(tau1b!=0) {\n"
  "    Ab =  Ab * exp_Ab + amp_Ab * grand()\n"
  "  }\n"
  "  if(tau2b!=0) {\n"
  "    Bb =  Bb * exp_Bb + amp_Bb * grand()\n"
  "  }\n"
  "}\n"
  "\n"
  "AFTER SOLVE {\n"
  "  if(tau1a==0) {\n"
  "    Aa =  std_Aa * grand()\n"
  "  }\n"
  "  if(tau2a==0) {\n"
  "    Ba =  std_Ba * grand()\n"
  "  }\n"
  "  ga = Ba - Aa\n"
  "  if (ga < 0) { ga = 0 }\n"
  "\n"
  "  if(tau1b==0) {\n"
  "    Ab =  std_Ab * grand()\n"
  "  }\n"
  "  if(tau2b==0) {\n"
  "    Bb =  std_Bb * grand()\n"
  "  }\n"
  "	gb = Bb - Ab\n"
  "  if (gb < 0) { gb = 0 }\n"
  "\n"
  "	i = ga*(v - ea) + gb*(v - eb)\n"
  "}\n"
  "\n"
  "\n"
  "VERBATIM\n"
  "double nrn_random_pick(void* r);\n"
  "void* nrn_random_arg(int argpos);\n"
  "ENDVERBATIM\n"
  "\n"
  "FUNCTION grand() {\n"
  "VERBATIM\n"
  "    if (_p_donotuse) {\n"
  "        /*\n"
  "         : Supports separate independent but reproducible streams for\n"
  "         : each instance. However, the corresponding hoc Random\n"
  "         : distribution MUST be set to Random.normal(0,1)\n"
  "         */\n"
  "        _lgrand = nrn_random_pick(_p_donotuse);\n"
  "    }else{\n"
  "        /* only can be used in main thread */\n"
  "        if (_nt != nrn_threads) {\n"
  "          hoc_execerror(\"multithread random in InUnif\",\" only via hoc Random\");\n"
  "        }\n"
  "ENDVERBATIM\n"
  "        : the old standby. Cannot use if reproducible parallel sim\n"
  "        : independent of nhost or which host this instance is on\n"
  "        : is desired, since each instance on this cpu draws from\n"
  "        : the same stream\n"
  "        grand = normrand(0,1)\n"
  "VERBATIM\n"
  "    }\n"
  "ENDVERBATIM\n"
  "}\n"
  "\n"
  "PROCEDURE new_seed(seed) {		: procedure to set the seed\n"
  "	set_seed(seed)\n"
  "	VERBATIM\n"
  "	  printf(\"Setting random generator with seed = %g\\n\", _lseed);\n"
  "	ENDVERBATIM\n"
  "}\n"
  "\n"
  "PROCEDURE noiseFromRandom() {\n"
  "VERBATIM\n"
  " {\n"
  "    void** pv = (void**)(&_p_donotuse);\n"
  "    if (ifarg(1)) {\n"
  "        *pv = nrn_random_arg(1);\n"
  "    }else{\n"
  "        *pv = (void*)0;\n"
  "    }\n"
  " }\n"
  "ENDVERBATIM\n"
  "}\n"
  "\n"
  "NET_RECEIVE(weight (uS)) {\n"
  "	LOCAL srcid, w\n"
  "	if (weight > 999) {\n"
  "		srcid = floor(weight/1000) - 1\n"
  "		w = weight - (srcid+1)*1000\n"
  "	}else{\n"
  "		w = weight\n"
  "	}\n"
  "	Aa = Aa + w*factora\n"
  "	Ba = Ba + w*factora\n"
  "	totala = totala+w\n"
  "	Ab = Ab + w*factorb/3.37\n"
  "	Bb = Bb + w*factorb/3.37\n"
  "	totalb = totalb+w/3.37\n"
  "}\n"
  ;
#endif
