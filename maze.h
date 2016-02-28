#include <memory>
#include <vector>

#include "wall.h"
#include "cell.h"

using std::vector;

size_t getRandom(int n);


class Maze
{
public:
    typedef weak_ptr<Cell> WpCell;
    typedef shared_ptr<Cell> SpCell;
    typedef weak_ptr<Wall> WpWall;
    typedef shared_ptr<Wall> SpWall;

    explicit Maze(size_t s);
    Maze(size_t v, size_t h);

    void printCells();
    void printWalls();
    void drawMaze();

protected:
    Maze();
    Maze(const Maze&);
    Maze& operator=(const Maze&);

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

