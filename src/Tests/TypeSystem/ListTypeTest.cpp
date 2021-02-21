//
// Created by caedus on 20.02.2021.
//

#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "TypeSystem/Types/ListObject.hpp"
#include "Parser/Testing/ListBuilder.hpp"

namespace nastya::typesystem {

TEST(ListTypeTest, testConstructor)
{
    ListObject list;
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_EQ(list.toString(), "()");
    EXPECT_EQ(list.info(), "List => ()");
    parser::testing::ListBuilder builder;
    auto arg = builder.addLabel("abc").addString("demo").openList()
        .addNumber(1).addNumber(3).closeList().build();
    auto complex_list = dynamic_cast<ListObject&>(arg.getRawObject());
    EXPECT_EQ(complex_list.getSize(), 3);
    EXPECT_EQ(complex_list.toString(), "(abc \"demo\" (1 3))");
}

}
