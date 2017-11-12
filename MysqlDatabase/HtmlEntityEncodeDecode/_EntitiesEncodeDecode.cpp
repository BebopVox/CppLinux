// My simple example for sql injection
// Change char: ";", "&", "\"", "'", "<", ">", ":", "=", "!"
#include <string>
#include <iostream>

using namespace std;

string entitiesReplace( string str ) {
    string subs[] = { "&semi;", "&amp;", "&quot;", "&apos;", "&lt;", "&gt;", "&colon;", "&equals;", "&excl;" };
    string reps[] = { "#semi#", "#amp#", "#quot#", "#apos#", "#lt#", "#gt#", "#colon#", "#equals#", "#excl#" };
    size_t found;
    for( int j = 0; j < 9; j++ ) {
        do {
            found = str.find( subs[ j ] );
            if( found != string::npos ) {
                str.replace( found, subs[ j ].length(), reps[ j ] );
            }
        } while( found != string::npos );
       
    }
    return str;
}

string entitiesReplaceBack( string str ) {
    string subs[] = { "#semi#", "#amp#", "#quot#", "#apos#", "#lt#", "#gt#", "#colon#", "#equals#", "#excl#" };
    string reps[] = { "&semi;", "&amp;", "&quot;", "&apos;", "&lt;", "&gt;", "&colon;", "&equals;", "&excl;" };
    size_t found;
    for( int j = 0; j < 9; j++ ) {
        do {
            found = str.find( subs[ j ] );
            if( found != string::npos ) {
                str.replace( found, subs[ j ].length(), reps[ j ] );
            }
        } while( found != string::npos );
       
    }
    return str;
}

string entitiesDecode( string str ) {
    string subs[] = { "&semi;", "&amp;", "&quot;", "&apos;", "&lt;", "&gt;", "&colon;", "&equals;", "&excl;" };
    string reps[] = { ";", "&", "\"", "'", "<", ">", ":", "=", "!" };
    size_t found;
    for( int j = 0; j < 9; j++ ) {
        do {
            found = str.find( subs[ j ] );
            if( found != string::npos ) {
                str.replace( found, subs[ j ].length(), reps[ j ] );
            }
        } while( found != string::npos );
       
    }
    str = entitiesReplaceBack( str );
    return str;
}

string entitiesEncode( string str ) {
    str = entitiesReplace( str );
    string subs[] = { ";", "&", "\"", "'", "<", ">", ":", "=", "!" };
    string reps[] = { "&semi;", "&amp;", "&quot;", "&apos;", "&lt;", "&gt;", "&colon;", "&equals;", "&excl;" };
    size_t found;
    for( int j = 0; j < 9; j++ ) {
        do {
            found = str.find( subs[ j ] );
            if( found != string::npos ) {
                str.replace( found, subs[ j ].length(), reps[ j ] );
            }
        } while( found != string::npos );
       
    }
    return str;
}

int main() {
   
    std::string html = "<h1>Hello &quot; girls :) 'WooooW'! No i teraz jakiś \"CUDZYSLOWIE\". Nowe &amp; zdanie.";
   
    // Encode entities for mysql
    string encode = entitiesEncode( html );
    cout << "Encode: " << encode << endl << endl;
   
    // Decode
    string decode = entitiesDecode( encode );
    cout << "Decode : " << decode << endl << endl;
   
}
