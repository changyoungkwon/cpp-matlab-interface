//
// MATLAB Compiler: 5.2 (R2014b)
// Date: Fri Dec 28 01:58:16 2018
// Arguments: "-B" "macro_default" "-W" "cpplib:libmrxg" "-T" "link:lib" "-d"
// "/home/changyoung/hdd/workspace/use-matlab/src"
// "/home/changyoung/hdd/workspace/use-matlab/matlab/ifft3c.m"
// "/home/changyoung/hdd/workspace/use-matlab/matlab/mapVBVD.m"
// "/home/changyoung/hdd/workspace/use-matlab/matlab/mrxg_pre.m"
// "/home/changyoung/hdd/workspace/use-matlab/matlab/read_twix_hdr.m"
// "/home/changyoung/hdd/workspace/use-matlab/matlab/redim.m"
// "/home/changyoung/hdd/workspace/use-matlab/matlab/twix_map_obj.m" 
//

#include <stdio.h>
#define EXPORTING_libmrxg 1
#include "libmrxg.h"

static HMCRINSTANCE _mcr_inst = NULL;


#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
  return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
  int written = 0;
  size_t len = 0;
  len = strlen(s);
  written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
  if (len > 0 && s[ len-1 ] != '\n')
    written += mclWrite(2 /* stderr */, "\n", sizeof(char));
  return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libmrxg_C_API
#define LIB_libmrxg_C_API /* No special import/export declaration */
#endif

LIB_libmrxg_C_API 
bool MW_CALL_CONV libmrxgInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
    {
        mclCtfStream ctfStream = 
            mclGetEmbeddedCtfStream((void *)(libmrxgInitializeWithHandlers));
        if (ctfStream) {
            bResult = mclInitializeComponentInstanceEmbedded(   &_mcr_inst,
                                                                error_handler, 
                                                                print_handler,
                                                                ctfStream);
            mclDestroyStream(ctfStream);
        } else {
            bResult = 0;
        }
    }  
    if (!bResult)
    return false;
  return true;
}

LIB_libmrxg_C_API 
bool MW_CALL_CONV libmrxgInitialize(void)
{
  return libmrxgInitializeWithHandlers(mclDefaultErrorHandler, mclDefaultPrintHandler);
}

LIB_libmrxg_C_API 
void MW_CALL_CONV libmrxgTerminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_libmrxg_C_API 
void MW_CALL_CONV libmrxgPrintStackTrace(void) 
{
  char** stackTrace;
  int stackDepth = mclGetStackTrace(&stackTrace);
  int i;
  for(i=0; i<stackDepth; i++)
  {
    mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
    mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
  }
  mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_libmrxg_C_API 
bool MW_CALL_CONV mlxIfft3c(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "ifft3c", nlhs, plhs, nrhs, prhs);
}

LIB_libmrxg_C_API 
bool MW_CALL_CONV mlxMapVBVD(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "mapVBVD", nlhs, plhs, nrhs, prhs);
}

LIB_libmrxg_C_API 
bool MW_CALL_CONV mlxMrxg_pre(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "mrxg_pre", nlhs, plhs, nrhs, prhs);
}

LIB_libmrxg_C_API 
bool MW_CALL_CONV mlxRead_twix_hdr(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "read_twix_hdr", nlhs, plhs, nrhs, prhs);
}

LIB_libmrxg_C_API 
bool MW_CALL_CONV mlxRedim(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "redim", nlhs, plhs, nrhs, prhs);
}

LIB_libmrxg_C_API 
bool MW_CALL_CONV mlxTwix_map_obj(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "twix_map_obj", nlhs, plhs, nrhs, prhs);
}

LIB_libmrxg_CPP_API 
void MW_CALL_CONV ifft3c(int nargout, mwArray& im, const mwArray& d, const mwArray& 
                         option)
{
  mclcppMlfFeval(_mcr_inst, "ifft3c", nargout, 1, 2, &im, &d, &option);
}

LIB_libmrxg_CPP_API 
void MW_CALL_CONV mapVBVD(int nargout, mwArray& twix_obj, const mwArray& filename, const 
                          mwArray& varargin)
{
  mclcppMlfFeval(_mcr_inst, "mapVBVD", nargout, 1, -2, &twix_obj, &filename, &varargin);
}

LIB_libmrxg_CPP_API 
void MW_CALL_CONV mrxg_pre(int nargout, mwArray& rawd, mwArray& im_mask, mwArray& k_mask, 
                           mwArray& k_norm, mwArray& header, mwArray& recon_option, const 
                           mwArray& filename)
{
  mclcppMlfFeval(_mcr_inst, "mrxg_pre", nargout, 6, 1, &rawd, &im_mask, &k_mask, &k_norm, &header, &recon_option, &filename);
}

LIB_libmrxg_CPP_API 
void MW_CALL_CONV read_twix_hdr(int nargout, mwArray& prot, const mwArray& fid)
{
  mclcppMlfFeval(_mcr_inst, "read_twix_hdr", nargout, 1, 1, &prot, &fid);
}

LIB_libmrxg_CPP_API 
void MW_CALL_CONV redim(int nargout, mwArray& output, const mwArray& rawd, const mwArray& 
                        target_dim)
{
  mclcppMlfFeval(_mcr_inst, "redim", nargout, 1, 2, &output, &rawd, &target_dim);
}

LIB_libmrxg_CPP_API 
void MW_CALL_CONV twix_map_obj(int nargout, mwArray& varargout, const mwArray& varargin)
{
  mclcppMlfFeval(_mcr_inst, "twix_map_obj", nargout, -1, -1, &varargout, &varargin);
}

LIB_libmrxg_CPP_API 
void MW_CALL_CONV twix_map_obj(int nargout, mwArray& varargout)
{
  mclcppMlfFeval(_mcr_inst, "twix_map_obj", nargout, -1, 0, &varargout);
}

LIB_libmrxg_CPP_API 
void MW_CALL_CONV twix_map_obj(const mwArray& varargin)
{
  mclcppMlfFeval(_mcr_inst, "twix_map_obj", 0, 0, -1, &varargin);
}

LIB_libmrxg_CPP_API 
void MW_CALL_CONV twix_map_obj()
{
  mclcppMlfFeval(_mcr_inst, "twix_map_obj", 0, 0, 0);
}

