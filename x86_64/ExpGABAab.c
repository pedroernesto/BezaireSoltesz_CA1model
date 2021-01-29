/* Created by Language version: 6.2.0 */
/* NOT VECTORIZED */
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
 
#define _threadargscomma_ /**/
#define _threadargs_ /**/
 
#define _threadargsprotocomma_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define tau1a _p[0]
#define tau2a _p[1]
#define ea _p[2]
#define tau1b _p[3]
#define tau2b _p[4]
#define eb _p[5]
#define sid _p[6]
#define cid _p[7]
#define i _p[8]
#define ga _p[9]
#define gb _p[10]
#define Aa _p[11]
#define Ba _p[12]
#define Ab _p[13]
#define Bb _p[14]
#define factora _p[15]
#define factorb _p[16]
#define DAa _p[17]
#define DBa _p[18]
#define DAb _p[19]
#define DBb _p[20]
#define _g _p[21]
#define _tsav _p[22]
#define _nd_area  *_ppvar[0]._pval
 
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
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 /* declaration of user functions */
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
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
 _p = _prop->param; _ppvar = _prop->dparam;
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
 0, 0
};
 /* declare global and static user variables */
#define totalb totalb_ExpGABAab
 double totalb = 0;
#define totala totala_ExpGABAab
 double totala = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "tau2b", 1e-09, 1e+09,
 "tau1b", 1e-09, 1e+09,
 "tau2a", 1e-09, 1e+09,
 "tau1a", 1e-09, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "totala_ExpGABAab", "uS",
 "totalb_ExpGABAab", "uS",
 "tau1a", "ms",
 "tau2a", "ms",
 "ea", "mV",
 "tau1b", "ms",
 "tau2b", "ms",
 "eb", "mV",
 "sid", "1",
 "cid", "1",
 "Aa", "uS",
 "Ba", "uS",
 "Ab", "uS",
 "Bb", "uS",
 "i", "nA",
 "ga", "uS",
 "gb", "uS",
 0,0
};
 static double Ab0 = 0;
 static double Aa0 = 0;
 static double Bb0 = 0;
 static double Ba0 = 0;
 static double delta_t = 0.01;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "totala_ExpGABAab", &totala_ExpGABAab,
 "totalb_ExpGABAab", &totalb_ExpGABAab,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[2]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "6.2.0",
"ExpGABAab",
 "tau1a",
 "tau2a",
 "ea",
 "tau1b",
 "tau2b",
 "eb",
 "sid",
 "cid",
 0,
 "i",
 "ga",
 "gb",
 0,
 "Aa",
 "Ba",
 "Ab",
 "Bb",
 0,
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
 	_p = nrn_prop_data_alloc(_mechtype, 23, _prop);
 	/*initialize range parameters*/
 	tau1a = 0.1;
 	tau2a = 10;
 	ea = 0;
 	tau1b = 0.1;
 	tau2b = 10;
 	eb = 0;
 	sid = -1;
 	cid = -1;
  }
 	_prop->param = _p;
 	_prop->param_size = 23;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*f)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _ExpGABAab_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
  hoc_register_prop_size(_mechtype, 23, 3);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 ExpGABAab /home/pedroernesto/Documents/Project/Code/Models_Validation/Models_to_test/Hippocampus/BezaireSoltesz_CA1model/modeldbca1/x86_64/ExpGABAab.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[4], _dlist1[4];
 static int state(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   DAa = - Aa / tau1a ;
   DBa = - Ba / tau2a ;
   DAb = - Ab / tau1b ;
   DBb = - Bb / tau2b ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 DAa = DAa  / (1. - dt*( ( - 1.0 ) / tau1a )) ;
 DBa = DBa  / (1. - dt*( ( - 1.0 ) / tau2a )) ;
 DAb = DAb  / (1. - dt*( ( - 1.0 ) / tau1b )) ;
 DBb = DBb  / (1. - dt*( ( - 1.0 ) / tau2b )) ;
 return 0;
}
 /*END CVODE*/
 static int state () {_reset=0;
 {
    Aa = Aa + (1. - exp(dt*(( - 1.0 ) / tau1a)))*(- ( 0.0 ) / ( ( - 1.0 ) / tau1a ) - Aa) ;
    Ba = Ba + (1. - exp(dt*(( - 1.0 ) / tau2a)))*(- ( 0.0 ) / ( ( - 1.0 ) / tau2a ) - Ba) ;
    Ab = Ab + (1. - exp(dt*(( - 1.0 ) / tau1b)))*(- ( 0.0 ) / ( ( - 1.0 ) / tau1b ) - Ab) ;
    Bb = Bb + (1. - exp(dt*(( - 1.0 ) / tau2b)))*(- ( 0.0 ) / ( ( - 1.0 ) / tau2b ) - Bb) ;
   }
  return 0;
}
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{    _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
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
 
static int _ode_count(int _type){ return 4;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 ();
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 4; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol1 ();
 }}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  Ab = Ab0;
  Aa = Aa0;
  Bb = Bb0;
  Ba = Ba0;
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
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   ga = Ba - Aa ;
   gb = Bb - Ab ;
   i = ga * ( v - ea ) + gb * ( v - eb ) ;
   }
 _current += i;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _g = _nrn_current(_v + .001);
 	{ _rhs = _nrn_current(_v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
 double _break, _save;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _break = t + .5*dt; _save = t;
 v=_v;
{
 { {
 for (; t < _break; t += dt) {
 error =  state();
 if(error){fprintf(stderr,"at line 91 in file ExpGABAab.mod:\n	SOLVE state METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 }}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(Aa) - _p;  _dlist1[0] = &(DAa) - _p;
 _slist1[1] = &(Ba) - _p;  _dlist1[1] = &(DBa) - _p;
 _slist1[2] = &(Ab) - _p;  _dlist1[2] = &(DAb) - _p;
 _slist1[3] = &(Bb) - _p;  _dlist1[3] = &(DBb) - _p;
_first = 0;
}
