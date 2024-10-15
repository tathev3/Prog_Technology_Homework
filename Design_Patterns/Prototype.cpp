#include <iostream>
#include <memory>
#include <string>

class Hero {
public:
    virtual ~Hero() = 0; 
    virtual std::unique_ptr<Hero> clone() const = 0; 
    virtual void display() const = 0; 
};

Hero::~Hero() {}

class Warrior : public Hero {
private:
    std::string _name;
    std::string _weapon;
    int _health;
public:
    Warrior(const std::string& name, const std::string& weapon, int health)
        : _name(name), _weapon(weapon), _health(health) {}

    std::unique_ptr<Hero> clone() const override {
        return std::make_unique<Warrior>(*this); 
    }

    void display() const override {
        std::cout << "Warrior: " << _name << ", weapon: " << _weapon << ", health: " << _health << std::endl;
    }
    void setName(const std::string& name) { _name = name; }
    void setWeapon(const std::string& weapon) { _weapon = weapon; }
    void setHealth(int health) { _health = health; }
};

class Mage : public Hero {
private:
    std::string _name;
    std::string _spell;
    int _mana;
public:
    Mage(const std::string& name, const std::string& spell, int mana)
        : _name(name), _spell(spell), _mana(mana) {}

    std::unique_ptr<Hero> clone() const override {
        return std::make_unique<Mage>(*this); 
    }

    void display() const override {
        std::cout << "Mage: " << _name << ", spell: " << _spell << ", mana: " << _mana << std::endl;
    }

    void setName(const std::string& name) { _name = name; }
    void setSpell(const std::string& spell) { _spell = spell; }
    void setMana(int mana) { _mana = mana; }
};

class HeroFactory {
private:
    static Warrior warriorPrototype;
    static Mage magePrototype;
public:
    static std::unique_ptr<Hero> newWarrior(const std::string& name, const std::string& weapon, int health) {
        auto warrior = warriorPrototype.clone(); 
        dynamic_cast<Warrior*>(warrior.get())->setName(name);
        dynamic_cast<Warrior*>(warrior.get())->setWeapon(weapon); 
        dynamic_cast<Warrior*>(warrior.get())->setHealth(health); 
        return warrior; 
    }

    static std::unique_ptr<Hero> newMage(const std::string& name, const std::string& spell, int mana) {
        auto mage = magePrototype.clone(); 
        dynamic_cast<Mage*>(mage.get())->setName(name); 
        dynamic_cast<Mage*>(mage.get())->setSpell(spell); 
        dynamic_cast<Mage*>(mage.get())->setMana(mana); 
        return mage; 
    }
};

Warrior HeroFactory::warriorPrototype = Warrior("Thor", "Mjolnir", 200);
Mage HeroFactory::magePrototype = Mage("Doctor Strange", "Eldritch Whip", 300);

int main() {
    auto warrior1 = HeroFactory::newWarrior("Iron Man", "Infinity Gauntlet", 250);
    auto mage1 = HeroFactory::newMage("Scarlet Witch", "Hex", 400);

    warrior1->display();
    mage1->display();

    return 0;
}


