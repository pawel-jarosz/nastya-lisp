//
// Created by caedus on 20.02.2021.
//

#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "TypeSystem/Types/BooleanObject.hpp"

namespace nastya::typesystem {

TEST(BooleanTypeTest, testConstructors)
{
    std::vector test_cases = {true, false};
    std::vector result = {"#true", "Boolean => #true", "#false", "Boolean => #false"};
    size_t i = 0;
    for (const auto& test_case : test_cases)
    {
        BooleanObject object(test_case);
        EXPECT_EQ(object.getValue(), test_case);
        EXPECT_EQ(object.getType(), ObjectType::Boolean);
        std::unique_ptr<BooleanObject> cloned(dynamic_cast<BooleanObject*>(object.clone()));
        EXPECT_EQ(object.getType(), cloned->getType());
        EXPECT_EQ(object.getValue(), cloned->getValue());
        EXPECT_EQ(object.toString(), result[i]);
        EXPECT_EQ(object.info(), result[i + 1]);
        EXPECT_FALSE(object.isComparable());
        i += 2;
    }
}

}
