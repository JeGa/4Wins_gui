#ifndef CELLTEST_H
#define CELLTEST_H

#include <boost/test/unit_test.hpp>

#include "impl/Cell.h"

namespace data
{

    struct CellTest
    {
            data::Cell cell;
            data::Cell cell_default;

            CellTest() : cell(PLAYER1) {}
    };

}

#endif // CELLTEST_H
