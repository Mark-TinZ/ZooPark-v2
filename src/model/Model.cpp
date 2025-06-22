#include "model/Model.h"

Model::Model() : playerName("Player"), volume(0.5f) {}

void Model::setPlayerName(const std::string& name) {
    playerName = name;
}

std::string Model::getPlayerName() const {
    return playerName;
}

void Model::setVolume(float vol) {
    volume = vol;
}

float Model::getVolume() const {
    return volume;
}

void Model::resetGame() {
    playerName = "Player";
    volume = 0.5f;
}