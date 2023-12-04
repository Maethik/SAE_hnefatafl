/**
* @file functions.cpp
*
* @brief Implementation of the Hnefatafl game's functions.
*
* @author MG
* @date 06/11/23
*/

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <limits>
#include <climits>
#include <cmath>

using namespace std;

#include "typeDef.h"
#include "functions.h"

void clearConsole()
{
    #ifdef __WIN32
       system("cls");
    #elif __APPLE__
       system("clear");
    #elif __linux__
        system("clear");
    #endif
}

void displayHnefataflLogo()
{
    // display the Hnefatafl logo
    cout << R"(
██░ ██  ███▄    █ ▓█████   █████▒▄▄▄     ▄▄▄█████▓ ▄▄▄        █████▒██▓
▓██░ ██▒ ██ ▀█   █ ▓█   ▀ ▓██   ▒▒████▄   ▓  ██▒ ▓▒▒████▄    ▓██   ▒▓██▒
▒██▀▀██░▓██  ▀█ ██▒▒███   ▒████ ░▒██  ▀█▄ ▒ ▓██░ ▒░▒██  ▀█▄  ▒████ ░▒██░
░▓█ ░██ ▓██▒  ▐▌██▒▒▓█  ▄ ░▓█▒  ░░██▄▄▄▄██░ ▓██▓ ░ ░██▄▄▄▄██ ░▓█▒  ░▒██░
░▓█▒░██▓▒██░   ▓██░░▒████▒░▒█░    ▓█   ▓██▒ ▒██▒ ░  ▓█   ▓██▒░▒█░   ░██████▒
 ▒ ░░▒░▒░ ▒░   ▒ ▒ ░░ ▒░ ░ ▒ ░    ▒▒   ▓▒█░ ▒ ░░    ▒▒   ▓▒█░ ▒ ░   ░ ▒░▓  ░
 ▒ ░▒░ ░░ ░░   ░ ▒░ ░ ░  ░ ░       ▒   ▒▒ ░   ░      ▒   ▒▒ ░ ░     ░ ░ ▒  ░
 ░  ░░ ░   ░   ░ ░    ░    ░ ░     ░   ▒    ░        ░   ▒    ░ ░     ░ ░
 ░  ░  ░         ░    ░  ░             ░  ░              ░  ░           ░  ░)" << endl << endl << endl;
}

bool chooseSizeBoard(BoardSize &aBoardSize)
{
    int sizeChoice;

    cout << "With witch size of board do you want to play ? (11 or 13): ";
    if (cin >> sizeChoice)
    {
        switch (sizeChoice)
        {
        case 11: aBoardSize = LITTLE; return true; break;
        case 13: aBoardSize = BIG; return true; break;
        default: return false;
        }
    }
    else
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }


}

void initializeBoard(Cell aBoard[][BOARD_SIZE_MAX], const BoardSize &aBoardSize)
{
    const string SMALLBOARD = "X00AAAAA00X00000A0000000000000000A0000D0000AA000DDD000AAA0DDKDD0AAA000DDD000AA0000D0000A0000000000000000A00000X00AAAAA00X";
    const string BIGBOARD = "X000AAAAA000X000000A0000000000000000000000000D000000A00000D00000AA00000D00000AAA0DDDKDDD0AAA00000D00000AA00000D00000A000000D0000000000000000000000000A000000X000AAAAA000X";

    int size, tempBoardInit = 0;
    string map;

    switch (aBoardSize)
    {
    case LITTLE: size = 11; map = SMALLBOARD; break;
    case BIG: size = 13; map = BIGBOARD; break;
    }

    // initialize the board according the size chosen before
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (map[tempBoardInit] == 'X')
            {
                aBoard[row][col].itsCellType = FORTRESS;
                aBoard[row][col].itsPieceType = NONE;
            }
            else if (map[tempBoardInit] == 'A')
            {
                aBoard[row][col].itsCellType = NORMAL;
                aBoard[row][col].itsPieceType = SWORD;
            }
            else if (map[tempBoardInit] == 'D')
            {
                aBoard[row][col].itsCellType = NORMAL;
                aBoard[row][col].itsPieceType = SHIELD;
            }
            else if (map[tempBoardInit] == 'K')
            {
                aBoard[row][col].itsCellType = CASTLE;
                aBoard[row][col].itsPieceType = KING;
            }
            else
            {
                aBoard[row][col].itsCellType = NORMAL;
                aBoard[row][col].itsPieceType = NONE;
            }
            tempBoardInit += 1;
        }
        cout << endl;
    }
}

void displayBoard(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    const string LITTLEBORDER = "   +---+---+---+---+---+---+---+---+---+---+---+";
    const string BIGBORDER = "   +---+---+---+---+---+---+---+---+---+---+---+---+---+";

    // some specifications about notation
    cout << endl << "K: King" << endl;
    cout << "S: Sword" << endl;
    cout << "A: Shield" << endl << endl;

    // display the top border
    if (aBoardSize == LITTLE)
    {
        cout << "     1   2   3   4   5   6   7   8   9  10  11" << endl;
        cout << "   +---+---+---+---+---+---+---+---+---+---+---+" << endl;
    } else
    {
        cout << "     1   2   3   4   5   6   7   8   9  10  11  12  13" << endl;
        cout << "   +---+---+---+---+---+---+---+---+---+---+---+---+---+" << endl;
    }

    // display the board according the initializeBoard function
    for (int row = 0; row < aBoardSize; row++)
    {
        char letter = 'A' + row;
        cout << letter << "  |";

        for (int col = 0; col < aBoardSize; col++)
        {
            if (aBoard[row][col].itsPieceType == KING)
            {
                cout << " K |";
            }
            else if (aBoard[row][col].itsCellType == CASTLE)
            {
                cout << " Q |";
            }
            else if (aBoard[row][col].itsCellType == FORTRESS)
            {
                cout << " X |";
            }
            else if (aBoard[row][col].itsPieceType == SWORD)
            {
                cout << " S |";
            }
            else if (aBoard[row][col].itsPieceType == SHIELD)
            {
                cout << " A |";
            }
            else if (aBoard[row][col].itsPieceType == NONE)
            {
                cout << "   |";
            }
        }

        // display  the bottom border
        switch (aBoardSize)
        {
        case LITTLE: cout << endl << LITTLEBORDER << endl; break;
        case BIG: cout << endl << BIGBORDER << endl; break;
        }
    }
}

Position getPositionFromInput()
{
    const int GAPUPPER = 65, GAPLOWER = 97;
    Position newPosition;
    int posLength = 0, resultConv = 0;
    string pos, numPosPart;

    cin >> pos;
    cout << endl;

    newPosition.itsRow = pos[0];

    // count the length of pos
    for (int i = 0; pos[i]!='\0'; i++)
    {
        posLength += 1;
    }

    // init numPosPart size
    if (posLength == 2)
        numPosPart = "0";
    else
        numPosPart = pow(10, (posLength-2));

    // extract the numerical part of pos
    for (int i = 1; i < posLength; i++)
    {
        // verify if numbers are not followed by a lettre
        if (!(pos[i]>='1' && pos[i]<='9'))
        {
            newPosition.itsRow = -1;
            newPosition.itsCol = -1;
        }
        else
        {
            numPosPart[i-1] = pos[i];
        }
    }

    // convert numPosPart to an integer
    for (int i = 0; i<posLength-1; i++)
    {
        resultConv = resultConv * 10 + (numPosPart[i] - '0');
    }
    newPosition.itsCol = resultConv - 1;

    // verifications about itsRow value
    if (newPosition.itsRow >= 'A' && newPosition.itsRow <= 'Z')
    {
        newPosition.itsRow -= GAPUPPER;
    }
    else if (newPosition.itsRow >= 'a' && newPosition.itsRow <= 'z')
    {
        newPosition.itsRow -= GAPLOWER;
    }
    else
    {
        newPosition.itsRow = -1;
        newPosition.itsCol = -1;
    }

    // verifications about itsCol value
    if (!(newPosition.itsCol >= 0 && newPosition.itsCol <= INT_MAX))
    {
        newPosition.itsRow = -1;
        newPosition.itsCol = -1;
    }

    //cout << "{" << newPosition.itsRow << ", " << newPosition.itsCol << "}" << endl;

    return newPosition;
}

bool isValidPosition(const Position& aPos, const BoardSize& aBoardSize)
{
    // check if the position is on the board
    if ((aPos.itsRow >= 0 && aPos.itsRow < aBoardSize) && (aPos.itsCol >= 0 && aPos.itsCol < aBoardSize))
        return true;
    else
    {
        cout << "This cell is not within the board !" << endl;
        return false;
    }
}

bool isEmptyCell(const Cell aBoard[][BOARD_SIZE_MAX], const Position& aPos)
{
    // check if the cell is empty
    if (aBoard[aPos.itsRow][aPos.itsCol].itsPieceType == NONE)
        return true;
    else
        return false;
}

bool isValidMovement(const PlayerRole& aPlayer, const Cell aBoard[][BOARD_SIZE_MAX],const Position& aStartPos,const Position& aEndPos)
{
    bool isKing = false;

    // if the selected pawn belongs to the player
    switch (aPlayer)
    {
    case ATTACK:
        switch (aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType)
        {
        case NONE: return false; break;
        case SHIELD: return false; cout << "Ce pion ne vous apartient pas !"; break;
        case KING: cout << "Ce pion ne vous apartient pas !"; return false; break;
        }
        break;
    case DEFENSE:
        switch (aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType)
        {
            case NONE: return false; break;
            case SWORD: cout << "Ce pion ne vous apartient pas !"; return false; break;
            case KING: isKing = true;
        }
        break;
    }

    // if the end position is on the path of the selected pawn
    if (!(aEndPos.itsRow == aStartPos.itsRow) && !(aEndPos.itsCol == aStartPos.itsCol))
    {
        cout << "Position inatteignable !";
        return false;
    }

    // if there are any obstacles in the path
    // if the movment is in a row
    if (aEndPos.itsRow == aStartPos.itsRow)
    {
        if (aEndPos.itsCol < aStartPos.itsCol)
        {
            for (int i = aStartPos.itsCol-1; i >= aEndPos.itsCol; i--)
            {
                switch (isKing)
                {
                case true:
                    switch (aBoard[aStartPos.itsRow][i].itsPieceType)
                    {
                    case SHIELD: return false; break;
                    case SWORD: return false; break;
                    }
                    break;

                default:
                    switch (aBoard[aStartPos.itsRow][i].itsPieceType)
                    {
                    case SHIELD: return false; break;
                    case SWORD: return false; break;
                    case KING: return false; break;
                    }
                    switch (aBoard[aStartPos.itsRow][i].itsCellType)
                    {
                    case FORTRESS: return false; break;
                    case CASTLE: return false; break;
                    }
                }
            }
        }
        else if (aEndPos.itsCol > aStartPos.itsCol)
        {
            for (int i = aStartPos.itsCol+1; i <= aEndPos.itsCol; i++)
            {
                switch (isKing)
                {
                case true:
                    switch (aBoard[aStartPos.itsRow][i].itsPieceType)
                    {
                    case SHIELD: return false; break;
                    case SWORD: return false; break;
                    }
                    break;

                default:
                    switch (aBoard[aStartPos.itsRow][i].itsPieceType)
                    {
                    case SHIELD: return false; break;
                    case SWORD: return false; break;
                    case KING: return false; break;
                    }
                    switch (aBoard[aStartPos.itsRow][i].itsCellType)
                    {
                    case FORTRESS: return false; break;
                    case CASTLE: return false; break;
                    }
                }
            }
        }
    }

    // if the movement is in a column
    if (aEndPos.itsCol == aStartPos.itsCol)
    {
        if (aEndPos.itsRow < aStartPos.itsRow)
        {
            for (int i = aStartPos.itsRow-1; i >= aEndPos.itsRow; i--)
            {
                switch (isKing)
                {
                case true:
                    switch (aBoard[i][aStartPos.itsCol].itsPieceType)
                    {
                    case SHIELD: return false; break;
                    case SWORD: return false; break;
                    }
                    break;

                default:
                    switch (aBoard[i][aStartPos.itsCol].itsPieceType)
                    {
                    case SHIELD: return false; break;
                    case SWORD: return false; break;
                    case KING: return false; break;
                    }
                    switch (aBoard[i][aStartPos.itsCol].itsCellType)
                    {
                    case FORTRESS: return false; break;
                    case CASTLE: return false; break;
                    }
                }
            }
        }
        else if (aEndPos.itsRow > aStartPos.itsRow)
        {
            for (int i = aStartPos.itsRow+1; i <= aEndPos.itsRow; i++)
            {
                switch (isKing)
                {
                case true:
                    switch (aBoard[i][aStartPos.itsCol].itsPieceType)
                    {
                    case SHIELD: return false; break;
                    case SWORD: return false; break;
                    }
                    break;

                default:
                    switch (aBoard[i][aStartPos.itsCol].itsPieceType)
                    {
                    case SHIELD: return false; break;
                    case SWORD: return false; break;
                    case KING: return false; break;
                    }
                    switch (aBoard[i][aStartPos.itsCol].itsCellType)
                    {
                    case FORTRESS: return false; break;
                    case CASTLE: return false; break;
                    }
                }
            }
        }
    }

    // esle return true
    return true;
}

void movePiece(Cell aBoard[][BOARD_SIZE_MAX], const Position& aStartPos, const Position& aEndPos)
{
    aBoard[aEndPos.itsRow][aEndPos.itsCol].itsPieceType = aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType;
    aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType = NONE;
}

void capturePieces(const PlayerRole& aPlayer, Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, const Position& aEndPos)
{
    // array storing the four coordinates of the cells adjacent to aEndPos
    int directions[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    Cell actualCell = aBoard[aEndPos.itsRow][aEndPos.itsCol];

    // check for potential capture on the four cells
    for (auto& dir : directions)
    {
        int currentRow = aEndPos.itsRow + dir[0];
        int currentCol = aEndPos.itsCol + dir[1];

        Cell checkToDelete = aBoard[currentRow + dir[0]][currentCol + dir[1]];

        // checks whether the cell two cells away contains the same piece as aEndPos,
        // if it is a castle but does not contain a king,
        // if it is a fortress,
        // if it contains a king and the player is DEFENDED,
        // if it contains a SHIELD and the current square contains a king
        if (checkToDelete.itsPieceType == actualCell.itsPieceType || (checkToDelete.itsCellType == CASTLE && checkToDelete.itsPieceType != KING) || checkToDelete.itsCellType == FORTRESS || (checkToDelete.itsPieceType == KING && aPlayer == DEFENSE) || (actualCell.itsPieceType == KING && checkToDelete.itsPieceType == SHIELD))
        {
            aBoard[currentRow][currentCol].itsPieceType = NONE;
        }
    }
}

bool isSwordLeft(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    // go through the board until you find a SWORD piece
    for (int row = 0; row < aBoardSize; row++)
    {
        for (int col = 0; col < aBoardSize; col++)
        {
            if (aBoard[row][col].itsPieceType == SWORD)
                return true;
        }
    }
    return false;
}

Position getKingPosition(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    // go through the board until you find the king piece
    Position kingPos;
    for (int row = 0; row < aBoardSize; row++)
    {
        for (int col = 0; col < aBoardSize; col++)
        {
            // if the king is here, we initialise kingPos at this position and turn it over
            if (aBoard[row][col].itsPieceType == KING)
            {
                kingPos.itsRow = row;
                kingPos.itsCol = col;
                return kingPos;
            }
        }
    }
    // otherwise, we return the default position
    kingPos.itsRow = -1;
    kingPos.itsCol = -1;
    return kingPos;
}

bool isKingEscaped(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    // we check if the king is on a fortress, if so we return true, if not we return false
    Position kingPos = getKingPosition(aBoard, aBoardSize);
    if (aBoard[kingPos.itsRow][kingPos.itsCol].itsCellType == FORTRESS)
        return true;
    return false;
}

bool isKingCaptured(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    bool north = false, east = false, south = false, west = false;
    Position kingPos = getKingPosition(aBoard, aBoardSize);

    // we check the capture conditions for the four sides
    if (aBoard[kingPos.itsRow - 1][kingPos.itsCol].itsPieceType == SWORD ||
        aBoard[kingPos.itsRow - 1][kingPos.itsCol].itsCellType == CASTLE ||
        aBoard[kingPos.itsRow - 1][kingPos.itsCol].itsCellType == FORTRESS ||
        kingPos.itsRow == 0)
        north = true;
    if (aBoard[kingPos.itsRow][kingPos.itsCol + 1].itsPieceType == SWORD ||
        aBoard[kingPos.itsRow][kingPos.itsCol + 1].itsCellType == CASTLE ||
        aBoard[kingPos.itsRow][kingPos.itsCol + 1].itsCellType == FORTRESS ||
        kingPos.itsCol == aBoardSize-1)
        east = true;
    if (aBoard[kingPos.itsRow + 1][kingPos.itsCol].itsPieceType == SWORD ||
        aBoard[kingPos.itsRow + 1][kingPos.itsCol].itsCellType == CASTLE ||
        aBoard[kingPos.itsRow + 1][kingPos.itsCol].itsCellType == FORTRESS ||
        kingPos.itsRow == aBoardSize-1)
        south = true;
    if (aBoard[kingPos.itsRow][kingPos.itsCol - 1].itsPieceType == SWORD ||
        aBoard[kingPos.itsRow][kingPos.itsCol - 1].itsCellType == CASTLE ||
        aBoard[kingPos.itsRow][kingPos.itsCol - 1].itsCellType == FORTRESS ||
        kingPos.itsCol == 0)
        west = true;

    if (north && east && south && west)
        return true;
    return false;
}
