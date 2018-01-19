#include "IAntGUI.hpp"

#include "AntWidget.hpp"
#include "IAntGuiImpl.hpp"

#include <QPixmap>
#include <QPainter>

#include <map>
#include <algorithm>
#include <memory>
#include <iostream>
#include <unistd.h>

namespace antgui
{
    using namespace std;

    std::shared_ptr<IAntGui> IAntGui::getGUI()
    {
        return std::shared_ptr<IAntGui>(new AntGuiQtImpl());
    }

    void IAntCui::BeginPaint() {
        for (unsigned i = 1; i < field.size() - 1; ++i) {
            for (unsigned j = 1; j < field[i].size() - 1; ++j) {
                field[i][j] = "*";
            }
        }
    }

    void IAntCui::SetAnt(const Ant &ant) {
        Point cur = ant.getPoint();
        std::string res = "a";
        if (ant.hasFood()) {
            res = "@";
        }
        if (ant.isFrozen()) {
            res = "w";
        }
        res = "\033[1;3" + std::to_string(ant.getTeamId()) + "m" + res + "\033[0m";
        field[cur.y][cur.x] = res;
    }
    void IAntCui::SetFood(const Food &food) {
        Point cur = food.getPoint();
        field[cur.y][cur.x] = "\033[1;30mf\033[0m";
    }

    void IAntCui::SetTeamScore(int teamId, int score) {
        std::cout << "\033[1;3" << teamId + 1 << "m";
        std::cout << "team " << teamId << ": " << score << std::endl << "\033[0m" << std::flush;
    }

    void IAntCui::EndPaint() {
        for (unsigned i = 0; i < field.size(); ++i) {
            for (unsigned j = 0; j < field[i].size(); ++j) {
                std::cout << field[i][j];
            }
            std::cout << std::endl << std::flush;
        }
        usleep(50000);
        for (unsigned i = 0; i < field.size() + 4; ++i) {
            std::cout << "\33[1A\33[2K\r" << std::flush;
        }
    }




}
