#pragma once
#include "Portfolio.hpp"
#include "Dashboard.hpp"

class App
{
public:
    App();
    ~App();

    void run();

private:
    sf::RenderWindow mWindow;
    sf::Font mFont;

    Portfolio mPortfolio;
    Dashboard mDashboard;

    // Menu buttons
    sf::RectangleShape mLoadButton;
    sf::RectangleShape mDashboardButton;
    sf::RectangleShape mSortValueButton;
    sf::RectangleShape mSortProfitButton;
    sf::RectangleShape mSummaryButton;
    sf::RectangleShape mExitButton;

    // Summary message shown on screen
    string mStatusMessage;

private:
    void initializeButtons();
    void handleEvents();
    void render();

    bool isMouseOverButton(const sf::RectangleShape& button, float mouseX, float mouseY);

    void drawButton(const sf::RectangleShape& button, const string& label, float textX, float textY);
    void drawText(const string& text, float x, float y, unsigned int size = 24, sf::Color color = sf::Color::White);

    void loadPortfolioFiles();
    void showSummary();
};