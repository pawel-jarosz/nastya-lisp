//
// Created by caedus on 01.02.2021.
//

#pragma once

#include <Runtime/Interface/IEvaluator.hpp>

namespace nastya::runtime {

class IEvaluatorFactory
{
public:
    virtual ~IEvaluatorFactory() = default;
    virtual std::unique_ptr<IEvaluator> create() const = 0;
};

}  // namespace nastya::runtime

