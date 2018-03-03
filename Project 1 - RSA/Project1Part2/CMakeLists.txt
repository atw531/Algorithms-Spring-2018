cmake_minimum_required(VERSION 3.8)
project(bigInt435)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        BigInteger.cc
        BigInteger.hh
        BigIntegerAlgorithms.cc
        BigIntegerAlgorithms.hh
        BigIntegerLibrary.hh
        BigIntegerUtils.cc
        BigIntegerUtils.hh
        BigUnsigned.cc
        BigUnsigned.hh
        BigUnsignedInABase.cc
        BigUnsignedInABase.hh
        NumberlikeArray.hh
		sha256.hh
		sha256.cc
        rsa435.cc
        rsaUtils.cc
        rsaUtils.hh)

add_executable(bigInt435 ${SOURCE_FILES})