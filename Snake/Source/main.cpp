#include<SFML\Graphics.hpp>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<sstream>
#include<string.h>

int direction, points, n=10;
float height = 72.0, lenght = 128.0, grid = 10.0;

std::vector<sf::RectangleShape>snake;
sf::RenderWindow window(sf::VideoMode(lenght*grid, height*grid), "SNAKE");
sf::RectangleShape food(sf::Vector2f(grid, grid));
sf::RectangleShape snk(sf::Vector2f(grid, grid));
sf::Font font,font1;
sf::Text text,score, title, credit;


int isPlaying = 3;

float Random(int dimension)
{///Returns a random position
	float number;
	number = 25.f + (rand() % dimension);
	return number;
}
void spawn_snake()
{//Spawn the snake
	snake.push_back(snk);
	snake[0].setPosition(sf::Vector2f(lenght*grid / 2, height*grid / 2));
	for (int i = 1; i <n; i++)
	{
		sf::Vector2f poz = snake[i - 1].getPosition();
		snake.push_back(snk);
		snake[i].setPosition(poz.x + grid, poz.y);

	}

}
void Respawn()
{
	food.setPosition(sf::Vector2f(Random(lenght*grid - 25), Random(height*grid - 25)));
	for (int i = 0; i < snake.size(); i++)
		if (food.getGlobalBounds().intersects(snake[i].getGlobalBounds()))
			Respawn();
}
void Grow()
{	//Grow the snake after it eats food
	sf::Vector2f poz = snake[snake.size() - 1].getPosition();
	snake.push_back(snk);
	snake[snake.size() - 1].setPosition(poz.x + grid, poz.y);
}
void EAT()
{	//Eat the food
	if (snake[0].getGlobalBounds().intersects(food.getGlobalBounds()))
		{	Grow();
			points++;  
			Respawn();
		}
}
void DIE()
{
	for(int i=1;i<snake.size();i++)
			if (snake[0].getGlobalBounds().intersects(snake[i].getGlobalBounds()))
				{
				
				isPlaying = 0;

				}
}

int ChangeDIR()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && direction != 2) return 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && direction != 1) return 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && direction != 4) return 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && direction != 3) return 4;
	return direction;
}
void wall()
{	//Wall = Portal to the oposite wall
	sf::Vector2f poz = snake[0].getPosition();
	if (poz.x < 0) 
		{ snake[0].setPosition(lenght*grid, poz.y); }

	if (poz.x > lenght*grid) 
		{ snake[0].setPosition(0.f, poz.y); }

	if (poz.y < 0) 
		{ snake[0].setPosition(poz.x,height*grid); }

	if (poz.y > height*grid) 
		{ snake[0].setPosition(poz.x, 0.f); }

}
void move_the_snake(int &dir)
{// Movement
					//*******
	
		if (dir == 1) //Up
				{for (int i = snake.size() - 1; i >= 1; i--)
							{
								sf::Vector2f poz = snake[i - 1].getPosition();
								snake[i].setPosition(poz.x, poz.y);
							}
					snake[0].move(0.f, -grid);
				}
	                //*******

		if (dir == 2) //Down
				{for (int i = snake.size() - 1; i >= 1; i--)
					{
						sf::Vector2f poz = snake[i - 1].getPosition();
						snake[i].setPosition(poz.x, poz.y);
					}
					snake[0].move(0.0f, grid);
					}
		           //*******

		if (dir == 3) //Left
				{for (int i = snake.size() - 1; i >= 1; i--)
					{
						sf::Vector2f poz = snake[i - 1].getPosition();
						snake[i].setPosition(poz.x, poz.y);
					}
					snake[0].move(-grid, 0.0f);
					}
			       //*******

		if (dir == 4) //Right
					{for (int i = snake.size() - 1; i >= 1; i--)
						{
							sf::Vector2f poz = snake[i - 1].getPosition();
							snake[i].setPosition(poz.x, poz.y);
						}
						snake[0].move(grid, 0.0f);
					}


		}

void reset_game()
{
	isPlaying = 1;
	points = 0;
	snake.clear();
	spawn_snake();
}
	
int main()
{	//Text
			//Check if the font loaded 
		if (!font.loadFromFile("Under My Umbrella DEMO.otf")) 
				{ std::cout << "error : font not loaded"; }
		if (!font1.loadFromFile("KIN668.TTF"))
				{ std::cout << "error : font1 not loaded"; }
			//Text customisation
		int size = 60;
		text.setFont(font);
		text.setString("GAME OVER!");
		text.setCharacterSize(size);
		text.setPosition(sf::Vector2f(lenght*grid / 2, height*grid / 2-size));
		float width = text.getLocalBounds().width;
		text.move(sf::Vector2f(-(width/2), 0.f));
		text.setFillColor(sf::Color::Red);
			//Score customisation
		score.setFont(font1);
		score.setFillColor(sf::Color::White);
		score.setCharacterSize(20);
		score.setPosition(sf::Vector2f(5.f, 5.f));
			//title customizatoin
		title.setFont(font);
		title.setString("SNAKE");
		title.setFillColor(sf::Color::Green);
		title.setCharacterSize(150);
		title.setPosition(sf::Vector2f(lenght*grid / 2 -150, height*grid / 2 - 150));
			//credits customizatoin
		credit.setFont(font1);
		credit.setString("C�t�lin Andrei Preda");
		credit.setFillColor(sf::Color::White);
		credit.setCharacterSize(20);
		credit.setPosition(sf::Vector2f(lenght*grid / 2 -125 , height*grid-65));


	//food 
	food.setFillColor(sf::Color::Red);
		//->Spawn food
		food.setPosition(sf::Vector2f(100.0f,100.0f));
	//snk
	snk.setFillColor(sf::Color::Green);
		//Spawn the snake
		spawn_snake();
	//the game loop
	window.setFramerateLimit(30);

	
		while (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event))
					{
						if ( (event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) )
							window.close();
					}
				
				//Wipe the screen
				window.clear();
				
				if (isPlaying == 3)
				{
					window.draw(title);
					window.draw(credit);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) isPlaying = 1;


				}
				if(isPlaying==1)
				{
				
					//seed random numbers
					srand(time(0));
					//movement
					direction = ChangeDIR();
					move_the_snake(direction);
					
					// Eat, Grow & Die   ...teleport as well	
					EAT();
					wall();
					DIE();
					//Points
					std::ostringstream string;
					string << "Points : " << points;
					score.setString(string.str());
					//Draw the snake
					for (int i = 0; i<snake.size(); i++)
						window.draw(snake[i]);
					//Draw the food
					window.draw(food);
					//Draw the score
					window.draw(score);
					
				}
				if (isPlaying == 0) {
					
					window.draw(text);
					
					direction = 7;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
					reset_game();

				}

				//Display
				window.display();
				
			}
	
}