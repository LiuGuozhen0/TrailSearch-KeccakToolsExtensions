#ifndef _INKERNELSEARCH_
#define _INKERNELSEARCH_

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
// #include "Keccak-f.h"

using namespace std;
#define CASENUMBER 22

typedef std::vector<std::vector<unsigned int>> DualVector;
typedef std::vector<std::vector<std::vector<unsigned int>>> TriVector;
typedef set <multiset <unsigned int, greater <unsigned int>>> multisetSet;
typedef multiset <unsigned int, greater <unsigned int>> ValuePatternmultiset;


/**
  * Print the value patterns of a specific set to the screen.
  */
void printValueSlicePattern(multisetSet valuePattern);

/**
  * For a group of slice patterns, e.g., {{1,4},{2,3}}, generate all the possible input
  * differences for each slice pattern case and store all the cases in the 3D vector.
  */
void genInputforAllActiveSbox(DualVector slicePatternCase,TriVector& activeSboxAllCase);
/**
  * For any slices of two sboxes, generate the relating valid value patterns.
  */
void twoSboxValuePatternSearch(TriVector& activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern2);
/**
  *For any slices of three sboxes, generate the relating valid value patterns.
  */
void threeSboxValuePatternSearch(TriVector& activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern3);
/**
  *For any slices of four sboxes, generate the relating valid value patterns.
  */
void fourSboxValuePatternSearch(TriVector& activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern4);
/**
  *For any slices of five sboxes, generate the relating valid value patterns.
  */
void fiveSboxValuePatternSearch(TriVector& activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern5);

/**
  * Generate the valid value patterns of a fixed number of active bits.
  */
void generateValidSliceValuePattern(unsigned int nBit, set <multiset <unsigned int, greater <unsigned int> > > & patternSet);
/**
  * The initial code of generating valid slice value patterns.
  */
void generateValidSliceValuePattern(void);
/**
  *
  */
void vectorOf2Peers(void);

void vortexSearchTest(void);
void determineXforStartingSlice2Bits(ValuePatternmultiset oneValuePattern, BitPosition& bQ1, BitPosition& bP2);
bool validPatterFilter2Bits(BitPosition bP, BitPosition bQ);
bool rhoFilter2Peers(BitPosition aP1, BitPosition aQ1, BitPosition aP2, BitPosition aQ2);
void inversePi(unsigned int X, unsigned int Y, unsigned int & x, unsigned int & y);
void Pi(unsigned int x, unsigned int y, unsigned int & X, unsigned int & Y);







#endif
