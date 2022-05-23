#include "General.h"

/// <summary>
/// Sets the needed variables
/// </summary>
void Setup();
/// <summary>
/// Handles the inputs
/// </summary>
void Input();
/// <summary>
/// Handles the logic of the game
/// </summary>
void Logic();
/// <summary>
/// Draws the screen
/// </summary>
void Draw();

General general;

int main()
{
    Setup();
    while (general.run)
    {
        Input();
        Logic();
        Draw();
    }
}

void Setup()
{
    std::cout.sync_with_stdio(false);

    srand(time(NULL));

    int totalEnemies = 0;
    std::cout << "Cuantos enemigos quieres? ";
    std::cin >> totalEnemies;
    if (totalEnemies < 1)
        totalEnemies = 1;
    for (size_t i = 0; i < totalEnemies; i++)
    {
        general.enemies.push_back(Enemy(general.pacman_map.spawn_enemy, 5.0f * i));
    }

}

void Input()
{
    general.input = USER_INPUTS::NONE;
    if (ConsoleUtils::KeyPressed(VK_UP) || ConsoleUtils::KeyPressed('W'))
    {
        general.input = USER_INPUTS::UP;
    }
    if (ConsoleUtils::KeyPressed(VK_DOWN) || ConsoleUtils::KeyPressed('S'))
    {
        general.input = USER_INPUTS::DOWN;
    }
    if (ConsoleUtils::KeyPressed(VK_RIGHT) || ConsoleUtils::KeyPressed('D'))
    {
        general.input = USER_INPUTS::RIGHT;
    }
    if (ConsoleUtils::KeyPressed(VK_LEFT) || ConsoleUtils::KeyPressed('A'))
    {
        general.input = USER_INPUTS::LEFT;
    }
    if (ConsoleUtils::KeyPressed(VK_ESCAPE) || ConsoleUtils::KeyPressed('Q'))
    {
        general.input = USER_INPUTS::QUIT;
    }
}

void Logic()
{
    if (general.gameComplete || general.gameOver)
    {
        switch (general.input)
        {
        case QUIT:
            general.run = false;
            break;
        }
    }
    else
    {

        switch (general.input)
        {
        case QUIT:
            general.run = false;
            break;
        }

        general.player.Update(&general.pacman_map, general.input, &general.enemies);

        if (general.pacman_map.points <= 0)
        {
            general.gameComplete = true;
        }


        for (size_t i = 0; i < general.enemies.size(); i++)
        {
            switch (general.enemies[i].update(&general.pacman_map, general.player.position))
            {
            case Enemy::ENEMY_STATE::ENEMY_EATEN:
                general.player.position = general.player.spawn;
                general.player.life--;
                break;
            case Enemy::ENEMY_STATE::ENEMY_KILLED:
                general.enemies[i].Kill();
                general.player.points += 50;
                break;
            default:
                break;
            }
        }
        if (general.player.life <= 0) {
            general.gameOver = true;
        }
    }
}

void Draw()
{
    ConsoleUtils::Console_SetPos(0, 0);
    general.pacman_map.Draw();

    general.player.Draw();
    for (size_t i = 0; i < general.enemies.size(); i++)
    {
        general.enemies[i].Draw();
    }
    ConsoleUtils::Console_ClearCharacter({ 0,(short)general.pacman_map.Height });
    ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::CYAN);
    std::cout << "Puntuacion actual: " << general.player.points << " Puntuacion pendiente: " << general.pacman_map.points << std::endl;
    if (general.gameComplete)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::GREEN);
        std::cout << "YOU WIN!" << std::endl;
    }
    if (general.gameOver)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::RED);
        std::cout << "GAME OVER!" << std::endl;
    }

    std::cout << TimeManager::getInstance().framecount << std::endl;
    std::cout << TimeManager::getInstance().deltaTime << std::endl;
    std::cout << TimeManager::getInstance().time << std::endl;

    TimeManager::getInstance().NextFrame();
}