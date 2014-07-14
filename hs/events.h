#ifndef HS_EVENTS_H
#define HS_EVENTS_H

#include <QObject>

#include "hs/engine.h"

class Events : public QObject { Q_OBJECT
public:
	explicit Events(QObject *parent = 0);
/*
signals:
	void attacks(QObject* actor);
	void isAttacked(QObject* target);
	void isPlayed(QObject* target);
	void isDamaged(QObject* target);
	void isHealed(QObject* target);
	void isDestroyed(QObject* target);
	void isRevealed(QObject* target);	//for secrets
	void startTurn(bool opponent);
	void endTurn(bool opponent);
public slots:
	void drawCard(int count=1);
	void damage(int amount, Targets target);
	void heal(int amount, Targets target);
	void destroy(Targets target);
	void buff(Buff buff, Targets target);
	void clearBuff(Buff buff, Targets target);
	void silence(Targets target);
	void summon(Creature creature);
*/
};

#endif // HS_EVENTS_H
