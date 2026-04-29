#pragma once
#include "Portfolio.hpp"

class App
{
public:
    App();
    void run();

private:
    Portfolio portfolio;

    void displayMenu();
    void handleChoice(int choice);
};