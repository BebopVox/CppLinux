// stream files
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string settings[100];

int main(int argc, char *argv[])
{
    // Mime validate
    Mime m = Mime();
    cout << "Email " <<  m.validEmail("he.llo-ala.dam@ddd.fff-fff.com") << endl;

    // find From: in DATA
    // findFrom(DATA);

    // cut emails and sort
    vector<vector<string>> emails = m.findEmails("heniek <hello-ala.dam@dddfff-fff.com>, dam@ddd.fff.com hhhh@ddd.online, ddd@www.sss");
    vector<vector<string>> emails2 = m.findEmails("dam@ddd.fff.com hhhh@ddd.online, <hello-ala.dam@dddfff-fff.com> ");

    try{
        cout << "email size " << emails.size() << endl;
        for(int i=0; i < emails.size();i++){
            vector<string> eml = emails.at(i) ;
            vector<string> eml2 = emails2.at(i);

            cout << "Compare " << m.Compare(eml, eml2) << endl;

            cout << eml.at(0) << endl;
            cout << eml2.at(0) << endl;
        }
    }catch(std::exception e){
        e.what();
    }
    return 0;
}
