#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0};
        size_t len = k.length();

        if (len == 0) {
            return 0;
        }

        int wIndex = 4;
        size_t pos = len;

        while (wIndex >= 0 && pos > 0) {
            size_t chunkStart;
            if (pos >= 6) {
                chunkStart = pos - 6;
            }
            else {
                chunkStart = 0;
            }
            size_t chunkSize = pos - chunkStart;

            w[wIndex] = 0;
            for (size_t i = 0; i < chunkSize; ++i) {
                w[wIndex] = w[wIndex] * 36 + letterDigitToNumber(k[chunkStart + i]);
            }

            pos = chunkStart;
            wIndex--;
        }

        unsigned long long hash = 0;
        for (int i = 0; i < 5; ++i) {
            hash += rValues[i] * w[i];
        }
        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = tolower(letter);
        if (letter >= 'a' && letter <= 'z') {
            return letter - 'a';
        }
        else if (letter >= '0' && letter <= '9') {
            return 26 + (letter - '0');
        }
        else {
            return 0; // Invalid character
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i = 0; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
