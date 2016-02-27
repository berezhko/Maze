#include <iostream>
#include <string>
#include <memory>
#include "maze.h"

using namespace std;


int main(int ac, char *av[])
{
    if (ac < 2)
        return 0;

    Maze *m;
    if (ac == 2)
        m = new Maze(stoi(av[1]));
    else
        m = new Maze(stoi(av[1]), stoi(av[2]));

    unique_ptr<Maze> up(m);
    up->drawMaze();
}
