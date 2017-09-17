#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

int main(int count, char *strings[])
{
  std::string str = "your string in utf8";
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>> converter;
  std::wstring wstr = converter.from_bytes(str);
}
