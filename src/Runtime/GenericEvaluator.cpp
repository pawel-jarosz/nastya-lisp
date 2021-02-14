//
// Created by caedus on 30.01.2021.
//

#include "Runtime/GenericEvaluator.hpp"

#include <algorithm>

namespace nastya::runtime {

GenericEvaluator::GenericEvaluator(std::string name)
: m_name{std::move(name)}
{
}

std::string GenericEvaluator::getName() const
{
    return m_name;
}

typesystem::ObjectStorage GenericEvaluator::preExecute(const typesystem::ListObject& object, IMachine& vm) const
{
    const auto content = object.getContent();
    std::vector<typesystem::ObjectStorage> arguments;
    std::for_each(++content.begin(), content.end(), [&](const auto& obj) { arguments.emplace_back(vm.run(obj)); });
    std::unique_ptr<typesystem::IObject> obj(new typesystem::ListObject(arguments));
    typesystem::ObjectStorage result(std::move(obj));
    return result;
}
void GenericEvaluator::postExecute(IMachine& vm) const
{
}

}
