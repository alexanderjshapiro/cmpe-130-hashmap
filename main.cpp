#include <iostream>
#include "hashes/all.h"

using namespace std;

uint64_t currentTime() {
    return chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
}

int main() {
    unsigned int RUNS = 100;

    uint64_t times[RUNS];
    for (int run = 1; run <= RUNS; run++) {
        unsigned int NUM = 100000;

        auto hashes = new string[NUM];

        uint64_t start = currentTime();

        for (int i = 0; i < NUM; i++) {
            string str = to_string(currentTime());
            char c[str.size() + 1];
            str.copy(c, str.size() + 1);
            c[str.size()] = '\0';

            hashes[i] = Chocobo1::MD5().addData(c, str.size()).finalize().toString();
        }

        uint64_t end = currentTime();
        uint64_t duration = end - start;

        times[run] = duration;
    }

    uint64_t sum = 0;
    for (uint64_t time : times) sum += time;
    uint64_t avg = sum / RUNS;
    double sec = avg / 1000000000.0;

    cout << sec << endl;

    return 0;
}
