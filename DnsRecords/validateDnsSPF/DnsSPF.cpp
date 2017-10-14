#include "dnsspf.h"

#define N 4096
#define MST (-2)

using namespace std;

// Check is server with this ip can send email for this domain
bool DnsSPF::DnsSPFvalidIP(string host, string ip){
    // get DNS spf records ip addresses
    vector<string> v = getDnsTXT(host);
    // is allowed ip address
    if (std::find(v.begin(), v.end(), ip) != v.end())
    {
        cout << "FOUND IP ADDRESS"<<endl;
        return true;
    }
    return false;
}

// return list ip addresses from TXT dns txt records only: > SMTPspf:1.2.3.4 or ip4:1.1.1.1
vector<string> DnsSPF::getDnsTXT(std::string domain)
{
	// ip list 
	vector<string> ips;

	try{
	    res_init();	    
	    u_char nsbuf[N];
	    //char dispbuf[N];
	    ns_msg msg;
	    ns_rr rr;
	    int i, l;

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
	                        for (unsigned int i=1; i<sm.size(); i++)
	                        {
	                            cout << "REGES " << sm[0] << endl;
	                            ips.push_back(sm[0]);
	                        }
	                    }
	                }
	              }
	        #endif
	    }
	}catch(...){
		return ips;
	}
    // ---------
    return ips;
}

// return TXT dns records list with v=spf1 i v=spf2
vector<string> DnsSPF::getDnsSPF(std::string domain)
{
    // TXT SPF list
    vector<string> spflist;
    try{
	    res_init();
	    u_char nsbuf[N];
	    //char dispbuf[N];
	    ns_msg msg;
	    ns_rr rr;
	    int i, l;

	    // TXT RECORD	    
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
	              /* just grab the TXT answer info */
	              ns_initparse(nsbuf, l, &msg);
	              l = ns_msg_count(msg, ns_s_an);
	              for (i = 0; i < l; i++)
	              {
	                ns_parserr(&msg, ns_s_an, i, &rr);
	                std::string spf = std::string((char*)ns_rr_rdata(rr));
	                 // cout << "TXT " << spf << endl;
	                if(spf.find(std::string("v=spf1")) != std::string::npos || spf.find(std::string("v=spf2")) != std::string::npos){
	                    spflist.push_back(spf);
	                }
	              }
	        #endif
	    }
	}catch(...){
		return spflist;
	}
    // return TXT records containing =spf
    return spflist;
}

// return email mx hosts list from dns
vector<string> DnsSPF::getDnsMX(std::string email) {
	// hosts list
	vector<string> mxhosts;

	try{
	    string domain = "localhost";
	    vector<string> em = splitDelimiter(email,"@");
	    if(em.size() > 1){
	        domain = em.at(em.size()-1);
	    }    

	    res_init();
	    u_char nsbuf[N];
	    //char dispbuf[N];
	    ns_msg msg;
	    ns_rr rr;
	    int i, l;

	    l = res_query(domain.c_str(), ns_c_any, ns_t_mx, nsbuf, sizeof(nsbuf));
	    if (l < 0)
	    {
	      perror(domain.c_str());
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
	                ns_parserr(&msg, ns_s_an, i, &rr);
	                // int prr = ns_parserr(&msg, ns_s_an, j, &rr);
	                // priority
	                char exchange[NS_MAXDNAME];
	                const u_char *rdata = ns_rr_rdata(rr);
	                // const uint16_t pri = ns_get16(rdata);
	                // int len = dn_expand(nsbuf, nsbuf + 250, rdata + 2, exchange, sizeof(exchange));
	                dn_expand(nsbuf, nsbuf + 250, rdata + 2, exchange, sizeof(exchange));
	                // priority
	                // printf("Pri->%d\n", pri);
	                // hostname
	                // printf("Exchange->%s\n", exchange);
	                mxhosts.push_back(exchange);
	              }
	        #endif
	    }
    }catch(...){
		return mxhosts;
	}
    // ---------
    return mxhosts;
}

// validate ip address in spf records
bool DnsSPF::validSpfIP(string ipAddress, string domain, string spf){
	try{
		// remve empty char
		domain = RemoveSpaces(domain);
		// explode spf
		vector<string> parts = splitDelimiter(spf," ");
		// erase first part v=spf1
		parts.erase(parts.begin());

		// don't check when spf contain +all or ~all allow all
		// if(inVector(parts,"+all") || inVector(parts,"~all")){
		if(inVector(parts,"+all")){
			return 1;
		}

		// validate records
		for (unsigned int i=0;i<parts.size();i++)
		{		
			// get part
			string record = parts.at(i);
			// replace empty char
			record = RemoveSpaces(record);			

			if(record.length() > 0){		
				// redirect
				if(Contain(record,"redirect=")){
					string hoop = RemoveSpaces(replaceAll(record,"redirect="," "));
					vector<string> rlist = getDnsSPF(hoop);
					for (unsigned int i = 0; i < rlist.size(); i++)
					{
						string rec = rlist.at(i);
						int val = validSpfIP(ipAddress,domain,rec);
						if (val)
						{
							return 1;
						}
					}										
				}		
				// ipv4:
				if(Contain(record,"ip4:")){
					string ip = RemoveSpaces(replaceAll(record,"ip4:"," "));
					if(Contain(record,"/")){
						// return validateRangeIP("173.194.0.0/16","173.194.0.123");
						int ok = validateRangeIP(ip,ipAddress);
						if(ok)return 1;
					}else if(ip == ipAddress){
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
					vector<string> mxhosts = getDnsMX(domain);
					for (unsigned int i = 0; i < mxhosts.size(); i++)
					{
						string host = mxhosts.at(i);
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
					// validate from dns txt spf not ip
					string hoop = RemoveSpaces(replaceAll(record,"include:"," "));
					vector<string> rlist = getDnsSPF(hoop);					
					for (unsigned int i = 0; i < rlist.size(); i++)
					{
						string rec = rlist.at(i);
						int val = validSpfIP(ipAddress,domain,rec);
						if (val)
						{
							return 1;
						}
					}
					//string host = RemoveSpaces(replaceAll(record,"include:"," "));
					//string ip = hostname_to_ip(host);
					//if(ip == ipAddress){
					//	return 1;
					//}			
				}
				// ptr - wszystkie servery z hostem z revers dns mogą wysyłać			
				if(Contain(record,"ptr") && record.length() == 3){
					// revers host
					string ptr = ip_to_hostname(ipAddress);
					// domena pasuje do revers
					if(domain == ptr){
						return 1;
					}			
				}
				// ptr - wszystkie servery z hostem z revers dns mogą wysyłać			
				if(Contain(record,"ptr:")){
					string host = RemoveSpaces(replaceAll(record,"ptr:"," "));					
					// revers host
					string ptr = ip_to_hostname(ipAddress);					
					// size
					if(ptr.length() > host.length()){
						int len = host.length();
						ptr = ptr.substr(ptr.length()-len);
						// revers host zawiera
						if(ptr == host){
							return 1;
						}
					}
					if(ptr == host){
						return 1;
					}
				}				
			}						
		}		
	}catch(...){
		return 0;
	}
	// default -all don't allow from ip
	return 0;
}

// if vector contain string return 1 else 0
bool DnsSPF::inVector(std::vector<string> v, string search){
	for(unsigned int i = 0; i < v.size(); i++){
		// remove empty char
	    if(v.at(i) == search){
	    	return 1;
	    }
	}
	return 0;
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

string DnsSPF::RemoveSpaces(string str)
{
	/*
  char* i = (char *)source.c_str();
  char* j = (char *)source.c_str();
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
  */
	std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
	str.erase(end_pos, str.end());
  	return str;
}

vector<string> DnsSPF::split(string s, char delim) {
	vector<string> v;
    auto i = 0;
    auto pos = s.find(delim);
    while (pos != string::npos) {
      v.push_back(s.substr(i, pos-i));
      i = ++pos;
      pos = s.find(delim, pos);
      if (pos == string::npos)
         v.push_back(s.substr(i, s.length()));
    }
    return v;
}

// validate if ip is in range "64.18.0.0/16"
bool DnsSPF::validateRangeIP(string ipsubnet,string ip){
	char * CIDR = (char *)ipsubnet.c_str();
	if(Contain(ipsubnet,"/")){
		uint32_t my_ip = inet_addr(ip.c_str());                  // Convert your IP string to uint32 "64.18.44.55"
		vector<string> vr = split(CIDR,'/');	
		if(vr.size() > 0){
			uint32_t range = inet_addr( vr.at(0).c_str() );// Convert IP part of CIDR to uint32
			int num_bits = atoi( vr.at(1).c_str() );       // Convert bits part of CIDR to int
			int mask = (1 << num_bits) - 1;                // Calc mask
			if ((my_ip & mask) == (range & mask)){
			    // cout << "OK IP RANGE" << endl;
			    return 1;
			}else{
				// cout << "ERROR MASK OK " << endl;
				return 0;
			}
		}	
	}
	return 0;
}


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
