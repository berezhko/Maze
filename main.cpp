#include <iostream>
#include <string>
#include <memory>

#include "maze.h"

using namespace std;

void drawMaze(Maze *m)
{
    size_t sizev;
    size_t sizeh;
    tie(sizev, sizeh) = m->getDimension();

    shared_ptr<Wall> wall;
    cout << "+";
    for (size_t i = 0; i < sizeh; i++)
        cout << "--+";
    cout << endl;
    string hline = "+";

    Iterator_ptr i(m->createIterator());
    for (i->begin();! i->end(); i++){
        shared_ptr<Cell> cell = i->currentCell();
        if (cell->getId() == sizeh*sizev)
            break;

        if (cell->getId() % sizeh == 1)
            (cell->getId() == 1) ? cout << " " : cout << "|";
        cout << "  ";

        wall = cell->getWall(cell->getId()+sizeh);
        if (wall != nullptr){
            if( wall->isExist() )
                hline += "--+";
            else
                hline += "  +";
        }

        wall = cell->getWall(cell->getId()+1);
        if (wall != nullptr){
            if( wall->isExist() )
                cout << "|";
            else
                cout << " ";
        }else{
            cout << "|" << endl << hline << endl;
            hline = "+";
        }
    }
    cout << "   " << endl << "+";
    for (size_t i = 0; i < sizeh; i++)
        cout << "--+";
    cout << endl;
}

unique_ptr<Maze> initMaze(int ac, char *av[])
{
    if (ac < 2)
        return nullptr;

    Maze *m;
    if (ac == 2)
        m = new Maze(stoi(av[1]));
    else
        m = new Maze(stoi(av[1]), stoi(av[2]));

    unique_ptr<Maze> up(m);
    return up;
}

int main(int ac, char *av[])
{
    unique_ptr<Maze> maze = initMaze(ac, av);

    if (maze)
        drawMaze(maze.get());
}
