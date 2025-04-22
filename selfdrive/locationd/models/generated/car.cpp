#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.13.2                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_6913607775412413035) {
   out_6913607775412413035[0] = delta_x[0] + nom_x[0];
   out_6913607775412413035[1] = delta_x[1] + nom_x[1];
   out_6913607775412413035[2] = delta_x[2] + nom_x[2];
   out_6913607775412413035[3] = delta_x[3] + nom_x[3];
   out_6913607775412413035[4] = delta_x[4] + nom_x[4];
   out_6913607775412413035[5] = delta_x[5] + nom_x[5];
   out_6913607775412413035[6] = delta_x[6] + nom_x[6];
   out_6913607775412413035[7] = delta_x[7] + nom_x[7];
   out_6913607775412413035[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_821314435508382384) {
   out_821314435508382384[0] = -nom_x[0] + true_x[0];
   out_821314435508382384[1] = -nom_x[1] + true_x[1];
   out_821314435508382384[2] = -nom_x[2] + true_x[2];
   out_821314435508382384[3] = -nom_x[3] + true_x[3];
   out_821314435508382384[4] = -nom_x[4] + true_x[4];
   out_821314435508382384[5] = -nom_x[5] + true_x[5];
   out_821314435508382384[6] = -nom_x[6] + true_x[6];
   out_821314435508382384[7] = -nom_x[7] + true_x[7];
   out_821314435508382384[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3645815308730357106) {
   out_3645815308730357106[0] = 1.0;
   out_3645815308730357106[1] = 0.0;
   out_3645815308730357106[2] = 0.0;
   out_3645815308730357106[3] = 0.0;
   out_3645815308730357106[4] = 0.0;
   out_3645815308730357106[5] = 0.0;
   out_3645815308730357106[6] = 0.0;
   out_3645815308730357106[7] = 0.0;
   out_3645815308730357106[8] = 0.0;
   out_3645815308730357106[9] = 0.0;
   out_3645815308730357106[10] = 1.0;
   out_3645815308730357106[11] = 0.0;
   out_3645815308730357106[12] = 0.0;
   out_3645815308730357106[13] = 0.0;
   out_3645815308730357106[14] = 0.0;
   out_3645815308730357106[15] = 0.0;
   out_3645815308730357106[16] = 0.0;
   out_3645815308730357106[17] = 0.0;
   out_3645815308730357106[18] = 0.0;
   out_3645815308730357106[19] = 0.0;
   out_3645815308730357106[20] = 1.0;
   out_3645815308730357106[21] = 0.0;
   out_3645815308730357106[22] = 0.0;
   out_3645815308730357106[23] = 0.0;
   out_3645815308730357106[24] = 0.0;
   out_3645815308730357106[25] = 0.0;
   out_3645815308730357106[26] = 0.0;
   out_3645815308730357106[27] = 0.0;
   out_3645815308730357106[28] = 0.0;
   out_3645815308730357106[29] = 0.0;
   out_3645815308730357106[30] = 1.0;
   out_3645815308730357106[31] = 0.0;
   out_3645815308730357106[32] = 0.0;
   out_3645815308730357106[33] = 0.0;
   out_3645815308730357106[34] = 0.0;
   out_3645815308730357106[35] = 0.0;
   out_3645815308730357106[36] = 0.0;
   out_3645815308730357106[37] = 0.0;
   out_3645815308730357106[38] = 0.0;
   out_3645815308730357106[39] = 0.0;
   out_3645815308730357106[40] = 1.0;
   out_3645815308730357106[41] = 0.0;
   out_3645815308730357106[42] = 0.0;
   out_3645815308730357106[43] = 0.0;
   out_3645815308730357106[44] = 0.0;
   out_3645815308730357106[45] = 0.0;
   out_3645815308730357106[46] = 0.0;
   out_3645815308730357106[47] = 0.0;
   out_3645815308730357106[48] = 0.0;
   out_3645815308730357106[49] = 0.0;
   out_3645815308730357106[50] = 1.0;
   out_3645815308730357106[51] = 0.0;
   out_3645815308730357106[52] = 0.0;
   out_3645815308730357106[53] = 0.0;
   out_3645815308730357106[54] = 0.0;
   out_3645815308730357106[55] = 0.0;
   out_3645815308730357106[56] = 0.0;
   out_3645815308730357106[57] = 0.0;
   out_3645815308730357106[58] = 0.0;
   out_3645815308730357106[59] = 0.0;
   out_3645815308730357106[60] = 1.0;
   out_3645815308730357106[61] = 0.0;
   out_3645815308730357106[62] = 0.0;
   out_3645815308730357106[63] = 0.0;
   out_3645815308730357106[64] = 0.0;
   out_3645815308730357106[65] = 0.0;
   out_3645815308730357106[66] = 0.0;
   out_3645815308730357106[67] = 0.0;
   out_3645815308730357106[68] = 0.0;
   out_3645815308730357106[69] = 0.0;
   out_3645815308730357106[70] = 1.0;
   out_3645815308730357106[71] = 0.0;
   out_3645815308730357106[72] = 0.0;
   out_3645815308730357106[73] = 0.0;
   out_3645815308730357106[74] = 0.0;
   out_3645815308730357106[75] = 0.0;
   out_3645815308730357106[76] = 0.0;
   out_3645815308730357106[77] = 0.0;
   out_3645815308730357106[78] = 0.0;
   out_3645815308730357106[79] = 0.0;
   out_3645815308730357106[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7862105813698802705) {
   out_7862105813698802705[0] = state[0];
   out_7862105813698802705[1] = state[1];
   out_7862105813698802705[2] = state[2];
   out_7862105813698802705[3] = state[3];
   out_7862105813698802705[4] = state[4];
   out_7862105813698802705[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7862105813698802705[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7862105813698802705[7] = state[7];
   out_7862105813698802705[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8996959716687712579) {
   out_8996959716687712579[0] = 1;
   out_8996959716687712579[1] = 0;
   out_8996959716687712579[2] = 0;
   out_8996959716687712579[3] = 0;
   out_8996959716687712579[4] = 0;
   out_8996959716687712579[5] = 0;
   out_8996959716687712579[6] = 0;
   out_8996959716687712579[7] = 0;
   out_8996959716687712579[8] = 0;
   out_8996959716687712579[9] = 0;
   out_8996959716687712579[10] = 1;
   out_8996959716687712579[11] = 0;
   out_8996959716687712579[12] = 0;
   out_8996959716687712579[13] = 0;
   out_8996959716687712579[14] = 0;
   out_8996959716687712579[15] = 0;
   out_8996959716687712579[16] = 0;
   out_8996959716687712579[17] = 0;
   out_8996959716687712579[18] = 0;
   out_8996959716687712579[19] = 0;
   out_8996959716687712579[20] = 1;
   out_8996959716687712579[21] = 0;
   out_8996959716687712579[22] = 0;
   out_8996959716687712579[23] = 0;
   out_8996959716687712579[24] = 0;
   out_8996959716687712579[25] = 0;
   out_8996959716687712579[26] = 0;
   out_8996959716687712579[27] = 0;
   out_8996959716687712579[28] = 0;
   out_8996959716687712579[29] = 0;
   out_8996959716687712579[30] = 1;
   out_8996959716687712579[31] = 0;
   out_8996959716687712579[32] = 0;
   out_8996959716687712579[33] = 0;
   out_8996959716687712579[34] = 0;
   out_8996959716687712579[35] = 0;
   out_8996959716687712579[36] = 0;
   out_8996959716687712579[37] = 0;
   out_8996959716687712579[38] = 0;
   out_8996959716687712579[39] = 0;
   out_8996959716687712579[40] = 1;
   out_8996959716687712579[41] = 0;
   out_8996959716687712579[42] = 0;
   out_8996959716687712579[43] = 0;
   out_8996959716687712579[44] = 0;
   out_8996959716687712579[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8996959716687712579[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8996959716687712579[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8996959716687712579[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8996959716687712579[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8996959716687712579[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8996959716687712579[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8996959716687712579[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8996959716687712579[53] = -9.8000000000000007*dt;
   out_8996959716687712579[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8996959716687712579[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8996959716687712579[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8996959716687712579[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8996959716687712579[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8996959716687712579[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8996959716687712579[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8996959716687712579[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8996959716687712579[62] = 0;
   out_8996959716687712579[63] = 0;
   out_8996959716687712579[64] = 0;
   out_8996959716687712579[65] = 0;
   out_8996959716687712579[66] = 0;
   out_8996959716687712579[67] = 0;
   out_8996959716687712579[68] = 0;
   out_8996959716687712579[69] = 0;
   out_8996959716687712579[70] = 1;
   out_8996959716687712579[71] = 0;
   out_8996959716687712579[72] = 0;
   out_8996959716687712579[73] = 0;
   out_8996959716687712579[74] = 0;
   out_8996959716687712579[75] = 0;
   out_8996959716687712579[76] = 0;
   out_8996959716687712579[77] = 0;
   out_8996959716687712579[78] = 0;
   out_8996959716687712579[79] = 0;
   out_8996959716687712579[80] = 1;
}
void h_25(double *state, double *unused, double *out_3188227517340141291) {
   out_3188227517340141291[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6879590732005334705) {
   out_6879590732005334705[0] = 0;
   out_6879590732005334705[1] = 0;
   out_6879590732005334705[2] = 0;
   out_6879590732005334705[3] = 0;
   out_6879590732005334705[4] = 0;
   out_6879590732005334705[5] = 0;
   out_6879590732005334705[6] = 1;
   out_6879590732005334705[7] = 0;
   out_6879590732005334705[8] = 0;
}
void h_24(double *state, double *unused, double *out_7119305775158129999) {
   out_7119305775158129999[0] = state[4];
   out_7119305775158129999[1] = state[5];
}
void H_24(double *state, double *unused, double *out_225385273897148948) {
   out_225385273897148948[0] = 0;
   out_225385273897148948[1] = 0;
   out_225385273897148948[2] = 0;
   out_225385273897148948[3] = 0;
   out_225385273897148948[4] = 1;
   out_225385273897148948[5] = 0;
   out_225385273897148948[6] = 0;
   out_225385273897148948[7] = 0;
   out_225385273897148948[8] = 0;
   out_225385273897148948[9] = 0;
   out_225385273897148948[10] = 0;
   out_225385273897148948[11] = 0;
   out_225385273897148948[12] = 0;
   out_225385273897148948[13] = 0;
   out_225385273897148948[14] = 1;
   out_225385273897148948[15] = 0;
   out_225385273897148948[16] = 0;
   out_225385273897148948[17] = 0;
}
void h_30(double *state, double *unused, double *out_4704711977544382068) {
   out_4704711977544382068[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7039457011576608713) {
   out_7039457011576608713[0] = 0;
   out_7039457011576608713[1] = 0;
   out_7039457011576608713[2] = 0;
   out_7039457011576608713[3] = 0;
   out_7039457011576608713[4] = 1;
   out_7039457011576608713[5] = 0;
   out_7039457011576608713[6] = 0;
   out_7039457011576608713[7] = 0;
   out_7039457011576608713[8] = 0;
}
void h_26(double *state, double *unused, double *out_2084043604207756776) {
   out_2084043604207756776[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7825650022830160687) {
   out_7825650022830160687[0] = 0;
   out_7825650022830160687[1] = 0;
   out_7825650022830160687[2] = 0;
   out_7825650022830160687[3] = 0;
   out_7825650022830160687[4] = 0;
   out_7825650022830160687[5] = 0;
   out_7825650022830160687[6] = 0;
   out_7825650022830160687[7] = 1;
   out_7825650022830160687[8] = 0;
}
void h_27(double *state, double *unused, double *out_8189900785000986936) {
   out_8189900785000986936[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4864693699776183802) {
   out_4864693699776183802[0] = 0;
   out_4864693699776183802[1] = 0;
   out_4864693699776183802[2] = 0;
   out_4864693699776183802[3] = 1;
   out_4864693699776183802[4] = 0;
   out_4864693699776183802[5] = 0;
   out_4864693699776183802[6] = 0;
   out_4864693699776183802[7] = 0;
   out_4864693699776183802[8] = 0;
}
void h_29(double *state, double *unused, double *out_7309117298353079719) {
   out_7309117298353079719[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7549688355891000897) {
   out_7549688355891000897[0] = 0;
   out_7549688355891000897[1] = 1;
   out_7549688355891000897[2] = 0;
   out_7549688355891000897[3] = 0;
   out_7549688355891000897[4] = 0;
   out_7549688355891000897[5] = 0;
   out_7549688355891000897[6] = 0;
   out_7549688355891000897[7] = 0;
   out_7549688355891000897[8] = 0;
}
void h_28(double *state, double *unused, double *out_5153114733556654251) {
   out_5153114733556654251[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8933425446253224468) {
   out_8933425446253224468[0] = 1;
   out_8933425446253224468[1] = 0;
   out_8933425446253224468[2] = 0;
   out_8933425446253224468[3] = 0;
   out_8933425446253224468[4] = 0;
   out_8933425446253224468[5] = 0;
   out_8933425446253224468[6] = 0;
   out_8933425446253224468[7] = 0;
   out_8933425446253224468[8] = 0;
}
void h_31(double *state, double *unused, double *out_8487681330019059389) {
   out_8487681330019059389[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7199441920596809211) {
   out_7199441920596809211[0] = 0;
   out_7199441920596809211[1] = 0;
   out_7199441920596809211[2] = 0;
   out_7199441920596809211[3] = 0;
   out_7199441920596809211[4] = 0;
   out_7199441920596809211[5] = 0;
   out_7199441920596809211[6] = 0;
   out_7199441920596809211[7] = 0;
   out_7199441920596809211[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_6913607775412413035) {
  err_fun(nom_x, delta_x, out_6913607775412413035);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_821314435508382384) {
  inv_err_fun(nom_x, true_x, out_821314435508382384);
}
void car_H_mod_fun(double *state, double *out_3645815308730357106) {
  H_mod_fun(state, out_3645815308730357106);
}
void car_f_fun(double *state, double dt, double *out_7862105813698802705) {
  f_fun(state,  dt, out_7862105813698802705);
}
void car_F_fun(double *state, double dt, double *out_8996959716687712579) {
  F_fun(state,  dt, out_8996959716687712579);
}
void car_h_25(double *state, double *unused, double *out_3188227517340141291) {
  h_25(state, unused, out_3188227517340141291);
}
void car_H_25(double *state, double *unused, double *out_6879590732005334705) {
  H_25(state, unused, out_6879590732005334705);
}
void car_h_24(double *state, double *unused, double *out_7119305775158129999) {
  h_24(state, unused, out_7119305775158129999);
}
void car_H_24(double *state, double *unused, double *out_225385273897148948) {
  H_24(state, unused, out_225385273897148948);
}
void car_h_30(double *state, double *unused, double *out_4704711977544382068) {
  h_30(state, unused, out_4704711977544382068);
}
void car_H_30(double *state, double *unused, double *out_7039457011576608713) {
  H_30(state, unused, out_7039457011576608713);
}
void car_h_26(double *state, double *unused, double *out_2084043604207756776) {
  h_26(state, unused, out_2084043604207756776);
}
void car_H_26(double *state, double *unused, double *out_7825650022830160687) {
  H_26(state, unused, out_7825650022830160687);
}
void car_h_27(double *state, double *unused, double *out_8189900785000986936) {
  h_27(state, unused, out_8189900785000986936);
}
void car_H_27(double *state, double *unused, double *out_4864693699776183802) {
  H_27(state, unused, out_4864693699776183802);
}
void car_h_29(double *state, double *unused, double *out_7309117298353079719) {
  h_29(state, unused, out_7309117298353079719);
}
void car_H_29(double *state, double *unused, double *out_7549688355891000897) {
  H_29(state, unused, out_7549688355891000897);
}
void car_h_28(double *state, double *unused, double *out_5153114733556654251) {
  h_28(state, unused, out_5153114733556654251);
}
void car_H_28(double *state, double *unused, double *out_8933425446253224468) {
  H_28(state, unused, out_8933425446253224468);
}
void car_h_31(double *state, double *unused, double *out_8487681330019059389) {
  h_31(state, unused, out_8487681330019059389);
}
void car_H_31(double *state, double *unused, double *out_7199441920596809211) {
  H_31(state, unused, out_7199441920596809211);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
