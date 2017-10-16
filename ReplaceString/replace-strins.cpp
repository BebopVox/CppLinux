std::string replaceAll( string s1, string search, string replace ) {
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s1.find( search, pos );
        if( pos == string::npos ) break;
        // Replace by erasing and inserting
        s1.erase( pos, search.length() );
        s1.insert( pos, replace );
    }
    return s1;
}

std::string ReplaceString(std::string subject, const std::string& search,const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

std::string getStringBetween(const std::string s, const std::string start_delim, const std::string &stop_delim){
    unsigned first_delim_pos = s.find(start_delim);
    unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
    unsigned last_delim_pos = s.find_first_of(stop_delim, end_pos_of_first_delim);
    return s.substr(end_pos_of_first_delim, last_delim_pos - end_pos_of_first_delim);
}

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
