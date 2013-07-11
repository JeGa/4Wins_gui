#include "FieldTest.h"

#include "GameFactory.h"
#include <stdexcept>

namespace data
{
	
	BOOST_AUTO_TEST_SUITE(FieldTestSuite)

    BOOST_FIXTURE_TEST_CASE(testInit, FieldTest)
    {
        BOOST_CHECK_EQUAL(controller::GameFactory::DEFAULT_WIDTH, field_default->getWidth());
        BOOST_CHECK_EQUAL(controller::GameFactory::DEFAULT_HEIGHT, field_default->getHeight());
        BOOST_CHECK_EQUAL(9, field->getWidth());
        BOOST_CHECK_EQUAL(10, field->getHeight());
    }

    BOOST_FIXTURE_TEST_CASE(testSetGet, FieldTest)
    {
        BOOST_CHECK_NO_THROW(field_default->setCellStatus(0, 0, PLAYER1));
        BOOST_CHECK_EQUAL(PLAYER1, field_default->getCell(0, 0)->getColor());

        BOOST_CHECK_THROW(field->setCellStatus(-1, 0, PLAYER1),
            std::out_of_range);
        BOOST_CHECK_THROW(field->setCellStatus(0, 100, PLAYER1),
            std::out_of_range);
    }
	
	BOOST_AUTO_TEST_SUITE_END()

}
