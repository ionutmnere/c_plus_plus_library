#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>



int main()
{
  // <p>hello</p>
  auto text = "hello";
  std::string output;
  output += "<p>";
  output += text;
  output += "</p>";
  std::cout <<  text << std::endl;

  // <ul><li>hello</li><li>world</li></ul>
  std::string words[] = { "hello", "world" };
  std::ostringstream oss;
  oss << "<ul>";
  for (auto w : words)
    oss << "  <li>" << w << "</li>";
  oss << "</ul>";
  std::cout << oss.str() << std::endl;

  std::cout << std::endl << "main finished. exiting..." << std::endl;
}