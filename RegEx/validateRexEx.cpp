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

std::vector<std::string> matches;
std::string pattern, subject;
subject = "Some text with a lots of foo foo and " +  char(255) + " again " + char(255);
pattern = "/" + char(255) + char(255) + "+|foo+/";
preg_match_all(pattern, subject, matches);

// email 
// ((\w+)@(\w+)\.(\w+))+

// regex email all for smtp "asasa" <email@email.com> , <email@eee.eee>, hello@eeee.ooo, "asa sa"<email@email.com>
	//        ((\"[\s\S]+\") <(\w+)@(\w+)\.(\w+)>|(\"[\s\S]+\")<(\w+)@(\w+)\.(\w+)>|(\w+)@(\w+)\.(\w+))+

// only emails: eee@email.com dla c++ bez / and /g
//      /((\w+)@(\w+)\.(\w+))+/g

// all emails smtp
//  ((((\"[\s\S]{1,50}\") <(\w+)@(\w+)\.(\w+)>)(,| ))|(<(\w+)@(\w+)\.(\w+)>)(,| )|((\w+)@(\w+)\.(\w+)))+

// mail FROM: <email@email.ccc>
//     /^((mail from:) <(\w+)@(\w+)\.(\w+)>(?=$))|^((mail from:)<(\w+)@(\w+)\.(\w+)>(?=$))/ig
// mail From: hello@email.commm
//   /^((mail from:) <(\w+)@(\w+)\.(\w+)>(?=$|\r\n))|^((mail from:)<(\w+)@(\w+)\.(\w+)>(?=$|\r\n))|^((mail from:) (\w+)@(\w+)\.(\w+)(?=$|\r\n))|^((mail from:)(\w+)@(\w+)\.(\w+)(?=$|\r\n))/ig
//  i - case insensitive
//  g -group match search multiple

// ipv4
//   ([0-9]{1,3}\.){3}[0-9]{1,3}(\/[0-9]{1,2})|([0-9]{1,3}\.){3}[0-9]{1,3}|\b([0-9]{1,3}\.){3}[0-9]{1,3}\b


// bonduary
//  (?<=(boundary="))([\s\S]| |w\[0-9]| )+?(?=("))
// html tag
//  (?<=(<tag>))([\s\S]| |w\[0-9]| )+?(?=(<\/tag>))

// From: emails
//  (?<=(From: ))(.*)+?(?=())

// To:
//  (?<=((\n)To: )|(^To: ))(.*)+?(?=())

// Subject email
//  (?<=(Subject: ))(.*)+?(?=())

// Content type
//  (?<=(Content-Type: text\/html; charset="))([\s\S]| |w\[0-9]| )+?(?=("))
//  (?<=(Content-Type: text\/plain; charset="))([\s\S]| |w\[0-9]| )+?(?=("))
//  (?<=(Content-Type: image\/gif; name="))(.*)+?(?=("))
//  (?<=(Content-Transfer-Encoding: ))(.*)+?(?=(|\r\n))
//  (?<=(Content-Disposition: attachment; filename="))(.*)+?(?=("))
//  (?<=(Content-Disposition: inline; filename="))(.*)+?(?=("))
//  (?<=(Content-ID: <))(.*)+?(?=(>))


// cut all empty lines 
// ^(\s*|\S)[\r\n]
// ^[\s\t]*(\r\n|\n|\r)


// Extraction of a sub-match
    std::regex base_regex("([a-z]+)\\.txt");
    std::smatch base_match;
 
    for (const auto &fname : fnames) {
        if (std::regex_match(fname, base_match, base_regex)) {
            // The first sub_match is the whole string; the next
            // sub_match is the first parenthesized expression.
            if (base_match.size() == 2) {
                std::ssub_match base_sub_match = base_match[1];
                std::string base = base_sub_match.str();
                std::cout << fname << " has a base of " << base << '\n';
            }
        }
    }
 

string BreakermindSslServer::MsgID(std::string email){
    long double tm = getTimestampMicro();
    std::string id = std::to_string(tm);
    // random msg id
    int msgID = 100000 + (rand() % static_cast<int>(999999 - 100000 + 1));
    return id.append("_").append(std::to_string(msgID)).append(std::string("_")).append(email);
}

long long int BreakermindSslServer::getTimestampMicro(){
    /* Example of timestamp in microsecond. */
    struct timeval timer_usec;
    long long int timestamp_usec; /* timestamp in microsecond */
    if (!gettimeofday(&timer_usec, NULL)) {
        timestamp_usec = ((long long int) timer_usec.tv_sec) * 1000000ll + (long long int) timer_usec.tv_usec;
    }else {
        timestamp_usec = -1;
    }
    return timestamp_usec;
}

long long int BreakermindSslServer::getTimestampMilliseconds(){
    /* Example of timestamp in millisecond. */
    struct timeb timer_msec;
    long long int timestamp_msec; /* timestamp in millisecond. */
    if (!ftime(&timer_msec)) {
        timestamp_msec = ((long long int) timer_msec.time) * 1000ll + (long long int) timer_msec.millitm;
    }
    else {
        timestamp_msec = -1;
    }
    return timestamp_msec;
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

vector<std::string> BreakermindSslServer::searchEmail(std::string string)
{
    vector<std::string> ve;
    ve.clear();
   // define a regular expression
    // single email: /^(\w+)(\.|_|-)?(\w*)@(\w+)(\.(\w+))$/ig
   // const std::regex pattern("(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+");
   std::regex pattern("(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+");

   std::cout << string << std::endl;
   std::sregex_iterator iter(string.begin(), string.end(), pattern);
   std::sregex_iterator end;

   while(iter != end)
   {
       std::cout << "size: " << iter->size() << std::endl;
       for(unsigned i = 0; i < iter->size(); ++i)       {
           std::cout << "the " << i + 1 << "th match" << ": " << (*iter)[i] << std::endl;
           ve.push_back((*iter)[i]);
       }
       ++iter;
   }
   return ve;
}

vector<vector<string>> BreakermindSslServer::findEmails(const string& s)
{
    const string& reg_ex("(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+");
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
    return captured_groups;
}

std::string BreakermindSslServer::findSubject(const string& s)
{
    // std::regex rgx("(Subject: )(\\w+\\W|\\.|\"|<|>|-|_| |!|,|[ąęśćźżńół]|[0-9]|\\.*|\\?)+(\\n|\\r\\n|\\0)");
    std::regex rgx("(Subject: )(\.*)+(\\n|\\r\\n|\\0)");
    std::smatch match;

    if (std::regex_search(s.begin(), s.end(), match, rgx))
    std::cout << "match Subject: " << match[0] << '\n';
    return match[0];
}

std::string BreakermindSslServer::findFrom(const string& s)
{
    std::regex rgx("(From: )(\.*)+(\\n|\\r\\n|\\0)");
    std::smatch match;

    if (std::regex_search(s.begin(), s.end(), match, rgx))
    std::cout << "match From: " << match[0] << '\n';
    return match[0];
}

std::string BreakermindSslServer::findTo(const string& s)
{
    std::regex rgx("(To: )(\.*)+(\\n|\\r\\n|\\0)");
    std::smatch match;

    if (std::regex_search(s.begin(), s.end(), match, rgx))
    std::cout << "match To: " << match[0] << '\n';
    return match[0];
}

//bool BreakermindSslServer::validEmail(std::string& email)
bool BreakermindSslServer::validEmail(std::string email)
{
   // define a regular expression
    // single email: /^(\w+)(\.|_|-)?(\w*)@(\w+)(\.(\w+))$/ig
   // const std::regex pattern("(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+");
   std::regex pattern("^(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+($|\\n|\\r\\n|\\0))");
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
   // std::regex pattern("^((mail from:)<(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>($|\\r\\n|\\n|\\0))|^((mail from:) <(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>($|\\r\\n|\\n|\\0))|^((mail from:) (\\w+)(\\.|_|-)?(\\w*)@(\\w+)\.(\\w+)($\\r\\n|\\n|\\0))|^((mail from:)(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)($|\\r\\n|\\n|\\0))|^((mail from:)<(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>(?=$|\\n|\\r\\n|\\0))|^((mail from:) <(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>(?=$|\\n|\\r\\n|\\0))|^((mail from:) (\\w+)(\\.|_|-)?(\\w*)@(\\w+)\.(\\w+)(?=$|\\n|\\r\\n|\\0))|^((mail from:)(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)(?=$|\\n|\\r\\n|\\0))", std::regex_constants::icase );
   std::regex pattern("^((mail from:)<(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)> BODY=8BITMIME($|\\n|\\r\\n|\\0))|^((mail from:)<(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>($|\\n|\\r\\n|\\0))|^((mail from:) <(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>($|\\n|\\r\\n|\\0))|^((mail from:) (\\w+)(\\.|_|-)?(\\w*)@(\\w+)\.(\\w+)($|\\n|\\r\\n|\\0))|^((mail from:)(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)($|\\n|\\r\\n|\\0))", std::regex_constants::icase );

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
    // std::regex pattern("^((rcpt to:)<(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>(\\r\\n)(?=$|\\n|\\r\\n|\\0))|^((rcpt to:) <(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>(\\r\\n)(?=$|\\n|\\r\\n|\\0))|^((rcpt to:) (\\w+)(\\.|_|-)?(\\w*)@(\\w+)\.(\\w+)(\\r\\n)(?=$|\\n|\\r\\n|\\0))|^((rcpt to:)(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)(\\r\\n)(?=$|\\n|\\r\\n|\\0))|^((rcpt to:)<(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>(?=$|\\n|\\r\\n|\\0))|^((rcpt to:) <(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>(?=$|\\n|\\r\\n|\\0))|^((rcpt to:) (\\w+)(\\.|_|-)?(\\w*)@(\\w+)\.(\\w+)(?=$|\\n|\\r\\n|\\0))|^((rcpt to:)(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)(?=$|\\n|\\r\\n|\\0))", std::regex_constants::icase );
    std::regex pattern("^((rcpt to:)<(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>($|\\n|\\r\\n|\\0))|^((rcpt to:) <(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)>($|\\n|\\r\\n|\\0))|^((rcpt to:)(\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)($|\\n|\\r\\n|\\0))|^((rcpt to:) (\\w+)(\\.|_|-)?(\\w*)@(\\w+)\\.(\\w+)($|\\n|\\r\\n|\\0))", std::regex_constants::icase );
   // try to match the string with the regular expression
   return std::regex_match(email, pattern);
}

bool BreakermindSslServer::validEhlo(std::string email)
{
   // expression (?=$|\\n|\\r\\n|\\0)
   // std::regex pattern("^((ehlo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\\-]*[ąęśćźżółA-Za-z0-9])(\\r\\n|\\0)(?=$|\\n|\\r\\n|\\0))|^((helo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\\-]*[ąęśćźżółA-Za-z0-9])(\\r\\n|\\0)(?=$|\\n|\\r\\n|\\0))|^((helo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\\-]*[ąęśćźżółA-Za-z0-9])(?=$|\\n|\\r\\n|\\0))|^((ehlo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\\-]*[ąęśćźżółA-Za-z0-9])(?=$|\\n|\\r\\n|\\0))", std::regex_constants::icase );
   // std::regex pattern("^((ehlo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\\-]*[ąęśćźżółA-Za-z0-9])|^((helo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\-]*[ąęśćźżółA-Za-z0-9])", std::regex_constants::icase );
   // try to match the string with the regular expression
   std::regex pattern("^((EHLO )(\.*)($|\\r\\n|\\n|\\0))|^((ehlo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\\-]*[ąęśćźżółA-Za-z0-9])($|\\r\\n|\\n|\\0))|^((helo) (([a-zA-Ząęśćźżół]|[a-zA-Ząęśćźżół][ąęśćźżóła-zA-Z0-9\\-]*[ąęśćźżóła-zA-Z0-9])\.)*([ąęśćźżółA-Za-z]|[ąęśćźżółA-Za-z][ąęśćźżółA-Za-z0-9\\-]*[ąęśćźżółA-Za-z0-9])($|\\r\\n|\\n|\\0))", std::regex_constants::icase );
   return std::regex_match(email, pattern);
}

bool BreakermindSslServer::validDataEnd(std::string data)
{
   // expression
   std::regex pattern("(\\.\\n)|(\\n\\.\\n)|(\\.$)|(\\.\\r\\n)|(\\r\\n\\.\\r\\n$|(\\.\\r\\n))");
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
        //cout << token << endl;
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

// multiple delimiters single characters delimiter: (,.-)
vector<string> BreakermindSslServer::SplitDelimiters(string str, string delimiters){
    vector <string> parts;
    char * pch;
    // cout << "String to split " << str;
    pch = strtok(convertStringToChar(str),delimiters.c_str()); // (char*)str.c_str();
    int i = 0;
    while (pch != NULL)
    {
        // printf ("\n%s\n",pch);
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
