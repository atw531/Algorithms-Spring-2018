// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "sha256.hh"
#include "BigIntegerLibrary.hh"
#include "rsaUtils.hh"

int main(int argc, char *argv[]) {

    /**
     * Valid arguments:
     * arg1 -> 's', 'v'
     * arg2 -> file name
     */
    std::string action;
    std::string inputFileName;
    if(argc == 3) {
        action = argv[01];
        inputFileName = argv[2];
    } else {
        std::cout << "Invalid argument count.\n";
        return 1;
    }

    if(action == "s") {

        std::string input = "";
        std::cout << "Would you like to generate new keys? [Y or N]: ";
        std::cin >> input;

        if(input == "Y" || input == "y") {
            generateKeys();
        }

        std::cout << "Signing file " + inputFileName + "\n";

        try {
            sign(inputFileName);
        } catch(char const* err) {
            std::cout << "ERROR:\nThe library threw an exception:\n" << err << std::endl;
        }

    } else if(action == "v") {
        std::cout << "Verifying file '" + inputFileName + "' with signature '" + inputFileName + ".signature'.\n";

        bool isError = false;
        if(verify(inputFileName, isError)) {
            std::cout << "File verified successfully!\n";
        } else {
            if(isError) {
                std::cout << "Error validating the file.\n";
            } else {
                std::cout << "File is unverified. The file has been modified.\n";
            }
        }

    } else {
        std::cout << "Invalid argument. Valid options: v (verify) or s (sign).\n";
    }

    return 0;
}