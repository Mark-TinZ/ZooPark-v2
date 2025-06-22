#include "view/GameWindow.h"
#include "imgui.h"

GameWindow::GameWindow() : gameStatus("Score: 0") {}

void GameWindow::render() {
    // Настройка docking - исправленная версия
    ImGui::DockSpaceOverViewport(0); // Используем 0 как ID по умолчанию
    
    // Главное меню
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Game")) {
                // Обработчик в Presenter
            }
            if (ImGui::MenuItem("Settings")) {
                showSettings = true;
            }
            if (ImGui::MenuItem("Exit")) {
                exitRequested = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Игровое окно
    ImGui::Begin("Game");
    ImGui::Text("%s", gameStatus.c_str());
    if (ImGui::Button("Add Score")) {
        // Обработчик в Presenter
    }
    ImGui::End();
}

void GameWindow::setGameStatus(const std::string& status) {
    gameStatus = status;
}

void GameWindow::setShowSettings(bool show) {
    showSettings = show;
}

bool GameWindow::isSettingsRequested() const {
    return showSettings;
}

bool GameWindow::isExitRequested() const {
	return exitRequested;
}

void GameWindow::setExitRequested(bool exit) {
	exitRequested = exit;
}