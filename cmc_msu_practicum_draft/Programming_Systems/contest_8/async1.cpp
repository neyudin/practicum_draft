#include <iostream>
#include <map>
#include <future>
#include <thread>
#include <fstream>
#include <string>
#include <mutex>
#include <chrono>
#include <vector>
#include <algorithm>
std::mutex m;
void filecounter(std::map<std::string, int> &cont, const char *filename) {
    /*m.lock();
    std::cout << "thread: " << std::this_thread::get_id() << std::endl << std::flush;
    m.unlock();*/
    std::fstream f(filename, std::ios_base::in);
    while (!f.eof()) {
        std::string s;
        f >> s;
        if (f.eof()) {
            break;
        }
        std::lock_guard<std::mutex> guard(m);
        ++cont[s];
    }
}
int main(int argc, const char **argv) {
    /*m.lock();
    std::cout << "main thread: " << std::this_thread::get_id() << std::endl << std::flush;
    m.unlock();*/
    std::vector<std::future<void>> futures;
    std::map<std::string, int> words;
    for (int i = 1; i < argc; ++i) {    
        futures.push_back(std::async(std::launch::async, filecounter, std::ref(words), argv[i]));
    }
    for (int i = 0; i < argc - 1; ++i) {
        futures[i].wait();
    }
    std::cout << words.size() << std::endl;
    std::multimap<int, std::string> freq;
    for (auto it = words.cbegin(); it != words.cend(); ++it) {
        freq.insert(std::pair<int, std::string>(it->second, it->first));
    }
    auto rit = freq.crbegin();
    for (int i = 0; (i < 20) && (rit != freq.crend());) {
        int size = freq.count(rit->first);
        std::vector<std::string> v;
        for (int j = 0; (j < size) && (rit != freq.crend()); ++j) {
            v.push_back(rit->second);
            ++rit;
        }
        std::sort(v.begin(), v.end());
        --rit;
        for (auto it = v.cbegin(); (it != v.cend()) && (i < 20); ++it) {
            std::cout << *it << ' ' << rit->first << std::endl;
            ++i;
        }
        ++rit;
    }
}