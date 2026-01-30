🎮 Brick Mania

Classic Brick-Breaker Game with Power-Ups
Personal Project | C++ | OpenGL (GLEW & GLUT)

📌 Project Overview

Brick Mania is a 2D arcade-style game where the player controls a ball to break stacked bricks 🧱. The goal is to clear all blocks to win while leveraging power-ups and shields for an engaging gameplay experience. This project demonstrates game logic, collision handling, and OOP principles in action.

🎯 Objectives

Implement smooth ball and paddle mechanics.

Introduce interactive power-ups (enlarge paddle, shield, multi-ball).

Randomize brick layouts for each playthrough.

Apply OOP concepts like classes, inheritance, and encapsulation.

Develop a fun, replayable arcade game with graphics using OpenGL.

🧱 Game Mechanics
Ball & Paddle

The ball bounces off walls, bricks, and paddle.

Missing the ball reduces player lives.

Paddle movement is controlled via arrow keys (← →).

Bricks

Multiple bricks are stacked at the top.

Some bricks require multiple hits to break.

Clearing all bricks results in victory.

⚡ Power-Ups

Enlarge Paddle – Makes controlling the ball easier.

Shield 🛡️ – Prevents the ball from falling at the bottom.

Multi-ball – Adds extra balls to speed up brick clearing.

Score Boost – Temporarily increases points earned.

🧩 Features

Randomized brick layouts every game.

Animated menus and interactive UI.

Smooth collision detection for ball and bricks.

Replayable and addictive arcade gameplay.

💻 Technologies Used

C++ – Core game logic

OpenGL, GLEW, GLUT – Graphics rendering

OOP Principles – Classes, inheritance, encapsulation, modular design

⚙️ Rules

Start with 3 lives; losing a ball reduces one life.

Clear all bricks to win the game.

Collect power-ups as they appear randomly.

Bricks may require more than one hit.

Game ends if all lives are lost or all bricks are cleared.

🛠️ How to Run

Clone the repository:

git clone https://github.com/username/brick-mania.git


Compile using g++:

g++ *.cpp -lGL -lGLEW -lGLUT -o BrickMania


Run the game:

./BrickMania

🚀 Final Note

Brick Mania combines classic arcade fun with modern OOP design, demonstrating how clean coding and fundamental principles can create an enjoyable and interactive gaming experience.
