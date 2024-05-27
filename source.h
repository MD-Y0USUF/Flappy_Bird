#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include <iostream>
class Images {
public:
	Image piller_up = LoadImage("src/top.png");
	Image piller_down = LoadImage("src/bottom.png");
	Image bird = LoadImage("src/birds.png");
	Image bacground_sky = LoadImage("src/bg.png");
	Image ground = LoadImage("src/landSpace_final.png");
	Image land = LoadImage("src/ground.png");
	Image score_board = LoadImage("src/scor.png");
	Image game_over = LoadImage("src/gameover.png");
};

