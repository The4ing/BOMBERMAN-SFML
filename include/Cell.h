#include "GameObject.h"

class Cell {
public:
    GameObject* content;
    bool isWalkable;
    bool isExplodable;

    Cell() : content(nullptr), isWalkable(true), isExplodable(false) {}

    ~Cell() { delete content; }
};
