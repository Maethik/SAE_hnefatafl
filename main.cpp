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
#include "scenario.h"

using namespace std;

void launchTests()
{
    cout << endl << "********* Start testing *********" << endl << endl;
    test_chooseSizeBoard();
    test_initializeBoard();
    test_getPositionFromInput();
    test_isValidPosition();
    test_isEmptyCell();
    test_isValidMovement();
    test_movePiece();
    test_capturePieces();
    test_isSwordLeft();
    test_getKingPosition();
    test_isKingEscaped();
    test_isKingCaptured();
    cout << endl << "********** End testing **********" << endl << endl;
}

void launchScenarios()
{

    while (!kingEscapedScenario())
    {
        cout << endl;
    }
    cout << "La partie est finit" << endl;
}

void playGame()
{
    BoardSize selectedSize = BIG;
    Position thePosition, newPosition;
    PlayerRole thePlayer = ATTACK;

    Cell theBoard[selectedSize][BOARD_SIZE_MAX];

    displayHnefataflLogo();
    chooseSizeBoard(selectedSize);
    initializeBoard(theBoard, selectedSize);
    displayBoard(theBoard, selectedSize);

    do
    {
        cout << thePlayer << " play !" << endl;
        do
        {
            cout << "Which pawn do you want to move? ";
            thePosition = getPositionFromInput();
        } while (isEmptyCell(theBoard, thePosition) || !isValidPosition(thePosition, selectedSize));

        do
        {
            cout << "Where? ";
            newPosition = getPositionFromInput();
        } while (!isValidMovement(thePlayer, theBoard, thePosition, newPosition));

        movePiece(theBoard, thePosition, newPosition);

        clearConsole();

        char beginPos = thePosition.itsRow + 'A', endPos = newPosition.itsRow + 1;
        cout << thePlayer << " move " << theBoard[newPosition.itsRow][newPosition.itsCol].itsPieceType << " in " << beginPos << thePosition.itsCol + 1 << " to " << endPos << newPosition.itsCol + 1 << endl;

        capturePieces(thePlayer, theBoard, selectedSize, newPosition);
        displayBoard(theBoard, selectedSize);


        switch (thePlayer)
        {
        case ATTACK: thePlayer = DEFENSE; break;
        case DEFENSE: thePlayer = ATTACK; break;
        }
    } while (isSwordLeft(theBoard, selectedSize) || !isKingEscaped(theBoard, selectedSize) || !isKingCaptured(theBoard, selectedSize));
}

int main()
{
    // Uncomment the line below to run tests
    //launchTests();
    // Launch scenarios
    launchScenarios();
    // Start the game
    //playGame();

    return 0;
}
