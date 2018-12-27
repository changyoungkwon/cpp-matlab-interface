//
// MATLAB Compiler: 5.2 (R2014b)
// Date: Thu Dec 27 17:40:59 2018
// Arguments: "-B" "macro_default" "-W" "cpplib:libmrxg" "-T" "link:lib" "-d"
// "src" "matlab/mapVBVD.m" "matlab/mrxg_pre.m" 
//

#ifndef __libmrxg_h
#define __libmrxg_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_libmrxg
#define PUBLIC_libmrxg_C_API __global
#else
#define PUBLIC_libmrxg_C_API /* No import statement needed. */
#endif

#define LIB_libmrxg_C_API PUBLIC_libmrxg_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_libmrxg
#define PUBLIC_libmrxg_C_API __declspec(dllexport)
#else
#define PUBLIC_libmrxg_C_API __declspec(dllimport)
#endif

#define LIB_libmrxg_C_API PUBLIC_libmrxg_C_API


#else

#define LIB_libmrxg_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libmrxg_C_API 
#define LIB_libmrxg_C_API /* No special import/export declaration */
#endif

extern LIB_libmrxg_C_API 
bool MW_CALL_CONV libmrxgInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_libmrxg_C_API 
bool MW_CALL_CONV libmrxgInitialize(void);

extern LIB_libmrxg_C_API 
void MW_CALL_CONV libmrxgTerminate(void);



extern LIB_libmrxg_C_API 
void MW_CALL_CONV libmrxgPrintStackTrace(void);

extern LIB_libmrxg_C_API 
bool MW_CALL_CONV mlxMapVBVD(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libmrxg_C_API 
bool MW_CALL_CONV mlxMrxg_pre(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_libmrxg
#define PUBLIC_libmrxg_CPP_API __declspec(dllexport)
#else
#define PUBLIC_libmrxg_CPP_API __declspec(dllimport)
#endif

#define LIB_libmrxg_CPP_API PUBLIC_libmrxg_CPP_API

#else

#if !defined(LIB_libmrxg_CPP_API)
#if defined(LIB_libmrxg_C_API)
#define LIB_libmrxg_CPP_API LIB_libmrxg_C_API
#else
#define LIB_libmrxg_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_libmrxg_CPP_API void MW_CALL_CONV mapVBVD(int nargout, mwArray& twix_obj, const mwArray& filename, const mwArray& varargin);

extern LIB_libmrxg_CPP_API void MW_CALL_CONV mrxg_pre(int nargout, mwArray& rawd, mwArray& im_mask, mwArray& k_mask, mwArray& k_norm, mwArray& header, const mwArray& filename);

#endif
#endif
