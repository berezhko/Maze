#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <cassert>

#include "maze.h"

using namespace std;

typedef weak_ptr<Cell> WpCell;
typedef shared_ptr<Cell> SpCell;
typedef weak_ptr<Wall> WpWall;
typedef shared_ptr<Wall> SpWall;


Maze::Maze(size_t s): Maze(s, s) { }
Maze::Maze(size_t v, size_t h): sizev(v), sizeh(h)
{
    makeCells();
    makeWalls();
    makeMaze();
}

size_t Maze::countCells() const
{
    return sizev*sizeh;
}

SpCell Maze::getCell(size_t i) const
{
    assert(i <= countCells());
    return cells[i];
}

Iterator* Maze::createIterator()
{
    return new Iterator(this);
}

pair<size_t, size_t> Maze::getDimension() const
{
    return make_pair(sizev, sizeh);
}

void Maze::makeMaze()
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

vector<SpCell> Maze::findNeighborCell(size_t id)
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

void Maze::makeCells()
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

void Maze::makeWalls()
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


Iterator::Iterator(Maze *m): maze(m), id(0) {}

void Iterator::first()
{
    id = 0;
}

void Iterator::next()
{
    id++;
}

bool Iterator::isDone()
{
    return id >= maze->countCells();
}

SpCell Iterator::currentCell()
{
    return maze->getCell(id);
}

Iterator_ptr::Iterator_ptr(Iterator *i): _i(i) {}
Iterator_ptr::~Iterator_ptr()
{
    //cout << "Iterator destroy" << endl;
    delete _i;
}

Iterator* Iterator_ptr::operator->() {return _i;}
Iterator Iterator_ptr::operator*() {return *_i;}

