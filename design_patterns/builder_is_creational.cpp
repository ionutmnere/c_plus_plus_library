#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

struct HtmlBuilder;

class HtmlElement
{
  friend class HtmlBuilder;
  std::string name;
  std::string text;
  std::vector<HtmlElement> elements;
  const size_t indent_size = 2;

  HtmlElement() {}
  HtmlElement(const std::string& name, const std::string& text)
    : name(name),
    text(text)
  {
  }
 public:
  std::string str(int indent = 0) const
  {
    std::ostringstream oss;
    std::string i(indent_size*indent, ' ');
    oss << i << "<" << name << ">" << std::endl;
    if (text.size() > 0)
      oss << std::string(indent_size*(indent + 1), ' ') << text << std::endl;

    for (const auto& e : elements)
      oss << e.str(indent + 1);

    oss << i << "</" << name << ">" << std::endl;
    return oss.str();
  }
  static std::unique_ptr<HtmlBuilder> build(std::string root_name)
  {
    return std::make_unique<HtmlBuilder>(root_name);
  }
};

struct HtmlBuilder 
{
  HtmlBuilder(std::string root_name) {
    root.name = root_name;
  }
  // void to start with
  HtmlBuilder& add_child(std::string child_name, std::string child_text) {
    HtmlElement e{ child_name, child_text };
    root.elements.emplace_back(e);
    return *this;
  }
  // pointer based
  HtmlBuilder& add_child_2(std::string child_name, std::string child_text)
  {
    HtmlElement e{ child_name, child_text };
    root.elements.emplace_back(e);
    return *this;
  }
  std::string str() { return root.str(); }

  operator HtmlElement() const { return root; }
  
  HtmlElement root;
};

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

  // easier
  HtmlBuilder builder{ "ul" };
  builder.add_child("li", "hello").add_child("li", "world");
  std::cout << builder.str() << std::endl;
  std::cout << std::endl;

  // using static method from HtmlElement
  // this is possible because of operator HtmlElement() const { return root; }
  HtmlElement builder2 = HtmlElement::build("ul")->add_child("li", "hello").add_child("li", "world");
  std::cout << builder2.str() << std::endl;

  std::cout << std::endl << "main finished. exiting..." << std::endl;
}