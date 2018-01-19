#include "IAntLogic.hpp"

#include <stdlib.h>
#include <string.h>

#include <limits>
#include <random>

namespace antlogic
{
    AntAction GetAction(const Ant &ant, AntSensor sensors[3][3])
    {
        // char *memory = ant.getMemory();
        // AntAction action;
        // if (memory[1] == 0 && sensors[1][1].isFood && !sensors[1][1].isMyHill) {
        //   action.actionType = GET;
        //   memory[1] = 1;
        //   return action;
        // }
        // memory[1] = 0;
        // if (ant.hasFood() && sensors[1][1].isMyHill) {
        //   action.actionType = PUT;
        //   return action;
        // }          
        // if (memory[0] == 0 && sensors[2][1].isWall)
        //   memory[0] = 1;        
        // else if (memory[0] == 1 && sensors[1][2].isWall)
        //   memory[0] = 2;        
        // else if (memory[0] == 2 && sensors[0][1].isWall)
        //   memory[0] = 3;        
        // else if (memory[0] == 3 && sensors[1][0].isWall)
        //   memory[0] = 0;
        // if (memory[0] == 0)
        //   action.actionType = MOVE_RIGHT;
        // else if (memory[0] == 1)
        //   action.actionType = MOVE_DOWN;
        // else if (memory[0] == 2)
        //   action.actionType = MOVE_LEFT;
        // else 
        //   action.actionType = MOVE_UP;
        // return action;

      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<int> dis(0, 9);
      AntAction a;
      a.actionType = static_cast<AntActionType>(dis(gen));
      std::uniform_int_distribution<int> dis2(0, 1);
      a.putSmell = dis2(gen);
      std::uniform_int_distribution<int> dis3(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
      a.smell = dis3(gen);
      return a;
    }
}