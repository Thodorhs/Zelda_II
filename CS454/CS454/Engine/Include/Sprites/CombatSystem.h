#pragma once
#include <iostream>


class CombatSystem {
private:
	int hp;
	int damage;
	bool AttackingMode = false;
public:
	bool getAttackingMode() { return AttackingMode; }
	void setAttackingMode(bool ChangeMode) { AttackingMode = ChangeMode; }

	void setHp(int _hp) { hp = _hp; }
	int getHp() { return hp; }

	void setDamage(int _damage) { damage = _damage; }
	int getDamage() { return damage; }

	void ReceivedDamage(int _damage) { hp = hp - _damage; }

	CombatSystem() { hp = 69; damage = 69; };
	CombatSystem(int _hp, int _damage) : hp(_hp), damage(_damage) {};
};