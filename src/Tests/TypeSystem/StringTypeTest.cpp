//
// Created by caedus on 20.02.2021.
//

#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "TypeSystem/Types/NumberObject.hpp"
#include "TypeSystem/Types/StringObject.hpp"
#include "TypeSystem/Types/TypeSystemError.hpp"

namespace nastya::typesystem {

TEST(StringTypeTest, testStringObject)
{
    std::string test_case = "dummy string";
    StringObject object(test_case);
    EXPECT_EQ(object.getValue(), test_case);
    EXPECT_EQ(object.getType(), ObjectType::String);
    EXPECT_EQ(object.info(), "String => \"" + test_case + "\"");
    std::unique_ptr<StringObject> cloned(dynamic_cast<StringObject*>(object.clone()));
    EXPECT_EQ(object.getType(), cloned->getType());
    EXPECT_EQ(object.getValue(), cloned->getValue());
    EXPECT_TRUE(object.isComparable());
}

TEST(StringTypeTest, testStringCompare)
{
    std::string low = "a";
    std::string middle = "b";
    StringObject object(middle);
    NumberObject rhs(2);
    EXPECT_THROW(object.compare(rhs), TypeSystemError);
    StringObject low_object(low);
    StringObject middle_object(middle);
    EXPECT_EQ(low_object.compare(middle_object), -1);
    EXPECT_EQ(object.compare(middle_object), 0);
    EXPECT_EQ(middle_object.compare(low_object), 1);
}

}  // namespace nastya::typesystem
