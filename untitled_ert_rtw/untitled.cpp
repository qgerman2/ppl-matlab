//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: untitled.cpp
//
// Code generated for Simulink model 'untitled'.
//
// Model version                  : 1.41
// Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
// C/C++ source code generated on : Tue Sep 24 14:48:37 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "untitled.h"
#include "rtwtypes.h"

// Model step function
void untitled::step()
{
  Parma_Polyhedra_Library::C_Polyhedron A;
  Parma_Polyhedra_Library::C_Polyhedron B;
  Parma_Polyhedra_Library::C_Polyhedron R;
  Parma_Polyhedra_Library::C_Polyhedron b_B;
  real_T b_A[8];
  real_T b[4];
  int32_T i;
  static const int8_T d_A[8]{ 1, 0, -1, 0, 0, 1, 0, -1 };

  static const int8_T e_A[8]{ -1, 0, 1, 0, 0, -1, 0, 1 };

  // MATLAB Function: '<Root>/MATLAB Function'
  for (i = 0; i < 8; i++) {
    b_A[i] = d_A[i];
  }

  b[0] = 5.0;
  b[1] = 5.0;
  b[2] = 5.0;
  b[3] = 5.0;
  ppl_matlab::Polyhedron(&A, &b_A[0], 4.0, 2.0, &b[0], 4.0);
  for (i = 0; i < 8; i++) {
    b_A[i] = e_A[i];
  }

  b[0] = 1.0;
  b[1] = 1.0;
  b[2] = 1.0;
  b[3] = 1.0;
  ppl_matlab::Polyhedron(&B, &b_A[0], 4.0, 2.0, &b[0], 4.0);
  R = A;
  b_B = B;
  ppl_matlab::Contains(&R, &b_B);
  ppl_matlab::Minus(&R, &A, &B);

  // End of MATLAB Function: '<Root>/MATLAB Function'
}

// Model initialize function
void untitled::initialize()
{
  // (no initialization code required)
}

// Model terminate function
void untitled::terminate()
{
  // (no terminate code required)
}

// Constructor
untitled::untitled() :
  untitled_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
untitled::~untitled() = default;

// Real-Time Model get method
untitled::RT_MODEL_untitled_T * untitled::getRTM()
{
  return (&untitled_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
