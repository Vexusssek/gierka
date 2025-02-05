#include "Walka.h"

bool Walka::rozpocznijWalke(Player& player, Istota& przeciwnik) 
{
    while(player.isAlive() && przeciwnik.isAlive()) 
    {
        system("cls");
        printf("\nTwoja tura!\n");
        printf("HP: %d/%d  Mana: %d/%d\n", 
               player.getStats().getCurrentHp(), player.getStats().getMaxHp(),
               player.getStats().getCurrentMana(), player.getStats().getMaxMana());
        printf("Przeciwnik HP: %d\n", przeciwnik.getHp());

        if(player.getStats().isDead()) 
        {
            printf("\nGAME OVER!\n");
            return false;
        }

        printf("\nWybierz akcję:\n");
        printf("1. Zwykły atak\n");
        if(player.hasSkills()) 
        {
            printf("2. Użyj umiejętności\n");
        }

        char choice = _getch();
        if(choice == '1') 
        {
            if(player.attackSys(przeciwnik)) 
            {
                Kostka d10(10);
                Kostka d5(5);
                int goldReward = d10.rzut() + d5.rzut();
                player.getStats().addGold(goldReward);

                Kostka expDice(10);
                int expGain = 5 + expDice.rzut();
                player.getStats().addExperience(expGain);

                printf("\nZwyciężyłeś!\n");
                printf("Znaleziono %d złota!\n", goldReward);
                printf("Zdobyto %d doświadczenia!\n", expGain);
                system("pause");
                return true;
            }
        }
        else if(choice == '2' && player.hasSkills()) 
        {
            player.displaySkills();
            printf("Wybierz umiejętność (1-%zu): ", player.getSkillsCount());
            char skillChoice = _getch();
            int skillIndex = skillChoice - '1';
            
            if(player.useSkill(skillIndex, przeciwnik)) 
            {
                if(!przeciwnik.isAlive()) 
                {
                    Kostka d10(10);
                    Kostka d5(5);
                    int goldReward = d10.rzut() + d5.rzut();
                    player.getStats().addGold(goldReward);
                    printf("\nZnaleziono %d złota!\n", goldReward);

                    Kostka expDice(10);
                    int expGain = 5 + expDice.rzut();
                    player.getStats().addExperience(expGain);
                    printf("\nZdobyto %d doświadczenia!\n", expGain);
                    system("pause");
                    return true;
                }
            }
        }

        if(przeciwnik.isAlive()) 
        {
            printf("\nTura przeciwnika!\n");
            if(przeciwnik.attackSys(player)) 
            {
                player.damage(przeciwnik.getAttack());
                printf("Otrzymano %d obrażeń!\n", przeciwnik.getAttack());
                if(player.getStats().isDead()) 
                {
                    printf("\nGAME OVER!\n");
                    system("pause");
                    return false;
                }
            }
            
            // Banished One - mechanika ucieczki
            if (przeciwnik.getName() == "Banished One" && przeciwnik.getHp() < (przeciwnik.getMaxHp() * 0.7))
            {
                Kostka escapeChance(10);
                if (escapeChance.rzut() <= 4) 
                {
                    printf("\nO nie! Banished One uciekł...\n");
                    system("pause");
                    return true;
                }
            }

            if (przeciwnik.getName() == "Flamethrower" && przeciwnik.getHp() < 10) 
            {
                if (!przeciwnik.hasAlreadyHealed())
                {
                     Kostka healChance(10);
                     if (healChance.rzut() <= 4)
                    {
                        int maxHp = przeciwnik.getMaxHp();
                        int healAmount = maxHp * 0.5;
                        przeciwnik.heal(healAmount);
                        przeciwnik.setHealed(true);
                        printf("%s odnowił sobie %d HP!\n", przeciwnik.getName().c_str(), healAmount);
                    }
                }
            }

            if (przeciwnik.getName() == "Ice Minion" && przeciwnik.getHp() < 8) 
            {
                Kostka healChance(10);
                if (healChance.rzut() <= 6)
                {
                    int dmg = (przeciwnik.getAttack())* 5;
                    player.damage(dmg);
                    printf("%s Atak krytyczny! DMG: %d HP!\n", przeciwnik.getName().c_str(), dmg);
                }
            }

            system("pause");
        }
    }
    return player.isAlive();
}