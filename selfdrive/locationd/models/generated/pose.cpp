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
void err_fun(double *nom_x, double *delta_x, double *out_1889617797433936481) {
   out_1889617797433936481[0] = delta_x[0] + nom_x[0];
   out_1889617797433936481[1] = delta_x[1] + nom_x[1];
   out_1889617797433936481[2] = delta_x[2] + nom_x[2];
   out_1889617797433936481[3] = delta_x[3] + nom_x[3];
   out_1889617797433936481[4] = delta_x[4] + nom_x[4];
   out_1889617797433936481[5] = delta_x[5] + nom_x[5];
   out_1889617797433936481[6] = delta_x[6] + nom_x[6];
   out_1889617797433936481[7] = delta_x[7] + nom_x[7];
   out_1889617797433936481[8] = delta_x[8] + nom_x[8];
   out_1889617797433936481[9] = delta_x[9] + nom_x[9];
   out_1889617797433936481[10] = delta_x[10] + nom_x[10];
   out_1889617797433936481[11] = delta_x[11] + nom_x[11];
   out_1889617797433936481[12] = delta_x[12] + nom_x[12];
   out_1889617797433936481[13] = delta_x[13] + nom_x[13];
   out_1889617797433936481[14] = delta_x[14] + nom_x[14];
   out_1889617797433936481[15] = delta_x[15] + nom_x[15];
   out_1889617797433936481[16] = delta_x[16] + nom_x[16];
   out_1889617797433936481[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1637106724448845216) {
   out_1637106724448845216[0] = -nom_x[0] + true_x[0];
   out_1637106724448845216[1] = -nom_x[1] + true_x[1];
   out_1637106724448845216[2] = -nom_x[2] + true_x[2];
   out_1637106724448845216[3] = -nom_x[3] + true_x[3];
   out_1637106724448845216[4] = -nom_x[4] + true_x[4];
   out_1637106724448845216[5] = -nom_x[5] + true_x[5];
   out_1637106724448845216[6] = -nom_x[6] + true_x[6];
   out_1637106724448845216[7] = -nom_x[7] + true_x[7];
   out_1637106724448845216[8] = -nom_x[8] + true_x[8];
   out_1637106724448845216[9] = -nom_x[9] + true_x[9];
   out_1637106724448845216[10] = -nom_x[10] + true_x[10];
   out_1637106724448845216[11] = -nom_x[11] + true_x[11];
   out_1637106724448845216[12] = -nom_x[12] + true_x[12];
   out_1637106724448845216[13] = -nom_x[13] + true_x[13];
   out_1637106724448845216[14] = -nom_x[14] + true_x[14];
   out_1637106724448845216[15] = -nom_x[15] + true_x[15];
   out_1637106724448845216[16] = -nom_x[16] + true_x[16];
   out_1637106724448845216[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2437699087554365121) {
   out_2437699087554365121[0] = 1.0;
   out_2437699087554365121[1] = 0.0;
   out_2437699087554365121[2] = 0.0;
   out_2437699087554365121[3] = 0.0;
   out_2437699087554365121[4] = 0.0;
   out_2437699087554365121[5] = 0.0;
   out_2437699087554365121[6] = 0.0;
   out_2437699087554365121[7] = 0.0;
   out_2437699087554365121[8] = 0.0;
   out_2437699087554365121[9] = 0.0;
   out_2437699087554365121[10] = 0.0;
   out_2437699087554365121[11] = 0.0;
   out_2437699087554365121[12] = 0.0;
   out_2437699087554365121[13] = 0.0;
   out_2437699087554365121[14] = 0.0;
   out_2437699087554365121[15] = 0.0;
   out_2437699087554365121[16] = 0.0;
   out_2437699087554365121[17] = 0.0;
   out_2437699087554365121[18] = 0.0;
   out_2437699087554365121[19] = 1.0;
   out_2437699087554365121[20] = 0.0;
   out_2437699087554365121[21] = 0.0;
   out_2437699087554365121[22] = 0.0;
   out_2437699087554365121[23] = 0.0;
   out_2437699087554365121[24] = 0.0;
   out_2437699087554365121[25] = 0.0;
   out_2437699087554365121[26] = 0.0;
   out_2437699087554365121[27] = 0.0;
   out_2437699087554365121[28] = 0.0;
   out_2437699087554365121[29] = 0.0;
   out_2437699087554365121[30] = 0.0;
   out_2437699087554365121[31] = 0.0;
   out_2437699087554365121[32] = 0.0;
   out_2437699087554365121[33] = 0.0;
   out_2437699087554365121[34] = 0.0;
   out_2437699087554365121[35] = 0.0;
   out_2437699087554365121[36] = 0.0;
   out_2437699087554365121[37] = 0.0;
   out_2437699087554365121[38] = 1.0;
   out_2437699087554365121[39] = 0.0;
   out_2437699087554365121[40] = 0.0;
   out_2437699087554365121[41] = 0.0;
   out_2437699087554365121[42] = 0.0;
   out_2437699087554365121[43] = 0.0;
   out_2437699087554365121[44] = 0.0;
   out_2437699087554365121[45] = 0.0;
   out_2437699087554365121[46] = 0.0;
   out_2437699087554365121[47] = 0.0;
   out_2437699087554365121[48] = 0.0;
   out_2437699087554365121[49] = 0.0;
   out_2437699087554365121[50] = 0.0;
   out_2437699087554365121[51] = 0.0;
   out_2437699087554365121[52] = 0.0;
   out_2437699087554365121[53] = 0.0;
   out_2437699087554365121[54] = 0.0;
   out_2437699087554365121[55] = 0.0;
   out_2437699087554365121[56] = 0.0;
   out_2437699087554365121[57] = 1.0;
   out_2437699087554365121[58] = 0.0;
   out_2437699087554365121[59] = 0.0;
   out_2437699087554365121[60] = 0.0;
   out_2437699087554365121[61] = 0.0;
   out_2437699087554365121[62] = 0.0;
   out_2437699087554365121[63] = 0.0;
   out_2437699087554365121[64] = 0.0;
   out_2437699087554365121[65] = 0.0;
   out_2437699087554365121[66] = 0.0;
   out_2437699087554365121[67] = 0.0;
   out_2437699087554365121[68] = 0.0;
   out_2437699087554365121[69] = 0.0;
   out_2437699087554365121[70] = 0.0;
   out_2437699087554365121[71] = 0.0;
   out_2437699087554365121[72] = 0.0;
   out_2437699087554365121[73] = 0.0;
   out_2437699087554365121[74] = 0.0;
   out_2437699087554365121[75] = 0.0;
   out_2437699087554365121[76] = 1.0;
   out_2437699087554365121[77] = 0.0;
   out_2437699087554365121[78] = 0.0;
   out_2437699087554365121[79] = 0.0;
   out_2437699087554365121[80] = 0.0;
   out_2437699087554365121[81] = 0.0;
   out_2437699087554365121[82] = 0.0;
   out_2437699087554365121[83] = 0.0;
   out_2437699087554365121[84] = 0.0;
   out_2437699087554365121[85] = 0.0;
   out_2437699087554365121[86] = 0.0;
   out_2437699087554365121[87] = 0.0;
   out_2437699087554365121[88] = 0.0;
   out_2437699087554365121[89] = 0.0;
   out_2437699087554365121[90] = 0.0;
   out_2437699087554365121[91] = 0.0;
   out_2437699087554365121[92] = 0.0;
   out_2437699087554365121[93] = 0.0;
   out_2437699087554365121[94] = 0.0;
   out_2437699087554365121[95] = 1.0;
   out_2437699087554365121[96] = 0.0;
   out_2437699087554365121[97] = 0.0;
   out_2437699087554365121[98] = 0.0;
   out_2437699087554365121[99] = 0.0;
   out_2437699087554365121[100] = 0.0;
   out_2437699087554365121[101] = 0.0;
   out_2437699087554365121[102] = 0.0;
   out_2437699087554365121[103] = 0.0;
   out_2437699087554365121[104] = 0.0;
   out_2437699087554365121[105] = 0.0;
   out_2437699087554365121[106] = 0.0;
   out_2437699087554365121[107] = 0.0;
   out_2437699087554365121[108] = 0.0;
   out_2437699087554365121[109] = 0.0;
   out_2437699087554365121[110] = 0.0;
   out_2437699087554365121[111] = 0.0;
   out_2437699087554365121[112] = 0.0;
   out_2437699087554365121[113] = 0.0;
   out_2437699087554365121[114] = 1.0;
   out_2437699087554365121[115] = 0.0;
   out_2437699087554365121[116] = 0.0;
   out_2437699087554365121[117] = 0.0;
   out_2437699087554365121[118] = 0.0;
   out_2437699087554365121[119] = 0.0;
   out_2437699087554365121[120] = 0.0;
   out_2437699087554365121[121] = 0.0;
   out_2437699087554365121[122] = 0.0;
   out_2437699087554365121[123] = 0.0;
   out_2437699087554365121[124] = 0.0;
   out_2437699087554365121[125] = 0.0;
   out_2437699087554365121[126] = 0.0;
   out_2437699087554365121[127] = 0.0;
   out_2437699087554365121[128] = 0.0;
   out_2437699087554365121[129] = 0.0;
   out_2437699087554365121[130] = 0.0;
   out_2437699087554365121[131] = 0.0;
   out_2437699087554365121[132] = 0.0;
   out_2437699087554365121[133] = 1.0;
   out_2437699087554365121[134] = 0.0;
   out_2437699087554365121[135] = 0.0;
   out_2437699087554365121[136] = 0.0;
   out_2437699087554365121[137] = 0.0;
   out_2437699087554365121[138] = 0.0;
   out_2437699087554365121[139] = 0.0;
   out_2437699087554365121[140] = 0.0;
   out_2437699087554365121[141] = 0.0;
   out_2437699087554365121[142] = 0.0;
   out_2437699087554365121[143] = 0.0;
   out_2437699087554365121[144] = 0.0;
   out_2437699087554365121[145] = 0.0;
   out_2437699087554365121[146] = 0.0;
   out_2437699087554365121[147] = 0.0;
   out_2437699087554365121[148] = 0.0;
   out_2437699087554365121[149] = 0.0;
   out_2437699087554365121[150] = 0.0;
   out_2437699087554365121[151] = 0.0;
   out_2437699087554365121[152] = 1.0;
   out_2437699087554365121[153] = 0.0;
   out_2437699087554365121[154] = 0.0;
   out_2437699087554365121[155] = 0.0;
   out_2437699087554365121[156] = 0.0;
   out_2437699087554365121[157] = 0.0;
   out_2437699087554365121[158] = 0.0;
   out_2437699087554365121[159] = 0.0;
   out_2437699087554365121[160] = 0.0;
   out_2437699087554365121[161] = 0.0;
   out_2437699087554365121[162] = 0.0;
   out_2437699087554365121[163] = 0.0;
   out_2437699087554365121[164] = 0.0;
   out_2437699087554365121[165] = 0.0;
   out_2437699087554365121[166] = 0.0;
   out_2437699087554365121[167] = 0.0;
   out_2437699087554365121[168] = 0.0;
   out_2437699087554365121[169] = 0.0;
   out_2437699087554365121[170] = 0.0;
   out_2437699087554365121[171] = 1.0;
   out_2437699087554365121[172] = 0.0;
   out_2437699087554365121[173] = 0.0;
   out_2437699087554365121[174] = 0.0;
   out_2437699087554365121[175] = 0.0;
   out_2437699087554365121[176] = 0.0;
   out_2437699087554365121[177] = 0.0;
   out_2437699087554365121[178] = 0.0;
   out_2437699087554365121[179] = 0.0;
   out_2437699087554365121[180] = 0.0;
   out_2437699087554365121[181] = 0.0;
   out_2437699087554365121[182] = 0.0;
   out_2437699087554365121[183] = 0.0;
   out_2437699087554365121[184] = 0.0;
   out_2437699087554365121[185] = 0.0;
   out_2437699087554365121[186] = 0.0;
   out_2437699087554365121[187] = 0.0;
   out_2437699087554365121[188] = 0.0;
   out_2437699087554365121[189] = 0.0;
   out_2437699087554365121[190] = 1.0;
   out_2437699087554365121[191] = 0.0;
   out_2437699087554365121[192] = 0.0;
   out_2437699087554365121[193] = 0.0;
   out_2437699087554365121[194] = 0.0;
   out_2437699087554365121[195] = 0.0;
   out_2437699087554365121[196] = 0.0;
   out_2437699087554365121[197] = 0.0;
   out_2437699087554365121[198] = 0.0;
   out_2437699087554365121[199] = 0.0;
   out_2437699087554365121[200] = 0.0;
   out_2437699087554365121[201] = 0.0;
   out_2437699087554365121[202] = 0.0;
   out_2437699087554365121[203] = 0.0;
   out_2437699087554365121[204] = 0.0;
   out_2437699087554365121[205] = 0.0;
   out_2437699087554365121[206] = 0.0;
   out_2437699087554365121[207] = 0.0;
   out_2437699087554365121[208] = 0.0;
   out_2437699087554365121[209] = 1.0;
   out_2437699087554365121[210] = 0.0;
   out_2437699087554365121[211] = 0.0;
   out_2437699087554365121[212] = 0.0;
   out_2437699087554365121[213] = 0.0;
   out_2437699087554365121[214] = 0.0;
   out_2437699087554365121[215] = 0.0;
   out_2437699087554365121[216] = 0.0;
   out_2437699087554365121[217] = 0.0;
   out_2437699087554365121[218] = 0.0;
   out_2437699087554365121[219] = 0.0;
   out_2437699087554365121[220] = 0.0;
   out_2437699087554365121[221] = 0.0;
   out_2437699087554365121[222] = 0.0;
   out_2437699087554365121[223] = 0.0;
   out_2437699087554365121[224] = 0.0;
   out_2437699087554365121[225] = 0.0;
   out_2437699087554365121[226] = 0.0;
   out_2437699087554365121[227] = 0.0;
   out_2437699087554365121[228] = 1.0;
   out_2437699087554365121[229] = 0.0;
   out_2437699087554365121[230] = 0.0;
   out_2437699087554365121[231] = 0.0;
   out_2437699087554365121[232] = 0.0;
   out_2437699087554365121[233] = 0.0;
   out_2437699087554365121[234] = 0.0;
   out_2437699087554365121[235] = 0.0;
   out_2437699087554365121[236] = 0.0;
   out_2437699087554365121[237] = 0.0;
   out_2437699087554365121[238] = 0.0;
   out_2437699087554365121[239] = 0.0;
   out_2437699087554365121[240] = 0.0;
   out_2437699087554365121[241] = 0.0;
   out_2437699087554365121[242] = 0.0;
   out_2437699087554365121[243] = 0.0;
   out_2437699087554365121[244] = 0.0;
   out_2437699087554365121[245] = 0.0;
   out_2437699087554365121[246] = 0.0;
   out_2437699087554365121[247] = 1.0;
   out_2437699087554365121[248] = 0.0;
   out_2437699087554365121[249] = 0.0;
   out_2437699087554365121[250] = 0.0;
   out_2437699087554365121[251] = 0.0;
   out_2437699087554365121[252] = 0.0;
   out_2437699087554365121[253] = 0.0;
   out_2437699087554365121[254] = 0.0;
   out_2437699087554365121[255] = 0.0;
   out_2437699087554365121[256] = 0.0;
   out_2437699087554365121[257] = 0.0;
   out_2437699087554365121[258] = 0.0;
   out_2437699087554365121[259] = 0.0;
   out_2437699087554365121[260] = 0.0;
   out_2437699087554365121[261] = 0.0;
   out_2437699087554365121[262] = 0.0;
   out_2437699087554365121[263] = 0.0;
   out_2437699087554365121[264] = 0.0;
   out_2437699087554365121[265] = 0.0;
   out_2437699087554365121[266] = 1.0;
   out_2437699087554365121[267] = 0.0;
   out_2437699087554365121[268] = 0.0;
   out_2437699087554365121[269] = 0.0;
   out_2437699087554365121[270] = 0.0;
   out_2437699087554365121[271] = 0.0;
   out_2437699087554365121[272] = 0.0;
   out_2437699087554365121[273] = 0.0;
   out_2437699087554365121[274] = 0.0;
   out_2437699087554365121[275] = 0.0;
   out_2437699087554365121[276] = 0.0;
   out_2437699087554365121[277] = 0.0;
   out_2437699087554365121[278] = 0.0;
   out_2437699087554365121[279] = 0.0;
   out_2437699087554365121[280] = 0.0;
   out_2437699087554365121[281] = 0.0;
   out_2437699087554365121[282] = 0.0;
   out_2437699087554365121[283] = 0.0;
   out_2437699087554365121[284] = 0.0;
   out_2437699087554365121[285] = 1.0;
   out_2437699087554365121[286] = 0.0;
   out_2437699087554365121[287] = 0.0;
   out_2437699087554365121[288] = 0.0;
   out_2437699087554365121[289] = 0.0;
   out_2437699087554365121[290] = 0.0;
   out_2437699087554365121[291] = 0.0;
   out_2437699087554365121[292] = 0.0;
   out_2437699087554365121[293] = 0.0;
   out_2437699087554365121[294] = 0.0;
   out_2437699087554365121[295] = 0.0;
   out_2437699087554365121[296] = 0.0;
   out_2437699087554365121[297] = 0.0;
   out_2437699087554365121[298] = 0.0;
   out_2437699087554365121[299] = 0.0;
   out_2437699087554365121[300] = 0.0;
   out_2437699087554365121[301] = 0.0;
   out_2437699087554365121[302] = 0.0;
   out_2437699087554365121[303] = 0.0;
   out_2437699087554365121[304] = 1.0;
   out_2437699087554365121[305] = 0.0;
   out_2437699087554365121[306] = 0.0;
   out_2437699087554365121[307] = 0.0;
   out_2437699087554365121[308] = 0.0;
   out_2437699087554365121[309] = 0.0;
   out_2437699087554365121[310] = 0.0;
   out_2437699087554365121[311] = 0.0;
   out_2437699087554365121[312] = 0.0;
   out_2437699087554365121[313] = 0.0;
   out_2437699087554365121[314] = 0.0;
   out_2437699087554365121[315] = 0.0;
   out_2437699087554365121[316] = 0.0;
   out_2437699087554365121[317] = 0.0;
   out_2437699087554365121[318] = 0.0;
   out_2437699087554365121[319] = 0.0;
   out_2437699087554365121[320] = 0.0;
   out_2437699087554365121[321] = 0.0;
   out_2437699087554365121[322] = 0.0;
   out_2437699087554365121[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1371391185453368685) {
   out_1371391185453368685[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1371391185453368685[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1371391185453368685[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1371391185453368685[3] = dt*state[12] + state[3];
   out_1371391185453368685[4] = dt*state[13] + state[4];
   out_1371391185453368685[5] = dt*state[14] + state[5];
   out_1371391185453368685[6] = state[6];
   out_1371391185453368685[7] = state[7];
   out_1371391185453368685[8] = state[8];
   out_1371391185453368685[9] = state[9];
   out_1371391185453368685[10] = state[10];
   out_1371391185453368685[11] = state[11];
   out_1371391185453368685[12] = state[12];
   out_1371391185453368685[13] = state[13];
   out_1371391185453368685[14] = state[14];
   out_1371391185453368685[15] = state[15];
   out_1371391185453368685[16] = state[16];
   out_1371391185453368685[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6008208831774812485) {
   out_6008208831774812485[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6008208831774812485[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6008208831774812485[2] = 0;
   out_6008208831774812485[3] = 0;
   out_6008208831774812485[4] = 0;
   out_6008208831774812485[5] = 0;
   out_6008208831774812485[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6008208831774812485[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6008208831774812485[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6008208831774812485[9] = 0;
   out_6008208831774812485[10] = 0;
   out_6008208831774812485[11] = 0;
   out_6008208831774812485[12] = 0;
   out_6008208831774812485[13] = 0;
   out_6008208831774812485[14] = 0;
   out_6008208831774812485[15] = 0;
   out_6008208831774812485[16] = 0;
   out_6008208831774812485[17] = 0;
   out_6008208831774812485[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6008208831774812485[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6008208831774812485[20] = 0;
   out_6008208831774812485[21] = 0;
   out_6008208831774812485[22] = 0;
   out_6008208831774812485[23] = 0;
   out_6008208831774812485[24] = 0;
   out_6008208831774812485[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6008208831774812485[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6008208831774812485[27] = 0;
   out_6008208831774812485[28] = 0;
   out_6008208831774812485[29] = 0;
   out_6008208831774812485[30] = 0;
   out_6008208831774812485[31] = 0;
   out_6008208831774812485[32] = 0;
   out_6008208831774812485[33] = 0;
   out_6008208831774812485[34] = 0;
   out_6008208831774812485[35] = 0;
   out_6008208831774812485[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6008208831774812485[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6008208831774812485[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6008208831774812485[39] = 0;
   out_6008208831774812485[40] = 0;
   out_6008208831774812485[41] = 0;
   out_6008208831774812485[42] = 0;
   out_6008208831774812485[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6008208831774812485[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6008208831774812485[45] = 0;
   out_6008208831774812485[46] = 0;
   out_6008208831774812485[47] = 0;
   out_6008208831774812485[48] = 0;
   out_6008208831774812485[49] = 0;
   out_6008208831774812485[50] = 0;
   out_6008208831774812485[51] = 0;
   out_6008208831774812485[52] = 0;
   out_6008208831774812485[53] = 0;
   out_6008208831774812485[54] = 0;
   out_6008208831774812485[55] = 0;
   out_6008208831774812485[56] = 0;
   out_6008208831774812485[57] = 1;
   out_6008208831774812485[58] = 0;
   out_6008208831774812485[59] = 0;
   out_6008208831774812485[60] = 0;
   out_6008208831774812485[61] = 0;
   out_6008208831774812485[62] = 0;
   out_6008208831774812485[63] = 0;
   out_6008208831774812485[64] = 0;
   out_6008208831774812485[65] = 0;
   out_6008208831774812485[66] = dt;
   out_6008208831774812485[67] = 0;
   out_6008208831774812485[68] = 0;
   out_6008208831774812485[69] = 0;
   out_6008208831774812485[70] = 0;
   out_6008208831774812485[71] = 0;
   out_6008208831774812485[72] = 0;
   out_6008208831774812485[73] = 0;
   out_6008208831774812485[74] = 0;
   out_6008208831774812485[75] = 0;
   out_6008208831774812485[76] = 1;
   out_6008208831774812485[77] = 0;
   out_6008208831774812485[78] = 0;
   out_6008208831774812485[79] = 0;
   out_6008208831774812485[80] = 0;
   out_6008208831774812485[81] = 0;
   out_6008208831774812485[82] = 0;
   out_6008208831774812485[83] = 0;
   out_6008208831774812485[84] = 0;
   out_6008208831774812485[85] = dt;
   out_6008208831774812485[86] = 0;
   out_6008208831774812485[87] = 0;
   out_6008208831774812485[88] = 0;
   out_6008208831774812485[89] = 0;
   out_6008208831774812485[90] = 0;
   out_6008208831774812485[91] = 0;
   out_6008208831774812485[92] = 0;
   out_6008208831774812485[93] = 0;
   out_6008208831774812485[94] = 0;
   out_6008208831774812485[95] = 1;
   out_6008208831774812485[96] = 0;
   out_6008208831774812485[97] = 0;
   out_6008208831774812485[98] = 0;
   out_6008208831774812485[99] = 0;
   out_6008208831774812485[100] = 0;
   out_6008208831774812485[101] = 0;
   out_6008208831774812485[102] = 0;
   out_6008208831774812485[103] = 0;
   out_6008208831774812485[104] = dt;
   out_6008208831774812485[105] = 0;
   out_6008208831774812485[106] = 0;
   out_6008208831774812485[107] = 0;
   out_6008208831774812485[108] = 0;
   out_6008208831774812485[109] = 0;
   out_6008208831774812485[110] = 0;
   out_6008208831774812485[111] = 0;
   out_6008208831774812485[112] = 0;
   out_6008208831774812485[113] = 0;
   out_6008208831774812485[114] = 1;
   out_6008208831774812485[115] = 0;
   out_6008208831774812485[116] = 0;
   out_6008208831774812485[117] = 0;
   out_6008208831774812485[118] = 0;
   out_6008208831774812485[119] = 0;
   out_6008208831774812485[120] = 0;
   out_6008208831774812485[121] = 0;
   out_6008208831774812485[122] = 0;
   out_6008208831774812485[123] = 0;
   out_6008208831774812485[124] = 0;
   out_6008208831774812485[125] = 0;
   out_6008208831774812485[126] = 0;
   out_6008208831774812485[127] = 0;
   out_6008208831774812485[128] = 0;
   out_6008208831774812485[129] = 0;
   out_6008208831774812485[130] = 0;
   out_6008208831774812485[131] = 0;
   out_6008208831774812485[132] = 0;
   out_6008208831774812485[133] = 1;
   out_6008208831774812485[134] = 0;
   out_6008208831774812485[135] = 0;
   out_6008208831774812485[136] = 0;
   out_6008208831774812485[137] = 0;
   out_6008208831774812485[138] = 0;
   out_6008208831774812485[139] = 0;
   out_6008208831774812485[140] = 0;
   out_6008208831774812485[141] = 0;
   out_6008208831774812485[142] = 0;
   out_6008208831774812485[143] = 0;
   out_6008208831774812485[144] = 0;
   out_6008208831774812485[145] = 0;
   out_6008208831774812485[146] = 0;
   out_6008208831774812485[147] = 0;
   out_6008208831774812485[148] = 0;
   out_6008208831774812485[149] = 0;
   out_6008208831774812485[150] = 0;
   out_6008208831774812485[151] = 0;
   out_6008208831774812485[152] = 1;
   out_6008208831774812485[153] = 0;
   out_6008208831774812485[154] = 0;
   out_6008208831774812485[155] = 0;
   out_6008208831774812485[156] = 0;
   out_6008208831774812485[157] = 0;
   out_6008208831774812485[158] = 0;
   out_6008208831774812485[159] = 0;
   out_6008208831774812485[160] = 0;
   out_6008208831774812485[161] = 0;
   out_6008208831774812485[162] = 0;
   out_6008208831774812485[163] = 0;
   out_6008208831774812485[164] = 0;
   out_6008208831774812485[165] = 0;
   out_6008208831774812485[166] = 0;
   out_6008208831774812485[167] = 0;
   out_6008208831774812485[168] = 0;
   out_6008208831774812485[169] = 0;
   out_6008208831774812485[170] = 0;
   out_6008208831774812485[171] = 1;
   out_6008208831774812485[172] = 0;
   out_6008208831774812485[173] = 0;
   out_6008208831774812485[174] = 0;
   out_6008208831774812485[175] = 0;
   out_6008208831774812485[176] = 0;
   out_6008208831774812485[177] = 0;
   out_6008208831774812485[178] = 0;
   out_6008208831774812485[179] = 0;
   out_6008208831774812485[180] = 0;
   out_6008208831774812485[181] = 0;
   out_6008208831774812485[182] = 0;
   out_6008208831774812485[183] = 0;
   out_6008208831774812485[184] = 0;
   out_6008208831774812485[185] = 0;
   out_6008208831774812485[186] = 0;
   out_6008208831774812485[187] = 0;
   out_6008208831774812485[188] = 0;
   out_6008208831774812485[189] = 0;
   out_6008208831774812485[190] = 1;
   out_6008208831774812485[191] = 0;
   out_6008208831774812485[192] = 0;
   out_6008208831774812485[193] = 0;
   out_6008208831774812485[194] = 0;
   out_6008208831774812485[195] = 0;
   out_6008208831774812485[196] = 0;
   out_6008208831774812485[197] = 0;
   out_6008208831774812485[198] = 0;
   out_6008208831774812485[199] = 0;
   out_6008208831774812485[200] = 0;
   out_6008208831774812485[201] = 0;
   out_6008208831774812485[202] = 0;
   out_6008208831774812485[203] = 0;
   out_6008208831774812485[204] = 0;
   out_6008208831774812485[205] = 0;
   out_6008208831774812485[206] = 0;
   out_6008208831774812485[207] = 0;
   out_6008208831774812485[208] = 0;
   out_6008208831774812485[209] = 1;
   out_6008208831774812485[210] = 0;
   out_6008208831774812485[211] = 0;
   out_6008208831774812485[212] = 0;
   out_6008208831774812485[213] = 0;
   out_6008208831774812485[214] = 0;
   out_6008208831774812485[215] = 0;
   out_6008208831774812485[216] = 0;
   out_6008208831774812485[217] = 0;
   out_6008208831774812485[218] = 0;
   out_6008208831774812485[219] = 0;
   out_6008208831774812485[220] = 0;
   out_6008208831774812485[221] = 0;
   out_6008208831774812485[222] = 0;
   out_6008208831774812485[223] = 0;
   out_6008208831774812485[224] = 0;
   out_6008208831774812485[225] = 0;
   out_6008208831774812485[226] = 0;
   out_6008208831774812485[227] = 0;
   out_6008208831774812485[228] = 1;
   out_6008208831774812485[229] = 0;
   out_6008208831774812485[230] = 0;
   out_6008208831774812485[231] = 0;
   out_6008208831774812485[232] = 0;
   out_6008208831774812485[233] = 0;
   out_6008208831774812485[234] = 0;
   out_6008208831774812485[235] = 0;
   out_6008208831774812485[236] = 0;
   out_6008208831774812485[237] = 0;
   out_6008208831774812485[238] = 0;
   out_6008208831774812485[239] = 0;
   out_6008208831774812485[240] = 0;
   out_6008208831774812485[241] = 0;
   out_6008208831774812485[242] = 0;
   out_6008208831774812485[243] = 0;
   out_6008208831774812485[244] = 0;
   out_6008208831774812485[245] = 0;
   out_6008208831774812485[246] = 0;
   out_6008208831774812485[247] = 1;
   out_6008208831774812485[248] = 0;
   out_6008208831774812485[249] = 0;
   out_6008208831774812485[250] = 0;
   out_6008208831774812485[251] = 0;
   out_6008208831774812485[252] = 0;
   out_6008208831774812485[253] = 0;
   out_6008208831774812485[254] = 0;
   out_6008208831774812485[255] = 0;
   out_6008208831774812485[256] = 0;
   out_6008208831774812485[257] = 0;
   out_6008208831774812485[258] = 0;
   out_6008208831774812485[259] = 0;
   out_6008208831774812485[260] = 0;
   out_6008208831774812485[261] = 0;
   out_6008208831774812485[262] = 0;
   out_6008208831774812485[263] = 0;
   out_6008208831774812485[264] = 0;
   out_6008208831774812485[265] = 0;
   out_6008208831774812485[266] = 1;
   out_6008208831774812485[267] = 0;
   out_6008208831774812485[268] = 0;
   out_6008208831774812485[269] = 0;
   out_6008208831774812485[270] = 0;
   out_6008208831774812485[271] = 0;
   out_6008208831774812485[272] = 0;
   out_6008208831774812485[273] = 0;
   out_6008208831774812485[274] = 0;
   out_6008208831774812485[275] = 0;
   out_6008208831774812485[276] = 0;
   out_6008208831774812485[277] = 0;
   out_6008208831774812485[278] = 0;
   out_6008208831774812485[279] = 0;
   out_6008208831774812485[280] = 0;
   out_6008208831774812485[281] = 0;
   out_6008208831774812485[282] = 0;
   out_6008208831774812485[283] = 0;
   out_6008208831774812485[284] = 0;
   out_6008208831774812485[285] = 1;
   out_6008208831774812485[286] = 0;
   out_6008208831774812485[287] = 0;
   out_6008208831774812485[288] = 0;
   out_6008208831774812485[289] = 0;
   out_6008208831774812485[290] = 0;
   out_6008208831774812485[291] = 0;
   out_6008208831774812485[292] = 0;
   out_6008208831774812485[293] = 0;
   out_6008208831774812485[294] = 0;
   out_6008208831774812485[295] = 0;
   out_6008208831774812485[296] = 0;
   out_6008208831774812485[297] = 0;
   out_6008208831774812485[298] = 0;
   out_6008208831774812485[299] = 0;
   out_6008208831774812485[300] = 0;
   out_6008208831774812485[301] = 0;
   out_6008208831774812485[302] = 0;
   out_6008208831774812485[303] = 0;
   out_6008208831774812485[304] = 1;
   out_6008208831774812485[305] = 0;
   out_6008208831774812485[306] = 0;
   out_6008208831774812485[307] = 0;
   out_6008208831774812485[308] = 0;
   out_6008208831774812485[309] = 0;
   out_6008208831774812485[310] = 0;
   out_6008208831774812485[311] = 0;
   out_6008208831774812485[312] = 0;
   out_6008208831774812485[313] = 0;
   out_6008208831774812485[314] = 0;
   out_6008208831774812485[315] = 0;
   out_6008208831774812485[316] = 0;
   out_6008208831774812485[317] = 0;
   out_6008208831774812485[318] = 0;
   out_6008208831774812485[319] = 0;
   out_6008208831774812485[320] = 0;
   out_6008208831774812485[321] = 0;
   out_6008208831774812485[322] = 0;
   out_6008208831774812485[323] = 1;
}
void h_4(double *state, double *unused, double *out_3596727777192918612) {
   out_3596727777192918612[0] = state[6] + state[9];
   out_3596727777192918612[1] = state[7] + state[10];
   out_3596727777192918612[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_762710813547104903) {
   out_762710813547104903[0] = 0;
   out_762710813547104903[1] = 0;
   out_762710813547104903[2] = 0;
   out_762710813547104903[3] = 0;
   out_762710813547104903[4] = 0;
   out_762710813547104903[5] = 0;
   out_762710813547104903[6] = 1;
   out_762710813547104903[7] = 0;
   out_762710813547104903[8] = 0;
   out_762710813547104903[9] = 1;
   out_762710813547104903[10] = 0;
   out_762710813547104903[11] = 0;
   out_762710813547104903[12] = 0;
   out_762710813547104903[13] = 0;
   out_762710813547104903[14] = 0;
   out_762710813547104903[15] = 0;
   out_762710813547104903[16] = 0;
   out_762710813547104903[17] = 0;
   out_762710813547104903[18] = 0;
   out_762710813547104903[19] = 0;
   out_762710813547104903[20] = 0;
   out_762710813547104903[21] = 0;
   out_762710813547104903[22] = 0;
   out_762710813547104903[23] = 0;
   out_762710813547104903[24] = 0;
   out_762710813547104903[25] = 1;
   out_762710813547104903[26] = 0;
   out_762710813547104903[27] = 0;
   out_762710813547104903[28] = 1;
   out_762710813547104903[29] = 0;
   out_762710813547104903[30] = 0;
   out_762710813547104903[31] = 0;
   out_762710813547104903[32] = 0;
   out_762710813547104903[33] = 0;
   out_762710813547104903[34] = 0;
   out_762710813547104903[35] = 0;
   out_762710813547104903[36] = 0;
   out_762710813547104903[37] = 0;
   out_762710813547104903[38] = 0;
   out_762710813547104903[39] = 0;
   out_762710813547104903[40] = 0;
   out_762710813547104903[41] = 0;
   out_762710813547104903[42] = 0;
   out_762710813547104903[43] = 0;
   out_762710813547104903[44] = 1;
   out_762710813547104903[45] = 0;
   out_762710813547104903[46] = 0;
   out_762710813547104903[47] = 1;
   out_762710813547104903[48] = 0;
   out_762710813547104903[49] = 0;
   out_762710813547104903[50] = 0;
   out_762710813547104903[51] = 0;
   out_762710813547104903[52] = 0;
   out_762710813547104903[53] = 0;
}
void h_10(double *state, double *unused, double *out_3709524755717009150) {
   out_3709524755717009150[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3709524755717009150[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3709524755717009150[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3076932292756208908) {
   out_3076932292756208908[0] = 0;
   out_3076932292756208908[1] = 9.8100000000000005*cos(state[1]);
   out_3076932292756208908[2] = 0;
   out_3076932292756208908[3] = 0;
   out_3076932292756208908[4] = -state[8];
   out_3076932292756208908[5] = state[7];
   out_3076932292756208908[6] = 0;
   out_3076932292756208908[7] = state[5];
   out_3076932292756208908[8] = -state[4];
   out_3076932292756208908[9] = 0;
   out_3076932292756208908[10] = 0;
   out_3076932292756208908[11] = 0;
   out_3076932292756208908[12] = 1;
   out_3076932292756208908[13] = 0;
   out_3076932292756208908[14] = 0;
   out_3076932292756208908[15] = 1;
   out_3076932292756208908[16] = 0;
   out_3076932292756208908[17] = 0;
   out_3076932292756208908[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3076932292756208908[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3076932292756208908[20] = 0;
   out_3076932292756208908[21] = state[8];
   out_3076932292756208908[22] = 0;
   out_3076932292756208908[23] = -state[6];
   out_3076932292756208908[24] = -state[5];
   out_3076932292756208908[25] = 0;
   out_3076932292756208908[26] = state[3];
   out_3076932292756208908[27] = 0;
   out_3076932292756208908[28] = 0;
   out_3076932292756208908[29] = 0;
   out_3076932292756208908[30] = 0;
   out_3076932292756208908[31] = 1;
   out_3076932292756208908[32] = 0;
   out_3076932292756208908[33] = 0;
   out_3076932292756208908[34] = 1;
   out_3076932292756208908[35] = 0;
   out_3076932292756208908[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3076932292756208908[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3076932292756208908[38] = 0;
   out_3076932292756208908[39] = -state[7];
   out_3076932292756208908[40] = state[6];
   out_3076932292756208908[41] = 0;
   out_3076932292756208908[42] = state[4];
   out_3076932292756208908[43] = -state[3];
   out_3076932292756208908[44] = 0;
   out_3076932292756208908[45] = 0;
   out_3076932292756208908[46] = 0;
   out_3076932292756208908[47] = 0;
   out_3076932292756208908[48] = 0;
   out_3076932292756208908[49] = 0;
   out_3076932292756208908[50] = 1;
   out_3076932292756208908[51] = 0;
   out_3076932292756208908[52] = 0;
   out_3076932292756208908[53] = 1;
}
void h_13(double *state, double *unused, double *out_4362699440761336099) {
   out_4362699440761336099[0] = state[3];
   out_4362699440761336099[1] = state[4];
   out_4362699440761336099[2] = state[5];
}
void H_13(double *state, double *unused, double *out_198108893865260799) {
   out_198108893865260799[0] = 0;
   out_198108893865260799[1] = 0;
   out_198108893865260799[2] = 0;
   out_198108893865260799[3] = 1;
   out_198108893865260799[4] = 0;
   out_198108893865260799[5] = 0;
   out_198108893865260799[6] = 0;
   out_198108893865260799[7] = 0;
   out_198108893865260799[8] = 0;
   out_198108893865260799[9] = 0;
   out_198108893865260799[10] = 0;
   out_198108893865260799[11] = 0;
   out_198108893865260799[12] = 0;
   out_198108893865260799[13] = 0;
   out_198108893865260799[14] = 0;
   out_198108893865260799[15] = 0;
   out_198108893865260799[16] = 0;
   out_198108893865260799[17] = 0;
   out_198108893865260799[18] = 0;
   out_198108893865260799[19] = 0;
   out_198108893865260799[20] = 0;
   out_198108893865260799[21] = 0;
   out_198108893865260799[22] = 1;
   out_198108893865260799[23] = 0;
   out_198108893865260799[24] = 0;
   out_198108893865260799[25] = 0;
   out_198108893865260799[26] = 0;
   out_198108893865260799[27] = 0;
   out_198108893865260799[28] = 0;
   out_198108893865260799[29] = 0;
   out_198108893865260799[30] = 0;
   out_198108893865260799[31] = 0;
   out_198108893865260799[32] = 0;
   out_198108893865260799[33] = 0;
   out_198108893865260799[34] = 0;
   out_198108893865260799[35] = 0;
   out_198108893865260799[36] = 0;
   out_198108893865260799[37] = 0;
   out_198108893865260799[38] = 0;
   out_198108893865260799[39] = 0;
   out_198108893865260799[40] = 0;
   out_198108893865260799[41] = 1;
   out_198108893865260799[42] = 0;
   out_198108893865260799[43] = 0;
   out_198108893865260799[44] = 0;
   out_198108893865260799[45] = 0;
   out_198108893865260799[46] = 0;
   out_198108893865260799[47] = 0;
   out_198108893865260799[48] = 0;
   out_198108893865260799[49] = 0;
   out_198108893865260799[50] = 0;
   out_198108893865260799[51] = 0;
   out_198108893865260799[52] = 0;
   out_198108893865260799[53] = 0;
}
void h_14(double *state, double *unused, double *out_7721317524785797518) {
   out_7721317524785797518[0] = state[6];
   out_7721317524785797518[1] = state[7];
   out_7721317524785797518[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3845499245842477199) {
   out_3845499245842477199[0] = 0;
   out_3845499245842477199[1] = 0;
   out_3845499245842477199[2] = 0;
   out_3845499245842477199[3] = 0;
   out_3845499245842477199[4] = 0;
   out_3845499245842477199[5] = 0;
   out_3845499245842477199[6] = 1;
   out_3845499245842477199[7] = 0;
   out_3845499245842477199[8] = 0;
   out_3845499245842477199[9] = 0;
   out_3845499245842477199[10] = 0;
   out_3845499245842477199[11] = 0;
   out_3845499245842477199[12] = 0;
   out_3845499245842477199[13] = 0;
   out_3845499245842477199[14] = 0;
   out_3845499245842477199[15] = 0;
   out_3845499245842477199[16] = 0;
   out_3845499245842477199[17] = 0;
   out_3845499245842477199[18] = 0;
   out_3845499245842477199[19] = 0;
   out_3845499245842477199[20] = 0;
   out_3845499245842477199[21] = 0;
   out_3845499245842477199[22] = 0;
   out_3845499245842477199[23] = 0;
   out_3845499245842477199[24] = 0;
   out_3845499245842477199[25] = 1;
   out_3845499245842477199[26] = 0;
   out_3845499245842477199[27] = 0;
   out_3845499245842477199[28] = 0;
   out_3845499245842477199[29] = 0;
   out_3845499245842477199[30] = 0;
   out_3845499245842477199[31] = 0;
   out_3845499245842477199[32] = 0;
   out_3845499245842477199[33] = 0;
   out_3845499245842477199[34] = 0;
   out_3845499245842477199[35] = 0;
   out_3845499245842477199[36] = 0;
   out_3845499245842477199[37] = 0;
   out_3845499245842477199[38] = 0;
   out_3845499245842477199[39] = 0;
   out_3845499245842477199[40] = 0;
   out_3845499245842477199[41] = 0;
   out_3845499245842477199[42] = 0;
   out_3845499245842477199[43] = 0;
   out_3845499245842477199[44] = 1;
   out_3845499245842477199[45] = 0;
   out_3845499245842477199[46] = 0;
   out_3845499245842477199[47] = 0;
   out_3845499245842477199[48] = 0;
   out_3845499245842477199[49] = 0;
   out_3845499245842477199[50] = 0;
   out_3845499245842477199[51] = 0;
   out_3845499245842477199[52] = 0;
   out_3845499245842477199[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1889617797433936481) {
  err_fun(nom_x, delta_x, out_1889617797433936481);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1637106724448845216) {
  inv_err_fun(nom_x, true_x, out_1637106724448845216);
}
void pose_H_mod_fun(double *state, double *out_2437699087554365121) {
  H_mod_fun(state, out_2437699087554365121);
}
void pose_f_fun(double *state, double dt, double *out_1371391185453368685) {
  f_fun(state,  dt, out_1371391185453368685);
}
void pose_F_fun(double *state, double dt, double *out_6008208831774812485) {
  F_fun(state,  dt, out_6008208831774812485);
}
void pose_h_4(double *state, double *unused, double *out_3596727777192918612) {
  h_4(state, unused, out_3596727777192918612);
}
void pose_H_4(double *state, double *unused, double *out_762710813547104903) {
  H_4(state, unused, out_762710813547104903);
}
void pose_h_10(double *state, double *unused, double *out_3709524755717009150) {
  h_10(state, unused, out_3709524755717009150);
}
void pose_H_10(double *state, double *unused, double *out_3076932292756208908) {
  H_10(state, unused, out_3076932292756208908);
}
void pose_h_13(double *state, double *unused, double *out_4362699440761336099) {
  h_13(state, unused, out_4362699440761336099);
}
void pose_H_13(double *state, double *unused, double *out_198108893865260799) {
  H_13(state, unused, out_198108893865260799);
}
void pose_h_14(double *state, double *unused, double *out_7721317524785797518) {
  h_14(state, unused, out_7721317524785797518);
}
void pose_H_14(double *state, double *unused, double *out_3845499245842477199) {
  H_14(state, unused, out_3845499245842477199);
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
