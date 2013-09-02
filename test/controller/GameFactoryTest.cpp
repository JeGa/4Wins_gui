#include "GameFactoryTest.h"

#include <iostream>

namespace controller
{

	BOOST_AUTO_TEST_SUITE(GameFactoryTestSuite)
	
    BOOST_FIXTURE_TEST_CASE(testInit, GameFactoryTest)
    {
        std::string strraw("");
        std::string strfunc("");

        for (int j = 0; j < field->getHeight(); j++) {
            for (int i = 0; i < field->getWidth(); i++) {
                std::string cellString;

                if (field->getCellStatus(i, j) == PLAYER1)
                    cellString = PLAYER1_CHAR;
                else if (field->getCellStatus(i, j) == PLAYER2)
                    cellString = PLAYER2_CHAR;
                else
                    cellString = NOTSET_CHAR;

                strraw.append(cellString);
            }
            strraw.append("\n");
        }

        strfunc = field->toString();

        std::cout << std::endl << strraw << std::endl << strfunc;
        BOOST_CHECK(!strraw.compare(strfunc));
    }
	
	BOOST_AUTO_TEST_SUITE_END()

}
