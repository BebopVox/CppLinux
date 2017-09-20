std::string spf = "SMTPspf:123.321.123.321";
if(spf.find(std::string("SMTPspf:")) != std::string::npos){
  cout << "TXT " <<  spf << endl;

  // const regex r("(\\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b)");
  // const regex r("(([0-9]{1,3}).([0-9]{1,3}).([0-9]{1,3}).([0-9]{1,3}))");
  const regex r("(\\d{1,3}(\\.\\d{1,3}){3})");
  smatch sm;
  if (regex_search(spf, sm, r))
  {
      cout << "input string has " << sm.size() << " matches " << endl;
      for (int i=1; i<sm.size(); i++)
      {
          cout << "REGES " << sm[0] << endl;
          ips.push_back(sm[0]);
      }
  }
}
