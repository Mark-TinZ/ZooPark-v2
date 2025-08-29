#include "presenter/Presenter.h"

// В этой минимальной реализации Presenter не вмешивается в логку UI,
// он просто дергает рендер соответствующих окон. Любая "умная" связка
// (сигналы/флаги/смена сцен) может быть добавлена позже.

Presenter::Presenter(Model& m, GameLogic& gl, 
                     GameWindowUI& gw, SettingsWindow& sw, 
                     StoryWindow& stw, AnimalWindow& aw)
    : model(m), gameLogic(gl), gameWindowUI(gw), settingsWindow(sw), storyWindow(stw), animalWindow(aw)
{
}

void Presenter::update() {
    // Рендер главного меню из Presenter, чтобы main.cpp не вызывал его отдельно
    gameWindowUI.Render();

    // Эти окна уже рендерятся из main.cpp; при желании можно перенести и их сюда.
}

void Presenter::handleInput() {
    // Пока ничего: логику обработки инпута/флагов можно добавить позже.
}

// void Presenter::update() {
// 	gameWindowUI.setGameStatus(gameLogic.getGameStatus());
// 	settingsWindow.setVisible(gameWindowUI.isSettingsRequested());

// 	if (storyWindow.isFinished()) {
// 		// gameLogic.updateScore(1);
// 		animalWindow.setVisible(true);
		
// 	}

// 	if (gameWindowUI.isNewGameRequested()) {
// 		storyWindow.setVisible(true);   // включаем показ истории
// 		gameWindowUI.setNewGameRequested(false); // сбрасываем флаг
// 	}
// }

// void Presenter::handleInput() {
// 	if (gameWindowUI.isExitRequested()) {
// 		ImGui::OpenPopup("Подтверждение выхода");
// 		gameWindowUI.setExitRequested(false); // Сброс флага
// 		// glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
// 		// return;
// 	}

// 	if (ImGui::BeginPopupModal("Подтверждение выхода", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
// 		ImGui::Text("Вы уверены, что хотите выйти?");
// 		if (ImGui::Button("Да")) {
// 			glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
// 			ImGui::CloseCurrentPopup();
// 		}
// 		ImGui::SameLine();
// 		if (ImGui::Button("Нет")) {
// 			ImGui::CloseCurrentPopup();
// 		}
// 		ImGui::EndPopup();
// 	}

// 	if (gameWindowUI.isSettingsRequested()) {
// 		settingsWindow.setVisible(true);
// 	}

// 	if (settingsWindow.isApplyClicked()) {
// 		model.setPlayerName(settingsWindow.getPlayerNameInput());
// 		model.setVolume(settingsWindow.getVolumeInput());
// 	}

// 	if (settingsWindow.isResetClicked()) {
// 		model.resetGame();
// 		gameLogic.updateScore(-gameLogic.getScore()); // Сброс очков
// 		settingsWindow.setPlayerName(model.getPlayerName());
// 		settingsWindow.setVolume(model.getVolume());
// 	}
// }