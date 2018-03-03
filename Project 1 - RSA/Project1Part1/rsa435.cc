
/***

	Generates the public and private keys for RSA.

	Written by Alex Walenchok
	Algorithms - The University of Akron - Spring 2018

***/

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "sha256.hh"
#include "BigIntegerLibrary.hh"
#include "rsaUtils.hh"

int main() {

	try {
		// Generate the keys using the function in the rsaUtils library
		generateKeys();
	} catch(const char* err) {
		std::cout << "ERROR:\nThe library threw an exception:\n" << err << std::endl;
	}

    return 0;
}