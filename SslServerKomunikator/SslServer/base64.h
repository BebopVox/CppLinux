#ifndef BASE64_H
#define BASE64_H

#include <string>

// using namespace std;

class Base64
{
public:
    Base64();
    std::string base64_encode(unsigned char const* , unsigned int len);
    std::string base64_encode(std::string str , unsigned int len);
    std::string base64_encode(std::string str);
    static std::string base64_decode(std::string const& s);
    static inline bool is_base64(unsigned char c);
    static const std::string base64_chars;
};

#endif // BASE64_H
