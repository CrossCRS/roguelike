#pragma once

class Attribute {
public:
    enum Index {
        HEALTH,
        STRENGTH,
        LAST // Enum size marker
    };

    Attribute(int _current, int _base);
    Attribute();

    int getCurrent() const;
    int getBase() const;

    void setCurrent(int value);
    void setBase(int value);

private:
    int current;
    int base;
};