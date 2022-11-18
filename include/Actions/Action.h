#pragma once

#include <memory>
#include "Entities/Character.h"

class Action {
public:
    virtual ~Action() = default;
    virtual void execute() = 0;

    virtual std::shared_ptr<Character> getPerformer() { return nullptr; }
};