#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_6913607775412413035);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_821314435508382384);
void car_H_mod_fun(double *state, double *out_3645815308730357106);
void car_f_fun(double *state, double dt, double *out_7862105813698802705);
void car_F_fun(double *state, double dt, double *out_8996959716687712579);
void car_h_25(double *state, double *unused, double *out_3188227517340141291);
void car_H_25(double *state, double *unused, double *out_6879590732005334705);
void car_h_24(double *state, double *unused, double *out_7119305775158129999);
void car_H_24(double *state, double *unused, double *out_225385273897148948);
void car_h_30(double *state, double *unused, double *out_4704711977544382068);
void car_H_30(double *state, double *unused, double *out_7039457011576608713);
void car_h_26(double *state, double *unused, double *out_2084043604207756776);
void car_H_26(double *state, double *unused, double *out_7825650022830160687);
void car_h_27(double *state, double *unused, double *out_8189900785000986936);
void car_H_27(double *state, double *unused, double *out_4864693699776183802);
void car_h_29(double *state, double *unused, double *out_7309117298353079719);
void car_H_29(double *state, double *unused, double *out_7549688355891000897);
void car_h_28(double *state, double *unused, double *out_5153114733556654251);
void car_H_28(double *state, double *unused, double *out_8933425446253224468);
void car_h_31(double *state, double *unused, double *out_8487681330019059389);
void car_H_31(double *state, double *unused, double *out_7199441920596809211);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}