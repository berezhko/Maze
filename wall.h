#ifndef WALL_H
#define WALL_H

#include "cell.h"


class Wall
{
public:
    Wall(Cell w1, Cell w2);

    void breakWall();
    bool isExist() const;
    void printWall() const;
    friend bool operator==(const Wall& lhs, const Wall& rhs);
    friend bool operator!=(const Wall& lhs, const Wall& rhs);

private:
    pair<Cell, Cell> wall;
    bool exist;
};

#endif
