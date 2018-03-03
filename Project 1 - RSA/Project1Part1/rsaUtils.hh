#include "BigIntegerLibrary.hh"

#ifndef BIGINT435_RSAUTILS_HH
#define BIGINT435_RSAUTILS_HH

BigUnsigned generateLargePrime(const int& minDigits);
void writeFile(const std::string& outString, const char* fileName);
void generateKeys();
void sign(const std::string& fileName);
bool verify(std::string fileName, bool& isError);

#endif //BIGINT435_RSAUTILS_HH
