#ifndef _KKECCAK_H_
#define _KKECCAK_H_



#include <stdio.h>
#include <string.h>

typedef unsigned char UINT8;
typedef unsigned long long  UINT64;
typedef UINT64 tKeccakLane;

#define cKeccakB    1600

#define cKeccakLaneSizeInBits   (sizeof(tKeccakLane) * 8)/* 64*8 ??? */

#define index(x, y) (((x)%5)+5*((y)%5)) /* x + 5*y */
#define ROL64(a, offset) ((offset != 0) ? ((((UINT64)(a)) << offset) ^ (((UINT64)(a)) >> (64-offset))) : (a))
#define ROR64(a, offset) ((offset != 0) ? ((((UINT64)a) >> offset) ^ (((UINT64)a) << (64-offset))) : a)





int LFSR86540(UINT8 *LFSR);
void KeccakInitializeRoundConstants(); /* initialize RCs */
void KeccakInitializeRhoOffsets();
void displayStateAs64bitWords(const UINT64 *A);
void display1600Bits(unsigned int *A);
void theta(UINT64 *A);
void rho(UINT64 *A);
void pi(UINT64 *A);
void chi(UINT64 *A);
void iota(UINT64 *A, unsigned int indexRound);
void KeccakR(UINT64 *A, unsigned int indexRound);
void PrintKeccakR(const UINT64 *A, unsigned int indexRound);
void KeccakL(UINT64* A);

void inverseChi(UINT64* A);
void inverseTheta(UINT64* A);
void inversePi(UINT64* A);
void inverseRho(UINT64 *A);
void inverseIota(UINT64* A, unsigned int indexRound);
void inverseKeccakR(UINT64 *A, unsigned int indexRound);
void inverseKeccakL(UINT64* A);

void State2Bit(const UINT64 *A, unsigned int *B);
void Bit2State(unsigned int *B, UINT64 *A );
void XorDiff(UINT64 *A, UINT64 *B, UINT64 *C);
//Linear transformation
void Ltrans(UINT64 *A);
//Generate linear transformation
void generLT(char result[2560000]);
int is_collision(UINT64 *A, UINT64 *B);

#endif

