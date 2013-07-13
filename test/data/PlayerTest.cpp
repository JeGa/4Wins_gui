#include "PlayerTest.h"

#include "impl/Player.h"
#include <fstream>

namespace data
{
	
	BOOST_AUTO_TEST_SUITE(PlayerTestSuite)

    BOOST_FIXTURE_TEST_CASE(testGet, PlayerTest)
    {
        BOOST_CHECK(!p1.getName().compare("Han Solo"));

        p1.addGameStatistic(Player::WIN);
        BOOST_CHECK_EQUAL(1, p1.getWins());
        BOOST_CHECK_EQUAL(1, p1.getPlayedGames());
        p1.addGameStatistic(Player::LOOSE);
        BOOST_CHECK_EQUAL(1, p1.getLooses());
        BOOST_CHECK_EQUAL(2, p1.getPlayedGames());

        BOOST_CHECK_EQUAL(0.5, p1.getWinRatio());
    }

    BOOST_FIXTURE_TEST_CASE(testWriteToDisk, PlayerTest)
    {
        p1.addGameStatistic(Player::WIN);
        p1.addGameStatistic(Player::LOOSE);
        p1.writeToDisk();

        std::ifstream in((p1.getName() + ".player").c_str(), std::ios::binary);
        std::string str;

        while(in) {
            std::string tmp;
            getline(in, tmp);
            if (in)
                str += tmp + "\n";
        }

        in.close();
        BOOST_CHECK(!p1.toString().compare(str));
    }
    
    BOOST_FIXTURE_TEST_CASE(testKey, PlayerTest)
    {
        // Key has to be unique
        Player tmp("Tmp", "");
        BOOST_CHECK_NE(p1.getKey(), tmp.getKey());
    }
	
	BOOST_AUTO_TEST_SUITE_END()

}
