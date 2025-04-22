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
void err_fun(double *nom_x, double *delta_x, double *out_698032175064450046) {
   out_698032175064450046[0] = delta_x[0] + nom_x[0];
   out_698032175064450046[1] = delta_x[1] + nom_x[1];
   out_698032175064450046[2] = delta_x[2] + nom_x[2];
   out_698032175064450046[3] = delta_x[3] + nom_x[3];
   out_698032175064450046[4] = delta_x[4] + nom_x[4];
   out_698032175064450046[5] = delta_x[5] + nom_x[5];
   out_698032175064450046[6] = delta_x[6] + nom_x[6];
   out_698032175064450046[7] = delta_x[7] + nom_x[7];
   out_698032175064450046[8] = delta_x[8] + nom_x[8];
   out_698032175064450046[9] = delta_x[9] + nom_x[9];
   out_698032175064450046[10] = delta_x[10] + nom_x[10];
   out_698032175064450046[11] = delta_x[11] + nom_x[11];
   out_698032175064450046[12] = delta_x[12] + nom_x[12];
   out_698032175064450046[13] = delta_x[13] + nom_x[13];
   out_698032175064450046[14] = delta_x[14] + nom_x[14];
   out_698032175064450046[15] = delta_x[15] + nom_x[15];
   out_698032175064450046[16] = delta_x[16] + nom_x[16];
   out_698032175064450046[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5780803266693922923) {
   out_5780803266693922923[0] = -nom_x[0] + true_x[0];
   out_5780803266693922923[1] = -nom_x[1] + true_x[1];
   out_5780803266693922923[2] = -nom_x[2] + true_x[2];
   out_5780803266693922923[3] = -nom_x[3] + true_x[3];
   out_5780803266693922923[4] = -nom_x[4] + true_x[4];
   out_5780803266693922923[5] = -nom_x[5] + true_x[5];
   out_5780803266693922923[6] = -nom_x[6] + true_x[6];
   out_5780803266693922923[7] = -nom_x[7] + true_x[7];
   out_5780803266693922923[8] = -nom_x[8] + true_x[8];
   out_5780803266693922923[9] = -nom_x[9] + true_x[9];
   out_5780803266693922923[10] = -nom_x[10] + true_x[10];
   out_5780803266693922923[11] = -nom_x[11] + true_x[11];
   out_5780803266693922923[12] = -nom_x[12] + true_x[12];
   out_5780803266693922923[13] = -nom_x[13] + true_x[13];
   out_5780803266693922923[14] = -nom_x[14] + true_x[14];
   out_5780803266693922923[15] = -nom_x[15] + true_x[15];
   out_5780803266693922923[16] = -nom_x[16] + true_x[16];
   out_5780803266693922923[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6648112690817590410) {
   out_6648112690817590410[0] = 1.0;
   out_6648112690817590410[1] = 0.0;
   out_6648112690817590410[2] = 0.0;
   out_6648112690817590410[3] = 0.0;
   out_6648112690817590410[4] = 0.0;
   out_6648112690817590410[5] = 0.0;
   out_6648112690817590410[6] = 0.0;
   out_6648112690817590410[7] = 0.0;
   out_6648112690817590410[8] = 0.0;
   out_6648112690817590410[9] = 0.0;
   out_6648112690817590410[10] = 0.0;
   out_6648112690817590410[11] = 0.0;
   out_6648112690817590410[12] = 0.0;
   out_6648112690817590410[13] = 0.0;
   out_6648112690817590410[14] = 0.0;
   out_6648112690817590410[15] = 0.0;
   out_6648112690817590410[16] = 0.0;
   out_6648112690817590410[17] = 0.0;
   out_6648112690817590410[18] = 0.0;
   out_6648112690817590410[19] = 1.0;
   out_6648112690817590410[20] = 0.0;
   out_6648112690817590410[21] = 0.0;
   out_6648112690817590410[22] = 0.0;
   out_6648112690817590410[23] = 0.0;
   out_6648112690817590410[24] = 0.0;
   out_6648112690817590410[25] = 0.0;
   out_6648112690817590410[26] = 0.0;
   out_6648112690817590410[27] = 0.0;
   out_6648112690817590410[28] = 0.0;
   out_6648112690817590410[29] = 0.0;
   out_6648112690817590410[30] = 0.0;
   out_6648112690817590410[31] = 0.0;
   out_6648112690817590410[32] = 0.0;
   out_6648112690817590410[33] = 0.0;
   out_6648112690817590410[34] = 0.0;
   out_6648112690817590410[35] = 0.0;
   out_6648112690817590410[36] = 0.0;
   out_6648112690817590410[37] = 0.0;
   out_6648112690817590410[38] = 1.0;
   out_6648112690817590410[39] = 0.0;
   out_6648112690817590410[40] = 0.0;
   out_6648112690817590410[41] = 0.0;
   out_6648112690817590410[42] = 0.0;
   out_6648112690817590410[43] = 0.0;
   out_6648112690817590410[44] = 0.0;
   out_6648112690817590410[45] = 0.0;
   out_6648112690817590410[46] = 0.0;
   out_6648112690817590410[47] = 0.0;
   out_6648112690817590410[48] = 0.0;
   out_6648112690817590410[49] = 0.0;
   out_6648112690817590410[50] = 0.0;
   out_6648112690817590410[51] = 0.0;
   out_6648112690817590410[52] = 0.0;
   out_6648112690817590410[53] = 0.0;
   out_6648112690817590410[54] = 0.0;
   out_6648112690817590410[55] = 0.0;
   out_6648112690817590410[56] = 0.0;
   out_6648112690817590410[57] = 1.0;
   out_6648112690817590410[58] = 0.0;
   out_6648112690817590410[59] = 0.0;
   out_6648112690817590410[60] = 0.0;
   out_6648112690817590410[61] = 0.0;
   out_6648112690817590410[62] = 0.0;
   out_6648112690817590410[63] = 0.0;
   out_6648112690817590410[64] = 0.0;
   out_6648112690817590410[65] = 0.0;
   out_6648112690817590410[66] = 0.0;
   out_6648112690817590410[67] = 0.0;
   out_6648112690817590410[68] = 0.0;
   out_6648112690817590410[69] = 0.0;
   out_6648112690817590410[70] = 0.0;
   out_6648112690817590410[71] = 0.0;
   out_6648112690817590410[72] = 0.0;
   out_6648112690817590410[73] = 0.0;
   out_6648112690817590410[74] = 0.0;
   out_6648112690817590410[75] = 0.0;
   out_6648112690817590410[76] = 1.0;
   out_6648112690817590410[77] = 0.0;
   out_6648112690817590410[78] = 0.0;
   out_6648112690817590410[79] = 0.0;
   out_6648112690817590410[80] = 0.0;
   out_6648112690817590410[81] = 0.0;
   out_6648112690817590410[82] = 0.0;
   out_6648112690817590410[83] = 0.0;
   out_6648112690817590410[84] = 0.0;
   out_6648112690817590410[85] = 0.0;
   out_6648112690817590410[86] = 0.0;
   out_6648112690817590410[87] = 0.0;
   out_6648112690817590410[88] = 0.0;
   out_6648112690817590410[89] = 0.0;
   out_6648112690817590410[90] = 0.0;
   out_6648112690817590410[91] = 0.0;
   out_6648112690817590410[92] = 0.0;
   out_6648112690817590410[93] = 0.0;
   out_6648112690817590410[94] = 0.0;
   out_6648112690817590410[95] = 1.0;
   out_6648112690817590410[96] = 0.0;
   out_6648112690817590410[97] = 0.0;
   out_6648112690817590410[98] = 0.0;
   out_6648112690817590410[99] = 0.0;
   out_6648112690817590410[100] = 0.0;
   out_6648112690817590410[101] = 0.0;
   out_6648112690817590410[102] = 0.0;
   out_6648112690817590410[103] = 0.0;
   out_6648112690817590410[104] = 0.0;
   out_6648112690817590410[105] = 0.0;
   out_6648112690817590410[106] = 0.0;
   out_6648112690817590410[107] = 0.0;
   out_6648112690817590410[108] = 0.0;
   out_6648112690817590410[109] = 0.0;
   out_6648112690817590410[110] = 0.0;
   out_6648112690817590410[111] = 0.0;
   out_6648112690817590410[112] = 0.0;
   out_6648112690817590410[113] = 0.0;
   out_6648112690817590410[114] = 1.0;
   out_6648112690817590410[115] = 0.0;
   out_6648112690817590410[116] = 0.0;
   out_6648112690817590410[117] = 0.0;
   out_6648112690817590410[118] = 0.0;
   out_6648112690817590410[119] = 0.0;
   out_6648112690817590410[120] = 0.0;
   out_6648112690817590410[121] = 0.0;
   out_6648112690817590410[122] = 0.0;
   out_6648112690817590410[123] = 0.0;
   out_6648112690817590410[124] = 0.0;
   out_6648112690817590410[125] = 0.0;
   out_6648112690817590410[126] = 0.0;
   out_6648112690817590410[127] = 0.0;
   out_6648112690817590410[128] = 0.0;
   out_6648112690817590410[129] = 0.0;
   out_6648112690817590410[130] = 0.0;
   out_6648112690817590410[131] = 0.0;
   out_6648112690817590410[132] = 0.0;
   out_6648112690817590410[133] = 1.0;
   out_6648112690817590410[134] = 0.0;
   out_6648112690817590410[135] = 0.0;
   out_6648112690817590410[136] = 0.0;
   out_6648112690817590410[137] = 0.0;
   out_6648112690817590410[138] = 0.0;
   out_6648112690817590410[139] = 0.0;
   out_6648112690817590410[140] = 0.0;
   out_6648112690817590410[141] = 0.0;
   out_6648112690817590410[142] = 0.0;
   out_6648112690817590410[143] = 0.0;
   out_6648112690817590410[144] = 0.0;
   out_6648112690817590410[145] = 0.0;
   out_6648112690817590410[146] = 0.0;
   out_6648112690817590410[147] = 0.0;
   out_6648112690817590410[148] = 0.0;
   out_6648112690817590410[149] = 0.0;
   out_6648112690817590410[150] = 0.0;
   out_6648112690817590410[151] = 0.0;
   out_6648112690817590410[152] = 1.0;
   out_6648112690817590410[153] = 0.0;
   out_6648112690817590410[154] = 0.0;
   out_6648112690817590410[155] = 0.0;
   out_6648112690817590410[156] = 0.0;
   out_6648112690817590410[157] = 0.0;
   out_6648112690817590410[158] = 0.0;
   out_6648112690817590410[159] = 0.0;
   out_6648112690817590410[160] = 0.0;
   out_6648112690817590410[161] = 0.0;
   out_6648112690817590410[162] = 0.0;
   out_6648112690817590410[163] = 0.0;
   out_6648112690817590410[164] = 0.0;
   out_6648112690817590410[165] = 0.0;
   out_6648112690817590410[166] = 0.0;
   out_6648112690817590410[167] = 0.0;
   out_6648112690817590410[168] = 0.0;
   out_6648112690817590410[169] = 0.0;
   out_6648112690817590410[170] = 0.0;
   out_6648112690817590410[171] = 1.0;
   out_6648112690817590410[172] = 0.0;
   out_6648112690817590410[173] = 0.0;
   out_6648112690817590410[174] = 0.0;
   out_6648112690817590410[175] = 0.0;
   out_6648112690817590410[176] = 0.0;
   out_6648112690817590410[177] = 0.0;
   out_6648112690817590410[178] = 0.0;
   out_6648112690817590410[179] = 0.0;
   out_6648112690817590410[180] = 0.0;
   out_6648112690817590410[181] = 0.0;
   out_6648112690817590410[182] = 0.0;
   out_6648112690817590410[183] = 0.0;
   out_6648112690817590410[184] = 0.0;
   out_6648112690817590410[185] = 0.0;
   out_6648112690817590410[186] = 0.0;
   out_6648112690817590410[187] = 0.0;
   out_6648112690817590410[188] = 0.0;
   out_6648112690817590410[189] = 0.0;
   out_6648112690817590410[190] = 1.0;
   out_6648112690817590410[191] = 0.0;
   out_6648112690817590410[192] = 0.0;
   out_6648112690817590410[193] = 0.0;
   out_6648112690817590410[194] = 0.0;
   out_6648112690817590410[195] = 0.0;
   out_6648112690817590410[196] = 0.0;
   out_6648112690817590410[197] = 0.0;
   out_6648112690817590410[198] = 0.0;
   out_6648112690817590410[199] = 0.0;
   out_6648112690817590410[200] = 0.0;
   out_6648112690817590410[201] = 0.0;
   out_6648112690817590410[202] = 0.0;
   out_6648112690817590410[203] = 0.0;
   out_6648112690817590410[204] = 0.0;
   out_6648112690817590410[205] = 0.0;
   out_6648112690817590410[206] = 0.0;
   out_6648112690817590410[207] = 0.0;
   out_6648112690817590410[208] = 0.0;
   out_6648112690817590410[209] = 1.0;
   out_6648112690817590410[210] = 0.0;
   out_6648112690817590410[211] = 0.0;
   out_6648112690817590410[212] = 0.0;
   out_6648112690817590410[213] = 0.0;
   out_6648112690817590410[214] = 0.0;
   out_6648112690817590410[215] = 0.0;
   out_6648112690817590410[216] = 0.0;
   out_6648112690817590410[217] = 0.0;
   out_6648112690817590410[218] = 0.0;
   out_6648112690817590410[219] = 0.0;
   out_6648112690817590410[220] = 0.0;
   out_6648112690817590410[221] = 0.0;
   out_6648112690817590410[222] = 0.0;
   out_6648112690817590410[223] = 0.0;
   out_6648112690817590410[224] = 0.0;
   out_6648112690817590410[225] = 0.0;
   out_6648112690817590410[226] = 0.0;
   out_6648112690817590410[227] = 0.0;
   out_6648112690817590410[228] = 1.0;
   out_6648112690817590410[229] = 0.0;
   out_6648112690817590410[230] = 0.0;
   out_6648112690817590410[231] = 0.0;
   out_6648112690817590410[232] = 0.0;
   out_6648112690817590410[233] = 0.0;
   out_6648112690817590410[234] = 0.0;
   out_6648112690817590410[235] = 0.0;
   out_6648112690817590410[236] = 0.0;
   out_6648112690817590410[237] = 0.0;
   out_6648112690817590410[238] = 0.0;
   out_6648112690817590410[239] = 0.0;
   out_6648112690817590410[240] = 0.0;
   out_6648112690817590410[241] = 0.0;
   out_6648112690817590410[242] = 0.0;
   out_6648112690817590410[243] = 0.0;
   out_6648112690817590410[244] = 0.0;
   out_6648112690817590410[245] = 0.0;
   out_6648112690817590410[246] = 0.0;
   out_6648112690817590410[247] = 1.0;
   out_6648112690817590410[248] = 0.0;
   out_6648112690817590410[249] = 0.0;
   out_6648112690817590410[250] = 0.0;
   out_6648112690817590410[251] = 0.0;
   out_6648112690817590410[252] = 0.0;
   out_6648112690817590410[253] = 0.0;
   out_6648112690817590410[254] = 0.0;
   out_6648112690817590410[255] = 0.0;
   out_6648112690817590410[256] = 0.0;
   out_6648112690817590410[257] = 0.0;
   out_6648112690817590410[258] = 0.0;
   out_6648112690817590410[259] = 0.0;
   out_6648112690817590410[260] = 0.0;
   out_6648112690817590410[261] = 0.0;
   out_6648112690817590410[262] = 0.0;
   out_6648112690817590410[263] = 0.0;
   out_6648112690817590410[264] = 0.0;
   out_6648112690817590410[265] = 0.0;
   out_6648112690817590410[266] = 1.0;
   out_6648112690817590410[267] = 0.0;
   out_6648112690817590410[268] = 0.0;
   out_6648112690817590410[269] = 0.0;
   out_6648112690817590410[270] = 0.0;
   out_6648112690817590410[271] = 0.0;
   out_6648112690817590410[272] = 0.0;
   out_6648112690817590410[273] = 0.0;
   out_6648112690817590410[274] = 0.0;
   out_6648112690817590410[275] = 0.0;
   out_6648112690817590410[276] = 0.0;
   out_6648112690817590410[277] = 0.0;
   out_6648112690817590410[278] = 0.0;
   out_6648112690817590410[279] = 0.0;
   out_6648112690817590410[280] = 0.0;
   out_6648112690817590410[281] = 0.0;
   out_6648112690817590410[282] = 0.0;
   out_6648112690817590410[283] = 0.0;
   out_6648112690817590410[284] = 0.0;
   out_6648112690817590410[285] = 1.0;
   out_6648112690817590410[286] = 0.0;
   out_6648112690817590410[287] = 0.0;
   out_6648112690817590410[288] = 0.0;
   out_6648112690817590410[289] = 0.0;
   out_6648112690817590410[290] = 0.0;
   out_6648112690817590410[291] = 0.0;
   out_6648112690817590410[292] = 0.0;
   out_6648112690817590410[293] = 0.0;
   out_6648112690817590410[294] = 0.0;
   out_6648112690817590410[295] = 0.0;
   out_6648112690817590410[296] = 0.0;
   out_6648112690817590410[297] = 0.0;
   out_6648112690817590410[298] = 0.0;
   out_6648112690817590410[299] = 0.0;
   out_6648112690817590410[300] = 0.0;
   out_6648112690817590410[301] = 0.0;
   out_6648112690817590410[302] = 0.0;
   out_6648112690817590410[303] = 0.0;
   out_6648112690817590410[304] = 1.0;
   out_6648112690817590410[305] = 0.0;
   out_6648112690817590410[306] = 0.0;
   out_6648112690817590410[307] = 0.0;
   out_6648112690817590410[308] = 0.0;
   out_6648112690817590410[309] = 0.0;
   out_6648112690817590410[310] = 0.0;
   out_6648112690817590410[311] = 0.0;
   out_6648112690817590410[312] = 0.0;
   out_6648112690817590410[313] = 0.0;
   out_6648112690817590410[314] = 0.0;
   out_6648112690817590410[315] = 0.0;
   out_6648112690817590410[316] = 0.0;
   out_6648112690817590410[317] = 0.0;
   out_6648112690817590410[318] = 0.0;
   out_6648112690817590410[319] = 0.0;
   out_6648112690817590410[320] = 0.0;
   out_6648112690817590410[321] = 0.0;
   out_6648112690817590410[322] = 0.0;
   out_6648112690817590410[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7821804503371700671) {
   out_7821804503371700671[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7821804503371700671[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7821804503371700671[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7821804503371700671[3] = dt*state[12] + state[3];
   out_7821804503371700671[4] = dt*state[13] + state[4];
   out_7821804503371700671[5] = dt*state[14] + state[5];
   out_7821804503371700671[6] = state[6];
   out_7821804503371700671[7] = state[7];
   out_7821804503371700671[8] = state[8];
   out_7821804503371700671[9] = state[9];
   out_7821804503371700671[10] = state[10];
   out_7821804503371700671[11] = state[11];
   out_7821804503371700671[12] = state[12];
   out_7821804503371700671[13] = state[13];
   out_7821804503371700671[14] = state[14];
   out_7821804503371700671[15] = state[15];
   out_7821804503371700671[16] = state[16];
   out_7821804503371700671[17] = state[17];
}
void F_fun(double *state, double dt, double *out_205686487848379182) {
   out_205686487848379182[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_205686487848379182[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_205686487848379182[2] = 0;
   out_205686487848379182[3] = 0;
   out_205686487848379182[4] = 0;
   out_205686487848379182[5] = 0;
   out_205686487848379182[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_205686487848379182[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_205686487848379182[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_205686487848379182[9] = 0;
   out_205686487848379182[10] = 0;
   out_205686487848379182[11] = 0;
   out_205686487848379182[12] = 0;
   out_205686487848379182[13] = 0;
   out_205686487848379182[14] = 0;
   out_205686487848379182[15] = 0;
   out_205686487848379182[16] = 0;
   out_205686487848379182[17] = 0;
   out_205686487848379182[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_205686487848379182[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_205686487848379182[20] = 0;
   out_205686487848379182[21] = 0;
   out_205686487848379182[22] = 0;
   out_205686487848379182[23] = 0;
   out_205686487848379182[24] = 0;
   out_205686487848379182[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_205686487848379182[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_205686487848379182[27] = 0;
   out_205686487848379182[28] = 0;
   out_205686487848379182[29] = 0;
   out_205686487848379182[30] = 0;
   out_205686487848379182[31] = 0;
   out_205686487848379182[32] = 0;
   out_205686487848379182[33] = 0;
   out_205686487848379182[34] = 0;
   out_205686487848379182[35] = 0;
   out_205686487848379182[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_205686487848379182[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_205686487848379182[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_205686487848379182[39] = 0;
   out_205686487848379182[40] = 0;
   out_205686487848379182[41] = 0;
   out_205686487848379182[42] = 0;
   out_205686487848379182[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_205686487848379182[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_205686487848379182[45] = 0;
   out_205686487848379182[46] = 0;
   out_205686487848379182[47] = 0;
   out_205686487848379182[48] = 0;
   out_205686487848379182[49] = 0;
   out_205686487848379182[50] = 0;
   out_205686487848379182[51] = 0;
   out_205686487848379182[52] = 0;
   out_205686487848379182[53] = 0;
   out_205686487848379182[54] = 0;
   out_205686487848379182[55] = 0;
   out_205686487848379182[56] = 0;
   out_205686487848379182[57] = 1;
   out_205686487848379182[58] = 0;
   out_205686487848379182[59] = 0;
   out_205686487848379182[60] = 0;
   out_205686487848379182[61] = 0;
   out_205686487848379182[62] = 0;
   out_205686487848379182[63] = 0;
   out_205686487848379182[64] = 0;
   out_205686487848379182[65] = 0;
   out_205686487848379182[66] = dt;
   out_205686487848379182[67] = 0;
   out_205686487848379182[68] = 0;
   out_205686487848379182[69] = 0;
   out_205686487848379182[70] = 0;
   out_205686487848379182[71] = 0;
   out_205686487848379182[72] = 0;
   out_205686487848379182[73] = 0;
   out_205686487848379182[74] = 0;
   out_205686487848379182[75] = 0;
   out_205686487848379182[76] = 1;
   out_205686487848379182[77] = 0;
   out_205686487848379182[78] = 0;
   out_205686487848379182[79] = 0;
   out_205686487848379182[80] = 0;
   out_205686487848379182[81] = 0;
   out_205686487848379182[82] = 0;
   out_205686487848379182[83] = 0;
   out_205686487848379182[84] = 0;
   out_205686487848379182[85] = dt;
   out_205686487848379182[86] = 0;
   out_205686487848379182[87] = 0;
   out_205686487848379182[88] = 0;
   out_205686487848379182[89] = 0;
   out_205686487848379182[90] = 0;
   out_205686487848379182[91] = 0;
   out_205686487848379182[92] = 0;
   out_205686487848379182[93] = 0;
   out_205686487848379182[94] = 0;
   out_205686487848379182[95] = 1;
   out_205686487848379182[96] = 0;
   out_205686487848379182[97] = 0;
   out_205686487848379182[98] = 0;
   out_205686487848379182[99] = 0;
   out_205686487848379182[100] = 0;
   out_205686487848379182[101] = 0;
   out_205686487848379182[102] = 0;
   out_205686487848379182[103] = 0;
   out_205686487848379182[104] = dt;
   out_205686487848379182[105] = 0;
   out_205686487848379182[106] = 0;
   out_205686487848379182[107] = 0;
   out_205686487848379182[108] = 0;
   out_205686487848379182[109] = 0;
   out_205686487848379182[110] = 0;
   out_205686487848379182[111] = 0;
   out_205686487848379182[112] = 0;
   out_205686487848379182[113] = 0;
   out_205686487848379182[114] = 1;
   out_205686487848379182[115] = 0;
   out_205686487848379182[116] = 0;
   out_205686487848379182[117] = 0;
   out_205686487848379182[118] = 0;
   out_205686487848379182[119] = 0;
   out_205686487848379182[120] = 0;
   out_205686487848379182[121] = 0;
   out_205686487848379182[122] = 0;
   out_205686487848379182[123] = 0;
   out_205686487848379182[124] = 0;
   out_205686487848379182[125] = 0;
   out_205686487848379182[126] = 0;
   out_205686487848379182[127] = 0;
   out_205686487848379182[128] = 0;
   out_205686487848379182[129] = 0;
   out_205686487848379182[130] = 0;
   out_205686487848379182[131] = 0;
   out_205686487848379182[132] = 0;
   out_205686487848379182[133] = 1;
   out_205686487848379182[134] = 0;
   out_205686487848379182[135] = 0;
   out_205686487848379182[136] = 0;
   out_205686487848379182[137] = 0;
   out_205686487848379182[138] = 0;
   out_205686487848379182[139] = 0;
   out_205686487848379182[140] = 0;
   out_205686487848379182[141] = 0;
   out_205686487848379182[142] = 0;
   out_205686487848379182[143] = 0;
   out_205686487848379182[144] = 0;
   out_205686487848379182[145] = 0;
   out_205686487848379182[146] = 0;
   out_205686487848379182[147] = 0;
   out_205686487848379182[148] = 0;
   out_205686487848379182[149] = 0;
   out_205686487848379182[150] = 0;
   out_205686487848379182[151] = 0;
   out_205686487848379182[152] = 1;
   out_205686487848379182[153] = 0;
   out_205686487848379182[154] = 0;
   out_205686487848379182[155] = 0;
   out_205686487848379182[156] = 0;
   out_205686487848379182[157] = 0;
   out_205686487848379182[158] = 0;
   out_205686487848379182[159] = 0;
   out_205686487848379182[160] = 0;
   out_205686487848379182[161] = 0;
   out_205686487848379182[162] = 0;
   out_205686487848379182[163] = 0;
   out_205686487848379182[164] = 0;
   out_205686487848379182[165] = 0;
   out_205686487848379182[166] = 0;
   out_205686487848379182[167] = 0;
   out_205686487848379182[168] = 0;
   out_205686487848379182[169] = 0;
   out_205686487848379182[170] = 0;
   out_205686487848379182[171] = 1;
   out_205686487848379182[172] = 0;
   out_205686487848379182[173] = 0;
   out_205686487848379182[174] = 0;
   out_205686487848379182[175] = 0;
   out_205686487848379182[176] = 0;
   out_205686487848379182[177] = 0;
   out_205686487848379182[178] = 0;
   out_205686487848379182[179] = 0;
   out_205686487848379182[180] = 0;
   out_205686487848379182[181] = 0;
   out_205686487848379182[182] = 0;
   out_205686487848379182[183] = 0;
   out_205686487848379182[184] = 0;
   out_205686487848379182[185] = 0;
   out_205686487848379182[186] = 0;
   out_205686487848379182[187] = 0;
   out_205686487848379182[188] = 0;
   out_205686487848379182[189] = 0;
   out_205686487848379182[190] = 1;
   out_205686487848379182[191] = 0;
   out_205686487848379182[192] = 0;
   out_205686487848379182[193] = 0;
   out_205686487848379182[194] = 0;
   out_205686487848379182[195] = 0;
   out_205686487848379182[196] = 0;
   out_205686487848379182[197] = 0;
   out_205686487848379182[198] = 0;
   out_205686487848379182[199] = 0;
   out_205686487848379182[200] = 0;
   out_205686487848379182[201] = 0;
   out_205686487848379182[202] = 0;
   out_205686487848379182[203] = 0;
   out_205686487848379182[204] = 0;
   out_205686487848379182[205] = 0;
   out_205686487848379182[206] = 0;
   out_205686487848379182[207] = 0;
   out_205686487848379182[208] = 0;
   out_205686487848379182[209] = 1;
   out_205686487848379182[210] = 0;
   out_205686487848379182[211] = 0;
   out_205686487848379182[212] = 0;
   out_205686487848379182[213] = 0;
   out_205686487848379182[214] = 0;
   out_205686487848379182[215] = 0;
   out_205686487848379182[216] = 0;
   out_205686487848379182[217] = 0;
   out_205686487848379182[218] = 0;
   out_205686487848379182[219] = 0;
   out_205686487848379182[220] = 0;
   out_205686487848379182[221] = 0;
   out_205686487848379182[222] = 0;
   out_205686487848379182[223] = 0;
   out_205686487848379182[224] = 0;
   out_205686487848379182[225] = 0;
   out_205686487848379182[226] = 0;
   out_205686487848379182[227] = 0;
   out_205686487848379182[228] = 1;
   out_205686487848379182[229] = 0;
   out_205686487848379182[230] = 0;
   out_205686487848379182[231] = 0;
   out_205686487848379182[232] = 0;
   out_205686487848379182[233] = 0;
   out_205686487848379182[234] = 0;
   out_205686487848379182[235] = 0;
   out_205686487848379182[236] = 0;
   out_205686487848379182[237] = 0;
   out_205686487848379182[238] = 0;
   out_205686487848379182[239] = 0;
   out_205686487848379182[240] = 0;
   out_205686487848379182[241] = 0;
   out_205686487848379182[242] = 0;
   out_205686487848379182[243] = 0;
   out_205686487848379182[244] = 0;
   out_205686487848379182[245] = 0;
   out_205686487848379182[246] = 0;
   out_205686487848379182[247] = 1;
   out_205686487848379182[248] = 0;
   out_205686487848379182[249] = 0;
   out_205686487848379182[250] = 0;
   out_205686487848379182[251] = 0;
   out_205686487848379182[252] = 0;
   out_205686487848379182[253] = 0;
   out_205686487848379182[254] = 0;
   out_205686487848379182[255] = 0;
   out_205686487848379182[256] = 0;
   out_205686487848379182[257] = 0;
   out_205686487848379182[258] = 0;
   out_205686487848379182[259] = 0;
   out_205686487848379182[260] = 0;
   out_205686487848379182[261] = 0;
   out_205686487848379182[262] = 0;
   out_205686487848379182[263] = 0;
   out_205686487848379182[264] = 0;
   out_205686487848379182[265] = 0;
   out_205686487848379182[266] = 1;
   out_205686487848379182[267] = 0;
   out_205686487848379182[268] = 0;
   out_205686487848379182[269] = 0;
   out_205686487848379182[270] = 0;
   out_205686487848379182[271] = 0;
   out_205686487848379182[272] = 0;
   out_205686487848379182[273] = 0;
   out_205686487848379182[274] = 0;
   out_205686487848379182[275] = 0;
   out_205686487848379182[276] = 0;
   out_205686487848379182[277] = 0;
   out_205686487848379182[278] = 0;
   out_205686487848379182[279] = 0;
   out_205686487848379182[280] = 0;
   out_205686487848379182[281] = 0;
   out_205686487848379182[282] = 0;
   out_205686487848379182[283] = 0;
   out_205686487848379182[284] = 0;
   out_205686487848379182[285] = 1;
   out_205686487848379182[286] = 0;
   out_205686487848379182[287] = 0;
   out_205686487848379182[288] = 0;
   out_205686487848379182[289] = 0;
   out_205686487848379182[290] = 0;
   out_205686487848379182[291] = 0;
   out_205686487848379182[292] = 0;
   out_205686487848379182[293] = 0;
   out_205686487848379182[294] = 0;
   out_205686487848379182[295] = 0;
   out_205686487848379182[296] = 0;
   out_205686487848379182[297] = 0;
   out_205686487848379182[298] = 0;
   out_205686487848379182[299] = 0;
   out_205686487848379182[300] = 0;
   out_205686487848379182[301] = 0;
   out_205686487848379182[302] = 0;
   out_205686487848379182[303] = 0;
   out_205686487848379182[304] = 1;
   out_205686487848379182[305] = 0;
   out_205686487848379182[306] = 0;
   out_205686487848379182[307] = 0;
   out_205686487848379182[308] = 0;
   out_205686487848379182[309] = 0;
   out_205686487848379182[310] = 0;
   out_205686487848379182[311] = 0;
   out_205686487848379182[312] = 0;
   out_205686487848379182[313] = 0;
   out_205686487848379182[314] = 0;
   out_205686487848379182[315] = 0;
   out_205686487848379182[316] = 0;
   out_205686487848379182[317] = 0;
   out_205686487848379182[318] = 0;
   out_205686487848379182[319] = 0;
   out_205686487848379182[320] = 0;
   out_205686487848379182[321] = 0;
   out_205686487848379182[322] = 0;
   out_205686487848379182[323] = 1;
}
void h_4(double *state, double *unused, double *out_4018057612377416184) {
   out_4018057612377416184[0] = state[6] + state[9];
   out_4018057612377416184[1] = state[7] + state[10];
   out_4018057612377416184[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7402273692872303017) {
   out_7402273692872303017[0] = 0;
   out_7402273692872303017[1] = 0;
   out_7402273692872303017[2] = 0;
   out_7402273692872303017[3] = 0;
   out_7402273692872303017[4] = 0;
   out_7402273692872303017[5] = 0;
   out_7402273692872303017[6] = 1;
   out_7402273692872303017[7] = 0;
   out_7402273692872303017[8] = 0;
   out_7402273692872303017[9] = 1;
   out_7402273692872303017[10] = 0;
   out_7402273692872303017[11] = 0;
   out_7402273692872303017[12] = 0;
   out_7402273692872303017[13] = 0;
   out_7402273692872303017[14] = 0;
   out_7402273692872303017[15] = 0;
   out_7402273692872303017[16] = 0;
   out_7402273692872303017[17] = 0;
   out_7402273692872303017[18] = 0;
   out_7402273692872303017[19] = 0;
   out_7402273692872303017[20] = 0;
   out_7402273692872303017[21] = 0;
   out_7402273692872303017[22] = 0;
   out_7402273692872303017[23] = 0;
   out_7402273692872303017[24] = 0;
   out_7402273692872303017[25] = 1;
   out_7402273692872303017[26] = 0;
   out_7402273692872303017[27] = 0;
   out_7402273692872303017[28] = 1;
   out_7402273692872303017[29] = 0;
   out_7402273692872303017[30] = 0;
   out_7402273692872303017[31] = 0;
   out_7402273692872303017[32] = 0;
   out_7402273692872303017[33] = 0;
   out_7402273692872303017[34] = 0;
   out_7402273692872303017[35] = 0;
   out_7402273692872303017[36] = 0;
   out_7402273692872303017[37] = 0;
   out_7402273692872303017[38] = 0;
   out_7402273692872303017[39] = 0;
   out_7402273692872303017[40] = 0;
   out_7402273692872303017[41] = 0;
   out_7402273692872303017[42] = 0;
   out_7402273692872303017[43] = 0;
   out_7402273692872303017[44] = 1;
   out_7402273692872303017[45] = 0;
   out_7402273692872303017[46] = 0;
   out_7402273692872303017[47] = 1;
   out_7402273692872303017[48] = 0;
   out_7402273692872303017[49] = 0;
   out_7402273692872303017[50] = 0;
   out_7402273692872303017[51] = 0;
   out_7402273692872303017[52] = 0;
   out_7402273692872303017[53] = 0;
}
void h_10(double *state, double *unused, double *out_2239744291470184978) {
   out_2239744291470184978[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2239744291470184978[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2239744291470184978[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5031652819947027519) {
   out_5031652819947027519[0] = 0;
   out_5031652819947027519[1] = 9.8100000000000005*cos(state[1]);
   out_5031652819947027519[2] = 0;
   out_5031652819947027519[3] = 0;
   out_5031652819947027519[4] = -state[8];
   out_5031652819947027519[5] = state[7];
   out_5031652819947027519[6] = 0;
   out_5031652819947027519[7] = state[5];
   out_5031652819947027519[8] = -state[4];
   out_5031652819947027519[9] = 0;
   out_5031652819947027519[10] = 0;
   out_5031652819947027519[11] = 0;
   out_5031652819947027519[12] = 1;
   out_5031652819947027519[13] = 0;
   out_5031652819947027519[14] = 0;
   out_5031652819947027519[15] = 1;
   out_5031652819947027519[16] = 0;
   out_5031652819947027519[17] = 0;
   out_5031652819947027519[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5031652819947027519[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5031652819947027519[20] = 0;
   out_5031652819947027519[21] = state[8];
   out_5031652819947027519[22] = 0;
   out_5031652819947027519[23] = -state[6];
   out_5031652819947027519[24] = -state[5];
   out_5031652819947027519[25] = 0;
   out_5031652819947027519[26] = state[3];
   out_5031652819947027519[27] = 0;
   out_5031652819947027519[28] = 0;
   out_5031652819947027519[29] = 0;
   out_5031652819947027519[30] = 0;
   out_5031652819947027519[31] = 1;
   out_5031652819947027519[32] = 0;
   out_5031652819947027519[33] = 0;
   out_5031652819947027519[34] = 1;
   out_5031652819947027519[35] = 0;
   out_5031652819947027519[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5031652819947027519[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5031652819947027519[38] = 0;
   out_5031652819947027519[39] = -state[7];
   out_5031652819947027519[40] = state[6];
   out_5031652819947027519[41] = 0;
   out_5031652819947027519[42] = state[4];
   out_5031652819947027519[43] = -state[3];
   out_5031652819947027519[44] = 0;
   out_5031652819947027519[45] = 0;
   out_5031652819947027519[46] = 0;
   out_5031652819947027519[47] = 0;
   out_5031652819947027519[48] = 0;
   out_5031652819947027519[49] = 0;
   out_5031652819947027519[50] = 1;
   out_5031652819947027519[51] = 0;
   out_5031652819947027519[52] = 0;
   out_5031652819947027519[53] = 1;
}
void h_13(double *state, double *unused, double *out_1172069521836927214) {
   out_1172069521836927214[0] = state[3];
   out_1172069521836927214[1] = state[4];
   out_1172069521836927214[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3433839172520547670) {
   out_3433839172520547670[0] = 0;
   out_3433839172520547670[1] = 0;
   out_3433839172520547670[2] = 0;
   out_3433839172520547670[3] = 1;
   out_3433839172520547670[4] = 0;
   out_3433839172520547670[5] = 0;
   out_3433839172520547670[6] = 0;
   out_3433839172520547670[7] = 0;
   out_3433839172520547670[8] = 0;
   out_3433839172520547670[9] = 0;
   out_3433839172520547670[10] = 0;
   out_3433839172520547670[11] = 0;
   out_3433839172520547670[12] = 0;
   out_3433839172520547670[13] = 0;
   out_3433839172520547670[14] = 0;
   out_3433839172520547670[15] = 0;
   out_3433839172520547670[16] = 0;
   out_3433839172520547670[17] = 0;
   out_3433839172520547670[18] = 0;
   out_3433839172520547670[19] = 0;
   out_3433839172520547670[20] = 0;
   out_3433839172520547670[21] = 0;
   out_3433839172520547670[22] = 1;
   out_3433839172520547670[23] = 0;
   out_3433839172520547670[24] = 0;
   out_3433839172520547670[25] = 0;
   out_3433839172520547670[26] = 0;
   out_3433839172520547670[27] = 0;
   out_3433839172520547670[28] = 0;
   out_3433839172520547670[29] = 0;
   out_3433839172520547670[30] = 0;
   out_3433839172520547670[31] = 0;
   out_3433839172520547670[32] = 0;
   out_3433839172520547670[33] = 0;
   out_3433839172520547670[34] = 0;
   out_3433839172520547670[35] = 0;
   out_3433839172520547670[36] = 0;
   out_3433839172520547670[37] = 0;
   out_3433839172520547670[38] = 0;
   out_3433839172520547670[39] = 0;
   out_3433839172520547670[40] = 0;
   out_3433839172520547670[41] = 1;
   out_3433839172520547670[42] = 0;
   out_3433839172520547670[43] = 0;
   out_3433839172520547670[44] = 0;
   out_3433839172520547670[45] = 0;
   out_3433839172520547670[46] = 0;
   out_3433839172520547670[47] = 0;
   out_3433839172520547670[48] = 0;
   out_3433839172520547670[49] = 0;
   out_3433839172520547670[50] = 0;
   out_3433839172520547670[51] = 0;
   out_3433839172520547670[52] = 0;
   out_3433839172520547670[53] = 0;
}
void h_14(double *state, double *unused, double *out_6344550142343754918) {
   out_6344550142343754918[0] = state[6];
   out_6344550142343754918[1] = state[7];
   out_6344550142343754918[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4319485260576930721) {
   out_4319485260576930721[0] = 0;
   out_4319485260576930721[1] = 0;
   out_4319485260576930721[2] = 0;
   out_4319485260576930721[3] = 0;
   out_4319485260576930721[4] = 0;
   out_4319485260576930721[5] = 0;
   out_4319485260576930721[6] = 1;
   out_4319485260576930721[7] = 0;
   out_4319485260576930721[8] = 0;
   out_4319485260576930721[9] = 0;
   out_4319485260576930721[10] = 0;
   out_4319485260576930721[11] = 0;
   out_4319485260576930721[12] = 0;
   out_4319485260576930721[13] = 0;
   out_4319485260576930721[14] = 0;
   out_4319485260576930721[15] = 0;
   out_4319485260576930721[16] = 0;
   out_4319485260576930721[17] = 0;
   out_4319485260576930721[18] = 0;
   out_4319485260576930721[19] = 0;
   out_4319485260576930721[20] = 0;
   out_4319485260576930721[21] = 0;
   out_4319485260576930721[22] = 0;
   out_4319485260576930721[23] = 0;
   out_4319485260576930721[24] = 0;
   out_4319485260576930721[25] = 1;
   out_4319485260576930721[26] = 0;
   out_4319485260576930721[27] = 0;
   out_4319485260576930721[28] = 0;
   out_4319485260576930721[29] = 0;
   out_4319485260576930721[30] = 0;
   out_4319485260576930721[31] = 0;
   out_4319485260576930721[32] = 0;
   out_4319485260576930721[33] = 0;
   out_4319485260576930721[34] = 0;
   out_4319485260576930721[35] = 0;
   out_4319485260576930721[36] = 0;
   out_4319485260576930721[37] = 0;
   out_4319485260576930721[38] = 0;
   out_4319485260576930721[39] = 0;
   out_4319485260576930721[40] = 0;
   out_4319485260576930721[41] = 0;
   out_4319485260576930721[42] = 0;
   out_4319485260576930721[43] = 0;
   out_4319485260576930721[44] = 1;
   out_4319485260576930721[45] = 0;
   out_4319485260576930721[46] = 0;
   out_4319485260576930721[47] = 0;
   out_4319485260576930721[48] = 0;
   out_4319485260576930721[49] = 0;
   out_4319485260576930721[50] = 0;
   out_4319485260576930721[51] = 0;
   out_4319485260576930721[52] = 0;
   out_4319485260576930721[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_698032175064450046) {
  err_fun(nom_x, delta_x, out_698032175064450046);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5780803266693922923) {
  inv_err_fun(nom_x, true_x, out_5780803266693922923);
}
void pose_H_mod_fun(double *state, double *out_6648112690817590410) {
  H_mod_fun(state, out_6648112690817590410);
}
void pose_f_fun(double *state, double dt, double *out_7821804503371700671) {
  f_fun(state,  dt, out_7821804503371700671);
}
void pose_F_fun(double *state, double dt, double *out_205686487848379182) {
  F_fun(state,  dt, out_205686487848379182);
}
void pose_h_4(double *state, double *unused, double *out_4018057612377416184) {
  h_4(state, unused, out_4018057612377416184);
}
void pose_H_4(double *state, double *unused, double *out_7402273692872303017) {
  H_4(state, unused, out_7402273692872303017);
}
void pose_h_10(double *state, double *unused, double *out_2239744291470184978) {
  h_10(state, unused, out_2239744291470184978);
}
void pose_H_10(double *state, double *unused, double *out_5031652819947027519) {
  H_10(state, unused, out_5031652819947027519);
}
void pose_h_13(double *state, double *unused, double *out_1172069521836927214) {
  h_13(state, unused, out_1172069521836927214);
}
void pose_H_13(double *state, double *unused, double *out_3433839172520547670) {
  H_13(state, unused, out_3433839172520547670);
}
void pose_h_14(double *state, double *unused, double *out_6344550142343754918) {
  h_14(state, unused, out_6344550142343754918);
}
void pose_H_14(double *state, double *unused, double *out_4319485260576930721) {
  H_14(state, unused, out_4319485260576930721);
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
