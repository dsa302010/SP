#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_9096196563184828167);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2510715355574267806);
void pose_H_mod_fun(double *state, double *out_6571093323919857525);
void pose_f_fun(double *state, double dt, double *out_8641421515160522541);
void pose_F_fun(double *state, double dt, double *out_1965387258042231969);
void pose_h_4(double *state, double *unused, double *out_5430219983567452590);
void pose_H_4(double *state, double *unused, double *out_3296871245128908272);
void pose_h_10(double *state, double *unused, double *out_2671944880378075133);
void pose_H_10(double *state, double *unused, double *out_1775443925111280628);
void pose_h_13(double *state, double *unused, double *out_2650730557120445897);
void pose_H_13(double *state, double *unused, double *out_6509145070461241073);
void pose_h_14(double *state, double *unused, double *out_3815293765870846970);
void pose_H_14(double *state, double *unused, double *out_7260112101468392801);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}