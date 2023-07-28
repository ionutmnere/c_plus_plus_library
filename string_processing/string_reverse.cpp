#include <iostream>
#include <string>
#include <list>
#include <algorithm>


std::string reverse_brute_force(const std::string& l_input) {
    std::string result;
    std::list<std::string> l_parts;
    std::string aux;
    for(int i = 0; i<l_input.length(); ++i) {
        if( i == l_input.length() - 1) {
            aux += l_input[i];
            l_parts.push_front(aux);
            aux.clear();
        }
        else if (l_input[i] == ' ') {
            if(aux.length() > 0) {
                l_parts.push_front(aux);
                aux.clear();
            }
        }
        else {
            aux += l_input[i];
        }
    }
    for(std::list<std::string>::iterator it = l_parts.begin(); it != l_parts.end(); ++it) {
        if(it != --l_parts.end() ) {
            result += *it + ' ';
        } 
        else {
            result += *it;
        }
    }
    return result;
}

std::string reverse_smart_recursive(const std::string& l_input) {
    size_t l_space_pos = l_input.find(' ');
    if(l_space_pos != std::string::npos) {
        std::string remain = l_input.substr(l_space_pos+1);
        return reverse_smart_recursive(remain) + " " + l_input.substr(0, l_space_pos);
    }
    else return l_input;
}

int main() 
{
    std::cout << "input: '" << "dadsa 123 tralala" << "'" << std::endl;
    std::cout << "reverse_brute_force: '" << reverse_brute_force("dadsa 123 tralala") << "'" << std::endl;
    std::cout << "reverse_smart_recursive: '" << reverse_smart_recursive("dadsa 123 tralala") << "'"<< std::endl;
    std::cout << std::endl;

    const std::string l_input2("dadsa 123 ");
    std::cout << "input: '" << l_input2 << "'" << std::endl;
    std::cout << "reverse_brute_force: '" << reverse_brute_force(l_input2) << "'" << std::endl;
    std::cout << "reverse_smart_recursive: '" << reverse_smart_recursive(l_input2) << "'"<< std::endl;
    std::cout << std::endl;

    const std::string l_input3(" dadsa123");
    std::cout << "input: '" << l_input3 << "'" << std::endl;
    std::cout << "reverse_brute_force: '" << reverse_brute_force(l_input3) << "'" << std::endl;
    std::cout << "reverse_smart_recursive: '" << reverse_smart_recursive(l_input3) << "'"<< std::endl;
    std::cout << std::endl;

    std::cout << "main finished. exiting..." << std::endl;
    return 0;
}
