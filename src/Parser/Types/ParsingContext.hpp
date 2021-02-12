//
// Created by caedus on 12.02.2021.
//

#pragma once

namespace nastya::parser {

struct ParsingContext {
    size_t start_position;
    size_t end_position;

    ParsingContext() = default;
    ParsingContext(size_t start_pos) : start_position{start_pos}{};
};

}
