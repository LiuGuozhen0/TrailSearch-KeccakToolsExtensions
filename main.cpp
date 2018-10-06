/*
The Keccak sponge function, designed by Guido Bertoni, Joan Daemen,
Michaël Peeters and Gilles Van Assche. For more information, feedback or
questions, please refer to our website: http://keccak.noekeon.org/

Implementation by the designers,
hereby denoted as "the implementer".

To the extent possible under law, the implementer has waived all copyright
and related or neighboring rights to the source code in this file.
http://creativecommons.org/publicdomain/zero/1.0/
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include "duplex.h"
#include "Keccak.h"
#include "KeccakCrunchyContest.h"
#include "Keccak-f25LUT.h"
#include "Keccak-fCodeGen.h"
#include "Keccak-fDCEquations.h"
#include "Keccak-fDCLC.h"
#include "Keccak-fEquations.h"
#include "Keccak-fPropagation.h"
#include "Keccak-fTrailExtension.h"
#include "Keccak-fTrailExtensionBasedOnParity.h"
#include "Keccak-fTrails.h"
#include "Keccak-fTree.h"
#include "Keyakv2-test.h"
#include "Ketjev2-test.h"
#include "Kravatte.h"
#include "Kravatte-test.h"
#include "KravatteModes-test.h"

#include "Keccak-fTrailCoreInKernelAtC.h"

using namespace std;

int main(int argc, char *argv[])
{
    try {
        
    }
    catch(Exception e) {
        cout << e.reason << endl;
    }

    return EXIT_SUCCESS;
}
