#include "kkeccak.h"

UINT64 KeccakRoundConstants[24];/* define a public list to store RCs */
unsigned int KeccakRhoOffsets[25];/* define a public list to store offsets of rho */

int LFSR86540(UINT8 *LFSR)/* Algorithm 5 - FIPS202 */
{
	int result = ((*LFSR) & 0x01) != 0;
	if (((*LFSR) & 0x80) != 0)
		// Primitive polynomial over GF(2): x^8+x^6+x^5+x^4+1
		(*LFSR) = ((*LFSR) << 1) ^ 0x71;
	else
		(*LFSR) <<= 1;
	return result;
}

void KeccakInitializeRoundConstants()/* initialize RCs */
{
	UINT8 LFSRstate = 0x01;
	unsigned int i, j, bitPosition;

	for(i=0; i<24; i++) {
		KeccakRoundConstants[i] = 0;
		for(j=0; j<7; j++) {
			bitPosition = (1<<j)-1; //2^j-1
			if(LFSR86540(&LFSRstate))
				KeccakRoundConstants[i] ^= (UINT64)1<<bitPosition;
		}
	}
}


/* initialize offsets of rho  */
void KeccakInitializeRhoOffsets()
{
	unsigned int x, y, t, newX, newY;

	KeccakRhoOffsets[index(0, 0)] = 0;
	x = 1;
	y = 0;
	for(t=0; t<24; t++) {
		KeccakRhoOffsets[index(x, y)] = ((t+1)*(t+2)/2) % 64;
		newX = (0*x+1*y) % 5;
		newY = (2*x+3*y) % 5;
		x = newX;
		y = newY;
	}
}

/* display the state as 32-bit words, as "%X" is only permitted for 32-bit words and no formatted output for 64-bit words */
void displayStateAs64bitWords(const UINT64 *A)
{
	unsigned int i, j;

	for(i=0; i<5; i++){
		for(j=0; j<5; j++){
			/*printf("%X",A[index(i,j)]);*/
			printf("%08X%08X, ", (unsigned int)(A[i*5+j] >> 32),(unsigned int)(A[i*5+j] & 0xFFFFFFFFULL));
		}
		printf("\n");
	}
	printf("\n");
}

/* display the state as 5 rows of bits. A has 1600 items and each item is 0 or 1. */
void display1600Bits(unsigned int *A)
{
	unsigned int i;

	for(i=0; i<1600; i++){
		if(i%320 == 0){ printf("\n");}
		printf("%X", A[i]&01);
	}
	printf("\n");
}

/* five transformations in a round of Keccak permutation */
void theta(UINT64 *A)
{
	unsigned int x, y;
	UINT64 C[5], D[5];

	for(x=0; x<5; x++) {
		C[x] = 0; 
		for(y=0; y<5; y++) 
			C[x] ^= A[index(x, y)];
	}
	for(x=0; x<5; x++)
		D[x] = ROL64(C[(x+1)%5], 1) ^ C[(x+4)%5];
	for(x=0; x<5; x++)
		for(y=0; y<5; y++)
			A[index(x, y)] ^= D[x];
}

void rho(UINT64 *A)
{
	unsigned int x, y;

	for(x=0; x<5; x++) for(y=0; y<5; y++)
		A[index(x, y)] = ROL64(A[index(x, y)], KeccakRhoOffsets[index(x, y)]);
}

void pi(UINT64 *A)
{
	unsigned int x, y;
	UINT64 tempA[25];

	for(x=0; x<5; x++) for(y=0; y<5; y++)
		tempA[index(x, y)] = A[index(x, y)];
	for(x=0; x<5; x++) for(y=0; y<5; y++)
		A[index((0*x+1*y)%5, (2*x+3*y)%5)] = tempA[index(x, y)];
}

void chi(UINT64 *A)
{
	unsigned int x, y;
	UINT64 C[5];

	for(y=0; y<5; y++) { 
		for(x=0; x<5; x++)
			C[x] = A[index(x, y)] ^ ((~A[index(x+1, y)]) & A[index(x+2, y)]);
		for(x=0; x<5; x++)
			A[index(x, y)] = C[x];
	}
}

void iota(UINT64 *A, unsigned int indexRound)
{
	A[index(0, 0)] ^= KeccakRoundConstants[indexRound];
}

void inverseChi(UINT64* A)
{
	for(unsigned int y=0; y<5; y++) {
		unsigned int length = 5;
		UINT64 C[5];
		for(unsigned int x=0; x<length; x++) 
			C[x] = A[index(x,y)];
		for(unsigned int x=0; x<(3*(length-1)/2); x++) {
			unsigned int X = (length-2)*x;
			A[index(X,y)] = C[X%5] ^ (A[index(X+2,y)] & (~C[(X+1)%5]));
		}
	}
}

void inverseTheta(UINT64* A)
{
	const unsigned int laneSize = 64;
	UINT64 C[5];
	for(unsigned int x=0; x<5; x++) {
		C[x] = A[index(x,0)];
		for(unsigned int y=1; y<5; y++){
			C[x] ^= A[index(x,y)];
		}
	}
	const UINT64 inversePositions64[5] = {
		0xDE26BC4D789AF134ULL,
		0x09AF135E26BC4D78ULL,
		0xEBC4D789AF135E26ULL,
		0x7135E26BC4D789AFULL,
		0xCD789AF135E26BC4ULL };
	UINT64 inversePositions[5] = { 0 };
	for(unsigned int z=0; z<64; z+=laneSize)
		for(unsigned int x=0; x<5; x++)
			inversePositions[x] ^= inversePositions64[x] >> z;
	for(unsigned int z=0; z<laneSize; z++) {
		for(unsigned int xOff=0; xOff<5; xOff++)
			for(int x=0; x<5; x++)
				for(unsigned int y=0; y<5; y++)
					if ((inversePositions[xOff] & 1) != 0)
						A[index(x, y)] ^= C[(x-xOff+5)%5];
		for(unsigned int xOff=0; xOff<5; xOff++) {
			C[xOff] = ROL64(C[xOff], 1);
			inversePositions[xOff] >>= 1;
		}
	}
}

void inversePi(UINT64* A)
{
	unsigned int x, y;
	UINT64 tempA[25];
	for(x=0; x<5; x++) for(y=0; y<5; y++)
		tempA[index(x, y)] = A[index(x, y)];
	for(x=0; x<5; x++) for(y=0; y<5; y++)
		A[index(x, y)] = tempA[index(0*x+1*y, 2*x+3*y)];
}

void inverseRho(UINT64 *A)
{
	unsigned int x, y;

	for(x=0; x<5; x++) for(y=0; y<5; y++)
		A[index(x, y)] = ROR64(A[index(x, y)], KeccakRhoOffsets[index(x, y)]);
}

void inverseIota(UINT64* A, unsigned int indexRound){
	iota(A, indexRound);
}

/* a round of Keccak permutation */
void KeccakR(UINT64 *A, unsigned int indexRound)
{
	theta(A);
	rho(A);
	pi(A);
	chi(A);
	iota(A, indexRound);
}

void PrintKeccakR(const UINT64 *A, unsigned int indexRound)
{
	UINT64 B[25];
	memcpy(B, A, sizeof(B));
	printf("Before Theta:\n"); displayStateAs64bitWords(B);
	theta(B);
	printf("Bfter Theta:\n"); displayStateAs64bitWords(B);
	rho(B);
	printf("Bfter Rho:\n"); displayStateAs64bitWords(B);
	pi(B);
	printf("Bfter Pi:\n"); displayStateAs64bitWords(B);
	chi(B);
	printf("Bfter Chi:\n"); displayStateAs64bitWords(B);
	iota(B, indexRound);
	printf("Bfter iota:\n"); displayStateAs64bitWords(B);
}

void KeccakL(UINT64* A)
{
	theta(A);
	rho(A);
	pi(A);
}

void inverseKeccakL(UINT64* A)
{
	inversePi(A);
	inverseRho(A);
	inverseTheta(A);
}

void inverseKeccakR(UINT64 *A, unsigned int indexRound)
{
	inverseIota(A, indexRound);
	inverseChi(A);
	inversePi(A);
	inverseRho(A);
	inverseTheta(A);
}
/* A[25]--> B[1600]*/
void State2Bit(const UINT64 *A, unsigned int *B)
{
	unsigned int i, j;
	for(i = 0; i < 5; i++){
		for(j = 0; j < 64; j++){
			B[320*i+5*j] = (A[5*i] >> (63-j) & 0x01);
			B[320*i+5*j+1] = (A[5*i+1] >> (63-j) & 0x01);
			B[320*i+5*j+2] = (A[5*i+2] >> (63-j) & 0x01);
			B[320*i+5*j+3] = (A[5*i+3] >> (63-j) & 0x01);
			B[320*i+5*j+4] = (A[5*i+4] >> (63-j) & 0x01);
		}
	}
}

/* A[25]--> B[1600]*/
void Bit2State(unsigned int *B, UINT64 *A )
{
	unsigned int i, j;
	for(i = 0; i < 5; i++){
		A[5*i] = 0;
		A[5*i+1] = 0;
		A[5*i+2] = 0;
		A[5*i+3] = 0;
		A[5*i+4] = 0;
		for(j = 0; j < 64; j++){
			A[5*i] |= ((UINT64)(B[320*i+5*j]) << (63-j));
			A[5*i+1] |= ((UINT64)(B[320*i+5*j+1]) << (63-j));
			A[5*i+2] |= ((UINT64)(B[320*i+5*j+2]) << (63-j));
			A[5*i+3] |= ((UINT64)(B[320*i+5*j+3]) << (63-j));
			A[5*i+4] |= ((UINT64)(B[320*i+5*j+4]) << (63-j));
		}
	}
}



/* xor-difference of state A and B, and output the difference */
void XorDiff(UINT64 *A, UINT64 *B, UINT64 *C)
{  
	unsigned int i;
	for(i = 0; i< 25; i++){
		C[i] = A[i]^B[i];
	}
	//displayStateAs64bitWords(C);
	/*State2Bit(C,D);
	  display1600Bits(D);*/
}

/* L=pi\circle rho \circle theta */
void Ltrans(UINT64 *A)
{
	theta(A);
	rho(A);
	pi(A);
}

/** Generate the matrix expression of L=pi\circle rho \circle theta, and store it in L.txt
 */
void generLT(char result[2560000])
{
	unsigned int A[1600] = {0};
	//char result[1600*1600];
	UINT64 temp[25] = {0};
	unsigned int i, j, k;

	FILE *fp;  

	for(i = 0; i < 1600; i++){ A[i] = 0;}

	k =0;
	for(i = 0; i < 1600; i++){
		A[i] = 1;
		Bit2State(A,temp);
		Ltrans(temp);
		State2Bit(temp,A);
		k += A[0];
		for(j = 0; j < 1600; j++){
			if(A[j]==0){
				result[1600*j + i] = '0';
			}
			else{
				result[1600*j + i] = '1';
			}
			//result[j][i] = ((unsigned short)A[j]);
			A[j] = 0;
		}
	} 

	//printf("every row of L has %d nonzeros.\n",k);


}


int is_collision(UINT64 *A, UINT64 *B)
{
#if (KECCAK==224)
	if( (A[0]==B[0]) && (A[1]==B[1]) && (A[2]==B[2]) && ( (A[3]&0xFFFFFFFF) == (B[3]&0xFFFFFFFF) ) )//RIGHT HALF
#elif	(KECCAK==160)
	if( (A[0]==B[0]) && (A[1]==B[1]) && ( (A[2]&0xFFFFFFFF) == (B[2]&0xFFFFFFFF) ) )//RIGHT HALF
#elif (KECCAK==128)
	if( (A[0]==B[0]) && (A[1]==B[1]) && (A[2]==B[2]) && (A[3]==B[3]))	// assume 256-bit digest
#endif
	{   
		printf("M1 after the 4-th rounds is:\n");
		displayStateAs64bitWords(A);
		printf("M2 after the 4-th rounds is:\n");
		displayStateAs64bitWords(B);
		UINT64 C[25];
		XorDiff(A, B, C);
		printf("the diff after the 4-th rounds is:\n");
		displayStateAs64bitWords(C);
		return 1;
	}
	return 0;
}




