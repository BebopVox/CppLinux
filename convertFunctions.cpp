long double getTimestampMilli(){
    long double Timestamp = time(0);
    long double TimestampMS = Timestamp*1000;
    return TimestampMS;
}

long double getTimestamp(){
    long double Timestamp = time(0);
    return Timestamp;
}

string convertLongDoubleToString(long double lo) {
    stringstream bl;
    bl << lo;
    return bl.str();
}
// String to char
char* convertStringToChar(std::string str){
    return (char*)str.c_str();
}

// String to const char
const char* convertStringToChar(std::string str){
    return str.c_str();
}

bool validEmail(std::string email)
{
   // define a regular expression
   const std::regex pattern
      ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

   // try to match the string with the regular expression
   return std::regex_match(email, pattern);
}

// string delimiter
vector<string> splitDelimiter(string str, string delim)
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
vector<string> SplitDelimiters(string str, string delimiters){
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

string replaceAll( string s, string search, string replace ) {
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
