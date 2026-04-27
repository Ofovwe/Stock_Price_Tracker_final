#pragma once

#include "Asset.hpp"
#include "Portfolio.hpp"

class Dashboard
{
public:
	Dashboard(double width = 1200.0f, double height = 800.0f);
	void run(const Portfolio& portfolio);

private:
	sf::RenderWindow mWindow;
    sf::Font mFont;

	double mWidth;
	double mHeight;

    void handleEvents();
    void render(const Portfolio& portfolio);

    void drawBackground();
    void drawHeader(const Portfolio& portfolio);
    void drawAssetTable(const Portfolio& portfolio);
    void drawBarChart(const Portfolio& portfolio);

    void drawText(const std::string& text,
        float x,
        float y,
        unsigned int size = 20,
        sf::Color color = sf::Color::White);
};