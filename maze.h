#include <memory>
#include <vector>

#include "wall.h"
#include "cell.h"

using std::vector;

size_t getRandom(int n);

class Iterator;

class Maze
{
public:
    typedef weak_ptr<Cell> WpCell;
    typedef shared_ptr<Cell> SpCell;
    typedef weak_ptr<Wall> WpWall;
    typedef shared_ptr<Wall> SpWall;

    explicit Maze(size_t s);
    Maze(size_t v, size_t h);

    size_t countCells() const;
    SpCell getCell(size_t id) const;
    Iterator* createIterator();
    pair<size_t, size_t> getDimension() const;

protected:
    Maze();
    //Maze(const Maze&);
    //Maze& operator=(const Maze&);

private:
    void makeMaze();
    vector<SpCell> findNeighborCell(size_t id);
    void makeCells();
    void makeWalls();

private:
    size_t sizev;
    size_t sizeh;
    vector<SpCell> cells;
    vector<SpWall> walls;
};


class Iterator
{
public:
    typedef shared_ptr<Cell> SpCell;

    Iterator(Maze *m);

    void begin();
    void operator++();
    void operator++(int);
    bool end();
    SpCell currentCell();

private:
    Maze *maze;
    size_t id;
};


class Iterator_ptr
{
public:
    Iterator_ptr(Iterator *i);
    ~Iterator_ptr();

    Iterator* operator->();
    Iterator operator*();
    void operator++();
    void operator++(int);
protected:
    Iterator_ptr(const Iterator_ptr&);
    Iterator_ptr& operator=(const Iterator_ptr&);

private:
    Iterator *_i;
};
