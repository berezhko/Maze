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
        cout << "+";
        for (size_t i = 0; i < sizeh; i++)
            cout << "--+";
        cout << endl;
        for (auto& cell: cells){
            if ((cell->getId() % sizeh == 0) && (cell->getId() != sizeh*sizev)){
                cout << "  |"<< endl << "+";
                size_t id = cell->getId() - sizeh;
                for (; id < cell->getId(); id++){
                    SpWall wall { new Wall( *(cells[id]), *(cells[id+sizeh]) ) };
                    auto poswall = find_if(walls.begin(), walls.end(), [&wall](SpWall w){return *w == *wall;});
                    assert(poswall != walls.end());
                    if( (*poswall)->isExist() )
                        cout << "--+";
                    else
                        cout << "  +";
                }
                cout << endl;
            }else if (cell->getId() != sizeh*sizev){
                if (cell->getId() % sizeh == 1)
                    (cell->getId() == 1) ? cout << " " : cout << "|";
                cout << "  ";
                SpWall wall { new Wall( *cell, *(cells[cell->getId()]) ) };
                auto poswall = find_if(walls.begin(), walls.end(), [&wall](SpWall w){return *w == *wall;});
                assert(poswall != walls.end());
                if( (*poswall)->isExist() )
                    cout << "|";
                else
                    cout << " ";
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
                steck.push_back(randomcell);
                Wall wall = Wall(*cell, *randomcell);
                for (auto& w: walls)
                    if (*w == wall){
                        w->breakWall();
                        break;
                    }
            }else{
                steck.pop_back();
            }
        }
    }
    vector<SpCell> findNeighborCell(size_t id)
    {
        size_t line = ((id-1)/sizeh) + 1;
        vector<SpCell> nb;

        if (id + sizeh <= sizeh*sizev)
            nb.push_back( cells[id+sizeh - 1] );
        if (id - sizeh >= 1 && id - sizeh <= sizeh*sizev)
            nb.push_back( cells[id-sizeh - 1] );
        if (id + 1 <= line*sizeh)
            nb.push_back( cells[id+1 - 1] );
        if (id - 1 >= (line-1)*sizeh+1)
            nb.push_back( cells[id-1 -1] );

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
            cell->storeNeighborCell(nb);
            // TODO makeWall() do this
        }
    }
    void makeWalls()
    {
        for (auto& cell: cells){
            vector<SpCell> nb =  findNeighborCell(cell->getId());

            for (auto& nbcell: nb){
                SpWall wall {new Wall(*nbcell, *cell), [](Wall *w) {
                                    //w->printWall();
                                    delete w;
                }};
                auto poswall = find_if(walls.begin(), walls.end(),
                                    [&wall](SpWall w){return *w == *wall;});
                if (poswall == walls.end())
                    walls.push_back(wall);
                // TODO save to me as weak_ptr<Wall>
                // cell->storeWallToNeigCell(wall)
            }
        }
    }

private:
    size_t sizeh;
    size_t sizev;
    vector<SpCell> cells;
    vector<SpWall> walls;
};

