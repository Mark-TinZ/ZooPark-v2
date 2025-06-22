#include "model/GameLogic.h"

void GameLogic::updateScore(int points) {
    score += points;
}

int GameLogic::getScore() const {
    return score;
}

std::string GameLogic::getGameStatus() const {
    return "Score: " + std::to_string(score);
}