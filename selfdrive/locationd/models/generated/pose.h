#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_253594164780828539);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2215340346188359086);
void pose_H_mod_fun(double *state, double *out_1114507033744955760);
void pose_f_fun(double *state, double dt, double *out_7503615216406855844);
void pose_F_fun(double *state, double dt, double *out_448987525618456395);
void pose_h_4(double *state, double *unused, double *out_227196828506725750);
void pose_H_4(double *state, double *unused, double *out_1868668035799668367);
void pose_h_10(double *state, double *unused, double *out_2719718819013543410);
void pose_H_10(double *state, double *unused, double *out_8678441851357101835);
void pose_h_13(double *state, double *unused, double *out_2726070254487103051);
void pose_H_13(double *state, double *unused, double *out_5080941861132001168);
void pose_h_14(double *state, double *unused, double *out_8209254362122978467);
void pose_H_14(double *state, double *unused, double *out_5831908892139152896);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}