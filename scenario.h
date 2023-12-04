#ifndef SCENARIO_H
#define SCENARIO_H

#include "typeDef.h"

/**
 * @brief Scenario execution function for capturing the king
 *
 * @return True if the game is finished and flase otherwise
 */
bool captureKingScenario();

/**
 * @brief Scenario execution function for pawn capture
 *
 * @return True if the game is finished and flase otherwise
 */
bool capturePieceScenario();

/**
 * @brief Scenario execution function for the situation where the king escapes
 *
 * @return True if the game is finished and flase otherwise
 */
bool kingEscapedScenario();

#endif // SCENARIO_H
