string removeBcc(string s){
    std::regex reg("((BCC:)(.*))", regex_constants::icase);   // matches words beginning by "sub"	
	return std::regex_replace (s,reg,"");
}
