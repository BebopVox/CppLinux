#include "base64.h"
#include <iostream>

int main() {
  const std::string s = 
    "Hello string\n"
    "http:/breakermind.com\n"
    "passion for data\n";

  std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
  std::string decoded = base64_decode(encoded);

  std::cout << "encoded: " << std::endl << encoded << std::endl << std::endl;
  std::cout << "decoded: " << std::endl << decoded << std::endl;

  // with string
  std::string encoded1 = base64_encode(s, s.length());
  std::string decoded1 = base64_decode(encoded1);

  std::cout << "encoded1: " << std::endl << encoded1 << std::endl << std::endl;
  std::cout << "decoded1: " << std::endl << decoded1 << std::endl;

  // with string
  std::string encoded2 = base64_encode(s);
  std::string decoded2 = base64_decode(encoded2);

  std::cout << "encoded2: " << std::endl << encoded2 << std::endl << std::endl;
  std::cout << "decoded2: " << std::endl << decoded2 << std::endl;

  // Test all possibilites of fill bytes (none, one =, two ==)
  // References calculated with: https://www.base64encode.org/

  std::string rest0_original = "abc";
  std::string rest0_reference = "YWJj";

  std::string rest0_encoded = base64_encode(reinterpret_cast<const unsigned char*>(rest0_original.c_str()),
    rest0_original.length());
  std::string rest0_decoded = base64_decode(rest0_encoded);

  std::cout << "encoded:   " << rest0_encoded << std::endl;
  std::cout << "reference: " << rest0_reference << std::endl;
  std::cout << "decoded:   " << rest0_decoded << std::endl << std::endl;


  std::string rest1_original = "abcd";
  std::string rest1_reference = "YWJjZA==";

  std::string rest1_encoded = base64_encode(reinterpret_cast<const unsigned char*>(rest1_original.c_str()),
    rest1_original.length());
  std::string rest1_decoded = base64_decode(rest1_encoded);

  std::cout << "encoded:   " << rest1_encoded << std::endl;
  std::cout << "reference: " << rest1_reference << std::endl;
  std::cout << "decoded:   " << rest1_decoded << std::endl << std::endl;


  std::string rest2_original = "abcde";
  std::string rest2_reference = "YWJjZGU=";

  std::string rest2_encoded = base64_encode(reinterpret_cast<const unsigned char*>(rest2_original.c_str()),
    rest2_original.length());
  std::string rest2_decoded = base64_decode(rest2_encoded);

  std::cout << "encoded:   " << rest2_encoded << std::endl;
  std::cout << "reference: " << rest2_reference << std::endl;
  std::cout << "decoded:   " << rest2_decoded << std::endl << std::endl;

  return 0;
}
