#ifndef PRESENTER_H
#define PRESENTER_H

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "model/Model.h"
#include "model/GameLogic.h"
#include "view/GameWindow.h"
#include "view/SettingsWindow.h"

class Presenter {
public:
    Presenter(Model& model, GameLogic& gameLogic, GameWindow& gameWindow, SettingsWindow& settingsWindow);
    void update();
    void handleInput();

private:
    Model& model;
    GameLogic& gameLogic;
    GameWindow& gameWindow;
    SettingsWindow& settingsWindow;
};

#endif