#ifndef UTILS_H
#define UTILS_H

#include <QVariant>

class Utils
{
public:
    template<typename QEnum>
    static QString QtEnumToString (const QEnum value)
    {
      return QVariant::fromValue(value).toString();
    }

    static int calculateJammerStartAngle(int pAngle);
    static int calculateJammerEndAngle(int pAngle);


    static uint8_t twosComplement(uint8_t val);

    static uint8_t calculateChecksumWithTwosComplement(const unsigned char *data, unsigned int size);

    static uint8_t calculateChecksumWithTwosComplement(const char *data, unsigned int size);

    // same as above, convenience function
    static uint8_t calculateChecksumWithTwosComplement(const QByteArray &pBuffer);

    static bool checkChecksum(const QByteArray &pBuffer);

    template <typename T>
    static bool setBit(T& var, int index, bool data) {
        if(index >= sizeof(T)*8) {
            return false;
        }

        int mask = 1 << index;
        var = ((var & ~mask) | (data << index));
        return true;
    }

public:

    static int const SCANNABLE_RANGE = 15;

private:
    Utils(){}
};

#endif // UTILS_H
