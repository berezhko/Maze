#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <ctime>
#include <cassert>

#include "cell.h"
#include "wall.h"

using namespace std;

typedef weak_ptr<Cell> WpCell;
typedef shared_ptr<Cell> SpCell;
typedef weak_ptr<Wall> WpWall;
typedef shared_ptr<Wall> SpWall;


size_t getRandom(int n)
{
    static int flag;
    static std::default_random_engine dre;
    if (flag == 0)
        dre.seed(time(NULL));
    flag = 1;

    uniform_int_distribution<int> di(0, n-1);

    return (size_t)di(dre);
}

bool operator==(const Cell& lhs, const Cell& rhs)
{
    return  (lhs.id == rhs.id);
}

bool operator!=(const Cell& lhs, const Cell& rhs)
{
    return !(lhs == rhs);
}


Cell::Cell(size_t i):
    id(i),
    visit(false){}

Cell::Cell(const Cell& cell)
{
    id = cell.getId();
    visit = cell.isVisit();
}

bool Cell::isVisit() const
{
    return visit;
}

void Cell::toVisit()
{
    visit = true;
}

size_t Cell::getId() const
{
    return id;
}

void Cell::storeNeighborCells(const vector<SpCell>& nb)
{
    for (auto& n: nb)
        neighbor.push_back(n);
}

void Cell::storeWallToNeigCell(const SpWall& w)
{
    walls.push_back(w);
}

WpCell Cell::getNeighborNotVisit()
{
    vector<WpCell> tmp;
    for (auto& nb: neighbor)
        if (nb.lock()->isVisit() == false)
            tmp.push_back(nb);

    assert(tmp.size() != 0);

    size_t rnd = getRandom(tmp.size());
    return tmp[rnd];
}

bool Cell::existNeighborNotVisit() const
{
    for (auto& nb: neighbor)
        if (nb.lock()->isVisit() == false)
            return true;
    return false;
}

void Cell::printNeighbor() const
{
    cout << getId() << ": ";
    for (auto& nb: neighbor)
        cout << nb.lock()->getId() << " ";
    cout << endl;
}

void Cell::printNeighborNotVisit() const
{
    cout << getId() << ": ";
    for (auto& nb: neighbor)
        if (nb.lock()->isVisit() == false)
            cout << nb.lock()->getId() << " ";
}

void Cell::printWallToNeigCell() const
{
    cout << getId() << ": ";
    for (auto& w: walls)
        w.lock()->printWall();
    cout << endl;
}

bool Cell::breakWall(const SpCell& nb)
{
    Wall wall = Wall(*this, *nb);
    for (auto& w: walls)
        if (*(w.lock()) == wall){
            w.lock()->breakWall();
            return true;
        }
    return false;
}

SpWall Cell::getWall(const SpCell& nb)
{
    return getWall(nb->getId());
}

SpWall Cell::getWall(size_t id)
{
    for (auto& nb: neighbor){
        if (id == nb.lock()->getId()){
            Wall wall = Wall( *this, *(nb.lock()) );
            for (auto& w: walls)
                if (*(w.lock()) == wall)
                    return w.lock();
            assert(false);
        }
    }
    return nullptr;
}

