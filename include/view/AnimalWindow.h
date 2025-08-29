#pragma once
#include "view/View.h"
#include "model/Animal.h"
#include <vector>
#include <string>

class AnimalWindow: public View {
public:
	AnimalWindow();
	void render() override;

	void setVisible(bool vis);
	bool isVisible() const;

private:
	bool visible;
	bool createModalOpen;

	std::vector<Animal> animals;

	// Временные поля для создания персонажей
	char nameBuffer[128];
	int age;
	float weight;
	int dietIndex;
	int happiness;
	int cleanliness;
};