#ifndef HS_CONCEPTS_H
#define HS_CONCEPTS_H

#include <map>
#include <list>
#include <string>
#include <iostream>

#include "str_enum.h"

#define CST_BoardSize 7
#define CST_HandSize 10

class CardBase {
public:
	CardBase(void);

	class Cost{
	public:
		Cost(void);
	private:
	};
	class Attack{
	public:
		Attack(void);
	private:
	};
	class Health{
	public:
		Health(void);
	private:
	};
protected:
	Cost* cost;
	Attack* attack;
	Health* health;
};













class Attack {
public:
	Attack(unsigned int val) : value(val), base_value(val) { }

	void Set(unsigned int val) { value=val; }
	unsigned int Get(void) const { return value; }

	bool equal(const Attack& other) const {
		return value==other.value;
	}
	bool less(const Attack& other) const {
		return value<other.value;
	}
	short checkBuff(void) const {	//1=green,0=white,-1=white
		return (value>base_value ? 1 : (value<base_value ? -1 : 0));
	}
private:
	unsigned int value, base_value;
};
class Health {
public:
	Health(int val) : value(val),max(val),base_max(val) { }

	short Add(int pt) {
		if((value+=pt)>max) {
			value=max; return 1;
		} else if(value<=0) {
			return -1;
		} else return 0;
	}

	void Set(int val) { max=val; Add(0); }
	int Get(void) const { return value; }
	short checkBuff(void) const {	//1=green,0=white,-1=red
		return (value<max ? -1 : (max>base_max ? 1 : 0));
	}

	bool equal(const Health& other) const {
		return max==other.max;
	}
	bool less(const Health& other) const {
		return max<other.max;
	}
private:
	int value, max, base_max;
};

class Hero {
public:
	Hero(void);
	~Hero(void);

	class Armor {
	public:
		Armor(unsigned int val) : value(val) { }

		void Set(unsigned int val) { value=val; }
		unsigned int Get(void) const { return value; }

		unsigned int Add(int pt) {
			if(pt<0) {
				unsigned int pt_tmp=static_cast<unsigned int>(-pt);
				if(pt_tmp>value) {
					value=0; return (pt_tmp-value);
				} else {
					value-=pt_tmp; return 0;
				}
			} else {
				value+=pt;
				return 0;
			}
		}
	private:
		unsigned int value;
	};

	static std::unordered_set<StrEnum,StrEnum::StrHash> type;
	enum Type {
		none, druid, hunter, mage,
		paladin, priest, rogue,
		shaman, warlock, warrior
	};
private:
};

class Creature {
public:
	Creature(void);
	~Creature(void);

	enum Status {
		normal=0, buffed=1, debuffed=2,
		damaged=4,killed=8, destroyed=16
	};
	unsigned int getStatus(void) const {	//for effects and coloring
		unsigned int result=normal;
	//	if(health.isDamaged()) result|=damaged;
	//	if(health.GetVal()<0) result|=killed;
		if(!health.equal(base->health)) {
			result|=(health.less(base->health)?debuffed:buffed);
		}
		if(!attack.equal(base->attack)) {
			result|=(attack.less(base->attack)?debuffed:buffed);
		}
		return result;
	}	//might result in buffed+debuffed -> check source
private:
	Attack attack;
	Health health;

	const Creature* base;
};
class Spell {
public:
	Spell(void);
	~Spell(void);

	enum Target {
		none=0, enemy=1, friendly=2, minion=4, hero=8
	};
private:
	unsigned int targets;	//can compile multiple Target values
};
class Card {
public:
	Card(void);
	~Card(void) { }

	static std::map<std::string,Card> CardList;
	static void Print(void);

	unsigned int cost;
	enum Type { spell, creature, weapon } type;
	enum Rarity { common, rare, epic, legendary } rarity;
	enum Set { basic, expert, dream, promotion_basic, promotion_expert,
			   missions, legacy } set;
	Hero::Type card_class;
private:
	static std::map<std::string,Card> fillCardList(void);
};

class Board {	//one side of the board
public:
	Board(void) { }
	~Board(void) { }

	void Place(const Creature& crt, int pos);

	bool CanAdd(void) const {
		return contents.size()<=CST_BoardSize;
	}
	std::size_t size(void) const {
		return contents.size();
	}
private:
	std::list<Creature> contents;
};

class Hand {
public:
	Hand(void);
	~Hand(void);

	bool Add(const Card& crd) {
		if(contents.size()<=CST_HandSize) {
			contents.push_back(crd);
			return true;
		} else {
			return false;
		}
	}
	std::size_t size(void) const {
		return contents.size();
	}
private:
	std::list<Card> contents;
};

class Scene {	//whole scene
public:
private:
	std::pair<Hero,Hero> heroes;	//first is player's
	std::pair<Hand,Hand> hands;		//second is opponent's
	std::pair<Board,Board> board;
};

#endif // HS_CONCEPTS_H
