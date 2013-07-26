#include "GameManagerTest.h"

namespace controller
{
    
    BOOST_AUTO_TEST_SUITE(GameManagerTestSuite)

    
    BOOST_FIXTURE_TEST_CASE(testPlay, GameManagerTest)
    {
        BOOST_CHECK_EQUAL(game, manager->getActiveGame());
        
        // Maps: 2 Player, 1 Game
                
        // New game set active
        IGame *tmp = f.getGameDefault(p1, p2, p1);
        manager->newGame(tmp);
        BOOST_CHECK(manager->getActiveGame() == tmp);

        // 2 Player 2 Games
        
        // 2 Player 1 Game
        manager->deleteGame(tmp);
        BOOST_CHECK(manager->getActiveGame() == nullptr);
    }
    
    BOOST_FIXTURE_TEST_CASE(testInput, GameManagerTest)
    {
        manager->input(0, 0);
        
        BOOST_CHECK_EQUAL(p1, manager->getActiveGame()->getCellStatus(0, game->getHeight()-1));
    }
    
    BOOST_AUTO_TEST_SUITE_END()

}

