#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1889617797433936481);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1637106724448845216);
void pose_H_mod_fun(double *state, double *out_2437699087554365121);
void pose_f_fun(double *state, double dt, double *out_1371391185453368685);
void pose_F_fun(double *state, double dt, double *out_6008208831774812485);
void pose_h_4(double *state, double *unused, double *out_3596727777192918612);
void pose_H_4(double *state, double *unused, double *out_762710813547104903);
void pose_h_10(double *state, double *unused, double *out_3709524755717009150);
void pose_H_10(double *state, double *unused, double *out_3076932292756208908);
void pose_h_13(double *state, double *unused, double *out_4362699440761336099);
void pose_H_13(double *state, double *unused, double *out_198108893865260799);
void pose_h_14(double *state, double *unused, double *out_7721317524785797518);
void pose_H_14(double *state, double *unused, double *out_3845499245842477199);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}