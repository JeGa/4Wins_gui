#include "GameFactoryTest.h"

#include <iostream>

namespace controller
{

	BOOST_FIXTURE_TEST_SUITE(GameFactoryTestSuite, GameFactoryTest)
	
    BOOST_AUTO_TEST_CASE(testInit)
    {
/*        std::string strraw("");
        std::string strfunc("");

        for (int j = 0; j < field->getHeight(); j++) {
            for (int i = 0; i < field->getWidth(); i++) {
                strraw.append(field->getCell(i, j)->toString());
            }
            strraw.append("\n");
        }

        strfunc = field->toString();

        std::cout << strraw << std::endl << strfunc;
        EXPECT_STREQ(strraw.c_str(), strfunc.c_str());*/
    }
	
	BOOST_AUTO_TEST_SUITE_END()

}
