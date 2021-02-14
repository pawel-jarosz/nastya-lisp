//
// Created by caedus on 10.01.2021.
//

#pragma once

#include "TypeSystem/Types/BooleanObject.hpp"
#include "TypeSystem/Types/LabelObject.hpp"
#include "TypeSystem/Types/LambdaObject.hpp"
#include "TypeSystem/Types/ListObject.hpp"
#include "TypeSystem/Types/NumberObject.hpp"
#include "TypeSystem/Types/StringObject.hpp"
#include "TypeSystem/ObjectStorage.hpp"

namespace nastya::utils {

struct Cast {
    static const typesystem::BooleanObject& as_boolean(const typesystem::ObjectStorage& storage, std::string msg = "");
    static const typesystem::NumberObject& as_number(const typesystem::ObjectStorage& storage, std::string msg = "");
    static const typesystem::StringObject& as_string(const typesystem::ObjectStorage& storage, std::string msg = "");
    static const typesystem::LabelObject& as_label(const typesystem::ObjectStorage& storage, std::string msg = "");
    static const typesystem::ListObject& as_list(const typesystem::ObjectStorage& storage, std::string msg = "");
    static const typesystem::LambdaObject& as_lambda(const typesystem::ObjectStorage& storage, std::string msg = "");
};

}
