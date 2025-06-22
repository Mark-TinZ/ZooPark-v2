#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "view/View.h"
#include <string>

class GameWindow : public View {
public:
    GameWindow();
    void render() override;
    void setGameStatus(const std::string& status);
    void setShowSettings(bool show);
    bool isSettingsRequested() const;
	bool isExitRequested() const;
	void setExitRequested(bool exit);

private:
    std::string gameStatus;
    bool showSettings = false;
	bool exitRequested = false;
};

#endif