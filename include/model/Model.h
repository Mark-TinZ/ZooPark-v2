#ifndef MODEL_H
#define MODEL_H

#include <string>

class Model {
public:
    Model();
    void setPlayerName(const std::string& name);
    std::string getPlayerName() const;
    void setVolume(float volume);
    float getVolume() const;
    void resetGame();

private:
    std::string playerName;
    float volume;
};

#endif