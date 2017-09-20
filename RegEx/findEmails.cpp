vector<vector<string>> BreakermindSslServer::findEmails(const string& s)
{
    const string& reg_ex("(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+");
    regex rx(reg_ex, regex_constants::icase);
    vector<vector<string>> captured_groups;
    vector<string> captured_subgroups;
    const std::sregex_token_iterator end_i;
    for (std::sregex_token_iterator i(s.cbegin(), s.cend(), rx);
        i != end_i;
        ++i)
    {
        captured_subgroups.clear();
        string group = *i;
        smatch res;
        if(regex_search(group, res, rx))
        {
            for(unsigned i=0; i<res.size() ; i++)
                captured_subgroups.push_back(res[i]);

            if(captured_subgroups.size() > 0)
                captured_groups.push_back(captured_subgroups);
        }

    }
    captured_groups.push_back(captured_subgroups);
    return captured_groups;
}

// usage
vector<string> mailto;
vector<vector<string>> emails = findEmails(cmsg);
// cout << "EMAILS FROM SIZE " << emails.size() << endl;
for(int i = 0; i < emails.size(); i++){
    vector<string> email1 = emails.at(0);
    // cout << "EMAIL1 FROM SIZE " << email1.size() << endl;
    cout << "EMAIL " << email1.at(0) << endl;
    // save recipients email
    mailto.push_back(email1.at(0));
}
