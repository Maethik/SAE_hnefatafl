/**
* @file main.cpp
*
* @brief Implementation of the Hnefatafl game.
*
* This file contains the implementation of the Hnefatafl game, including setup, gameplay, and outcome
determination.
* It also provides a testing suite for various game functions.
*
* @author MG
* @date 06/11/23
*/

#include <iostream>
#include "typeDef.h"
#include "functions.cpp"
#include "tests.h"

using namespace std;

void launchTests()
{
    cout << endl << "********* Start testing *********" << endl << endl;
    test_capturePieces();
    cout << endl << "********** End testing **********" << endl << endl;
}

void playGame()
{

}

int main()
{
    // Uncomment the line below to run tests
    launchTests();
    // Start the game
    //playGame();

    return 0;
}
