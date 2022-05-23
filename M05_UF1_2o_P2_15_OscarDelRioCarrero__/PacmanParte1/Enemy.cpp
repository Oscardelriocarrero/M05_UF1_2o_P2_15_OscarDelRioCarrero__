#include "Enemy.h"

void Enemy::RandomDirection()
{
	int random = rand() % 4;
	switch (random)
	{
	case 0:
		direction = { 0,1 };
		break;
	case 1:
		direction = { 0,-1 };
		break;
	case 2:
		direction = { 1,0 };
		break;
	case 3:
		direction = { -1,0 };
		break;
	}
}

Enemy::Enemy()
{
	spawn = { 0,0 };
	position = spawn;
	direction = { 0,0};
	character = 'x';
	background = ConsoleUtils::CONSOLE_COLOR::BLACK;
	foreground = ConsoleUtils::CONSOLE_COLOR::BLACK;
}

Enemy::Enemy(COORD _spawn, float _spawn_countdown)
{
	spawn_countdown = TimeManager::getInstance().time + _spawn_countdown;
	spawn = _spawn;
	position = spawn;
	direction = { 0,0 };
	character = 'x';

	powerUp_countdown = 0;

	background = ConsoleUtils::CONSOLE_COLOR::BLACK;
	foreground = ConsoleUtils::CONSOLE_COLOR::BLACK;

	foreground_powerUp = ConsoleUtils::CONSOLE_COLOR::CYAN;
	foreground_noPowerUp = ConsoleUtils::CONSOLE_COLOR::RED;
}

void Enemy::PowerUpPicked()
{
	powerUp_countdown = TimeManager::getInstance().time + powerUpTime;
}

Enemy::ENEMY_STATE Enemy::update(Map* _map, COORD playerPos)
{
	ENEMY_STATE state = ENEMY_STATE::ENEMY_NORMAL;
	if (spawn_countdown < TimeManager::getInstance().time)
	{
		RandomDirection();

		COORD newPosition = position;
		newPosition.X += direction.X;
		newPosition.Y += direction.Y;

		if (newPosition.X < 0)
		{
			newPosition.X = _map->Width - 1;
		}
		newPosition.X %= _map->Width;
		if (newPosition.Y < 0)
		{
			newPosition.Y = _map->Height - 1;
		}
		newPosition.Y %= _map->Height;

		switch (_map->GetTile(newPosition.X, newPosition.Y))
		{
		case Map::MAP_TILES::MAP_WALL:
			newPosition = position;
			break;
		}

		position = newPosition;

		if (position.X == playerPos.X && position.Y == playerPos.Y)
		{
			if (powerUp_countdown <= TimeManager::getInstance().time)
			{
				state = ENEMY_STATE::ENEMY_EATEN;
			}
			else
			{
				state = ENEMY_STATE::ENEMY_KILLED;
			}
		}

		if (powerUp_countdown <= TimeManager::getInstance().time)
		{
			foreground = foreground_noPowerUp;
		}
		else
		{
			foreground = foreground_powerUp;
		}
	}
	
	return state;
}

void Enemy::Kill()
{
	position = spawn;
	spawn_countdown = TimeManager::getInstance().time + spawnTime;
}

void Enemy::Draw()
{
	if(spawn_countdown < TimeManager::getInstance().time)
	{
		ConsoleUtils::Console_SetPos(position);
		ConsoleUtils::Console_SetColor(foreground, background);
		std::cout << character;
	}
}
