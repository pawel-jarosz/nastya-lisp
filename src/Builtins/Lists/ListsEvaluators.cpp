//
// Created by caedus on 21.12.2020.
//

#include "ListsEvaluators.hpp"

#include "LispExpression/TypeSystem/ListObject.hpp"

namespace nastya::builtins::lists {
lisp::ObjectStorage HeadEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const {
    if (object.getType() == lisp::ObjectType::List) {
        // TODO: Error handling
        const auto& list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
        auto content = list.getContent();
        return content[0];
    }
    throw;
}

lisp::ObjectStorage TailEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const {
    if (object.getType() == lisp::ObjectType::List) {
        // TODO: Error handling
        const auto& list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
        auto content = list.getContent();
        std::vector<lisp::ObjectStorage> tail(++content.begin(), content.end());
        return lisp::ObjectStorage(std::unique_ptr<lisp::IObject>(new lisp::typesystem::ListObject(tail)));
    }
    throw;
}

}
