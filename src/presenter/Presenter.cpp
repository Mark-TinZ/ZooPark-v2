#include "presenter/Presenter.h"

Presenter::Presenter(Model& m, GameLogic& gl, GameWindow& gw, SettingsWindow& sw)
    : model(m), gameLogic(gl), gameWindow(gw), settingsWindow(sw) {
    gameWindow.setGameStatus(gameLogic.getGameStatus());
    settingsWindow.setPlayerName(model.getPlayerName());
    settingsWindow.setVolume(model.getVolume());
}

void Presenter::update() {
    gameWindow.setGameStatus(gameLogic.getGameStatus());
    settingsWindow.setVisible(gameWindow.isSettingsRequested());
}

void Presenter::handleInput() {
	if (gameWindow.isExitRequested()) {
		ImGui::OpenPopup("Подтверждение выхода");
		gameWindow.setExitRequested(false); // Сброс флага
		// glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
        // return;
	}

	if (ImGui::BeginPopupModal("Подтверждение выхода", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Вы уверены, что хотите выйти?");
        if (ImGui::Button("Да")) {
            glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Нет")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    if (gameWindow.isSettingsRequested()) {
        settingsWindow.setVisible(true);
    }

    if (settingsWindow.isApplyClicked()) {
        model.setPlayerName(settingsWindow.getPlayerNameInput());
        model.setVolume(settingsWindow.getVolumeInput());
    }

    if (settingsWindow.isResetClicked()) {
        model.resetGame();
        gameLogic.updateScore(-gameLogic.getScore()); // Сброс очков
        settingsWindow.setPlayerName(model.getPlayerName());
        settingsWindow.setVolume(model.getVolume());
    }
}