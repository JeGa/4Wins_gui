#include "PlayerTest.h"

#include "impl/Player.h"
#include <fstream>

namespace data
{
	
	BOOST_FIXTURE_TEST_SUITE(PlayerTestSuite, PlayerTest)

    BOOST_AUTO_TEST_CASE(testGet)
    {
/*        EXPECT_STREQ("Han Solo", p1.getName().c_str());


        p1.addGameStatistic(Player::WIN);
        EXPECT_EQ(1, p1.getWins());
        EXPECT_EQ(1, p1.getPlayedGames());
        p1.addGameStatistic(Player::LOOSE);
        EXPECT_EQ(1, p1.getLooses());
        EXPECT_EQ(2, p1.getPlayedGames());

        EXPECT_EQ(0.5, p1.getWinRatio());*/
    }

    BOOST_AUTO_TEST_CASE(testWriteToDisk)
    {
/*        p1.addGameStatistic(Player::WIN);
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
        EXPECT_STREQ(p1.toString().c_str(), str.c_str());*/
    }
	
	BOOST_AUTO_TEST_SUITE_END()

}
