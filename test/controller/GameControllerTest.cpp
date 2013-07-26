#include "GameControllerTest.h"

#include <iostream>

namespace controller
{
	
	BOOST_AUTO_TEST_SUITE(GameControllerTestSuite)

    BOOST_FIXTURE_TEST_CASE(testGame, GameControllerTest)
    {
        gc->playGame(game);

        BOOST_CHECK_EQUAL(p1, gc->onTurn());
        BOOST_CHECK(gc->toggleTurn(0, 0));
        BOOST_CHECK_EQUAL(p2, gc->onTurn());
    }

    BOOST_FIXTURE_TEST_CASE(testAlgorithmCorrect, GameControllerTest)
    {
        gc->playGame(game);
        // w = 5, h = 8

        // 4 left up
        BOOST_CHECK(gc->toggleTurn(0, 0)); // 1 p1
        BOOST_CHECK_EQUAL(p2, gc->onTurn());
        BOOST_CHECK(gc->toggleTurn(1, 0));
        BOOST_CHECK(gc->toggleTurn(0, 1)); // 2 p1
        BOOST_CHECK(gc->toggleTurn(2, 0));
        BOOST_CHECK(gc->toggleTurn(0, 2)); // 3 p1
        BOOST_CHECK(gc->toggleTurn(3, 0));
        BOOST_CHECK(gc->toggleTurn(0, 3)); // 4 p1

        BOOST_CHECK(!gc->getGame()->isRunning());
        BOOST_CHECK_EQUAL(p1, gc->getGame()->getWinner());
    }


    BOOST_FIXTURE_TEST_CASE(testAlgorithmFailure, GameControllerTest)
    {
        gc->playGame(game);

        BOOST_CHECK(gc->toggleTurn(0, 0));
        BOOST_CHECK(!gc->toggleTurn(0, 0));

        BOOST_CHECK(!gc->toggleTurn(0, 4));
    }

    BOOST_FIXTURE_TEST_CASE(testSetCells, GameControllerTest)
    {
        // Only for visual

        gc->playGame(game);

        gc->toggleTurn(0, 0);
        gc->toggleTurn(1, 0);
        gc->toggleTurn(2, 0);
        gc->toggleTurn(3, 0);
        gc->toggleTurn(4, 0);

        gc->toggleTurn(0, 0);
        gc->toggleTurn(0, 1);
        gc->toggleTurn(0, 2);
        gc->toggleTurn(0, 3);
        gc->toggleTurn(0, 4);
        gc->toggleTurn(0, 5);

        std::cout << std::endl << game->toString() << std::endl;
    }
	
	BOOST_AUTO_TEST_SUITE_END()
	
}
