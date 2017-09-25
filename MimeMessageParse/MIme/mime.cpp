#include "mime.h"

Mime::Mime()
{

}

// email validate
bool Mime::validEmail(std::string email){
    // std::regex pattern("[a-z0-9-_.ąęśćźżńół]+@[a-z0-9-_.ąęśćźżńół]+", std::regex_constants::icase);
    std::regex pattern("^[a-z0-9-_.ąęśćźżńół]+@((\\w+([-.]))+(\\w+))+$", std::regex_constants::icase);
    // try to match the string with the regular expression
    return std::regex_match(email, pattern);
}

// find emails
vector<vector<string>> Mime::findEmails(const string& s)
{
    const string& reg_ex("[a-z0-9-_.ąęśćźżńół]+@((\\w+([-.]))+(\\w+))");
    regex rx(reg_ex, regex_constants::icase);
    vector<vector<string>> captured_groups;
    vector<string> captured_subgroups;
    const std::sregex_token_iterator end_i;
    for (std::sregex_token_iterator i(s.cbegin(), s.cend(), rx);
        i != end_i;
        ++i)
    {
        captured_subgroups.clear();
        string group = *i;
        smatch res;
        if(regex_search(group, res, rx))
        {
            for(unsigned i=0; i<res.size() ; i++)
                captured_subgroups.push_back(res[i]);

            if(captured_subgroups.size() > 0)
                captured_groups.push_back(captured_subgroups);
        }

    }
    captured_groups.push_back(captured_subgroups);
    sort( captured_groups.begin(), captured_groups.end() );
    captured_groups.erase( unique( captured_groups.begin(), captured_groups.end() ), captured_groups.end() );
    return captured_groups;
}

bool Mime::Compare(vector<string> v1, vector<string> v2){
    if(v1.size() == v2.size()){
        return equal(v1.begin(), v1.end(), v2.begin());
    }else{
        return 0;
    }
}

std::string Mime::findSubject(const string& s)
{
    // std::regex rgx("(Subject: )(\\w+\\W|\\.|\"|<|>|-|_| |!|,|[ąęśćźżńół]|[0-9]|\\.*|\\?)+(\\n|\\r\\n|\\0)");
    std::regex rgx("(\nSubject: |^Subject: )(.)+(\\n|\\r\\n|\\0)");
    std::smatch match;

    if (std::regex_search(s.begin(), s.end(), match, rgx))
    //std::cout << "match Subject: " << match[0] << '\n';
    return match[0];
}

std::string Mime::findFrom(const string& s)
{
    std::regex rgx("(\\nFrom: |^From: ))(.)+(\\n|\\r\\n|\\0)");
    std::smatch match;

    if (std::regex_search(s.begin(), s.end(), match, rgx))
    //std::cout << "match From: " << match[0] << '\n';
    return match[0];
}

std::string Mime::findTo(const string& s)
{
    std::regex rgx("(\\nTo: |^To: ))(.)+(\\n|\\r\\n|\\0)");
    std::smatch match;

    if (std::regex_search(s.begin(), s.end(), match, rgx))
    //std::cout << "match To: " << match[0] << '\n';
    return match[0];
}
