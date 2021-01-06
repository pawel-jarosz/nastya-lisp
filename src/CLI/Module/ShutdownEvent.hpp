//
// Created by caedus on 06.01.2021.
//

#pragma once

#include <But/Exception.hpp>

namespace nastya::cli::module {

BUT_DEFINE_EXCEPTION(ShutdownEvent, But::Exception, "Close interpreter");

}
