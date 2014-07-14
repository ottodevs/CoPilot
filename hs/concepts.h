#ifndef HS_CONCEPTS_H
#define HS_CONCEPTS_H

#include <map>
#include <list>
#include <string>
#include <iostream>

#include "str_enum.h"

#define CST_BoardSize	7
#define CST_HandSize	10
#define CST_HeroHealth	30

class CharacterBase {
public:
	CharacterBase(unsigned int atk, int hth) {
		attack=atk;
		if(hth<0) hth=0;
		health=health_max=hth;
	}

	void Heal(unsigned int amount) {
		health+=amount; if(health>health_max) health=health_max;
	}
	void Damage(unsigned int amount) {
		health-=amount;
	}
	bool		isDead(void)	const { return (health<=0 ? true : false); }
	bool		isDamaged(void)	const { return (health<health_max ? true : false); }
	unsigned int getAttack(void)const { return attack; }
	int			getHealth(void)	const { return health; }
protected:
	unsigned int attack;
	int health, health_max;
};

class Hero : public CharacterBase {
public:
	enum class Type : unsigned short { none=0,
		Warrior=1, Shaman=2, Rogue=3,
		Paladin=4, Hunter=5, Druid=6,
		Warlock=7, Mage=8, Priest=9
	};

	Hero(Type tp) : CharacterBase(0,CST_HeroHealth) {
		armour=0;
		type=tp;
	}

	void ArmourUp(unsigned int amount) {
		armour+=amount;
	}
	void Damage(unsigned int amount) {
		if(amount>armour) {
			CharacterBase::Damage(amount-armour);
			armour=0;
		} else {
			armour-=amount;
		}
	}
	unsigned int getArmour(void) const { return armour; }

//	static std::unordered_set<StrEnum,StrEnum::StrHash> type;	//to consider
private:
	unsigned int armour;
	Type type;
};

class CardBase {
public:
	CardBase(unsigned int cst, Hero::Type tp) {
		cost=cst; class_type=tp;
	}

	static std::map<std::string,CardBase> fillCardList(void);
	static std::map<std::string,CardBase> CardList;

	unsigned int getCost(void) const { return cost; }

	enum class Type : unsigned short { none=0,
		spell, creature, weapon
	} type;
	enum class Rarity : unsigned short { none=0,
		common, rare, epic, legendary
	} rarity;
	enum class Set : unsigned short { none=0,
		basic, expert, dream, promo_basic, promo_expert,
		missions, legacy
	} set;
protected:
	unsigned int cost;
	Hero::Type class_type;	//forward declaration of nested enums is not possible, moved the CardBase class
	std::string name;
	std::string text;
};

#endif // HS_CONCEPTS_H
