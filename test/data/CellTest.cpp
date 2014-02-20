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

    BOOST_FIXTURE_TEST_CASE(testInternals, CellTest)
    {
        cell.setColor(PLAYER2);

        Cell tmp {cell}; // Copy ctor
        BOOST_CHECK_EQUAL(PLAYER2, tmp.getColor());

        cell.setColor(PLAYER1);
        tmp = cell;
        BOOST_CHECK_EQUAL(PLAYER1, tmp.getColor());
    }

    BOOST_AUTO_TEST_SUITE_END()

}
