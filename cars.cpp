#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
using namespace sf;
using namespace std;
int main()
{

    RenderWindow window(VideoMode(600, 600), "Hello");
    Texture characterText, characterTextFlip;
    characterText.loadFromFile("./Mon.png");
    characterTextFlip.loadFromFile("./Monflip.png");
    Sprite character, characterFlip;
    character.setTexture(characterText);
    characterFlip.setTexture(characterTextFlip);
    Vector2u size = characterText.getSize();
    Vector2u sizef = characterTextFlip.getSize();
    size.x /= 6;
    sizef.x /= 6;
    Clock clock;
    float t = 0;
    int speed = 200;
    int i = 0;
    int j = 1, k = 0;
    while (window.isOpen())
    {
        Event e;

        while (window.pollEvent(e))
        {
            if (e.Closed == e.type)
                window.close();
        }

        character.setTextureRect(IntRect(size.x * 0, 0, size.x, size.y));
        characterFlip.setTextureRect(IntRect(sizef.x * 0, 0, sizef.x, sizef.y));
        character.setScale(3, 3);
        characterFlip.setScale(3, 3);
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            k = 1;
            if (j == 1)
            {
                characterFlip.setPosition(character.getPosition());
                j--;
            }
            characterFlip.setTextureRect(IntRect(sizef.x * i, 0, sizef.x, sizef.y));
            characterFlip.setScale(3, 3);
            window.draw(characterFlip);
            characterFlip.move(-speed * t, 0);
            window.display();
            window.clear();

        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            character.setTextureRect(IntRect(size.x * i, 0, size.x, size.y));
            character.setScale(3, 3);
            //character.setPosition(characterFlip.getPosition());
            j = 1;
            if (k == 1)
            {
                character.setPosition(characterFlip.getPosition());
                k--;
            }
            window.draw(character);
            character.move(speed * t, 0);
            window.display();
            window.clear();
        }


       

        t = clock.getElapsedTime().asSeconds();
        clock.restart();
        i++;
        i %= 6;
    }


    return 0;
}