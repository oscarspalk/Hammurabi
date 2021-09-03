#include "Person.h"

int Person::getBushels() {
	return Person::bushels;
}

Person::Person(int bushels) : bushels(bushels), farmedAcres(0) {}

int Person::farmAnAcre() {
	if (farmedAcres >= 10) {
		return 0;
	}
	else {
		Person::farmedAcres++;
		return 1;
	}
}

void Person::newYear() {
	this->farmedAcres = 0;
	this->bushels = 0;
}

bool Person::canSurvive() {
	return bushels < 20 ? false : true;
}

void Person::addBushels(int bushels2) {
	Person::bushels += bushels2;
}

bool Person::farmingFatigue() {
	return farmedAcres == 10 ? true : false;
}