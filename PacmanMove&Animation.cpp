#include <SFML/Graphics.hpp>
#include <iomanip>
using namespace std;
using namespace sf;

int main()
{
	Clock gameClock;
	float deltaTime = 0;
	float delay = 0.2f;
	float timer = 0;
	int i = 0;
	int speed = 200;

	RenderWindow window(VideoMode(1000, 800), "Pacio");
	Texture pacmantexture;
	pacmantexture.loadFromFile("./GeneralSprites0.png");

	Sprite pacman;
	pacman.setTexture(pacmantexture);
	pacman.setTextureRect(IntRect(32, 0, 16, 16));
	pacman.setScale(3, 3);
	while (window.isOpen())
	{
		gameClock.restart();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (timer < 0)
			{
				i++;
				i %= 3;
				pacman.setTextureRect(IntRect((i * 16), 0, 16, 16));
				timer = delay;
			}
			else
			{
				timer -= deltaTime;
			}
			pacman.move(speed * deltaTime, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (timer < 0)
			{
				i++;
				i %= 3;
				if (i == 2)
					pacman.setTextureRect(IntRect((i * 16), 0, 16, 16));
				else
					pacman.setTextureRect(IntRect((i * 16), 32, 16, 16));
				timer = delay;
			}
			else
			{
				timer -= deltaTime;
			}
			pacman.move(0, -speed * deltaTime);
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
		{
			 if (timer < 0)
			 {
				i++;
				i %= 3;
				if (i == 2)
					pacman.setTextureRect(IntRect((i * 16), 0, 16, 16));
				else
					pacman.setTextureRect(IntRect((i * 16), 48, 16, 16));
				timer = delay;
			 }
			 else
			 {
				timer -= deltaTime;
			 }
			 pacman.move(0, speed * deltaTime);
		}
		else if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
		{
			 if (timer < 0)
			 {
				i++;
				i %= 3;
				if (i == 2)
					pacman.setTextureRect(IntRect((i * 16), 0, 16, 16));
				else
					pacman.setTextureRect(IntRect((i * 16), 16, 16, 16));
				timer = delay;
			 }
			 else
			 {
				timer -= deltaTime;
			 }
			 pacman.move(-speed * deltaTime, 0);
		 }

		 window.clear();
		 window.draw(pacman);
		 window.display();

		deltaTime = gameClock.getElapsedTime().asSeconds();
	}
}
