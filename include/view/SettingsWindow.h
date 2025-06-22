#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "view/View.h"
#include <string>

class SettingsWindow : public View {
public:
    SettingsWindow();
    void render() override;
    void setPlayerName(const std::string& name);
    void setVolume(float volume);
    std::string getPlayerNameInput() const;
    float getVolumeInput() const;
    bool isApplyClicked() const;
    bool isResetClicked() const;
    void setVisible(bool visible);

private:
    std::string playerNameInput;
    float volumeInput;
    bool applyClicked = false;
    bool resetClicked = false;
    bool visible = false;
};

#endif