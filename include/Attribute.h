#pragma once

enum class AttributeIndex {
    HEALTH,
    STRENGTH, // Damage, ability to wield some items(?)
    DEXTERITY // Dodge chance, hit chance(?)
};

class Attribute {
public:
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