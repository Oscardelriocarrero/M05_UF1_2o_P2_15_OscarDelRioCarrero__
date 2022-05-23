#pragma once
#include "ConsoleUtils.h"
#include "Map.h"
#include "TimeManager.h"
#include <stdlib.h>
#include <time.h>

class Enemy
{
	const float powerUpTime = 15;
	float powerUp_countdown;
	const float spawnTime = 10;
	float spawn_countdown;
	COORD spawn;
	COORD position;
	COORD direction;
	char character;
	ConsoleUtils::CONSOLE_COLOR background;
	ConsoleUtils::CONSOLE_COLOR foreground;

	ConsoleUtils::CONSOLE_COLOR foreground_powerUp;
	ConsoleUtils::CONSOLE_COLOR foreground_noPowerUp;
	void RandomDirection();

public:
	enum ENEMY_STATE { ENEMY_NORMAL, ENEMY_EATEN, ENEMY_KILLED };
	Enemy();
	Enemy(COORD _spawn, float _spawn_countdown = 10);
	void PowerUpPicked();
	ENEMY_STATE update(Map* _map, COORD playerPos);
	void Kill();
	void Draw();
};

