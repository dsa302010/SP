#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_698032175064450046);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5780803266693922923);
void pose_H_mod_fun(double *state, double *out_6648112690817590410);
void pose_f_fun(double *state, double dt, double *out_7821804503371700671);
void pose_F_fun(double *state, double dt, double *out_205686487848379182);
void pose_h_4(double *state, double *unused, double *out_4018057612377416184);
void pose_H_4(double *state, double *unused, double *out_7402273692872303017);
void pose_h_10(double *state, double *unused, double *out_2239744291470184978);
void pose_H_10(double *state, double *unused, double *out_5031652819947027519);
void pose_h_13(double *state, double *unused, double *out_1172069521836927214);
void pose_H_13(double *state, double *unused, double *out_3433839172520547670);
void pose_h_14(double *state, double *unused, double *out_6344550142343754918);
void pose_H_14(double *state, double *unused, double *out_4319485260576930721);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}