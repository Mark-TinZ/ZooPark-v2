#pragma once
#include <string>

enum class DietType { Herbivore, Carnivore, Omnivore };

class Animal {
public:
	Animal(const std::string& name, int age, float weight, DietType diet, int happiness, int cleanliness);

	const std::string& getName() const;
	int getAge() const;
	float getWeight() const;
	DietType getDiet() const;
	int getHappiness() const;
	int getCleanliness() const;

private:
	std::string name;
	int age;
	float weight;
	DietType diet;
	int happiness;
	int cleanliness;
};