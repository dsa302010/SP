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
void car_err_fun(double *nom_x, double *delta_x, double *out_4273181642969390997);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6633799699500651562);
void car_H_mod_fun(double *state, double *out_964501077597558523);
void car_f_fun(double *state, double dt, double *out_8290906818071251536);
void car_F_fun(double *state, double dt, double *out_4363217185205169263);
void car_h_25(double *state, double *unused, double *out_3714313283911477105);
void car_H_25(double *state, double *unused, double *out_6586862653237595014);
void car_h_24(double *state, double *unused, double *out_6480609586723894025);
void car_H_24(double *state, double *unused, double *out_3542545443233246822);
void car_h_30(double *state, double *unused, double *out_7961595563447723575);
void car_H_30(double *state, double *unused, double *out_6457523706094354944);
void car_h_26(double *state, double *unused, double *out_4919047326201318176);
void car_H_26(double *state, double *unused, double *out_2845359334363538790);
void car_h_27(double *state, double *unused, double *out_1006403735662789937);
void car_H_27(double *state, double *unused, double *out_4282760394293930033);
void car_h_29(double *state, double *unused, double *out_5149043460177870192);
void car_H_29(double *state, double *unused, double *out_6967755050408747128);
void car_h_28(double *state, double *unused, double *out_403087850986312420);
void car_H_28(double *state, double *unused, double *out_1885356033339216554);
void car_h_31(double *state, double *unused, double *out_2263681891282593938);
void car_H_31(double *state, double *unused, double *out_6617508615114555442);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}