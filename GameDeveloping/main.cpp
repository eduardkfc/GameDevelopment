#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{
    Vector2i SCR_RES; 
    SCR_RES.x = 1920;
    SCR_RES.y = 1080;
    RenderWindow window(VideoMode(SCR_RES.x,SCR_RES.y), "REFLEX STRIKE", Style::Default);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);
    

    window.clear(Color::White);
    window.display();
    return 0;
}