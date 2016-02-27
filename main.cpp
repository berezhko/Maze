#include <iostream>
#include <string>

#include "maze.h"

using namespace std;


int main(int ac, char *av[])
{
    if (ac < 2)
        return 0;

    Maze m = Maze(stoi(av[1]));

    m.makeMaze();
    m.drawMaze();
}
