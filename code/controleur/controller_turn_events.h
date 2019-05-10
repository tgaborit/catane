/**
* \file controller_turn_events.h
* \brief
* \author Titouan Gaborit
* \date 4 mai 2019
*
*
*
*/

#ifndef CATANE_CONTROLLER_TURN_EVENTS_H
#define CATANE_CONTROLLER_TURN_EVENTS_H

#include <SDL.h>
#include "modele/headers/partie.h"

void craftDevEvent(Partie* the_game);
void craftRoadEvent(Partie* the_game, SDL_Window* window, SDL_bool* program_launched);
void craftSettleEvent(Partie* the_game, SDL_Window* window, SDL_bool* program_launched);
void craftCityEvent(Partie* the_game, SDL_Window* window, SDL_bool* program_launched);

void useKnightEvent(Partie* the_game, SDL_Window* window, SDL_bool* program_launched);
void useMonopEvent(Partie* the_game, SDL_Window* window, SDL_bool* program_launched);
void useInventEvent(Partie* the_game, SDL_Window* window, SDL_bool* program_launched);
void useRoadsEvent(Partie* the_game, SDL_Window* window, SDL_bool* program_launched);
void useUnivEvent(Partie* the_game);

void rollDiceEvent(Partie* the_game, SDL_Window* window, SDL_bool* program_launched);
void endTurnEvent(Partie* the_game);

void activateRobberEvent(Partie* the_game, SDL_Window* window, SDL_bool* program_launched);

#endif //CATANE_CONTROLLER_TURN_EVENTS_H
