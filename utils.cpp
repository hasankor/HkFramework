#include "utils.h"

int Utils::calculateJammerStartAngle(int pAngle)
{
     return ((pAngle - (SCANNABLE_RANGE / 2)) + 360) % 360;
}

int Utils::calculateJammerEndAngle(int pAngle)
{
    return ((pAngle + (SCANNABLE_RANGE / 2)) + 360) % 360;
}

uint8_t Utils::twosComplement(uint8_t val)
{
    return -val;
}

uint8_t Utils::calculateChecksumWithTwosComplement(const unsigned char *data, unsigned int size)
{
    uint8_t sum = 0;
    for (unsigned int index = 0; index < size; ++index) {
        sum += data[index];
    }
    return twosComplement(sum);
}

uint8_t Utils::calculateChecksumWithTwosComplement(const char *data, unsigned int size)
{
    return calculateChecksumWithTwosComplement((const uchar*)data, size);
}

uint8_t Utils::calculateChecksumWithTwosComplement(const QByteArray &pBuffer)
{
    return calculateChecksumWithTwosComplement(pBuffer.constData(), pBuffer.size());
}

bool Utils::checkChecksum(const QByteArray &pBuffer)
{
    return calculateChecksumWithTwosComplement(pBuffer.constData(), pBuffer.size()-1) == (uint8_t)(pBuffer[pBuffer.size()-1]);
}
