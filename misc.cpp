#include "misc.h"


using namespace std;

int Sbox(int a){
	int res=0;
	for (int i=0;i<5;i++){
		res=res^((a>>i&0x1)^(~((a>>(i+1)%5)&0x1))&((a>>(i+2)%5)&0x1))<<i;
	}
	return res;
}
/** The very classical DDT of an Sbox.
  */
int differential_distribution_table_origin(int DDT[32][32]){
	cout<<"for rev"<<endl;
	int din,x;
	for (int i=0;i<32;i++)
		for (int j=0; j<32; j++)
			DDT[i][j]=0;

	for (din=0; din<32; din++){
		for (x=0;x<32;x++){
			DDT[din][Sbox(x)^Sbox(x^din)]++;
		}
	}
	return 0;
}

/** This function ouput a DDT of possible output differences, i.e., the item of DDT[i] indicates how many input differences will lead to the output difference i.
 *  DDT[i][0] stores the number of compatible input differences.
 *  DDT[i][1], DDT[i][2], and etc list the corresponding compatible input differences.
 */
int differential_distribution_table(int DDT[32][32]){
	cout<<"for dir"<<endl;
	int din,dout, x, k, index;
	for (int i=0;i<32;i++)
		for (int j=0; j<32; j++)
			DDT[i][j]=0;
	for (int i=0;i<32;i++)
		DDT[i][0]=1;

	for (din=0; din<32; din++){
		for (x=0;x<32;x++){
			dout = Sbox(x)^Sbox(x^din);
			int flag = 0;
			for(k=1;k<32;k++){
				if(DDT[dout][k]==din) {flag = 1; break;}
			}
			if(flag==0){
				index = DDT[dout][0];
				DDT[dout][index] =  din;
				DDT[dout][0]++;
			}
		}
	}
	return 0;
}

//This function output a table that lists all possible output difference corresponding to associated input differences without considering the possibility of existence of each differential.
//For example, DDT[1][0]=5 (5-1 actually) gives the number of ouput differences in terms of 1 as input  difference
//DDT[1][1]=9 stores the actual value of the first output difference
//DDT[1][2]=19, DDT[1][3]=1 and DDT[1][4]=11 store the 2nd/3rd and 4th output differences respectively.
int differential_distribution_table_dir(int DDT[32][32]){
	int din,dout, x, k, index;
	for (int i=0;i<32;i++)//Initialize DDT
		for (int j=0; j<32; j++)
			DDT[i][j]=0;
	for (int i=0;i<32;i++)
		DDT[i][0]=1;

	for (din=0; din<32; din++){
		for (x=0;x<32;x++){
			dout = Sbox(x)^Sbox(x^din);
			int flag = 0;
			for(k=1;k<32;k++){
				if(DDT[din][k]==dout) {flag = 1; break;}//break jump out of one loop
			}
			if(flag==0){
				index = DDT[din][0];
				DDT[din][index] =  dout;
				DDT[din][0]++;
			}
		}
	}
	return 0;
}

int print_DDT(int DDT[32][32]){
	for (int i=0;i<32;i++){
		for (int j=0;j<32;j++){
			cout<<DDT[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}

int gen_diff320(UINT64 Diff[25], unsigned int diff[320])
{
    unsigned int B[1600];
    int i;
    State2Bit(Diff,B);
	int AS = 0;/*number of active sboxes*/

    for (i=0;i<320;i++){
	    diff[i]=B[i*5]^(B[i*5+1]<<1)^(B[i*5+2]<<2)^(B[i*5+3]<<3)^(B[i*5+4]<<4);
	    if(diff[i]) AS++;
    }
	return AS;
}
int gen_diff320( vector<UINT64>& A, unsigned int diff[320])
{
    int i,j, dout;
	int total_active = 0;

    for(i=0;i<320;i++){
        dout = 0;
        for(j=0;j<5;j++){
            dout ^= ((A[(i/64)*5 + j]>>(i%64))&0x1)<<j;//(B[5*i + j]<<j);
        }
		diff[i] = dout;
		total_active += (dout>0)?1:0;
    }
    return total_active;
}

//The table checkCollision stores the bool values that determine whether an input difference satisfies the requirement on collisions
void generateCheckCollistion160(bool checkCollision[32][2]) //for 160
{
	int DDT[32][32];
	differential_distribution_table_dir(DDT);
//    print_DDT(DDT);
	int i, j;
	bool flag;
	//check whether the input difference will result in an output difference that satisfies the MSB 2-bit as zero
	for(i=1; i<32; i++){
		flag = false;
		for(j=1; j<DDT[i][0]; j++){
			if((DDT[i][j]&0x18) == 0){
				flag = true;
				break;
			}
		}
		checkCollision[i][0] = flag;
	}

    //check whether the input difference will result in an output difference that satisfies the MSB 3-bit as zero
	for(i=1; i<32; i++){
		flag = false;
		for(j=1; j<DDT[i][0]; j++){
			if((DDT[i][j]&0x1c) == 0){
				flag = true;
				break;
			}
		}
		checkCollision[i][1] = flag;
	}
	checkCollision[0][0] = true;
	checkCollision[0][1] = true;
	
}

void generateCheckCollistion224(bool checkCollision[32][2]) //for 160
{
	int DDT[32][32];
	differential_distribution_table_dir(DDT);
	print_DDT(DDT);
	int i, j;
	bool flag;
	
	for(i=1; i<32; i++){
		flag = false;
		for(j=1; j<DDT[i][0]; j++){
			if((DDT[i][j]&0x7) == 0){
				flag = true;
				break;
			}
		}
		checkCollision[i][0] = flag;
	}
	
	for(i=1; i<32; i++){
		flag = false;
		for(j=1; j<DDT[i][0]; j++){
			if((DDT[i][j]&0xf) == 0){
				flag = true;
				break;
			}
		}
		checkCollision[i][1] = flag;
	}
	checkCollision[0][0] = true;
	checkCollision[0][1] = true;
	
}
