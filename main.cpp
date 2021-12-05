#include <iostream>
#include "hashes/all.h"

using namespace std;

uint64_t currentTime() {
    return chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
}

int main() {
    unsigned int RUNS = 100;

    uint64_t times[RUNS];
    unsigned collisions = 0;
    for (int run = 0; run < RUNS; run++) {
        unsigned int NUM = 1000;

        auto hashes = new bool[NUM];
        for (int i = 0; i < NUM; i++) hashes[i] = false;

        uint64_t start = currentTime();

        for (int i = 0; i < NUM; i++) {
            string str = to_string(currentTime());
            char c[str.size() + 1];
            str.copy(c, str.size() + 1);
            c[str.size()] = '\0';

            string hash = Chocobo1::CRC_32().addData(c, str.size()).finalize().toString();
            unsigned long long index = stoll(hash.substr(hash.size() - 8), 0, 16) % NUM;
            if (!hashes[index]) hashes[index] = true;
            else collisions++;
        }

        uint64_t end = currentTime();
        uint64_t duration = end - start;

        times[run] = duration;
    }

    uint64_t sum = 0;
    for (uint64_t time : times) sum += time;

    cout << sum / RUNS << endl;
    cout << collisions / RUNS << endl;

    return 0;
}
