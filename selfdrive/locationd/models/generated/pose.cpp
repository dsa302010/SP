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
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_9096196563184828167) {
   out_9096196563184828167[0] = delta_x[0] + nom_x[0];
   out_9096196563184828167[1] = delta_x[1] + nom_x[1];
   out_9096196563184828167[2] = delta_x[2] + nom_x[2];
   out_9096196563184828167[3] = delta_x[3] + nom_x[3];
   out_9096196563184828167[4] = delta_x[4] + nom_x[4];
   out_9096196563184828167[5] = delta_x[5] + nom_x[5];
   out_9096196563184828167[6] = delta_x[6] + nom_x[6];
   out_9096196563184828167[7] = delta_x[7] + nom_x[7];
   out_9096196563184828167[8] = delta_x[8] + nom_x[8];
   out_9096196563184828167[9] = delta_x[9] + nom_x[9];
   out_9096196563184828167[10] = delta_x[10] + nom_x[10];
   out_9096196563184828167[11] = delta_x[11] + nom_x[11];
   out_9096196563184828167[12] = delta_x[12] + nom_x[12];
   out_9096196563184828167[13] = delta_x[13] + nom_x[13];
   out_9096196563184828167[14] = delta_x[14] + nom_x[14];
   out_9096196563184828167[15] = delta_x[15] + nom_x[15];
   out_9096196563184828167[16] = delta_x[16] + nom_x[16];
   out_9096196563184828167[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2510715355574267806) {
   out_2510715355574267806[0] = -nom_x[0] + true_x[0];
   out_2510715355574267806[1] = -nom_x[1] + true_x[1];
   out_2510715355574267806[2] = -nom_x[2] + true_x[2];
   out_2510715355574267806[3] = -nom_x[3] + true_x[3];
   out_2510715355574267806[4] = -nom_x[4] + true_x[4];
   out_2510715355574267806[5] = -nom_x[5] + true_x[5];
   out_2510715355574267806[6] = -nom_x[6] + true_x[6];
   out_2510715355574267806[7] = -nom_x[7] + true_x[7];
   out_2510715355574267806[8] = -nom_x[8] + true_x[8];
   out_2510715355574267806[9] = -nom_x[9] + true_x[9];
   out_2510715355574267806[10] = -nom_x[10] + true_x[10];
   out_2510715355574267806[11] = -nom_x[11] + true_x[11];
   out_2510715355574267806[12] = -nom_x[12] + true_x[12];
   out_2510715355574267806[13] = -nom_x[13] + true_x[13];
   out_2510715355574267806[14] = -nom_x[14] + true_x[14];
   out_2510715355574267806[15] = -nom_x[15] + true_x[15];
   out_2510715355574267806[16] = -nom_x[16] + true_x[16];
   out_2510715355574267806[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6571093323919857525) {
   out_6571093323919857525[0] = 1.0;
   out_6571093323919857525[1] = 0.0;
   out_6571093323919857525[2] = 0.0;
   out_6571093323919857525[3] = 0.0;
   out_6571093323919857525[4] = 0.0;
   out_6571093323919857525[5] = 0.0;
   out_6571093323919857525[6] = 0.0;
   out_6571093323919857525[7] = 0.0;
   out_6571093323919857525[8] = 0.0;
   out_6571093323919857525[9] = 0.0;
   out_6571093323919857525[10] = 0.0;
   out_6571093323919857525[11] = 0.0;
   out_6571093323919857525[12] = 0.0;
   out_6571093323919857525[13] = 0.0;
   out_6571093323919857525[14] = 0.0;
   out_6571093323919857525[15] = 0.0;
   out_6571093323919857525[16] = 0.0;
   out_6571093323919857525[17] = 0.0;
   out_6571093323919857525[18] = 0.0;
   out_6571093323919857525[19] = 1.0;
   out_6571093323919857525[20] = 0.0;
   out_6571093323919857525[21] = 0.0;
   out_6571093323919857525[22] = 0.0;
   out_6571093323919857525[23] = 0.0;
   out_6571093323919857525[24] = 0.0;
   out_6571093323919857525[25] = 0.0;
   out_6571093323919857525[26] = 0.0;
   out_6571093323919857525[27] = 0.0;
   out_6571093323919857525[28] = 0.0;
   out_6571093323919857525[29] = 0.0;
   out_6571093323919857525[30] = 0.0;
   out_6571093323919857525[31] = 0.0;
   out_6571093323919857525[32] = 0.0;
   out_6571093323919857525[33] = 0.0;
   out_6571093323919857525[34] = 0.0;
   out_6571093323919857525[35] = 0.0;
   out_6571093323919857525[36] = 0.0;
   out_6571093323919857525[37] = 0.0;
   out_6571093323919857525[38] = 1.0;
   out_6571093323919857525[39] = 0.0;
   out_6571093323919857525[40] = 0.0;
   out_6571093323919857525[41] = 0.0;
   out_6571093323919857525[42] = 0.0;
   out_6571093323919857525[43] = 0.0;
   out_6571093323919857525[44] = 0.0;
   out_6571093323919857525[45] = 0.0;
   out_6571093323919857525[46] = 0.0;
   out_6571093323919857525[47] = 0.0;
   out_6571093323919857525[48] = 0.0;
   out_6571093323919857525[49] = 0.0;
   out_6571093323919857525[50] = 0.0;
   out_6571093323919857525[51] = 0.0;
   out_6571093323919857525[52] = 0.0;
   out_6571093323919857525[53] = 0.0;
   out_6571093323919857525[54] = 0.0;
   out_6571093323919857525[55] = 0.0;
   out_6571093323919857525[56] = 0.0;
   out_6571093323919857525[57] = 1.0;
   out_6571093323919857525[58] = 0.0;
   out_6571093323919857525[59] = 0.0;
   out_6571093323919857525[60] = 0.0;
   out_6571093323919857525[61] = 0.0;
   out_6571093323919857525[62] = 0.0;
   out_6571093323919857525[63] = 0.0;
   out_6571093323919857525[64] = 0.0;
   out_6571093323919857525[65] = 0.0;
   out_6571093323919857525[66] = 0.0;
   out_6571093323919857525[67] = 0.0;
   out_6571093323919857525[68] = 0.0;
   out_6571093323919857525[69] = 0.0;
   out_6571093323919857525[70] = 0.0;
   out_6571093323919857525[71] = 0.0;
   out_6571093323919857525[72] = 0.0;
   out_6571093323919857525[73] = 0.0;
   out_6571093323919857525[74] = 0.0;
   out_6571093323919857525[75] = 0.0;
   out_6571093323919857525[76] = 1.0;
   out_6571093323919857525[77] = 0.0;
   out_6571093323919857525[78] = 0.0;
   out_6571093323919857525[79] = 0.0;
   out_6571093323919857525[80] = 0.0;
   out_6571093323919857525[81] = 0.0;
   out_6571093323919857525[82] = 0.0;
   out_6571093323919857525[83] = 0.0;
   out_6571093323919857525[84] = 0.0;
   out_6571093323919857525[85] = 0.0;
   out_6571093323919857525[86] = 0.0;
   out_6571093323919857525[87] = 0.0;
   out_6571093323919857525[88] = 0.0;
   out_6571093323919857525[89] = 0.0;
   out_6571093323919857525[90] = 0.0;
   out_6571093323919857525[91] = 0.0;
   out_6571093323919857525[92] = 0.0;
   out_6571093323919857525[93] = 0.0;
   out_6571093323919857525[94] = 0.0;
   out_6571093323919857525[95] = 1.0;
   out_6571093323919857525[96] = 0.0;
   out_6571093323919857525[97] = 0.0;
   out_6571093323919857525[98] = 0.0;
   out_6571093323919857525[99] = 0.0;
   out_6571093323919857525[100] = 0.0;
   out_6571093323919857525[101] = 0.0;
   out_6571093323919857525[102] = 0.0;
   out_6571093323919857525[103] = 0.0;
   out_6571093323919857525[104] = 0.0;
   out_6571093323919857525[105] = 0.0;
   out_6571093323919857525[106] = 0.0;
   out_6571093323919857525[107] = 0.0;
   out_6571093323919857525[108] = 0.0;
   out_6571093323919857525[109] = 0.0;
   out_6571093323919857525[110] = 0.0;
   out_6571093323919857525[111] = 0.0;
   out_6571093323919857525[112] = 0.0;
   out_6571093323919857525[113] = 0.0;
   out_6571093323919857525[114] = 1.0;
   out_6571093323919857525[115] = 0.0;
   out_6571093323919857525[116] = 0.0;
   out_6571093323919857525[117] = 0.0;
   out_6571093323919857525[118] = 0.0;
   out_6571093323919857525[119] = 0.0;
   out_6571093323919857525[120] = 0.0;
   out_6571093323919857525[121] = 0.0;
   out_6571093323919857525[122] = 0.0;
   out_6571093323919857525[123] = 0.0;
   out_6571093323919857525[124] = 0.0;
   out_6571093323919857525[125] = 0.0;
   out_6571093323919857525[126] = 0.0;
   out_6571093323919857525[127] = 0.0;
   out_6571093323919857525[128] = 0.0;
   out_6571093323919857525[129] = 0.0;
   out_6571093323919857525[130] = 0.0;
   out_6571093323919857525[131] = 0.0;
   out_6571093323919857525[132] = 0.0;
   out_6571093323919857525[133] = 1.0;
   out_6571093323919857525[134] = 0.0;
   out_6571093323919857525[135] = 0.0;
   out_6571093323919857525[136] = 0.0;
   out_6571093323919857525[137] = 0.0;
   out_6571093323919857525[138] = 0.0;
   out_6571093323919857525[139] = 0.0;
   out_6571093323919857525[140] = 0.0;
   out_6571093323919857525[141] = 0.0;
   out_6571093323919857525[142] = 0.0;
   out_6571093323919857525[143] = 0.0;
   out_6571093323919857525[144] = 0.0;
   out_6571093323919857525[145] = 0.0;
   out_6571093323919857525[146] = 0.0;
   out_6571093323919857525[147] = 0.0;
   out_6571093323919857525[148] = 0.0;
   out_6571093323919857525[149] = 0.0;
   out_6571093323919857525[150] = 0.0;
   out_6571093323919857525[151] = 0.0;
   out_6571093323919857525[152] = 1.0;
   out_6571093323919857525[153] = 0.0;
   out_6571093323919857525[154] = 0.0;
   out_6571093323919857525[155] = 0.0;
   out_6571093323919857525[156] = 0.0;
   out_6571093323919857525[157] = 0.0;
   out_6571093323919857525[158] = 0.0;
   out_6571093323919857525[159] = 0.0;
   out_6571093323919857525[160] = 0.0;
   out_6571093323919857525[161] = 0.0;
   out_6571093323919857525[162] = 0.0;
   out_6571093323919857525[163] = 0.0;
   out_6571093323919857525[164] = 0.0;
   out_6571093323919857525[165] = 0.0;
   out_6571093323919857525[166] = 0.0;
   out_6571093323919857525[167] = 0.0;
   out_6571093323919857525[168] = 0.0;
   out_6571093323919857525[169] = 0.0;
   out_6571093323919857525[170] = 0.0;
   out_6571093323919857525[171] = 1.0;
   out_6571093323919857525[172] = 0.0;
   out_6571093323919857525[173] = 0.0;
   out_6571093323919857525[174] = 0.0;
   out_6571093323919857525[175] = 0.0;
   out_6571093323919857525[176] = 0.0;
   out_6571093323919857525[177] = 0.0;
   out_6571093323919857525[178] = 0.0;
   out_6571093323919857525[179] = 0.0;
   out_6571093323919857525[180] = 0.0;
   out_6571093323919857525[181] = 0.0;
   out_6571093323919857525[182] = 0.0;
   out_6571093323919857525[183] = 0.0;
   out_6571093323919857525[184] = 0.0;
   out_6571093323919857525[185] = 0.0;
   out_6571093323919857525[186] = 0.0;
   out_6571093323919857525[187] = 0.0;
   out_6571093323919857525[188] = 0.0;
   out_6571093323919857525[189] = 0.0;
   out_6571093323919857525[190] = 1.0;
   out_6571093323919857525[191] = 0.0;
   out_6571093323919857525[192] = 0.0;
   out_6571093323919857525[193] = 0.0;
   out_6571093323919857525[194] = 0.0;
   out_6571093323919857525[195] = 0.0;
   out_6571093323919857525[196] = 0.0;
   out_6571093323919857525[197] = 0.0;
   out_6571093323919857525[198] = 0.0;
   out_6571093323919857525[199] = 0.0;
   out_6571093323919857525[200] = 0.0;
   out_6571093323919857525[201] = 0.0;
   out_6571093323919857525[202] = 0.0;
   out_6571093323919857525[203] = 0.0;
   out_6571093323919857525[204] = 0.0;
   out_6571093323919857525[205] = 0.0;
   out_6571093323919857525[206] = 0.0;
   out_6571093323919857525[207] = 0.0;
   out_6571093323919857525[208] = 0.0;
   out_6571093323919857525[209] = 1.0;
   out_6571093323919857525[210] = 0.0;
   out_6571093323919857525[211] = 0.0;
   out_6571093323919857525[212] = 0.0;
   out_6571093323919857525[213] = 0.0;
   out_6571093323919857525[214] = 0.0;
   out_6571093323919857525[215] = 0.0;
   out_6571093323919857525[216] = 0.0;
   out_6571093323919857525[217] = 0.0;
   out_6571093323919857525[218] = 0.0;
   out_6571093323919857525[219] = 0.0;
   out_6571093323919857525[220] = 0.0;
   out_6571093323919857525[221] = 0.0;
   out_6571093323919857525[222] = 0.0;
   out_6571093323919857525[223] = 0.0;
   out_6571093323919857525[224] = 0.0;
   out_6571093323919857525[225] = 0.0;
   out_6571093323919857525[226] = 0.0;
   out_6571093323919857525[227] = 0.0;
   out_6571093323919857525[228] = 1.0;
   out_6571093323919857525[229] = 0.0;
   out_6571093323919857525[230] = 0.0;
   out_6571093323919857525[231] = 0.0;
   out_6571093323919857525[232] = 0.0;
   out_6571093323919857525[233] = 0.0;
   out_6571093323919857525[234] = 0.0;
   out_6571093323919857525[235] = 0.0;
   out_6571093323919857525[236] = 0.0;
   out_6571093323919857525[237] = 0.0;
   out_6571093323919857525[238] = 0.0;
   out_6571093323919857525[239] = 0.0;
   out_6571093323919857525[240] = 0.0;
   out_6571093323919857525[241] = 0.0;
   out_6571093323919857525[242] = 0.0;
   out_6571093323919857525[243] = 0.0;
   out_6571093323919857525[244] = 0.0;
   out_6571093323919857525[245] = 0.0;
   out_6571093323919857525[246] = 0.0;
   out_6571093323919857525[247] = 1.0;
   out_6571093323919857525[248] = 0.0;
   out_6571093323919857525[249] = 0.0;
   out_6571093323919857525[250] = 0.0;
   out_6571093323919857525[251] = 0.0;
   out_6571093323919857525[252] = 0.0;
   out_6571093323919857525[253] = 0.0;
   out_6571093323919857525[254] = 0.0;
   out_6571093323919857525[255] = 0.0;
   out_6571093323919857525[256] = 0.0;
   out_6571093323919857525[257] = 0.0;
   out_6571093323919857525[258] = 0.0;
   out_6571093323919857525[259] = 0.0;
   out_6571093323919857525[260] = 0.0;
   out_6571093323919857525[261] = 0.0;
   out_6571093323919857525[262] = 0.0;
   out_6571093323919857525[263] = 0.0;
   out_6571093323919857525[264] = 0.0;
   out_6571093323919857525[265] = 0.0;
   out_6571093323919857525[266] = 1.0;
   out_6571093323919857525[267] = 0.0;
   out_6571093323919857525[268] = 0.0;
   out_6571093323919857525[269] = 0.0;
   out_6571093323919857525[270] = 0.0;
   out_6571093323919857525[271] = 0.0;
   out_6571093323919857525[272] = 0.0;
   out_6571093323919857525[273] = 0.0;
   out_6571093323919857525[274] = 0.0;
   out_6571093323919857525[275] = 0.0;
   out_6571093323919857525[276] = 0.0;
   out_6571093323919857525[277] = 0.0;
   out_6571093323919857525[278] = 0.0;
   out_6571093323919857525[279] = 0.0;
   out_6571093323919857525[280] = 0.0;
   out_6571093323919857525[281] = 0.0;
   out_6571093323919857525[282] = 0.0;
   out_6571093323919857525[283] = 0.0;
   out_6571093323919857525[284] = 0.0;
   out_6571093323919857525[285] = 1.0;
   out_6571093323919857525[286] = 0.0;
   out_6571093323919857525[287] = 0.0;
   out_6571093323919857525[288] = 0.0;
   out_6571093323919857525[289] = 0.0;
   out_6571093323919857525[290] = 0.0;
   out_6571093323919857525[291] = 0.0;
   out_6571093323919857525[292] = 0.0;
   out_6571093323919857525[293] = 0.0;
   out_6571093323919857525[294] = 0.0;
   out_6571093323919857525[295] = 0.0;
   out_6571093323919857525[296] = 0.0;
   out_6571093323919857525[297] = 0.0;
   out_6571093323919857525[298] = 0.0;
   out_6571093323919857525[299] = 0.0;
   out_6571093323919857525[300] = 0.0;
   out_6571093323919857525[301] = 0.0;
   out_6571093323919857525[302] = 0.0;
   out_6571093323919857525[303] = 0.0;
   out_6571093323919857525[304] = 1.0;
   out_6571093323919857525[305] = 0.0;
   out_6571093323919857525[306] = 0.0;
   out_6571093323919857525[307] = 0.0;
   out_6571093323919857525[308] = 0.0;
   out_6571093323919857525[309] = 0.0;
   out_6571093323919857525[310] = 0.0;
   out_6571093323919857525[311] = 0.0;
   out_6571093323919857525[312] = 0.0;
   out_6571093323919857525[313] = 0.0;
   out_6571093323919857525[314] = 0.0;
   out_6571093323919857525[315] = 0.0;
   out_6571093323919857525[316] = 0.0;
   out_6571093323919857525[317] = 0.0;
   out_6571093323919857525[318] = 0.0;
   out_6571093323919857525[319] = 0.0;
   out_6571093323919857525[320] = 0.0;
   out_6571093323919857525[321] = 0.0;
   out_6571093323919857525[322] = 0.0;
   out_6571093323919857525[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8641421515160522541) {
   out_8641421515160522541[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8641421515160522541[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8641421515160522541[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8641421515160522541[3] = dt*state[12] + state[3];
   out_8641421515160522541[4] = dt*state[13] + state[4];
   out_8641421515160522541[5] = dt*state[14] + state[5];
   out_8641421515160522541[6] = state[6];
   out_8641421515160522541[7] = state[7];
   out_8641421515160522541[8] = state[8];
   out_8641421515160522541[9] = state[9];
   out_8641421515160522541[10] = state[10];
   out_8641421515160522541[11] = state[11];
   out_8641421515160522541[12] = state[12];
   out_8641421515160522541[13] = state[13];
   out_8641421515160522541[14] = state[14];
   out_8641421515160522541[15] = state[15];
   out_8641421515160522541[16] = state[16];
   out_8641421515160522541[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1965387258042231969) {
   out_1965387258042231969[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1965387258042231969[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1965387258042231969[2] = 0;
   out_1965387258042231969[3] = 0;
   out_1965387258042231969[4] = 0;
   out_1965387258042231969[5] = 0;
   out_1965387258042231969[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1965387258042231969[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1965387258042231969[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1965387258042231969[9] = 0;
   out_1965387258042231969[10] = 0;
   out_1965387258042231969[11] = 0;
   out_1965387258042231969[12] = 0;
   out_1965387258042231969[13] = 0;
   out_1965387258042231969[14] = 0;
   out_1965387258042231969[15] = 0;
   out_1965387258042231969[16] = 0;
   out_1965387258042231969[17] = 0;
   out_1965387258042231969[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1965387258042231969[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1965387258042231969[20] = 0;
   out_1965387258042231969[21] = 0;
   out_1965387258042231969[22] = 0;
   out_1965387258042231969[23] = 0;
   out_1965387258042231969[24] = 0;
   out_1965387258042231969[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1965387258042231969[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1965387258042231969[27] = 0;
   out_1965387258042231969[28] = 0;
   out_1965387258042231969[29] = 0;
   out_1965387258042231969[30] = 0;
   out_1965387258042231969[31] = 0;
   out_1965387258042231969[32] = 0;
   out_1965387258042231969[33] = 0;
   out_1965387258042231969[34] = 0;
   out_1965387258042231969[35] = 0;
   out_1965387258042231969[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1965387258042231969[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1965387258042231969[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1965387258042231969[39] = 0;
   out_1965387258042231969[40] = 0;
   out_1965387258042231969[41] = 0;
   out_1965387258042231969[42] = 0;
   out_1965387258042231969[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1965387258042231969[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1965387258042231969[45] = 0;
   out_1965387258042231969[46] = 0;
   out_1965387258042231969[47] = 0;
   out_1965387258042231969[48] = 0;
   out_1965387258042231969[49] = 0;
   out_1965387258042231969[50] = 0;
   out_1965387258042231969[51] = 0;
   out_1965387258042231969[52] = 0;
   out_1965387258042231969[53] = 0;
   out_1965387258042231969[54] = 0;
   out_1965387258042231969[55] = 0;
   out_1965387258042231969[56] = 0;
   out_1965387258042231969[57] = 1;
   out_1965387258042231969[58] = 0;
   out_1965387258042231969[59] = 0;
   out_1965387258042231969[60] = 0;
   out_1965387258042231969[61] = 0;
   out_1965387258042231969[62] = 0;
   out_1965387258042231969[63] = 0;
   out_1965387258042231969[64] = 0;
   out_1965387258042231969[65] = 0;
   out_1965387258042231969[66] = dt;
   out_1965387258042231969[67] = 0;
   out_1965387258042231969[68] = 0;
   out_1965387258042231969[69] = 0;
   out_1965387258042231969[70] = 0;
   out_1965387258042231969[71] = 0;
   out_1965387258042231969[72] = 0;
   out_1965387258042231969[73] = 0;
   out_1965387258042231969[74] = 0;
   out_1965387258042231969[75] = 0;
   out_1965387258042231969[76] = 1;
   out_1965387258042231969[77] = 0;
   out_1965387258042231969[78] = 0;
   out_1965387258042231969[79] = 0;
   out_1965387258042231969[80] = 0;
   out_1965387258042231969[81] = 0;
   out_1965387258042231969[82] = 0;
   out_1965387258042231969[83] = 0;
   out_1965387258042231969[84] = 0;
   out_1965387258042231969[85] = dt;
   out_1965387258042231969[86] = 0;
   out_1965387258042231969[87] = 0;
   out_1965387258042231969[88] = 0;
   out_1965387258042231969[89] = 0;
   out_1965387258042231969[90] = 0;
   out_1965387258042231969[91] = 0;
   out_1965387258042231969[92] = 0;
   out_1965387258042231969[93] = 0;
   out_1965387258042231969[94] = 0;
   out_1965387258042231969[95] = 1;
   out_1965387258042231969[96] = 0;
   out_1965387258042231969[97] = 0;
   out_1965387258042231969[98] = 0;
   out_1965387258042231969[99] = 0;
   out_1965387258042231969[100] = 0;
   out_1965387258042231969[101] = 0;
   out_1965387258042231969[102] = 0;
   out_1965387258042231969[103] = 0;
   out_1965387258042231969[104] = dt;
   out_1965387258042231969[105] = 0;
   out_1965387258042231969[106] = 0;
   out_1965387258042231969[107] = 0;
   out_1965387258042231969[108] = 0;
   out_1965387258042231969[109] = 0;
   out_1965387258042231969[110] = 0;
   out_1965387258042231969[111] = 0;
   out_1965387258042231969[112] = 0;
   out_1965387258042231969[113] = 0;
   out_1965387258042231969[114] = 1;
   out_1965387258042231969[115] = 0;
   out_1965387258042231969[116] = 0;
   out_1965387258042231969[117] = 0;
   out_1965387258042231969[118] = 0;
   out_1965387258042231969[119] = 0;
   out_1965387258042231969[120] = 0;
   out_1965387258042231969[121] = 0;
   out_1965387258042231969[122] = 0;
   out_1965387258042231969[123] = 0;
   out_1965387258042231969[124] = 0;
   out_1965387258042231969[125] = 0;
   out_1965387258042231969[126] = 0;
   out_1965387258042231969[127] = 0;
   out_1965387258042231969[128] = 0;
   out_1965387258042231969[129] = 0;
   out_1965387258042231969[130] = 0;
   out_1965387258042231969[131] = 0;
   out_1965387258042231969[132] = 0;
   out_1965387258042231969[133] = 1;
   out_1965387258042231969[134] = 0;
   out_1965387258042231969[135] = 0;
   out_1965387258042231969[136] = 0;
   out_1965387258042231969[137] = 0;
   out_1965387258042231969[138] = 0;
   out_1965387258042231969[139] = 0;
   out_1965387258042231969[140] = 0;
   out_1965387258042231969[141] = 0;
   out_1965387258042231969[142] = 0;
   out_1965387258042231969[143] = 0;
   out_1965387258042231969[144] = 0;
   out_1965387258042231969[145] = 0;
   out_1965387258042231969[146] = 0;
   out_1965387258042231969[147] = 0;
   out_1965387258042231969[148] = 0;
   out_1965387258042231969[149] = 0;
   out_1965387258042231969[150] = 0;
   out_1965387258042231969[151] = 0;
   out_1965387258042231969[152] = 1;
   out_1965387258042231969[153] = 0;
   out_1965387258042231969[154] = 0;
   out_1965387258042231969[155] = 0;
   out_1965387258042231969[156] = 0;
   out_1965387258042231969[157] = 0;
   out_1965387258042231969[158] = 0;
   out_1965387258042231969[159] = 0;
   out_1965387258042231969[160] = 0;
   out_1965387258042231969[161] = 0;
   out_1965387258042231969[162] = 0;
   out_1965387258042231969[163] = 0;
   out_1965387258042231969[164] = 0;
   out_1965387258042231969[165] = 0;
   out_1965387258042231969[166] = 0;
   out_1965387258042231969[167] = 0;
   out_1965387258042231969[168] = 0;
   out_1965387258042231969[169] = 0;
   out_1965387258042231969[170] = 0;
   out_1965387258042231969[171] = 1;
   out_1965387258042231969[172] = 0;
   out_1965387258042231969[173] = 0;
   out_1965387258042231969[174] = 0;
   out_1965387258042231969[175] = 0;
   out_1965387258042231969[176] = 0;
   out_1965387258042231969[177] = 0;
   out_1965387258042231969[178] = 0;
   out_1965387258042231969[179] = 0;
   out_1965387258042231969[180] = 0;
   out_1965387258042231969[181] = 0;
   out_1965387258042231969[182] = 0;
   out_1965387258042231969[183] = 0;
   out_1965387258042231969[184] = 0;
   out_1965387258042231969[185] = 0;
   out_1965387258042231969[186] = 0;
   out_1965387258042231969[187] = 0;
   out_1965387258042231969[188] = 0;
   out_1965387258042231969[189] = 0;
   out_1965387258042231969[190] = 1;
   out_1965387258042231969[191] = 0;
   out_1965387258042231969[192] = 0;
   out_1965387258042231969[193] = 0;
   out_1965387258042231969[194] = 0;
   out_1965387258042231969[195] = 0;
   out_1965387258042231969[196] = 0;
   out_1965387258042231969[197] = 0;
   out_1965387258042231969[198] = 0;
   out_1965387258042231969[199] = 0;
   out_1965387258042231969[200] = 0;
   out_1965387258042231969[201] = 0;
   out_1965387258042231969[202] = 0;
   out_1965387258042231969[203] = 0;
   out_1965387258042231969[204] = 0;
   out_1965387258042231969[205] = 0;
   out_1965387258042231969[206] = 0;
   out_1965387258042231969[207] = 0;
   out_1965387258042231969[208] = 0;
   out_1965387258042231969[209] = 1;
   out_1965387258042231969[210] = 0;
   out_1965387258042231969[211] = 0;
   out_1965387258042231969[212] = 0;
   out_1965387258042231969[213] = 0;
   out_1965387258042231969[214] = 0;
   out_1965387258042231969[215] = 0;
   out_1965387258042231969[216] = 0;
   out_1965387258042231969[217] = 0;
   out_1965387258042231969[218] = 0;
   out_1965387258042231969[219] = 0;
   out_1965387258042231969[220] = 0;
   out_1965387258042231969[221] = 0;
   out_1965387258042231969[222] = 0;
   out_1965387258042231969[223] = 0;
   out_1965387258042231969[224] = 0;
   out_1965387258042231969[225] = 0;
   out_1965387258042231969[226] = 0;
   out_1965387258042231969[227] = 0;
   out_1965387258042231969[228] = 1;
   out_1965387258042231969[229] = 0;
   out_1965387258042231969[230] = 0;
   out_1965387258042231969[231] = 0;
   out_1965387258042231969[232] = 0;
   out_1965387258042231969[233] = 0;
   out_1965387258042231969[234] = 0;
   out_1965387258042231969[235] = 0;
   out_1965387258042231969[236] = 0;
   out_1965387258042231969[237] = 0;
   out_1965387258042231969[238] = 0;
   out_1965387258042231969[239] = 0;
   out_1965387258042231969[240] = 0;
   out_1965387258042231969[241] = 0;
   out_1965387258042231969[242] = 0;
   out_1965387258042231969[243] = 0;
   out_1965387258042231969[244] = 0;
   out_1965387258042231969[245] = 0;
   out_1965387258042231969[246] = 0;
   out_1965387258042231969[247] = 1;
   out_1965387258042231969[248] = 0;
   out_1965387258042231969[249] = 0;
   out_1965387258042231969[250] = 0;
   out_1965387258042231969[251] = 0;
   out_1965387258042231969[252] = 0;
   out_1965387258042231969[253] = 0;
   out_1965387258042231969[254] = 0;
   out_1965387258042231969[255] = 0;
   out_1965387258042231969[256] = 0;
   out_1965387258042231969[257] = 0;
   out_1965387258042231969[258] = 0;
   out_1965387258042231969[259] = 0;
   out_1965387258042231969[260] = 0;
   out_1965387258042231969[261] = 0;
   out_1965387258042231969[262] = 0;
   out_1965387258042231969[263] = 0;
   out_1965387258042231969[264] = 0;
   out_1965387258042231969[265] = 0;
   out_1965387258042231969[266] = 1;
   out_1965387258042231969[267] = 0;
   out_1965387258042231969[268] = 0;
   out_1965387258042231969[269] = 0;
   out_1965387258042231969[270] = 0;
   out_1965387258042231969[271] = 0;
   out_1965387258042231969[272] = 0;
   out_1965387258042231969[273] = 0;
   out_1965387258042231969[274] = 0;
   out_1965387258042231969[275] = 0;
   out_1965387258042231969[276] = 0;
   out_1965387258042231969[277] = 0;
   out_1965387258042231969[278] = 0;
   out_1965387258042231969[279] = 0;
   out_1965387258042231969[280] = 0;
   out_1965387258042231969[281] = 0;
   out_1965387258042231969[282] = 0;
   out_1965387258042231969[283] = 0;
   out_1965387258042231969[284] = 0;
   out_1965387258042231969[285] = 1;
   out_1965387258042231969[286] = 0;
   out_1965387258042231969[287] = 0;
   out_1965387258042231969[288] = 0;
   out_1965387258042231969[289] = 0;
   out_1965387258042231969[290] = 0;
   out_1965387258042231969[291] = 0;
   out_1965387258042231969[292] = 0;
   out_1965387258042231969[293] = 0;
   out_1965387258042231969[294] = 0;
   out_1965387258042231969[295] = 0;
   out_1965387258042231969[296] = 0;
   out_1965387258042231969[297] = 0;
   out_1965387258042231969[298] = 0;
   out_1965387258042231969[299] = 0;
   out_1965387258042231969[300] = 0;
   out_1965387258042231969[301] = 0;
   out_1965387258042231969[302] = 0;
   out_1965387258042231969[303] = 0;
   out_1965387258042231969[304] = 1;
   out_1965387258042231969[305] = 0;
   out_1965387258042231969[306] = 0;
   out_1965387258042231969[307] = 0;
   out_1965387258042231969[308] = 0;
   out_1965387258042231969[309] = 0;
   out_1965387258042231969[310] = 0;
   out_1965387258042231969[311] = 0;
   out_1965387258042231969[312] = 0;
   out_1965387258042231969[313] = 0;
   out_1965387258042231969[314] = 0;
   out_1965387258042231969[315] = 0;
   out_1965387258042231969[316] = 0;
   out_1965387258042231969[317] = 0;
   out_1965387258042231969[318] = 0;
   out_1965387258042231969[319] = 0;
   out_1965387258042231969[320] = 0;
   out_1965387258042231969[321] = 0;
   out_1965387258042231969[322] = 0;
   out_1965387258042231969[323] = 1;
}
void h_4(double *state, double *unused, double *out_5430219983567452590) {
   out_5430219983567452590[0] = state[6] + state[9];
   out_5430219983567452590[1] = state[7] + state[10];
   out_5430219983567452590[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3296871245128908272) {
   out_3296871245128908272[0] = 0;
   out_3296871245128908272[1] = 0;
   out_3296871245128908272[2] = 0;
   out_3296871245128908272[3] = 0;
   out_3296871245128908272[4] = 0;
   out_3296871245128908272[5] = 0;
   out_3296871245128908272[6] = 1;
   out_3296871245128908272[7] = 0;
   out_3296871245128908272[8] = 0;
   out_3296871245128908272[9] = 1;
   out_3296871245128908272[10] = 0;
   out_3296871245128908272[11] = 0;
   out_3296871245128908272[12] = 0;
   out_3296871245128908272[13] = 0;
   out_3296871245128908272[14] = 0;
   out_3296871245128908272[15] = 0;
   out_3296871245128908272[16] = 0;
   out_3296871245128908272[17] = 0;
   out_3296871245128908272[18] = 0;
   out_3296871245128908272[19] = 0;
   out_3296871245128908272[20] = 0;
   out_3296871245128908272[21] = 0;
   out_3296871245128908272[22] = 0;
   out_3296871245128908272[23] = 0;
   out_3296871245128908272[24] = 0;
   out_3296871245128908272[25] = 1;
   out_3296871245128908272[26] = 0;
   out_3296871245128908272[27] = 0;
   out_3296871245128908272[28] = 1;
   out_3296871245128908272[29] = 0;
   out_3296871245128908272[30] = 0;
   out_3296871245128908272[31] = 0;
   out_3296871245128908272[32] = 0;
   out_3296871245128908272[33] = 0;
   out_3296871245128908272[34] = 0;
   out_3296871245128908272[35] = 0;
   out_3296871245128908272[36] = 0;
   out_3296871245128908272[37] = 0;
   out_3296871245128908272[38] = 0;
   out_3296871245128908272[39] = 0;
   out_3296871245128908272[40] = 0;
   out_3296871245128908272[41] = 0;
   out_3296871245128908272[42] = 0;
   out_3296871245128908272[43] = 0;
   out_3296871245128908272[44] = 1;
   out_3296871245128908272[45] = 0;
   out_3296871245128908272[46] = 0;
   out_3296871245128908272[47] = 1;
   out_3296871245128908272[48] = 0;
   out_3296871245128908272[49] = 0;
   out_3296871245128908272[50] = 0;
   out_3296871245128908272[51] = 0;
   out_3296871245128908272[52] = 0;
   out_3296871245128908272[53] = 0;
}
void h_10(double *state, double *unused, double *out_2671944880378075133) {
   out_2671944880378075133[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2671944880378075133[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2671944880378075133[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1775443925111280628) {
   out_1775443925111280628[0] = 0;
   out_1775443925111280628[1] = 9.8100000000000005*cos(state[1]);
   out_1775443925111280628[2] = 0;
   out_1775443925111280628[3] = 0;
   out_1775443925111280628[4] = -state[8];
   out_1775443925111280628[5] = state[7];
   out_1775443925111280628[6] = 0;
   out_1775443925111280628[7] = state[5];
   out_1775443925111280628[8] = -state[4];
   out_1775443925111280628[9] = 0;
   out_1775443925111280628[10] = 0;
   out_1775443925111280628[11] = 0;
   out_1775443925111280628[12] = 1;
   out_1775443925111280628[13] = 0;
   out_1775443925111280628[14] = 0;
   out_1775443925111280628[15] = 1;
   out_1775443925111280628[16] = 0;
   out_1775443925111280628[17] = 0;
   out_1775443925111280628[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1775443925111280628[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1775443925111280628[20] = 0;
   out_1775443925111280628[21] = state[8];
   out_1775443925111280628[22] = 0;
   out_1775443925111280628[23] = -state[6];
   out_1775443925111280628[24] = -state[5];
   out_1775443925111280628[25] = 0;
   out_1775443925111280628[26] = state[3];
   out_1775443925111280628[27] = 0;
   out_1775443925111280628[28] = 0;
   out_1775443925111280628[29] = 0;
   out_1775443925111280628[30] = 0;
   out_1775443925111280628[31] = 1;
   out_1775443925111280628[32] = 0;
   out_1775443925111280628[33] = 0;
   out_1775443925111280628[34] = 1;
   out_1775443925111280628[35] = 0;
   out_1775443925111280628[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1775443925111280628[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1775443925111280628[38] = 0;
   out_1775443925111280628[39] = -state[7];
   out_1775443925111280628[40] = state[6];
   out_1775443925111280628[41] = 0;
   out_1775443925111280628[42] = state[4];
   out_1775443925111280628[43] = -state[3];
   out_1775443925111280628[44] = 0;
   out_1775443925111280628[45] = 0;
   out_1775443925111280628[46] = 0;
   out_1775443925111280628[47] = 0;
   out_1775443925111280628[48] = 0;
   out_1775443925111280628[49] = 0;
   out_1775443925111280628[50] = 1;
   out_1775443925111280628[51] = 0;
   out_1775443925111280628[52] = 0;
   out_1775443925111280628[53] = 1;
}
void h_13(double *state, double *unused, double *out_2650730557120445897) {
   out_2650730557120445897[0] = state[3];
   out_2650730557120445897[1] = state[4];
   out_2650730557120445897[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6509145070461241073) {
   out_6509145070461241073[0] = 0;
   out_6509145070461241073[1] = 0;
   out_6509145070461241073[2] = 0;
   out_6509145070461241073[3] = 1;
   out_6509145070461241073[4] = 0;
   out_6509145070461241073[5] = 0;
   out_6509145070461241073[6] = 0;
   out_6509145070461241073[7] = 0;
   out_6509145070461241073[8] = 0;
   out_6509145070461241073[9] = 0;
   out_6509145070461241073[10] = 0;
   out_6509145070461241073[11] = 0;
   out_6509145070461241073[12] = 0;
   out_6509145070461241073[13] = 0;
   out_6509145070461241073[14] = 0;
   out_6509145070461241073[15] = 0;
   out_6509145070461241073[16] = 0;
   out_6509145070461241073[17] = 0;
   out_6509145070461241073[18] = 0;
   out_6509145070461241073[19] = 0;
   out_6509145070461241073[20] = 0;
   out_6509145070461241073[21] = 0;
   out_6509145070461241073[22] = 1;
   out_6509145070461241073[23] = 0;
   out_6509145070461241073[24] = 0;
   out_6509145070461241073[25] = 0;
   out_6509145070461241073[26] = 0;
   out_6509145070461241073[27] = 0;
   out_6509145070461241073[28] = 0;
   out_6509145070461241073[29] = 0;
   out_6509145070461241073[30] = 0;
   out_6509145070461241073[31] = 0;
   out_6509145070461241073[32] = 0;
   out_6509145070461241073[33] = 0;
   out_6509145070461241073[34] = 0;
   out_6509145070461241073[35] = 0;
   out_6509145070461241073[36] = 0;
   out_6509145070461241073[37] = 0;
   out_6509145070461241073[38] = 0;
   out_6509145070461241073[39] = 0;
   out_6509145070461241073[40] = 0;
   out_6509145070461241073[41] = 1;
   out_6509145070461241073[42] = 0;
   out_6509145070461241073[43] = 0;
   out_6509145070461241073[44] = 0;
   out_6509145070461241073[45] = 0;
   out_6509145070461241073[46] = 0;
   out_6509145070461241073[47] = 0;
   out_6509145070461241073[48] = 0;
   out_6509145070461241073[49] = 0;
   out_6509145070461241073[50] = 0;
   out_6509145070461241073[51] = 0;
   out_6509145070461241073[52] = 0;
   out_6509145070461241073[53] = 0;
}
void h_14(double *state, double *unused, double *out_3815293765870846970) {
   out_3815293765870846970[0] = state[6];
   out_3815293765870846970[1] = state[7];
   out_3815293765870846970[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7260112101468392801) {
   out_7260112101468392801[0] = 0;
   out_7260112101468392801[1] = 0;
   out_7260112101468392801[2] = 0;
   out_7260112101468392801[3] = 0;
   out_7260112101468392801[4] = 0;
   out_7260112101468392801[5] = 0;
   out_7260112101468392801[6] = 1;
   out_7260112101468392801[7] = 0;
   out_7260112101468392801[8] = 0;
   out_7260112101468392801[9] = 0;
   out_7260112101468392801[10] = 0;
   out_7260112101468392801[11] = 0;
   out_7260112101468392801[12] = 0;
   out_7260112101468392801[13] = 0;
   out_7260112101468392801[14] = 0;
   out_7260112101468392801[15] = 0;
   out_7260112101468392801[16] = 0;
   out_7260112101468392801[17] = 0;
   out_7260112101468392801[18] = 0;
   out_7260112101468392801[19] = 0;
   out_7260112101468392801[20] = 0;
   out_7260112101468392801[21] = 0;
   out_7260112101468392801[22] = 0;
   out_7260112101468392801[23] = 0;
   out_7260112101468392801[24] = 0;
   out_7260112101468392801[25] = 1;
   out_7260112101468392801[26] = 0;
   out_7260112101468392801[27] = 0;
   out_7260112101468392801[28] = 0;
   out_7260112101468392801[29] = 0;
   out_7260112101468392801[30] = 0;
   out_7260112101468392801[31] = 0;
   out_7260112101468392801[32] = 0;
   out_7260112101468392801[33] = 0;
   out_7260112101468392801[34] = 0;
   out_7260112101468392801[35] = 0;
   out_7260112101468392801[36] = 0;
   out_7260112101468392801[37] = 0;
   out_7260112101468392801[38] = 0;
   out_7260112101468392801[39] = 0;
   out_7260112101468392801[40] = 0;
   out_7260112101468392801[41] = 0;
   out_7260112101468392801[42] = 0;
   out_7260112101468392801[43] = 0;
   out_7260112101468392801[44] = 1;
   out_7260112101468392801[45] = 0;
   out_7260112101468392801[46] = 0;
   out_7260112101468392801[47] = 0;
   out_7260112101468392801[48] = 0;
   out_7260112101468392801[49] = 0;
   out_7260112101468392801[50] = 0;
   out_7260112101468392801[51] = 0;
   out_7260112101468392801[52] = 0;
   out_7260112101468392801[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_9096196563184828167) {
  err_fun(nom_x, delta_x, out_9096196563184828167);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2510715355574267806) {
  inv_err_fun(nom_x, true_x, out_2510715355574267806);
}
void pose_H_mod_fun(double *state, double *out_6571093323919857525) {
  H_mod_fun(state, out_6571093323919857525);
}
void pose_f_fun(double *state, double dt, double *out_8641421515160522541) {
  f_fun(state,  dt, out_8641421515160522541);
}
void pose_F_fun(double *state, double dt, double *out_1965387258042231969) {
  F_fun(state,  dt, out_1965387258042231969);
}
void pose_h_4(double *state, double *unused, double *out_5430219983567452590) {
  h_4(state, unused, out_5430219983567452590);
}
void pose_H_4(double *state, double *unused, double *out_3296871245128908272) {
  H_4(state, unused, out_3296871245128908272);
}
void pose_h_10(double *state, double *unused, double *out_2671944880378075133) {
  h_10(state, unused, out_2671944880378075133);
}
void pose_H_10(double *state, double *unused, double *out_1775443925111280628) {
  H_10(state, unused, out_1775443925111280628);
}
void pose_h_13(double *state, double *unused, double *out_2650730557120445897) {
  h_13(state, unused, out_2650730557120445897);
}
void pose_H_13(double *state, double *unused, double *out_6509145070461241073) {
  H_13(state, unused, out_6509145070461241073);
}
void pose_h_14(double *state, double *unused, double *out_3815293765870846970) {
  h_14(state, unused, out_3815293765870846970);
}
void pose_H_14(double *state, double *unused, double *out_7260112101468392801) {
  H_14(state, unused, out_7260112101468392801);
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
