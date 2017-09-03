#include "dnsspf.h"
#include <iostream>

#define N 4096
#define MST (-2)

using namespace std;

DnsSPF::DnsSPF(std::string domain)
{

    u_char nsbuf[N];
        char dispbuf[N];
        ns_msg msg;
        ns_rr rr;
        int i, l;

        // HEADER
        printf("Domain : %s\n", std::string(domain));

        // MX RECORD
        printf("MX records : \n");
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
                    printf("Pri->%d\n", pri);
                    printf("Exchange->%s\n", exchange);

                    ns_sprintrr(&msg, &rr, NULL, NULL, dispbuf, sizeof(dispbuf));
                    printf ("\t%s\n", dispbuf);
                    cout << "IP Address " << hostname_to_ip(exchange) << endl;

                    // get the current time
                    time_t rawtime;
                    tm * ptm;
                    time ( &rawtime );
                    ptm = gmtime ( &rawtime );

                    // log this information to ipaddr.log
                    ofstream ipaddr_log("ipaddr.log", ios::app);
                    ipaddr_log << (ptm->tm_hour+MST%24) << ":" << (ptm->tm_min) << " " << domain << " " << exchange << " (" << hostname_to_ip(exchange) << ")" << endl;
                    ipaddr_log.close();

                  }
            #endif
        }
        // ---------


}

/*
    Get ip from domain name
 */

string DnsSPF::hostname_to_ip(std::string hostname)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
    char ip[250];

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
