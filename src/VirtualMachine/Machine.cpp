//
// Created by caedus on 22.12.2020.
//

#include <algorithm>

#include "LispExpression/TypeSystem/LabelObject.hpp"
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "Builtins/BuiltinsException.hpp"
#include "Modules/ModuleException.hpp"
#include "VirtualMachine/Machine.hpp"

#include "VirtualMachine/MachineRuntimeException.hpp"

namespace nastya::vm {

Machine::Machine(const modules::IModuleRegistry& registry) : m_modules{registry}
{
}

lisp::ObjectStorage Machine::run(const lisp::ObjectStorage& list)
{
    if (list.getType() != lisp::ObjectType::List)
    {
        return list;
    }
    // GCOVR_EXCL_START
    //
    // Casts does not required to be check for bad_cast error because type are checked with enum.
    // Index is correct because earlier we checked if it is not empty list.
    auto raw_object = dynamic_cast<lisp::typesystem::ListObject&>(list.getRawObject());
    if (raw_object.isEmpty()) {
        return lisp::ObjectStorage(list);
    }
    auto content = raw_object.getContent();
    if (content[0].getType() != lisp::ObjectType::Label) {
        BUT_THROW(MachineRuntimeException, "Invalid command format");
    }
    auto label = dynamic_cast<lisp::typesystem::LabelObject&>(content[0].getRawObject());
    // GCOVR_EXCL_STOP
    std::vector<lisp::ObjectStorage> arguments;
    if (label.getValue() == "Quote")
    {
        arguments = std::vector(++content.begin(), content.end());
    }
    else
    {
        std::for_each(++content.begin(), content.end(), [&](const auto& obj) { arguments.emplace_back(run(obj)); });
    }
    std::unique_ptr<lisp::typesystem::ListObject> obj(new lisp::typesystem::ListObject(arguments));
    lisp::ObjectStorage argument(std::move(obj));
    std::string message;
    return m_modules.getFunction(label.getValue()).evaluate(*this, argument);
}

}  // namespace nastya::vm
