CC = c++
CFLAGS = -I .. -Wno-ignored-attributes -D__MIPP__ -g

all:
	$(CC) $(CFLAGS) -march=native testEigen.cpp -o testEigen

sse2:
	$(CC) $(CFLAGS) -march=opteron testEigen.cpp -o testEigen

sse3:
	$(CC) $(CFLAGS) -march=opteron-sse3 testEigen.cpp -o testEigen

ssse3:
	$(CC) $(CFLAGS) -march=core2 testEigen.cpp -o testEigen

sse4.1:
	$(CC) $(CFLAGS) -march=nano-3000 testEigen.cpp -o testEigen

sse4.2:
	$(CC) $(CFLAGS) -march=corei7 testEigen.cpp -o testEigen

avx:
	$(CC) $(CFLAGS) -march=corei7-avx testEigen.cpp -o testEigen

avx2:
	$(CC) $(CFLAGS) -march=core-avx2 testEigen.cpp -o testEigen

avx512:
	$(CC) $(CFLAGS) -march=skylake-avx512 testEigen.cpp -o testEigen

clean:
	rm testEigen
