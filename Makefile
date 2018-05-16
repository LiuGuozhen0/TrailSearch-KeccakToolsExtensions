CC = clang++ -std=c++11 -stdlib=libc++
CFLAGS = -c -ggdb -fstack-protector-all -Wall

objects = bitstring.o duplex.o Farfalle.o genKATShortMsg.o \
Keccak-f.o Keccak-f25LUT.o Keccak-fAffineBases.o Keccak-fCodeGen.o \
Keccak-fDCEquations.o Keccak-fDCLC.o Keccak-fDisplay.o Keccak-fEquations.o \
Keccak-fParity.o Keccak-fParityBounds.o \
Keccak-fParts.o Keccak-fPositions.o Keccak-fPropagation.o Keccak-fState.o \
Keccak-fTrailCore3Rounds.o Keccak-fTrailCoreInKernelAtC.o Keccak-fTrailCoreParity.o \
Keccak-fTrailCoreRows.o Keccak-fTrailExtension.o Keccak-fTrailExtensionBasedOnParity.o \
Keccak-fTrails.o Keccak-fTree.o \
Keccak.o KeccakCrunchyContest.o Ketjev2-test.o Ketjev2.o Keyakv2.o Keyakv2-test.o Kravatte.o Kravatte-test.o KravatteModes-test.o \
monkey.o Motorist.o padding.o progress.o sponge.o spongetree.o transformations.o \
main.o


inKernelSearch_PreviousMethods: main current
		$(CC) $(objects) -o inKernelAtCTrailCoreSearch_PreviousMethods

main:
		$(CC) $(CFLAGS) main.cpp

current:
		$(CC) $(CFLAGS) Keccak-fTrailCoreInKernelAtC.cpp

original:
		$(CC) $(CFLAGS) bitstring.cpp duplex.cpp Farfalle.cpp genKATShortMsg.cpp \
		Keccak-f.cpp Keccak-f25LUT.cpp Keccak-fAffineBases.cpp Keccak-fCodeGen.cpp \
		Keccak-fDCEquations.cpp Keccak-fDCLC.cpp Keccak-fDisplay.cpp Keccak-fEquations.cpp \
		Keccak-fParity.cpp Keccak-fParityBounds.cpp \
		Keccak-fParts.cpp Keccak-fPositions.cpp Keccak-fPropagation.cpp Keccak-fState.cpp \
		Keccak-fTrailCore3Rounds.cpp Keccak-fTrailCoreParity.cpp \
		Keccak-fTrailCoreRows.cpp Keccak-fTrailExtension.cpp Keccak-fTrailExtensionBasedOnParity.cpp \
		Keccak-fTrails.cpp Keccak-fTree.cpp \
		Keccak.cpp KeccakCrunchyContest.cpp Ketjev2-test.cpp Ketjev2.cpp Keyakv2.cpp Keyakv2-test.cpp Kravatte.cpp Kravatte-test.cpp KravatteModes-test.cpp \
		monkey.cpp Motorist.cpp padding.cpp progress.cpp sponge.cpp spongetree.cpp transformations.cpp

clean:
		rm -rf *.o inKernelAtCTrailCoreSearch_PreviousMethods
