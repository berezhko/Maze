#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <ctime>

using namespace std;


size_t getRandom(int n)
{
    static int flag;
    static std::default_random_engine dre;
    if (flag == 0)
        dre.seed(time(NULL));
    flag = 1;

    uniform_int_distribution<int> di(0, n-1);
    di(dre);

    return (size_t)di(dre);
}


class Cell
{
public:
    typedef weak_ptr<Cell> WpCell;
    typedef shared_ptr<Cell> SpCell;

    Cell(size_t i):
        id(i),
        visit(false){}

    Cell(const Cell& cell)
    {
        id = cell.getId();
        visit = cell.isVisit();
    }

    bool isVisit() const
    {
        return visit;
    }
    void toVisit()
    {
        visit = true;
    }
    size_t getId() const
    {
        return id;
    }
    void storeNeighborCell(const vector<SpCell>& nb)
    {
        for (auto& n: nb)
            neighbor.push_back(n);
    }
    WpCell getNeighborNotVisit()
    {
        vector<WpCell> tmp;
        for (auto& nb: neighbor)
            if (nb.lock()->isVisit() == false)
                tmp.push_back(nb);

        size_t rnd = getRandom(tmp.size());
        return tmp[rnd];
    }
    bool existNeighborNotVisit()
    {
        for (auto& nb: neighbor)
            if (nb.lock()->isVisit() == false)
                return true;
        return false;
    }
    void printNeighbor()
    {
        cout << getId() << ": ";
        for (auto& nb: neighbor)
            cout << nb.lock()->getId() << " ";
        cout << endl;
    }
    void printNeighborNotVisit()
    {
        cout << getId() << ": ";
        for (auto& nb: neighbor)
            if (nb.lock()->isVisit() == false)
                cout << nb.lock()->getId() << " ";
    }

    friend bool operator==(const Cell& lhs, const Cell& rhs);
    friend bool operator!=(const Cell& lhs, const Cell& rhs);
private:
    Cell(){}

    size_t id;
    bool visit;
    vector<WpCell> neighbor;
};

inline bool operator==(const Cell& lhs, const Cell& rhs)
{
    return  (lhs.id == rhs.id);
}

inline bool operator!=(const Cell& lhs, const Cell& rhs)
{
    return !(lhs == rhs);
}

#endif
