#pragma once

#include "Asset.hpp"
#include "Portfolio.hpp"

class Dashboard
{
public:
	Dashboard(float width = 1200.0f, float height = 800.0f);
	void run(Portfolio& portfolio);

private:
	sf::RenderWindow mWindow;
    sf::Font mFont;

	float mWidth;
	float mHeight;

    void handleEvents();
    void render(Portfolio& portfolio);

    void drawBackground();
    void drawHeader(Portfolio& portfolio);
    void drawAssetTable(Portfolio& portfolio);
    void drawBarChart(Portfolio& portfolio);

    void drawText(const std::string& text,
        float x,
        float y,
        unsigned int size = 20,
        sf::Color color = sf::Color::White);
};