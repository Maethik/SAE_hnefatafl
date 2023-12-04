#include <iostream>
#include <sstream>

#include "typeDef.h"
#include "functions.h"
#include "tests.h"

using namespace std;

bool captureKingScenario()
{
    PlayerRole thePlayer = ATTACK;
    Position thePosition, newPosition;
    Cell theBoard[BOARD_SIZE_MAX][BOARD_SIZE_MAX];

    resetBoard(theBoard, LITTLE);

    theBoard[5][6].itsPieceType = KING;
    theBoard[9][7].itsPieceType = SWORD;
    theBoard[5][8].itsPieceType = SHIELD;
    theBoard[5][5].itsCellType = CASTLE;

    displayBoard(theBoard, LITTLE);

    cout << thePlayer << " play !" << endl;
    do
    {
        cout << "Which pawn do you want to move? ";
        thePosition = getPositionFromInput();
    } while (isEmptyCell(theBoard, thePosition) || !isValidPosition(thePosition, LITTLE));

    do
    {
        cout << "Where? ";
        newPosition = getPositionFromInput();
    } while (!isValidMovement(thePlayer, theBoard, thePosition, newPosition));

    movePiece(theBoard, thePosition, newPosition);

    clearConsole();

    capturePieces(thePlayer, theBoard, LITTLE, newPosition);
    displayBoard(theBoard, LITTLE);

    if (isKingCaptured(theBoard, LITTLE) || !isSwordLeft(theBoard, LITTLE) || isKingEscaped(theBoard, LITTLE))
        return true;
    else
        return false;
}

bool capturePieceScenario()
{
    PlayerRole thePlayer = DEFENSE;
    Position thePosition, newPosition;
    Cell theBoard[BOARD_SIZE_MAX][BOARD_SIZE_MAX];

    resetBoard(theBoard, LITTLE);

    theBoard[0][2].itsPieceType = SWORD;
    theBoard[0][1].itsPieceType = SHIELD;
    theBoard[3][3].itsPieceType = SHIELD;
    theBoard[0][0].itsCellType = FORTRESS;
    theBoard[5][5].itsPieceType = KING;

    displayBoard(theBoard, LITTLE);

    cout << thePlayer << " play !" << endl;
    do
    {
        cout << "Which pawn do you want to move? ";
        thePosition = getPositionFromInput();
    } while (isEmptyCell(theBoard, thePosition) || !isValidPosition(thePosition, LITTLE));

    do
    {
        cout << "Where? ";
        newPosition = getPositionFromInput();
    } while (!isValidMovement(thePlayer, theBoard, thePosition, newPosition));

    movePiece(theBoard, thePosition, newPosition);

    clearConsole();

    capturePieces(thePlayer, theBoard, LITTLE, newPosition);
    displayBoard(theBoard, LITTLE);

    if (!isSwordLeft(theBoard, LITTLE) || isKingCaptured(theBoard, LITTLE) || isKingEscaped(theBoard, LITTLE))
        return true;
    else
        return false;
}

bool kingEscapedScenario()
{
    PlayerRole thePlayer = DEFENSE;
    Position thePosition, newPosition;
    Cell theBoard[BOARD_SIZE_MAX][BOARD_SIZE_MAX];

    resetBoard(theBoard, LITTLE);

    theBoard[0][2].itsPieceType = SWORD;
    theBoard[0][0].itsCellType = FORTRESS;
    theBoard[0][10].itsCellType = FORTRESS;
    theBoard[0][1].itsPieceType = KING;

    displayBoard(theBoard, LITTLE);

    cout << thePlayer << " play !" << endl;
    do
    {
        cout << "Which pawn do you want to move? ";
        thePosition = getPositionFromInput();
    } while (isEmptyCell(theBoard, thePosition) || !isValidPosition(thePosition, LITTLE));

    do
    {
        cout << "Where? ";
        newPosition = getPositionFromInput();
    } while (!isValidMovement(thePlayer, theBoard, thePosition, newPosition));

    movePiece(theBoard, thePosition, newPosition);

    clearConsole();

    capturePieces(thePlayer, theBoard, LITTLE, newPosition);
    displayBoard(theBoard, LITTLE);

    if (!isSwordLeft(theBoard, LITTLE) || isKingCaptured(theBoard, LITTLE) || isKingEscaped(theBoard, LITTLE))
        return true;
    else
        return false;
}
