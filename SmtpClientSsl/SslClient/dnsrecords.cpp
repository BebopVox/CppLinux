#include "dnsrecords.h"

DnsRecords::DnsRecords()
{

}

vector<string> DnsRecords::getMX(std::string email, int show = 0, int logToFile = 0)
{
    string domain = "localhost";
    vector<string> em = splitDelimiter(email,"@");
    if(em.size() > 1){
        domain = em.at(em.size()-1);
    }
    vector<string> mxhosts;
    res_init();
    u_char nsbuf[N];
    char dispbuf[N];
    ns_msg msg;
    ns_rr rr;
    int i, l;
    if(show > 0){
        // HEADER
        printf("Domain : %s\n", std::string(domain));
        // MX RECORD
        printf("MX records : \n");
    }
    l = res_query(domain.c_str(), ns_c_any, ns_t_mx, nsbuf, sizeof(nsbuf));
    if (l < 0)
    {
      // perror(domain.c_str());
      return mxhosts;
    } else {
        #ifdef USE_PQUERY
              /* this will give lots of detailed info on the request and reply */
              res_pquery(&_res, nsbuf, l, stdout);
        #else
            /* just grab the MX answer info */
            ns_initparse(nsbuf, l, &msg);
            l = ns_msg_count(msg, ns_s_an);
            for (i = 0; i < l; i++)
            {
                ns_parserr(&msg, ns_s_an, i, &rr); // int prr = ns_parserr(&msg, ns_s_an, j, &rr);
                // priority
                char exchange[NS_MAXDNAME];
                const u_char *rdata = ns_rr_rdata(rr);
                const uint16_t pri = ns_get16(rdata);
                int len = dn_expand(nsbuf, nsbuf + 250, rdata + 2, exchange, sizeof(exchange));
                if(show > 0){
                    // priority
                    printf("Pri->%d\n", pri);
                    // hostname
                    printf("Exchange->%s\n", exchange);
                }
                mxhosts.push_back(exchange);

                if(logToFile > 0){
                    // get the current time
                    time_t rawtime;
                    tm * ptm;
                    time ( &rawtime );
                    ptm = gmtime ( &rawtime );
                    // log this information to ipaddr.log file
                    ofstream ipaddr_log("ipaddr.log", ios::app);
                    ipaddr_log << (ptm->tm_hour+MST%24) << ":" << (ptm->tm_min) << " " << domain << " " << exchange << " (" << hostnameIP(exchange) << ")" << endl;
                    ipaddr_log.close();
                }
            }
        #endif
    }
    // ---------
    return mxhosts;
}

// string delimiter
vector<string> DnsRecords::splitDelimiter(string str, string delim)
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
        // cout << token << endl;
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

// Get ip from domain name
string DnsRecords::hostnameIP(std::string hostname)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
    char ip[255];
    if ( (he = gethostbyname( (char*)hostname.c_str() ) ) == NULL)
    {
        // get the host info
        herror("gethostbyname");
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

// valid ip4
bool DnsRecords::validIPv4(const string& str)
{
    struct sockaddr_in sa;
    return inet_pton(AF_INET, str.c_str(), &(sa.sin_addr))!=0;
}

// valid ip6
bool DnsRecords::validIPv6(const string& str)
{
    struct sockaddr_in6 sa;
    return inet_pton(AF_INET6, str.c_str(), &(sa.sin6_addr))!=0;
}

