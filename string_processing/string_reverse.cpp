#include <iostream>
#include <string>
#include <list>
#include <algorithm>


std::string reverse_brute_force(const std::string& l_input, const char delim=' ') {
    std::string result;
    std::list<std::string> l_parts;
    std::string aux;
    for(int i = 0; i<l_input.length(); ++i) {
        if( i == l_input.length() - 1) {
            aux += l_input[i];
            l_parts.push_front(aux);
            aux.clear();
        }
        else if (l_input[i] == delim) {
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
            result += *it + delim;
        } 
        else {
            result += *it;
        }
    }
    return result;
}

std::string reverse_smart_recursive(const std::string& l_input, const std::string delim=" ") {
    size_t delim_pos = l_input.find(delim);
    if(delim_pos != std::string::npos) {
        std::string remain = l_input.substr(delim_pos+delim.length());
        return reverse_smart_recursive(remain, delim) + delim + l_input.substr(0, delim_pos);;
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

    const std::string l_input4("how are you today?");
    const char delim = 'a';
    std::string delim_str; delim_str += delim;
    std::cout << "input: '" << l_input4 << "'" << " delimiter: '" << delim << "'"<< std::endl;
    std::cout << "reverse_brute_force    : '" << reverse_brute_force(l_input4, delim) << "'" << std::endl;
    std::cout << "reverse_smart_recursive: '" << reverse_smart_recursive(l_input4, delim_str) << "'"<< std::endl;
    std::cout << std::endl;

    const std::string l_input5("6_5_4_3_2_1_0");
    const char delim5 = '_';
    delim_str.clear(); delim_str += delim5;
    std::cout << "input: '" << l_input5 << "'" << " delimiter: '" << delim5 << "'"<< std::endl;
    std::cout << "reverse_brute_force    : '" << reverse_brute_force(l_input5, delim5) << "'" << std::endl;
    std::cout << "reverse_smart_recursive: '" << reverse_smart_recursive(l_input5, delim_str) << "'"<< std::endl;
    std::cout << std::endl;

    const std::string l_input6("456 a 123 a 0");
    const char delim6 = 'a';
    delim_str.clear(); delim_str += delim6;
    std::cout << "input: '" << l_input6 << "'" << " delimiter: '" << delim6 << "'"<< std::endl;
    std::cout << "reverse_brute_force    : '" << reverse_brute_force(l_input6, delim6) << "'" << std::endl;
    std::cout << "reverse_smart_recursive: '" << reverse_smart_recursive(l_input6, delim_str) << "'"<< std::endl;
    std::cout << std::endl;

    const std::string l_input7("456___123___0");
    const std::string str_delimiter = "___";
    std::cout << "input: '" << l_input7 << "'" << " delimiter: '" << str_delimiter << "'"<< std::endl;    
    std::cout << "reverse_smart_recursive: '" << reverse_smart_recursive(l_input7, str_delimiter) << "'"<< std::endl;
    std::cout << std::endl;

    std::cout << "main finished. exiting..." << std::endl;
    return 0;
}
