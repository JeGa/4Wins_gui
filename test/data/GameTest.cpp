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
	
    BOOST_FIXTURE_TEST_CASE(testKey, GameTest)
    {
        // Key has to be unique
        Game *tmp = new Game(f.getDefaultField(), p1, p2, p1);
        
        BOOST_CHECK_NE(game->getKey(), tmp->getKey());
        
        delete tmp;
    }
    
    BOOST_FIXTURE_TEST_CASE(testRunning, GameTest)
    {
        game->setRunning(false);
        BOOST_CHECK(!game->isRunning());
    }

	BOOST_AUTO_TEST_SUITE_END()

}
