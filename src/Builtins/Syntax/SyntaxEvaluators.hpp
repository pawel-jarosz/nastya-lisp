//
// Created by caedus on 09.01.2021.
//

#pragma once

#include "Runtime/GenericEvaluatorFactory.hpp"
#include "Runtime/GenericEvaluator.hpp"

namespace nastya::builtins::syntax {

class IfEvaluator : public runtime::GenericEvaluator, public runtime::GenericEvaluatorFactory<IfEvaluator>
{
public:
    IfEvaluator() : runtime::GenericEvaluator{"If"} {}
    typesystem::ObjectStorage preExecute(const typesystem::ListObject& object,
                                   runtime::IMachine& vm) const override;
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override;
};

class CondEvaluator : public runtime::GenericEvaluator, public runtime::GenericEvaluatorFactory<CondEvaluator>
{
public:
    CondEvaluator() : runtime::GenericEvaluator{"Cond"} {}
    typesystem::ObjectStorage preExecute(const typesystem::ListObject& object,
                                   runtime::IMachine& vm) const override;
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override;
};

class DefineEvaluator : public runtime::GenericEvaluator, public runtime::GenericEvaluatorFactory<DefineEvaluator>
{
public:
    DefineEvaluator() : runtime::GenericEvaluator{"Define"} {}
    typesystem::ObjectStorage preExecute(const typesystem::ListObject& object,
                                   runtime::IMachine& vm) const override;
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override;
};

class LetInEvaluator : public runtime::GenericEvaluator, public runtime::GenericEvaluatorFactory<LetInEvaluator>
{
public:
    LetInEvaluator() : runtime::GenericEvaluator{"Let"} {}
    typesystem::ObjectStorage preExecute(const typesystem::ListObject& object,
                                   runtime::IMachine& vm) const override;
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override;

};

class LambdaEvaluator : public runtime::GenericEvaluator, public runtime::GenericEvaluatorFactory<LambdaEvaluator>
{
public:
    LambdaEvaluator() : runtime::GenericEvaluator{"Lambda"} {}
    typesystem::ObjectStorage preExecute(const typesystem::ListObject& object,
                                   runtime::IMachine& vm) const override;
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override;

};

}  // namespace nastya::builtins::syntax
