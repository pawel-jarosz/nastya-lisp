//
// Created by caedus on 20.03.2021.
//

#include "VirtualMachine/Machine.hpp"
#include "Utilities/ListBuilder.hpp"
#include "TypeSystem/Types/LabelObject.hpp"
#include "TypeSystem/Types/NumberObject.hpp"
#include "TypeSystem/ObjectStorage.hpp"
#include "VirtualMachine/MachineRuntimeException.hpp"

#include "Modules/Testing/ModuleRegistryMock.hpp"


#include <gtest/gtest.h>

namespace nastya::vm {

using namespace utils;
using namespace typesystem;

using namespace ::testing;

struct MemoryAccessTest : public Test {
    MemoryAccessTest() : module_registry{}, machine{module_registry} {
    }

    modules::ModuleRegistryMock module_registry;
    Machine machine;
};

TEST_F(MemoryAccessTest, getVariableFromHeap) {
    LabelObject invalid_name{"InvalidName"};
    LabelObject variable_name{"VariableName"};
    ObjectStorage variable_value{std::unique_ptr<IObject>{new NumberObject{2}}};
    auto result = machine.run(ObjectStorage{std::unique_ptr<IObject>{invalid_name.clone()}});
    EXPECT_EQ(result.toString(), invalid_name.toString());
    machine.registerVariableOnHeap(variable_name, variable_value);
    result = machine.run(ObjectStorage{std::unique_ptr<IObject>{variable_name.clone()}});
    EXPECT_EQ(result.toString(), variable_value.toString());
}

TEST_F(MemoryAccessTest, getOverridedVariableFromStack) {
    LabelObject variable_name{"VariableName"};
    ObjectStorage name_storage{std::unique_ptr<IObject>{variable_name.clone()}};
    for (int i = 0; i < 4; i++) {
        ObjectStorage variable_value{std::unique_ptr<IObject>{new NumberObject{i}}};
        machine.pushStackFrame();
        machine.registerVariableOnStack(variable_name, variable_value);
        auto result = machine.run(name_storage);
        EXPECT_EQ(result.toString(), std::to_string(i));
    }
    for (int i = 4; i > 0; i--) {
        auto result = machine.run(name_storage);
        EXPECT_EQ(result.toString(), std::to_string(i - 1));
        machine.popStackFrame();
    }
    EXPECT_FALSE(machine.popStackFrame());
}

TEST_F(MemoryAccessTest, getVariableFromStackBottom) {
    LabelObject bottom_name{"BottonName"};
    LabelObject variable_name{"VariableName"};
    ObjectStorage bottom_value{std::unique_ptr<IObject>{new NumberObject{2}}};
    ObjectStorage name_storage{std::unique_ptr<IObject>{variable_name.clone()}};
    ObjectStorage bottom_storage{std::unique_ptr<IObject>{bottom_name.clone()}};

    machine.registerVariableOnStack(bottom_name, bottom_value);

    for (int i = 0; i < 4; i++) {
        ObjectStorage variable_value{std::unique_ptr<IObject>{new NumberObject{i}}};
        machine.pushStackFrame();
        machine.registerVariableOnStack(variable_name, variable_value);
    }
    auto result = machine.run(bottom_storage);
    EXPECT_EQ(result.toString(), std::to_string(2));
    for (int i = 4; i > 0; i--) {
        machine.popStackFrame();
    }
}

TEST_F(MemoryAccessTest, notLabelSimpleCaseIsIdentity) {
    ObjectStorage value{std::unique_ptr<IObject>{new NumberObject{2}}};
    EXPECT_EQ(machine.run(value).toString(), value.toString());
}

}
