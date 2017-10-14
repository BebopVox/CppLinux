#include "dnsspf.h"
#include <iostream>
#include <regex>
// ip address
#include <sstream>
// network
#include <arpa/inet.h>
// str sockadr
#include <netdb.h>

// find
#include <algorithm>

// perror
#include <errno.h>

#define N 4096
#define MST (-2)

using namespace std;

// Check is server with this ip can send email for this domain
bool DnsSPF::DnsSPFvalidIP(string host, string ip){
    // get DNS spf records ip addresses
    vector<string> v = DnsTXT(host);
    // is allowed ip address
    if (std::find(v.begin(), v.end(), ip) != v.end())
    {
        cout << "FOUND IP ADDRESS"<<endl;
        return true;
    }
    return false;
}

// return list ip addresses from TXT dns txt records only: > SMTPspf:1.2.3.4
vector<string> DnsSPF::DnsTXT(std::string domain)
{
    res_init();
    vector<string> ips;

    u_char nsbuf[N];
    char dispbuf[N];
    ns_msg msg;
    ns_rr rr;
    int i, l;

    // HEADER
    // printf("Domain : %s\n", std::string(domain));
	cout << "Domain " << std::string(domain) << endl;

    // MX RECORD
    printf("TXT records : \n");
    // l = res_query(domain.c_str(), ns_c_any, ns_t_txt, nsbuf, sizeof(nsbuf));
    l = res_query(domain.c_str(), C_IN, ns_t_txt, nsbuf, sizeof(nsbuf));
    if (l < 0)
    {
      perror(domain.c_str());
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
                ns_parserr(&msg, ns_s_an, i, &rr);
                std::string spf = std::string((char*)ns_rr_rdata(rr));
                 // cout << "TXT " << spf << endl;
                if(spf.find(std::string("SMTPspf:")) != std::string::npos || spf.find(std::string("v=spf1")) != std::string::npos){
                    cout << "TXT " <<  spf << endl;

                    // const regex r("(\\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b)");
                    // const regex r("(([0-9]{1,3}).([0-9]{1,3}).([0-9]{1,3}).([0-9]{1,3}))");
                    const regex r("(\\d{1,3}(\\.\\d{1,3}){3})");
                    smatch sm;
                    if (regex_search(spf, sm, r))
                    {
                        cout << "input string has " << sm.size() << " matches " << endl;
                        for (int i=1; i<sm.size(); i++)
                        {
                            cout << "REGES " << sm[0] << endl;
                            ips.push_back(sm[0]);
                        }
                    }
                }

                // get the current time
                time_t rawtime;
                tm * ptm;
                time ( &rawtime );
                ptm = gmtime ( &rawtime );

                // log this information to ipaddr.log
                ofstream ipaddr_log("ipaddr.log", ios::app);
                ipaddr_log << (ptm->tm_hour+MST%24) << ":" << (ptm->tm_min) << " " << domain << " " << ns_rr_rdata(rr) << " " << endl;
                ipaddr_log.close();

              }
        #endif
    }
    // ---------
    return ips;
}

void DnsSPF::DnsMX(std::string domain)
{

    res_init();

    u_char nsbuf[N];
        char dispbuf[N];
        ns_msg msg;
        ns_rr rr;
        int i, l;

        // HEADER
        // printf("Domain : %s\n", std::string(domain));
	cout << "Domain " << std::string(domain) << endl;

        // MX RECORD
        // printf("MX records : \n");
	cout << " Mx records " << endl;

        l = res_query(domain.c_str(), ns_c_any, ns_t_mx, nsbuf, sizeof(nsbuf));
        if (l < 0)
        {
          perror(domain.c_str());
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
                    ns_parserr(&msg, ns_s_an, i, &rr);
                    // int prr = ns_parserr(&msg, ns_s_an, j, &rr);

                    //BLOCK 1
                    char *cp;
                    cp = (char *) ns_rr_name(rr);
                    printf("CP->%s\n", (char *) cp);
                    int i1 = ns_rr_type(rr);
                    printf("Type->%d\n", i1);
                    int i2 = ns_rr_class(rr);
                    printf("Class->%d\n", i2);
                    int i3 = ns_rr_ttl(rr);
                    printf("TTL->%d\n", i3);
                    int i4 = ns_rr_rdlen(rr);
                    printf("DataLength->%d\n", i4);

                    // priority
                    char exchange[NS_MAXDNAME];
                    const u_char *rdata = ns_rr_rdata(rr);
                    const uint16_t pri = ns_get16(rdata);
                    int len = dn_expand(nsbuf, nsbuf + 250, rdata + 2, exchange, sizeof(exchange));
                    // priority
                    printf("Pri->%d\n", pri);
                    // hostname
                    printf("Exchange->%s\n", exchange);

                    ns_sprintrr(&msg, &rr, NULL, NULL, dispbuf, sizeof(dispbuf));
                    printf ("\t%s\n", dispbuf);
                    cout << "IP Address " << hostname_to_ip(exchange) << endl;

                    // TXT
                    cout << "TXT " <<  ns_rr_rdata(rr) << endl;
                    //cout << ns_rr_ttl(rr) << endl;
                    //cout << ntohs(*(unsigned short*)ns_rr_rdata(rr)) << endl;
                    //cout << ntohs(*((unsigned short*)ns_rr_rdata(rr) + 1)) << endl;
                    //cout << ntohs(*((unsigned short*)ns_rr_rdata(rr) + 2)) << endl;

                    /*
                    // get the current time
                    time_t rawtime;
                    tm * ptm;
                    time ( &rawtime );
                    ptm = gmtime ( &rawtime );

                    // log this information to ipaddr.log
                    ofstream ipaddr_log("ipaddr.log", ios::app);
                    ipaddr_log << (ptm->tm_hour+MST%24) << ":" << (ptm->tm_min) << " " << domain << " " << exchange << " (" << hostname_to_ip(exchange) << ")" << endl;
                    ipaddr_log.close();
                    */

                  }
            #endif
        }
        // ---------
}

// return email mx hosts list from dns
vector<string> DnsSPF::DnsMX2(std::string email)
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

        // HEADER
        // printf("Domain : %s\n", std::string(domain));

        // MX RECORD
        // printf("MX records : \n");
        l = res_query(domain.c_str(), ns_c_any, ns_t_mx, nsbuf, sizeof(nsbuf));
        if (l < 0)
        {
          perror(domain.c_str());
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
                    ns_parserr(&msg, ns_s_an, i, &rr);
                    // int prr = ns_parserr(&msg, ns_s_an, j, &rr);

                    // priority
                    char exchange[NS_MAXDNAME];
                    const u_char *rdata = ns_rr_rdata(rr);
                    const uint16_t pri = ns_get16(rdata);
                    int len = dn_expand(nsbuf, nsbuf + 250, rdata + 2, exchange, sizeof(exchange));
                    // priority
                    // printf("Pri->%d\n", pri);
                    // hostname
                    // printf("Exchange->%s\n", exchange);
                    mxhosts.push_back(exchange);

                    /*
                    // get the current time
                    time_t rawtime;
                    tm * ptm;
                    time ( &rawtime );
                    ptm = gmtime ( &rawtime );

                    // log this information to ipaddr.log
                    ofstream ipaddr_log("ipaddr.log", ios::app);
                    ipaddr_log << (ptm->tm_hour+MST%24) << ":" << (ptm->tm_min) << " " << domain << " " << exchange << " (" << hostname_to_ip(exchange) << ")" << endl;
                    ipaddr_log.close();
                    */
                  }
            #endif
        }
        // ---------
        return mxhosts;
}

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

string DnsSPF::replaceAll(string s,string search,string replace) {
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


bool DnsSPF::validSpfIP(string ipAddress, string domain, string spf){
	try{
		// remve empty char
		domain = RemoveSpaces(domain);
		// explode spf
		vector<string> parts = splitDelimiter(spf," ");
		// erase first part v=spf1
		parts.erase(parts.begin());

		for (unsigned int i=0;i<parts.size();i++)
		{		
			// get part
			string record = parts.at(i);
			// replace empty char
			record = RemoveSpaces(record);			

			if(record.length() > 0){
				// +all, ~all - allow all records
				if(Contain(record,"+all") || Contain(record,"~all")){
					return 1;
				}
				// ipv4:
				if(Contain(record,"ip4:")){
					string ip = RemoveSpaces(replaceAll(record,"ip4:"," "));
					if(ip == ipAddress){
						return 1;
					}			
				}
				// ipv6:
				if(Contain(record,"ip6:")){
					string ip = RemoveSpaces(replaceAll(record,"ip6:"," "));
					if(ip == ipAddress){
						return 1;
					}			
				}
				// a				
				if(Contain(record,"a") && record.length() == 1){
					string ip = hostname_to_ip(domain);
					if(ip == ipAddress){
						return 1;
					}			
				}
				// mx records for domain
				if(Contain(record,"mx") && record.length() == 2){
					string email = "m@";
					email.append(domain);
					vector<string> mxhosts = DnsMX2(email);
					for (int i = 0; i < mxhosts.size(); i++)
					{
						string ip = hostname_to_ip(host);	
						if(ip == ipAddress){
							return 1;
						}			
					}			
				}
				// a:
				if(Contain(record,"a:")){
					string host = RemoveSpaces(replaceAll(record,"a:"," "));
					string ip = hostname_to_ip(host);
					if(ip == ipAddress){
						return 1;
					}			
				}
				// include:
				if(Contain(record,"include:")){
					string host = RemoveSpaces(replaceAll(record,"include:"," "));
					string ip = hostname_to_ip(host);
					if(ip == ipAddress){
						return 1;
					}			
				}
				// all
				if(Contain(record,"-all")){
					return 0;
				}
			}
		}
	}catch(...){
		return 0;
	}
	return 0;
}
