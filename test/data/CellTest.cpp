#include "CellTest.h"

namespace data
{

    BOOST_AUTO_TEST_SUITE(CellTestSuite)

    BOOST_FIXTURE_TEST_CASE(testInit, CellTest)
    {
        BOOST_CHECK_EQUAL(PLAYER1, cell.getColor());
        BOOST_CHECK_EQUAL(NOTSET, cell_default.getColor());
    }

    BOOST_FIXTURE_TEST_CASE(testSetGet, CellTest)
    {
        cell.setColor(PLAYER2);
        BOOST_CHECK_EQUAL(PLAYER2, cell.getColor());
    }

    BOOST_AUTO_TEST_SUITE_END()

}
