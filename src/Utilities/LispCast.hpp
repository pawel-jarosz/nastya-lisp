//
// Created by caedus on 10.01.2021.
//

#pragma once

#include "LispExpression/ObjectStorage.hpp"
#include "LispExpression/TypeSystem/BooleanObject.hpp"
#include "LispExpression/TypeSystem/StringObject.hpp"
#include "LispExpression/TypeSystem/NumberObject.hpp"
#include "LispExpression/TypeSystem/LabelObject.hpp"
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "LispExpression/TypeSystem/LambdaObject.hpp"

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
