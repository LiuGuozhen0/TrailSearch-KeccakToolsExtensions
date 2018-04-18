#include "inKernelSearch.h"


void generateValidSliceValuePattern(void)
{
  unsigned int slicePatternCase[CASENUMBER][6] = {
    {2,1,1,0,0,0},//2-bit active slice, orbitals
    {2,1,2,0,0,0},{3,1,1,1,0,0},//3-bit active slice, 2 kinds
    {2,1,3,0,0,0},{2,2,2,0,0,0},{3,1,1,2,0,0},{4,1,1,1,1,0},//4-bit active slice, 4 kinds
    {2,1,4,0,0,0},{2,2,3,0,0,0},{3,1,1,3,0,0},{3,1,2,2,0,0},{4,1,1,1,2,0},{5,1,1,1,1,1},//5-bit active slice, 6 kinds
    {2,1,5,0,0,0},{2,2,4,0,0,0},{2,3,3,0,0,0},{3,1,1,4,0,0},{3,1,2,3,0,0},{3,2,2,2,0,0},{4,1,1,1,3,0},{4,1,1,2,2,0},{5,1,1,1,1,2}//6-bit active slice, 9 kinds
  };
  std::vector<unsigned int> set1{1, 2, 4, 8, 16};
  std::vector<unsigned int> set2{3, 5, 6, 9, 10, 12, 17, 18, 20, 24};
  std::vector<unsigned int> set3{7, 11, 13, 14, 19, 21, 22, 25, 26, 28};
  std::vector<unsigned int> set4{15, 23, 27, 29, 30};
  std::vector<unsigned int> set5{31};
  int DDTOutput[32][32];
  differential_distribution_table_dir(DDTOutput);
  // print_DDT(DDTOutput);

  int Case, nSbox;
  for (Case = 0; Case < CASENUMBER; Case++) {
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
        case 4:
        for (int i = 0; i < set4.size(); i++) {
          Sbox.push_back(set4[i]);
        }
        break;
        default:
        for (int i = 0; i < set5.size(); i++) {
          Sbox.push_back(set5[i]);
        }
      }
      activeSbox.push_back(Sbox);
    }
    int i, j, k, m, n;
    int ii, jj, kk, mm, nn;
    switch (activeSbox.size()) {
      case 2:
      {
        set <multiset <unsigned int, greater <unsigned int> > > Set2;
        for (i = 0; i < activeSbox[0].size(); i++) {//the vector stores all possible input differences of the first active sbox
          for (j = 0; j < activeSbox[1].size(); j++) {//the vector stores all possible input differences of the second active sbox
            bool flag = 0;
            for (ii = 1; ii < DDTOutput[activeSbox[0][i]][0]; ii++) {//for each of the input difference, check all compatible output differences
              for (jj = 1; jj < DDTOutput[activeSbox[1][j]][0]; jj++) {
                unsigned int output1 = DDTOutput[activeSbox[0][i]][ii];
                unsigned int output2 = DDTOutput[activeSbox[1][j]][jj];
                if ((output1^output2)==0) {
                  multiset <unsigned int, greater <unsigned int> > validSlice;
                  validSlice.insert(activeSbox[0][i]);
                  validSlice.insert(activeSbox[1][j]);
                  Set2.insert(validSlice);
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
        set <multiset <unsigned int, greater <unsigned int> > > :: iterator itSet2;
        for ( itSet2 = Set2.begin(); itSet2 != Set2.end(); itSet2++) {
          multiset <unsigned int, greater <unsigned int> > :: iterator it2;
          for ( it2 = (*itSet2).begin(); it2 != (*itSet2).end(); it2++) {
            bitset<5> input(*it2);
            cout << " " << input;
          }
          std::cout << endl;
        }
      }
      break;

      case 3:
      {
        set <multiset <unsigned int, greater <unsigned int> > > Set3;
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
                      multiset <unsigned int, greater <unsigned int> > validSlice;
                      validSlice.insert(activeSbox[0][i]);
                      validSlice.insert(activeSbox[1][j]);
                      validSlice.insert(activeSbox[2][k]);
                      Set3.insert(validSlice);
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
        set <multiset <unsigned int, greater <unsigned int> > > :: iterator itSet3;
        for ( itSet3 = Set3.begin(); itSet3 != Set3.end(); ++itSet3) {
          multiset <unsigned int, greater <unsigned int> > :: iterator it3;
          for ( it3 = (*itSet3).begin(); it3 != (*itSet3).end(); ++it3) {
            bitset<5> input(*it3);
            cout << " " << input;
          }
          cout << endl;
        }
      }
      break;

      case 4:
      {
        set <multiset <unsigned int, greater <unsigned int> > > Set4;
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
                          multiset <unsigned int, greater<unsigned int> > validSlice;
                          validSlice.insert(activeSbox[0][i]);
                          validSlice.insert(activeSbox[1][j]);
                          validSlice.insert(activeSbox[2][k]);
                          validSlice.insert(activeSbox[3][m]);
                          Set4.insert(validSlice);
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
        set <multiset <unsigned int, greater <unsigned int> > > :: iterator itSet4;
        for ( itSet4 = Set4.begin(); itSet4 != Set4.end(); ++itSet4) {
          multiset <unsigned int, greater <unsigned int> > :: iterator it4;
          for ( it4 = (*itSet4).begin(); it4 != (*itSet4).end(); ++it4) {
            bitset<5> input(*it4);
            cout << " " << input;
          }
          cout << endl;
        }
      }//The statement within a case clause must be one block
      break;

      default:
      set <multiset <unsigned int, greater <unsigned int> > > Set5;
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
                            multiset <unsigned int, greater <unsigned int> > validSlice;
                            // multiset <unsigned int, greater <unsigned int>> :: iterator it5;
                            validSlice.insert(activeSbox[0][i]);
                            validSlice.insert(activeSbox[1][j]);
                            validSlice.insert(activeSbox[2][k]);
                            validSlice.insert(activeSbox[3][m]);
                            validSlice.insert(activeSbox[4][n]);
                            // for ( it5 = validSlice.begin(); it5 != validSlice.end(); ++it5) {
                            //   bitset<5> input(*it5);
                            //   cout << "  " << input;
                            // }
                            // cout << endl;
                            Set5.insert(validSlice);
                            //bitset<5> input1(activeSbox[0][i]);
                            //bitset<5> input2(activeSbox[1][j]);
                            // bitset<5> input3(activeSbox[2][k]);
                            // bitset<5> input4(activeSbox[3][m]);
                            // bitset<5> input5(activeSbox[4][n]);
                            //std::cout << input1 << "  " << input2 << "  " << input3 << "  " << input4 << "  " << input5 << endl;
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
      set <multiset <unsigned int, greater <unsigned int> > > :: iterator itSet5;
      for ( itSet5 = Set5.begin(); itSet5 != Set5.end(); ++itSet5) {
        multiset <unsigned int, greater <unsigned int> > :: iterator it5;
        for ( it5 = (*itSet5).begin(); it5 != (*itSet5).end(); ++it5) {
          bitset<5> input(*it5);
          cout << "  " << input;
        }
        cout << endl;
      }
    }
  }
}

void genInputforAllActiveSbox(DualVector& slicePatternCase,TriVector& activeSboxAllCase) {
  std::vector<unsigned int> set1{1, 2, 4, 8, 16};
  std::vector<unsigned int> set2{3, 5, 6, 9, 10, 12, 17, 18, 20, 24};
  std::vector<unsigned int> set3{7, 11, 13, 14, 19, 21, 22, 25, 26, 28};
  std::vector<unsigned int> set4{15, 23, 27, 29, 30};
  std::vector<unsigned int> set5{31};

  int Case, nSbox;

  for (Case = 0; Case < slicePatternCase.size(); Case++) {
    DualVector activeSbox;
    for (nSbox = 0; nSbox <= slicePatternCase[Case].size(); nSbox++) {
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
        case 4:
        for (int i = 0; i < set4.size(); i++) {
          Sbox.push_back(set4[i]);
        }
        break;
        default:
        for (int i = 0; i < set5.size(); i++) {
          Sbox.push_back(set5[i]);
        }
      }
      activeSbox.push_back(Sbox);
    }
    activeSboxAllCase.push_back(activeSbox);
  }
}

void printValueSlicePattern(multisetSet& valuePattern){
  cout << valuePattern.size() << " value patterns in total!" << endl;
  multisetSet :: iterator itSet;
  for ( itSet = valuePattern.begin(); itSet != valuePattern.end(); itSet++) {
    multiset <unsigned int, greater <unsigned int> > :: iterator it;
    for ( it = (*itSet).begin(); it != (*itSet).end(); it++) {
      bitset<5> input(*it);
      cout << " " << input;
    }
    cout << endl;
  }
}

void twoSboxValuePatternSearch(TriVector& activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern2){
  int i, j, ii, jj;
  int cases;
  for ( cases = 0; cases < activeSboxAllCase.size(); cases++) {
    for (i = 0; i < activeSboxAllCase[cases][0].size(); i++) {//the vector stores all possible input differences of the first active sbox
      for (j = 0; j < activeSboxAllCase[cases][1].size(); j++) {//the vector stores all possible input differences of the second active sbox
        bool flag = 0;
        for (ii = 1; ii < DDTOutput[activeSboxAllCase[cases][0][i]][0]; ii++) {//for each of the input difference, check all compatible output differences
          for (jj = 1; jj < DDTOutput[activeSboxAllCase[cases][1][j]][0]; jj++) {
            unsigned int output1 = DDTOutput[activeSboxAllCase[cases][0][i]][ii];
            unsigned int output2 = DDTOutput[activeSboxAllCase[cases][1][j]][jj];
            if ((output1^output2)==0) {
              multiset <unsigned int, greater <unsigned int> > validSlice;
              validSlice.insert(activeSboxAllCase[cases][0][i]);
              validSlice.insert(activeSboxAllCase[cases][1][j]);
              valuePattern2.insert(validSlice);
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
  }
  // printValueSlicePattern(valuePattern2);
}

void threeSboxValuePatternSearch(TriVector& activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern3){
  int i, j, k, ii, jj, kk;
  int cases;
  for ( cases = 0; cases < activeSboxAllCase.size(); cases++) {
    for (i = 0; i < activeSboxAllCase[cases][0].size(); i++) {
      for (j = 0; j < activeSboxAllCase[cases][1].size(); j++) {
        for ( k = 0; k < activeSboxAllCase[cases][2].size(); k++) {
          bool flag = 0;
          for ( ii = 0; ii < DDTOutput[activeSboxAllCase[cases][0][i]][0]; ii++) {
            for ( jj = 0; jj < DDTOutput[activeSboxAllCase[cases][1][j]][0]; jj++) {
              for ( kk = 0; kk < DDTOutput[activeSboxAllCase[cases][2][k]][0]; kk++) {
                unsigned int output1 = DDTOutput[activeSboxAllCase[cases][0][i]][ii];
                unsigned int output2 = DDTOutput[activeSboxAllCase[cases][1][j]][jj];
                unsigned int output3 = DDTOutput[activeSboxAllCase[cases][2][k]][kk];
                unsigned int outputvalue = output1 ^ output2 ^ output3;
                if (outputvalue == 0) {
                  multiset <unsigned int, greater <unsigned int> > validSlice;
                  validSlice.insert(activeSboxAllCase[cases][0][i]);
                  validSlice.insert(activeSboxAllCase[cases][1][j]);
                  validSlice.insert(activeSboxAllCase[cases][2][k]);
                  valuePattern3.insert(validSlice);
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
  }
  // printValueSlicePattern(valuePattern3);
}


void fourSboxValuePatternSearch(TriVector& activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern4){
  int i, j, k, m, ii, jj, kk, mm;
  int cases;
  for ( cases = 0; cases < activeSboxAllCase.size(); cases++) {
    for ( i = 0; i < activeSboxAllCase[cases][0].size(); i++) {
      for ( j = 0; j < activeSboxAllCase[cases][1].size(); j++) {
        for ( k = 0; k < activeSboxAllCase[cases][2].size(); k++) {
          for ( m = 0; m < activeSboxAllCase[cases][3].size(); m++) {
            bool flag = 0;
            for ( ii = 0; ii < DDTOutput[activeSboxAllCase[cases][0][i]][0]; ii++) {
              for ( jj = 0; jj < DDTOutput[activeSboxAllCase[cases][1][j]][0]; jj++) {
                for ( kk = 0; kk < DDTOutput[activeSboxAllCase[cases][2][k]][0]; kk++) {
                  for ( mm = 0; mm < DDTOutput[activeSboxAllCase[cases][3][m]][0]; mm++) {
                    unsigned int output1 = DDTOutput[activeSboxAllCase[cases][0][i]][ii];
                    unsigned int output2 = DDTOutput[activeSboxAllCase[cases][1][j]][jj];
                    unsigned int output3 = DDTOutput[activeSboxAllCase[cases][2][k]][kk];
                    unsigned int output4 = DDTOutput[activeSboxAllCase[cases][3][m]][mm];
                    unsigned int outputvalue = output1 ^ output2 ^ output3 ^ output4;
                    if (outputvalue==0) {
                      multiset <unsigned int, greater<unsigned int> > validSlice;
                      validSlice.insert(activeSboxAllCase[cases][0][i]);
                      validSlice.insert(activeSboxAllCase[cases][1][j]);
                      validSlice.insert(activeSboxAllCase[cases][2][k]);
                      validSlice.insert(activeSboxAllCase[cases][3][m]);
                      valuePattern4.insert(validSlice);
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
  }
  // printValueSlicePattern(valuePattern4);
}


void fiveSboxValuePatternSearch(TriVector& activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern5){
  int i, j, k, m, n, ii, jj, kk, mm, nn;
  int cases;
  for ( cases = 0; cases < activeSboxAllCase.size(); cases++) {
    for ( i = 0; i < activeSboxAllCase[cases][0].size(); i++) {
      for ( j = 0; j < activeSboxAllCase[cases][1].size(); j++) {
        for ( k = 0; k < activeSboxAllCase[cases][2].size(); k++) {
          for ( m = 0; m < activeSboxAllCase[cases][3].size(); m++) {
            for ( n = 0; n < activeSboxAllCase[cases][4].size(); n++) {
              bool flag = 0;
              for ( ii = 0; ii < DDTOutput[activeSboxAllCase[cases][0][i]][0]; ii++) {
                for ( jj = 0; jj < DDTOutput[activeSboxAllCase[cases][1][j]][0]; jj++) {
                  for ( kk = 0; kk < DDTOutput[activeSboxAllCase[cases][2][k]][0]; kk++) {
                    for ( mm = 0; mm < DDTOutput[activeSboxAllCase[cases][3][m]][0]; mm++) {
                      for ( nn = 0; nn < DDTOutput[activeSboxAllCase[cases][4][n]][0]; nn++) {
                        unsigned int output1 = DDTOutput[activeSboxAllCase[cases][0][i]][ii];
                        unsigned int output2 = DDTOutput[activeSboxAllCase[cases][1][j]][jj];
                        unsigned int output3 = DDTOutput[activeSboxAllCase[cases][2][k]][kk];
                        unsigned int output4 = DDTOutput[activeSboxAllCase[cases][3][m]][mm];
                        unsigned int output5 = DDTOutput[activeSboxAllCase[cases][4][n]][nn];
                        unsigned int outputvalue = output1 ^ output2 ^ output3 ^ output4 ^ output5;
                        if (outputvalue == 0) {
                          multiset <unsigned int, greater <unsigned int> > validSlice;
                          validSlice.insert(activeSboxAllCase[cases][0][i]);
                          validSlice.insert(activeSboxAllCase[cases][1][j]);
                          validSlice.insert(activeSboxAllCase[cases][2][k]);
                          validSlice.insert(activeSboxAllCase[cases][3][m]);
                          validSlice.insert(activeSboxAllCase[cases][4][n]);
                          valuePattern5.insert(validSlice);
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
  // printValueSlicePattern(valuePattern5);
}


void generateValidSliceValuePattern(unsigned int nBit, set <multiset <unsigned int, greater <unsigned int> > > & patternSet) {
  int DDTOutput[32][32];
  differential_distribution_table_dir(DDTOutput);

  switch (nBit) {
    case 2:
    {
      DualVector twoBitSlice{{1,1}};
      TriVector activeSbox;
      genInputforAllActiveSbox(twoBitSlice,activeSbox);
      twoSboxValuePatternSearch(activeSbox, DDTOutput, patternSet);
    }
    break;

    case 3:
    {
      DualVector twoSboxSlice{{1,2}};
      TriVector activeSbox2;
      DualVector threeSboxSlice{{1,1,1}};
      TriVector activeSbox3;
      genInputforAllActiveSbox(twoSboxSlice, activeSbox2);
      genInputforAllActiveSbox(threeSboxSlice, activeSbox3);
      twoSboxValuePatternSearch(activeSbox2, DDTOutput, patternSet);
      threeSboxValuePatternSearch(activeSbox3, DDTOutput, patternSet);
    }
    break;

    case 4:
    {
      DualVector twoSboxSlice{{1,3},{2,2}};
      TriVector activeSbox2;
      DualVector threeSboxSlice{{1,1,2}};
      TriVector activeSbox3;
      DualVector fourSboxSlice{{1,1,1,1}};
      TriVector activeSbox4;
      genInputforAllActiveSbox(twoSboxSlice, activeSbox2);
      genInputforAllActiveSbox(threeSboxSlice, activeSbox3);
      genInputforAllActiveSbox(fourSboxSlice, activeSbox4);
      twoSboxValuePatternSearch(activeSbox2, DDTOutput, patternSet);
      threeSboxValuePatternSearch(activeSbox3, DDTOutput, patternSet);
      fourSboxValuePatternSearch(activeSbox4, DDTOutput, patternSet);
    }
    break;

    case 5:
    {
      DualVector twoSboxSlice{{1,4},{2,3}};
      TriVector activeSbox2;
      DualVector threeSboxSlice{{1,1,3},{1,2,2}};
      TriVector activeSbox3;
      DualVector fourSboxSlice{{1,1,1,2}};
      TriVector activeSbox4;
      DualVector fiveSboxSlice{{1,1,1,1,1}};
      TriVector activeSbox5;
      genInputforAllActiveSbox(twoSboxSlice, activeSbox2);
      genInputforAllActiveSbox(threeSboxSlice, activeSbox3);
      genInputforAllActiveSbox(fourSboxSlice, activeSbox4);
      genInputforAllActiveSbox(fiveSboxSlice, activeSbox5);
      twoSboxValuePatternSearch(activeSbox2, DDTOutput, patternSet);
      threeSboxValuePatternSearch(activeSbox3, DDTOutput, patternSet);
      fourSboxValuePatternSearch(activeSbox4, DDTOutput, patternSet);
      fiveSboxValuePatternSearch(activeSbox5, DDTOutput, patternSet);
    }
    break;
    default:
    ;
  }
}



/*
  * This is toy code for searching vortex of 2 peers.
  * This test function is written for better implementation of in kernel trail core search.
  */

void vectorOf2Peers(void) {
  unsigned int offset[5][5] = {//[x][y] fashion, my state is [y][x]fashion
        {0, 36, 3, 41, 18},
        {1, 44, 10, 45, 2},
        {62, 6, 43, 15, 61},
        {28, 55, 25, 21, 56},
        {27, 20, 39, 8, 14}
    };
    set <multiset <unsigned int, greater <unsigned int> > > sliceValuePattern2;
    generateValidSliceValuePattern(2, sliceValuePattern2);
    printValueSlicePattern(sliceValuePattern2);

    // multisetSet sliceValuePattern3;
    // generateValidSliceValuePattern(3, sliceValuePattern3);
    // printValueSlicePattern(sliceValuePattern3);
    //
    // multisetSet sliceValuePattern4;
    // generateValidSliceValuePattern(4, sliceValuePattern4);
    // printValueSlicePattern(sliceValuePattern4);

    // multisetSet sliceValuePattern5;
    // generateValidSliceValuePattern(5, sliceValuePattern5);
    // printValueSlicePattern(sliceValuePattern5);
}
