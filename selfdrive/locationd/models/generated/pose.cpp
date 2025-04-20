#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.13.2                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_253594164780828539) {
   out_253594164780828539[0] = delta_x[0] + nom_x[0];
   out_253594164780828539[1] = delta_x[1] + nom_x[1];
   out_253594164780828539[2] = delta_x[2] + nom_x[2];
   out_253594164780828539[3] = delta_x[3] + nom_x[3];
   out_253594164780828539[4] = delta_x[4] + nom_x[4];
   out_253594164780828539[5] = delta_x[5] + nom_x[5];
   out_253594164780828539[6] = delta_x[6] + nom_x[6];
   out_253594164780828539[7] = delta_x[7] + nom_x[7];
   out_253594164780828539[8] = delta_x[8] + nom_x[8];
   out_253594164780828539[9] = delta_x[9] + nom_x[9];
   out_253594164780828539[10] = delta_x[10] + nom_x[10];
   out_253594164780828539[11] = delta_x[11] + nom_x[11];
   out_253594164780828539[12] = delta_x[12] + nom_x[12];
   out_253594164780828539[13] = delta_x[13] + nom_x[13];
   out_253594164780828539[14] = delta_x[14] + nom_x[14];
   out_253594164780828539[15] = delta_x[15] + nom_x[15];
   out_253594164780828539[16] = delta_x[16] + nom_x[16];
   out_253594164780828539[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2215340346188359086) {
   out_2215340346188359086[0] = -nom_x[0] + true_x[0];
   out_2215340346188359086[1] = -nom_x[1] + true_x[1];
   out_2215340346188359086[2] = -nom_x[2] + true_x[2];
   out_2215340346188359086[3] = -nom_x[3] + true_x[3];
   out_2215340346188359086[4] = -nom_x[4] + true_x[4];
   out_2215340346188359086[5] = -nom_x[5] + true_x[5];
   out_2215340346188359086[6] = -nom_x[6] + true_x[6];
   out_2215340346188359086[7] = -nom_x[7] + true_x[7];
   out_2215340346188359086[8] = -nom_x[8] + true_x[8];
   out_2215340346188359086[9] = -nom_x[9] + true_x[9];
   out_2215340346188359086[10] = -nom_x[10] + true_x[10];
   out_2215340346188359086[11] = -nom_x[11] + true_x[11];
   out_2215340346188359086[12] = -nom_x[12] + true_x[12];
   out_2215340346188359086[13] = -nom_x[13] + true_x[13];
   out_2215340346188359086[14] = -nom_x[14] + true_x[14];
   out_2215340346188359086[15] = -nom_x[15] + true_x[15];
   out_2215340346188359086[16] = -nom_x[16] + true_x[16];
   out_2215340346188359086[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1114507033744955760) {
   out_1114507033744955760[0] = 1.0;
   out_1114507033744955760[1] = 0.0;
   out_1114507033744955760[2] = 0.0;
   out_1114507033744955760[3] = 0.0;
   out_1114507033744955760[4] = 0.0;
   out_1114507033744955760[5] = 0.0;
   out_1114507033744955760[6] = 0.0;
   out_1114507033744955760[7] = 0.0;
   out_1114507033744955760[8] = 0.0;
   out_1114507033744955760[9] = 0.0;
   out_1114507033744955760[10] = 0.0;
   out_1114507033744955760[11] = 0.0;
   out_1114507033744955760[12] = 0.0;
   out_1114507033744955760[13] = 0.0;
   out_1114507033744955760[14] = 0.0;
   out_1114507033744955760[15] = 0.0;
   out_1114507033744955760[16] = 0.0;
   out_1114507033744955760[17] = 0.0;
   out_1114507033744955760[18] = 0.0;
   out_1114507033744955760[19] = 1.0;
   out_1114507033744955760[20] = 0.0;
   out_1114507033744955760[21] = 0.0;
   out_1114507033744955760[22] = 0.0;
   out_1114507033744955760[23] = 0.0;
   out_1114507033744955760[24] = 0.0;
   out_1114507033744955760[25] = 0.0;
   out_1114507033744955760[26] = 0.0;
   out_1114507033744955760[27] = 0.0;
   out_1114507033744955760[28] = 0.0;
   out_1114507033744955760[29] = 0.0;
   out_1114507033744955760[30] = 0.0;
   out_1114507033744955760[31] = 0.0;
   out_1114507033744955760[32] = 0.0;
   out_1114507033744955760[33] = 0.0;
   out_1114507033744955760[34] = 0.0;
   out_1114507033744955760[35] = 0.0;
   out_1114507033744955760[36] = 0.0;
   out_1114507033744955760[37] = 0.0;
   out_1114507033744955760[38] = 1.0;
   out_1114507033744955760[39] = 0.0;
   out_1114507033744955760[40] = 0.0;
   out_1114507033744955760[41] = 0.0;
   out_1114507033744955760[42] = 0.0;
   out_1114507033744955760[43] = 0.0;
   out_1114507033744955760[44] = 0.0;
   out_1114507033744955760[45] = 0.0;
   out_1114507033744955760[46] = 0.0;
   out_1114507033744955760[47] = 0.0;
   out_1114507033744955760[48] = 0.0;
   out_1114507033744955760[49] = 0.0;
   out_1114507033744955760[50] = 0.0;
   out_1114507033744955760[51] = 0.0;
   out_1114507033744955760[52] = 0.0;
   out_1114507033744955760[53] = 0.0;
   out_1114507033744955760[54] = 0.0;
   out_1114507033744955760[55] = 0.0;
   out_1114507033744955760[56] = 0.0;
   out_1114507033744955760[57] = 1.0;
   out_1114507033744955760[58] = 0.0;
   out_1114507033744955760[59] = 0.0;
   out_1114507033744955760[60] = 0.0;
   out_1114507033744955760[61] = 0.0;
   out_1114507033744955760[62] = 0.0;
   out_1114507033744955760[63] = 0.0;
   out_1114507033744955760[64] = 0.0;
   out_1114507033744955760[65] = 0.0;
   out_1114507033744955760[66] = 0.0;
   out_1114507033744955760[67] = 0.0;
   out_1114507033744955760[68] = 0.0;
   out_1114507033744955760[69] = 0.0;
   out_1114507033744955760[70] = 0.0;
   out_1114507033744955760[71] = 0.0;
   out_1114507033744955760[72] = 0.0;
   out_1114507033744955760[73] = 0.0;
   out_1114507033744955760[74] = 0.0;
   out_1114507033744955760[75] = 0.0;
   out_1114507033744955760[76] = 1.0;
   out_1114507033744955760[77] = 0.0;
   out_1114507033744955760[78] = 0.0;
   out_1114507033744955760[79] = 0.0;
   out_1114507033744955760[80] = 0.0;
   out_1114507033744955760[81] = 0.0;
   out_1114507033744955760[82] = 0.0;
   out_1114507033744955760[83] = 0.0;
   out_1114507033744955760[84] = 0.0;
   out_1114507033744955760[85] = 0.0;
   out_1114507033744955760[86] = 0.0;
   out_1114507033744955760[87] = 0.0;
   out_1114507033744955760[88] = 0.0;
   out_1114507033744955760[89] = 0.0;
   out_1114507033744955760[90] = 0.0;
   out_1114507033744955760[91] = 0.0;
   out_1114507033744955760[92] = 0.0;
   out_1114507033744955760[93] = 0.0;
   out_1114507033744955760[94] = 0.0;
   out_1114507033744955760[95] = 1.0;
   out_1114507033744955760[96] = 0.0;
   out_1114507033744955760[97] = 0.0;
   out_1114507033744955760[98] = 0.0;
   out_1114507033744955760[99] = 0.0;
   out_1114507033744955760[100] = 0.0;
   out_1114507033744955760[101] = 0.0;
   out_1114507033744955760[102] = 0.0;
   out_1114507033744955760[103] = 0.0;
   out_1114507033744955760[104] = 0.0;
   out_1114507033744955760[105] = 0.0;
   out_1114507033744955760[106] = 0.0;
   out_1114507033744955760[107] = 0.0;
   out_1114507033744955760[108] = 0.0;
   out_1114507033744955760[109] = 0.0;
   out_1114507033744955760[110] = 0.0;
   out_1114507033744955760[111] = 0.0;
   out_1114507033744955760[112] = 0.0;
   out_1114507033744955760[113] = 0.0;
   out_1114507033744955760[114] = 1.0;
   out_1114507033744955760[115] = 0.0;
   out_1114507033744955760[116] = 0.0;
   out_1114507033744955760[117] = 0.0;
   out_1114507033744955760[118] = 0.0;
   out_1114507033744955760[119] = 0.0;
   out_1114507033744955760[120] = 0.0;
   out_1114507033744955760[121] = 0.0;
   out_1114507033744955760[122] = 0.0;
   out_1114507033744955760[123] = 0.0;
   out_1114507033744955760[124] = 0.0;
   out_1114507033744955760[125] = 0.0;
   out_1114507033744955760[126] = 0.0;
   out_1114507033744955760[127] = 0.0;
   out_1114507033744955760[128] = 0.0;
   out_1114507033744955760[129] = 0.0;
   out_1114507033744955760[130] = 0.0;
   out_1114507033744955760[131] = 0.0;
   out_1114507033744955760[132] = 0.0;
   out_1114507033744955760[133] = 1.0;
   out_1114507033744955760[134] = 0.0;
   out_1114507033744955760[135] = 0.0;
   out_1114507033744955760[136] = 0.0;
   out_1114507033744955760[137] = 0.0;
   out_1114507033744955760[138] = 0.0;
   out_1114507033744955760[139] = 0.0;
   out_1114507033744955760[140] = 0.0;
   out_1114507033744955760[141] = 0.0;
   out_1114507033744955760[142] = 0.0;
   out_1114507033744955760[143] = 0.0;
   out_1114507033744955760[144] = 0.0;
   out_1114507033744955760[145] = 0.0;
   out_1114507033744955760[146] = 0.0;
   out_1114507033744955760[147] = 0.0;
   out_1114507033744955760[148] = 0.0;
   out_1114507033744955760[149] = 0.0;
   out_1114507033744955760[150] = 0.0;
   out_1114507033744955760[151] = 0.0;
   out_1114507033744955760[152] = 1.0;
   out_1114507033744955760[153] = 0.0;
   out_1114507033744955760[154] = 0.0;
   out_1114507033744955760[155] = 0.0;
   out_1114507033744955760[156] = 0.0;
   out_1114507033744955760[157] = 0.0;
   out_1114507033744955760[158] = 0.0;
   out_1114507033744955760[159] = 0.0;
   out_1114507033744955760[160] = 0.0;
   out_1114507033744955760[161] = 0.0;
   out_1114507033744955760[162] = 0.0;
   out_1114507033744955760[163] = 0.0;
   out_1114507033744955760[164] = 0.0;
   out_1114507033744955760[165] = 0.0;
   out_1114507033744955760[166] = 0.0;
   out_1114507033744955760[167] = 0.0;
   out_1114507033744955760[168] = 0.0;
   out_1114507033744955760[169] = 0.0;
   out_1114507033744955760[170] = 0.0;
   out_1114507033744955760[171] = 1.0;
   out_1114507033744955760[172] = 0.0;
   out_1114507033744955760[173] = 0.0;
   out_1114507033744955760[174] = 0.0;
   out_1114507033744955760[175] = 0.0;
   out_1114507033744955760[176] = 0.0;
   out_1114507033744955760[177] = 0.0;
   out_1114507033744955760[178] = 0.0;
   out_1114507033744955760[179] = 0.0;
   out_1114507033744955760[180] = 0.0;
   out_1114507033744955760[181] = 0.0;
   out_1114507033744955760[182] = 0.0;
   out_1114507033744955760[183] = 0.0;
   out_1114507033744955760[184] = 0.0;
   out_1114507033744955760[185] = 0.0;
   out_1114507033744955760[186] = 0.0;
   out_1114507033744955760[187] = 0.0;
   out_1114507033744955760[188] = 0.0;
   out_1114507033744955760[189] = 0.0;
   out_1114507033744955760[190] = 1.0;
   out_1114507033744955760[191] = 0.0;
   out_1114507033744955760[192] = 0.0;
   out_1114507033744955760[193] = 0.0;
   out_1114507033744955760[194] = 0.0;
   out_1114507033744955760[195] = 0.0;
   out_1114507033744955760[196] = 0.0;
   out_1114507033744955760[197] = 0.0;
   out_1114507033744955760[198] = 0.0;
   out_1114507033744955760[199] = 0.0;
   out_1114507033744955760[200] = 0.0;
   out_1114507033744955760[201] = 0.0;
   out_1114507033744955760[202] = 0.0;
   out_1114507033744955760[203] = 0.0;
   out_1114507033744955760[204] = 0.0;
   out_1114507033744955760[205] = 0.0;
   out_1114507033744955760[206] = 0.0;
   out_1114507033744955760[207] = 0.0;
   out_1114507033744955760[208] = 0.0;
   out_1114507033744955760[209] = 1.0;
   out_1114507033744955760[210] = 0.0;
   out_1114507033744955760[211] = 0.0;
   out_1114507033744955760[212] = 0.0;
   out_1114507033744955760[213] = 0.0;
   out_1114507033744955760[214] = 0.0;
   out_1114507033744955760[215] = 0.0;
   out_1114507033744955760[216] = 0.0;
   out_1114507033744955760[217] = 0.0;
   out_1114507033744955760[218] = 0.0;
   out_1114507033744955760[219] = 0.0;
   out_1114507033744955760[220] = 0.0;
   out_1114507033744955760[221] = 0.0;
   out_1114507033744955760[222] = 0.0;
   out_1114507033744955760[223] = 0.0;
   out_1114507033744955760[224] = 0.0;
   out_1114507033744955760[225] = 0.0;
   out_1114507033744955760[226] = 0.0;
   out_1114507033744955760[227] = 0.0;
   out_1114507033744955760[228] = 1.0;
   out_1114507033744955760[229] = 0.0;
   out_1114507033744955760[230] = 0.0;
   out_1114507033744955760[231] = 0.0;
   out_1114507033744955760[232] = 0.0;
   out_1114507033744955760[233] = 0.0;
   out_1114507033744955760[234] = 0.0;
   out_1114507033744955760[235] = 0.0;
   out_1114507033744955760[236] = 0.0;
   out_1114507033744955760[237] = 0.0;
   out_1114507033744955760[238] = 0.0;
   out_1114507033744955760[239] = 0.0;
   out_1114507033744955760[240] = 0.0;
   out_1114507033744955760[241] = 0.0;
   out_1114507033744955760[242] = 0.0;
   out_1114507033744955760[243] = 0.0;
   out_1114507033744955760[244] = 0.0;
   out_1114507033744955760[245] = 0.0;
   out_1114507033744955760[246] = 0.0;
   out_1114507033744955760[247] = 1.0;
   out_1114507033744955760[248] = 0.0;
   out_1114507033744955760[249] = 0.0;
   out_1114507033744955760[250] = 0.0;
   out_1114507033744955760[251] = 0.0;
   out_1114507033744955760[252] = 0.0;
   out_1114507033744955760[253] = 0.0;
   out_1114507033744955760[254] = 0.0;
   out_1114507033744955760[255] = 0.0;
   out_1114507033744955760[256] = 0.0;
   out_1114507033744955760[257] = 0.0;
   out_1114507033744955760[258] = 0.0;
   out_1114507033744955760[259] = 0.0;
   out_1114507033744955760[260] = 0.0;
   out_1114507033744955760[261] = 0.0;
   out_1114507033744955760[262] = 0.0;
   out_1114507033744955760[263] = 0.0;
   out_1114507033744955760[264] = 0.0;
   out_1114507033744955760[265] = 0.0;
   out_1114507033744955760[266] = 1.0;
   out_1114507033744955760[267] = 0.0;
   out_1114507033744955760[268] = 0.0;
   out_1114507033744955760[269] = 0.0;
   out_1114507033744955760[270] = 0.0;
   out_1114507033744955760[271] = 0.0;
   out_1114507033744955760[272] = 0.0;
   out_1114507033744955760[273] = 0.0;
   out_1114507033744955760[274] = 0.0;
   out_1114507033744955760[275] = 0.0;
   out_1114507033744955760[276] = 0.0;
   out_1114507033744955760[277] = 0.0;
   out_1114507033744955760[278] = 0.0;
   out_1114507033744955760[279] = 0.0;
   out_1114507033744955760[280] = 0.0;
   out_1114507033744955760[281] = 0.0;
   out_1114507033744955760[282] = 0.0;
   out_1114507033744955760[283] = 0.0;
   out_1114507033744955760[284] = 0.0;
   out_1114507033744955760[285] = 1.0;
   out_1114507033744955760[286] = 0.0;
   out_1114507033744955760[287] = 0.0;
   out_1114507033744955760[288] = 0.0;
   out_1114507033744955760[289] = 0.0;
   out_1114507033744955760[290] = 0.0;
   out_1114507033744955760[291] = 0.0;
   out_1114507033744955760[292] = 0.0;
   out_1114507033744955760[293] = 0.0;
   out_1114507033744955760[294] = 0.0;
   out_1114507033744955760[295] = 0.0;
   out_1114507033744955760[296] = 0.0;
   out_1114507033744955760[297] = 0.0;
   out_1114507033744955760[298] = 0.0;
   out_1114507033744955760[299] = 0.0;
   out_1114507033744955760[300] = 0.0;
   out_1114507033744955760[301] = 0.0;
   out_1114507033744955760[302] = 0.0;
   out_1114507033744955760[303] = 0.0;
   out_1114507033744955760[304] = 1.0;
   out_1114507033744955760[305] = 0.0;
   out_1114507033744955760[306] = 0.0;
   out_1114507033744955760[307] = 0.0;
   out_1114507033744955760[308] = 0.0;
   out_1114507033744955760[309] = 0.0;
   out_1114507033744955760[310] = 0.0;
   out_1114507033744955760[311] = 0.0;
   out_1114507033744955760[312] = 0.0;
   out_1114507033744955760[313] = 0.0;
   out_1114507033744955760[314] = 0.0;
   out_1114507033744955760[315] = 0.0;
   out_1114507033744955760[316] = 0.0;
   out_1114507033744955760[317] = 0.0;
   out_1114507033744955760[318] = 0.0;
   out_1114507033744955760[319] = 0.0;
   out_1114507033744955760[320] = 0.0;
   out_1114507033744955760[321] = 0.0;
   out_1114507033744955760[322] = 0.0;
   out_1114507033744955760[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7503615216406855844) {
   out_7503615216406855844[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7503615216406855844[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7503615216406855844[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7503615216406855844[3] = dt*state[12] + state[3];
   out_7503615216406855844[4] = dt*state[13] + state[4];
   out_7503615216406855844[5] = dt*state[14] + state[5];
   out_7503615216406855844[6] = state[6];
   out_7503615216406855844[7] = state[7];
   out_7503615216406855844[8] = state[8];
   out_7503615216406855844[9] = state[9];
   out_7503615216406855844[10] = state[10];
   out_7503615216406855844[11] = state[11];
   out_7503615216406855844[12] = state[12];
   out_7503615216406855844[13] = state[13];
   out_7503615216406855844[14] = state[14];
   out_7503615216406855844[15] = state[15];
   out_7503615216406855844[16] = state[16];
   out_7503615216406855844[17] = state[17];
}
void F_fun(double *state, double dt, double *out_448987525618456395) {
   out_448987525618456395[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_448987525618456395[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_448987525618456395[2] = 0;
   out_448987525618456395[3] = 0;
   out_448987525618456395[4] = 0;
   out_448987525618456395[5] = 0;
   out_448987525618456395[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_448987525618456395[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_448987525618456395[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_448987525618456395[9] = 0;
   out_448987525618456395[10] = 0;
   out_448987525618456395[11] = 0;
   out_448987525618456395[12] = 0;
   out_448987525618456395[13] = 0;
   out_448987525618456395[14] = 0;
   out_448987525618456395[15] = 0;
   out_448987525618456395[16] = 0;
   out_448987525618456395[17] = 0;
   out_448987525618456395[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_448987525618456395[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_448987525618456395[20] = 0;
   out_448987525618456395[21] = 0;
   out_448987525618456395[22] = 0;
   out_448987525618456395[23] = 0;
   out_448987525618456395[24] = 0;
   out_448987525618456395[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_448987525618456395[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_448987525618456395[27] = 0;
   out_448987525618456395[28] = 0;
   out_448987525618456395[29] = 0;
   out_448987525618456395[30] = 0;
   out_448987525618456395[31] = 0;
   out_448987525618456395[32] = 0;
   out_448987525618456395[33] = 0;
   out_448987525618456395[34] = 0;
   out_448987525618456395[35] = 0;
   out_448987525618456395[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_448987525618456395[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_448987525618456395[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_448987525618456395[39] = 0;
   out_448987525618456395[40] = 0;
   out_448987525618456395[41] = 0;
   out_448987525618456395[42] = 0;
   out_448987525618456395[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_448987525618456395[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_448987525618456395[45] = 0;
   out_448987525618456395[46] = 0;
   out_448987525618456395[47] = 0;
   out_448987525618456395[48] = 0;
   out_448987525618456395[49] = 0;
   out_448987525618456395[50] = 0;
   out_448987525618456395[51] = 0;
   out_448987525618456395[52] = 0;
   out_448987525618456395[53] = 0;
   out_448987525618456395[54] = 0;
   out_448987525618456395[55] = 0;
   out_448987525618456395[56] = 0;
   out_448987525618456395[57] = 1;
   out_448987525618456395[58] = 0;
   out_448987525618456395[59] = 0;
   out_448987525618456395[60] = 0;
   out_448987525618456395[61] = 0;
   out_448987525618456395[62] = 0;
   out_448987525618456395[63] = 0;
   out_448987525618456395[64] = 0;
   out_448987525618456395[65] = 0;
   out_448987525618456395[66] = dt;
   out_448987525618456395[67] = 0;
   out_448987525618456395[68] = 0;
   out_448987525618456395[69] = 0;
   out_448987525618456395[70] = 0;
   out_448987525618456395[71] = 0;
   out_448987525618456395[72] = 0;
   out_448987525618456395[73] = 0;
   out_448987525618456395[74] = 0;
   out_448987525618456395[75] = 0;
   out_448987525618456395[76] = 1;
   out_448987525618456395[77] = 0;
   out_448987525618456395[78] = 0;
   out_448987525618456395[79] = 0;
   out_448987525618456395[80] = 0;
   out_448987525618456395[81] = 0;
   out_448987525618456395[82] = 0;
   out_448987525618456395[83] = 0;
   out_448987525618456395[84] = 0;
   out_448987525618456395[85] = dt;
   out_448987525618456395[86] = 0;
   out_448987525618456395[87] = 0;
   out_448987525618456395[88] = 0;
   out_448987525618456395[89] = 0;
   out_448987525618456395[90] = 0;
   out_448987525618456395[91] = 0;
   out_448987525618456395[92] = 0;
   out_448987525618456395[93] = 0;
   out_448987525618456395[94] = 0;
   out_448987525618456395[95] = 1;
   out_448987525618456395[96] = 0;
   out_448987525618456395[97] = 0;
   out_448987525618456395[98] = 0;
   out_448987525618456395[99] = 0;
   out_448987525618456395[100] = 0;
   out_448987525618456395[101] = 0;
   out_448987525618456395[102] = 0;
   out_448987525618456395[103] = 0;
   out_448987525618456395[104] = dt;
   out_448987525618456395[105] = 0;
   out_448987525618456395[106] = 0;
   out_448987525618456395[107] = 0;
   out_448987525618456395[108] = 0;
   out_448987525618456395[109] = 0;
   out_448987525618456395[110] = 0;
   out_448987525618456395[111] = 0;
   out_448987525618456395[112] = 0;
   out_448987525618456395[113] = 0;
   out_448987525618456395[114] = 1;
   out_448987525618456395[115] = 0;
   out_448987525618456395[116] = 0;
   out_448987525618456395[117] = 0;
   out_448987525618456395[118] = 0;
   out_448987525618456395[119] = 0;
   out_448987525618456395[120] = 0;
   out_448987525618456395[121] = 0;
   out_448987525618456395[122] = 0;
   out_448987525618456395[123] = 0;
   out_448987525618456395[124] = 0;
   out_448987525618456395[125] = 0;
   out_448987525618456395[126] = 0;
   out_448987525618456395[127] = 0;
   out_448987525618456395[128] = 0;
   out_448987525618456395[129] = 0;
   out_448987525618456395[130] = 0;
   out_448987525618456395[131] = 0;
   out_448987525618456395[132] = 0;
   out_448987525618456395[133] = 1;
   out_448987525618456395[134] = 0;
   out_448987525618456395[135] = 0;
   out_448987525618456395[136] = 0;
   out_448987525618456395[137] = 0;
   out_448987525618456395[138] = 0;
   out_448987525618456395[139] = 0;
   out_448987525618456395[140] = 0;
   out_448987525618456395[141] = 0;
   out_448987525618456395[142] = 0;
   out_448987525618456395[143] = 0;
   out_448987525618456395[144] = 0;
   out_448987525618456395[145] = 0;
   out_448987525618456395[146] = 0;
   out_448987525618456395[147] = 0;
   out_448987525618456395[148] = 0;
   out_448987525618456395[149] = 0;
   out_448987525618456395[150] = 0;
   out_448987525618456395[151] = 0;
   out_448987525618456395[152] = 1;
   out_448987525618456395[153] = 0;
   out_448987525618456395[154] = 0;
   out_448987525618456395[155] = 0;
   out_448987525618456395[156] = 0;
   out_448987525618456395[157] = 0;
   out_448987525618456395[158] = 0;
   out_448987525618456395[159] = 0;
   out_448987525618456395[160] = 0;
   out_448987525618456395[161] = 0;
   out_448987525618456395[162] = 0;
   out_448987525618456395[163] = 0;
   out_448987525618456395[164] = 0;
   out_448987525618456395[165] = 0;
   out_448987525618456395[166] = 0;
   out_448987525618456395[167] = 0;
   out_448987525618456395[168] = 0;
   out_448987525618456395[169] = 0;
   out_448987525618456395[170] = 0;
   out_448987525618456395[171] = 1;
   out_448987525618456395[172] = 0;
   out_448987525618456395[173] = 0;
   out_448987525618456395[174] = 0;
   out_448987525618456395[175] = 0;
   out_448987525618456395[176] = 0;
   out_448987525618456395[177] = 0;
   out_448987525618456395[178] = 0;
   out_448987525618456395[179] = 0;
   out_448987525618456395[180] = 0;
   out_448987525618456395[181] = 0;
   out_448987525618456395[182] = 0;
   out_448987525618456395[183] = 0;
   out_448987525618456395[184] = 0;
   out_448987525618456395[185] = 0;
   out_448987525618456395[186] = 0;
   out_448987525618456395[187] = 0;
   out_448987525618456395[188] = 0;
   out_448987525618456395[189] = 0;
   out_448987525618456395[190] = 1;
   out_448987525618456395[191] = 0;
   out_448987525618456395[192] = 0;
   out_448987525618456395[193] = 0;
   out_448987525618456395[194] = 0;
   out_448987525618456395[195] = 0;
   out_448987525618456395[196] = 0;
   out_448987525618456395[197] = 0;
   out_448987525618456395[198] = 0;
   out_448987525618456395[199] = 0;
   out_448987525618456395[200] = 0;
   out_448987525618456395[201] = 0;
   out_448987525618456395[202] = 0;
   out_448987525618456395[203] = 0;
   out_448987525618456395[204] = 0;
   out_448987525618456395[205] = 0;
   out_448987525618456395[206] = 0;
   out_448987525618456395[207] = 0;
   out_448987525618456395[208] = 0;
   out_448987525618456395[209] = 1;
   out_448987525618456395[210] = 0;
   out_448987525618456395[211] = 0;
   out_448987525618456395[212] = 0;
   out_448987525618456395[213] = 0;
   out_448987525618456395[214] = 0;
   out_448987525618456395[215] = 0;
   out_448987525618456395[216] = 0;
   out_448987525618456395[217] = 0;
   out_448987525618456395[218] = 0;
   out_448987525618456395[219] = 0;
   out_448987525618456395[220] = 0;
   out_448987525618456395[221] = 0;
   out_448987525618456395[222] = 0;
   out_448987525618456395[223] = 0;
   out_448987525618456395[224] = 0;
   out_448987525618456395[225] = 0;
   out_448987525618456395[226] = 0;
   out_448987525618456395[227] = 0;
   out_448987525618456395[228] = 1;
   out_448987525618456395[229] = 0;
   out_448987525618456395[230] = 0;
   out_448987525618456395[231] = 0;
   out_448987525618456395[232] = 0;
   out_448987525618456395[233] = 0;
   out_448987525618456395[234] = 0;
   out_448987525618456395[235] = 0;
   out_448987525618456395[236] = 0;
   out_448987525618456395[237] = 0;
   out_448987525618456395[238] = 0;
   out_448987525618456395[239] = 0;
   out_448987525618456395[240] = 0;
   out_448987525618456395[241] = 0;
   out_448987525618456395[242] = 0;
   out_448987525618456395[243] = 0;
   out_448987525618456395[244] = 0;
   out_448987525618456395[245] = 0;
   out_448987525618456395[246] = 0;
   out_448987525618456395[247] = 1;
   out_448987525618456395[248] = 0;
   out_448987525618456395[249] = 0;
   out_448987525618456395[250] = 0;
   out_448987525618456395[251] = 0;
   out_448987525618456395[252] = 0;
   out_448987525618456395[253] = 0;
   out_448987525618456395[254] = 0;
   out_448987525618456395[255] = 0;
   out_448987525618456395[256] = 0;
   out_448987525618456395[257] = 0;
   out_448987525618456395[258] = 0;
   out_448987525618456395[259] = 0;
   out_448987525618456395[260] = 0;
   out_448987525618456395[261] = 0;
   out_448987525618456395[262] = 0;
   out_448987525618456395[263] = 0;
   out_448987525618456395[264] = 0;
   out_448987525618456395[265] = 0;
   out_448987525618456395[266] = 1;
   out_448987525618456395[267] = 0;
   out_448987525618456395[268] = 0;
   out_448987525618456395[269] = 0;
   out_448987525618456395[270] = 0;
   out_448987525618456395[271] = 0;
   out_448987525618456395[272] = 0;
   out_448987525618456395[273] = 0;
   out_448987525618456395[274] = 0;
   out_448987525618456395[275] = 0;
   out_448987525618456395[276] = 0;
   out_448987525618456395[277] = 0;
   out_448987525618456395[278] = 0;
   out_448987525618456395[279] = 0;
   out_448987525618456395[280] = 0;
   out_448987525618456395[281] = 0;
   out_448987525618456395[282] = 0;
   out_448987525618456395[283] = 0;
   out_448987525618456395[284] = 0;
   out_448987525618456395[285] = 1;
   out_448987525618456395[286] = 0;
   out_448987525618456395[287] = 0;
   out_448987525618456395[288] = 0;
   out_448987525618456395[289] = 0;
   out_448987525618456395[290] = 0;
   out_448987525618456395[291] = 0;
   out_448987525618456395[292] = 0;
   out_448987525618456395[293] = 0;
   out_448987525618456395[294] = 0;
   out_448987525618456395[295] = 0;
   out_448987525618456395[296] = 0;
   out_448987525618456395[297] = 0;
   out_448987525618456395[298] = 0;
   out_448987525618456395[299] = 0;
   out_448987525618456395[300] = 0;
   out_448987525618456395[301] = 0;
   out_448987525618456395[302] = 0;
   out_448987525618456395[303] = 0;
   out_448987525618456395[304] = 1;
   out_448987525618456395[305] = 0;
   out_448987525618456395[306] = 0;
   out_448987525618456395[307] = 0;
   out_448987525618456395[308] = 0;
   out_448987525618456395[309] = 0;
   out_448987525618456395[310] = 0;
   out_448987525618456395[311] = 0;
   out_448987525618456395[312] = 0;
   out_448987525618456395[313] = 0;
   out_448987525618456395[314] = 0;
   out_448987525618456395[315] = 0;
   out_448987525618456395[316] = 0;
   out_448987525618456395[317] = 0;
   out_448987525618456395[318] = 0;
   out_448987525618456395[319] = 0;
   out_448987525618456395[320] = 0;
   out_448987525618456395[321] = 0;
   out_448987525618456395[322] = 0;
   out_448987525618456395[323] = 1;
}
void h_4(double *state, double *unused, double *out_227196828506725750) {
   out_227196828506725750[0] = state[6] + state[9];
   out_227196828506725750[1] = state[7] + state[10];
   out_227196828506725750[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1868668035799668367) {
   out_1868668035799668367[0] = 0;
   out_1868668035799668367[1] = 0;
   out_1868668035799668367[2] = 0;
   out_1868668035799668367[3] = 0;
   out_1868668035799668367[4] = 0;
   out_1868668035799668367[5] = 0;
   out_1868668035799668367[6] = 1;
   out_1868668035799668367[7] = 0;
   out_1868668035799668367[8] = 0;
   out_1868668035799668367[9] = 1;
   out_1868668035799668367[10] = 0;
   out_1868668035799668367[11] = 0;
   out_1868668035799668367[12] = 0;
   out_1868668035799668367[13] = 0;
   out_1868668035799668367[14] = 0;
   out_1868668035799668367[15] = 0;
   out_1868668035799668367[16] = 0;
   out_1868668035799668367[17] = 0;
   out_1868668035799668367[18] = 0;
   out_1868668035799668367[19] = 0;
   out_1868668035799668367[20] = 0;
   out_1868668035799668367[21] = 0;
   out_1868668035799668367[22] = 0;
   out_1868668035799668367[23] = 0;
   out_1868668035799668367[24] = 0;
   out_1868668035799668367[25] = 1;
   out_1868668035799668367[26] = 0;
   out_1868668035799668367[27] = 0;
   out_1868668035799668367[28] = 1;
   out_1868668035799668367[29] = 0;
   out_1868668035799668367[30] = 0;
   out_1868668035799668367[31] = 0;
   out_1868668035799668367[32] = 0;
   out_1868668035799668367[33] = 0;
   out_1868668035799668367[34] = 0;
   out_1868668035799668367[35] = 0;
   out_1868668035799668367[36] = 0;
   out_1868668035799668367[37] = 0;
   out_1868668035799668367[38] = 0;
   out_1868668035799668367[39] = 0;
   out_1868668035799668367[40] = 0;
   out_1868668035799668367[41] = 0;
   out_1868668035799668367[42] = 0;
   out_1868668035799668367[43] = 0;
   out_1868668035799668367[44] = 1;
   out_1868668035799668367[45] = 0;
   out_1868668035799668367[46] = 0;
   out_1868668035799668367[47] = 1;
   out_1868668035799668367[48] = 0;
   out_1868668035799668367[49] = 0;
   out_1868668035799668367[50] = 0;
   out_1868668035799668367[51] = 0;
   out_1868668035799668367[52] = 0;
   out_1868668035799668367[53] = 0;
}
void h_10(double *state, double *unused, double *out_2719718819013543410) {
   out_2719718819013543410[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2719718819013543410[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2719718819013543410[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8678441851357101835) {
   out_8678441851357101835[0] = 0;
   out_8678441851357101835[1] = 9.8100000000000005*cos(state[1]);
   out_8678441851357101835[2] = 0;
   out_8678441851357101835[3] = 0;
   out_8678441851357101835[4] = -state[8];
   out_8678441851357101835[5] = state[7];
   out_8678441851357101835[6] = 0;
   out_8678441851357101835[7] = state[5];
   out_8678441851357101835[8] = -state[4];
   out_8678441851357101835[9] = 0;
   out_8678441851357101835[10] = 0;
   out_8678441851357101835[11] = 0;
   out_8678441851357101835[12] = 1;
   out_8678441851357101835[13] = 0;
   out_8678441851357101835[14] = 0;
   out_8678441851357101835[15] = 1;
   out_8678441851357101835[16] = 0;
   out_8678441851357101835[17] = 0;
   out_8678441851357101835[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8678441851357101835[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8678441851357101835[20] = 0;
   out_8678441851357101835[21] = state[8];
   out_8678441851357101835[22] = 0;
   out_8678441851357101835[23] = -state[6];
   out_8678441851357101835[24] = -state[5];
   out_8678441851357101835[25] = 0;
   out_8678441851357101835[26] = state[3];
   out_8678441851357101835[27] = 0;
   out_8678441851357101835[28] = 0;
   out_8678441851357101835[29] = 0;
   out_8678441851357101835[30] = 0;
   out_8678441851357101835[31] = 1;
   out_8678441851357101835[32] = 0;
   out_8678441851357101835[33] = 0;
   out_8678441851357101835[34] = 1;
   out_8678441851357101835[35] = 0;
   out_8678441851357101835[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8678441851357101835[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8678441851357101835[38] = 0;
   out_8678441851357101835[39] = -state[7];
   out_8678441851357101835[40] = state[6];
   out_8678441851357101835[41] = 0;
   out_8678441851357101835[42] = state[4];
   out_8678441851357101835[43] = -state[3];
   out_8678441851357101835[44] = 0;
   out_8678441851357101835[45] = 0;
   out_8678441851357101835[46] = 0;
   out_8678441851357101835[47] = 0;
   out_8678441851357101835[48] = 0;
   out_8678441851357101835[49] = 0;
   out_8678441851357101835[50] = 1;
   out_8678441851357101835[51] = 0;
   out_8678441851357101835[52] = 0;
   out_8678441851357101835[53] = 1;
}
void h_13(double *state, double *unused, double *out_2726070254487103051) {
   out_2726070254487103051[0] = state[3];
   out_2726070254487103051[1] = state[4];
   out_2726070254487103051[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5080941861132001168) {
   out_5080941861132001168[0] = 0;
   out_5080941861132001168[1] = 0;
   out_5080941861132001168[2] = 0;
   out_5080941861132001168[3] = 1;
   out_5080941861132001168[4] = 0;
   out_5080941861132001168[5] = 0;
   out_5080941861132001168[6] = 0;
   out_5080941861132001168[7] = 0;
   out_5080941861132001168[8] = 0;
   out_5080941861132001168[9] = 0;
   out_5080941861132001168[10] = 0;
   out_5080941861132001168[11] = 0;
   out_5080941861132001168[12] = 0;
   out_5080941861132001168[13] = 0;
   out_5080941861132001168[14] = 0;
   out_5080941861132001168[15] = 0;
   out_5080941861132001168[16] = 0;
   out_5080941861132001168[17] = 0;
   out_5080941861132001168[18] = 0;
   out_5080941861132001168[19] = 0;
   out_5080941861132001168[20] = 0;
   out_5080941861132001168[21] = 0;
   out_5080941861132001168[22] = 1;
   out_5080941861132001168[23] = 0;
   out_5080941861132001168[24] = 0;
   out_5080941861132001168[25] = 0;
   out_5080941861132001168[26] = 0;
   out_5080941861132001168[27] = 0;
   out_5080941861132001168[28] = 0;
   out_5080941861132001168[29] = 0;
   out_5080941861132001168[30] = 0;
   out_5080941861132001168[31] = 0;
   out_5080941861132001168[32] = 0;
   out_5080941861132001168[33] = 0;
   out_5080941861132001168[34] = 0;
   out_5080941861132001168[35] = 0;
   out_5080941861132001168[36] = 0;
   out_5080941861132001168[37] = 0;
   out_5080941861132001168[38] = 0;
   out_5080941861132001168[39] = 0;
   out_5080941861132001168[40] = 0;
   out_5080941861132001168[41] = 1;
   out_5080941861132001168[42] = 0;
   out_5080941861132001168[43] = 0;
   out_5080941861132001168[44] = 0;
   out_5080941861132001168[45] = 0;
   out_5080941861132001168[46] = 0;
   out_5080941861132001168[47] = 0;
   out_5080941861132001168[48] = 0;
   out_5080941861132001168[49] = 0;
   out_5080941861132001168[50] = 0;
   out_5080941861132001168[51] = 0;
   out_5080941861132001168[52] = 0;
   out_5080941861132001168[53] = 0;
}
void h_14(double *state, double *unused, double *out_8209254362122978467) {
   out_8209254362122978467[0] = state[6];
   out_8209254362122978467[1] = state[7];
   out_8209254362122978467[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5831908892139152896) {
   out_5831908892139152896[0] = 0;
   out_5831908892139152896[1] = 0;
   out_5831908892139152896[2] = 0;
   out_5831908892139152896[3] = 0;
   out_5831908892139152896[4] = 0;
   out_5831908892139152896[5] = 0;
   out_5831908892139152896[6] = 1;
   out_5831908892139152896[7] = 0;
   out_5831908892139152896[8] = 0;
   out_5831908892139152896[9] = 0;
   out_5831908892139152896[10] = 0;
   out_5831908892139152896[11] = 0;
   out_5831908892139152896[12] = 0;
   out_5831908892139152896[13] = 0;
   out_5831908892139152896[14] = 0;
   out_5831908892139152896[15] = 0;
   out_5831908892139152896[16] = 0;
   out_5831908892139152896[17] = 0;
   out_5831908892139152896[18] = 0;
   out_5831908892139152896[19] = 0;
   out_5831908892139152896[20] = 0;
   out_5831908892139152896[21] = 0;
   out_5831908892139152896[22] = 0;
   out_5831908892139152896[23] = 0;
   out_5831908892139152896[24] = 0;
   out_5831908892139152896[25] = 1;
   out_5831908892139152896[26] = 0;
   out_5831908892139152896[27] = 0;
   out_5831908892139152896[28] = 0;
   out_5831908892139152896[29] = 0;
   out_5831908892139152896[30] = 0;
   out_5831908892139152896[31] = 0;
   out_5831908892139152896[32] = 0;
   out_5831908892139152896[33] = 0;
   out_5831908892139152896[34] = 0;
   out_5831908892139152896[35] = 0;
   out_5831908892139152896[36] = 0;
   out_5831908892139152896[37] = 0;
   out_5831908892139152896[38] = 0;
   out_5831908892139152896[39] = 0;
   out_5831908892139152896[40] = 0;
   out_5831908892139152896[41] = 0;
   out_5831908892139152896[42] = 0;
   out_5831908892139152896[43] = 0;
   out_5831908892139152896[44] = 1;
   out_5831908892139152896[45] = 0;
   out_5831908892139152896[46] = 0;
   out_5831908892139152896[47] = 0;
   out_5831908892139152896[48] = 0;
   out_5831908892139152896[49] = 0;
   out_5831908892139152896[50] = 0;
   out_5831908892139152896[51] = 0;
   out_5831908892139152896[52] = 0;
   out_5831908892139152896[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_253594164780828539) {
  err_fun(nom_x, delta_x, out_253594164780828539);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2215340346188359086) {
  inv_err_fun(nom_x, true_x, out_2215340346188359086);
}
void pose_H_mod_fun(double *state, double *out_1114507033744955760) {
  H_mod_fun(state, out_1114507033744955760);
}
void pose_f_fun(double *state, double dt, double *out_7503615216406855844) {
  f_fun(state,  dt, out_7503615216406855844);
}
void pose_F_fun(double *state, double dt, double *out_448987525618456395) {
  F_fun(state,  dt, out_448987525618456395);
}
void pose_h_4(double *state, double *unused, double *out_227196828506725750) {
  h_4(state, unused, out_227196828506725750);
}
void pose_H_4(double *state, double *unused, double *out_1868668035799668367) {
  H_4(state, unused, out_1868668035799668367);
}
void pose_h_10(double *state, double *unused, double *out_2719718819013543410) {
  h_10(state, unused, out_2719718819013543410);
}
void pose_H_10(double *state, double *unused, double *out_8678441851357101835) {
  H_10(state, unused, out_8678441851357101835);
}
void pose_h_13(double *state, double *unused, double *out_2726070254487103051) {
  h_13(state, unused, out_2726070254487103051);
}
void pose_H_13(double *state, double *unused, double *out_5080941861132001168) {
  H_13(state, unused, out_5080941861132001168);
}
void pose_h_14(double *state, double *unused, double *out_8209254362122978467) {
  h_14(state, unused, out_8209254362122978467);
}
void pose_H_14(double *state, double *unused, double *out_5831908892139152896) {
  H_14(state, unused, out_5831908892139152896);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
