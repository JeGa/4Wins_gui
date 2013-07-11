#include "GameTest.h"

namespace data
{
	
	BOOST_AUTO_TEST_SUITE(GameTestSuite)

    BOOST_FIXTURE_TEST_CASE(testGetPlayer, GameTest)
    {
        BOOST_CHECK_EQUAL(p1, game->getPlayer1());
        BOOST_CHECK_EQUAL(p2, game->getPlayer2());
    }

    BOOST_FIXTURE_TEST_CASE(testGetSetCell, GameTest)
    {
        game->setCellStatus(0, 0, p1);
        BOOST_CHECK_EQUAL(p1, game->getCellStatus(0, 0));
    }

    BOOST_FIXTURE_TEST_CASE(testOnTurn, GameTest)
    {
        BOOST_CHECK_EQUAL(p1, game->onTurn());
    }
	
	BOOST_AUTO_TEST_SUITE_END()

}
