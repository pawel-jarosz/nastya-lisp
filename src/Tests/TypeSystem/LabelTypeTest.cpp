//
// Created by caedus on 20.02.2021.
//

#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "TypeSystem/Types/LabelObject.hpp"

namespace nastya::typesystem {

TEST(LabelTypeTest, testConstructor)
{
    std::string test_case = "dummy_label";
    LabelObject object(test_case);
    EXPECT_EQ(object.getValue(), test_case);
    EXPECT_EQ(object.getType(), ObjectType::Label);
    EXPECT_EQ(object.info(), "Label => " + test_case);
    std::unique_ptr<LabelObject> cloned(dynamic_cast<LabelObject*>(object.clone()));
    EXPECT_EQ(object.getType(), cloned->getType());
    EXPECT_EQ(object.getValue(), cloned->getValue());
    EXPECT_FALSE(object.isComparable());
}

}
