CC = c++
CFLAGS = -I .. -Wno-ignored-attributes -D__MIPP__ -g

all:
	$(CC) $(CFLAGS) -march=native nrTestEigen.cpp -o nrTestEigen

mmx:
	$(CC) $(CFLAGS) -mmmx nrTestEigen.cpp -o nrTestEigen

sse:
	$(CC) $(CFLAGS) -msse nrTestEigen.cpp -o nrTestEigen

sse2:
	$(CC) $(CFLAGS) -msse2 nrTestEigen.cpp -o nrTestEigen
# -march=opteron

sse3:
	$(CC) $(CFLAGS) -msse3 nrTestEigen.cpp -o nrTestEigen
# -march=opteron-sse3

ssse3:
	$(CC) $(CFLAGS) -mssse3 nrTestEigen.cpp -o nrTestEigen
# -march=core2

sse4.1:
	$(CC) $(CFLAGS) -msse4.1 nrTestEigen.cpp -o nrTestEigen
# -march=nano-3000

sse4.2:
	$(CC) $(CFLAGS) -msse4.2 nrTestEigen.cpp -o nrTestEigen
# -march=corei7

avx:
	$(CC) $(CFLAGS) -mavx nrTestEigen.cpp -o nrTestEigen
# -march=corei7-avx

avx2:
	$(CC) $(CFLAGS) -mavx2 nrTestEigen.cpp -o nrTestEigen
# -march=core-avx2

avx512:
	$(CC) $(CFLAGS) -mfma -mavx512f nrTestEigen.cpp -o nrTestEigen
# -march=skylake-avx512

clean:
	rm nrTestEigen
