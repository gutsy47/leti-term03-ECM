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
    // wtf is going on here? sizeof() = 16, there's only 10 actual and one '1' bit...
    static_assert(std::numeric_limits<long double>::is_iec559, "Only support IEC 559 (IEEE 754) long double");

    const size_t size = sizeof(long double);

    // Use union due to binary operands isn't working with double
    // And use array of char w/ size of long double (16 chars), cuz there's no int which uses 16 bytes.
    // One element of array represents one byte of double
    union LDoubleToBytesUnion {
        unsigned char bytes[size];
        long double value;
    };

    LDoubleToBytesUnion value{.value = iValue};
    std::string binaryLDouble;
    for (int i = 9; i >= 0; --i) {
        unsigned int order = sizeof(char) * 8;
        unsigned char mask = 1 << (order - 1);
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

/**
 * Swap bits x and y in ioVariable
 * @param[in/out] ioVariable - short int variable which will be changed
 * @param x - first bit position (indexation from 0)
 * @param y - second bit position (indexation from 0)
 */
void swapBitsSInt(short int& ioVariable, unsigned short x, unsigned short y) {
    const size_t size = sizeof(short int) * 8;

    if (x == y) return;                 // Nothing to do
    if (x >= size || y >= size) return; // Out of range error

    // Get masks & values of x & y bits
    unsigned xMask = 1 << (size - x - 1),
             yMask = 1 << (size - y - 1);
    bool bitValueX = ioVariable & xMask,
         bitValueY = ioVariable & yMask;


    // Swap values
    if (bitValueX != bitValueY) {
        ioVariable = (bitValueX ? short(ioVariable | yMask) : short(ioVariable & ~yMask));
        ioVariable = (bitValueY ? short(ioVariable | xMask) : short(ioVariable & ~xMask));
    }
}

/**
 * Swap bits x and y in ioVariable
 * @param[in/out] ioVariable - long double variable which will be changed
 * @param x - first bit position (indexation from 0)
 * @param y - second bit position (indexation from 0)
 */
void swapBitsLDouble(long double& ioVariable, unsigned short x, unsigned short y) {
    static_assert(std::numeric_limits<long double>::is_iec559, "Only support IEC 559 (IEEE 754) long double");

    const size_t size = sizeof(long double);

    if (x == y) return;                               // Nothing to do
    if (x + 48 >= size*8 || y + 48 >= size*8) return; // Out of range error

    // Binary operands do not work with double, so use union
    union LDoubleToBytesUnion {
        unsigned char bytes[size];
        long double value;
    };
    LDoubleToBytesUnion value{.value = ioVariable};

    // To get to the desired bit,
    // first need to get to the desired byte (X % 8),
    // then shift to the left by 7 - x % 8 bits
    unsigned char xMask = 1 << (7 - x % 8),
                  yMask = 1 << (7 - y % 8);

    // To get to the desired byte (element of array),
    // shift to the left by x/8 times.
    // Actually formula might be 16 - x/8, but there is some strange things about LD in MinGW or smh
    unsigned int xByte = 9 - x / 8,
                 yByte = 9 - y / 8;
    // Get the values of bits
    bool bitValueX = value.bytes[xByte] & xMask,
         bitValueY = value.bytes[yByte] & yMask;

    // Swap values
    if (bitValueX != bitValueY) {
        value.bytes[yByte] = (bitValueX ? short(value.bytes[yByte] | yMask) : short(value.bytes[yByte] & ~yMask));
        value.bytes[xByte] = (bitValueY ? short(value.bytes[xByte] | xMask) : short(value.bytes[xByte] & ~xMask));
    }

    ioVariable = value.value;
}