#ifndef MIME_H
#define MIME_H

#include <string>
#include <regex>

using namespace std;

class Mime
{
public:
    Mime();
    bool validEmail(std::string email);
    vector<vector<string>> findEmails(const string& s);
    bool Compare(vector<string> v1, vector<string> v2);
    std::string findSubject(const string& s);
    std::string findFrom(const string& s);
    std::string findTo(const string& s);
};

#endif // MIME_H
