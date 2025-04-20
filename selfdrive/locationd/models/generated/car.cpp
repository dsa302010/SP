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
void err_fun(double *nom_x, double *delta_x, double *out_5183070159646580) {
   out_5183070159646580[0] = delta_x[0] + nom_x[0];
   out_5183070159646580[1] = delta_x[1] + nom_x[1];
   out_5183070159646580[2] = delta_x[2] + nom_x[2];
   out_5183070159646580[3] = delta_x[3] + nom_x[3];
   out_5183070159646580[4] = delta_x[4] + nom_x[4];
   out_5183070159646580[5] = delta_x[5] + nom_x[5];
   out_5183070159646580[6] = delta_x[6] + nom_x[6];
   out_5183070159646580[7] = delta_x[7] + nom_x[7];
   out_5183070159646580[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2308484352558447754) {
   out_2308484352558447754[0] = -nom_x[0] + true_x[0];
   out_2308484352558447754[1] = -nom_x[1] + true_x[1];
   out_2308484352558447754[2] = -nom_x[2] + true_x[2];
   out_2308484352558447754[3] = -nom_x[3] + true_x[3];
   out_2308484352558447754[4] = -nom_x[4] + true_x[4];
   out_2308484352558447754[5] = -nom_x[5] + true_x[5];
   out_2308484352558447754[6] = -nom_x[6] + true_x[6];
   out_2308484352558447754[7] = -nom_x[7] + true_x[7];
   out_2308484352558447754[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3102617155598295572) {
   out_3102617155598295572[0] = 1.0;
   out_3102617155598295572[1] = 0.0;
   out_3102617155598295572[2] = 0.0;
   out_3102617155598295572[3] = 0.0;
   out_3102617155598295572[4] = 0.0;
   out_3102617155598295572[5] = 0.0;
   out_3102617155598295572[6] = 0.0;
   out_3102617155598295572[7] = 0.0;
   out_3102617155598295572[8] = 0.0;
   out_3102617155598295572[9] = 0.0;
   out_3102617155598295572[10] = 1.0;
   out_3102617155598295572[11] = 0.0;
   out_3102617155598295572[12] = 0.0;
   out_3102617155598295572[13] = 0.0;
   out_3102617155598295572[14] = 0.0;
   out_3102617155598295572[15] = 0.0;
   out_3102617155598295572[16] = 0.0;
   out_3102617155598295572[17] = 0.0;
   out_3102617155598295572[18] = 0.0;
   out_3102617155598295572[19] = 0.0;
   out_3102617155598295572[20] = 1.0;
   out_3102617155598295572[21] = 0.0;
   out_3102617155598295572[22] = 0.0;
   out_3102617155598295572[23] = 0.0;
   out_3102617155598295572[24] = 0.0;
   out_3102617155598295572[25] = 0.0;
   out_3102617155598295572[26] = 0.0;
   out_3102617155598295572[27] = 0.0;
   out_3102617155598295572[28] = 0.0;
   out_3102617155598295572[29] = 0.0;
   out_3102617155598295572[30] = 1.0;
   out_3102617155598295572[31] = 0.0;
   out_3102617155598295572[32] = 0.0;
   out_3102617155598295572[33] = 0.0;
   out_3102617155598295572[34] = 0.0;
   out_3102617155598295572[35] = 0.0;
   out_3102617155598295572[36] = 0.0;
   out_3102617155598295572[37] = 0.0;
   out_3102617155598295572[38] = 0.0;
   out_3102617155598295572[39] = 0.0;
   out_3102617155598295572[40] = 1.0;
   out_3102617155598295572[41] = 0.0;
   out_3102617155598295572[42] = 0.0;
   out_3102617155598295572[43] = 0.0;
   out_3102617155598295572[44] = 0.0;
   out_3102617155598295572[45] = 0.0;
   out_3102617155598295572[46] = 0.0;
   out_3102617155598295572[47] = 0.0;
   out_3102617155598295572[48] = 0.0;
   out_3102617155598295572[49] = 0.0;
   out_3102617155598295572[50] = 1.0;
   out_3102617155598295572[51] = 0.0;
   out_3102617155598295572[52] = 0.0;
   out_3102617155598295572[53] = 0.0;
   out_3102617155598295572[54] = 0.0;
   out_3102617155598295572[55] = 0.0;
   out_3102617155598295572[56] = 0.0;
   out_3102617155598295572[57] = 0.0;
   out_3102617155598295572[58] = 0.0;
   out_3102617155598295572[59] = 0.0;
   out_3102617155598295572[60] = 1.0;
   out_3102617155598295572[61] = 0.0;
   out_3102617155598295572[62] = 0.0;
   out_3102617155598295572[63] = 0.0;
   out_3102617155598295572[64] = 0.0;
   out_3102617155598295572[65] = 0.0;
   out_3102617155598295572[66] = 0.0;
   out_3102617155598295572[67] = 0.0;
   out_3102617155598295572[68] = 0.0;
   out_3102617155598295572[69] = 0.0;
   out_3102617155598295572[70] = 1.0;
   out_3102617155598295572[71] = 0.0;
   out_3102617155598295572[72] = 0.0;
   out_3102617155598295572[73] = 0.0;
   out_3102617155598295572[74] = 0.0;
   out_3102617155598295572[75] = 0.0;
   out_3102617155598295572[76] = 0.0;
   out_3102617155598295572[77] = 0.0;
   out_3102617155598295572[78] = 0.0;
   out_3102617155598295572[79] = 0.0;
   out_3102617155598295572[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1169021739879233041) {
   out_1169021739879233041[0] = state[0];
   out_1169021739879233041[1] = state[1];
   out_1169021739879233041[2] = state[2];
   out_1169021739879233041[3] = state[3];
   out_1169021739879233041[4] = state[4];
   out_1169021739879233041[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1169021739879233041[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1169021739879233041[7] = state[7];
   out_1169021739879233041[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4031067058537679613) {
   out_4031067058537679613[0] = 1;
   out_4031067058537679613[1] = 0;
   out_4031067058537679613[2] = 0;
   out_4031067058537679613[3] = 0;
   out_4031067058537679613[4] = 0;
   out_4031067058537679613[5] = 0;
   out_4031067058537679613[6] = 0;
   out_4031067058537679613[7] = 0;
   out_4031067058537679613[8] = 0;
   out_4031067058537679613[9] = 0;
   out_4031067058537679613[10] = 1;
   out_4031067058537679613[11] = 0;
   out_4031067058537679613[12] = 0;
   out_4031067058537679613[13] = 0;
   out_4031067058537679613[14] = 0;
   out_4031067058537679613[15] = 0;
   out_4031067058537679613[16] = 0;
   out_4031067058537679613[17] = 0;
   out_4031067058537679613[18] = 0;
   out_4031067058537679613[19] = 0;
   out_4031067058537679613[20] = 1;
   out_4031067058537679613[21] = 0;
   out_4031067058537679613[22] = 0;
   out_4031067058537679613[23] = 0;
   out_4031067058537679613[24] = 0;
   out_4031067058537679613[25] = 0;
   out_4031067058537679613[26] = 0;
   out_4031067058537679613[27] = 0;
   out_4031067058537679613[28] = 0;
   out_4031067058537679613[29] = 0;
   out_4031067058537679613[30] = 1;
   out_4031067058537679613[31] = 0;
   out_4031067058537679613[32] = 0;
   out_4031067058537679613[33] = 0;
   out_4031067058537679613[34] = 0;
   out_4031067058537679613[35] = 0;
   out_4031067058537679613[36] = 0;
   out_4031067058537679613[37] = 0;
   out_4031067058537679613[38] = 0;
   out_4031067058537679613[39] = 0;
   out_4031067058537679613[40] = 1;
   out_4031067058537679613[41] = 0;
   out_4031067058537679613[42] = 0;
   out_4031067058537679613[43] = 0;
   out_4031067058537679613[44] = 0;
   out_4031067058537679613[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4031067058537679613[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4031067058537679613[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4031067058537679613[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4031067058537679613[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4031067058537679613[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4031067058537679613[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4031067058537679613[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4031067058537679613[53] = -9.8000000000000007*dt;
   out_4031067058537679613[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4031067058537679613[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4031067058537679613[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4031067058537679613[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4031067058537679613[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4031067058537679613[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4031067058537679613[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4031067058537679613[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4031067058537679613[62] = 0;
   out_4031067058537679613[63] = 0;
   out_4031067058537679613[64] = 0;
   out_4031067058537679613[65] = 0;
   out_4031067058537679613[66] = 0;
   out_4031067058537679613[67] = 0;
   out_4031067058537679613[68] = 0;
   out_4031067058537679613[69] = 0;
   out_4031067058537679613[70] = 1;
   out_4031067058537679613[71] = 0;
   out_4031067058537679613[72] = 0;
   out_4031067058537679613[73] = 0;
   out_4031067058537679613[74] = 0;
   out_4031067058537679613[75] = 0;
   out_4031067058537679613[76] = 0;
   out_4031067058537679613[77] = 0;
   out_4031067058537679613[78] = 0;
   out_4031067058537679613[79] = 0;
   out_4031067058537679613[80] = 1;
}
void h_25(double *state, double *unused, double *out_3797779737749367699) {
   out_3797779737749367699[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4709859895118768502) {
   out_4709859895118768502[0] = 0;
   out_4709859895118768502[1] = 0;
   out_4709859895118768502[2] = 0;
   out_4709859895118768502[3] = 0;
   out_4709859895118768502[4] = 0;
   out_4709859895118768502[5] = 0;
   out_4709859895118768502[6] = 1;
   out_4709859895118768502[7] = 0;
   out_4709859895118768502[8] = 0;
}
void h_24(double *state, double *unused, double *out_4971536777182051766) {
   out_4971536777182051766[0] = state[4];
   out_4971536777182051766[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3137494115755253560) {
   out_3137494115755253560[0] = 0;
   out_3137494115755253560[1] = 0;
   out_3137494115755253560[2] = 0;
   out_3137494115755253560[3] = 0;
   out_3137494115755253560[4] = 1;
   out_3137494115755253560[5] = 0;
   out_3137494115755253560[6] = 0;
   out_3137494115755253560[7] = 0;
   out_3137494115755253560[8] = 0;
   out_3137494115755253560[9] = 0;
   out_3137494115755253560[10] = 0;
   out_3137494115755253560[11] = 0;
   out_3137494115755253560[12] = 0;
   out_3137494115755253560[13] = 0;
   out_3137494115755253560[14] = 1;
   out_3137494115755253560[15] = 0;
   out_3137494115755253560[16] = 0;
   out_3137494115755253560[17] = 0;
}
void h_30(double *state, double *unused, double *out_3848739851859394286) {
   out_3848739851859394286[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2191526936611519875) {
   out_2191526936611519875[0] = 0;
   out_2191526936611519875[1] = 0;
   out_2191526936611519875[2] = 0;
   out_2191526936611519875[3] = 0;
   out_2191526936611519875[4] = 1;
   out_2191526936611519875[5] = 0;
   out_2191526936611519875[6] = 0;
   out_2191526936611519875[7] = 0;
   out_2191526936611519875[8] = 0;
}
void h_26(double *state, double *unused, double *out_1152933415801451359) {
   out_1152933415801451359[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8451363213992824726) {
   out_8451363213992824726[0] = 0;
   out_8451363213992824726[1] = 0;
   out_8451363213992824726[2] = 0;
   out_8451363213992824726[3] = 0;
   out_8451363213992824726[4] = 0;
   out_8451363213992824726[5] = 0;
   out_8451363213992824726[6] = 0;
   out_8451363213992824726[7] = 1;
   out_8451363213992824726[8] = 0;
}
void h_27(double *state, double *unused, double *out_2630035936673225962) {
   out_2630035936673225962[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4366290248411944786) {
   out_4366290248411944786[0] = 0;
   out_4366290248411944786[1] = 0;
   out_4366290248411944786[2] = 0;
   out_4366290248411944786[3] = 1;
   out_4366290248411944786[4] = 0;
   out_4366290248411944786[5] = 0;
   out_4366290248411944786[6] = 0;
   out_4366290248411944786[7] = 0;
   out_4366290248411944786[8] = 0;
}
void h_29(double *state, double *unused, double *out_1036187748589540903) {
   out_1036187748589540903[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1681295592297127691) {
   out_1681295592297127691[0] = 0;
   out_1681295592297127691[1] = 1;
   out_1681295592297127691[2] = 0;
   out_1681295592297127691[3] = 0;
   out_1681295592297127691[4] = 0;
   out_1681295592297127691[5] = 0;
   out_1681295592297127691[6] = 0;
   out_1681295592297127691[7] = 0;
   out_1681295592297127691[8] = 0;
}
void h_28(double *state, double *unused, double *out_3769005580740623184) {
   out_3769005580740623184[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6763694609366658265) {
   out_6763694609366658265[0] = 1;
   out_6763694609366658265[1] = 0;
   out_6763694609366658265[2] = 0;
   out_6763694609366658265[3] = 0;
   out_6763694609366658265[4] = 0;
   out_6763694609366658265[5] = 0;
   out_6763694609366658265[6] = 0;
   out_6763694609366658265[7] = 0;
   out_6763694609366658265[8] = 0;
}
void h_31(double *state, double *unused, double *out_63903738679133953) {
   out_63903738679133953[0] = state[8];
}
void H_31(double *state, double *unused, double *out_9077571316226176202) {
   out_9077571316226176202[0] = 0;
   out_9077571316226176202[1] = 0;
   out_9077571316226176202[2] = 0;
   out_9077571316226176202[3] = 0;
   out_9077571316226176202[4] = 0;
   out_9077571316226176202[5] = 0;
   out_9077571316226176202[6] = 0;
   out_9077571316226176202[7] = 0;
   out_9077571316226176202[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5183070159646580) {
  err_fun(nom_x, delta_x, out_5183070159646580);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2308484352558447754) {
  inv_err_fun(nom_x, true_x, out_2308484352558447754);
}
void car_H_mod_fun(double *state, double *out_3102617155598295572) {
  H_mod_fun(state, out_3102617155598295572);
}
void car_f_fun(double *state, double dt, double *out_1169021739879233041) {
  f_fun(state,  dt, out_1169021739879233041);
}
void car_F_fun(double *state, double dt, double *out_4031067058537679613) {
  F_fun(state,  dt, out_4031067058537679613);
}
void car_h_25(double *state, double *unused, double *out_3797779737749367699) {
  h_25(state, unused, out_3797779737749367699);
}
void car_H_25(double *state, double *unused, double *out_4709859895118768502) {
  H_25(state, unused, out_4709859895118768502);
}
void car_h_24(double *state, double *unused, double *out_4971536777182051766) {
  h_24(state, unused, out_4971536777182051766);
}
void car_H_24(double *state, double *unused, double *out_3137494115755253560) {
  H_24(state, unused, out_3137494115755253560);
}
void car_h_30(double *state, double *unused, double *out_3848739851859394286) {
  h_30(state, unused, out_3848739851859394286);
}
void car_H_30(double *state, double *unused, double *out_2191526936611519875) {
  H_30(state, unused, out_2191526936611519875);
}
void car_h_26(double *state, double *unused, double *out_1152933415801451359) {
  h_26(state, unused, out_1152933415801451359);
}
void car_H_26(double *state, double *unused, double *out_8451363213992824726) {
  H_26(state, unused, out_8451363213992824726);
}
void car_h_27(double *state, double *unused, double *out_2630035936673225962) {
  h_27(state, unused, out_2630035936673225962);
}
void car_H_27(double *state, double *unused, double *out_4366290248411944786) {
  H_27(state, unused, out_4366290248411944786);
}
void car_h_29(double *state, double *unused, double *out_1036187748589540903) {
  h_29(state, unused, out_1036187748589540903);
}
void car_H_29(double *state, double *unused, double *out_1681295592297127691) {
  H_29(state, unused, out_1681295592297127691);
}
void car_h_28(double *state, double *unused, double *out_3769005580740623184) {
  h_28(state, unused, out_3769005580740623184);
}
void car_H_28(double *state, double *unused, double *out_6763694609366658265) {
  H_28(state, unused, out_6763694609366658265);
}
void car_h_31(double *state, double *unused, double *out_63903738679133953) {
  h_31(state, unused, out_63903738679133953);
}
void car_H_31(double *state, double *unused, double *out_9077571316226176202) {
  H_31(state, unused, out_9077571316226176202);
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
