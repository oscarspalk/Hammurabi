#pragma once
class Person
{
private:
	int bushels;
	int farmedAcres;
public:
	Person(int bushels);
	void addBushels(int bushels);
	int getBushels();
	int farmAnAcre();
	void newYear();
	bool canSurvive();
	bool farmingFatigue();
};

