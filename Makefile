 CC = g++ -std=c++11

 #CFLAGS = -std=c++11 -Wall
 CFLAGS = -c -ggdb -Wall

 objects = Keccak-f.o Keccak-f25LUT.o genKATShortMsg.o Farfalle.o duplex.o \
 bitstring.o transformations.o spongetree.o sponge.o progress.o padding.o Motorist.o \
 monkey.o KravatteModes-test.o Kravatte.o Kravatte-test.o Keyakv2.o Keyakv2-test.o \
 Ketjev2.o Ketjev2-test.o KeccakCrunchyContest.o Keccak.o Keccak-fTrails.o Keccak-fTrailExtensionBasedOnParity.o \
 Keccak-fTrailExtension.o Keccak-fTrailCoreRows.o Keccak-fTrailCoreParity.o Keccak-fTrailCoreInKernelAtC.o \
 Keccak-fTrailCore3Rounds.o Keccak-fState.o Keccak-fPositions.o Keccak-fParts.o \
 Keccak-fParityBounds.o Keccak-fParity.o Keccak-fEquations.o Keccak-fDisplay.o \
 Keccak-fDCLC.o Keccak-fDCEquations.o Keccak-fCodeGen.o Keccak-fAffineBases.o \
 misc.o kkeccak.o Keccak-fTree.o Keccak-fPropagation.o inKernelSearch.o main.o

#vortexSearch following the "-o" is the created executable file.
#Generally, make only performs the first target
#the other targets are placed as the prerequisites of the first target
#One exception is the "clean" target, which will be directly run by typing "make clean" in command line
vortexSearch: present main.o
		$(CC) $(objects) -o vortexSearch

#the target "present" is not a file but an action
present:
		$(CC) $(CFLAGS) inKernelSearch.cpp


main.o:
		$(CC) $(CFLAGS) main.cpp


#The cpps from the original KeccakTools.
#Most often, these cpps won't be changed.
#The other rules are processed because their targets appear as the prerequisites of the "goal".
original:
		$(CC) $(CFLAGS) Keccak-f.cpp Keccak-f25LUT.cpp genKATShortMsg.cpp Farfalle.cpp duplex.cpp \
		bitstring.cpp transformations.cpp spongetree.cpp sponge.cpp progress.cpp padding.cpp Motorist.cpp \
		monkey.cpp KravatteModes-test.cpp Kravatte.cpp Kravatte-test.cpp Keyakv2.cpp Keyakv2-test.cpp \
		Ketjev2.cpp Ketjev2-test.cpp KeccakCrunchyContest.cpp Keccak.cpp Keccak-fTrails.cpp Keccak-fTrailExtensionBasedOnParity.cpp \
		Keccak-fTrailExtension.cpp Keccak-fTrailCoreRows.cpp Keccak-fTrailCoreParity.cpp Keccak-fTrailCoreInKernelAtC.cpp \
		Keccak-fTrailCore3Rounds.cpp Keccak-fState.cpp Keccak-fPositions.cpp Keccak-fParts.cpp \
		Keccak-fParityBounds.cpp Keccak-fParity.cpp Keccak-fEquations.cpp Keccak-fDisplay.cpp \
		Keccak-fDCLC.cpp Keccak-fDCEquations.cpp Keccak-fCodeGen.cpp Keccak-fAffineBases.cpp \
		misc.cpp kkeccak.cpp Keccak-fTree.cpp Keccak-fPropagation.cpp

clean:
		rm -rf *.o vortexSearch
