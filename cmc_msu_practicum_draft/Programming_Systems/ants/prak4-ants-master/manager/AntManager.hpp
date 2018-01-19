#ifndef ANTMANAGER_HPP
#define ANTMANAGER_HPP

#include "IAntGUI.hpp"
#include "IAntLogic.hpp"


#include <memory>

#include <vector>
#include <string>
#include <cstring>
#include <utility>


class ANT: public antgui::Ant {
    char *mem = nullptr;
    unsigned team_id;
    bool food = false;
public:
    antlogic::AntAction(*action)(const antlogic::Ant&,antlogic::AntSensor[3][3]);
    int cur_x, cur_y;
    int pause = 0;
    ANT(int tid = 1, void* func = nullptr, int x = 0, int y = 0): antgui::Ant() {
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
    bool isFrozen() const {return pause > 0;}
    antgui::Point getPoint() const {return antgui::Point(cur_x, cur_y);}
};

enum {
    MY_PLAYER_COUNT = 4,
    MY_FIELD_SIZE = 31,
    MY_ANT_COUNT = 10
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
    unsigned Hill = 0;
    int Food = 0;
    bool isWall = true;
};

class FOOD: public antgui::Food {
    int x, y, count;
public:
    FOOD(int cur_x, int cur_y, int cur_count): x(cur_x), y(cur_y), count(cur_count) {}
    antgui::Point getPoint() const {return antgui::Point(x, y);}
    int getCount() const {return count;}
};

class food_iterator {
public:
    int size;
    food_iterator(int size) : size(size) {}
};

struct Base {
    std::vector<std::pair<int, int>> coords;
    std::vector<void *> strategy;
};

class AntManager
{
    int maxAntCountPerTeam;
    unsigned teamCount;
    int height;
    int width;
    std::shared_ptr<antgui::IAntGui> gui;
public:
    std::vector<TEAM> teams;
    std::vector<std::vector<CELL>> field;
    std::vector<std::pair<int, int>> hills;
    AntManager(int height,
               int width,
               int teamCount,
               int maxAntCountPerTeam, Base &base);

    virtual void step(int iRun);
    void setGui(std::shared_ptr<antgui::IAntGui> gui);
    void setCui();
    void consolePlay(unsigned num);
    void setFoodGeneretor(std::shared_ptr<food_iterator> it);
};

#endif
