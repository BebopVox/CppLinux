// correct
// email
std::regex pattern("^(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+($|\\n|\\r\\n|\\0))");
// smtp
std::regex pattern("^((ehlo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\\-]*[ąęśćźżółA-Za-z0-9])($|\\r\\n|\\n|\\0))|^((helo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\\-]*[ąęśćźżółA-Za-z0-9])($|\\r\\n|\\n|\\0))", std::regex_constants::icase );
std::regex pattern("^((mail from:)<(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>($|\\n|\\r\\n|\\0))|^((mail from:) <(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>($|\\n|\\r\\n|\\0))|^((mail from:) (\\w+)(\\.|_|-)?(\\w*)@(\\w+)\.(\\w+)($|\\n|\\r\\n|\\0))|^((mail from:)(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)($|\\n|\\r\\n|\\0))", std::regex_constants::icase );
std::regex pattern("^((rcpt to:)<(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>($|\\n|\\r\\n|\\0))|^((rcpt to:) <(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>($|\\n|\\r\\n|\\0))|^((rcpt to:)(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)($|\\n|\\r\\n|\\0))|^((rcpt to:) (\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)($|\\n|\\r\\n|\\0))", std::regex_constants::icase );
std::regex pattern("(\\.\\n)|(\\n\\.\\n)|(\\.$)|(\\.\\r\\n)|(\\r\\n\\.\\r\\n$|(\\.\\r\\n))");
// smtp end DATA
std::regex pattern("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");

// demo examples
bool BreakermindSslServer::validEmail(std::string email)
{
   // define a regular expression
    // single email: /^(\w+)(\.|_|-)?(\w*)@(\w+)(\.(\w+))$/ig
   // const std::regex pattern("(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+");
   std::regex pattern("^(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+(?=$|\\n|\\r\\n|\\0))");
   // try to match the string with the regular expression
   return std::regex_match(email, pattern);
}

bool BreakermindSslServer::validEmailFrom(std::string email)
{
   // define a regular expression
    // single email: /^(\w+)(\.|_|-)?(\w*)@(\w+)(\.(\w+))$/ig
   // const std::regex pattern("(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+");
   // without - _
   // std::regex pattern("^((mail from:)<(\\w+)@(\\w+)\\.(\\w+)>(?=$|\\n|\\r\\n|\\0))|^((mail from:) <(\\w+)@(\\w+)\\.(\\w+)>(?=$|\\n|\\r\\n|\\0))|^((mail from:) (\\w+)@(\\w+)\.(\\w+)(?=$|\\n|\\r\\n|\\0))|^((mail from:)(\\w+)@(\\w+)\\.(\\w+)(?=$|\\n|\\r\\n|\\0))", std::regex_constants::icase );
   // with - _
   std::regex pattern("^((mail from:)<(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>(\\r\\n)(?=$|\\n|\\r\\n|\\0))|^((mail from:) <(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>(\\r\\n)(?=$|\\n|\\r\\n|\\0))|^((mail from:) (\\w+)(\\.|_|-)?(\\w*)@(\\w+)\.(\\w+)(\\r\\n)(?=$|\\n|\\r\\n|\\0))|^((mail from:)(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)(\\r\\n)(?=$|\\n|\\r\\n|\\0))", std::regex_constants::icase );
   // std::regex pattern("^((mail from:)<(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>)|^((mail from:) <(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>)|^((mail from:) (\\w+)(\\.|_|-)?(\\w*)@(\\w+)\.(\\w+))|^((mail from:)(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+))", std::regex_constants::icase );
   // try to match the string with the regular expression
   return std::regex_match(email, pattern);
}

bool BreakermindSslServer::validEmailRcpt(std::string email)
{
   // define a regular expression
   // single email: /^(\w+)(\.|_|-)?(\w*)@(\w+)(\.(\w+))$/ig
   // const std::regex pattern("(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+");
    // without _ -
   // std::regex pattern("^((rcpt to:)<(\\w+)@(\\w+)\\.(\\w+)>(?=$|\\n|\\r\\n|\\0))|^((rcpt to:) <(\\w+)@(\\w+)\\.(\\w+)>(?=$|\\n|\\r\\n|\\0))|^((rcpt to:) (\\w+)@(\\w+)\.(\\w+)(?=$|\\n|\\r\\n|\\0))|^((rcpt to:)(\\w+)@(\\w+)\\.(\\w+)(?=$|\\n|\\r\\n|\\0))", std::regex_constants::icase );
    // with - _
    std::regex pattern("^((rcpt to:)<(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>(?=$|\\n|\\r\\n|\\0))|^((rcpt to:) <(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>(\\r\\n)(?=$|\\n|\\r\\n|\\0))|^((rcpt to:) (\\w+)(\\.|_|-)?(\\w*)@(\\w+)\.(\\w+)(\\r\\n)(?=$|\\n|\\r\\n|\\0))|^((rcpt to:)(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)(?=$|\\n|\\r\\n|\\0))", std::regex_constants::icase );
   // try to match the string with the regular expression
   return std::regex_match(email, pattern);
}

bool BreakermindSslServer::validEhlo(std::string email)
{
   // expression (?=$|\\n|\\r\\n|\\0)
   std::regex pattern("^((ehlo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\\-]*[ąęśćźżółA-Za-z0-9])(\\r\\n)(?=$|\\n|\\r\\n|\\0))|^((helo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\-]*[ąęśćźżółA-Za-z0-9])(\\r\\n)(?=$|\\n|\\r\\n|\\0))", std::regex_constants::icase );
   // std::regex pattern("^((ehlo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\\-]*[ąęśćźżółA-Za-z0-9])|^((helo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\-]*[ąęśćźżółA-Za-z0-9])", std::regex_constants::icase );
   // try to match the string with the regular expression
   return std::regex_match(email, pattern);
}

bool BreakermindSslServer::validDataEnd(std::string data)
{
   // expression
   std::regex pattern("(\\n\\.\\n)|(\\.$)|(\\r\\n\\.\\r\\n$|^(.|\r|\n))");
   // try to match the string with the regular expression
   return std::regex_match(data, pattern);
}

bool BreakermindSslServer::validIP4(std::string ip)
{
   // expression
   std::regex pattern("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
   // try to match the string with the regular expression
   return std::regex_match(ip, pattern);
}

// string delimiter
vector<string> BreakermindSslServer::splitDelimiter(string str, string delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
        cout << token << endl;
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

// multiple delimiters single characters delimiter: (,.-)
vector<string> BreakermindSslServer::SplitDelimiters(string str, string delimiters){
    vector <string> parts;
    char * pch;
    cout << "String to split " << str;
    pch = strtok(convertStringToChar(str),delimiters.c_str()); // (char*)str.c_str();
    int i = 0;
    while (pch != NULL)
    {
        printf ("\n%s\n",pch);
        parts.push_back(pch);
        pch = strtok (NULL, delimiters.c_str());
        i++;
    }
    return parts;
}

string BreakermindSslServer::replaceAll( string s, string search, string replace ) {
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s.find( search, pos );
        if( pos == string::npos ) break;
        // Replace by erasing and inserting
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
    return s;
}

long double BreakermindSslServer::getTimestampMilli(){
    long double Timestamp = time(0);
    long double TimestampMS = Timestamp*1000;
    return TimestampMS;
}

long double BreakermindSslServer::getTimestamp(){
    long double Timestamp = time(0);
    return Timestamp;
}

string BreakermindSslServer::convertLongDoubleToString(long double lo) {
    stringstream bl;
    bl << lo;
    return bl.str();
}

char* BreakermindSslServer::convertStringToChar(std::string str){
    return (char*)str.c_str();
}

bool BreakermindSslServer::Contain(std::string str, std::string search){
    std::size_t found = str.find(search);
    if (found!=std::string::npos){
        return 1;
    }
    return 0;
}
