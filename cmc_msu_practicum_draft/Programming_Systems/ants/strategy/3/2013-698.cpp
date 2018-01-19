#include "IAntLogic.hpp"

#include <stdlib.h>
#include <string.h>

namespace antlogic
{
    const int dx0[] = {1, 1, 0, -1, -1, -1, 0, 1};
    const int dy0[] = {0, 1, 1, 1, 0, -1, -1, -1};
    const int dx[] = {0, -1, 0, 1};
    const int dy[] = {-1, 0, 1, 0};
    AntAction GetAction(const Ant &ant, AntSensor sensors[3][3])
    {


        char *memory = ant.getMemory();
        AntAction action;


        for(int i = 0; i < 4; i++)
        {
            if(sensors[1 + dx[i]][1 + dy[i]].isEnemy && memory[6])
            {
                action.actionType = AntActionType(BITE_UP + i);
                memory[6] = 0;
                return action;
            }
        }
        if(sensors[1][1].isMyHill)
        {
            memory[2] = rand()%4;
        }

        if (ant.hasFood() && sensors[1][1].isMyHill)
        {
            action.actionType = PUT;
        }
        else if (!ant.hasFood() && !sensors[1][1].isMyHill && sensors[1][1].isFood)
        {
            action.actionType = GET;
        }
        else
        {        
            if(sensors[1 + dx[memory[2]]][1 + dy[memory[2]]].isWall)
            {
                memory[2] += 2;
            }
            action.actionType = AntActionType(memory[2]);
        }
        return action;
    }
}
