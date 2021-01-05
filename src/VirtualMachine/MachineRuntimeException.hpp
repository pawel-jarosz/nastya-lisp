//
// Created by caedus on 05.01.2021.
//

#pragma once

#include <But/Exception.hpp>

namespace nastya::vm {

BUT_DEFINE_EXCEPTION(MachineRuntimeException, But::Exception, "MachineRuntimeException");

}