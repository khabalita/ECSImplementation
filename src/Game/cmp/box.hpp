#pragma once
#include <cstdint>
#include <vector>

// Patron Composite
struct BoundingBox_t {
    //manejo las cuatro esquinas de mi caja de colision
    uint32_t xLeft { 0 }, xRight { 0 };
    uint32_t yUp { 0 }, yDown { 0 };
};

struct BoundingBoxNode_t {
    BoundingBox_t box;
    std::vector<BoundingBoxNode_t> childs;
};