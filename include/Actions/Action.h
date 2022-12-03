#pragma once

class Action {
public:
    virtual ~Action() = default;
    virtual void execute() = 0;

    virtual float getSpeed() { return 1.0f; }
};