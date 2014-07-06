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
	enum Type {none, additive, hard};
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

class Creature : public CardBase {
public:
	Creature(void);
private:
	Buff variance;
};

class Spell : public CardBase {
public:
	Spell(void);
private:
	Buff variance;
};

#endif // HS_ENGINE_H
