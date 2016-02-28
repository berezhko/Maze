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
    for (i->first();! i->isDone(); i->next()){
        shared_ptr<Cell> cell = i->currentCell();
        if (cell->getId() == sizeh*sizev)
            break;

        if (cell->getId() % sizeh == 1)
            (cell->getId() == 1) ? cout << " " : cout << "|";
        cout << "  ";

        size_t down = cell->getId()+sizeh;
        wall = cell->getWall(down);
        if (wall != nullptr){
            if( wall->isExist() )
                hline += "--+";
            else
                hline += "  +";
        }

        size_t right = cell->getId()+1;
        wall = cell->getWall(right);
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


int main(int ac, char *av[])
{
    if (ac < 2)
        return 0;

    Maze *m;

    if (ac == 2)
        m = new Maze(stoi(av[1]));
    else
        m = new Maze(stoi(av[1]), stoi(av[2]));

    drawMaze(m);


}
