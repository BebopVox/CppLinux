string Quotes(std::string &s)
{
    std::size_t n = s.length();
    std::string escaped;
    escaped.reserve(n * 2);        // pessimistic preallocation

    for (std::size_t i = 0; i < n; ++i) {
        if (s[i] == '\\' || s[i] == '\'')
            escaped += '\\';
        if (s[i] == '\\' || s[i] == '\"')
            escaped += '\\';
        escaped += s[i];
    }
    return escaped;
}
