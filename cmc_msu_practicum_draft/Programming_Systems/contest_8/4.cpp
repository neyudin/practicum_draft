#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
struct File {
    const char *filename;
    std::vector<std::string> surname;
    std::vector<std::vector<int>> marks;
    std::vector<double> average;
    double mean;
    File(const char *name): filename(name), mean(0) {}
};
int main(int argc, char **argv) {
    std::vector<File> files;
    for (int i = 1; i < argc; ++i) {
        files.push_back(File(argv[i]));
    }
    for (unsigned i = 0; i < files.size(); ++i) {
        std::fstream f(files[i].filename, std::ios_base::in);
        unsigned j = 0;
        while (!f.eof()) {
            std::string sname;
            f >> sname;
            if (f.eof()) {
                break;
            }
            files[i].surname.push_back(sname);
            files[i].marks.push_back({0});
            int mark = -1, num = 0;
            f >> mark;
            if ((mark > 1) && (mark < 6)) {
                files[i].marks[j][0] = mark;
                num = 1;
            }
            while (mark != 0) {
                f >> mark;
                if ((mark > 1) && (mark < 6)) {
                    if (num == 1) {
                        files[i].marks[j].push_back(mark);
                    } else {
                        files[i].marks[j][0] = mark;
                        num = 1;
                    }
                }
            }
            ++j;
        }
        double sum = 0;
        for (j = 0; j < files[i].surname.size(); ++j) {
            sum = 0;
            for (unsigned k = 0; k < files[i].marks[j].size(); ++k) {
                sum += files[i].marks[j][k];
            }
            files[i].average.push_back(sum/files[i].marks[j].size());
        }
        sum = 0;
        for (j = 0; j < files[i].average.size(); ++j) {
            sum += files[i].average[j];
        }
        files[i].mean = sum/files[i].average.size();
    }
    double sum = 0;
    for (auto filesit = files.begin(); filesit != files.end(); ++filesit) {
        sum += filesit->mean;
    }
    if (files.size() != 0) {
        sum /= files.size();
    }
    //test output
    /*for (unsigned i = 0; i < files.size(); ++i) {
        std::cout << std::endl << files[i].filename << ':' << std::endl << std::endl;
        for (unsigned j = 0; j < files[i].surname.size(); ++j) {
            std::cout << files[i].surname[j] << ' ';
            for (unsigned k = 0; k < files[i].marks[j].size(); ++k) {
                std::cout << files[i].marks[j][k] << ' ';
            }
            std::cout << "average: " << files[i].average[j] << std::endl;
        }
        std::cout << std::endl << "mean: " << files[i].mean << std::endl;
    }
    std::cout << std::endl << "MEAN OF ALL FILES: " << sum << std::endl << std::endl;*/
    std::fstream f("result.txt", std::ios_base::out);
    for (auto filesit = files.cbegin(); filesit != files.cend(); ++filesit) {
        auto surnameit = filesit->surname.cbegin();
        auto marksit = filesit->marks.cbegin();
        for (auto averageit = filesit->average.cbegin(); averageit != filesit->average.cend(); 
            ++surnameit, ++marksit, ++averageit) {
            if (*averageit < sum) {
                continue;
            }
            f << filesit->filename << ' ' << *surnameit;
            for (auto marksitit = marksit->cbegin(); marksitit != marksit->cend(); ++marksitit) {
                f << ' ' << *marksitit;
            }
            f << std::endl;
        }
    }
}