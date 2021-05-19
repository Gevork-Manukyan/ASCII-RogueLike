#pragma once
class Mob
{
public:
	Mob(char symbol, int x, int y);

	//Getters
	std::string getName() { return _name; }
	int getHealth() { return _health; }
	int getAttack() { return _attack; }
	int getDefense() { return _defense; }
	int getX() { return _x; }
	int getY() { return _y; }
	void getLocation(int& x, int& y) { x = _x; y = _y; }
	char getSymbol() { return _symbol; }
	int getID() { return _ID; }

	//Setters
	void setLocation(int x, int y) { _x = x; _y = y; }

	int attack();
	int takeDamage(int attack);
	void addExperience(int EMPTY) {}

private:
	//Mob name
	std::string _name;
	//Hit points
	int _health;
	//Damage output
	int _attack;
	//Damage block
	int _defense;
	//Location
	int _x;
	int _y;
	//Icon
	char _symbol;
	//Exp worth
	int _experienceValue;
	//Mob's unique ID value
	int _ID;

	void createSnake(int x, int y, int ID);
	void createOgre(int x, int y, int ID);
};

