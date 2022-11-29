#pragma once

class Attribute {
public:
    enum Index {
        HEALTH,
        STRENGTH, // Damage, ability to wield some items(?)
        DEXTERITY, // Dodge chance, hit chance(?)
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