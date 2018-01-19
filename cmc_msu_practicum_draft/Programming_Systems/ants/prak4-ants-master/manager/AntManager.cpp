#include "AntManager.hpp"
#include <memory.h>
#include <vector>
#include <map>
#include <ctime>
#include <memory>

//
//  AntManager
//

void initialize(std::vector<std::vector<CELL>> &field, std::vector<std::pair<int, int>> &hills, std::vector<TEAM> &teams) {
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
                        unsigned count = 0;
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
                        unsigned count = 0;
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
                        unsigned count = 0;
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
                        unsigned count = 0;
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

AntManager::AntManager(int height, int width, int teamCount, int maxAntCountPerTeam, Base &base)
{
	this->height = height;
	this->width = width;
	this->teamCount = teamCount;
	this->maxAntCountPerTeam = maxAntCountPerTeam;
    this->field.resize(height);
    for (int i = 0; i < height; ++i) {
        this->field[i].resize(width);
    }
    for (int i = 0; i < teamCount; ++i) {
        this->hills.push_back({base.coords[i].first, base.coords[i].second});
    }
    for (int i = 0; i < teamCount; ++i) {
        teams.push_back(TEAM(i + 1, maxAntCountPerTeam, base.strategy[i], hills[i].first, hills[i].second));
    }
    initialize(this->field, this->hills, this->teams);
}

void AntManager::step(int step)
{
    ++step;
    move(field, teams);

    gui->BeginPaint();

    for (unsigned i = 0; i < teams.size(); ++i) {
        for (unsigned j = 0; j < teams[i].units.size(); ++j) {
            gui->SetAnt(teams[i].units[j]);
        }
    }

    for (unsigned i = 1; i < field.size() - 1; ++i) {
        for (unsigned j = 1; j < field[i].size() - 1; ++j) {
            if (field[i][j].Food == 0) {
                continue;
            }
            gui->SetFood(FOOD(j, i, field[i][j].Food));
        }
    }

    for (unsigned t = 0; t < teamCount; t++)
    {
        gui->SetTeamScore(t, field[hills[t].second][hills[t].first].Food);

    }
    gui->EndPaint();
}

void AntManager::setGui(std::shared_ptr<antgui::IAntGui> gui)
{
    this->gui = gui;
}

void AntManager::setCui()
{
    gui = std::dynamic_pointer_cast<antgui::IAntGui>(std::shared_ptr<antgui::IAntCui>(
          new antgui::IAntCui(field[0].size(), field.size())));
}

void AntManager::consolePlay(unsigned num)
{
    setFoodGeneretor(std::make_shared<food_iterator>(field.size()));
    for (unsigned i = 0; i < num; ++i) {
        step(i);
    }
    for (unsigned t = 0; t < teamCount; t++)
    {
        gui->SetTeamScore(t, field[hills[t].second][hills[t].first].Food);

    }
}

void AntManager::setFoodGeneretor(std::shared_ptr<food_iterator> it)
{
    std::srand(time(nullptr));
    for (unsigned i = 1; i < field.size() - 1; ++i) {
        for (unsigned j = 1; j < field[i].size() - 1; ++j) {
            if (field[i][j].Hill > 0) {
                continue;
            }
            int switcher = std::rand() % 8;
            if (switcher == 6) {
                field[i][j].Food = std::rand()/(RAND_MAX + 1.0) * it->size;
                continue;
            }
            if (switcher == 5) {
                field[i][j].Food = std::rand()/(RAND_MAX + 1.0) * 5;
                continue;
            }
        }
    }
}
