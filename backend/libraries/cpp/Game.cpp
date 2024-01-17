#include <random>
#include <string>

#include "../header/Game.h"
#include "../header/Log.h"

void Game::ChooseRandomText()
{
    int max = this->randomTexts.size();

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> dist(0, max - 1);
    this->chosenText = dist(generator);
}

void Game::CalculateWordCount()
{
    int wc = 1;
    for (auto letter : this->randomTexts[this->wordCount])
        wc = letter == ' ' ? wc+1 : wc;
    this->wordCount = wc;
}

void Game::SetPlayerProgress(std::string userId, int progress)
{
    for (Player &player : this->players)
    {
        if (player.id == userId)
        {
            player.progress = progress;
            if (player.progress >= this->wordCount)
                this->finished = true;
            Log::Write("Set " + userId + "'s progress to " + std::to_string(progress));
            return;
        }
    }

    Log::Write("Player " + userId + " is not in game");
}

Game::Game(std::list<Player> players)
{
    this->players = players;
    this->ChooseRandomText();
    this->CalculateWordCount();
}