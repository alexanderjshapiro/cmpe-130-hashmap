#include <iostream>
#include "hashes/all.h"

using namespace std;

uint64_t currentTime() {
    return chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
}

string hashString(string key) {
    char c[key.size() + 1];
    key.copy(c, key.size() + 1);
    c[key.size()] = '\0';
    return Chocobo1::CRC_32 ().addData(c, key.size()).finalize().toString();
}

int main() {
    const unsigned int NUMBER_OF_RUNS = 100;
    const unsigned int TABLE_SIZE = 1000;
    const double LOAD_FACTOR = 0.75;

    const unsigned int MAX_SIZE = int(TABLE_SIZE * LOAD_FACTOR);

    uint64_t time = 0;
    unsigned int collisions = 0;

    for (unsigned int run = 0; run < NUMBER_OF_RUNS; run++) {
        auto table = new string[TABLE_SIZE];

        auto keys = new string[MAX_SIZE];
        for (int i = 0; i < MAX_SIZE; i++) keys[i] = to_string(random());

        // Start timer
        uint64_t startTime = currentTime();

        for (int i = 0; i < MAX_SIZE; i++) {
            string key = keys[i];

            string hash = hashString(key);

            bool done = false;

            for (unsigned int attempt = 0; !done; attempt++) {
                unsigned long long shortHash = stoll(hash.substr(hash.size() - 8), nullptr, 16);
                unsigned int index = shortHash % TABLE_SIZE;
                if (table[index].empty()) {
                    table[index] = key;
                    done = true;
                }
                else collisions++;
            }

        }

        // End timer
        uint64_t endTime = currentTime();
        uint64_t duration = endTime - startTime;
        time += duration;
    }

    time /= NUMBER_OF_RUNS;
    collisions /= NUMBER_OF_RUNS;

    cout << time << endl;
    cout << collisions << endl;

    return 0;
}
