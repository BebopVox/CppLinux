/**
 * compile: g++ -std=c++0x -o dnssd dnssd.cpp -lresolv
 * Your g++ compiler must have lambda support
 * 
 * Code based on examples from:
 *      http://www.cs.columbia.edu/~zwb/project/dotslash/dots_apache/dnsc.c
 *      http://people.samba.org/bzr/jerry/slag/unix/query-srv.c
 */ 
#include <arpa/nameser.h>
#include <functional>
#include <iostream>
#include <netinet/in.h>
#include <resolv.h>
#include <string.h>
#include <map>

using namespace std;

int main(int argc, char **argv) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " [SRV|TXT] [service]" << endl;
        return 1;
    }

    res_init();

    int response;
    unsigned char query_buffer[1024];
    {
        ns_type type;

        if (!strcmp(argv[1], "SRV")) {
            type= ns_t_srv;
        } else if (!strcmp(argv[1], "TXT")) {
            type= ns_t_txt;
        } else {
            cerr << "Invalid argument: '" << argv[1] << "'.  Must be [SRV|TXT]" << endl;
            return 1;
        }
        response= res_query(argv[2], C_IN, type, query_buffer, sizeof(query_buffer));
        if (response < 0) {
            cerr << "Error looking up service: '" << argv[2] << "'" << endl;
            return 2;
        }
    }

    ns_msg nsMsg;
    ns_initparse(query_buffer, response, &nsMsg);

    map<ns_type, function<void (const ns_rr &rr)>> callbacks;
    callbacks[ns_t_srv]= [&nsMsg](const ns_rr &rr) -> void {
        cout << ns_rr_ttl(rr) << endl;
        cout << ntohs(*(unsigned short*)ns_rr_rdata(rr)) << endl;
        cout << ntohs(*((unsigned short*)ns_rr_rdata(rr) + 1)) << endl;
        cout << ntohs(*((unsigned short*)ns_rr_rdata(rr) + 2)) << endl;

        char name[1024];
        dn_expand(ns_msg_base(nsMsg), ns_msg_end(nsMsg), 
                ns_rr_rdata(rr) + 6, name, sizeof(name));
        cout << name << endl;
    };
    callbacks[ns_t_txt]= [&nsMsg](const ns_rr &rr) -> void {
        cout << ns_rr_rdata(rr) + 1 << endl;
    };

    for(int x= 0; x < ns_msg_count(nsMsg, ns_s_an); x++) {
        ns_rr rr;
        ns_parserr(&nsMsg, ns_s_an, x, &rr);
        ns_type type= ns_rr_type(rr);
        if (callbacks.count(type)) {
            callbacks[type](rr);
        }
    }
    return 0;
}
