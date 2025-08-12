#include "cyclone.h"
#include "sha256_portable.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

using namespace std::chrono;

static std::atomic<uint64_t> g_count{0};

static void worker_thread_func(int id, std::atomic<bool>& stop_flag) {
    // local PRNG
    std::mt19937_64 rng((uint64_t)std::random_device{}() ^ (uint64_t)id);
    uint8_t data[32];
    uint8_t hash1[32], hash2[32];
    SHA256_CTX ctx;

    while (!stop_flag.load(std::memory_order_relaxed)) {
        // generate 32 random bytes
        uint64_t r1 = rng();
        uint64_t r2 = rng();
        uint64_t r3 = rng();
        uint64_t r4 = rng();
        memcpy(data, &r1, 8);
        memcpy(data+8, &r2, 8);
        memcpy(data+16, &r3, 8);
        memcpy(data+24, &r4, 8);

        // double SHA256 (simulate work)
        sha256_init(&ctx);
        sha256_update(&ctx, data, 32);
        sha256_final(&ctx, hash1);

        sha256_init(&ctx);
        sha256_update(&ctx, hash1, 32);
        sha256_final(&ctx, hash2);

        g_count.fetch_add(1, std::memory_order_relaxed);
    }
}

void Cyclone::run_seconds(int seconds) {
    unsigned int nthreads = std::max(1u, std::thread::hardware_concurrency());
    std::vector<std::thread> threads;
    std::atomic<bool> stop_flag{false};

    // start workers
    for (unsigned i=0;i<nthreads;i++) threads.emplace_back(worker_thread_func, (int)i, std::ref(stop_flag));

    // monitor speed
    auto t0 = steady_clock::now();
    uint64_t last_count = 0;

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        auto t1 = steady_clock::now();
        uint64_t now = g_count.load(std::memory_order_relaxed);
        double elapsed = duration_cast<duration<double>>(t1 - t0).count();
        uint64_t delta = now - last_count;
        double rate = delta / 2.0; // per second approx over last 2s
        std::cout << "threads=" << nthreads << "  total=" << now << "  " << (uint64_t)rate << " keys/s (recent)" << std::endl;
        last_count = now;

        if (seconds>0 && std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count() >= seconds) break;
    }

    stop_flag.store(true);
    for (auto &th: threads) if (th.joinable()) th.join();
}
