#include "view/AnimalWindow.h"
#include "model/Animal.h"
#include "imgui.h"
#include <cstdio>

AnimalWindow::AnimalWindow()
	: visible(false), createModalOpen(false),
		age(0), weight(0.0f), dietIndex(0), happiness(50), cleanliness(50)
{
	nameBuffer[0] = '\0';
}

void AnimalWindow::render() {
	if (!visible) return;

	ImGui::Begin("Животные", &visible);

	if (ImGui::Button("Создать животное")) {
		printf("okey");
		createModalOpen = true;
		ImGui::OpenPopup("Создание животного");
	}

	ImGui::Separator();

	// Спосок животных
	if (animals.empty()) {
		ImGui::Text("Пока нет животных.");
	} else {
		for (size_t i = 0; i < animals.size(); i++) {
			const Animal& a = animals[i];
			ImGui::Text("%s | Возраст: %d | Вес: %.1f | Питание: %s | Счастье: %d | Чистота: %d",
				a.getName().c_str(), a.getAge(), a.getWeight(),
				(a.getDiet() == DietType::Herbivore ? "Травоядный" : 
				a.getDiet() == DietType::Carnivore ? "Хищник" : "Всеядный"),
				a.getHappiness(), a.getCleanliness()
			);
		}	
	}

	// Модальное окно создания животного
	if (ImGui::BeginPopupModal("Создание животного", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputText("Имя", nameBuffer, sizeof(nameBuffer));
		ImGui::InputInt("Возраст", &age);
		ImGui::InputFloat("Вес", &weight);

		const char* diets[] = { "Травоядный", "Хищник", "Всеядный" };
		ImGui::Combo("Тип питания", &dietIndex, diets, IM_ARRAYSIZE(diets));

		ImGui::InputInt("Счастье", &happiness, 0, 100);
		ImGui::InputInt("Чистота", &cleanliness, 0, 100);

		if (ImGui::Button("Отмена")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Создать")) {
			DietType diet = DietType::Herbivore;
			if (dietIndex == 1) diet = DietType::Carnivore;
			else if (dietIndex == 2) diet = DietType::Omnivore;

			animals.emplace_back(
				std::string(nameBuffer),
				age,
				weight,
				diet,
				happiness,
				cleanliness
			);

			// Сброс формы
			nameBuffer[0] = '\0';
			age = 0;
			weight = 0.0f;
			dietIndex = 0;
			happiness = 50;
			cleanliness = 50;

			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	ImGui::End();
}

void AnimalWindow::setVisible(bool vis) {
	visible = vis;
}

bool AnimalWindow::isVisible() const {
	return visible;
}