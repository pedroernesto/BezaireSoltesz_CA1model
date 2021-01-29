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
 static void _hoc_install_fastconn(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_fastconn", _hoc_setdata,
 "install_fastconn", _hoc_install_fastconn,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 0,0
};
 static double v = 0;
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
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "6.2.0",
"fastconn",
 0,
 0,
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 0, _prop);
 	/*initialize range parameters*/
 	_prop->param = _p;
 	_prop->param_size = 0;
 
}
 static void _initlists();
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*f)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _fastconn_reg() {
	int _vectorized = 0;
  _initlists();
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 fastconn /home/pedroernesto/Documents/Project/Code/Models_Validation/Models_to_test/Hippocampus/BezaireSoltesz_CA1model/modeldbca1/x86_64/fastconn.mod\n");
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int install_fastconn();
 
/*VERBATIM*/
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
 
/*VERBATIM*/
extern double* vector_vec();
extern int vector_capacity();
extern void* vector_arg();
extern double get_x_pos(double gid, double gmin, double BinNumX, double BinNumYZ, double binSizeX);
extern double get_y_pos(double gid, double gmin, double BinNumY, double BinNumZ, double binSizeY);
extern double get_z_pos(double gid, double gmin, double BinNumZ, double binSizeZ, double ZHeight);
//void srand(unsigned seed);
 
/*VERBATIM*/

static  double fastconn (void* vv) {
  int finalconn, ny, nz, nhigh, num_pre, num_post, gmin, gmax, steps, myflaggy, myi, postgmin, stepover;
  double *x, *y, *z, *high, a, b, c, nconv, ncell, axonal_extent;

	/* Get hoc vectors into c arrays */
	finalconn = vector_instance_px(vv, &x); // x is an array corresponding
											// to the placeholder vector
											// of connections to make

	ny = vector_arg_px(1, &y); // y is an array of parameters
	nz = vector_arg_px(2, &z); // z is an array of the postsynaptic gids
	nhigh = vector_arg_px(3, &high); // high is an array of the starting high indices to use
	
	/* Load the parameters from the param array */
	gmin = y[0];	// presynaptic start gid
	gmax = y[1];	// presynaptic end gid
	num_pre = gmax - gmin + 1;	// number of presynaptic cells
	
	nconv = y[2];	// total number of desired connections
	ncell = y[3];	// total number of postsynaptic cells
	num_post = y[4];	// number of postsynaptic cells owned by this host
	axonal_extent = y[5];	// total distance over which distribution fits
	steps = y[6];	// resolution of the distribution fit (in steps)
	a = y[7];		// distribution fit coefficient a
	b = y[8];		// distribution fit coefficient b
	c = y[9];		// distribution fit coefficient c
	postgmin = y[24];	// postsynaptic start gid
	stepover = y[26];	// postsynaptic start gid

	myi=2+num_post;	// myi will give the next index into finalconn
			// 0 is reserved for # conns to make
			// 1 is reserved for # cells (each having an entry for their last high index used by nrnRan4int)

	/* Get positions of the presynaptic and postsynaptic cells*/

	// (1) a single NxM malloc: really this is a large 1-dim array of int values
	//     onto which we will map 2D accesses 
	// 

	// declaration and allocation:

	double *prepos;    // the type is a pointer to a double (the bucket type)
	prepos = (double *)malloc(sizeof(double)*num_pre*3);

	double *postpos;    // the type is a pointer to a double (the bucket type)
	postpos = (double *)malloc(sizeof(double)*num_post*3);

	// in memory: 
	//                   row 0       row 1     row 2 ...
	// 2d_array -----> [ 0, 0, ... , 0, 0, ... 0, 0, ... ] 

	// access using [] notation: 
	//    cannot use [i][j] syntax because the compiler has no idea where the 
	//    next row starts within this chunk of heap space, so must use single 
	//    index value that is calculated using row and column index values and 
	//    the column dimension

	int cell;

	for (cell=0; cell<num_pre; cell++) {
		prepos[cell*3 + 0] = get_x_pos(cell+gmin, gmin, y[10], y[11]*y[12], y[13]);
		prepos[cell*3 + 1] = get_y_pos(cell+gmin, gmin, y[11], y[12], y[14]);
		prepos[cell*3 + 2] = get_z_pos(cell+gmin, gmin, y[12], y[15], y[16]);
	}

	for (cell=0; cell<num_post; cell++) {
		postpos[cell*3 + 0] = get_x_pos(z[cell], postgmin, y[17], y[18]*y[19], y[20]);
		postpos[cell*3 + 1] = get_y_pos(z[cell], postgmin, y[18], y[19], y[21]);
		postpos[cell*3 + 2] = get_z_pos(z[cell], postgmin, y[19], y[22], y[23]);
	}

	/* calculate the distribution of desired connections*/   
	double current_distance [steps], connection_distribution [steps], distribution_denominator, conndist;
	int step, feasible_conns_this_step [steps], desired_conns_this_step [steps];

	distribution_denominator = 0.0;
	int max_fraction_step; max_fraction_step=0;
	for (step=0; step<steps; step++) {
		current_distance[step] = axonal_extent*1.0*(step+1)/(steps); /* current_distance[step] = distance step (in terms of max distance)*/
		//connection_distribution[step] = (1.0/a)*exp(-((current_distance[step]-b)*1.0/c)*((current_distance[step]-b)*1.0/c))*axonal_extent;
		connection_distribution[step] = exp(-a*((current_distance[step]-b)*1.0/c)*((current_distance[step]-b)*1.0/c));
		if (connection_distribution[step]>connection_distribution[max_fraction_step]) {
			max_fraction_step=step;
		}
		distribution_denominator = distribution_denominator + connection_distribution[step];
	}

	if (connection_distribution[max_fraction_step]/distribution_denominator*nconv < 0.5) { //distribution_denominator) { // nconv = nconn*1.0/ncell
		for (step=0; step<steps; step++) {
			desired_conns_this_step[step] = round((2.0*connection_distribution[step]/distribution_denominator)*(nconv));// the number of desired
															// connections for each
															// distance bin step, per cell
		}
	} else {
		for (step=0; step<steps; step++) {
			desired_conns_this_step[step] = round((connection_distribution[step]/distribution_denominator)*(nconv));// the number of desired
															// connections for each
															// distance bin step, per cell
		}
	}

	/* for each postsynaptic cell, find the possible connections and
	 * make the desired number of connections where possible */   
	int m, n, i, q, goupto, rem, extra, szr, szp [steps];
	double distance_between;
	u_int32_t idx1, idx2, maxidx1; // high and low index (seeds) for MCell_Ran4
	maxidx1 = y[25];

	for (n=0; n<num_post; n++) { // for each post cell
		int myx = (int)z[n]; // get the gid of the current postsynaptic cell in int form
		idx1 = high[n];	// reset the high index for the next postsynaptic
						// cell. It should be set to a value that is 
						// certainly higher than what would have been
						// used during previous calls for this low index/gid
						// We accomplish that by setting it equal to the
						// sum of all previous numconns/ncell (for this
						// post cell type, with the previous pre cell types)?
		idx2 = myx;		// set the low index equal to the gid


		double *sortedpos;    // the type is a pointer to a double (the bucket type)
		sortedpos = (double *)malloc(sizeof(double)*num_pre*steps);
		
		//double sortedpos [num_pre][steps];
		for (step=0; step< steps; step++) {
			szp [step]=0; 	// initialize the szp array to 0
							// (it holds a number per bin, telling which
							// index of the array you are on for that bin)
							// when filling the array with available
							// connections for each bin
			feasible_conns_this_step[step] = desired_conns_this_step[step];		
		}
		
		double dist;
		for(m=0; m<num_pre; m++) { // for each pre cell
			// calculate the distance between the pre and post cells
			distance_between = sqrt((1.0*prepos[m*3 +0] - postpos[n*3 +0])*(prepos[m*3 +0] - postpos[n*3 +0])+(prepos[m*3 +1] - postpos[n*3 +1])*(prepos[m*3 +1] - postpos[n*3 +1])+(prepos[m*3 +2] - postpos[n*3 +2])*(prepos[m*3 +2] - postpos[n*3 +2]));
			for (step=0; step< steps; step++) {
				/*if (ncell==2 && num_pre==3) {
					printf("distance=%f step=%d stepmax=%f gmin=%d postg=%d\n", distance_between, step, current_distance[step], gmin, postgmin);
				}*/

				if (distance_between<= current_distance[step]) // if the distance is less than the max distance for that step
				{
					sortedpos[szp [step]*steps + step] = m;
					//sortedpos [szp [step]] [step] = m;	// add this pre cell to this particular bin's column (the next row, which szp keeps track of)
					szp [step]++;
					break;
				}
			}
		}

		/*if (ncell==2 && num_pre==3) {
			for (step=0; step< steps; step++) {
				printf("step: %d  szp: %d\n", step, szp [step]);
			}
		}*/

		// now, this particular post cell has an array (sortedpos) where each
		// column contains a bunch of pre-cell gids whose distances fit within
		// that column's "step" or "distance bin"
		// There is also a feasible_conns_this_step array that gives the ideal # of connections
		// for each step
			
		rem=0;extra=0;
		for (step=0; step<steps; step++) {	// for each step except the last one
			szr = szp [step]; // Get the number of available connections for this step
			if (feasible_conns_this_step[step] + rem> szr) { //If more are wanted than are available,
				rem=feasible_conns_this_step[step]+rem-szr;
				// check the previous level (closer level) for extras
				if (step>0) {
					for(i=1; i<=step; i++) {
						if (szp [step-i] > feasible_conns_this_step[step-i]) {
							if (szp [step-i] - feasible_conns_this_step[step-i]>rem) {
								extra = rem;
							} else {
								extra = szp [step-i] - feasible_conns_this_step[step-i];
							}
							feasible_conns_this_step[step-i] = feasible_conns_this_step[step-i] + extra;
							feasible_conns_this_step[step] = feasible_conns_this_step[step] - extra;
							rem = rem - extra;				
						}
					}
				}
				if (rem>0 && step<steps-1) { // if that still doesn't satisfy all the remainder
					for(i=step+1; i<steps; i++) {				
						if (szp [i] > feasible_conns_this_step[i]) {
							if (szp [i] - feasible_conns_this_step[i]>rem) {
								extra = rem;
							} else {
								extra = szp [i] - feasible_conns_this_step[i];
							}
							feasible_conns_this_step[i] = feasible_conns_this_step[i] + extra;
							feasible_conns_this_step[step] = feasible_conns_this_step[step] - extra;
							rem = rem - extra;
						}
					}
				}
			}
		}

		/*if (ncell==2 && num_pre==3) {
			for (step=0; step< steps; step++) {
				printf("step: %d  szp: %d  feasible_conns_this_step: %d\n", step, szp [step], feasible_conns_this_step[step]);
			}
		}*/
	
		rem=0;
		for (step=0; step<steps; step++) {	// for each step
			if (feasible_conns_this_step[step]>0) { // if this particular step wants any connections
				/* Find all the possible connections for each distance level  */
				
				/*if (ncell==2 && num_pre==3) {
					printf("precells=%d postcells=%d step=%d szr=%d\n", num_pre, ncell, step, szr);
				}*/
				
				szr = szp [step]; // Get the number of available connections for this step
				int r[szr]; // Define an array the length of the number of available connections
				for (i=0; i< szr; i++) { 
					r[i] =  sortedpos[i*steps + step];
					//r[i] =  sortedpos [i] [step]; // Fill the array with the available connections (in terms of the pre cell)
				}

				/* this random routine allows a pre-cell to make multiple connections on the post cell*/
				int tmp;
				u_int32_t randi;
				for (i=0; i<szr-1; i++) {
					randi =  nrnRan4int(&idx1, idx2) % (u_int32_t)szr; // limit to the range of indices in the r array
					tmp = r [i];	// randomly reorganize the pre cells in the r array
					r[i] = r[randi];
					r[randi] = tmp;
				}

				if (feasible_conns_this_step[step]>szr) { 	// if the number of desired connections (ones wanted in this step, plus unmade ones from previous steps)
										// is more than the available amount, set the remainder to the excess ones that can't be made in this step
					goupto=szr;			// and set the number to make (based on the desired and available amts)
				} else {
					goupto=feasible_conns_this_step[step];	// set the number to make (based on the desired and available amts)
				}

				for (q=0; q<goupto; q++) { 	// for each one to make, r[q] gives the precell index in the pre_pos array (this program assumes
											// the gid range is continuous from gmin to gmax arguments to this mechanism.
											// n is the post-cell here. 
					x [myi] = (r[q]+gmin)*1.0;				// presynaptic gid	
					if (num_post>1) {
						x [myi+1*stepover] = (z[n])*1.0;	// postsynaptic gid
						//x [myi+2*stepover] = (step+1)*1.0;	// distance step
					}
					myi++;
				}
			} 
		}
		x [2+n] = idx1 + 1;
		//if (idx1>maxidx1) { maxidx1=idx1;}
		free(sortedpos);
	}
	x [0] = myi-2-num_post;	// fill the first element of the array (vector)
					// with the total number of connections to make,
					// which may be less than the desired number (and
					// hence the size of the array)
	x [1] = num_post; // (double)maxidx1;
	
	free(prepos);
	free(postpos);
	return finalconn;
}
 
static int  install_fastconn (  ) {
   
/*VERBATIM*/
	install_vector_method("fastconn", fastconn);
  return 0; }
 
static void _hoc_install_fastconn(void) {
  double _r;
   _r = 1.;
 install_fastconn (  );
 hoc_retpushx(_r);
}

static void initmodel() {
  int _i; double _save;_ninits++;
{

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

static double _nrn_current(double _v){double _current=0.;v=_v;{
} return _current;
}

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
}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}
