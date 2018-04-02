#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <m4ri/m4ri.h>
//#include "List.h"
#include "kkeccak.h"
#include <vector>

using namespace std;

int Sbox(int a);

/** the very classic DDT
 */
int differential_distribution_table_origin(int DDT[32][32]);

int differential_distribution_table(int DDT[32][32]);//compatible input differences table
int differential_distribution_table_dir(int DDT[32][32]);//compatible output differences table

int print_DDT(int DDT[32][32]);

/** Generate all 320 input difference and the number of active sboxes from difference state.
 */
int gen_diff320(UINT64 Diff[25], unsigned int diff[320]);
int gen_diff320( vector<UINT64>& A, unsigned int diff[320]);

/** The first row of the matrix determine whether the input difference satifies the requirement of resulting in MSB 2-bit collision after chi.
 *  The second row of the matrix determine whether the input difference satisfies the requirement of resulting in MSB 3-bit collision after chi.
 */
void generateCheckCollistion160(bool checkCollision[32][2]);
void generateCheckCollistion224(bool checkCollision[32][2]);
#endif
