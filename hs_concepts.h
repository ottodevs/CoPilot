#ifndef HS_CONCEPTS_H
#define HS_CONCEPTS_H

#include <map>
#include <list>
#include <string>

#define CST_BoardSize 7
#define CST_HandSize 10

class Attack {
public:
	Attack(unsigned int val) : value(val) { }

	void Set(unsigned int val) { value=val; }
	unsigned int Get(void) const { return value; }

	bool equal(const Attack& other) const {
		return value==other.value;
	}
	bool less(const Attack& other) const {
		return value<other.value;
	}
private:
	unsigned int value;
};
class Health {
public:
	Health(int val) : max(val),value(val) { }

	bool Add(int pt) {
		if((value+=pt)>max) {
			value=max; return false;
		} else return true;
	}
	bool Subtract(int pt) {		//to show overkill
		return ((value-=pt)>0);
	}

	void Set(int val) { max=val; value=val; }
	int GetVal(void) const { return value; }
	bool isDamaged(void) const { return value<max; }

	bool equal(const Health& other) const {
		return max==other.max;
	}
	bool less(const Health& other) const {
		return max<other.max;
	}
private:
	int max;
	int value;
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
		if(health.isDamaged()) result&=damaged;
		if(health.GetVal()<0) result&=killed;
		if(!health.equal(base->health)) {
			result&=(health.less(base->health)?debuffed:buffed);
		}
		if(!attack.equal(base->attack)) {
			result&=(attack.less(base->attack)?debuffed:buffed);
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
	~Card(void);
private:
	unsigned int cost;

	static const std::map<std::string,Card> CardList;
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

class Hero {
public:
	Hero(void);
	~Hero(void);

	class Armor {
	public:
		Armor(unsigned int val) : value(val) { }

		void Set(unsigned int val) { value=val; }
		unsigned int Get(void) const { return value; }

		void Add(unsigned int pt) { value+=pt; }
		unsigned int Subtract(unsigned int pt) {
			if(value>pt) { value-=pt; return 0; }
			else { pt-=value; value=0; return pt; }
		}
	private:
		unsigned int value;
	};
private:
};

class Scene {	//whole scene
public:
private:
	std::pair<Hero,Hero> heroes;	//first is player's
	std::pair<Hand,Hand> hands;		//second is opponent's
	std::pair<Board,Board> board;
};

#endif // HS_CONCEPTS_H
