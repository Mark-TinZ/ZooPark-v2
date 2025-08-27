#include "model/Animal.h"

Animal::Animal(const std::string& n, int a, float w, DietType d, int h, int c)
	: name(n), age(a), weight(w), diet(d), happiness(h), cleanliness(c) {}

const std::string& Animal::getName() const { return name; }
int Animal::getAge() const { return age; }
float Animal::getWeight() const { return weight; }
DietType Animal::getDiet() const { return diet; }
int Animal::getHappiness() const { return happiness; }
int Animal::getCleanliness() const { return cleanliness; }
