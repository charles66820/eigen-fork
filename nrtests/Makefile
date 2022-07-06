CC = c++
CFLAGS = -I .. -Wno-ignored-attributes -D__MIPP__ -g

all:
	$(CC) $(CFLAGS) -march=native testEigen.cpp -o testEigen

mmx:
	$(CC) $(CFLAGS) -mmmx testEigen.cpp -o testEigen

sse:
	$(CC) $(CFLAGS) -msse testEigen.cpp -o testEigen

sse2:
	$(CC) $(CFLAGS) -msse2 testEigen.cpp -o testEigen
# -march=opteron

sse3:
	$(CC) $(CFLAGS) -msse3 testEigen.cpp -o testEigen
# -march=opteron-sse3

ssse3:
	$(CC) $(CFLAGS) -mssse3 testEigen.cpp -o testEigen
# -march=core2

sse4.1:
	$(CC) $(CFLAGS) -msse4.1 testEigen.cpp -o testEigen
# -march=nano-3000

sse4.2:
	$(CC) $(CFLAGS) -msse4.2 testEigen.cpp -o testEigen
# -march=corei7

avx:
	$(CC) $(CFLAGS) -mavx testEigen.cpp -o testEigen
# -march=corei7-avx

avx2:
	$(CC) $(CFLAGS) -mavx2 testEigen.cpp -o testEigen
# -march=core-avx2

avx512:
	$(CC) $(CFLAGS) -mfma -mavx512f testEigen.cpp -o testEigen
# -march=skylake-avx512

clean:
	rm testEigen
