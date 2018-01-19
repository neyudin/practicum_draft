#include <dlfcn.h>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include "IAntLogic.hpp"
class ANT: public antlogic::Ant {
    char *mem = nullptr;
    unsigned team_id;
    bool food = false;
public:
    antlogic::AntAction(*action)(const antlogic::Ant&,antlogic::AntSensor[3][3]);
    int cur_x, cur_y;
    int pause = 0;
    ANT(int tid = 1, void* func = nullptr, int x = 0, int y = 0): antlogic::Ant() {
        mem = new char[antlogic::MAX_MEMORY];
        memset(mem, 0, antlogic::MAX_MEMORY);
        team_id = tid;
        action = (antlogic::AntAction(*)(const antlogic::Ant&,antlogic::AntSensor[3][3])) func;
        cur_x = x;
        cur_y = y;
    }
    ANT(const ANT &obj) {
        mem = new char[antlogic::MAX_MEMORY];
        memcpy(mem, obj.mem, antlogic::MAX_MEMORY);
        team_id = obj.team_id;
        food = obj.food;
        action = obj.action;
        cur_x = obj.cur_x;
        cur_y = obj.cur_y;
        pause = obj.pause;
    }
    ~ANT() {
        delete [] mem;
    }
    char *getMemory() const {
        return mem;
    }
    bool hasFood() const {
        return food;
    }
    int getTeamId() const {
        return team_id;
    }
    void getFood() {
        food = true;
    }
    void putFood() {
        food = false;
    }
};
class TEAM {
public:
    unsigned team_id;
    std::vector<ANT> units;
    TEAM(unsigned tid = 1, int unum = 1, void *func = nullptr, int x = 0, int y = 0): team_id(tid) {
        for (int i = 0; i < unum; ++i) {
            units.push_back(ANT(team_id, func, x, y));
        }
    }
    ~TEAM() {}
};
struct CELL {
    std::vector<int> ants;
    std::vector<std::vector<ANT*>> ants_pointers;
    int smell = 0;
    int smellIntensity = 0;
    unsigned Hill = 0;//0 -> None, else -> TeamId
    int Food = 0;
    bool isWall = true;
};
void putfood(std::vector<std::vector<CELL>> &field) {
    for (unsigned i = 1; i < field.size() - 1; ++i) {
        for (unsigned j = 1; j < field[i].size() - 1; ++j) {
            if (field[i][j].Hill > 0) {
                continue;
            }
            int switcher = std::rand() % 8;
            if (switcher == 7) {
                field[i][j].Food = std::rand()/(RAND_MAX + 1.0) * 100;
                continue;
            }
            if (switcher == 6) {
                field[i][j].Food = std::rand()/(RAND_MAX + 1.0) * 10;
                continue;
            }
            if (switcher == 5) {
                field[i][j].Food = std::rand()/(RAND_MAX + 1.0) * 5;
                continue;
            }
        }
    }
}
void start(std::vector<std::vector<CELL>> &field, std::vector<std::pair<int, int>> &hills, std::vector<TEAM> &teams) {
    for (unsigned i = 1; i < field.size() - 1; ++i) {
        for (unsigned j = 1; j < field[i].size() - 1; ++j) {
            field[i][j].ants.resize(teams.size());
            field[i][j].ants_pointers.resize(teams.size());
            for (unsigned k = 0; k < field[i][j].ants_pointers.size(); ++k) {
                for (unsigned l = 0; l < teams[k].units.size(); ++l) {
                    field[i][j].ants_pointers[k].push_back(nullptr);
                }
            }
            field[i][j].isWall = false;
        }
    }
    for (unsigned i = 0; i < hills.size(); ++i) {
        field[hills[i].second][hills[i].first].Hill = i + 1;
        field[hills[i].second][hills[i].first].ants[i] = teams[i].units.size();
        for (unsigned j = 0; j < teams[i].units.size(); ++j) {
            field[hills[i].second][hills[i].first].ants_pointers[i][j] = &(teams[i].units[j]);
        }
    }
    putfood(field);
}
void print(std::vector<std::vector<CELL>> &field) {
    std::cout << std::endl;
    for (unsigned i = 0; i < field.size(); ++i) {
        for (unsigned j = 0; j < field[i].size(); ++j) {
            if (field[i][j].isWall == true) {
                std::cout << '#';
                continue;
            }
            std::string c = "*";
            if (field[i][j].Hill > 0) {
                c = "\033[1;3" + std::to_string(field[i][j].Hill) + "mH\033[0m";
            }
            if ((field[i][j].Hill ==  0) && (field[i][j].smellIntensity > 0)) {
                c = "\033[1;35ms\033[0m";
            }
            if ((field[i][j].Hill == 0) && (field[i][j].Food > 0)) {
                c = "\033[1;30mf\033[0m";
            }
            int count = 0;
            for (unsigned k = 0; k < field[i][j].ants.size(); ++k) {
                if (field[i][j].ants[k] > 0) {
                    c = "\033[1;3" + std::to_string(k + 1) + "m" + std::to_string(k + 1) + "\033[0m";
                    if (field[i][j].ants[k] > 1) {
                        c = "\033[1;3" + std::to_string(k + 1) + "m@\033[0m";
                    }
                    ++count;
                }
            }
            if (count > 1) {
                c = "\033[1;36m@\033[0m";
            }
            count = 0;
            for (unsigned k = 0; k < field[i][j].ants_pointers.size(); ++k) {
                for (unsigned l = 0; l < field[i][j].ants_pointers[k].size(); ++l) {
                    if (field[i][j].ants_pointers[k][l] == nullptr) {
                        continue;
                    }
                    if ((field[i][j].ants_pointers[k][l])->pause > 0) {
                        c = "\033[1;3" + std::to_string(k + 1) + "mw\033[0m";
                        ++count;
                        break;
                    }
                }
            }
            if (count > 1) {
                c = "\033[1;36mw\033[0m";
            }
            std::cout << c;
        }
        std::cout << std::endl << std::flush;
    }
}
void print_stat(std::vector<std::vector<CELL>> &field, std::vector<std::pair<int, int>> &hills, int num, int overall) {
    std::cout << std::endl;
    for (unsigned i = 0; i < hills.size(); ++i) {
        std::cout << "\033[1;3" << i + 1 << "m";
        std::cout << "team " << i + 1 << ": " << field[hills[i].second][hills[i].first].Food << std::endl << "\033[0m" << std::flush;
    }
    std::cout << "stage number: " << num << " of " << overall << std::endl << std::flush;
}
void clear(int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << "\33[1A\33[2K\r" << std::flush;
    }
}
void move(std::vector<std::vector<CELL>> &field, std::vector<TEAM> &teams) {
    for (unsigned i = 0; i < teams.size(); ++i) {
        for (unsigned j = 0; j < teams[i].units.size(); ++j) {
            if (teams[i].units[j].pause == 0) {
                int x = teams[i].units[j].cur_x;
                int y = teams[i].units[j].cur_y;
                unsigned tid = teams[i].units[j].getTeamId();
                antlogic::AntSensor sensors[3][3];
                for (int l = 0; l < 3; ++l) {
                    for (int k = 0; k < 3; ++k) {
                        sensors[k][l].smell = field[y - 1 + l][x - 1 + k].smell;
                        sensors[k][l].smellIntensity = field[y - 1 + l][x - 1 + k].smellIntensity;
                        if (field[y - 1 + l][x - 1 + k].Hill > 0) {
                            if (field[y - 1 + l][x - 1 + k].Hill == tid) {
                                sensors[k][l].isMyHill = true;
                            } else {
                                sensors[k][l].isEnemyHill = true;
                            }
                        }
                        sensors[k][l].isWall = field[y - 1 + l][x - 1 + k].isWall;
                        if (sensors[k][l].isWall == true) {
                            continue;
                        }
                        if (field[y - 1 + l][x - 1 + k].Food > 0) {
                            sensors[k][l].isFood = true;
                        }
                        if ((l != 1) && (k != 1) && (field[y - 1 + l][x - 1 + k].ants[tid - 1] > 0)) {
                            sensors[k][l].isFriend = true;
                        }
                        if ((l == 1) && (k == 1) && (field[y - 1 + l][x - 1 + k].ants[tid - 1] > 1)) {
                            sensors[k][l].isFriend = true;
                        }
                        for (unsigned m = 0; m < field[y - 1 + l][x - 1 + k].ants.size(); ++m) {
                            if ((m != tid - 1) && (field[y - 1 + l][x - 1 + k].ants[m] > 0)) {
                                sensors[k][l].isEnemy = true;
                            }
                        }
                    }
                }
                antlogic::AntAction ACTION = teams[i].units[j].action(teams[i].units[j], sensors);
                if (ACTION.putSmell == true) {
                    field[y][x].smell = ACTION.smell;
                    field[y][x].smellIntensity = 100;
                }
                std::multimap<int, ANT*> chosen;
                switch (ACTION.actionType) {
                    case antlogic::MOVE_UP:
                        if (field[y - 1][x].isWall == true) {
                            break;
                        }
                        teams[i].units[j].cur_y -= 1;
                        field[y][x].ants[tid - 1] -= 1;
                        field[y - 1][x].ants[tid - 1] += 1;
                        field[y - 1][x].ants_pointers[tid - 1][j] = field[y][x].ants_pointers[tid - 1][j];
                        field[y][x].ants_pointers[tid - 1][j] = nullptr;
                        break;
                    case antlogic::MOVE_LEFT:
                        if (field[y][x - 1].isWall == true) {
                            break;
                        }
                        teams[i].units[j].cur_x -= 1;
                        field[y][x].ants[tid - 1] -= 1;
                        field[y][x - 1].ants[tid - 1] += 1;
                        field[y][x - 1].ants_pointers[tid - 1][j] = field[y][x].ants_pointers[tid - 1][j];
                        field[y][x].ants_pointers[tid - 1][j] = nullptr;
                        break;
                    case antlogic::MOVE_DOWN:
                        if (field[y + 1][x].isWall == true) {
                            break;
                        }
                        teams[i].units[j].cur_y += 1;
                        field[y][x].ants[tid - 1] -= 1;
                        field[y + 1][x].ants[tid - 1] += 1;
                        field[y + 1][x].ants_pointers[tid - 1][j] = field[y][x].ants_pointers[tid - 1][j];
                        field[y][x].ants_pointers[tid - 1][j] = nullptr;
                        break;
                    case antlogic::MOVE_RIGHT:
                        if (field[y][x + 1].isWall == true) {
                            break;
                        }
                        teams[i].units[j].cur_x += 1;
                        field[y][x].ants[tid - 1] -= 1;
                        field[y][x + 1].ants[tid - 1] += 1;
                        field[y][x + 1].ants_pointers[tid - 1][j] = field[y][x].ants_pointers[tid - 1][j];
                        field[y][x].ants_pointers[tid - 1][j] = nullptr;
                        break;
                    case antlogic::GET:
                        if ((field[y][x].Food == 0) || (teams[i].units[j].hasFood() == true)) {
                            break;
                        }
                        field[y][x].Food -= 1;
                        teams[i].units[j].getFood();
                        break;
                    case antlogic::PUT:
                        if (teams[i].units[j].hasFood() == false) {
                            break;
                        }
                        field[y][x].Food += 1;
                        teams[i].units[j].putFood();
                        break;
                    case antlogic::BITE_UP: {
                        if (field[y - 1][x].isWall == true) {
                            break;
                        }
                        for (unsigned k = 0; k < field[y - 1][x].ants_pointers.size(); ++k) {
                            if (k == tid - 1) {
                                continue;
                            }
                            for (unsigned l = 0; l < field[y - 1][x].ants_pointers[k].size(); ++l) {
                                if (field[y - 1][x].ants_pointers[k][l] == nullptr) {
                                    continue;
                                }
                                chosen.insert(std::pair<int, ANT*>((field[y - 1][x].ants_pointers[k][l])->pause, field[y - 1][x].ants_pointers[k][l]));
                            }
                        }
                        auto it = chosen.begin();
                        if (it == chosen.end()) {
                            break;
                        }
                        auto pair = chosen.equal_range(it->first);
                        auto cit = pair.first;
                        int count = 0;
                        for(; cit != pair.second; ++cit) {
                            ++count;
                        }
                        count = std::rand() % count;
                        cit = pair.first;
                        for (unsigned k = 0; k < count; ++k) {
                            ++cit;
                        }
                        cit->second->pause = 8;
                        if (cit->second->hasFood() == true) {
                            cit->second->putFood();
                            field[cit->second->cur_y][cit->second->cur_x].Food += 1;
                        }
                        break;
                    }
                    case antlogic::BITE_LEFT: {
                        if (field[y][x - 1].isWall == true) {
                            break;
                        }
                        for (unsigned k = 0; k < field[y][x - 1].ants_pointers.size(); ++k) {
                            if (k == tid - 1) {
                                continue;
                            }
                            for (unsigned l = 0; l < field[y][x - 1].ants_pointers[k].size(); ++l) {
                                if (field[y][x - 1].ants_pointers[k][l] == nullptr) {
                                    continue;
                                }
                                chosen.insert(std::pair<int, ANT*>((field[y][x - 1].ants_pointers[k][l])->pause, field[y][x - 1].ants_pointers[k][l]));
                            }
                        }
                        auto it = chosen.begin();
                        if (it == chosen.end()) {
                            break;
                        }
                        auto pair = chosen.equal_range(it->first);
                        auto cit = pair.first;
                        int count = 0;
                        for(; cit != pair.second; ++cit) {
                            ++count;
                        }
                        count = std::rand() % count;
                        cit = pair.first;
                        for (unsigned k = 0; k < count; ++k) {
                            ++cit;
                        }
                        cit->second->pause = 8;
                        if (cit->second->hasFood() == true) {
                            cit->second->putFood();
                            field[cit->second->cur_y][cit->second->cur_x].Food += 1;
                        }
                        break;
                    }
                    case antlogic::BITE_DOWN: {
                        if (field[y + 1][x].isWall == true) {
                            break;
                        }
                        for (unsigned k = 0; k < field[y + 1][x].ants_pointers.size(); ++k) {
                            if (k == tid - 1) {
                                continue;
                            }
                            for (unsigned l = 0; l < field[y + 1][x].ants_pointers[k].size(); ++l) {
                                if (field[y + 1][x].ants_pointers[k][l] == nullptr) {
                                    continue;
                                }
                                chosen.insert(std::pair<int, ANT*>((field[y + 1][x].ants_pointers[k][l])->pause, field[y + 1][x].ants_pointers[k][l]));
                            }
                        }
                        auto it = chosen.begin();
                        if (it == chosen.end()) {
                            break;
                        }
                        auto pair = chosen.equal_range(it->first);
                        auto cit = pair.first;
                        int count = 0;
                        for(; cit != pair.second; ++cit) {
                            ++count;
                        }
                        count = std::rand() % count;
                        cit = pair.first;
                        for (unsigned k = 0; k < count; ++k) {
                            ++cit;
                        }
                        cit->second->pause = 8;
                        if (cit->second->hasFood() == true) {
                            cit->second->putFood();
                            field[cit->second->cur_y][cit->second->cur_x].Food += 1;
                        }
                        break;
                    }
                    case antlogic::BITE_RIGHT: {
                        if (field[y][x + 1].isWall == true) {
                            break;
                        }
                        for (unsigned k = 0; k < field[y][x + 1].ants_pointers.size(); ++k) {
                            if (k == tid - 1) {
                                continue;
                            }
                            for (unsigned l = 0; l < field[y][x + 1].ants_pointers[k].size(); ++l) {
                                if (field[y][x + 1].ants_pointers[k][l] == nullptr) {
                                    continue;
                                }
                                chosen.insert(std::pair<int, ANT*>((field[y][x + 1].ants_pointers[k][l])->pause, field[y][x + 1].ants_pointers[k][l]));
                            }
                        }
                        auto it = chosen.begin();
                        if (it == chosen.end()) {
                            break;
                        }
                        auto pair = chosen.equal_range(it->first);
                        auto cit = pair.first;
                        int count = 0;
                        for(; cit != pair.second; ++cit) {
                            ++count;
                        }
                        count = std::rand() % count;
                        cit = pair.first;
                        for (unsigned k = 0; k < count; ++k) {
                            ++cit;
                        }
                        cit->second->pause = 8;
                        if (cit->second->hasFood() == true) {
                            cit->second->putFood();
                            field[cit->second->cur_y][cit->second->cur_x].Food += 1;
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
            if (teams[i].units[j].pause > 0) {
                teams[i].units[j].pause -= 1;
            }
        }
    }
    for (unsigned i = 1; i < field.size() - 1; ++i) {
        for (unsigned j = 1; j < field[i].size() - 1; ++j) {
            if (field[i][j].smellIntensity > 0) {
                field[i][j].smellIntensity -= 1;
            }
        }
    }
}
int main(int argc, char **argv) {
    std::srand(std::time(nullptr));
    const char *action_function = "_ZN8antlogic9GetActionERKNS_3AntEPA3_NS_9AntSensorE";
    std::vector<TEAM> teams;
    std::vector<void*> strategies;
    std::cout << "Enter field size" << std::endl;
    int N;
    std::cin >> N;
    std::vector<std::vector<CELL>> field(N);
    for (int i = 0; i < N; ++i) {
        field[i].resize(N);
    }
    std::cout << "Enter coordinates for each Hill from " << argc - 1 << std::endl;
    std::vector<std::pair<int, int>> hills;
    for (int i = 1; i < argc; ++i) {
        int x, y;
        std::cin >> x >> y;
        hills.push_back({x, y});
    }
    std::cout << "Enter number of units for each team from " << argc - 1 << std::endl;
    for (int i = 1; i < argc; ++i) {
        int n;
        std::cin >> n;
        strategies.push_back(dlopen(argv[i], RTLD_LAZY));
        teams.push_back(TEAM(i, n, dlsym(strategies[i - 1], action_function), hills[i - 1].first, hills[i - 1].second));
    }
    start(field, hills, teams);
    std::cout << "Enter day's length" << std::endl;
    int DAY_LENGTH;
    std::cin >> DAY_LENGTH;
    for (int i = 0; i < DAY_LENGTH; ++i) {
        print(field);
        print_stat(field, hills, i, DAY_LENGTH);
        move(field, teams);
        usleep(50000);
        clear(field.size() + hills.size() + 3);
    }
    print_stat(field, hills, DAY_LENGTH, DAY_LENGTH);
    for (int i = 1; i < argc; ++i) {
        dlclose(strategies[i - 1]);
    }
}