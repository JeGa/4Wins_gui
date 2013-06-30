#include "FieldTest.h"
#include "GameFactory.h"

namespace data
{
	
	BOOST_FIXTURE_TEST_SUITE(FieldTestSuite, FieldTest)

    BOOST_AUTO_TEST_CASE(testInit)
    {
/*        EXPECT_EQ(controller::GameFactory::DEFAULT_WIDTH, field_default->getWidth());
        EXPECT_EQ(controller::GameFactory::DEFAULT_HEIGHT, field_default->getHeight());
        EXPECT_EQ(9, field->getWidth());
        EXPECT_EQ(10, field->getHeight());*/
    }

    BOOST_AUTO_TEST_CASE(testSetGet)
    {
//        field_default->setCellStatus(0, 0, PLAYER1);
        /*EXPECT_EQ(PLAYER1, field->getCell(0, 0)->getColor());

        EXPECT_ANY_THROW(field->setCell(-1, 0, PLAYER1));
        EXPECT_ANY_THROW(field->setCell(0, 100, PLAYER1));*/
    }
	
	BOOST_AUTO_TEST_SUITE_END()

}
