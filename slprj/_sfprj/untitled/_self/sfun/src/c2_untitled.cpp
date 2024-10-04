/* Include files */

#include "untitled_sfun.h"
#include "c2_untitled.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(S);
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

/* Forward Declarations */

/* Type Definitions */

/* Named Constants */
const int32_T CALL_EVENT{ -1 };

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static emlrtRSInfo c2_emlrtRSI{ 6,     /* lineNo */
  "MATLAB Function",                   /* fcnName */
  "#untitled:1"                        /* pathName */
};

static emlrtRSInfo c2_b_emlrtRSI{ 11,  /* lineNo */
  "MATLAB Function",                   /* fcnName */
  "#untitled:1"                        /* pathName */
};

static emlrtRSInfo c2_c_emlrtRSI{ 13,  /* lineNo */
  "MATLAB Function",                   /* fcnName */
  "#untitled:1"                        /* pathName */
};

static emlrtRSInfo c2_d_emlrtRSI{ 15,  /* lineNo */
  "MATLAB Function",                   /* fcnName */
  "#untitled:1"                        /* pathName */
};

/* Function Declarations */
static void initialize_c2_untitled(SFc2_untitledInstanceStruct *chartInstance);
static void initialize_params_c2_untitled(SFc2_untitledInstanceStruct
  *chartInstance);
static void mdl_start_c2_untitled(SFc2_untitledInstanceStruct *chartInstance);
static void mdl_terminate_c2_untitled(SFc2_untitledInstanceStruct *chartInstance);
static void mdl_setup_runtime_resources_c2_untitled(SFc2_untitledInstanceStruct *
  chartInstance);
static void mdl_cleanup_runtime_resources_c2_untitled
  (SFc2_untitledInstanceStruct *chartInstance);
static void enable_c2_untitled(SFc2_untitledInstanceStruct *chartInstance);
static void disable_c2_untitled(SFc2_untitledInstanceStruct *chartInstance);
static void sf_gateway_c2_untitled(SFc2_untitledInstanceStruct *chartInstance);
static void ext_mode_exec_c2_untitled(SFc2_untitledInstanceStruct *chartInstance);
static void c2_update_jit_animation_c2_untitled(SFc2_untitledInstanceStruct
  *chartInstance);
static void c2_do_animation_call_c2_untitled(SFc2_untitledInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_untitled(SFc2_untitledInstanceStruct
  *chartInstance);
static void set_sim_state_c2_untitled(SFc2_untitledInstanceStruct *chartInstance,
  const mxArray *c2_st);
static real_T c2_emlrt_marshallIn(SFc2_untitledInstanceStruct *chartInstance,
  const mxArray *c2_nullptr, const char_T *c2_identifier);
static real_T c2_b_emlrt_marshallIn(SFc2_untitledInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_slStringInitializeDynamicBuffers(SFc2_untitledInstanceStruct
  *chartInstance);
static void c2_chart_data_browse_helper(SFc2_untitledInstanceStruct
  *chartInstance, int32_T c2_ssIdNumber, const mxArray **c2_mxData, uint8_T
  *c2_isValueTooBig);
static void init_dsm_address_info(SFc2_untitledInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_untitledInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_untitled(SFc2_untitledInstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
  chartInstance->c2_doneDoubleBufferReInit = false;
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void initialize_params_c2_untitled(SFc2_untitledInstanceStruct
  *chartInstance)
{
}

static void mdl_start_c2_untitled(SFc2_untitledInstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void mdl_terminate_c2_untitled(SFc2_untitledInstanceStruct *chartInstance)
{
}

static void mdl_setup_runtime_resources_c2_untitled(SFc2_untitledInstanceStruct *
  chartInstance)
{
  static const uint32_T c2_decisionTxtEndIdx{ 0U };

  static const uint32_T c2_decisionTxtStartIdx{ 0U };

  setDataBrowseFcn(chartInstance->S, (void *)&c2_chart_data_browse_helper);
  chartInstance->c2_RuntimeVar = sfListenerCacheSimStruct(chartInstance->S);
  sfListenerInitializeRuntimeVars(chartInstance->c2_RuntimeVar,
    &chartInstance->c2_IsDebuggerActive,
    &chartInstance->c2_IsSequenceViewerPresent, 0, 0,
    &chartInstance->c2_mlFcnLineNumber, &chartInstance->c2_IsHeatMapPresent, 0);
  sfSetAnimationVectors(chartInstance->S, &chartInstance->c2_JITStateAnimation[0],
                        &chartInstance->c2_JITTransitionAnimation[0]);
  covrtCreateStateflowInstanceData(chartInstance->c2_covrtInstance, 1U, 0U, 1U,
    2U);
  covrtChartInitFcn(chartInstance->c2_covrtInstance, 0U, false, false, false);
  covrtStateInitFcn(chartInstance->c2_covrtInstance, 0U, 0U, false, false, false,
                    0U, &c2_decisionTxtStartIdx, &c2_decisionTxtEndIdx);
  covrtTransInitFcn(chartInstance->c2_covrtInstance, 0U, 0, NULL, NULL, 0U, NULL);
  covrtEmlInitFcn(chartInstance->c2_covrtInstance, "", 4U, 0U, 1U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlFcnInitFcn(chartInstance->c2_covrtInstance, 4U, 0U, 0U, "c2_untitled",
                     0, -1, 229);
  covrtEmlInitFcn(chartInstance->c2_covrtInstance,
                  "C:/Users/aero/Documents/repos/ppl-matlab/ppl.m", 14U, 0U, 7U,
                  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlFcnInitFcn(chartInstance->c2_covrtInstance, 14U, 0U, 1U,
                     "ppl_getDescriptiveName", 83, -1, 160);
  covrtEmlFcnInitFcn(chartInstance->c2_covrtInstance, 14U, 0U, 2U,
                     "ppl_isSupportedContext", 169, -1, 250);
  covrtEmlFcnInitFcn(chartInstance->c2_covrtInstance, 14U, 0U, 3U,
                     "ppl_updateBuildInfo", 259, -1, 659);
  covrtEmlFcnInitFcn(chartInstance->c2_covrtInstance, 14U, 0U, 4U,
                     "ppl_Polyhedron", 669, -1, 985);
  covrtEmlFcnInitFcn(chartInstance->c2_covrtInstance, 14U, 0U, 5U,
                     "ppl_Contains", 995, -1, 1224);
  covrtEmlFcnInitFcn(chartInstance->c2_covrtInstance, 14U, 0U, 6U, "ppl_Minus",
                     1234, -1, 1496);
  covrtEmlFcnInitFcn(chartInstance->c2_covrtInstance, 14U, 0U, 0U, "ppl_ppl", 9,
                     -1, 12);
}

static void mdl_cleanup_runtime_resources_c2_untitled
  (SFc2_untitledInstanceStruct *chartInstance)
{
  sfListenerLightTerminate(chartInstance->c2_RuntimeVar);
  covrtDeleteStateflowInstanceData(chartInstance->c2_covrtInstance);
}

static void enable_c2_untitled(SFc2_untitledInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_untitled(SFc2_untitledInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void sf_gateway_c2_untitled(SFc2_untitledInstanceStruct *chartInstance)
{
  static real_T c2_b_A[8]{ 1.0, 0.0, -1.0, -0.0, 0.0, 1.0, -0.0, -1.0 };

  static real_T c2_d_A[8]{ -1.0, -0.0, 1.0, 0.0, -0.0, -1.0, 0.0, 1.0 };

  Parma_Polyhedra_Library::C_Polyhedron c2_P;
  Parma_Polyhedra_Library::C_Polyhedron c2_R;
  Parma_Polyhedra_Library::C_Polyhedron c2_S;
  Parma_Polyhedra_Library::C_Polyhedron c2_b_B;
  Parma_Polyhedra_Library::C_Polyhedron c2_c_A;
  Parma_Polyhedra_Library::C_Polyhedron c2_c_B;
  Parma_Polyhedra_Library::C_Polyhedron c2_e_A;
  real_T c2_A[8];
  real_T c2_b[4];
  int32_T c2_i;
  int32_T c2_i1;
  int32_T c2_i2;
  int32_T c2_i3;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_JITTransitionAnimation[0] = 0U;
  chartInstance->c2_sfEvent = CALL_EVENT;
  covrtEmlFcnEval(chartInstance->c2_covrtInstance, 4U, 0, 0);
  for (c2_i = 0; c2_i < 8; c2_i++) {
    c2_A[c2_i] = c2_b_A[c2_i];
  }

  for (c2_i1 = 0; c2_i1 < 4; c2_i1++) {
    c2_b[c2_i1] = 5.0;
  }

  covrtEmlFcnEval(chartInstance->c2_covrtInstance, 14U, 0, 4);
  ppl_matlab::Polyhedron(&c2_c_A, &c2_A[0], 4.0, 2.0, &c2_b[0]);
  for (c2_i2 = 0; c2_i2 < 8; c2_i2++) {
    c2_A[c2_i2] = c2_d_A[c2_i2];
  }

  for (c2_i3 = 0; c2_i3 < 4; c2_i3++) {
    c2_b[c2_i3] = 1.0;
  }

  covrtEmlFcnEval(chartInstance->c2_covrtInstance, 14U, 0, 4);
  ppl_matlab::Polyhedron(&c2_b_B, &c2_A[0], 4.0, 2.0, &c2_b[0]);
  c2_e_A = c2_c_A;
  c2_c_B = c2_b_B;
  covrtEmlFcnEval(chartInstance->c2_covrtInstance, 14U, 0, 5);
  ppl_matlab::Contains(&c2_e_A, &c2_c_B);
  c2_P = c2_c_A;
  c2_S = c2_b_B;
  covrtEmlFcnEval(chartInstance->c2_covrtInstance, 14U, 0, 6);
  ppl_matlab::Minus(&c2_R, &c2_P, &c2_S);
  *chartInstance->c2_y = 10.0;
  covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 0U, *chartInstance->c2_y);
}

static void ext_mode_exec_c2_untitled(SFc2_untitledInstanceStruct *chartInstance)
{
}

static void c2_update_jit_animation_c2_untitled(SFc2_untitledInstanceStruct
  *chartInstance)
{
}

static void c2_do_animation_call_c2_untitled(SFc2_untitledInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_untitled(SFc2_untitledInstanceStruct
  *chartInstance)
{
  const mxArray *c2_b_y{ nullptr };

  const mxArray *c2_c_y{ nullptr };

  const mxArray *c2_st{ nullptr };

  c2_st = nullptr;
  c2_b_y = nullptr;
  sf_mex_assign(&c2_b_y, sf_mex_createcellmatrix(1, 1), false);
  c2_c_y = nullptr;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", chartInstance->c2_y, 0, 0U, 0, 0U, 0),
                false);
  sf_mex_setcell(c2_b_y, 0, c2_c_y);
  sf_mex_assign(&c2_st, c2_b_y, false);
  return c2_st;
}

static void set_sim_state_c2_untitled(SFc2_untitledInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  *chartInstance->c2_y = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 0)), "y");
  sf_mex_destroy(&c2_u);
  sf_mex_destroy(&c2_st);
}

const mxArray *sf_c2_untitled_get_eml_resolved_functions_info()
{
  const mxArray *c2_nameCaptureInfo{ nullptr };

  const char_T *c2_data[4]{
    "789c6360f4f465646060e06380023608c50be50a4069260654802ecf88838601560616147d30f97e289d9c9f57925a5102e1e425e6a6c275a6e4e766e625e695"
    "845416a43214a516e7e794a5a68065d2327352433273538391397e205eae1b92149c039202b19d335293b3834b73198a328a112ecc41e6c0c32301877f590884",
    "073a400f0f747594da07339f19a77d109982821caad8870e88f5df0c32ed83996f48c03e987cb473acb3554c68716a51714c626a517e8c4b7e72696e6a5e4971"
    "4c516a417e710c30207473134b721293404cbd5c347726e070073f91eec4950f781938c074bdd86d467ada176c19524a4ffb6060a0ecabc0611eb1e94c0c877d",
    "0268f24615fe46868695e6011e89d9959551be014ec665a94e08770410b087903b1870f0696d3e00cc834c3a",
    "" };

  c2_nameCaptureInfo = nullptr;
  emlrtNameCaptureMxArrayR2016a(&c2_data[0], 1560U, &c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static real_T c2_emlrt_marshallIn(SFc2_untitledInstanceStruct *chartInstance,
  const mxArray *c2_nullptr, const char_T *c2_identifier)
{
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y;
  c2_thisId.fIdentifier = const_cast<const char_T *>(c2_identifier);
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nullptr),
    &c2_thisId);
  sf_mex_destroy(&c2_nullptr);
  return c2_b_y;
}

static real_T c2_b_emlrt_marshallIn(SFc2_untitledInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_b_y;
  real_T c2_d;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d, 1, 0, 0U, 0, 0U, 0);
  c2_b_y = c2_d;
  sf_mex_destroy(&c2_u);
  return c2_b_y;
}

static void c2_slStringInitializeDynamicBuffers(SFc2_untitledInstanceStruct
  *chartInstance)
{
}

static void c2_chart_data_browse_helper(SFc2_untitledInstanceStruct
  *chartInstance, int32_T c2_ssIdNumber, const mxArray **c2_mxData, uint8_T
  *c2_isValueTooBig)
{
  real_T c2_d;
  *c2_mxData = nullptr;
  *c2_mxData = nullptr;
  *c2_isValueTooBig = 0U;
  if (c2_ssIdNumber == 5U) {
    c2_d = *chartInstance->c2_y;
    sf_mex_assign(c2_mxData, sf_mex_create("mxData", &c2_d, 0, 0U, 0, 0U, 0),
                  false);
  }
}

static void init_dsm_address_info(SFc2_untitledInstanceStruct *chartInstance)
{
}

static void init_simulink_io_address(SFc2_untitledInstanceStruct *chartInstance)
{
  chartInstance->c2_covrtInstance = (CovrtStateflowInstance *)
    sfrtGetCovrtInstance(chartInstance->S);
  chartInstance->c2_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c2_y = (real_T *)ssGetOutputPortSignal_wrapper(chartInstance->S,
    1);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SFunction Glue Code */
void sf_c2_untitled_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1331490156U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(91094499U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(919478123U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1914566821U);
}

mxArray *sf_c2_untitled_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,1);
  mxSetCell(mxcell3p, 0, mxCreateString("ppl"));
  return(mxcell3p);
}

mxArray *sf_c2_untitled_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("ir_vars");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("A");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_untitled_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_untitled(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  mxArray *mxVarInfo = sf_mex_decode(
    "eNpjYPT0ZQACPiCWYGRgYAPSHEDMxAABrFA+IxKGiLPAxRWAuKSyIBUkXlyU7JkCpPMSc8H8xNI"
    "Kz7y0fLD5FgwI89kImM8JFYeAD/aU6RdxAOk3QNLPQkC/AJBVCQ0XEAAALEwMtA=="
    );
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_untitled_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const char* sf_get_instance_specialization(void)
{
  return "scGlB3ZTQpQIXq1ie8leJAF";
}

static void sf_opaque_initialize_c2_untitled(void *chartInstanceVar)
{
  initialize_params_c2_untitled((SFc2_untitledInstanceStruct*) chartInstanceVar);
  initialize_c2_untitled((SFc2_untitledInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_untitled(void *chartInstanceVar)
{
  enable_c2_untitled((SFc2_untitledInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_untitled(void *chartInstanceVar)
{
  disable_c2_untitled((SFc2_untitledInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_untitled(void *chartInstanceVar)
{
  sf_gateway_c2_untitled((SFc2_untitledInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_untitled(SimStruct* S)
{
  return get_sim_state_c2_untitled((SFc2_untitledInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_untitled(SimStruct* S, const mxArray *st)
{
  set_sim_state_c2_untitled((SFc2_untitledInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_cleanup_runtime_resources_c2_untitled(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_untitledInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_untitled_optimization_info();
    }

    mdl_cleanup_runtime_resources_c2_untitled((SFc2_untitledInstanceStruct*)
      chartInstanceVar);
    ((SFc2_untitledInstanceStruct*) chartInstanceVar)->
      ~SFc2_untitledInstanceStruct();
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_mdl_start_c2_untitled(void *chartInstanceVar)
{
  mdl_start_c2_untitled((SFc2_untitledInstanceStruct*) chartInstanceVar);
  if (chartInstanceVar) {
    sf_reset_warnings_ChartRunTimeInfo(((SFc2_untitledInstanceStruct*)
      chartInstanceVar)->S);
  }
}

static void sf_opaque_mdl_terminate_c2_untitled(void *chartInstanceVar)
{
  mdl_terminate_c2_untitled((SFc2_untitledInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_untitled(SimStruct *S)
{
  mdlProcessParamsCommon(S);
  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_untitled((SFc2_untitledInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

const char* sf_c2_untitled_get_post_codegen_info(void)
{
  int i;
  const char* encStrCodegen [23] = {
    "eNrdWE1v40QYdtpSsdAuIKEFIST2yGVXtBXaBS2wzdc2qN1kcbqgUrRM7TfxqOOxOx9pwgXuIMH",
    "P4D9w5cCBM0LiT3DkyDuOk7puaDyOoBWW3Oa1/cwz88z7ZTuV1p6Dx008f3zDcVbx//N4Ljnj47",
    "nUrmTO8fUV50Fqd15wHC8gQrV4L3LsDy/yoQ/c1b0eHVpiuQ47RJBQluDlJIRPQEZMKxpxu8lT3",
    "gMB3MMB4kgoK15JQ80oP25q7hlm+WlAvcANIs38Kg5I/DZno3/ijbXqIGOdCvBUE8BXgYh0P2gy",
    "0r9cBaFOawF4x1KH1lpJUK6OzVLlnmaKxgwaQ/BaXCqCKsg563UVUVBTQ2sPodKdoKMwZpTw4lo",
    "HRLoQo3co2I99/NvWCtUryIt8R5QTFQlKWCNkNePhBbEdhvPcQ7dm1jqrUNXhSPf7lPeNukKHwH",
    "H96CcFtOrVogEI0oc2t4xBs7rGMNngqV8Wj8GWcctSMajD8a7IUtiEtzFAhWRJ3qbHa4QxaYftR",
    "vEuDIAl/HWiSAnsmN8CLCX1u9FTIkwUWEaS5vREQ4qtRdynxXd4kEMlCfcxJs8CcBoalwIfZZ5O",
    "fTrQPJ/UUkVhDcOovrtbkO8itsUViB7xoHDuE4RKwAknfmXJ61NJjphBo0oqWWXhEYCXhjqyp3n",
    "9NBLHqLFtkj3TykSCHRr8PtRBQZIwGujdTwnTBeccSsxwxj32JWYsO17EmvgpBfaIF4Bv6gllsA",
    "fSDCAL52esI9u42gFVozpIT9C4aCRpCT4WEqNSdxTDPj/m0Slviih0047gEr8CwKxBBMeyUMWyJ",
    "EZNnHyxWQs46RrPKtOehUQxcmR84xFwrCxmraYSEg+jqsGxdcMJLYJ16VdY2rmkUmE7NWokMeAn",
    "/ejrFbt+9JXU3prGUkt2Be4UwTLMsVPaPkqaPejSEJILLsGeYmymh+F9xznjvbF0Oe8S/qqUxDk",
    "L4h5mcCsz9Hkxg3s5tb3NZ5pjcjEaz+JfK6DzBPfDst3+rKf290nPj2l5qM4a8TNPj0L0b65MiK",
    "Dr4o4N0rn26Hiv3Kzx2FhhM3Nraphb5neS+F1M/CLIBAzLGhd0yOs5ObJ6FsGZ55fP4ZadOGYL8",
    "QVz+DZyOGN/Xvui9v7hvgQhDwmI6LAeeUlnKQ8FvsHIQ5zUnXHAmp93wwzf/QzfS3P2eT29/vWt",
    "PyqL4N33unoRvLPg/LP4nTl638rpbezNYXtzY2N0r7NDjkejg71OdWsA1fF4b2fGq8wYL7vvZZ4",
    "viyub97J5aD3Hs5LDraYaPbj75W+Dn3/9QLV/+vab29/tLML/i2WduJnab07ee6ad4eBC81Rk/1",
    "/L7b+xpfeIVbcOuk/iJ63PTjYo3Gfw8XazVF2bXL+NpzJZ0YwvvJafSZ1Ej9+t8/6+Omf8G+f8/",
    "c+PFsO/+rBIPqyc06vijHJ+e93r71XV+6ucp01fYIur/Md8V7W+fzvvX7fny/Y3120dziX5aW3G",
    "uiq5ca/run537OrQW6n94fRbVC2gzJ/xNpzexhfW3qy7/xP//stSv0mf0DD6pR/TD7a2OWEjfP0",
    "df15IL3eE+Y47vSWAyNnfGK6iDhV9/1zLxbexTyn3o1N5Z2Pz3c1F6trfTXlEDQ==",
    ""
  };

  static char newstr [1641] = "";
  newstr[0] = '\0';
  for (i = 0; i < 23; i++) {
    strcat(newstr, encStrCodegen[i]);
  }

  return newstr;
}

static void mdlSetWorkWidths_c2_untitled(SimStruct *S)
{
  const char* newstr = sf_c2_untitled_get_post_codegen_info();
  sf_set_work_widths(S, newstr);
  ssSetChecksum0(S,(3596627516U));
  ssSetChecksum1(S,(1036829814U));
  ssSetChecksum2(S,(2344308596U));
  ssSetChecksum3(S,(1217142912U));
}

static void mdlRTW_c2_untitled(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlSetupRuntimeResources_c2_untitled(SimStruct *S)
{
  SFc2_untitledInstanceStruct *chartInstance;
  chartInstance = (SFc2_untitledInstanceStruct *)utMalloc(sizeof
    (SFc2_untitledInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_untitledInstanceStruct));
  chartInstance = new (chartInstance) SFc2_untitledInstanceStruct;
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_untitled;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_untitled;
  chartInstance->chartInfo.mdlStart = sf_opaque_mdl_start_c2_untitled;
  chartInstance->chartInfo.mdlTerminate = sf_opaque_mdl_terminate_c2_untitled;
  chartInstance->chartInfo.mdlCleanupRuntimeResources =
    sf_opaque_cleanup_runtime_resources_c2_untitled;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_untitled;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_untitled;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_untitled;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_untitled;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_untitled;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_untitled;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_untitled;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartEventFcn = NULL;
  chartInstance->S = S;
  chartInstance->chartInfo.dispatchToExportedFcn = NULL;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  mdl_setup_runtime_resources_c2_untitled(chartInstance);
}

void c2_untitled_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_SETUP_RUNTIME_RESOURCES:
    mdlSetupRuntimeResources_c2_untitled(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_untitled(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_untitled(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_untitled_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
