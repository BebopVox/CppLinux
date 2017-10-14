// Get ip from domain name
string DnsSPF::hostname_to_ip(std::string hostname)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
    char ip[250];
    if ( (he = gethostbyname( (char*)hostname.c_str() ) ) == NULL)
    {
        // get the host info
        // herror("gethostbyname");
        perror("gethostbyname");
        return "";
    }
    addr_list = (struct in_addr **) he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
    }
    cout << std::string(ip);
    return std::string(ip);
}

string DnsSPF::ip_to_hostname(std::string ip)
{
  struct hostent *hent;
  struct in_addr addr;
  if(!inet_aton(ip.c_str(), &addr))
    return((char *)ip.c_str());
  if((hent = gethostbyaddr((char *)&(addr.s_addr), sizeof(addr.s_addr),AF_INET)))
  {
    strcpy((char *)ip.c_str(), hent->h_name);
  }
  return((char *)ip.c_str());
}

// valid ip4
bool DnsSPF::is_ipv4_address(const string& str)
{
    struct sockaddr_in sa;
    return inet_pton(AF_INET, str.c_str(), &(sa.sin_addr))!=0;
}
// valid ip6
bool DnsSPF::is_ipv6_address(const string& str)
{
    struct sockaddr_in6 sa;
    return inet_pton(AF_INET6, str.c_str(), &(sa.sin6_addr))!=0;
}

// string delimiter
vector<string> DnsSPF::splitDelimiter(string str, string delim)
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

bool DnsSPF::Contain(std::string str, std::string search){
    std::size_t found = str.find(search);
    if (found!=std::string::npos){
        return 1;
    }
    return 0;
}

string DnsSPF::replaceAll( string s, string search, string replace ) {
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

char* DnsSPF::replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos){
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

void DnsSPF::RemoveSpaces(char* source)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}
