#include <random>
#include <string>

#include "../header/Game.h"

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

Game::Game(std::list<Player> players)
{
    this->players = players;
    this->ChooseRandomText();
    this->CalculateWordCount();
}