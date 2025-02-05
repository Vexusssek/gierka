#include "Potwor.h"
#include <cstdio>

Potwor::Potwor(std::string name, char symbol, int hp, int attack, int defense, 
               std::string description)
    : name(name), symbol(symbol), hp(hp), maxHp(hp), attack(attack), 
      defense(defense), description(description){}

void Potwor::heal(int amount) {
    hp = std::min(hp + amount, maxHp);
}

void Potwor::printInfo() const 
{
    printf("Nazwa: %s\nSymbol: %c\nHP: %d\nAtak: %d\nObrona: %d\nOpis: %s\n", 
        name.c_str(), symbol, hp, attack, defense, description.c_str());
}