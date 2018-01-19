#include <iostream>
#include <string>
#include <map>
#include <utility>
class Date {
    std::string year, month, day;
public:
    Date(std::string date) {
        unsigned i = 0;
        for (; date[i] != '/'; ++i) {
            year += date[i];
        }
        for (++i; date[i] != '/'; ++i) {
            month += date[i];
        }
        for (++i; i < date.size(); ++i) {
            day += date[i];
        }
        unsigned size = year.size();
        for (i = 0; i < 4 - size; ++i) {
            year = "0" + year;
        }
        size = month.size();
        for (i = 0; i < 2 - size; ++i) {
            month = "0" + month;
        }
        size = day.size();
        for (i = 0; i < 2 - size; ++i) {
            day = "0" + day;
        }
    }
    std::string get_date() const {
        std::string formatdate = year + "/" + month + "/" + day;
        return formatdate;
    }
};
int main() {
    std::map<std::string, std::map<std::string, char>> students;
    std::map<std::string, int> sorteddates;
    std::string surname = "", date = "";
    char mark = '.';
    while (std::cin >> surname >> date >> mark) {
        Date d(date);
        students[surname][d.get_date()] = mark;
        ++sorteddates[d.get_date()];
    }
    std::cout << ". ";
    for (auto dit = sorteddates.cbegin(); dit != sorteddates.cend(); ++dit) {
        std::cout << dit->first << ' ';
    }
    std::cout << std::endl;
    for (auto sit = students.begin(); sit != students.end(); ++sit) {
        std::cout << sit->first << ' ';
        for (auto dit = sorteddates.cbegin(); dit != sorteddates.cend(); ++dit) {
            if (sit->second.find(dit->first) != sit->second.end()) {
                std::cout << sit->second[dit->first] << ' ';
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}