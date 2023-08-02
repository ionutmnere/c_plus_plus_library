#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <thread>
#include <future>


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
    // static std::vector<std::thread::id> thread_ids;
    // if(std::find(thread_ids.begin(), thread_ids.end(), std::this_thread::get_id()) == thread_ids.end()) {
    //     thread_ids.push_back(std::this_thread::get_id());
    //     std::cout << "New thread doing work... " << std::this_thread::get_id() << std::endl;
    // } 
    size_t delim_pos = l_input.find(delim);
    if(delim_pos != std::string::npos) {
        std::string remain = l_input.substr(delim_pos+delim.length());
        return reverse_smart_recursive(remain, delim) + delim + l_input.substr(0, delim_pos);
    }
    else return l_input;
}

std::string reverse_string_paralel(const std::string& l_input, const int depth=1, const std::string delim=" ") {
    std::string result;
    size_t midle_pos = l_input.find(delim, (size_t)l_input.length()/2);
    // split work in half
    if(midle_pos != std::string::npos) {
        const std::string l_first_str = l_input.substr(0, midle_pos);
        std::future<std::string> l_first_half;
        if (depth > 1 && depth <= std::thread::hardware_concurrency()) { // split deeper but max to total cores level deep
            l_first_half = std::async(std::launch::async, reverse_string_paralel, l_first_str, depth+1, delim);
            result = reverse_string_paralel(l_input.substr(midle_pos+delim.length()), depth+1, delim);
        } else {
            l_first_half = std::async(std::launch::async, reverse_smart_recursive, l_first_str, delim);
            result = reverse_smart_recursive(l_input.substr(midle_pos+delim.length()), delim);
        }        
        result = result + delim + l_first_half.get();
    }
    return result;
}

int main() 
{
    std::cout << "input: '" << "dadsa 123 tralala dadsa 123 tralala" << "'" << std::endl;
    std::cout << "reverse_brute_force: '" << reverse_brute_force("dadsa 123 tralala dadsa 123 tralala") << "'" << std::endl;
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

    // --------- Sequential and paralel examples -------------------
    std::string l_input8("This is a long string to be reversed! ");
    /// double N times
    for (int i = 0; i < 10; ++i) {
        l_input8 = l_input8 + l_input8;
    }
    std::cout << "input length is " << l_input8.length() << std::endl;
    std::string sequential_run = reverse_smart_recursive(l_input8); // warm up
    std::chrono::duration<double> sequential_time(0);    
    for (int i=0; i< 10; ++i) {
        auto start_time = std::chrono::high_resolution_clock::now();
        reverse_smart_recursive(l_input8);
        sequential_time += std::chrono::high_resolution_clock::now() - start_time;
    }
    std::cout << "sequential_time: " << (sequential_time.count()*1000)/10 << " ms." << std::endl;

    std::string parallel_run = reverse_string_paralel(l_input8); // warm up
    // check if paralel and sequential did the same job
    if (sequential_run != parallel_run) {
        std::cout << "Algorithms do not work the same (paralel_run 1)!!!" << std::endl;
        std::cout << "sequential_run: '" << sequential_run << "'" << std::endl;
        std::cout << "paralel_run: '" << parallel_run << "'"<< std::endl;
    }
    std::chrono::duration<double> parallel_time(0);
    for (int i=0; i< 10; ++i) {
        auto start_time = std::chrono::high_resolution_clock::now();
        reverse_string_paralel(l_input8);
        parallel_time += std::chrono::high_resolution_clock::now() - start_time;
    }
    std::cout << "parallel_time: " << (parallel_time.count()*1000)/10 << " ms." << std::endl;
    std::cout << "Speedup: " << (float)(sequential_time/parallel_time) << std::endl;
    std::cout << "Efficiency: " <<  (float)(100*(sequential_time/parallel_time)/std::thread::hardware_concurrency()) 
              << " %" << std::endl << std::endl;
    
    l_input8 = l_input8 + l_input8 + l_input8;
    std::cout << "input length is " << l_input8.length() << std::endl;
    std::string sequential_run_2 = reverse_smart_recursive(l_input8); // warm up
    std::chrono::duration<double> sequential_time_2(0);    
    for (int i=0; i< 10; ++i) {
        auto start_time = std::chrono::high_resolution_clock::now();
        reverse_smart_recursive(l_input8);
        sequential_time_2 += std::chrono::high_resolution_clock::now() - start_time;
    }
    std::cout << "sequential_time_2: " << (sequential_time_2.count()*1000)/10 << " ms." << std::endl;

    std::chrono::duration<double> parallel_time_2(0);
    const int DEPTH = 3;
    std::string paralel_run_2 = reverse_string_paralel(l_input8, DEPTH); // warm up
    /// check if paralel and sequential did the same job
    if (sequential_run_2 != paralel_run_2) {
        std::cout << "Algorithms do not work the same (paralel_run 2)!!!" << std::endl;
        std::cout << "sequential_run_2: '" << sequential_run_2 << "'" << std::endl;
        std::cout << "paralel_run_2: '" << paralel_run_2 << "'"<< std::endl;
    }
    for (int i=0; i< 10; ++i) {
        auto start_time = std::chrono::high_resolution_clock::now();
        reverse_string_paralel(l_input8, DEPTH); // split the work one level deeper
        parallel_time_2 += std::chrono::high_resolution_clock::now() - start_time;
    }
    std::cout << "parallel_time_2: " << (parallel_time_2.count()*1000)/10 << " ms." << std::endl;
    std::cout << "Speedup: " << (float)(sequential_time_2/parallel_time_2) << std::endl;
    std::cout << "Efficiency: " <<  (float)(100*(sequential_time_2/parallel_time-2)/std::thread::hardware_concurrency()) 
              << " %" << std::endl << std::endl;

    std::cout << "main finished. exiting..." << std::endl;
    return 0;
}
