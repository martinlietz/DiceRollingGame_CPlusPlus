#include <iostream>
#include <string>
#include "DiceRollingGame.cpp"

using namespace std;

int main()
{
    DiceRollingGame game; // Create a DiceRollingGame object
    game.start();
    while(game.running == 1)
    {
        game.play();
    }
    return 0;
}
