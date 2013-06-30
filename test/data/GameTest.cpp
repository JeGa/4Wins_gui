#include "GameTest.h"

namespace data
{
	
	BOOST_FIXTURE_TEST_SUITE(GameTestSuite, GameTest)

    BOOST_AUTO_TEST_CASE(testGetPlayer)
    {
/*      EXPECT_EQ(p1, game->getPlayer1());
        EXPECT_EQ(p2, game->getPlayer2());*/
    }

    BOOST_AUTO_TEST_CASE(testGetSetCell)
    {
/*        game->setCellStatus(0, 0, p1);
        EXPECT_EQ(p1, game->getCellStatus(0, 0));*/
    }

    BOOST_AUTO_TEST_CASE(testOnTurn)
    {
//        EXPECT_EQ(p1, game->onTurn());
    }
	
	BOOST_AUTO_TEST_SUITE_END()

}
