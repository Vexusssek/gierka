#pragma once
#include <string>

class Potwor 
{
private:
    std::string name;
    char symbol;
    int hp;
    int maxHp;
    int attack;
    int defense;
    std::string description;
public:
    Potwor(std::string name, char symbol, int hp, int attack, int defense, 
           std::string description);
    ~Potwor() = default;

    std::string getName() const { return name; }
    char getSymbol() const { return symbol; }
    int getHp() const { return hp; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    std::string getDescription() const { return description; }
    void heal(int amount);
    int getMaxHp() const { return maxHp; }

    void printInfo() const;
};
