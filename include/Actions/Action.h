#pragma once

class Action {
public:
    virtual ~Action() = default;
    virtual void execute() = 0;
};