#include "view/SettingsWindow.h"
#include "imgui.h"

SettingsWindow::SettingsWindow() : playerNameInput("Player"), volumeInput(0.5f) {}

void SettingsWindow::render() {
    if (!visible) return;

    ImGui::Begin("Settings", &visible);
    char buffer[256];
    strncpy(buffer, playerNameInput.c_str(), sizeof(buffer));
    if (ImGui::InputText("Player Name", buffer, sizeof(buffer))) {
        playerNameInput = buffer;
    }
    ImGui::SliderFloat("Volume", &volumeInput, 0.0f, 1.0f);
    if (ImGui::Button("Apply")) {
        applyClicked = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
        resetClicked = true;
    }
    ImGui::End();

    // Диалоговое окно для подтверждения сброса
    if (resetClicked) {
        ImGui::OpenPopup("Confirm Reset");
    }
    if (ImGui::BeginPopupModal("Confirm Reset", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Are you sure you want to reset all settings?");
        if (ImGui::Button("Yes")) {
            resetClicked = true;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("No")) {
            resetClicked = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void SettingsWindow::setPlayerName(const std::string& name) {
    playerNameInput = name;
}

void SettingsWindow::setVolume(float volume) {
    volumeInput = volume;
}

std::string SettingsWindow::getPlayerNameInput() const {
    return playerNameInput;
}

float SettingsWindow::getVolumeInput() const {
    return volumeInput;
}

bool SettingsWindow::isApplyClicked() const {
    return applyClicked;
}

bool SettingsWindow::isResetClicked() const {
    return resetClicked;
}

void SettingsWindow::setVisible(bool vis) {
    visible = vis;
}