#ifndef WALL_H
#define WALL_H

#include "cell.h"

using namespace std;

class Wall
{
public:
    Wall(Cell w1, Cell w2):
        wall(make_pair(w1, w2)),
        exist(true) {}

    void breakWall()
    {
        exist = false;
    }
    bool isExist() const
    {
        return exist;
    }
    void printWall() const
    {
        cout << "(" << wall.first.getId() << ", " << wall.second.getId() << ")";
    }
    friend bool operator==(const Wall& lhs, const Wall& rhs);
    friend bool operator!=(const Wall& lhs, const Wall& rhs);

private:
    pair<Cell, Cell> wall;
    bool exist;
};

inline bool operator==(const Wall& lhs, const Wall& rhs)
{
    return  ((lhs.wall.first == rhs.wall.first &&
              lhs.wall.second == rhs.wall.second)
            ||
             (lhs.wall.first == rhs.wall.second &&
              lhs.wall.second == rhs.wall.first));
}

inline bool operator!=(const Wall& lhs, const Wall& rhs)
{
    return !(lhs == rhs);
}

#endif
