#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<vector>
#include<sstream>
using namespace sf;
using namespace std;

//Render full screen window
RenderWindow window(VideoMode(998, 1080), "Pac-Man", Style::Fullscreen | Style::Titlebar | Style::Close);

//Define PacPlayMode
int GameMode = 0, GameMode3i = 0;

//fps check
Clock gameClock;
float deltaTime = 0;

//Animation Control
float pacmanTimer = 0;
float pacmanDelay = 0.1f;
float ghostTimer = 0;
float ghostDelay = 0.3f;
float deathTimer = 0;
float deathDelay = 0.3f;
int pacmani = 0, ghostri = 0, ghostpi = 0, ghostci = 0, ghostoi = 0, deathi = 0;

//click Delay
float clickTimer = 0;
float clickDelay = 0.17f;

//Velocities
Vector2f pacmanSpeed = { 200, 200 }, ghostSpeed = { 100, 100 };

//Characters
Texture intetiestexture;
Sprite pacman, ghostr, ghostp, ghostc, ghosto;

//Fex the chase error in GameMode 1
Vector2f normalize(Vector2f vec)
{
	float mag = sqrtf(vec.x * vec.x + vec.y * vec.y);
	if (mag != 0)
	{
		vec.x /= mag;
		vec.y /= mag;
	}
	return vec;
}

// 1 -> One Player and ghost doesn't collide whith wall
// 2 -> One Player and ghost tracks your way whith collision
// 3 -> Two Players and the ghost player doesn't collide whith wall
// 4 -> Two Players and the ghost player collide but can use more than one ghost
void PacPlayMode(int x)
{
	//Pacman Movment
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (pacmanTimer < 0)
		{
			pacmani++;
			pacmani %= 3;
			pacman.setTextureRect(IntRect(850, (pacmani * 50), 50, 50));
			pacmanTimer = pacmanDelay;
		}
		else
		{
			pacmanTimer -= deltaTime;
		}
		pacman.move(pacmanSpeed.x * deltaTime, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		if (pacmanTimer < 0)
		{
			pacmani++;
			pacmani %= 3;
			pacman.setTextureRect(IntRect(850, 450 + (pacmani * 50), 50, 50));
			pacmanTimer = pacmanDelay;
		}
		else
		{
			pacmanTimer -= deltaTime;
		}
		pacman.move(0, -pacmanSpeed.y * deltaTime);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		if (pacmanTimer < 0)
		{
			pacmani++;
			pacmani %= 3;
			pacman.setTextureRect(IntRect(850, 150 + (pacmani * 50), 50, 50));
			pacmanTimer = pacmanDelay;
		}
		else
		{
			pacmanTimer -= deltaTime;
		}
		pacman.move(0, pacmanSpeed.y * deltaTime);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (pacmanTimer < 0)
		{
			pacmani++;
			pacmani %= 3;
			pacman.setTextureRect(IntRect(850, 300 + (pacmani * 50), 50, 50));
			pacmanTimer = pacmanDelay;
		}
		else
		{
			pacmanTimer -= deltaTime;
		}
		pacman.move(-pacmanSpeed.x * deltaTime, 0);
	}

	//Mode 1
	if (x == 1)
	{
		Vector2f ChaseDestance;
		ChaseDestance = ((pacman.getPosition()) - (ghostr.getPosition()));
		if (ChaseDestance.x > 0)
		{
			if (ghostTimer < 0)
			{
				ghostri++;
				ghostri %= 2;
				ghostr.setTextureRect(IntRect(650, (ghostri * 50), 50, 50));
				ghostTimer = ghostDelay;
			}
			else
			{
				ghostTimer -= deltaTime;
			}
		}
		if (ChaseDestance.x < 0)
		{
			if (ghostTimer < 0)
			{
				ghostri++;
				ghostri %= 2;
				ghostr.setTextureRect(IntRect(650, 200 + (ghostri * 50), 50, 50));
				ghostTimer = ghostDelay;
			}
			else
			{
				ghostTimer -= deltaTime;
			}
		}
		ghostr.move(normalize(ChaseDestance) * ghostSpeed.x * deltaTime);
		//window.clear();
		window.draw(ghostr);
		window.draw(pacman);
		//window.display();
	}

	//Mode 2
	else if (x == 2)
	{

	}

	//Mode 3
	else if (x == 3)
	{
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			if (ghostTimer < 0)
			{
				ghostri++;
				ghostri %= 2;
				ghostr.setTextureRect(IntRect(650, (ghostri * 50), 50, 50));
				ghostTimer = ghostDelay;
			}
			else
			{
				ghostTimer -= deltaTime;
			}
			ghostr.move(ghostSpeed.x * deltaTime, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			if (ghostTimer < 0)
			{
				ghostri++;
				ghostri %= 2;
				ghostr.setTextureRect(IntRect(650, 300 + (ghostri * 50), 50, 50));
				ghostTimer = ghostDelay;
			}
			else
			{
				ghostTimer -= deltaTime;
			}
			ghostr.move(0, -ghostSpeed.y * deltaTime);
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			if (ghostTimer < 0)
			{
				ghostri++;
				ghostri %= 2;
				ghostr.setTextureRect(IntRect(650, 100 + (ghostri * 50), 50, 50));
				ghostTimer = ghostDelay;
			}
			else
			{
				ghostTimer -= deltaTime;
			}
			ghostr.move(0, ghostSpeed.y * deltaTime);
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			if (ghostTimer < 0)
			{
				ghostri++;
				ghostri %= 2;
				ghostr.setTextureRect(IntRect(650, 200 + (ghostri * 50), 50, 50));
				ghostTimer = ghostDelay;
			}
			else
			{
				ghostTimer -= deltaTime;
			}
			ghostr.move(-ghostSpeed.x * deltaTime, 0);
		}
		//window.clear();
		window.draw(ghostr);
		window.draw(pacman);
		//window.display();
	}

	//Mode 4
	else if (x == 4)
	{
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			if (clickTimer < 0)
			{
				GameMode3i++;
				if (GameMode3i == 4)
				{
					ghostr.setTextureRect(IntRect(0, 600, 50, 50));
					ghostp.setTextureRect(IntRect(700, 0, 50, 50));
					ghostc.setTextureRect(IntRect(750, 0, 50, 50));
					ghosto.setTextureRect(IntRect(800, 0, 50, 50));
				}
				else if (GameMode3i == 1)
				{
					ghostr.setTextureRect(IntRect(650, 0, 50, 50));
					ghostp.setTextureRect(IntRect(0, 600, 50, 50));
					ghostc.setTextureRect(IntRect(750, 0, 50, 50));
					ghosto.setTextureRect(IntRect(800, 0, 50, 50));
				}
				else if (GameMode3i == 2)
				{
					ghostr.setTextureRect(IntRect(650, 0, 50, 50));
					ghostp.setTextureRect(IntRect(700, 0, 50, 50));
					ghostc.setTextureRect(IntRect(0, 600, 50, 50));
					ghosto.setTextureRect(IntRect(800, 0, 50, 50));
				}
				else if (GameMode3i == 3)
				{
					ghostr.setTextureRect(IntRect(650, 0, 50, 50));
					ghostp.setTextureRect(IntRect(700, 0, 50, 50));
					ghostc.setTextureRect(IntRect(750, 0, 50, 50));
					ghosto.setTextureRect(IntRect(0, 600, 50, 50));
				}
				clickTimer = clickDelay;
			}
			else
			{
				clickTimer -= deltaTime;
			}
		}
		GameMode3i %= 4;
		if (GameMode3i == 1)
		{
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				if (ghostTimer < 0)
				{
					ghostpi++;
					ghostpi %= 2;
					ghostp.setTextureRect(IntRect(700, (ghostpi * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghostp.move(ghostSpeed.x * deltaTime, 0);
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				if (ghostTimer < 0)
				{
					ghostpi++;
					ghostpi %= 2;
					ghostp.setTextureRect(IntRect(700, 300 + (ghostpi * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghostp.move(0, -ghostSpeed.y * deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				if (ghostTimer < 0)
				{
					ghostpi++;
					ghostpi %= 2;
					ghostp.setTextureRect(IntRect(700, 100 + (ghostpi * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghostp.move(0, ghostSpeed.y * deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				if (ghostTimer < 0)
				{
					ghostpi++;
					ghostpi %= 2;
					ghostp.setTextureRect(IntRect(700, 200 + (ghostpi * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghostp.move(-ghostSpeed.x * deltaTime, 0);
			}
		}
		else if (GameMode3i == 0)
		{
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				if (ghostTimer < 0)
				{
					ghostri++;
					ghostri %= 2;
					ghostr.setTextureRect(IntRect(650, (ghostri * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghostr.move(ghostSpeed.x * deltaTime, 0);
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				if (ghostTimer < 0)
				{
					ghostri++;
					ghostri %= 2;
					ghostr.setTextureRect(IntRect(650, 300 + (ghostri * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghostr.move(0, -ghostSpeed.y * deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				if (ghostTimer < 0)
				{
					ghostri++;
					ghostri %= 2;
					ghostr.setTextureRect(IntRect(650, 100 + (ghostri * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghostr.move(0, ghostSpeed.y * deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				if (ghostTimer < 0)
				{
					ghostri++;
					ghostri %= 2;
					ghostr.setTextureRect(IntRect(650, 200 + (ghostri * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghostr.move(-ghostSpeed.x * deltaTime, 0);
			}
		}
		else if (GameMode3i == 2)
		{
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				if (ghostTimer < 0)
				{
					ghostci++;
					ghostci %= 2;
					ghostc.setTextureRect(IntRect(750, (ghostci * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghostc.move(ghostSpeed.x * deltaTime, 0);
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				if (ghostTimer < 0)
				{
					ghostci++;
					ghostci %= 2;
					ghostc.setTextureRect(IntRect(750, 300 + (ghostci * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghostc.move(0, -ghostSpeed.y * deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				if (ghostTimer < 0)
				{
					ghostci++;
					ghostci %= 2;
					ghostc.setTextureRect(IntRect(750, 100 + (ghostci * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghostc.move(0, ghostSpeed.y * deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				if (ghostTimer < 0)
				{
					ghostci++;
					ghostci %= 2;
					ghostc.setTextureRect(IntRect(750, 200 + (ghostci * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghostc.move(-ghostSpeed.x * deltaTime, 0);
			}
		}
		else if (GameMode3i == 3)
		{
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				if (ghostTimer < 0)
				{
					ghostoi++;
					ghostoi %= 2;
					ghosto.setTextureRect(IntRect(800, (ghostoi * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghosto.move(ghostSpeed.x * deltaTime, 0);
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				if (ghostTimer < 0)
				{
					ghostoi++;
					ghostoi %= 2;
					ghosto.setTextureRect(IntRect(800, 300 + (ghostoi * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghosto.move(0, -ghostSpeed.y * deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				if (ghostTimer < 0)
				{
					ghostoi++;
					ghostoi %= 2;
					ghosto.setTextureRect(IntRect(800, 100 + (ghostoi * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghosto.move(0, ghostSpeed.y * deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				if (ghostTimer < 0)
				{
					ghostoi++;
					ghostoi %= 2;
					ghosto.setTextureRect(IntRect(800, 200 + (ghostoi * 50), 50, 50));
					ghostTimer = ghostDelay;
				}
				else
				{
					ghostTimer -= deltaTime;
				}
				ghosto.move(-ghostSpeed.x * deltaTime, 0);
			}
		}

		//window.clear();
		window.draw(ghostr);
		window.draw(ghostp);
		window.draw(ghostc);
		window.draw(ghosto);
		window.draw(pacman);
		//window.display();
	}
}

//Pacman Death Animation
void PacManDeath()
{
	while (deathi <= 10)
	{
		if (deathTimer < 0)
		{
			deathi++;
			pacman.setTextureRect(IntRect(350, (deathi * 50), 50, 50));
			deathTimer = deathDelay;
		}
		else
		{
			deathTimer -= deltaTime;
		}
		window.clear();
		window.draw(pacman);
		window.display();
		ghostr.setPosition(500, 400);
		
	}
	deathi = 0;
}

int main()
{
	// Sound effects
	SoundBuffer collectbf;
	collectbf.loadFromFile("./collect.wav");
	Sound collect;
	collect.setBuffer(collectbf);
	//window.setFramerateLimit(120);
	Texture mapTexture;
	mapTexture.loadFromFile("./resize map.png");
	Sprite map;
	map.setTexture(mapTexture);
	//map.setScale(1000.f/(2.f * 29.f), 800.f/(2.f* 248.f));

	intetiestexture.loadFromFile("./PacmanSprites.png");
	pacman.setTexture(intetiestexture);
	pacman.setTextureRect(IntRect(850, 0, 50, 50));
	pacman.setScale(1.25f, 1.25f);
	pacman.setPosition(630965-998/2,630);
	ghostr.setTexture(intetiestexture);
	ghostr.setTextureRect(IntRect(650, 0, 50, 50));
	ghostr.setScale(1.4, 1.4);
	ghostr.setPosition(500, 400);
	ghostp.setTexture(intetiestexture);
	ghostp.setTextureRect(IntRect(700, 0, 50, 50));
	ghostp.setScale(1.4, 1.4);
	ghostc.setTexture(intetiestexture);
	ghostc.setTextureRect(IntRect(750, 0, 50, 50));
	ghostc.setScale(1.4, 1.4);
	ghosto.setTexture(intetiestexture);
	ghosto.setTextureRect(IntRect(800, 0, 50, 50));
	ghosto.setScale(1.4, 1.4);
	//score
	long long score = -100;
	Font font;
	Text Score;
	font.loadFromFile("score.otf");
	Score.setFont(font);
	Score.setCharacterSize(48);
	Score.setFillColor(Color::White);
	Font font2;
	Text Live;
	font2.loadFromFile("score.otf");
	Live.setFont(font2);
	Live.setCharacterSize(48);
	Live.setFillColor(Color::White);
	Live.setPosition(0,998);
	Font font3;
	Text end;
	font3.loadFromFile("score.otf");
	end.setFont(font3);
	end.setCharacterSize(48);
	end.setFillColor(Color::White);
	end.setPosition(455 + 455.f/2.f,599);
	// game over
	Texture gameEndtext;
	gameEndtext.loadFromFile("./game over.jpg");
	Sprite gameEnd;
	gameEnd.setTexture(gameEndtext);
	gameEnd.setOrigin(320, 180);
	gameEnd.setPosition(455 * 2, 499);


	int lives = 0;
	float g = 100;
		vector<string> mapSketch = {
		"############################",
		"#            ##            #",
		"# 3          ##           3#",
		"#31###   ##  ##  ###   ##31#",
		"# 3                       3#",
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
		"# 3     #    #    #       3#",
		"#313#####    #    #####  31#",
		"# 3                       3#",
		"#                          #",
		"############################",
	};

	///*vector<string> mapSketch = {
	//	"############################",
	//	"#   1        ##           1#",
	//	"#            ##            #",
	//	"#  ###  ##   ##   ###  ##  #",
	//	"#                          #",
	//	"#                          #",
	//	"#   ##     ######     ##   #",
	//	"#   ##     ######     ##   #",
	//	"#      #     ##     #      #",
	//	"#      #     ##     #      #",
	//	"#####  ###        ###  #####",
	//	"#####  #            #  #####",
	//	"#####  #            #  #####",
	//	"          ##     ##         ",
	//	"          #       #         ",
	//	"          #       #         ",
	//	"#####  #  ######### #  #####",
	//	"#####  #            #  #####",
	//	"#####  #            #  #####",
	//	"#      #  ########  #      #",
	//	"#            ##            #",
	//	"#            ##            #",
	//	"#  ###  ###      ###  ###  #",
	//	"#    #                #    #",
	//	"##   #                # 1 ##",
	//	"##     #   #####   #      ##",
	//	"#      #     #     #       #",
	//	"#  #####     #     #####   #",
	//	"#     1                    #",
	//	"#                          #",
	//	"############################",
	//};*/
	//vector<string> mapSketch = {
	//	"###################",
	//	"#        #        #",
	//	"# ## ### # ### ## #",
	//	"# ## ### # ### ## #",
	//	"#                 #",
	//	"# ## # ##### # ## #",
	//	"#    #   #   #    #",
	//	"#### ### # ### ####",
	//	"#### #       # ####",
	//	"#### # ## ## # ####",
	//	"       #   #       ",
	//	"#### # ##### # ####",
	//	"#### #       # ####",
	//	"#### # ##### # ####",
	//	"#        #        #",
	//	"# ## ### # ### ## #",
	//	"#  #           #  #",
	//	"## # # ##### # # ##",
	//	"#    #   #   #    #",
	//	"# ###### # ###### #",
	//	"#                 #",
	//	"###################",
	//};
	vector<RectangleShape> fullPix;
	vector<CircleShape> points;
	vector<CircleShape> powerUps;
	vector < pair < CircleShape, pair<int, int >>> fullCirclePix;
		bool isalive = 0;
		int coincount = 132;
	while (window.isOpen())
	{
	if(Mouse::isButtonPressed(Mouse::Right))
	{
		cout << Mouse::getPosition().x << ' ' <<  Mouse::getPosition().y;
	}
		Vector2f pacmanSpeed = { 200, 200 }, ghostSpeed = { 75, 75};
		//Vector2f velocity = { 150,150 };
		gameClock.restart();
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}
		//y < 19, x < 22
		for (int y = 0; y < 29; ++y) {
			for (int x = 0; x < 31; ++x) {
				if (mapSketch[x][y] == '#')
				{
					RectangleShape pix(Vector2f(1, 1));
					// 600 + y, 100 + x
					pix.setPosition(455 + y * (1080.f / 30), x * (998.f / 28.f));
					pix.setScale((1080.f / 30), (998.f / 28.f));
					pix.setFillColor(Color::Blue);
					fullPix.push_back(pix);
					window.draw(pix);
				}
				else if (mapSketch[x][y] == ' ' && x % 2 == 0 && y % 2 == 0)
				{
					//CircleShape point(0.2f);
					//// 615 + y, 115 + x
					//point.setPosition(470 + y * (1080.f / 30), 15 + x * (998.f / 28.f));
					//point.setScale((1080.f / 30), (998.f / 28.f));
					//point.setFillColor(Color::Yellow);
					//points.push_back(point);
					//window.draw(point);
					CircleShape pix(0.2);
					pix.setPosition(455 + (y + 0.3) * (1080.f / 30), (x + 0.3) * (998.f / 28.f));
					pix.setScale((1080.f / 30), (998.f / 28.f));
					pix.setFillColor(Color::Magenta);
					fullCirclePix.push_back({ pix,{x,y} });
					window.draw(pix);
				}
				else if (mapSketch[x][y] == '1')
				{
					//CircleShape point(0.2f);
					//// 615 + y, 115 + x
					//point.setPosition(470 + y * (1080.f / 30), 15 + x * (998.f / 28.f));
					//point.setScale((1080.f / 30), (998.f / 28.f));
					//point.setFillColor(Color::Yellow);
					//points.push_back(point);
					//window.draw(point);
					CircleShape pix(0.5f);
					pix.setPosition(455 + (y ) * (1080.f / 30), (x ) * (998.f / 28.f));
					pix.setScale((1080.f / 30), (998.f / 28.f));
					pix.setFillColor(Color::Yellow);
					fullCirclePix.push_back({ pix,{x,y} });
					window.draw(pix);
				}
				
			}
		}
		
		

			 // teleport
		if (pacman.getGlobalBounds().left < 455.f)
			pacman.setPosition(998 + 455 - pacman.getGlobalBounds().width, pacman.getGlobalBounds().top);
		else if (pacman.getGlobalBounds().left + pacman.getGlobalBounds().width > 998.f + 455.f)
			pacman.setPosition(455, pacman.getGlobalBounds().top);
		// colision

		for (int i = 0; i < fullPix.size(); i++)
		{
		FloatRect nextpos = pacman.getGlobalBounds();
		nextpos.left += pacmanSpeed.x * deltaTime;
		nextpos.top += pacmanSpeed.y * deltaTime;
			
			if (fullPix[i].getGlobalBounds().intersects(nextpos))
			{
				// Right
				if (pacman.getGlobalBounds().left < fullPix[i].getGlobalBounds().left
					&& pacman.getGlobalBounds().left + pacman.getGlobalBounds().width < fullPix[i].getGlobalBounds().left + fullPix[i].getGlobalBounds().width
					&& pacman.getGlobalBounds().top < fullPix[i].getGlobalBounds().top + fullPix[i].getGlobalBounds().height
					&& pacman.getGlobalBounds().top + pacman.getGlobalBounds().height > fullPix[i].getGlobalBounds().top
					)
				{
					pacmanSpeed.x = 0.f;
					pacman.setPosition(fullPix[i].getGlobalBounds().left - pacman.getGlobalBounds().width, pacman.getGlobalBounds().top);
				}
				// Left
				else if (pacman.getGlobalBounds().left > fullPix[i].getGlobalBounds().left
					&& pacman.getGlobalBounds().left + pacman.getGlobalBounds().width > fullPix[i].getGlobalBounds().left + fullPix[i].getGlobalBounds().width
					&& pacman.getGlobalBounds().top < fullPix[i].getGlobalBounds().top + fullPix[i].getGlobalBounds().height
					&& pacman.getGlobalBounds().top + pacman.getGlobalBounds().height > fullPix[i].getGlobalBounds().top
					)
				{
					pacmanSpeed.x = 0.f;
					pacman.setPosition(fullPix[i].getGlobalBounds().left + fullPix[i].getGlobalBounds().width, pacman.getGlobalBounds().top);
				}
				// Top
				else if (pacman.getGlobalBounds().top > fullPix[i].getGlobalBounds().top
					&& pacman.getGlobalBounds().top + pacman.getGlobalBounds().height > fullPix[i].getGlobalBounds().top + fullPix[i].getGlobalBounds().height
					&& pacman.getGlobalBounds().left < fullPix[i].getGlobalBounds().left + fullPix[i].getGlobalBounds().width
					&& pacman.getGlobalBounds().left + pacman.getGlobalBounds().width > fullPix[i].getGlobalBounds().left
					)
				{
					pacmanSpeed.y = 0.f;
					pacman.setPosition(pacman.getGlobalBounds().left, fullPix[i].getGlobalBounds().top + fullPix[i].getGlobalBounds().height);
				}
				//  Bottom
				else if (pacman.getGlobalBounds().top < fullPix[i].getGlobalBounds().top
					&& pacman.getGlobalBounds().top + pacman.getGlobalBounds().height < fullPix[i].getGlobalBounds().top + fullPix[i].getGlobalBounds().height
					&& pacman.getGlobalBounds().left < fullPix[i].getGlobalBounds().left + fullPix[i].getGlobalBounds().width
					&& pacman.getGlobalBounds().left + pacman.getGlobalBounds().width > fullPix[i].getGlobalBounds().left
					)
				{
					pacmanSpeed.y = 0.f;
					pacman.setPosition(pacman.getGlobalBounds().left, fullPix[i].getGlobalBounds().top - pacman.getGlobalBounds().height);
				}

			}
		}
		
		FloatRect nextpos = ghostr.getGlobalBounds();
		/*nextpos.left += ghostSpeed.x*deltaTime;
		nextpos.top += ghostSpeed.y*deltaTime;*/
		if (pacman.getGlobalBounds().intersects(nextpos))
		{
			lives++;
			score -= 100;
			//if(lives == 3)
			PacManDeath();
			pacman.setPosition(500, 900);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num1))
			GameMode = 1;
		else if (Keyboard::isKeyPressed(Keyboard::Num2))
			GameMode = 2;
		else if (Keyboard::isKeyPressed(Keyboard::Num3))
			GameMode = 3;
		else if (Keyboard::isKeyPressed(Keyboard::Num4))
		{
			GameMode = 4;
			ghostr.setPosition(500, 350);
			ghostp.setPosition(500, 400);
			ghostc.setPosition(550, 400);
			ghosto.setPosition(450, 400);
		}
		if (GameMode != 0)
			PacPlayMode(GameMode);
			
		// assigning text
		stringstream ss;
		ss << "Score " << score;
		Score.setString(ss.str());
		window.draw(Score);
		stringstream sss;
		sss << "Lives " << 3-lives;
		Live.setString(sss.str());
		window.draw(Live);
		string gameOver ="           press Enter";
		end.setString(gameOver);
		//coins collision
		for (int i = 0; i < fullCirclePix.size(); i++)
		{
			if (fullCirclePix[i].first.getGlobalBounds().intersects(pacman.getGlobalBounds()))
			{
		     	collect.play();
				if (fullCirclePix[i].first.getFillColor() == Color::Magenta)
					score+=100;
				else
					score += 500;
				mapSketch[fullCirclePix[i].second.first][fullCirclePix[i].second.second] = '2';
			coincount--;
			}
		}
		if (coincount == 0)
		{
			mapSketch = {
	"############################",
	"#            ##            #",
	"# 3          ##           3#",
	"#31###   ##  ##  ###   ##31#",
	"# 3                       3#",
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
	"# 3     #    #    #       3#",
	"#313#####    #    #####  31#",
	"# 3                       3#",
	"#                          #",
	"############################",
			};
		}

		if (lives == 3 or isalive)
		{
			isalive = 1;
			RectangleShape black(Vector2f(1920, 1080));
			black.setFillColor(Color::Black);
			window.draw(black);
			window.draw(gameEnd);
			window.draw(end);
			GameMode = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			lives = 0;
			isalive = 0;
			score = 0;
			mapSketch = {
		"############################",
		"#            ##            #",
		"# 3          ##           3#",
		"#31###   ##  ##  ###   ##31#",
		"# 3                       3#",
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
		"# 3     #    #    #       3#",
		"#313#####    #    #####  31#",
		"# 3                       3#",
		"#                          #",
		"############################",
			};
			
		}
		
		
			window.display();
			window.clear();
		
		fullCirclePix.clear();
		fullPix.clear();
		

		deltaTime = gameClock.getElapsedTime().asSeconds();
	}
	return 0;
}
