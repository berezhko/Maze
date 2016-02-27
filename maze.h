#include <iostream>
#include <memory>
#include <vector>
#include <list>

#include "wall.h"
#include "cell.h"

using namespace std;


class Maze
{
public:
    typedef shared_ptr<Cell> SpCell;

    explicit Maze(size_t s): size(s)
    {
        makeCells();
        makeWalls();
    }

    void printCells()
    {
        for(auto& c: cells)
            c->printNeighbor();
    }
    void printWalls()
    {
        for(auto& wall: walls){
            if (wall.isExist()){
                wall.printWall();
                cout << endl;
            }
        }
    }
    void makeMaze()
    {
        list<SpCell> steck;
        steck.push_back(cells[0]);
        steck.back()->toVisit();
        while (!steck.empty()){
            SpCell cell = steck.back();
            if (cell->existNeighborNotVisit()){
                SpCell randomcell {cell->getNeighborNotVisit()};
                randomcell->toVisit();
                steck.push_back(randomcell);
                Wall wall = Wall(*cell, *randomcell);
                for (auto& w: walls)
                    if (w == wall){
                        w.breakWall();
                        break;
                    }
            }else{
                steck.pop_back();
            }
        }
    }
    void drawMaze()
    {
        cout << "+";
        for (size_t i = 0; i < size; i++)
            cout << "--+";
        cout << endl;
        for (auto& cell: cells){
            if ((cell->getId() % size == 0) && (cell->getId() != size*size)){
                cout << "  |"<< endl << "+";
                size_t id = cell->getId() - size;
                for (; id < cell->getId(); id++){
                    Wall wall = Wall( *(cells[id]), *(cells[id+size]) );
                    if( ! wallBreaked(wall) )
                        cout << "--+";
                    else
                        cout << "  +";
                }
                cout << endl;
            }else if (cell->getId() != size*size){
                if (cell->getId() % size == 1)
                    cout << "|";
                cout << "  ";
                Wall wall = Wall( *cell, *(cells[cell->getId()]) );
                if( ! wallBreaked(wall) )
                    cout << "|";
                else
                    cout << " ";
            }
        }
        cout << "  |" << endl << "+";
        for (size_t i = 0; i < size; i++)
            cout << "--+";
        cout << endl;
    }
private:
    Maze(): size(0) {}

    vector<SpCell> findNeighborCell(size_t id)
    {
        size_t line = ((id-1)/size) + 1;
        vector<SpCell> nb;

        if (id + size <= size*size)
            nb.push_back( cells[id+size - 1] );
        if (id - size >= 1 && id - size <= size*size)
            nb.push_back( cells[id-size -1] );
        if (id + 1 <= line*size)
            nb.push_back( cells[id+1 - 1] );
        if (id - 1 >= (line-1)*size+1)
            nb.push_back( cells[id-1 -1] );

        return nb;
    }
    void makeCells()
    {
        for (size_t id = 1; id <= size*size; id++)
            cells.push_back(SpCell {new Cell(id)});

        for (auto& cell: cells){
            vector<SpCell> nb = findNeighborCell(cell->getId());
            cell->storeNeighborCell(nb);
        }
    }
    bool wallExist(const Wall& w)
    {
        for (auto& wall: walls)
            if (wall == w)
                return true;
        return false;
    }
    bool wallBreaked(const Wall& w)
    {
        for (auto& wall: walls)
            if (wall == w)
                if (wall.isExist())
                    return false;
        return true;
    }
    void makeWalls()
    {
        for (auto& cell: cells){
            vector<SpCell> nb =  findNeighborCell(cell->getId());

            for (auto& nbcell: nb){
                Wall wall = Wall(*nbcell, *cell);
                if (!wallExist(wall))
                    walls.push_back(wall);
            }
        }
    }

    size_t size;
    vector<SpCell> cells;
    vector<Wall> walls;
};

