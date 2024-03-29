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
 
#define nrn_init _nrn_init__SGate
#define _nrn_initial _nrn_initial__SGate
#define nrn_cur _nrn_cur__SGate
#define _nrn_current _nrn_current__SGate
#define nrn_jacob _nrn_jacob__SGate
#define nrn_state _nrn_state__SGate
#define _net_receive _net_receive__SGate 
#define noiseFromRandom noiseFromRandom__SGate 
#define seed seed__SGate 
 
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
#define period _p[0]
#define number _p[1]
#define start _p[2]
#define depth _p[3]
#define phase _p[4]
#define gid _p[5]
#define randi _p[6]
#define on _p[7]
#define numtogo _p[8]
#define r _p[9]
#define v _p[10]
#define _tsav _p[11]
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
 static double _hoc_erand();
 static double _hoc_noiseFromRandom();
 static double _hoc_p();
 static double _hoc_seed();
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
 "erand", _hoc_erand,
 "noiseFromRandom", _hoc_noiseFromRandom,
 "p", _hoc_p,
 "seed", _hoc_seed,
 0, 0
};
#define erand erand_SGate
#define p p_SGate
 extern double erand( _threadargsproto_ );
 extern double p( _threadargsprotocomma_ double );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "depth", 0, 1,
 "number", 0, 1e+09,
 "period", 1e-09, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "period", "ms",
 "start", "ms",
 "phase", "ms",
 0,0
};
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"SGate",
 "period",
 "number",
 "start",
 "depth",
 "phase",
 "gid",
 "randi",
 0,
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
 	_p = nrn_prop_data_alloc(_mechtype, 12, _prop);
 	/*initialize range parameters*/
 	period = 100;
 	number = 1;
 	start = 50;
 	depth = 0;
 	phase = 0;
 	gid = 0;
 	randi = 0;
  }
 	_prop->param = _p;
 	_prop->param_size = 12;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 
#define _tqitem &(_ppvar[3]._pvoid)
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _sgate_reg() {
	int _vectorized = 1;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,(void*)0, (void*)0, (void*)0, nrn_init,
	 hoc_nrnpointerindex, 1,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 12, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "pointer");
  hoc_register_dparam_semantics(_mechtype, 3, "netsend");
 add_nrn_artcell(_mechtype, 3);
 add_nrn_has_net_event(_mechtype);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 SGate /home/pedroernesto/Documents/Project/Code/Models_Validation/Models_to_test/Hippocampus/BezaireSoltesz_CA1model/modeldbca1/sgate.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 
#define PI _nrnunit_PI[_nrnunit_use_legacy_]
static double _nrnunit_PI[2] = {0x1.921fb54442d18p+1, 3.14159}; /* 3.14159265358979312 */
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int noiseFromRandom(_threadargsproto_);
static int seed(_threadargsprotocomma_ double);
 
static int  seed ( _threadargsprotocomma_ double _lx ) {
   set_seed ( _lx ) ;
    return 0; }
 
static double _hoc_seed(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r = 1.;
 seed ( _p, _ppvar, _thread, _nt, *getarg(1) );
 return(_r);
}
 
/*VERBATIM*/
double nrn_random_pick(void* r);
void* nrn_random_arg(int argpos);
 
double erand ( _threadargsproto_ ) {
   double _lerand;
 
/*VERBATIM*/
  if (_p_donotuse) {
    /*
    :Supports separate independent but reproducible streams for
    : each instance. However, the corresponding hoc Random
    : distribution MUST be set to Random.uniform(0,1)
    */
    _lerand = nrn_random_pick(_p_donotuse);
  }else{
    /* only can be used in main thread */
    if (_nt != nrn_threads) {
hoc_execerror("multithread random in NetStim"," only via hoc Random");
    }
 _lerand = scop_random ( ) ;
   
/*VERBATIM*/
  }
 
return _lerand;
 }
 
static double _hoc_erand(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  erand ( _p, _ppvar, _thread, _nt );
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
 
double p ( _threadargsprotocomma_ double _lt ) {
   double _lp;
 _lp = 0.0 ;
   if ( on  == 1.0 ) {
     _lp = 1.0 + depth * ( cos ( 2.0 * PI * ( _lt - phase ) / period ) - 1.0 ) / 2.0 ;
     }
   
return _lp;
 }
 
static double _hoc_p(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  p ( _p, _ppvar, _thread, _nt, *getarg(1) );
 return(_r);
}
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{  double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _thread = (Datum*)0; _nt = (_NrnThread*)_pnt->_vnt;   _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   if ( _lflag  == 0.0 ) {
     if ( on  == 1.0 ) {
       r = erand ( _threadargs_ ) ;
       if ( r < p ( _threadargscomma_ t ) ) {
         net_event ( _pnt, t ) ;
         }
       }
     }
   else if ( _lflag  == 1.0 ) {
     if ( numtogo > 0.0 ) {
       on = 1.0 ;
       numtogo = numtogo - 1.0 ;
       artcell_net_send ( _tqitem, _args, _pnt, t +  period , 1.0 ) ;
       }
     else {
       on = 0.0 ;
       }
     }
   } }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
 {
   if ( period < 0.0 ) {
     period = 1e9 ;
     }
   if ( number < 0.0 ) {
     number = 0.0 ;
     }
   if ( start < 0.0 ) {
     start = 0.0 ;
     }
   if ( phase < 0.0 ) {
     phase = 0.0 ;
     }
   if ( depth < 0.0 ) {
     depth = 0.0 ;
     }
   if ( depth > 1.0 ) {
     depth = 1.0 ;
     }
   on = 0.0 ;
   if ( number > 0.0 ) {
     numtogo = number ;
     artcell_net_send ( _tqitem, (double*)0, _ppvar[1]._pvoid, t +  start , 1.0 ) ;
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
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{
} return _current;
}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
 v=_v;
{
}}

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
static const char* nmodl_filename = "/home/pedroernesto/Documents/Project/Code/Models_Validation/Models_to_test/Hippocampus/BezaireSoltesz_CA1model/modeldbca1/sgate.mod";
static const char* nmodl_file_text = 
  ": sgate.mod\n"
  ": draws from netstim.mod 2212 2008-09-08 14:32:26Z hines\n"
  ": Passes a fraction of \"input\" events that arrive while it is on.\n"
  ": The fraction fluctuates between 1 (100%) and 1-depth (0<=depth<=1)\n"
  ": and is governed by\n"
  ":   p(t) = 1 + depth*(cos(2*PI*(t-start)/period) - 1)/2\n"
  ":   p(t) = 1 + depth*(cos(2*PI*(t-phase)/period) - 1)/2\n"
  ": where\n"
  ":   depth = modulation depth (0..1, 1 == pass all, 0 == pass none, 0.5 = pass half)\n"
  ":   period = duration of a modulation cycle\n"
  ":   start = time at which modulation begins\n"
  ": Gate is on for \"number\" modulation cycles\n"
  "\n"
  "COMMENT\n"
  "Supplied (written?) by Ted Carnevale\n"
  "This mechanism can be combined with a NetStim that has noise=1 \n"
  "to implement a non-homogeneous Poisson process.\n"
  "Quoting from http://en.wikipedia.org/wiki/Non-homogeneous_Poisson_process\n"
  "retrieved on 5/1/2012:\n"
  "\"To simulate a non-homogeneous Poisson process with intensity function \n"
  "\n"
  "(t), \n"
  "choose a sufficiently large \n"
  "\n"
  " so that \n"
  "\n"
  "(t) = \n"
  "\n"
  " p(t) and simulate a Poisson \n"
  "process with rate parameter \n"
  "\n"
  ". Accept an event from the Poisson simulation at \n"
  "time t with probability p(t).\"\n"
  "This statement cited Ross, Sheldon M. (2006). Simulation. Academic Press. p. 32.\n"
  "Note:  fifth edition is planned for 11/29/2012\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON  { \n"
  "  ARTIFICIAL_CELL SGate : \"Stochastic Gate\"\n"
  "  RANGE period, number, start, phase\n"
  "  RANGE depth, gid, randi\n"
  "  THREADSAFE : only true if every instance has its own distinct Random\n"
  "  POINTER donotuse\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "  PI = (pi) (1)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "  period = 100 (ms) <1e-9,1e9>: duration of a modulation cycle (msec)\n"
  "  number = 1 <0,1e9> : number of modulation cycles\n"
  "  start = 50 (ms) : start of first cycle\n"
  "  depth = 0 <0,1> : modulation depth\n"
  "  phase = 0 (ms): peak of first cycle\n"
  "	gid = 0\n"
  "	randi = 0\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "  on (1)\n"
  "  donotuse\n"
  "  numtogo (1) : how many modulation cycles remain to be launched\n"
  "  r (1)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "  if (period < 0) { period = 1e9 }\n"
  "  if (number < 0) { number = 0 }\n"
  "  if (start < 0) { start = 0 }\n"
  "  if (phase < 0) { phase = 0 }\n"
  "  if (depth < 0) { depth = 0 }\n"
  "  if (depth > 1) { depth = 1 }\n"
  "\n"
  "  on = 0 : off--no events pass\n"
  "  if (number > 0) {\n"
  "    numtogo = number\n"
  "    net_send(start, 1) : to turn gate on\n"
  "  }\n"
  "}  \n"
  "\n"
  "PROCEDURE seed(x) {\n"
  "  set_seed(x)\n"
  "}\n"
  "\n"
  "VERBATIM\n"
  "double nrn_random_pick(void* r);\n"
  "void* nrn_random_arg(int argpos);\n"
  "ENDVERBATIM\n"
  "\n"
  "FUNCTION erand() {\n"
  "VERBATIM\n"
  "  if (_p_donotuse) {\n"
  "    /*\n"
  "    :Supports separate independent but reproducible streams for\n"
  "    : each instance. However, the corresponding hoc Random\n"
  "    : distribution MUST be set to Random.uniform(0,1)\n"
  "    */\n"
  "    _lerand = nrn_random_pick(_p_donotuse);\n"
  "  }else{\n"
  "    /* only can be used in main thread */\n"
  "    if (_nt != nrn_threads) {\n"
  "hoc_execerror(\"multithread random in NetStim\",\" only via hoc Random\");\n"
  "    }\n"
  "ENDVERBATIM\n"
  "    : the old standby. Cannot use if reproducible parallel sim\n"
  "    : independent of nhost or which host this instance is on\n"
  "    : is desired, since each instance on this cpu draws from\n"
  "    : the same stream\n"
  "    erand = scop_random()\n"
  "VERBATIM\n"
  "  }\n"
  "ENDVERBATIM\n"
  "}\n"
  "\n"
  "PROCEDURE noiseFromRandom() {\n"
  "VERBATIM\n"
  " {\n"
  "  void** pv = (void**)(&_p_donotuse);\n"
  "  if (ifarg(1)) {\n"
  "    *pv = nrn_random_arg(1);\n"
  "  }else{\n"
  "    *pv = (void*)0;\n"
  "  }\n"
  " }\n"
  "ENDVERBATIM\n"
  "}\n"
  "\n"
  ":   p(t) = 1 + depth*(cos(2*PI*(t-phase)/period) - 1)/2\n"
  "\n"
  "FUNCTION p(t (ms)) {\n"
  "  p = 0\n"
  "  if (on == 1) {\n"
  "    p = 1 + depth*(cos(2*PI*(t-phase)/period) - 1)/2\n"
  "  }\n"
  "}\n"
  "\n"
  ": flag  action\n"
  ": 0     if ON, decide whether to pass event\n"
  ": 1     decide whether to start a modulation cycle\n"
  "NET_RECEIVE (w) {\n"
  "  if (flag == 0) { : external event\n"
  "    if (on == 1) {\n"
  "      : decide whether to pass this event\n"
  "        r = erand()\n"
  "        if (r < p(t)) { net_event(t) }\n"
  "    }\n"
  "  } else if (flag == 1) {\n"
  "    if (numtogo>0) { : launch a new cycle\n"
  "      on = 1\n"
  "      numtogo = numtogo-1\n"
  "      net_send(period, 1) : to end this cycle\n"
  "    } else { : all done\n"
  "      on = 0\n"
  "    }\n"
  "  }\n"
  "}\n"
  ;
#endif
