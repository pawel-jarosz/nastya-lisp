#include <memory>
#include <string>

#include <gtest/gtest.h>

#include "TypeSystem/Types/StringObject.hpp"
#include "TypeSystem/ObjectStorage.hpp"
#include "TypeSystem/ObjectStorageException.hpp"

namespace nastya::lisp {

TEST(ObjectStorageTest, testStorage)
{
    std::string test_case = "Dummy string";
    std::unique_ptr<typesystem::IObject> object(dynamic_cast<typesystem::StringObject*>(new typesystem::StringObject(test_case)));
    typesystem::ObjectStorage storage(std::move(object));
    EXPECT_EQ(storage.getType(), typesystem::ObjectType::String);
    EXPECT_EQ(storage.getRawObject().getType(), typesystem::ObjectType::String);
    EXPECT_EQ(dynamic_cast<typesystem::StringObject&>(storage.getRawObject()).getValue(), test_case);
}

TEST(ObjectStorageTest, testNotinitializedStorage)
{
    typesystem::ObjectStorage storage;
    EXPECT_THROW(storage.getRawObject(), typesystem::ObjectStorageException);
    EXPECT_THROW(storage.getType(), typesystem::ObjectStorageException);
    EXPECT_THROW(storage.toString(), typesystem::ObjectStorageException);
}

TEST(ObjectStorageTest, testAssignment) {
    typesystem::ObjectStorage a(std::unique_ptr<typesystem::IObject>(new typesystem::StringObject("Dummy string")));
    typesystem::ObjectStorage b(std::unique_ptr<typesystem::IObject>(new typesystem::StringObject("Short")));
    b = a;
    EXPECT_EQ(a.toString(), b.toString());
}

TEST(ObjectStorageTest, testMove) {
    const std::string value{"dummy string"};
    typesystem::ObjectStorage a(std::unique_ptr<typesystem::IObject>(new typesystem::StringObject(value)));
    typesystem::ObjectStorage b(std::unique_ptr<typesystem::IObject>(new typesystem::StringObject("Short")));
    b = std::move(a);
    auto& raw_object = b.getRawObject();
    auto string_object = dynamic_cast<typesystem::StringObject&>(raw_object);
    EXPECT_EQ(string_object.getValue(), value);
}

}  // namespace nastya::lisp
