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
using namespace std;
#define CASENUMBER 22

typedef std::vector<std::vector<unsigned int> > DualVector;
typedef std::vector<std::vector<std::vector<unsigned int> > > TriVector;
typedef set <multiset <unsigned int, greater <unsigned int> > > multisetSet;
/**
  * Print the value patterns of a specific set to the screen.
  */
void printValueSlicePattern(multisetSet& valuePattern);

/**
  * For a group of slice patterns, e.g., {{1,4},{2,3}}, generate all the possible input
  * differences for each slice pattern case and store all the cases in the 3D vector.
  */
void genInputforAllActiveSbox(DualVector& slicePatternCase,TriVector& activeSboxAllCase);
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




#endif
