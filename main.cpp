#include <iostream>
#include <string>

#include "maze.h"

using namespace std;


int main(int ac, char *av[])
{
    Maze *m;
    if (ac < 2)
        return 0;

    if (ac == 2)
        m = new Maze(stoi(av[1]));
    else
        m = new Maze(stoi(av[1]), stoi(av[2]));

    m->drawMaze();
}
