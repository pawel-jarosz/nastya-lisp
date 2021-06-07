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

struct RunFlowTest : public Test {
    RunFlowTest() : module_registry{}, machine{module_registry} {
    }

    modules::ModuleRegistryMock module_registry;
    Machine machine;
};

TEST_F(RunFlowTest, notLabelSimpleCaseIsIdentity) {
    ObjectStorage value{std::unique_ptr<IObject>{new NumberObject{2}}};
    EXPECT_EQ(machine.run(value).toString(), value.toString());
}

}
