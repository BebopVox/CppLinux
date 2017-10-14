# walidacja rekordów SPF dns

### Funkcja/metoda 
validSpfIP(ipAddress,domena,spfTXT);

### How to

// dns
DnsSPF dns = DnsSPF(); <br>
int ok = dns.validateRangeIP("173.194.0.0/16","173.194.0.123");<br>
cout<< " Valid range: " << ok << endl;<br><br>

vector<string> spflist1 = dns.getDnsSPF("qflash.pl");<br>
for (unsigned int i = 0; i < spflist1.size(); ++i)<br><br>
{<br>
  cout << spflist1.at(i) << endl;<br>
  cout << "DNS IP is (qflash): " << dns.validSpfIP("92.222.7.98", "qflash.pl", spflist1.at(i)) << endl;<br>
}<br><br>

vector<string> spflist = dns.getDnsSPF("gmail.com");<br>
for (unsigned int i = 0; i < spflist.size(); ++i)<br>
{<br>
  cout << spflist.at(i) << endl;<br>
  cout << "DNS IP is: " << dns.validSpfIP("173.194.0.123", "gmail.com", spflist.at(i)) << endl;<br>
}<br>

spflist = dns.getDnsSPF("_spf.google.com");<br>
for (unsigned int i = 0; i < spflist.size(); ++i)<br>
{<br>
  cout << spflist.at(i) << endl;<br>
}<br>
<br>
spflist = dns.getDnsSPF("_netblocks.google.com");<br>
for (unsigned int i = 0; i < spflist.size(); ++i)<br>
{<br>
  cout << spflist.at(i) << endl;<br>
}<br>
