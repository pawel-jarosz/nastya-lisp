//
// Created by caedus on 22.12.2020.
//

#include "VirtualMachine//Machine.hpp"
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "LispExpression/TypeSystem/LabelObject.hpp"
#include <algorithm>
#include <iostream>

namespace nastya::vm {

Machine::Machine(const modules::ModuleRegistry& registry) : m_modules{registry} {

}

lisp::ObjectStorage Machine::run(const lisp::ObjectStorage& list) {
    if (list.getType() != lisp::ObjectType::List) {
        return list;
    }
    auto raw_object = dynamic_cast<lisp::typesystem::ListObject&>(list.getRawObject());
    auto content = raw_object.getContent();
    auto label = dynamic_cast<lisp::typesystem::LabelObject&>(content[0].getRawObject());
    std::vector<lisp::ObjectStorage> arguments;
    if (label.getValue() == "Quote") {
        arguments = std::vector(++content.begin(), content.end());
    }
    else {
        std::for_each(++content.begin(), content.end(), [&](const auto& obj){
          arguments.emplace_back(run(obj));
        });
    }
    std::unique_ptr<lisp::typesystem::ListObject> obj(new lisp::typesystem::ListObject(arguments));
    lisp::ObjectStorage argument(std::move(obj));
    return m_modules.getFunction(label.getValue()).evaluate(*this, argument);
}

}
