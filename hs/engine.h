#ifndef HS_ENGINE_H
#define HS_ENGINE_H

#include "hs/concepts.h"

class Effect {
public:
	Effect(void);
private:
};

class Buff {
public:
	Buff(void);
	~Buff(void);
private:
	enum class Type : unsigned short { none=0,
		aura, temp, hard
	};
	std::string name;
	std::string text;
};

class Targets {
public:
	Targets(void);
private:
};

class Queue {
public:
	Queue(void);
private:
};

class Spell : public CardBase {
public:
	Spell(std::string& nm, unsigned int cst, Hero::Type tp) : CardBase(cst,tp) {
		name=nm; type=CardBase::Type::spell;
	}
private:
	Buff variance;
};

class Minion : public CardBase, public CharacterBase {
public:
	Minion(std::string& nm, unsigned int cst, Hero::Type tp, unsigned int atk, int hth)
	: CardBase(cst,tp), CharacterBase(atk,hth) {
		name=nm;
	}
private:
	Buff variance;
};

class Hand {
public:
	Hand(void);
private:
	std::list<CardBase> contents;
};

class Deck {
public:
	Deck(void);
private:
	std::list<CardBase> contents;
};

class Board {
public:
	Board(void);
private:
	std::list<CharacterBase> contents;
};

class Scene {
public:
	Scene(void);
private:
	std::pair<Hero,Hero> heroes;	//first is player's
	std::pair<Hand,Hand> hands;		//second is opponent's
	std::pair<Board,Board> board;
};

#endif // HS_ENGINE_H
