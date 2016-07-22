//Stacks and Queues
//Copyright © 2016 Team SQ. All rights reserved.

//Globals.hpp

#ifndef Globals_hpp
#define Globals_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "ResourcePath.hpp"

using namespace std;

extern std::string rPath;
extern sf::RenderWindow* window;
extern float RES_X;
extern float RES_Y;
extern float RES_Y2;

/*pathCoords info:
 Applies to the vector index of the following:
 (top left x-coordinate) mod 5 = 0
 (top left y-coordinate) mod 5 = 1
 (bottom right x-coordinate) mod 5 = 2
 (bottom right y-coordinate) mod 5 = 3
 (allowed direction) mod 5 = 4
 */
extern std::vector<float> pathCoords;

/*
 Movement index:
 */
extern float leftF; //1.0
extern float upF; //2.0
extern float downF; //3.0

/*
 Level info:
*/
extern std::vector<int> lockedLevels;
extern std::vector<float> inTubePositionX;
extern std::vector<float> inTubePositionY;
extern std::vector<float> ballsPeriod; /* Balls appear on screen every x seconds. */
extern std::vector<float> ballsVX; /* Respective vx of balls in a level by level number. */
extern std::vector<float> ballsRadii;

#endif /* Globals_hpp */
