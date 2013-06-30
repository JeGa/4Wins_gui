#ifndef FIELDTEST_H
#define FIELDTEST_H

#include <boost/test/unit_test.hpp>

#include "IField.h"
#include "GameFactory.h"

namespace data
{

    struct FieldTest
    {
            IField *field;
            IField *field_default;
            controller::GameFactory f;

            FieldTest()
            {
                field = f.getField(9, 10);
                field_default = f.getDefaultField();
            }

            ~FieldTest()
            {
                delete field;
                delete field_default;
            }
    };

}

#endif // FIELDTEST_H
