#include <memory>
#include <string>

#include <gtest/gtest.h>

#include "LispExpression/ObjectStorage.hpp"
#include "LispExpression/TypeSystem/StringObject.hpp"
#include "LispExpression/ObjectStorageException.hpp"

namespace nastya::lisp {

TEST(ObjectStorageTest, testStorage)
{
    std::string test_case = "Dummy string";
    std::unique_ptr<IObject> object(dynamic_cast<typesystem::StringObject*>(
        new typesystem::StringObject(test_case)));
    ObjectStorage storage(std::move(object));
    EXPECT_EQ(storage.getType(), ObjectType::String);
    EXPECT_EQ(storage.getRawObject().getType(), ObjectType::String);
    EXPECT_EQ(dynamic_cast<typesystem::StringObject&>(storage.getRawObject())
                  .getValue(),
              test_case);
}

TEST(ObjectStorageTest, testNotinitializedStorage) {
    ObjectStorage storage;
    EXPECT_THROW(storage.getRawObject(), ObjectStorageException);
    EXPECT_THROW(storage.getType(), ObjectStorageException);
    EXPECT_THROW(storage.toString(), ObjectStorageException);
}

}  // namespace nastya::lisp
