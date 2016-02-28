#ifndef CELL_H
#define CELL_H

#include <memory>
#include <vector>

using namespace std;

class Wall;

class Cell
{
public:
    typedef weak_ptr<Cell> WpCell;
    typedef shared_ptr<Cell> SpCell;
    typedef weak_ptr<Wall> WpWall;
    typedef shared_ptr<Wall> SpWall;

    Cell(size_t i);

    Cell(const Cell& cell);

    bool isVisit() const;
    void toVisit();
    size_t getId() const;
    void storeNeighborCells(const vector<SpCell>& nb);
    void storeWallToNeigCell(const SpWall& w);
    WpCell getNeighborNotVisit();
    bool existNeighborNotVisit() const;
    void printNeighbor() const;
    void printNeighborNotVisit() const;
    void printWallToNeigCell() const;
    bool breakWall(const SpCell& nb);
    SpWall getWall(const SpCell& nb);

    friend bool operator==(const Cell& lhs, const Cell& rhs);
    friend bool operator!=(const Cell& lhs, const Cell& rhs);

protected:
    Cell();

private:
    size_t id;
    bool visit;
    vector<WpCell> neighbor;
    vector<WpWall> walls;
};

#endif
