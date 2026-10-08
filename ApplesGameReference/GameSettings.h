#pragma once
#include <string>

namespace ApplesGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";

	// Game settings constants
	const float PLAYER_SIZE = 20.f;
	const float APPLE_SIZE = 20.f;
	const float WALL_SIZE = 25.f;
	const float INITIAL_SPEED = 100.f;
	const float ACCELERATION = 10.f; // For each eaten apple player speed will be increased by this value
	const int NUM_APPLES = 20;
	const int NUM_WALLS = 10;
	const unsigned int SCREEN_WIDTH = 1920;
	const unsigned int SCREEN_HEGHT = 1080;
}
