CXX = clang++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Wno-write-strings -Wno-unused-variable -Wno-deprecated-copy -Wno-unused-parameter -Wno-sign-compare -Wno-strict-aliasing -Wno-unused-but-set-variable -funroll-loops -ftree-vectorize -fstrict-aliasing -fno-semantic-interposition -fno-trapping-math -fassociative-math -fopenmp -march=armv8-a+simd

SRCS = Cyclone.cpp Int.cpp IntGroup.cpp IntMod.cpp Point.cpp Random.cpp SECP256K1.cpp Timer.cpp sha256_portable.cpp ripemd160_portable.cpp crc32_portable.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = cyclone-arm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
