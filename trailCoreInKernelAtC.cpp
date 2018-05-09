#include "trailCoreInKernelAtC.h"

myTrailCoreInKernelAtC::myTrailCoreInKernelAtC(){
  // slicePatternCounter = 0;
  // statePatternWithDuplication;
  // statePatternDistanceCheckSpace;
  // statePatternWithoutDistanceCheck;


  // v1 = 0; v2 = 0; v3 = 0; v4 = 0; v5 = 0;
  // sliceValuePattern2, sliceValuePattern3, sliceValuePattern4, sliceValuePattern5;
  //
  // oneValuePattern;
  //
  // aP1, aQ1, aP2, aQ2, aP3, aQ3, aP4, aQ4, aP5, aQ5;
  // bP1, bQ1, bP2, bQ2, bP3, bQ3, bP4, bQ4, bP5, bQ5;
}

myTrailCoreInKernelAtC::~myTrailCoreInKernelAtC(){
  // ;
}

void myTrailCoreInKernelAtC::genInputforAllActiveSbox(DualVector slicePatternCase,TriVector& activeSboxAllCase) {
  std::vector<unsigned int> set1{1, 2, 4, 8, 16};
  std::vector<unsigned int> set2{3, 5, 6, 9, 10, 12, 17, 18, 20, 24};
  std::vector<unsigned int> set3{7, 11, 13, 14, 19, 21, 22, 25, 26, 28};
  std::vector<unsigned int> set4{15, 23, 27, 29, 30};
  std::vector<unsigned int> set5{31};

  int Case, nSbox;
  //each case indicates 1)number of active sboxes 2)number of bits within each Sbox
  //e.g., "slicePatternCase" stores {{1,3},{2,2},{1,1,2},{1,1,1,1}}, 4 possible cases
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

void myTrailCoreInKernelAtC::printValueSlicePattern(multisetSet valuePattern){
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

void myTrailCoreInKernelAtC::twoSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern2){
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

void myTrailCoreInKernelAtC::threeSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern3){
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


void myTrailCoreInKernelAtC::fourSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern4){
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

void myTrailCoreInKernelAtC::fiveSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern5){
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

void myTrailCoreInKernelAtC::generateValidSliceValuePattern(unsigned int nBit, multisetSet& patternSet) {
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

void myTrailCoreInKernelAtC::inversePi(unsigned int X, unsigned int Y, unsigned int & x, unsigned int & y){
  x = (1*X + 3*Y)%5;
  y = (1*X + 0*Y)%5;
}

void myTrailCoreInKernelAtC::Pi(unsigned int x, unsigned int y, unsigned int & X, unsigned int & Y){
  X = (0*x + 1*y)%5;
  Y = (2*x + 3*y)%5;
}

void myTrailCoreInKernelAtC::determineXforStartingSlice2Bits(ValuePatternmultiset oneValuePattern, BitPosition & bQ1, BitPosition & bP2){
  int sboxCounter = 0;
  ValuePatternmultiset :: iterator sboxiterator;
  for ( sboxiterator = oneValuePattern.begin(); sboxiterator != oneValuePattern.end(); sboxiterator++) {
    for (int bitIndicator = 0; bitIndicator < 5; bitIndicator++) {
      if (((*sboxiterator) >> bitIndicator) & 1) {
        if (sboxCounter == 0) {
          bQ1.x = bitIndicator;
        }
        if (sboxCounter == 1) {
          bP2.x = bitIndicator;
        }
      }
    }
    sboxCounter++;
  }
  return;
}

bool myTrailCoreInKernelAtC::validPatterFilter2Bits(BitPosition bP, BitPosition bQ){
  if ((bP.x == bQ.x) && (bP.y != bQ.y))
  return true;
  else
  return false;
}

bool myTrailCoreInKernelAtC::rhoFilter2Peers(BitPosition aP1, BitPosition aQ1, BitPosition aP2, BitPosition aQ2){
  unsigned int offset[5][5] = {//[x][y] fashion, my state is [y][x]fashion
        {0, 36, 3, 41, 18},
        {1, 44, 10, 45, 2},
        {62, 6, 43, 15, 61},
        {28, 55, 25, 21, 56},
        {27, 20, 39, 8, 14}
    };
  unsigned int v1, v2;
  v1 = (offset[aP1.x][aP1.y] - offset[aQ1.x][aQ1.y] + 64)%64;
  v2 = (offset[aQ2.x][aQ2.y] - offset[aP2.x][aP2.y] + 64)%64;

  if (v1 == v2) {
    return true;
  } else {
    return false;
  }
}

bool myTrailCoreInKernelAtC::rhoFilterVortexCase(unsigned int numberPeers){
  unsigned int offset[5][5] = {//[x][y] fashion, my state is [y][x]fashion
        {0, 36, 3, 41, 18},
        {1, 44, 10, 45, 2},
        {62, 6, 43, 15, 61},
        {28, 55, 25, 21, 56},
        {27, 20, 39, 8, 14}
    };
    v1 = (offset[aP1.x][aP1.y] - offset[aQ1.x][aQ1.y] + 64)%64;
    v2 = (offset[aQ2.x][aQ2.y] - offset[aP2.x][aP2.y] + 64)%64;
    v3 = (offset[aQ3.x][aQ3.y] - offset[aP3.x][aP3.y] + 64)%64;
    v4 = (offset[aQ4.x][aQ4.y] - offset[aP4.x][aP4.y] + 64)%64;
    v5 = (offset[aQ5.x][aQ5.y] - offset[aP5.x][aP5.y] + 64)%64;

  switch (numberPeers) {
    case 2:
    {
      if (v1 == v2) {
        return true;
      }
      else
      return false;
    }
    break;

    case 3:
    {
      // cout << "v1/v2/v3= " << v1 << " " << v2 << " " << v3 <<endl; //test
      if (v1 == ((v2 + v3)%64)) {
        // cout << "v1/v2/v3= " << v1 << " " << v2 << " " << v3 <<endl; //test
        return true;
      } else {
        return false;
      }
    }
    break;

    case 4:
    {
      if (v1 == ((v2 + v3 + v4)%64)) {
        cout << "v1/v2/v3/v4= " << v1 << " " << v2 << " " << v3 << " " << v4 <<endl;//test
        //Filter 3 need to be implemented here!!!
        return true;
      } else {
        return false;
      }
    }
    break;

    case 5:
    {
      if (v1 == ((v2 + v3 + v4 + v5)%64)) {
        cout << "v1/v2/v3/v4/v5= " << v1 << " " << v2 << " " << v3 << " " << v4 << " " << v5 <<endl;//test
        //Filter 3 need to be implemented here!!!
        return true;
      } else {
        return false;
      }
    }
    break;

    default:
    ;
  }
  cout << "No valid case is identified!" << endl;
  return false;
}

bool myTrailCoreInKernelAtC::statePatternDuplicationCheck(unsigned int numberPeers, unsigned int cases){
  switch (numberPeers) {
    case 3:
    {
      switch (cases) {
        case 1:
        {
          multiset<BitPosition> oneState;//The valid state pattern to be checked for duplication.

          bQ2.z = v2; bP3.z = v2; bQ3.z = v1; bP1.z = v1;

          oneState.insert(bQ1); oneState.insert(bP2); oneState.insert(bQ2);
          oneState.insert(bP3); oneState.insert(bQ3); oneState.insert(bP1);

          statePatternWithDuplication.insert(oneState);
          if (statePatternWithoutDistanceCheck.insert(oneState).second == true) {
            // cout << "Pass the natural duplication check!" << endl;
            if (statePatternDistanceCheckSpace.insert(oneState).second == true) {
              // cout << "Pass the distance duplication check!" << endl;
              allUniqueStatePattern.insert(oneState);
              expandDistanceCheckSpace(oneState);
              return true;
            } else {
              cout << "Distance Duplication 6-(x,y,z)!" << endl;
              return false;
            }
          } else {
            cout << "Naturally Duplicated 6-(x,y,z) obviously!" << endl;
            return false;
          }
        }
        break;

        default:
        ;
      }
    }
    break;

    default:
    ;
  }
  cout << "Unvalid cases are identified!" << endl;
  return false;
}

void myTrailCoreInKernelAtC::expandDistanceCheckSpace(multiset<BitPosition> oneStatePattern) {
  statePatternDistanceCheckSpace.insert(oneStatePattern);//At first, the original state pattern is added.

  multiset<BitPosition> tempStatePattern1, tempStatePattern2;
  multiset<BitPosition> :: iterator it1, it2, it3;
  unsigned int d1, d2;
  BitPosition tempBQ1 = bQ1, tempBP2 = bP2, tempBQ2 = bQ2,
              tempBP3 = bP3, tempBQ3 = bQ3, tempBP1 = bP1;

  it1 = oneStatePattern.begin();
  it2 = next(it1, 2); it3 = next(it1, 4);
  d1 = (64 + (*it2).z - (*it1).z)%64;
  d2 = (64 + (*it3).z - (*it2).z)%64;
  // d3 = (64 + (*it1).z - (*it3).z)%64;

  tempBQ1.z = (64 + bQ1.z - d1)%64; tempBP2.z = (64 + bP2.z - d1)%64;
  tempBQ2.z = (64 + bQ2.z - d1)%64; tempBP3.z = (64 + bP3.z - d1)%64;
  tempBQ3.z = (64 + bQ3.z - d1)%64; tempBP1.z = (64 + bP1.z - d1)%64;
  tempStatePattern1.insert(tempBQ1); tempStatePattern1.insert(tempBP2);
  tempStatePattern1.insert(tempBQ2); tempStatePattern1.insert(tempBP3);
  tempStatePattern1.insert(tempBQ3); tempStatePattern1.insert(tempBP1);

  tempBQ1.z = (64 + tempBQ1.z - d2)%64; tempBP2.z = (64 + tempBP2.z - d2)%64;
  tempBQ2.z = (64 + tempBQ2.z - d2)%64; tempBP3.z = (64 + tempBP3.z - d2)%64;
  tempBQ3.z = (64 + tempBQ3.z - d2)%64; tempBP1.z = (64 + tempBP1.z - d2)%64;
  tempStatePattern2.insert(tempBQ1); tempStatePattern2.insert(tempBP2);
  tempStatePattern2.insert(tempBQ2); tempStatePattern2.insert(tempBP3);
  tempStatePattern2.insert(tempBQ3); tempStatePattern2.insert(tempBP1);

  statePatternDistanceCheckSpace.insert(tempStatePattern1);
  statePatternDistanceCheckSpace.insert(tempStatePattern2);

  return;
}

void myTrailCoreInKernelAtC::printValidXYtoScreen(unsigned int numberPeers) {
  switch (numberPeers) {
    case 2:
    {//First state b, then state a.
      cout << "   Q1    P2     Q2     P1   " << endl;
      cout << bQ1 << bP2 << bQ2 << bP1 << endl;
      cout << "   P1    Q1     P2     Q2   " << endl;
      cout << aP1 << aQ1 << aP2 << aQ2 << endl << endl;
    }
    break;

    case 3:
    {//First state b, then state a.
      cout << "    Q1      P2       Q2       P3       Q3       P1" << endl;
      cout << bQ1 << bP2 << bQ2 << bP3 << bQ3 << bP1 << endl;
      cout << "    P1      Q1       P2       Q2       P3       Q3" << endl;
      cout << aP1 << aQ1 << aP2 << aQ2 << aP3 << aQ3 << endl << endl;
    }
    break;

    case 4:
    {//First state b, then state a.
      cout << "    Q1      P2       Q2       P3       Q3       P4       Q4       P1" << endl;
      cout << bQ1 << bP2 << bQ2 << bP3 << bQ3 << bP4 << bQ4 << bP1 << endl;
      cout << "    P1      Q1       P2       Q2       P3       Q3       P4       Q4" << endl;
      cout << aP1 << aQ1 << aP2 << aQ2 << aP3 << aQ3 << aP4 << aQ4 << endl << endl;
    }
    break;

    case 5:
    {//First state b, then state a.
      cout << "    Q1      P2       Q2       P3       Q3       P4       Q4       P5       Q5       P1" << endl;
      cout << bQ1 << bP2 << bQ2 << bP3 << bQ3 << bP4 << bQ4 << bP5 << bQ5 << bP1 << endl;
      cout << "    P1      Q1       P2       Q2       P3       Q3       P4       Q4       P5       Q5" << endl;
      cout << aP1 << aQ1 << aP2 << aQ2 << aP3 << aQ3 << aP4 << aQ4 << aP5 << aQ5 << endl << endl;
    }
    break;

    default:
    ;
  }
}

void myTrailCoreInKernelAtC::vortexSearchTest(void) {
  generateValidSliceValuePattern(2, sliceValuePattern2);

  for ( oneValuePattern = sliceValuePattern2.begin(); oneValuePattern != sliceValuePattern2.end(); oneValuePattern++) {
    determineXforStartingSlice2Bits((*oneValuePattern), bQ1, bP2);
    for ( slicePatternCounter = 0; slicePatternCounter < sbox2YPosition.size(); slicePatternCounter++) {
      bQ1.y = sbox2YPosition[slicePatternCounter][0];
      bP2.y = sbox2YPosition[slicePatternCounter][1];

      inversePi(bQ1.x, bQ1.y, aQ1.x, aQ1.y);
      inversePi(bP2.x, bP2.y, aP2.x, aP2.y);
      aP1.x = aQ1.x;
      aQ2.x = aP2.x;

      for (int peer1Counter = 0; peer1Counter < 5; peer1Counter++) {
        if (peer1Counter != aQ1.y) {
          aP1.y = peer1Counter;
          for (int peer2Counter = 0; peer2Counter < 5; peer2Counter++) {
            if (peer2Counter != aP2.y) {
              aQ2.y = peer2Counter;

              Pi(aP1.x, aP1.y, bP1.x, bP1.y);
              Pi(aQ2.x, aQ2.y, bQ2.x, bQ2.y);

              if (validPatterFilter2Bits(bP1, bQ2)) {
                if (rhoFilter2Peers(aP1, aQ1, aP2, aQ2)) {
                  cout << "Find one valid 4-(x,y) !" << endl;
                }
              }
            }
          }
        }
      }
    }
  }
}

void myTrailCoreInKernelAtC::printStatePatternToScreen(set<multiset<BitPosition>> statePatternSet){
  cout << statePatternSet.size() << " state patterns in total!" << endl;
  set<multiset<BitPosition>>::iterator statePattern;
  for ( statePattern = statePatternSet.begin(); statePattern != statePatternSet.end(); statePattern++) {
    multiset<BitPosition> :: iterator bitPos;
    for ( bitPos = (*statePattern).begin(); bitPos != (*statePattern).end(); bitPos++) {
      cout << (*bitPos);
    }
    cout << endl;
  }
}

void myTrailCoreInKernelAtC::printOriginalStatePatternSet(void) {
  cout << statePatternWithDuplication.size() << " state patterns with duplication in total!" << endl;
  multiset<multiset<BitPosition>>::iterator statePattern;
  for ( statePattern = statePatternWithDuplication.begin(); statePattern != statePatternWithDuplication.end(); statePattern++) {
    multiset<BitPosition> :: iterator bitPos;
    for ( bitPos = (*statePattern).begin(); bitPos != (*statePattern).end(); bitPos++) {
      cout << (*bitPos);
    }
    cout << endl;
  }
}


void myTrailCoreInKernelAtC::vortexSearch3Peers(void){
  generateValidSliceValuePattern(2, sliceValuePattern2);

  for ( oneValuePattern = sliceValuePattern2.begin(); oneValuePattern != sliceValuePattern2.end(); oneValuePattern++) {
    determineXforStartingSlice2Bits((*oneValuePattern), bQ1, bP2);
    for ( slicePatternCounter = 0; slicePatternCounter < sbox2YPosition.size(); slicePatternCounter++) {
      bQ1.y = sbox2YPosition[slicePatternCounter][0];
      bP2.y = sbox2YPosition[slicePatternCounter][1];

      inversePi(bQ1.x, bQ1.y, aQ1.x, aQ1.y);
      inversePi(bP2.x, bP2.y, aP2.x, aP2.y);
      aP1.x = aQ1.x;
      aQ2.x = aP2.x;

      for (int peerCounter1 = 0; peerCounter1 < 5; peerCounter1++) {//Q1"->Q1->P1(4)
        if (peerCounter1 != aQ1.y) {
          aP1.y = peerCounter1;
          Pi(aP1.x, aP1.y, bP1.x, bP1.y);//P1->P1"

          for (int peerCounter2 = 0; peerCounter2 < 5; peerCounter2++) {//P2"->P2->Q2(4)
            if (peerCounter2 != aP2.y) {
              aQ2.y = peerCounter2;

              Pi(aQ2.x, aQ2.y, bQ2.x, bQ2.y);//Q2->Q2"
              bP3.x = bQ2.x;
              for (int peerCounter3 = 0; peerCounter3 < 5; peerCounter3++) {//Q2"->P3"
                if (peerCounter3 != bQ2.y) {
                  bP3.y = peerCounter3;

                  inversePi(bP3.x, bP3.y, aP3.x, aP3.y);//P3"->P3
                  aQ3.x = aP3.x;
                  for (int peerCounter4 = 0; peerCounter4 < 5; peerCounter4++) {//P3->Q3
                    if (peerCounter4 != aP3.y) {
                      aQ3.y = peerCounter4;

                      Pi(aQ3.x, aQ3.y, bQ3.x, bQ3.y);//Q3->Q3"

                      if (validPatterFilter2Bits(bP1, bQ3)) {
                        if (rhoFilterVortexCase(3)) {
                          if (statePatternDuplicationCheck(3,1)) {
                            cout << "Find one valid 6-(x,y)!" << endl;
                            // printValidXYtoScreen(3);
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
      }
    }
  }
  cout << endl << "All the state patterns with duplications:" << endl;
  printOriginalStatePatternSet();

  // cout << endl << "State patterns with only natural duplication eliminated:" << endl;
  // printStatePatternToScreen(statePatternWithoutDistanceCheck);

  cout << endl << "The actual state patterns without any duplication:" << endl;
  printStatePatternToScreen(allUniqueStatePattern);

  // cout << endl << "Check the expanded space:  " << endl;
  // printStatePatternToScreen(statePatternDistanceCheckSpace);
  return;
}














































void p(void){}
