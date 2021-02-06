//
// Created by caedus on 01.02.2021.
//

#pragma once

#include <Runtime/Interface/IEvaluatorFactory.hpp>

namespace nastya::runtime {

template<typename Evaluator>
class GenericEvaluatorFactory : public IEvaluatorFactory
{
public:
    std::unique_ptr<IEvaluator> create() const override {
        std::unique_ptr<IEvaluator> evaluator{new Evaluator};
        return evaluator;
    }
};

}  // namespace nastya::runtime

