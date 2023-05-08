#pragma once
#include "../Classes&Structures/Liquid.hpp"
#include <SFML/Graphics.hpp>
#include <iterator>

void Liquid::Visualize()
{
    const int WX=1938;
    const int WY=1156;
    const double rad=4.0;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WX, WY), "SPH", sf::Style::Fullscreen, settings);
    window.setFramerateLimit(60);
    vector <sf::CircleShape> fluid;
    fluid.resize(liq.size());
    for (unsigned i=0; i<liq.size(); i++)
    {
        sf::Color c;
        if (liq[i].color=="red")
            c=sf::Color::Red;
        if (liq[i].color=="blue")
            c=sf::Color::Blue;
        if (liq[i].color=="green")
            c=sf::Color::Green;
        fluid[i].setFillColor(c);
        fluid[i].setRadius(rad);
        fluid[i].setOrigin(rad, rad);
        fluid[i].setPosition(liq[i].x, liq[i].y);
    }
    Starting();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //Moving realization
            //There's a refinement algorithm for movement (through partition of dtime)
            //Here's a place for Solve function
            //Algorithm can be done in two ways: through setPosition and move

            window.clear();
            for (vector <sf::CircleShape>::iterator it=fluid.begin(); it!=fluid.end(); ++it)
            {
                window.draw((*it));
            }
            window.display();
    }
}
