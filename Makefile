CXX = clang++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -march=armv8-a+simd -mtune=cortex-a78
LDFLAGS = 

SRC = src/main.cpp src/cyclone.cpp src/int.cpp src/util.cpp src/sha256_portable.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = cyclone_arm

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
