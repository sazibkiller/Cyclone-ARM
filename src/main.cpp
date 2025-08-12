#include "cyclone.h"
#include <iostream>

int main(int argc, char** argv) {
    int run_seconds = 0;
    if (argc >= 2) run_seconds = atoi(argv[1]);

    std::cout << "Cyclone-ARM : quick hash benchmark (double-SHA256)\n";
    Cyclone c;
    c.run_seconds(run_seconds); // 0 means run until Ctrl-C
    return 0;
}
