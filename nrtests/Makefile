CC = c++
CFLAGS = -I .. -Wno-ignored-attributes -D__MIPP__ -g

all:
	$(CC) $(CFLAGS) -march=native testEigen.cpp -o testEigen

sse:
	$(CC) $(CFLAGS) -march=opteron-sse3 testEigen.cpp -o testEigen

avx:
	$(CC) $(CFLAGS) -march=core-avx-i testEigen.cpp -o testEigen

avx2:
	$(CC) $(CFLAGS) -march=core-avx2 testEigen.cpp -o testEigen

avx512:
	$(CC) $(CFLAGS) -march=skylake-avx512 testEigen.cpp -o testEigen

clean:
	rm testEigen
