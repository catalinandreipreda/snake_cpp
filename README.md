# snake_cpp
![Screenshot from the game](Screenshots/Snake.png)
## Simple Snake game I made with C++ and SFML

Archive of old high-school project and first exposure to 2D graphics or game development.

To run the game, use the snake.exe application in snake_cpp\Release. The game should start with a welcome screen, to start playing press the 'enter' key.
![Screenshot from the game](Screenshots/Snake_start.png)

You can change the direction of the snake by pressing the WASD keys. Once started, it moves at a constant pace, which is easy to manage in the begining, but the difficulty rises when the tail gets very long.
When the snake is heading to a window's edge, it will emerge form the opposite side of the screen.

Food will spawn in random locations. A collision between the snake and the food will grow the snake, increase your score and respawn the food in a new location.

When the head of the snake hits an element of the tail, you lose and the Game Over screen is triggered. 
![Screenshot from the game](Screenshots/Snake_Game_Over.png)

The objective is simple: get the highest score possible
