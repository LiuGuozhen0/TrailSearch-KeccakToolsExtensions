#include "inKernelSearch.h"


void generateValidSlicePattern(void)
{
  unsigned int slicePatternCase[12][6] = {
    {2,1,2,0,0,0},{3,1,1,1,0,0},//3-bit active slice
    {2,1,3,0,0,0},{2,2,2,0,0,0},{3,1,1,2,0,0},{4,1,1,1,1,0},//4-bit active slice
    {2,1,4,0,0,0},{2,2,3,0,0,0},{3,1,1,3,0,0},{3,1,2,2,0,0},{4,1,1,1,2,0},{5,1,1,1,1,1}//5-bit active slice
  };
  std::vector<unsigned int> set1 = {1, 2, 4, 8, 16};
  std::vector<unsigned int> set2 = {3, 5, 6, 9, 10, 12, 17, 18, 20, 24};
  std::vector<unsigned int> set3 = {7, 11, 13, 14, 19, 21, 22, 25, 26, 28};
  std::vector<unsigned int> set4 = {15, 23, 27, 29, 30};
  int DDTOutput[32][32];
  differential_distribution_table_dir(DDTOutput);
  // print_DDT(DDTOutput);

  int Case, nSbox;
  for (Case = 0; Case < 12; Case++) {
    cout << "Case " << Case << ": " << slicePatternCase[Case][0] << " active sboxes, " << endl;
    std::vector<std::vector<unsigned int> > activeSbox;
    for (nSbox = 1; nSbox <= slicePatternCase[Case][0]; nSbox++) {
      std::vector<unsigned int> Sbox;
      switch (slicePatternCase[Case][nSbox]) {
        case 1:
        for (int i = 0; i < set1.size(); i++) {
          Sbox.push_back(set1[i]);
        }
        break;
        case 2:
        for (int i = 0; i < set2.size(); i++) {
          Sbox.push_back(set2[i]);
        }
        break;
        case 3:
        for (int i = 0; i < set3.size(); i++) {
          Sbox.push_back(set3[i]);
        }
        break;
        default:
        for (int i = 0; i < set4.size(); i++) {
          Sbox.push_back(set4[i]);
        }
      }
      activeSbox.push_back(Sbox);
    }
    int i, j, k, m, n;
    int ii, jj, kk, mm, nn;
    switch (activeSbox.size()) {
      case 2:
      for (i = 0; i < activeSbox[0].size(); i++) {//the vector stores all possible input differences of the first active sbox
        for (j = 0; j < activeSbox[1].size(); j++) {//the vector stores all possible input differences of the second active sbox
          bool flag = 0;
          for (ii = 1; ii < DDTOutput[activeSbox[0][i]][0]; ii++) {//for each of the input difference, check all compatible output differences
            for (jj = 1; jj < DDTOutput[activeSbox[1][j]][0]; jj++) {
              unsigned int output1 = DDTOutput[activeSbox[0][i]][ii];
              unsigned int output2 = DDTOutput[activeSbox[1][j]][jj];
              if ((output1^output2)==0) {
                bitset<5> input1(activeSbox[0][i]);
                bitset<5> input2(activeSbox[1][j]);
                std::cout << input1 << "  " << input2 << endl;
                flag = 1;
                break;
              }
            }
            if (flag) {
              break;
            }
          }
        }
      }
      break;

      case 3:
      for (i = 0; i < activeSbox[0].size(); i++) {
        for (j = 0; j < activeSbox[1].size(); j++) {
          for ( k = 0; k < activeSbox[2].size(); k++) {
            bool flag = 0;
            for ( ii = 0; ii < DDTOutput[activeSbox[0][i]][0]; ii++) {
              for ( jj = 0; jj < DDTOutput[activeSbox[1][j]][0]; jj++) {
                for ( kk = 0; kk < DDTOutput[activeSbox[2][k]][0]; kk++) {
                  unsigned int output1 = DDTOutput[activeSbox[0][i]][ii];
                  unsigned int output2 = DDTOutput[activeSbox[1][j]][jj];
                  unsigned int output3 = DDTOutput[activeSbox[2][k]][kk];
                  unsigned int outputvalue = output1 ^ output2 ^ output3;
                  if (outputvalue == 0) {
                    // std::cout << output1 << "  " << output2 << "  " << output3 << endl;
                    bitset<5> input1(activeSbox[0][i]);
                    bitset<5> input2(activeSbox[1][j]);
                    bitset<5> input3(activeSbox[2][k]);
                    std::cout << input1 << "  " << input2 << "  " << input3 << endl;
                    flag = 1;
                    break;
                  }
                }
                if (flag) {
                  break;
                }
              }
              if (flag) {
                break;
              }
            }
          }
        }
      }
      break;

      case 4:
      for ( i = 0; i < activeSbox[0].size(); i++) {
        for ( j = 0; j < activeSbox[1].size(); j++) {
          for ( k = 0; k < activeSbox[2].size(); k++) {
            for ( m = 0; m < activeSbox[3].size(); m++) {
              bool flag = 0;
              for ( ii = 0; ii < DDTOutput[activeSbox[0][i]][0]; ii++) {
                for ( jj = 0; jj < DDTOutput[activeSbox[1][j]][0]; jj++) {
                  for ( kk = 0; kk < DDTOutput[activeSbox[2][k]][0]; kk++) {
                    for ( mm = 0; mm < DDTOutput[activeSbox[3][m]][0]; mm++) {
                      unsigned int output1 = DDTOutput[activeSbox[0][i]][ii];
                      unsigned int output2 = DDTOutput[activeSbox[1][j]][jj];
                      unsigned int output3 = DDTOutput[activeSbox[2][k]][kk];
                      unsigned int output4 = DDTOutput[activeSbox[3][m]][mm];
                      unsigned int outputvalue = output1 ^ output2 ^ output3 ^ output4;
                      if (outputvalue==0) {
                        bitset<5> input1(activeSbox[0][i]);
                        bitset<5> input2(activeSbox[1][j]);
                        bitset<5> input3(activeSbox[2][k]);
                        bitset<5> input4(activeSbox[3][m]);
                        std::cout << input1 << "  " << input2 << "  " << input3 << "  " << input4 << endl;
                        flag = 1;
                        break;
                      }
                    }
                    if (flag) {
                      break;
                    }
                  }
                  if (flag) {
                    break;
                  }
                }
                if (flag) {
                  break;
                }
              }
            }
          }
        }
      }
      break;

      default:
      for ( i = 0; i < activeSbox[0].size(); i++) {
        for ( j = 0; j < activeSbox[1].size(); j++) {
          for ( k = 0; k < activeSbox[2].size(); k++) {
            for ( m = 0; m < activeSbox[3].size(); m++) {
              for ( n = 0; n < activeSbox[4].size(); n++) {
                bool flag = 0;
                for ( ii = 0; ii < DDTOutput[activeSbox[0][i]][0]; ii++) {
                  for ( jj = 0; jj < DDTOutput[activeSbox[1][j]][0]; jj++) {
                    for ( kk = 0; kk < DDTOutput[activeSbox[2][k]][0]; kk++) {
                      for ( mm = 0; mm < DDTOutput[activeSbox[3][m]][0]; mm++) {
                        for ( nn = 0; nn < DDTOutput[activeSbox[4][n]][0]; nn++) {
                          unsigned int output1 = DDTOutput[activeSbox[0][i]][ii];
                          unsigned int output2 = DDTOutput[activeSbox[1][j]][jj];
                          unsigned int output3 = DDTOutput[activeSbox[2][k]][kk];
                          unsigned int output4 = DDTOutput[activeSbox[3][m]][mm];
                          unsigned int output5 = DDTOutput[activeSbox[4][n]][nn];
                          unsigned int outputvalue = output1 ^ output2 ^ output3 ^ output4 ^ output5;
                          if (outputvalue == 0) {
                            bitset<5> input1(activeSbox[0][i]);
                            bitset<5> input2(activeSbox[1][j]);
                            bitset<5> input3(activeSbox[2][k]);
                            bitset<5> input4(activeSbox[3][m]);
                            bitset<5> input5(activeSbox[4][n]);
                            std::cout << input1 << "  " << input2 << "  " << input3 << "  " << input4 << "  " << input5 << endl;
                            flag = 1;
                            break;
                          }
                        }
                        if (flag) {
                          break;
                        }
                      }
                      if (flag) {
                        break;
                      }
                    }
                    if (flag) {
                      break;
                    }
                  }
                  if (flag) {
                    break;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

// void printDifferences(unsigned int difference)
// {
//   int i, k;
//   for (i = 0; i < 5; i++) {
//     k = difference>>
//   }
// }
