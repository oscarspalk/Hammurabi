#include <iostream>
#include "classes/Person.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#define START_PEOPLE 100
#define START_BUSHELS 2800
#define START_ACRES 1000
#define START_ACRE_VALUE 19

using namespace std;

template <class T>

T ask(string question, T returnValue) {
	T input;
	try {
		cout << question << endl;
		cin >> input;
		return input;
	}
	catch (exception e) {
		cout << "Please enter the correct values" << endl;
		return ask(question, returnValue);
	}
	
}
int year = 1;
int newPeople = 0;
int oldYearPeopleCount = START_PEOPLE;
int starvedPeople = 0;
int bushels = START_BUSHELS;
int acres = START_ACRES;
int plantedAcres = 0;
int RatAten = 0;
int deadPTotal = 0;
int newPTotal = 0;
int harvestingEfficiencyNumber = 0;
int acreValue = START_ACRE_VALUE;
vector<Person> people;

void buyAcres() {
	int amount = ask("How many acres of land do you want to buy?", 1);
	if (amount * acreValue > bushels) {
		cout << "You do not have enough credits for this." << endl;
		return buyAcres();
	}
	bushels -= amount * acreValue;
	acres += amount;
}

void sellAcres() {
	string question = "How many acres of land do you want to sell?";
	question.append(" (at ");
	question.append(to_string(acreValue));
	question.append(" per acre)");
	int amount = ask(question, 1);
	if (amount > acres) {
		cout << "You do not have enough acres for this." << endl;
		return sellAcres();
	}
	bushels += amount * acreValue;
	acres -= amount;
}

void feedPeople() {
	int amount = ask("How much grain do you want to feed to your people?", 1);
	if (amount <= bushels) {
		bushels -= amount;
		int peopleThatCanGetGrain = amount / 20;
		if (!(peopleThatCanGetGrain == 0))
		{
			if (peopleThatCanGetGrain > people.size()) {
				for (int j = 0; j < people.size(); j++)
				{
					people[j].addBushels(20);
				}
			}
			else {
				for (int i = 0; i < peopleThatCanGetGrain; i++)
				{
					people[i].addBushels(20);
				}
			}
		}
		return;
	}
	return feedPeople();
}

void seedAcres() {
	int amount = ask("How many acres do you want to seed?", 1);
	if (!(amount > acres)) {
		if (!(amount > people.size() * 10) && amount * 2 <= bushels) {
			int p = 0;
			for (int i = 0; i < amount; i++)
			{
				if (people[p].farmingFatigue()) {
					p++;
				}
				people[p].farmAnAcre();
				plantedAcres++;
				bushels -= 2;
			}
		}
		else {
			cout << "You do not have enough people or grain for this." << endl;
			return seedAcres();
		}
	}
	else {
		cout << "Invalid amount" << endl;
		return seedAcres();
	}
}

enum EndReason {
	STARVED_45, YEAR_10
};

void printEndScreen(EndReason reason) {
	system("cls");
	switch (reason)
	{
	case STARVED_45:
		cout << "Above 45% of your citizens starved, press enter to continue." << endl;
		cout << "All in all, you killed: " << deadPTotal << " people." << endl;
		
		break;
	case YEAR_10:
		cout << "You won, press enter to continue." << endl;
		cout << "All in all, you killed: " << deadPTotal << " people." << endl;
		break;
	default:
		
		break;
	}
	cin.get();
	cin.get();
}


void printNewYearMessage(int year, int starvedPeople, int newPeople, int population, int harvestedBushels, int bushelsPerAcre, int bushelsDbyRats, int bushels, int acres, int acreValue) {

	cout << "O great Hammurabi!" << endl;
	cout << "You are in year " << year << " of your ten year rule." << endl;
	cout << "In the previous year " << starvedPeople << " people starved to death." << endl;
	cout << "In the previous year " << newPeople << " people entered the kingdom." << endl;
	cout << "The population is now " << population << "." << endl;
	cout << "We harvested " << harvestedBushels << " bushels at " << bushelsPerAcre << " bushels per acre." << endl;
	cout << "Rats destroyed " << bushelsDbyRats << " bushels, leaving " << bushels << " bushels in storage." << endl;
	cout << "The city owns " << acres << " acres of land." << endl;
	cout << "Land is currently worth " << acreValue << " bushels per acre." << endl << endl;

}


int main() {

	// initialize the vector with people.
	for (int i = 0; i < START_PEOPLE; i++)
	{
		people.push_back(Person(0));
	}

	// gameloop
	while (year < 11)
	{
		// skips initial year.
		if (!(year == 1)) {

			// generate a number, if x <= 0.15, then kill half of the citizens.
			srand(time(NULL));
			int NumberProbability = (rand() % 100) + 1;
			if (NumberProbability <= -1) {
				int deadP = people.size() / 2;
				for (int j = 0; j < deadP; j++)
				{
					people.pop_back();
				}
				cout << "Your city was hit by a fatal plague, and half the people died :(" << endl;
			}

			// check if people cant survive.
			for (int i = people.size() - 1; i >= 0; i--) {
				if (!people[i].canSurvive()) {
					starvedPeople++;
					deadPTotal++;
					people.erase(people.begin() + i);
				}
			}

			// if you lost more than 45% of your people, then you will be thrown out.
			if (starvedPeople / oldYearPeopleCount >= 0.45) {
				printEndScreen(STARVED_45);
				return 0;
			}

			// if year is 10, then end the game
			if (year == 11) {
				printEndScreen(YEAR_10);
				return 0;
			}

			// reset peoples grain and fatigue.
			for (int i = 0; i < people.size(); i++)
			{
				people[i].newYear();
			}

			// if nobody starved, then calculate the amount of new citizens.
			if (!(starvedPeople > 0)) {
				int newPeopleC = (20 * acres + bushels) / (100 * people.size()) + 1;
				for (int i = 0; i < newPeopleC; i++)
				{
					people.push_back(Person(0));
					newPeople++;
					newPTotal++;
				}
			}

			// calculate how efficient the harvest was and the income.
			int harvestingEfficiency = (rand() % 5) + 1;
			harvestingEfficiencyNumber = harvestingEfficiency;
			bushels += harvestingEfficiency * plantedAcres;

			// check if rats have aten of the grain, if they have, notify the player.
			if (NumberProbability <= 40) {
				int howMuchRatAten = (rand() % 3) + 1;
				int estimatedTakings = bushels / 10 * howMuchRatAten;
				RatAten = estimatedTakings;
				bushels -= estimatedTakings;
				cout << "Rats have aten " << howMuchRatAten << "/10 of your grain." << endl;
			}

			// calculate the new land cost.
			acreValue = (rand() % 6) + 17;

		}
		printNewYearMessage(year, starvedPeople, newPeople, people.size(), plantedAcres, harvestingEfficiencyNumber, RatAten, bushels, acres, acreValue);
		
		// reset several variables, and make them ready for use again.
		newPeople = 0;
		plantedAcres = 0;
		oldYearPeopleCount = people.size();
		starvedPeople = 0;
		RatAten = 0;
		buyAcres();
		sellAcres();
		feedPeople();
		seedAcres();

		// clear window and increment year
		system("cls");
		year++;
	}
	cin.get();
	cin.get();
}

