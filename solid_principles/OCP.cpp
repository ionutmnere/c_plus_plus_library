/// This seems strange. The meaning of open is that the structure of code (call me architecture) should be open for extensions (by adding new features) 
/// but closed for modifications. The latter means that we do not need to modify the existing codebase in order to add new features,
/// we just build on top, or better extend it.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product {
    string name;
    Color color;
    Size size;
};

template <typename T> struct AndFilterSpec;

template <typename T> struct FilterSpec 
{
    virtual ~FilterSpec() = default;

    virtual bool is_satisfied(T* item) const = 0;
    
    AndFilterSpec<T> operator&&(const FilterSpec<T>& p_other) const {
        return AndFilterSpec<T>(*this, p_other);
    }
};

template <typename T>
struct ColorFilterSpec : FilterSpec<T> {
    Color m_color;
    ColorFilterSpec(Color color) :  m_color(color) {}
    bool is_satisfied(T* item) const {
        return item->color == m_color;
    }
};

template <typename T>
struct SizeFilterSpec : FilterSpec<T> {
    Size m_size;
    SizeFilterSpec(Size size) :  m_size(size) {}
    bool is_satisfied(T* item) const {
        return item->size == m_size;
    }
};

template <typename T>
struct AndFilterSpec : FilterSpec<T> 
{
    const FilterSpec<T>& m_first;
    const FilterSpec<T>& m_second;
    
    AndFilterSpec(const FilterSpec<T>& p_first, const FilterSpec<T>& p_second) : 
      m_first(p_first), 
      m_second(p_second) 
    {}
    
    bool is_satisfied(T* item) const {
        return m_first.is_satisfied(item) &&  m_second.is_satisfied(item);
    }
};


template <typename T>
struct Filter  {
    static vector<T*> filter(const vector<T*> items, const FilterSpec<T>& spec)
    {
        vector<T*> result;
        for (auto item : items) {
            if (spec.is_satisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};


int main(int argc, char const *argv[])
{
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};
    
    const vector<Product*> all {&apple, &tree, &house};

    const ColorFilterSpec<Product> green_filter(Color::green);
    for (auto item : Filter<Product>::filter(all, green_filter)) {
        cout << item->name << " is green." <<  endl;
    }

    const SizeFilterSpec<Product> large_filter(Size::large);
    for (auto item : Filter<Product>::filter(all, large_filter)) {
        cout << item->name << " is large." <<  endl;
    }

    const AndFilterSpec green_and_large(green_filter, large_filter);
    for (auto item : Filter<Product>::filter(all, green_and_large)) {
        cout << item->name << " is green and large." <<  endl;
    }

    auto green_and_large2 = green_filter && large_filter;
    for (auto item : Filter<Product>::filter(all, green_and_large2)) {
        cout << item->name << " is green and large." <<  endl;
    }

    for (auto item : Filter<Product>::filter(all, green_filter && large_filter)) {
        cout << item->name << " is green and large." <<  endl;
    }
    
    return 0;
}
