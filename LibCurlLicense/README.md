# lib curl https get request validate license key

```
#include <string>
#include <iostream>
#include "curl-license.h"
#include <curl/curl.h>

using namespace std;

int main(){
  // Create object
  LicenseCurl lic;
  // Validate key if 1 OK when 0 error
  cout << lic.checkKey("key");
}
```
