#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include "BigIntegerLibrary.hh"
#include "rsaUtils.hh"
#include "sha256.hh"

BigUnsigned generateLargePrime(const int& minDigits) {
    //srand(time(NULL));

    BigUnsigned prime = BigUnsigned(minDigits);
    for(int i = 0; i < minDigits - 1; i++) {
        prime = prime*10 + (rand() % 10);
    }

    // Keep last digit as 7 to increase probability of finding a prime
    prime = prime*10 + 7;

    // Check that the number is prime
    while(!(modexp(3, prime - 1, prime) == 1) &&
          !(modexp(7, prime - 1, prime) == 1)) {
        prime += 10;
    }

    return prime;
}

void writeFile(const std::string& outString, const char* fileName) {

    std::ofstream stream;
    stream.open(fileName, std::fstream::out);
    stream << outString;
    stream.close();

}

void generateKeys() {

    std::cout << "Generating new keys\n";

    /* Generate p and q */
    BigUnsigned p = generateLargePrime(278);
    BigUnsigned q = generateLargePrime(278);

    // Write out p and q to p_q.txt
    std::cout << "Writing p and q.\n";
    writeFile(bigUnsignedToString(p) + "\n" + bigUnsignedToString(q), "p_q.txt");

    /* Generate n and phi(n) */
    BigUnsigned n = p*q;
    BigUnsigned phi = (p - 1)*(q - 1);

    /* Generate e and d */
    // e must be odd integer, relatively prime to phi(n)
    BigInteger e = rand();
    BigInteger d;
    if(e % 2 == 0) { e += 1; }

    BigInteger gcd;
    BigInteger temp1;
    BigInteger temp2;
    bool finished = false;
    do {
        extendedEuclidean(e, phi, gcd, d, temp1);
        if(gcd == 1) {
            finished = true;
        } else {
            e += 2;
        }
    } while(!finished);
    d = (d % phi).getMagnitude();

    // Write out (d, n) and (e, n)
    std::cout << "Writing public and private keys.\n";
    writeFile((bigIntegerToString(e) + "\n" + bigUnsignedToString(n)), "e_n.txt");
    writeFile((bigIntegerToString(d) + "\n" + bigUnsignedToString(n)), "d_n.txt");

}

void sign(const std::string& fileName) {

    std::cout << "Generating signature.\n";

    /* Read File */
    std::ifstream mFile(fileName.c_str(), std::ios::binary);
    std::string data((std::istreambuf_iterator<char>(mFile)),
                     std::istreambuf_iterator<char>());

    // Run the file through the sha256 hash function
    std::string hash = sha256(data);
    BigUnsigned hashInt = stringToBigUnsigned16(hash);

    // Read in the private key (d, n)
    std::ifstream mPrivateKeyFile("d_n.txt");

    // If the private key file does not exist, then generate the keys
    if(!mPrivateKeyFile.is_open()) {
        std::cout << "The keys do not exists. Generating new keys.\n";
        generateKeys();
    }

    std::string temp;
    BigUnsigned d, n;

    // Parse out d
    std::getline(mPrivateKeyFile, temp);
    std::istringstream eISS(temp);
    std::string eStr, nStr;
    eISS >> eStr;

    // Parse out n
    std::getline(mPrivateKeyFile, temp);
    std::istringstream nISS(temp);
    nISS >> nStr;

    d = stringToBigUnsigned(eStr);
    n = stringToBigUnsigned(nStr);

    // (hashValue^d)%n -> Signature
    BigUnsigned signature = modexp(hashInt, stringToBigUnsigned(bigIntegerToString(d)), n);

    // Open signature file. Create it if it does not exist.
    // Write out the signature.
    std::ofstream signatureFile;
    signatureFile.open((fileName + ".signature").c_str(), std::fstream::out);
    signatureFile << bigUnsignedToString(signature);

    mFile.close();
    signatureFile.close();

}

bool verify(std::string fileName, bool& isError) {

    isError = false;

    // Read in the original file
    std::ifstream mFile(fileName.c_str(), std::ios::binary);
    if(!mFile.is_open()) {
        std::cout << "The file '" + fileName + "' does not exist in the current directory.\n";
        isError = true;
        return false;
    }
    std::string fileContents((std::istreambuf_iterator<char>(mFile)),
                             std::istreambuf_iterator<char>());

    // Read in the signature file
    std::ifstream mSigFile((fileName+".signature").c_str(), std::ios::binary);
    if(!mSigFile.is_open()) {
        std::cout << "The signature file '" + fileName + ".signature" + "' does not exist in the current directory.\n";
        isError = true;
        return false;
    }
    std::string sigString((std::istreambuf_iterator<char>(mSigFile)),
                            std::istreambuf_iterator<char>());
    BigUnsigned signatureContents = stringToBigUnsigned(sigString);

    // Read in the public key (e, n)
    std::ifstream mPubKeyFile("e_n.txt");

    if(!mPubKeyFile.is_open()) {
        std::cout << "The keys do not exist.\n";
        isError = true;
        return false;
    }

    std::string temp;
    BigUnsigned e, n;

    // Parse out e
    std::getline(mPubKeyFile, temp);
    std::istringstream eISS(temp);
    std::string eStr, nStr;
    eISS >> eStr;

    // Parse out n
    std::getline(mPubKeyFile, temp);
    std::istringstream nISS(temp);
    nISS >> nStr;

    e = stringToBigUnsigned(eStr);
    n = stringToBigUnsigned(nStr);

    mPubKeyFile.close();

    // Run the file through the sha256 hash function
    std::string hash = sha256(fileContents);
    BigUnsigned hashInt = stringToBigUnsigned16(hash);

    // (signature^e)%n
    BigUnsigned decryptedSig = modexp(signatureContents, e, n);

    // Compare the signature to the sha value
    return hashInt == decryptedSig;

}