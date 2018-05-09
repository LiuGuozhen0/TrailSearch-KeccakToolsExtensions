#ifndef _TRAILCOREINKERNELATC_
#define _TRAILCOREINKERNELATC_

#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <stack>
#include "misc.h"
#include <bitset>
#include <iterator>
#include "Keccak-fPositions.h"

using namespace std;

typedef std::vector<std::vector<unsigned int>> DualVector;
typedef std::vector<std::vector<std::vector<unsigned int>>> TriVector;
typedef set <multiset <unsigned int, greater <unsigned int>>> multisetSet;
typedef multiset <unsigned int, greater <unsigned int>> ValuePatternmultiset;

class myTrailCoreInKernelAtC{
public:
  /** This method prints the set that stores the valid state patterns to the screen.
    * @param statePatternSet there are various sets that store different kinds of state patterns at state b.
   */
  void printStatePatternToScreen(set<multiset<BitPosition>> statePatternSet);
  /** This method expand the state pattern of 3 slices at state b.
    * In that case, each state pattern stands for 3 patterns under the storing tradition.
    * Thus for each state pattern, we store all its identical patterns in the expanded space according to which
    * the duplicated patterns can be eliminated in the subsequent step.
    * @param oneStatePattern the state pattern that will be expanded.
    */
  void expandDistanceCheckSpace(multiset<BitPosition> oneStatePattern);
  /** This function prints all the valid 2n-(x,y,z) without any duplication check.
    */
  void printOriginalStatePatternSet(void);

  /** This method checks whether the present valid state pattern is a duplication of an already existing one.
    * With the searching method, there is a possibility that many duplicated state patterns are counted multiple times.
    * There are two kinds of duplication of state patterns: 1) one is cased by the distinctions of bits notated to construct the model while
    * actually different combinations of the denoted bits may stand for the same state pattern b 2) the other one is caused by the z-translation
    * invariant property when a state pattern is fixed there are several equal patterns resulted from rotating on z.
    * Practically, for a fixed state, there are 2^6 identical patterns and for each of them the distances of two continuous slices are determined and remained unchanged.
    * @param numberPeers
    * @param cases for example, for the 3 peers case, there are 2 subcases, i.e., 2+2+2 and 3+3
    */
  bool statePatternDuplicationCheck(unsigned int numberPeers, unsigned int cases);

  myTrailCoreInKernelAtC();
  ~myTrailCoreInKernelAtC();

  /** This method prints the searched 2n-(x,y) to screen for further analyzing.
    * @param numberPeers numberPeers indicates the number of peers in this vortex search.
    */
  void printValidXYtoScreen(unsigned int numberPeers);

  /** This method implements constraints imposed by rho for vortex search cases.
    * @param numberPeers The number of peers of each vortex search.
    */
  bool rhoFilterVortexCase(unsigned int numberPeers);

  /** This method generates vortex of three peers.
    */
  void vortexSearch3Peers(void);

  /** This method generate all the input differences candidates for the slice indicated by the slice pattern.
    * @param slicePatternCase store all the slice possiblities of a specific active bits, e.g., {{1,2},{1,1,1}} for 3 bits.
    * @param activeSboxAllCase stores all input differences for each slice possiblities
    */
  void genInputforAllActiveSbox(DualVector slicePatternCase,
                                TriVector& activeSboxAllCase);

  /** This method print all the valid slice value patterns to the screen.
    * @param valuePattern The Set of a Multiset that stores the valid slice value pattens.
    */
  void printValueSlicePattern(multisetSet valuePattern);

  /** This method generate the valid value slice patterns for the slice that contains two sboxes.
    * @param activeSboxAllCase The 3D vector stores the input differences of all the cases of two sboxes.
    * @param DDTOutput[32][32] The DDT of the 5-bit Sbox with DDTOutput[i][0] stores the number of compatible output differences of input i.
    * @param valuePattern2 The set of multiset that stores all the valid value patterns of two sboxes.
    */
  void twoSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern2);
  void threeSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern3);
  void fourSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern4);
  void fiveSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern5);

  /** This method generate all the valid value patterns of a slice with a specific number of active bits.
    * @param nBit The number of active bits of this active slice to be checked.
    * @param patternSet The set of multiset that stores all the valid value patterns for the slice with nBit bits.
    */
  void generateValidSliceValuePattern(unsigned int nBit, multisetSet& patternSet);

  /** These two methods transfer the two states before and after Pi.
    * @param X\Y (x,y) coordinates of the bit at state b.
    * @param x\y (x,y) coordinates of the same bit at state a.
    */
  void inversePi(unsigned int X, unsigned int Y, unsigned int & x, unsigned int & y);
  void Pi(unsigned int x, unsigned int y, unsigned int & X, unsigned int & Y);

  /** Determine the (x) coordinates of the bits in the starting slice of 2 bits at state b.
    * @param oneValuePattern One valid value patterned prepared previously.
    * @param bQ1\bP2 According to the 2 bit slice value pattern, determine the (x) of the two bits.
    */
  void determineXforStartingSlice2Bits(ValuePatternmultiset oneValuePattern, BitPosition & bQ1, BitPosition & bP2);

  /** This methods checks whether the two bits at state b form a valid value pattern.
    */
  bool validPatterFilter2Bits(BitPosition bP, BitPosition bQ);

  /** This method filters the 4-(x,y) at state a by checking the requirements imposed by rho.
    */
  bool rhoFilter2Peers(BitPosition aP1, BitPosition aQ1, BitPosition aP2, BitPosition aQ2);

  /** This is a test method that search vortex of two peers.
    */
  void vortexSearchTest(void);

  /** It's not a requirement to declare data first in a class.
    * It often makes sense to place data members last to emphasize
    * the functions providing the public user interface.
    */
private:
  /** This set stores all the state patterns at state b without any duplication check!
    */
  multiset<multiset<BitPosition>> statePatternWithDuplication;
  /** This set stores the state pattern space expanded by the patterns that pass the natural duplication check.
    * The distance check space is obtained from rotate the original state slicely.
    * With this check space, other distance duplicated patterns can be eliminated.
    */
  set<multiset<BitPosition>> statePatternDistanceCheckSpace;
  /** This set stores the state patterns at state b after natural duplication check but without distance duplication check.
    */
  set<multiset<BitPosition>> statePatternWithoutDistanceCheck;
  /** This set stores the actual state patterns at state b without any duplications
    */
  set<multiset<BitPosition>> allUniqueStatePattern;

  /** These 5 values are defined to check the rho filters.
    */
  unsigned int v1, v2, v3, v4, v5;
  /** This iterator points to the set that stores all the valid value patterns.
   */
  multisetSet ::iterator oneValuePattern;
  /** The counter is defined to indicate the actual slice pattern that is checked now.
    * For example, for 3 sboxes slice, there are 5*4*3=60 possible slice patterns to be checked.
    */
  unsigned int slicePatternCounter;
  /** These set of multiset containers are set to store the valid slice value patterns for
    * the slices of a certain number of active bits.
    */
  multisetSet sliceValuePattern2, sliceValuePattern3, sliceValuePattern4, sliceValuePattern5;
  /** The active bits that are going to be determined.
    */
  BitPosition aP1, aQ1, aP2, aQ2, aP3, aQ3, aP4, aQ4, aP5, aQ5;
  BitPosition bP1, bQ1, bP2, bQ2, bP3, bQ3, bP4, bQ4, bP5, bQ5;
  /** Index of sboxes when constructing slice patterns out of value patterns.
    * There exist duplicates of slice patterns.
    */
  const DualVector sbox2YPosition {
    {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 0}, {1, 2}, {1,3}, {1, 4}, {2, 0}, {2, 1},
    {2, 3}, {2, 4}, {3, 0}, {3, 1}, {3, 2}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3}
  };
  const DualVector sbox3YPosition {
    {0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 2, 1}, {0, 2, 3}, {0, 2, 4}, {0, 3, 1}, {0, 3, 2}, {0, 3, 4}, {0, 4, 1},
    {0, 4, 2}, {0, 4, 3}, {1, 0, 2}, {1, 0, 3}, {1, 0, 4}, {1, 2, 0}, {1, 2, 3}, {1, 2, 4}, {1, 3, 0}, {1, 3, 2},
    {1, 3, 4}, {1, 4, 0}, {1, 4, 2}, {1, 4, 3}, {2, 0, 1}, {2, 0, 3}, {2, 0, 4}, {2, 1, 0}, {2, 1, 3}, {2, 1, 4},
    {2, 3, 0}, {2, 3, 1}, {2, 3, 4}, {2, 4, 0}, {2, 4, 1}, {2, 4, 3}, {3, 0, 1}, {3, 0, 2}, {3, 0, 4}, {3, 1, 0},
    {3, 1, 2}, {3, 1, 4}, {3, 2, 0}, {3, 2, 1}, {3, 2, 4}, {3, 4, 0}, {3, 4, 1}, {3, 4, 2}, {4, 0, 1}, {4, 0, 2},
    {4, 0, 3}, {4, 1, 0}, {4, 1, 2}, {4, 1, 3}, {4, 2, 0}, {4, 2, 1}, {4, 2, 3}, {4, 3, 0}, {4, 3, 1}, {4, 3, 2}
  };
  const DualVector sbox4YPosition {
    {0, 1, 2, 3}, {0, 1, 2, 4}, {0, 1, 3, 2}, {0, 1, 3, 4}, {0, 1, 4, 2}, {0, 1, 4, 3},
    {0, 2, 1, 3}, {0, 2, 1, 4}, {0, 2, 3, 1}, {0, 2, 3, 4}, {0, 2, 4, 1}, {0, 2, 4, 3},
    {0, 3, 1, 2}, {0, 3, 1, 4}, {0, 3, 2, 1}, {0, 3, 2, 4}, {0, 3, 4, 1}, {0, 3, 4, 2},
    {0, 4, 1, 2}, {0, 4, 1, 3}, {0, 4, 2, 1}, {0, 4, 2, 3}, {0, 4, 3, 1}, {0, 4, 3, 2},
    {1, 0, 2, 3}, {1, 0, 2, 4}, {1, 0, 3, 2}, {1, 0, 3, 4}, {1, 0, 4, 2}, {1, 0, 4, 3},
    {1, 2, 0, 3}, {1, 2, 0, 4}, {1, 2, 3, 0}, {1, 2, 3, 4}, {1, 2, 4, 0}, {1, 2, 4, 3},
    {1, 3, 0, 2}, {1, 3, 0, 4}, {1, 3, 2, 0}, {1, 3, 2, 4}, {1, 3, 4, 0}, {1, 3, 4, 2},
    {1, 4, 0, 2}, {1, 4, 0, 3}, {1, 4, 2, 0}, {1, 4, 2, 3}, {1, 4, 3, 0}, {1, 4, 3, 2},
    {2, 0, 1, 3}, {2, 0, 1, 4}, {2, 0, 3, 1}, {2, 0, 3, 4}, {2, 0, 4, 1}, {2, 0, 4, 3},
    {2, 1, 0, 3}, {2, 1, 0, 4}, {2, 1, 3, 0}, {2, 1, 3, 4}, {2, 1, 4, 0}, {2, 1, 4, 3},
    {2, 3, 0, 1}, {2, 3, 0, 4}, {2, 3, 1, 0}, {2, 3, 1, 4}, {2, 3, 4, 0}, {2, 3, 4, 1},
    {2, 4, 0, 1}, {2, 4, 0, 3}, {2, 4, 1, 0}, {2, 4, 1, 3}, {2, 4, 3, 0}, {2, 4, 3, 1},
    {3, 0, 1, 2}, {3, 0, 1, 4}, {3, 0, 2, 1}, {3, 0, 2, 4}, {3, 0, 4, 1}, {3, 0, 4, 2},
    {3, 1, 0, 2}, {3, 1, 0, 4}, {3, 1, 2, 0}, {3, 1, 2, 4}, {3, 1, 4, 0}, {3, 1, 4, 2},
    {3, 2, 0, 1}, {3, 2, 0, 4}, {3, 2, 1, 0}, {3, 2, 1, 4}, {3, 2, 4, 0}, {3, 2, 4, 1},
    {3, 4, 0, 1}, {3, 4, 0, 2}, {3, 4, 1, 0}, {3, 4, 1, 2}, {3, 4, 2, 0}, {3, 4, 2, 1},
    {4, 0, 1, 2}, {4, 0, 1, 3}, {4, 0, 2, 1}, {4, 0, 2, 3}, {4, 0, 3, 1}, {4, 0, 3, 2},
    {4, 1, 0, 2}, {4, 1, 0, 3}, {4, 1, 2, 0}, {4, 1, 2, 3}, {4, 1, 3, 0}, {4, 1, 3, 2},
    {4, 2, 0, 1}, {4, 2, 0, 3}, {4, 2, 1, 0}, {4, 2, 1, 3}, {4, 2, 3, 0}, {4, 2, 3, 1},
    {4, 3, 0, 1}, {4, 3, 0, 2}, {4, 3, 1, 0}, {4, 3, 1, 2}, {4, 3, 2, 0}, {4, 3, 2, 1}
  };
  const DualVector sbox5YPosition {
    {0, 1, 2, 3, 4}, {0, 1, 2, 4, 3}, {0, 1, 3, 2, 4}, {0, 1, 3, 4, 2}, {0, 1, 4, 2, 3}, {0, 1, 4, 3, 2},
    {0, 2, 1, 3, 4}, {0, 2, 1, 4, 3}, {0, 2, 3, 1, 4}, {0, 2, 3, 4, 1}, {0, 2, 4, 1, 3}, {0, 2, 4, 3, 1},
    {0, 3, 1, 2, 4}, {0, 3, 1, 4, 2}, {0, 3, 2, 1, 4}, {0, 3, 2, 4, 1}, {0, 3, 4, 1, 2}, {0, 3, 4, 2, 1},
    {0, 4, 1, 2, 3}, {0, 4, 1, 3, 2}, {0, 4, 2, 1, 3}, {0, 4, 2, 3, 1}, {0, 4, 3, 1, 2}, {0, 4, 3, 2, 1},
    {1, 0, 2, 3, 4}, {1, 0, 2, 4, 3}, {1, 0, 3, 2, 4}, {1, 0, 3, 4, 2}, {1, 0, 4, 2, 3}, {1, 0, 4, 3, 2},
    {1, 2, 0, 3, 4}, {1, 2, 0, 4, 3}, {1, 2, 3, 0, 4}, {1, 2, 3, 4, 0}, {1, 2, 4, 0, 3}, {1, 2, 4, 3, 0},
    {1, 3, 0, 2, 4}, {1, 3, 0, 4, 2}, {1, 3, 2, 0, 4}, {1, 3, 2, 4, 0}, {1, 3, 4, 0, 2}, {1, 3, 4, 2, 0},
    {1, 4, 0, 2, 3}, {1, 4, 0, 3, 2}, {1, 4, 2, 0, 3}, {1, 4, 2, 3, 0}, {1, 4, 3, 0, 2}, {1, 4, 3, 2, 0},
    {2, 0, 1, 3, 4}, {2, 0, 1, 4, 3}, {2, 0, 3, 1, 4}, {2, 0, 3, 4, 1}, {2, 0, 4, 1, 3}, {2, 0, 4, 3, 1},
    {2, 1, 0, 3, 4}, {2, 1, 0, 4, 3}, {2, 1, 3, 0, 4}, {2, 1, 3, 4, 0}, {2, 1, 4, 0, 3}, {2, 1, 4, 3, 0},
    {2, 3, 0, 1, 4}, {2, 3, 0, 4, 1}, {2, 3, 1, 0, 4}, {2, 3, 1, 4, 0}, {2, 3, 4, 0, 1}, {2, 3, 4, 1, 0},
    {2, 4, 0, 1, 3}, {2, 4, 0, 3, 1}, {2, 4, 1, 0, 3}, {2, 4, 1, 3, 0}, {2, 4, 3, 0, 1}, {2, 4, 3, 1, 0},
    {3, 0, 1, 2, 4}, {3, 0, 1, 4, 2}, {3, 0, 2, 1, 4}, {3, 0, 2, 4, 1}, {3, 0, 4, 1, 2}, {3, 0, 4, 2, 1},
    {3, 1, 0, 2, 4}, {3, 1, 0, 4, 2}, {3, 1, 2, 0, 4}, {3, 1, 2, 4, 0}, {3, 1, 4, 0, 2}, {3, 1, 4, 2, 0},
    {3, 2, 0, 1, 4}, {3, 2, 0, 4, 1}, {3, 2, 1, 0, 4}, {3, 2, 1, 4, 0}, {3, 2, 4, 0, 1}, {3, 2, 4, 1, 0},
    {3, 4, 0, 1, 2}, {3, 4, 0, 2, 1}, {3, 4, 1, 0, 2}, {3, 4, 1, 2, 0}, {3, 4, 2, 0, 1}, {3, 4, 2, 1, 0},
    {4, 0, 1, 2, 3}, {4, 0, 1, 3, 2}, {4, 0, 2, 1, 3}, {4, 0, 2, 3, 1}, {4, 0, 3, 1, 2}, {4, 0, 3, 2, 1},
    {4, 1, 0, 2, 3}, {4, 1, 0, 3, 2}, {4, 1, 2, 0, 3}, {4, 1, 2, 3, 0}, {4, 1, 3, 0, 2}, {4, 1, 3, 2, 0},
    {4, 2, 0, 1, 3}, {4, 2, 0, 3, 1}, {4, 2, 1, 0, 3}, {4, 2, 1, 3, 0}, {4, 2, 3, 0, 1}, {4, 2, 3, 1, 0},
    {4, 3, 0, 1, 2}, {4, 3, 0, 2, 1}, {4, 3, 1, 0, 2}, {4, 3, 1, 2, 0}, {4, 3, 2, 0, 1}, {4, 3, 2, 1, 0}
  };
};



#endif
