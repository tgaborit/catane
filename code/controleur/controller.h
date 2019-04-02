/**
* \file controller.h
* \brief En-tête générale du contrôleur
* \author Titouan Gaborit
* \date 27 mars 2019
*
* En-tête déclarant les fonctions générales du contrôleur ainsi que la définition des macros générales.
*/

#ifndef CATANE_CONTROLLER_H
#define CATANE_CONTROLLER_H

/**
* \def WINDOWW
* Définit la largeur de la fenêtre
*/
#define WINDOWW 1920

/**
* \def WINDOWH
* Définit la hauteur de la fenêtre
*/
#define WINDOWH 950

SDL_bool isInArea(SDL_MouseButtonEvent mouse_button, SDL_Rect area);

void quitProgram(SDL_bool * pprogram_launched);

void SDL_ExitWithError(const char *message);

#endif //CATANE_CONTROLLER_H
