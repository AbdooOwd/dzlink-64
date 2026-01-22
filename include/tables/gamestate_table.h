/*
 * DEFINE_GAMESTATE's arguments:
 *    - argument 1: the name of the game state's struct type
 *    - argument 2: the game state's ID name in the enum
 * */

DEFINE_GAMESTATE(Setup, GAMESTATE_SETUP) // must be here for game initialization
DEFINE_GAMESTATE(Dev, GAMESTATE_DEV)
DEFINE_GAMESTATE(Play, GAMESTATE_PLAY)
