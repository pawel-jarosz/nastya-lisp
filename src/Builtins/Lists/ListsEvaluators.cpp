//
// Created by caedus on 21.12.2020.
//

#include "ListsEvaluators.hpp"

namespace nastya::builtins::lists {
lisp::ObjectStorage HeadEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const {
    // TODO: implement
    return object;
}

lisp::ObjectStorage TailEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const {
    // TODO: implement
    return object;
}

}
