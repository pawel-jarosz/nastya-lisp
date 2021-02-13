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
    static const lisp::typesystem::BooleanObject& as_boolean(const lisp::ObjectStorage& storage, std::string msg = "");
    static const lisp::typesystem::NumberObject& as_number(const lisp::ObjectStorage& storage, std::string msg = "");
    static const lisp::typesystem::StringObject& as_string(const lisp::ObjectStorage& storage, std::string msg = "");
    static const lisp::typesystem::LabelObject& as_label(const lisp::ObjectStorage& storage, std::string msg = "");
    static const lisp::typesystem::ListObject& as_list(const lisp::ObjectStorage& storage, std::string msg = "");
    static const lisp::typesystem::LambdaObject& as_lambda(const lisp::ObjectStorage& storage, std::string msg = "");
};

}
