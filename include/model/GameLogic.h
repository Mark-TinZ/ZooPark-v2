#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <string>

class GameLogic {
public:
    void updateScore(int points);
    int getScore() const;
    std::string getGameStatus() const;

private:
    int score = 0;
};

#endif