#include "utils.h"
#include <limits>

/**
 * Returns binary representation of int
 * @param[in] value - decimal integer
 * @return std::string - binary representation of value
 */
std::string getBitsOfSInt(short int iValue) {
    unsigned int order = sizeof(short int) * 8;
    unsigned int mask = 1 << (order - 1);
    std::string binarySInt;
    for (int i = 1; i <= order; ++i) {

        char bit = iValue & mask ? '1' : '0';

        binarySInt += bit;
        mask >>= 1;

        if (i == 1) binarySInt += ' ';
    }
    return binarySInt;
}


/**
 * Returns binary representation of double
 * @param[in] input - decimal long double
 * @return std::string - binary representation of value
 */
std::string getBitsOfLDouble(long double iValue) {
    static_assert(std::numeric_limits<long double>::is_iec559, "Only support IEC 559 (IEEE 754) long double");

    const size_t size = sizeof(long double);

    // Use union due to binary operands isn't working with double
    // And use array of char w/ size of long double (16 chars), cuz there's no int which uses 16 bytes.
    // One element of array represents one byte of double
    union DoubleIntUnion {
        unsigned char bytes[size];
        long double value;
    };

    DoubleIntUnion value{.value = iValue};
    std::string binaryLDouble;
    for (int i = 9; i >= 0; --i) {
        unsigned int order = sizeof(char) * 8;
        unsigned int mask = 1 << (order - 1);
        for (int j = 1; j <= order; j++) {

            char bit = value.bytes[i] & mask ? '1' : '0';

            binaryLDouble += bit;
            mask >>= 1;

            int currentBitIndex = (9 - i) * 8 + j;
            if (currentBitIndex == 1 || currentBitIndex == 16)
                binaryLDouble += ' ';
        }
    }

    return binaryLDouble;
}