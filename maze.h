#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <list>
#include <cassert>

#include "wall.h"
#include "cell.h"

using namespace std;


size_t getRandom(int n);


class Maze
{
public:
    typedef shared_ptr<Cell> SpCell;
    typedef shared_ptr<Wall> SpWall;

    explicit Maze(size_t s): Maze(s, s) { }
    Maze(size_t h, size_t v): sizeh(h), sizev(v)
    {
        makeCells();
        makeWalls();
        makeMaze();
    }

    void printCells()
    {
        for(auto& c: cells)
            c->printNeighbor();
    }
    void printWalls()
    {
        for(auto& wall: walls){
            if (wall->isExist()){
                wall->printWall();
                cout << endl;
            }
        }
    }
    void drawMaze()
    {
        SpWall wall;
        cout << "+";
        for (size_t i = 0; i < sizeh; i++)
            cout << "--+";
        cout << endl;
        string hline = "+";
        for (auto& cell: cells){
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

protected:
    Maze();
    Maze(const Maze&);
    Maze& operator=(const Maze&);

private:
    void makeMaze()
    {
        list<SpCell> steck;
        steck.push_back(cells[getRandom(cells.size())]);
        steck.back()->toVisit();
        while (!steck.empty()){
            SpCell cell = steck.back();
            if (cell->existNeighborNotVisit()){
                SpCell randomcell {cell->getNeighborNotVisit()};
                randomcell->toVisit();
                randomcell->breakWall(cell);
                steck.push_back(randomcell);
            }else{
                steck.pop_back();
            }
        }
    }
    vector<SpCell> findNeighborCell(size_t id)
    {
        size_t line = ((id-1)/sizeh) + 1;
        vector<SpCell> nb;

        if (id - sizeh >= 1 && id - sizeh <= sizeh*sizev)
            nb.push_back( cells[id-sizeh - 1] );
        if (id - 1 >= (line-1)*sizeh+1)
            nb.push_back( cells[id-1 -1] );
        if (id + 1 <= line*sizeh)
            nb.push_back( cells[id+1 - 1] );
        if (id + sizeh <= sizeh*sizev)
            nb.push_back( cells[id+sizeh - 1] );

        return nb;
    }
    void makeCells()
    {
        for (size_t id = 1; id <= sizeh*sizev; id++)
            cells.push_back(SpCell {new Cell(id), [](Cell *c) {
                                    //cout << c->getId() << " ";
                                    delete c;
            }});

        for (auto& cell: cells){
            vector<SpCell> nb = findNeighborCell(cell->getId());
            cell->storeNeighborCells(nb);
            // TODO makeWall() do this ?
        }
    }
    void makeWalls()
    {
        for (auto& cell: cells){
            vector<SpCell> nb =  findNeighborCell(cell->getId());

            for (auto& nbcell: nb){
                SpWall wall {new Wall(*cell, *nbcell), [](Wall *w) {
                                    //w->printWall();
                                    delete w;
                }};
                auto poswall = find_if(walls.begin(), walls.end(),
                                    [&wall](SpWall w){return *w == *wall;});
                if (poswall == walls.end()){
                    walls.push_back(wall);
                    cell->storeWallToNeigCell(wall);
                }else
                    cell->storeWallToNeigCell(*poswall);
            }
        }
    }

private:
    size_t sizeh;
    size_t sizev;
    vector<SpCell> cells;
    vector<SpWall> walls;
};

