#include <memory>
#include <string>

#include <gtest/gtest.h>

#include "LispExpression/ObjectStorage.hpp"
#include "LispExpression/ObjectStorageException.hpp"
#include "LispExpression/TypeSystem/StringObject.hpp"

namespace nastya::lisp {

TEST(ObjectStorageTest, testStorage)
{
    std::string test_case = "Dummy string";
    std::unique_ptr<IObject> object(dynamic_cast<typesystem::StringObject*>(new typesystem::StringObject(test_case)));
    ObjectStorage storage(std::move(object));
    EXPECT_EQ(storage.getType(), ObjectType::String);
    EXPECT_EQ(storage.getRawObject().getType(), ObjectType::String);
    EXPECT_EQ(dynamic_cast<typesystem::StringObject&>(storage.getRawObject()).getValue(), test_case);
}

TEST(ObjectStorageTest, testNotinitializedStorage)
{
    ObjectStorage storage;
    EXPECT_THROW(storage.getRawObject(), ObjectStorageException);
    EXPECT_THROW(storage.getType(), ObjectStorageException);
    EXPECT_THROW(storage.toString(), ObjectStorageException);
}

TEST(ObjectStorageTest, testAssignment) {
    ObjectStorage a(std::unique_ptr<IObject>(new typesystem::StringObject("Dummy string")));
    ObjectStorage b(std::unique_ptr<IObject>(new typesystem::StringObject("Short")));
    b = a;
    EXPECT_EQ(a.toString(), b.toString());
}

TEST(ObjectStorageTest, testMove) {
    const std::string value{"dummy string"};
    ObjectStorage a(std::unique_ptr<IObject>(new typesystem::StringObject(value)));
    ObjectStorage b(std::unique_ptr<IObject>(new typesystem::StringObject("Short")));
    b = std::move(a);
    auto& raw_object = b.getRawObject();
    auto string_object = dynamic_cast<typesystem::StringObject&>(raw_object);
    EXPECT_EQ(string_object.getValue(), value);
}

}  // namespace nastya::lisp
