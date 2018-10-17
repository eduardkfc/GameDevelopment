#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include <memory>
using namespace std;
using namespace sf;

int main()
{
    Vector2i SCR_RES; 
    SCR_RES.x = 1280;
    SCR_RES.y =  720;
    RenderWindow window(VideoMode(SCR_RES.x,SCR_RES.y), "REFLEX STRIKE", Style::Default);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);
    vector<std::unique_ptr<MoveParticles>> MoveObjects;
    
    while (window.isOpen())
    {
        window.clear(Color::White);
        
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            std::cout << "Created" << std::endl;
            MoveObjects.emplace_back(new Player (0,0));
        }
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type = Event::Closed) window.close();
            if (Keyboard::isKeyPressed(Keyboard::LAlt) &&
                Keyboard::isKeyPressed(Keyboard::F4))
            {
                window.close();
            }
        }
        for(std::unique_ptr<MoveParticles> & Object : MoveObjects)
        {
            window.draw(dynamic_cast<Player *> (Object.get())->sprite);
        }
        window.display();
    }

    
    return 0;
}