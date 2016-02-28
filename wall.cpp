#include <iostream>

#include "wall.h"
#include "cell.h"

using namespace std;


Wall::Wall(Cell w1, Cell w2):
    wall(make_pair(w1, w2)),
    exist(true) {}

void Wall::breakWall()
{
    exist = false;
}

bool Wall::isExist() const
{
    return exist;
}

void Wall::printWall() const
{
    cout    << "(" << wall.first.getId()
            << "," << wall.second.getId() << ")";
}

bool operator==(const Wall& lhs, const Wall& rhs)
{
    return  ((lhs.wall.first == rhs.wall.first &&
              lhs.wall.second == rhs.wall.second)
            ||
             (lhs.wall.first == rhs.wall.second &&
              lhs.wall.second == rhs.wall.first));
}

bool operator!=(const Wall& lhs, const Wall& rhs)
{
    return !(lhs == rhs);
}


