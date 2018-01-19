#include "IAntLogic.hpp"
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>

using namespace std;


const int ROLE = 0;

const int POSX = 1;

const int POSY = 2;


const int CNTMOVES = 3;
const int DESTX = 4;
const int DESTY = 5;

const int sclx = 6;
const int scly = 7;

const int STRIKE = 8;

const int ID = 9;

const int roles[] = {12, 112, 12, 3, 3, 3, 3, 3, 3, 3};

const int KILLLIMIT = 2;

const int HOMEX = 0;

const int HOMEY = 0;

const int LASTPX = 10;
const int LASTPY = 11;
const int ANGRY = 13;

const int SECRET = 849308;

const int SECRETM = 499124;

const int SECRETR = 34534;

const int NOW = 12;

const int NUMFAILS = 31;

const int LEAVE = 30;

const int ATTACK = 29;

const int MAXFAILS = 3;

const int ATTACKCODE = -69846;

const int WAIT = 28;

const int WAITLIMIT = 50;

const int DARKSIDE = -1;

namespace antlogic
{
    pair<bool, int> getsmell(AntSensor sensor[3][3], char* mem)
    {
        if (mem[POSX] == 0 && mem[POSY] == 0)
            return make_pair(false, 0);
        else if (mem[ROLE] == 3)
        {
            if ((mem[LASTPX] != 0 || mem[LASTPY] != 0 ) && mem[LEAVE])
            {
                int x = abs(mem[LASTPX]) * 31 + abs(mem[LASTPY]);
                x = x * SECRETM + SECRETR;
                x = -x;
                x ^= SECRET;
                --mem[LEAVE];
                return make_pair(true, x);
            }
            return make_pair(false, 0);
        }
        else if (rand() % 2)
            return make_pair(true, rand());
        else
            return make_pair(true, -rand());
    }
    pair<bool, pair<int, int> > getInfo(AntSensor sensor[3][3], char* mem)
    {
        pair<bool,pair<int, int> > xx;
        xx.first = false;
        int maxi = 60;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
            {
                int x = sensor[i][j].smell;
                if (x > 0)
                    continue;
                x ^= SECRET;
                x = -x;
                if (x % SECRETM != SECRETR)
                    continue;
                x /= SECRETM;
                if (x / 31 > 30)
                    continue;
                if (x / 31 < 3 && x % 31 < 3)
                    continue;
                if (sensor[i][j].smellIntensity > maxi)
                {
                    xx.first = true;
                    xx.second.first =  mem[sclx] * (x / 31);
                    xx.second.second = mem[scly] * (x % 31);
                    maxi = sensor[i][j].smellIntensity;
                }
            }
        return xx;
    }


    AntAction moveDown(char* mem, AntAction act, AntSensor sensors[3][3])
    {
        act.actionType = MOVE_DOWN;
        if (!sensors[1][2].isWall)
            --mem[POSY];
        mem[STRIKE] = 0;
        return act;
    }
    AntAction moveUp(char* mem, AntAction act, AntSensor sensors[3][3])
    {
        act.actionType = MOVE_UP;
        if (!sensors[1][0].isWall)
            ++mem[POSY];
        mem[STRIKE] = 0;
        return act;
    }
    AntAction moveLeft(char* mem, AntAction act, AntSensor sensors[3][3])
    {
        act.actionType = MOVE_LEFT;
        if (!sensors[0][1].isWall)
            --mem[POSX];
        mem[STRIKE] = 0;
        return act;
    }
    AntAction moveRight(char* mem, AntAction act, AntSensor sensors[3][3])
    {
        act.actionType = MOVE_RIGHT;
        if (!sensors[2][1].isWall)
            ++mem[POSX];
        mem[STRIKE] = 0;
        return act;
    }


    pair<bool, AntAction> fight(AntAction act, AntSensor sensors[3][3],char* mem)
    {
        if (mem[STRIKE] >= KILLLIMIT)
            return make_pair(false, act);
        pair<int, int> arr[] = {make_pair(0, 1), make_pair(1, 0), make_pair(0, -1), make_pair(-1, 0)};
        random_shuffle(arr, arr + 4);
        for (int i = 0; i < 4; ++i)
        {
            if (sensors[1 + arr[i].first][1 + arr[i].second].isEnemy)
            {
                ++mem[STRIKE];
                if (arr[i].first == 0)
                {
                    if (arr[i].second == 1)
                        act.actionType = BITE_DOWN;
                    else
                        act.actionType = BITE_UP;
                }
                else if (arr[i].first == 1)
                    act.actionType = BITE_RIGHT;
                else
                    act.actionType = BITE_LEFT;
                return make_pair(true, act);
            }
        }
        return make_pair(false, act);
    }
    AntAction goTo(AntAction act, char* mem, AntSensor sensors[3][3])
    {
        auto xx = fight(act, sensors, mem);
        if (xx.first)
            return xx.second;
        if (mem[POSX] == mem[DESTX] && mem[POSY] == mem[DESTY])
            act.actionType = BITE_DOWN;
        else if (mem[POSX] == mem[DESTX])
        {
            if (mem[POSY] < mem[DESTY])
                return moveUp(mem, act,sensors);
            else
                return moveDown(mem, act,sensors);
        }
        else if (mem[POSY] == mem[DESTY])
        {
            if (mem[POSX] < mem[DESTX])
                return moveRight(mem, act,sensors);
            else
                return moveLeft(mem, act,sensors);
        }
        else if (rand() % 2)
        {
            if (mem[POSY] < mem[DESTY])
                return moveUp(mem, act,sensors);
            else
                return moveDown(mem, act,sensors);
        }
        else
        {
            if (mem[POSX] < mem[DESTX])
                return moveRight(mem, act,sensors);
            else
                return moveLeft(mem, act,sensors);
        }
        return act;
    }

    AntAction GetAction(const Ant &ant, AntSensor sensors[3][3])
    {
        char *mem = ant.getMemory();
        srand(time(NULL) + mem[CNTMOVES] + 1001 * mem[ID]);
        AntAction act;
        act.actionType = BITE_DOWN;

        if (mem[ROLE] != 0)
        {
            pair<bool, int> sm = getsmell(sensors, mem);
            act.putSmell = sm.first;
            if (sm.first)
                act.smell = sm.second;
        }

        ++mem[CNTMOVES];
        if (!ant.hasFood() && mem[ROLE] == 3)
        {
            ++mem[ANGRY];
            if (mem[ANGRY] == DARKSIDE)
                mem[ROLE] = 1;

        }


        if (mem[DESTX] * mem[sclx] < 0 || mem[DESTX] * mem[sclx] > 30)
        {
            mem[DESTX] = 0;
            mem[DESTY] = 0;
        }
        if (mem[DESTY] * mem[scly] < 0 || mem[DESTY] * mem[scly] > 30)
        {
            mem[DESTX] = 0;
            mem[DESTY] = 0;
        }


        if (mem[ROLE] == 0) // Init
        {
            mem[NOW] = 16;
            mem[POSX] = 0;
            mem[POSY] = 0;
            mem[DESTX] = 0;
            mem[DESTY] = 0;
            if (sensors[1][2].isWall)
                mem[scly] = 1;
            else
                mem[scly] = -1;
            if (sensors[0][1].isWall)
                mem[sclx] = 1;
            else
                mem[sclx] = -1;
            if (sensors[1][1].smellIntensity == 0)
            {
                mem[ID] = 0;
                mem[ROLE] = roles[0];
                act.putSmell = true;
                act.smell = 1;
            }
            else
            {
                mem[ID] = sensors[1][1].smell;
                mem[ROLE] = roles[sensors[1][1].smell];
                act.putSmell = 1;
                act.smell = sensors[1][1].smell + 1;
            }
            return act;
        }
        if (mem[ROLE] == 1) //Trader
        {
            if ((mem[POSX] != HOMEX || mem[POSY] != HOMEY) && mem[ATTACK] == 0)
            {
                mem[DESTX] = 0;
                mem[DESTY] = 0;
                return goTo(act, mem, sensors);
            }
            if (sensors[1][1].smell == ATTACKCODE && sensors[1][1].smellIntensity > 90)
            {
                mem[ATTACK] = 1;
            }
            if (mem[ATTACK] == 0)
            {
                ++mem[WAIT];
                if (mem[WAIT] == WAITLIMIT)
                {
                    act.putSmell = 1;
                    act.smell = ATTACKCODE;
                    mem[DESTX] = ((int)mem[sclx]) * 0;
                    mem[DESTY] = ((int)mem[scly]) * 30;
                    mem[ATTACK] = 1;
                    return goTo(act, mem, sensors);
                }
                else
                {
                    auto xx = fight(act, sensors, mem);
                    if (xx.first)
                        return xx.second;
                    else
                    {
                        act.actionType = BITE_DOWN;
                        return act;
                    }
                }
            }
            if (ant.hasFood())
            {
                if (mem[POSX] == HOMEX && mem[POSY] == HOMEY)
                {
                    auto xx = fight(act, sensors, mem);
                    if (xx.first)
                        return xx.second;
                    else
                    {
                        act.actionType = PUT;
                        mem[DESTX] = 0;
                        mem[DESTY] = 0;
                        mem[WAIT] = 0;
                        mem[ATTACK] = 0;
                        return act;
                    }
                }
                mem[DESTX] = HOMEX;
                mem[DESTY] = HOMEY;
                act = goTo(act, mem, sensors);
            }
            else
            {
                if (sensors[1][1].isFood && !sensors[1][1].isMyHill)
                {
                    auto xx = fight(act, sensors, mem);
                    if (xx.first)
                        return xx.second;
                    else
                    {
                        act.actionType = GET;
                        return act;
                    }
                }
                if (mem[DESTX] == 0 && mem[DESTY] == 0)
                {
                    mem[DESTX] = ((int)mem[sclx]) * 0;
                    mem[DESTY] = ((int)mem[scly]) * 30;
                }
                if (mem[DESTX] == mem[POSX] && mem[DESTY] == mem[POSY])
                {
                    if (mem[DESTX] == ((int)mem[sclx]) * 0 && mem[DESTY] == ((int)mem[scly]) * 30)
                    {
                        mem[DESTX] = ((int)mem[sclx]) * 30;
                        mem[DESTY] = ((int)mem[scly]) * 30;
                    }
                    else if (mem[DESTX] == ((int)mem[sclx]) * 30 && mem[DESTY] == ((int)mem[scly]) * 30)
                    {
                        mem[DESTX] = ((int)mem[sclx]) * 30;
                        mem[DESTY] = ((int)mem[scly]) * 0;
                    }
                    else if (mem[DESTX] == ((int)mem[sclx]) * 30 && mem[DESTY] == ((int)mem[scly]) * 0)
                    {
                        mem[DESTX] = ((int)mem[sclx]) * 0;
                        mem[DESTY] = ((int)mem[scly]) * 0;
                    }
                }
                act = goTo(act, mem, sensors);
            }
            return act;
        }
        else if (mem[ROLE] % 10 == 2) //Hill Defender CORRECT
        {
            if (mem[ROLE] % 100 == 12)
            {
                if (mem[ROLE] == 12)
                {
                    mem[STRIKE] = 0;
                    auto xx = fight(act, sensors, mem);
                    if (xx.first)
                        return xx.second;
                    act.actionType = BITE_DOWN;
                    return act;
                }
                else
                {
                    if (mem[DESTX] == 0 && mem[DESTY] == 0)
                    {
                        mem[DESTX] = ((int)mem[sclx]) * 1;
                        mem[DESTY] = ((int)mem[scly]) * 1;
                        return goTo(act, mem, sensors);
                    }
                    else
                    {
                        if (mem[POSX] != mem[DESTX] || mem[POSY] != mem[DESTY])
                            return goTo(act, mem, sensors);
                        else
                        {
                            mem[STRIKE] = 0;
                            auto xx = fight(act, sensors, mem);
                            if (xx.first)
                                return xx.second;
                            act.actionType = BITE_DOWN;
                            return act;
                        }
                    }
                }
            }
            else if (mem[ROLE] % 100 == 22 || mem[ROLE] % 100 == 32)
            {
                if (mem[DESTX] == 0 && mem[DESTY] == 0)
                {
                    if (mem[ROLE] == 22)
                    {
                        mem[DESTX] = ((int)mem[sclx]) * 29;
                        mem[DESTY] = ((int)mem[scly]) * 1;
                    }
                    else if (mem[ROLE] == 122)
                    {
                        mem[DESTY] = ((int)mem[scly]) * 29;
                        mem[DESTX] = ((int)mem[sclx]) * 1;
                    }
                    else
                    {
                        mem[DESTX] = ((int)mem[sclx]) * 29;
                        mem[DESTY] = ((int)mem[scly]) * 29;
                    }
                    return goTo(act, mem, sensors);
                }
                else
                {
                    if (mem[POSX] != mem[DESTX] || mem[POSY] != mem[DESTY])
                        return goTo(act, mem, sensors);
                    else
                    {
                        mem[STRIKE] = 0;
                        auto xx = fight(act, sensors, mem);
                        if (xx.first)
                            return xx.second;
                        act.actionType = BITE_DOWN;
                        return act;
                    }
                }
            }
        }
        else if (mem[ROLE] == 3) //Thief
        {
            auto xx = getInfo(sensors, mem);
            if (xx.first)
            {
                mem[mem[NOW]] = xx.second.first;
                mem[mem[NOW] + 1] = xx.second.second;
                mem[NOW] += 2;
                if (mem[NOW] > 27)
                    mem[NOW] = 16;
            }
            if (ant.hasFood())
            {
                if (mem[POSX] == HOMEX && mem[POSY] == HOMEY)
                {
                    auto xx = fight(act, sensors, mem);
                    if (xx.first)
                        return xx.second;
                    else
                    {
                        act.actionType = PUT;
                        mem[DESTX] = 0;
                        mem[DESTY] = 0;
                        return act;
                    }
                }
                mem[DESTX] = 0;
                mem[DESTY] = 0;
                return goTo(act, mem, sensors);
            }
            else if (sensors[1][1].isFood && !sensors[1][1].isMyHill)
            {
                auto xx = fight(act, sensors, mem);
                if (xx.first)
                    return xx.second;
                else
                {
                    act.actionType = GET;
                    mem[ANGRY] = 0;
                    mem[LASTPX] = mem[POSX];
                    mem[LASTPY] = mem[POSY];
                    //mem[LASTPT] = mem[CNTMOVES];
                    mem[LEAVE] = 10;
                    mem[14] = mem[POSX];
                    mem[15] = mem[POSY];
                    mem[NUMFAILS] = 0;
                    return act;
                }
            }
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    if (( abs(i - 1) + abs(j - 1) == 1) && !sensors[i][j].isMyHill && sensors[i][j].isFood && abs(mem[DESTX] - mem[POSX]) + abs(mem[DESTY] - mem[POSY]) > 1)
                    {
                        mem[DESTX] = mem[POSX] + i - 1;
                        mem[DESTY] = mem[POSY] - (j - 1);
                        return goTo(act, mem, sensors);
                    }
                }
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    if (!sensors[i][j].isEnemy && !sensors[i][j].isMyHill && sensors[i][j].isFood && abs(mem[DESTX] - mem[POSX]) + abs(mem[DESTY] - mem[POSY]) > 2)
                    {
                        mem[DESTX] = mem[POSX] + i - 1;
                        mem[DESTY] = mem[POSY] - (j - 1);
                        return goTo(act, mem, sensors);
                    }
                }
            if (mem[POSX] == mem[DESTX] && mem[POSY] == mem[DESTY])
            {
                for (int i = 14; i <= 27; i += 2)
                {
                    if (mem[i] == mem[DESTX] && mem[i + 1] == mem[DESTY])
                    {
                        mem[i] = 0;
                        mem[i + 1] = 0;
                    }
                }
                mem[DESTX] = 0;
                mem[DESTY] = 0;
                ++mem[NUMFAILS];
            }
            if (mem[DESTX] != HOMEX || mem[DESTY] != HOMEY)
                return goTo(act, mem, sensors);
            int bstx = 100;
            int bsty = 100;
            for (int i = 14; i <= 27; i += 2)
            {
                if (mem[i] != 0 || mem[i + 1] != 0)
                {
                    if (abs(mem[POSX] - bstx) + abs(mem[POSY] - bsty) + abs(bstx) + abs(bsty) > abs(mem[POSX] - mem[i]) + abs(mem[POSY] - mem[i + 1]) + abs(mem[i]) + abs(mem[i + 1]))
                    {
                        bstx = mem[i];
                        bsty = mem[i + 1];
                    }
                }
            }
            if (bstx != 100 && mem[NUMFAILS] < MAXFAILS)
            {
                mem[DESTX] = bstx;
                mem[DESTY] = bsty;
                return goTo(act, mem, sensors);
            }
            else
            {
                mem[DESTX] = ((int)mem[sclx]) * (rand() % 31);
                mem[DESTY] = ((int)mem[scly]) * (rand() % 31);
                mem[NUMFAILS] = 0;
                return goTo(act, mem, sensors);
            }
        }
        return act;
    }
}

