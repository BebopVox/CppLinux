# walidacja rekordów SPF dns

### Funkcja/metoda 
validSpfIP(ipAddress,domena,spfTXT);

### How to

// dns
DnsSPF dns = DnsSPF();

int ok = dns.validateRangeIP("173.194.0.0/16","173.194.0.123");
cout<< " Valid range: " << ok << endl;

vector<string> spflist1 = dns.getDnsSPF("qflash.pl");
for (unsigned int i = 0; i < spflist1.size(); ++i)
{
  cout << spflist1.at(i) << endl;
  cout << "DNS IP is (qflash): " << dns.validSpfIP("92.222.7.98", "qflash.pl", spflist1.at(i)) << endl;
}


vector<string> spflist = dns.getDnsSPF("gmail.com");
for (unsigned int i = 0; i < spflist.size(); ++i)
{
  cout << spflist.at(i) << endl;
  cout << "DNS IP is: " << dns.validSpfIP("173.194.0.123", "gmail.com", spflist.at(i)) << endl;
}
