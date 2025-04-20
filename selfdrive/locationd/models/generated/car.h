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
void car_err_fun(double *nom_x, double *delta_x, double *out_5183070159646580);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2308484352558447754);
void car_H_mod_fun(double *state, double *out_3102617155598295572);
void car_f_fun(double *state, double dt, double *out_1169021739879233041);
void car_F_fun(double *state, double dt, double *out_4031067058537679613);
void car_h_25(double *state, double *unused, double *out_3797779737749367699);
void car_H_25(double *state, double *unused, double *out_4709859895118768502);
void car_h_24(double *state, double *unused, double *out_4971536777182051766);
void car_H_24(double *state, double *unused, double *out_3137494115755253560);
void car_h_30(double *state, double *unused, double *out_3848739851859394286);
void car_H_30(double *state, double *unused, double *out_2191526936611519875);
void car_h_26(double *state, double *unused, double *out_1152933415801451359);
void car_H_26(double *state, double *unused, double *out_8451363213992824726);
void car_h_27(double *state, double *unused, double *out_2630035936673225962);
void car_H_27(double *state, double *unused, double *out_4366290248411944786);
void car_h_29(double *state, double *unused, double *out_1036187748589540903);
void car_H_29(double *state, double *unused, double *out_1681295592297127691);
void car_h_28(double *state, double *unused, double *out_3769005580740623184);
void car_H_28(double *state, double *unused, double *out_6763694609366658265);
void car_h_31(double *state, double *unused, double *out_63903738679133953);
void car_H_31(double *state, double *unused, double *out_9077571316226176202);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}