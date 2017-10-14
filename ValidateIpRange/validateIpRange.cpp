vector<string> split(string s, char delim) {
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

// first example
uint32_t ip = inet_addr("64.18.0.22"); // value to check
uint32_t netip = inet_addr("64.18.0.0"); // network ip to compare with
uint32_t netmask = inet_addr("255.255.0.0"); // network ip subnet mask
if ((netip & netmask) == (ip & netmask))
    // is on same subnet...
  cout << "OK " << endl;
else
    // not on same subnet...
    cout << "NOT OK " << endl;
	

// second example
char CIDR[100] = "64.18.0.0/16";
uint32_t my_ip = inet_addr( "64.18.44.55" );            // Convert your IP string to uint32
vector<string> vr = split(CIDR,'/');	
if(vr.size() > 0){
  uint32_t range = inet_addr( vr.at(0).c_str() );   // Convert IP part of CIDR to uint32
  int num_bits = atoi( vr.at(1).c_str() );     // Convert bits part of CIDR to int
  int mask = (1 << num_bits) - 1;                // Calc mask

  if ((my_ip & mask) == (range & mask)){
      cout << "OK IP RANGE" << endl;
  }
  else{
    cout << "ERROR MASK OK " << endl;
  }
}
