//compile with
// -lresolv

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <resolv.h>
#include <cstring>
#include <string>
#include <string.h>

using namespace std;
int main(int argc, char** argv) {

    u_char nsbuf[4096];
    u_char dispbuf[4096];
    ns_msg msg;
    ns_rr rr;
    int i, j, l;
    std::string domain("gmail.com");
    l = res_query(domain.c_str(), ns_c_any, ns_t_mx, nsbuf, sizeof (nsbuf));
    if (l < 0) {
        perror(domain.c_str());        
    } else {
#ifdef USE_PQUERY
        res_pquery(&_res, nsbuf, l, stdout);
#else
        ns_initparse(nsbuf, l, &msg);
        l = ns_msg_count(msg, ns_s_an);
        for (j = 0; j < l; j++) {
            int prr = ns_parserr(&msg, ns_s_an, j, &rr);

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

            //BLOCK 2
            const u_char *rdata = ns_rr_rdata(rr) +1;
            printf("DataU_char-> %s\n", reinterpret_cast<const char*> (rdata));

            int len = strlen(reinterpret_cast<const char*> (rdata));
            printf("len->%d\n", len);

            char rdatatemp[1024];
            strncpy(rdatatemp, reinterpret_cast<const char*> (rdata), sizeof (rdatatemp));
            printf("DataChar->%s\n", rdatatemp);

            ns_sprintrr(&msg, &rr, NULL, NULL, reinterpret_cast<char*> (dispbuf), sizeof (dispbuf));
            printf("FullRecord->%s\n", dispbuf);
            printf("\n");
            
            char exchange[NS_MAXDNAME];
            
            // TTL
            //const u_char *rdata1 = ns_rr_rdata(rr);
            //const uint16_t pri = ns_get16(rdata);
            //int len1 = strlen(reinterpret_cast<const char*> (rdata));
            //int len2 = dn_expand(nsbuf, nsbuf + len1, rdata1 + 2, exchange, sizeof(exchange));
            //printf("Pri->%hu\n", pri);
            //printf("Exchange->%s\n", exchange);

        }
#endif
    }
    return 0;
}
