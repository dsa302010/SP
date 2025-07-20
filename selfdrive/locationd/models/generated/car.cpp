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
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_5044843038987617277) {
   out_5044843038987617277[0] = delta_x[0] + nom_x[0];
   out_5044843038987617277[1] = delta_x[1] + nom_x[1];
   out_5044843038987617277[2] = delta_x[2] + nom_x[2];
   out_5044843038987617277[3] = delta_x[3] + nom_x[3];
   out_5044843038987617277[4] = delta_x[4] + nom_x[4];
   out_5044843038987617277[5] = delta_x[5] + nom_x[5];
   out_5044843038987617277[6] = delta_x[6] + nom_x[6];
   out_5044843038987617277[7] = delta_x[7] + nom_x[7];
   out_5044843038987617277[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2951194386476127153) {
   out_2951194386476127153[0] = -nom_x[0] + true_x[0];
   out_2951194386476127153[1] = -nom_x[1] + true_x[1];
   out_2951194386476127153[2] = -nom_x[2] + true_x[2];
   out_2951194386476127153[3] = -nom_x[3] + true_x[3];
   out_2951194386476127153[4] = -nom_x[4] + true_x[4];
   out_2951194386476127153[5] = -nom_x[5] + true_x[5];
   out_2951194386476127153[6] = -nom_x[6] + true_x[6];
   out_2951194386476127153[7] = -nom_x[7] + true_x[7];
   out_2951194386476127153[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_9173407726795533624) {
   out_9173407726795533624[0] = 1.0;
   out_9173407726795533624[1] = 0.0;
   out_9173407726795533624[2] = 0.0;
   out_9173407726795533624[3] = 0.0;
   out_9173407726795533624[4] = 0.0;
   out_9173407726795533624[5] = 0.0;
   out_9173407726795533624[6] = 0.0;
   out_9173407726795533624[7] = 0.0;
   out_9173407726795533624[8] = 0.0;
   out_9173407726795533624[9] = 0.0;
   out_9173407726795533624[10] = 1.0;
   out_9173407726795533624[11] = 0.0;
   out_9173407726795533624[12] = 0.0;
   out_9173407726795533624[13] = 0.0;
   out_9173407726795533624[14] = 0.0;
   out_9173407726795533624[15] = 0.0;
   out_9173407726795533624[16] = 0.0;
   out_9173407726795533624[17] = 0.0;
   out_9173407726795533624[18] = 0.0;
   out_9173407726795533624[19] = 0.0;
   out_9173407726795533624[20] = 1.0;
   out_9173407726795533624[21] = 0.0;
   out_9173407726795533624[22] = 0.0;
   out_9173407726795533624[23] = 0.0;
   out_9173407726795533624[24] = 0.0;
   out_9173407726795533624[25] = 0.0;
   out_9173407726795533624[26] = 0.0;
   out_9173407726795533624[27] = 0.0;
   out_9173407726795533624[28] = 0.0;
   out_9173407726795533624[29] = 0.0;
   out_9173407726795533624[30] = 1.0;
   out_9173407726795533624[31] = 0.0;
   out_9173407726795533624[32] = 0.0;
   out_9173407726795533624[33] = 0.0;
   out_9173407726795533624[34] = 0.0;
   out_9173407726795533624[35] = 0.0;
   out_9173407726795533624[36] = 0.0;
   out_9173407726795533624[37] = 0.0;
   out_9173407726795533624[38] = 0.0;
   out_9173407726795533624[39] = 0.0;
   out_9173407726795533624[40] = 1.0;
   out_9173407726795533624[41] = 0.0;
   out_9173407726795533624[42] = 0.0;
   out_9173407726795533624[43] = 0.0;
   out_9173407726795533624[44] = 0.0;
   out_9173407726795533624[45] = 0.0;
   out_9173407726795533624[46] = 0.0;
   out_9173407726795533624[47] = 0.0;
   out_9173407726795533624[48] = 0.0;
   out_9173407726795533624[49] = 0.0;
   out_9173407726795533624[50] = 1.0;
   out_9173407726795533624[51] = 0.0;
   out_9173407726795533624[52] = 0.0;
   out_9173407726795533624[53] = 0.0;
   out_9173407726795533624[54] = 0.0;
   out_9173407726795533624[55] = 0.0;
   out_9173407726795533624[56] = 0.0;
   out_9173407726795533624[57] = 0.0;
   out_9173407726795533624[58] = 0.0;
   out_9173407726795533624[59] = 0.0;
   out_9173407726795533624[60] = 1.0;
   out_9173407726795533624[61] = 0.0;
   out_9173407726795533624[62] = 0.0;
   out_9173407726795533624[63] = 0.0;
   out_9173407726795533624[64] = 0.0;
   out_9173407726795533624[65] = 0.0;
   out_9173407726795533624[66] = 0.0;
   out_9173407726795533624[67] = 0.0;
   out_9173407726795533624[68] = 0.0;
   out_9173407726795533624[69] = 0.0;
   out_9173407726795533624[70] = 1.0;
   out_9173407726795533624[71] = 0.0;
   out_9173407726795533624[72] = 0.0;
   out_9173407726795533624[73] = 0.0;
   out_9173407726795533624[74] = 0.0;
   out_9173407726795533624[75] = 0.0;
   out_9173407726795533624[76] = 0.0;
   out_9173407726795533624[77] = 0.0;
   out_9173407726795533624[78] = 0.0;
   out_9173407726795533624[79] = 0.0;
   out_9173407726795533624[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5538223174505499831) {
   out_5538223174505499831[0] = state[0];
   out_5538223174505499831[1] = state[1];
   out_5538223174505499831[2] = state[2];
   out_5538223174505499831[3] = state[3];
   out_5538223174505499831[4] = state[4];
   out_5538223174505499831[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5538223174505499831[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5538223174505499831[7] = state[7];
   out_5538223174505499831[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4950882054475811039) {
   out_4950882054475811039[0] = 1;
   out_4950882054475811039[1] = 0;
   out_4950882054475811039[2] = 0;
   out_4950882054475811039[3] = 0;
   out_4950882054475811039[4] = 0;
   out_4950882054475811039[5] = 0;
   out_4950882054475811039[6] = 0;
   out_4950882054475811039[7] = 0;
   out_4950882054475811039[8] = 0;
   out_4950882054475811039[9] = 0;
   out_4950882054475811039[10] = 1;
   out_4950882054475811039[11] = 0;
   out_4950882054475811039[12] = 0;
   out_4950882054475811039[13] = 0;
   out_4950882054475811039[14] = 0;
   out_4950882054475811039[15] = 0;
   out_4950882054475811039[16] = 0;
   out_4950882054475811039[17] = 0;
   out_4950882054475811039[18] = 0;
   out_4950882054475811039[19] = 0;
   out_4950882054475811039[20] = 1;
   out_4950882054475811039[21] = 0;
   out_4950882054475811039[22] = 0;
   out_4950882054475811039[23] = 0;
   out_4950882054475811039[24] = 0;
   out_4950882054475811039[25] = 0;
   out_4950882054475811039[26] = 0;
   out_4950882054475811039[27] = 0;
   out_4950882054475811039[28] = 0;
   out_4950882054475811039[29] = 0;
   out_4950882054475811039[30] = 1;
   out_4950882054475811039[31] = 0;
   out_4950882054475811039[32] = 0;
   out_4950882054475811039[33] = 0;
   out_4950882054475811039[34] = 0;
   out_4950882054475811039[35] = 0;
   out_4950882054475811039[36] = 0;
   out_4950882054475811039[37] = 0;
   out_4950882054475811039[38] = 0;
   out_4950882054475811039[39] = 0;
   out_4950882054475811039[40] = 1;
   out_4950882054475811039[41] = 0;
   out_4950882054475811039[42] = 0;
   out_4950882054475811039[43] = 0;
   out_4950882054475811039[44] = 0;
   out_4950882054475811039[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4950882054475811039[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4950882054475811039[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4950882054475811039[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4950882054475811039[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4950882054475811039[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4950882054475811039[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4950882054475811039[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4950882054475811039[53] = -9.8000000000000007*dt;
   out_4950882054475811039[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4950882054475811039[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4950882054475811039[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4950882054475811039[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4950882054475811039[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4950882054475811039[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4950882054475811039[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4950882054475811039[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4950882054475811039[62] = 0;
   out_4950882054475811039[63] = 0;
   out_4950882054475811039[64] = 0;
   out_4950882054475811039[65] = 0;
   out_4950882054475811039[66] = 0;
   out_4950882054475811039[67] = 0;
   out_4950882054475811039[68] = 0;
   out_4950882054475811039[69] = 0;
   out_4950882054475811039[70] = 1;
   out_4950882054475811039[71] = 0;
   out_4950882054475811039[72] = 0;
   out_4950882054475811039[73] = 0;
   out_4950882054475811039[74] = 0;
   out_4950882054475811039[75] = 0;
   out_4950882054475811039[76] = 0;
   out_4950882054475811039[77] = 0;
   out_4950882054475811039[78] = 0;
   out_4950882054475811039[79] = 0;
   out_4950882054475811039[80] = 1;
}
void h_25(double *state, double *unused, double *out_3358506318036560584) {
   out_3358506318036560584[0] = state[6];
}
void H_25(double *state, double *unused, double *out_19780499116703613) {
   out_19780499116703613[0] = 0;
   out_19780499116703613[1] = 0;
   out_19780499116703613[2] = 0;
   out_19780499116703613[3] = 0;
   out_19780499116703613[4] = 0;
   out_19780499116703613[5] = 0;
   out_19780499116703613[6] = 1;
   out_19780499116703613[7] = 0;
   out_19780499116703613[8] = 0;
}
void h_24(double *state, double *unused, double *out_6481349920157455690) {
   out_6481349920157455690[0] = state[4];
   out_6481349920157455690[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4766289826083212647) {
   out_4766289826083212647[0] = 0;
   out_4766289826083212647[1] = 0;
   out_4766289826083212647[2] = 0;
   out_4766289826083212647[3] = 0;
   out_4766289826083212647[4] = 1;
   out_4766289826083212647[5] = 0;
   out_4766289826083212647[6] = 0;
   out_4766289826083212647[7] = 0;
   out_4766289826083212647[8] = 0;
   out_4766289826083212647[9] = 0;
   out_4766289826083212647[10] = 0;
   out_4766289826083212647[11] = 0;
   out_4766289826083212647[12] = 0;
   out_4766289826083212647[13] = 0;
   out_4766289826083212647[14] = 1;
   out_4766289826083212647[15] = 0;
   out_4766289826083212647[16] = 0;
   out_4766289826083212647[17] = 0;
}
void h_30(double *state, double *unused, double *out_7324972498852318591) {
   out_7324972498852318591[0] = state[4];
}
void H_30(double *state, double *unused, double *out_149119446259943683) {
   out_149119446259943683[0] = 0;
   out_149119446259943683[1] = 0;
   out_149119446259943683[2] = 0;
   out_149119446259943683[3] = 0;
   out_149119446259943683[4] = 1;
   out_149119446259943683[5] = 0;
   out_149119446259943683[6] = 0;
   out_149119446259943683[7] = 0;
   out_149119446259943683[8] = 0;
}
void h_26(double *state, double *unused, double *out_8268482351753981026) {
   out_8268482351753981026[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3761283817990759837) {
   out_3761283817990759837[0] = 0;
   out_3761283817990759837[1] = 0;
   out_3761283817990759837[2] = 0;
   out_3761283817990759837[3] = 0;
   out_3761283817990759837[4] = 0;
   out_3761283817990759837[5] = 0;
   out_3761283817990759837[6] = 0;
   out_3761283817990759837[7] = 1;
   out_3761283817990759837[8] = 0;
}
void h_27(double *state, double *unused, double *out_6395292369480893269) {
   out_6395292369480893269[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2323882758060368594) {
   out_2323882758060368594[0] = 0;
   out_2323882758060368594[1] = 0;
   out_2323882758060368594[2] = 0;
   out_2323882758060368594[3] = 1;
   out_2323882758060368594[4] = 0;
   out_2323882758060368594[5] = 0;
   out_2323882758060368594[6] = 0;
   out_2323882758060368594[7] = 0;
   out_2323882758060368594[8] = 0;
}
void h_29(double *state, double *unused, double *out_6120098307196387380) {
   out_6120098307196387380[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4037245484929919627) {
   out_4037245484929919627[0] = 0;
   out_4037245484929919627[1] = 1;
   out_4037245484929919627[2] = 0;
   out_4037245484929919627[3] = 0;
   out_4037245484929919627[4] = 0;
   out_4037245484929919627[5] = 0;
   out_4037245484929919627[6] = 0;
   out_4037245484929919627[7] = 0;
   out_4037245484929919627[8] = 0;
}
void h_28(double *state, double *unused, double *out_1393619101820047624) {
   out_1393619101820047624[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2073615213364593376) {
   out_2073615213364593376[0] = 1;
   out_2073615213364593376[1] = 0;
   out_2073615213364593376[2] = 0;
   out_2073615213364593376[3] = 0;
   out_2073615213364593376[4] = 0;
   out_2073615213364593376[5] = 0;
   out_2073615213364593376[6] = 0;
   out_2073615213364593376[7] = 0;
   out_2073615213364593376[8] = 0;
}
void h_31(double *state, double *unused, double *out_2900304955877998922) {
   out_2900304955877998922[0] = state[8];
}
void H_31(double *state, double *unused, double *out_10865462760256815) {
   out_10865462760256815[0] = 0;
   out_10865462760256815[1] = 0;
   out_10865462760256815[2] = 0;
   out_10865462760256815[3] = 0;
   out_10865462760256815[4] = 0;
   out_10865462760256815[5] = 0;
   out_10865462760256815[6] = 0;
   out_10865462760256815[7] = 0;
   out_10865462760256815[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5044843038987617277) {
  err_fun(nom_x, delta_x, out_5044843038987617277);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2951194386476127153) {
  inv_err_fun(nom_x, true_x, out_2951194386476127153);
}
void car_H_mod_fun(double *state, double *out_9173407726795533624) {
  H_mod_fun(state, out_9173407726795533624);
}
void car_f_fun(double *state, double dt, double *out_5538223174505499831) {
  f_fun(state,  dt, out_5538223174505499831);
}
void car_F_fun(double *state, double dt, double *out_4950882054475811039) {
  F_fun(state,  dt, out_4950882054475811039);
}
void car_h_25(double *state, double *unused, double *out_3358506318036560584) {
  h_25(state, unused, out_3358506318036560584);
}
void car_H_25(double *state, double *unused, double *out_19780499116703613) {
  H_25(state, unused, out_19780499116703613);
}
void car_h_24(double *state, double *unused, double *out_6481349920157455690) {
  h_24(state, unused, out_6481349920157455690);
}
void car_H_24(double *state, double *unused, double *out_4766289826083212647) {
  H_24(state, unused, out_4766289826083212647);
}
void car_h_30(double *state, double *unused, double *out_7324972498852318591) {
  h_30(state, unused, out_7324972498852318591);
}
void car_H_30(double *state, double *unused, double *out_149119446259943683) {
  H_30(state, unused, out_149119446259943683);
}
void car_h_26(double *state, double *unused, double *out_8268482351753981026) {
  h_26(state, unused, out_8268482351753981026);
}
void car_H_26(double *state, double *unused, double *out_3761283817990759837) {
  H_26(state, unused, out_3761283817990759837);
}
void car_h_27(double *state, double *unused, double *out_6395292369480893269) {
  h_27(state, unused, out_6395292369480893269);
}
void car_H_27(double *state, double *unused, double *out_2323882758060368594) {
  H_27(state, unused, out_2323882758060368594);
}
void car_h_29(double *state, double *unused, double *out_6120098307196387380) {
  h_29(state, unused, out_6120098307196387380);
}
void car_H_29(double *state, double *unused, double *out_4037245484929919627) {
  H_29(state, unused, out_4037245484929919627);
}
void car_h_28(double *state, double *unused, double *out_1393619101820047624) {
  h_28(state, unused, out_1393619101820047624);
}
void car_H_28(double *state, double *unused, double *out_2073615213364593376) {
  H_28(state, unused, out_2073615213364593376);
}
void car_h_31(double *state, double *unused, double *out_2900304955877998922) {
  h_31(state, unused, out_2900304955877998922);
}
void car_H_31(double *state, double *unused, double *out_10865462760256815) {
  H_31(state, unused, out_10865462760256815);
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
