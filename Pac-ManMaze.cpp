#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
using namespace sf;
using namespace std;


int main()
{

	Clock gameClock;
	float deltaTime = 0;
	float delay = 0.05f;
	float timer = 0;
	int i = 0;
	Vector2f velocity = { 100,100 };

	Texture mapTexture;
	mapTexture.loadFromFile("./resize map.png");
	Sprite map;
	map.setTexture(mapTexture);
	//map.setScale(1000.f/(2.f * 29.f), 800.f/(2.f* 248.f));

	Texture pacmantexture;
	pacmantexture.loadFromFile("./ppacman1.png");
	Sprite pacman;
	pacman.setTexture(pacmantexture);
	pacman.setTextureRect(IntRect(480.0f / 3.0f, 0, 16, 16));
	pacman.setScale(3.f, 3.f);
	pacman.setPosition(500, 500);


	RenderWindow window(VideoMode(998, 1080), "Pac-Man",Style::Fullscreen | Style::Titlebar | Style::Close); // for making full screen
	float g = 100;

	vector<string> mapSketch = {
		"############################",
		"#            ##            #",
		"#            ##            #",
		"#  ###   ##  ##  ###   ##  #",
		"#                          #",
		"#                          #",
		"#  ##      ######      ##  #",
		"#  ##      ######      ##  #",
		"#      #     ##     #      #",
		"#      #     ##     #      #",
		"#####  ###        ###  #####",
		"#####  #            #  #####",
		"#####  #            #  #####",
		"          ##    ##          ",
		"          #      #          ",
		"          #      #          ",
		"#####  #  ########  #  #####",
		"#####  #            #  #####",
		"#####  #            #  #####",
		"#      #  ########  #      #",
		"#            ##            #",
		"#            ##            #",
		"#  ###  ###      ###  ###  #",
		"#    #                #    #",
		"##   #                #   ##",
		"##      #  #####  #       ##",
		"#       #    #    #        #",
		"#   #####    #    #####    #",
		"#                          #",
		"#                          #",
		"############################",
	};
	vector<RectangleShape> fullPix;
	
	
	
	
	

	while (window.isOpen())
	{
		gameClock.restart();
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}
		// gravity collision
		for (int y = 0; y < 29; ++y) {
			for (int x = 0; x < 31; ++x) {
				if (mapSketch[x][y] == '#')
				{
					RectangleShape pix(Vector2f(1, 1));
					pix.setPosition(455+y * (1080.f / 30), x * (998.f / 28.f));
					pix.setScale((1080.f / 30), (998.f / 28.f));
					pix.setFillColor(Color::Blue);
					fullPix.push_back(pix);
					window.draw(pix);
					//window.display();

				}
			}
		cout << endl;
	    }
	   /* if (!(player.getGlobalBounds().intersects(wall.getGlobalBounds())))
			player.move(0, dt * g);*/


		//	// player movements
		
		
		
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
				pacman.move(velocity.x * deltaTime, 0);
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
				pacman.move(0, -velocity.y * deltaTime);
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
				pacman.move(0, velocity.y * deltaTime);
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
				pacman.move(-velocity.x * deltaTime, 0);

			}
			for (int i = 0; i < fullPix.size(); i++)
			{
				if (fullPix[i].getGlobalBounds().intersects(pacman.getGlobalBounds()))
				{
					if (pacman.getGlobalBounds().intersects(FloatRect(fullPix[i].getGlobalBounds().left - 1, fullPix[i].getGlobalBounds().top, 1, fullPix[i].getGlobalBounds().height)))
					{
						pacman.move(-velocity.x * deltaTime, 0);
					}


					else if (pacman.getGlobalBounds().intersects(FloatRect(fullPix[i].getGlobalBounds().left + fullPix[i].getGlobalBounds().width, fullPix[i].getGlobalBounds().top, 1, fullPix[i].getGlobalBounds().height)))
					{
						pacman.move(velocity.x * deltaTime, 0);
					}
					if (pacman.getGlobalBounds().intersects(FloatRect(fullPix[i].getGlobalBounds().left, fullPix[i].getGlobalBounds().top-1,fullPix[i].getGlobalBounds().width,3)))
					{
						pacman.move(0,-velocity.y * deltaTime);

					}
					else if (pacman.getGlobalBounds().intersects(FloatRect(fullPix[i].getGlobalBounds().left, fullPix[i].getGlobalBounds().top + fullPix[i].getGlobalBounds().height, fullPix[i].getGlobalBounds().width, 1)))
					{
						pacman.move(0, velocity.y * deltaTime);
					}
				}
			}
		
       
 
        
       

		

           //window.draw(map);
		   window.draw(pacman);
		 
		  window.display();
		  window.clear();

			deltaTime = gameClock.getElapsedTime().asSeconds();
	}
    return 0;
}