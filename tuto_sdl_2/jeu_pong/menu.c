#include <SDL2/SDL.h>
#include "formes.h"
#include<stdio.h>
int menu(SDL_Window *window, SDL_Renderer *renderer) {
    
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ExitWithError("initialisation SDL");
	//création fenêtre + rendu
	int width = 0;
	int height = 0;
	// ici on initialise la fenetre en fullscreen
	if (SDL_CreateWindowAndRenderer(width,height, SDL_WINDOW_MAXIMIZED, &window, &renderer) != 0) 
		SDL_ExitWithError("Impossible de creer rendu et fenêtre");
	// on recupere la taille de la fenetre
	width = SDL_GetWindowSurface(window)->w;
	height = SDL_GetWindowSurface(window)->h;

	SDL_Rect facile = createRect(width/3, height/5, width/3, height/15);
	SDL_Rect normal = createRect(width/3, height/5 + 2* height/15, width/3, height/15);
	SDL_Rect hardcore = createRect(width/3, height/5 + 4* height/15, width/3, height/15);
	SDL_Rect quitter = createRect(width/3, height/5+ 6* height/15, width/3, height/15);

    int choix = 0;
	int continuer = 1;
	int x = width/3.3-50, y= height/4.3 , r = 10;
	
	while(continuer) {
		// on affiche les menus
		SDL_SetRenderDrawColor(renderer, 0,0,0,0);
		SDL_RenderClear(renderer);
		if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) !=0)
			SDL_ExitWithError("Il n'est pas possible de changer la couleur");
		if (SDL_RenderFillRect(renderer,&facile) !=0 )
			SDL_ExitWithError("Impossible de creer le menu facile");
		if (SDL_RenderFillRect(renderer,&normal) !=0 )
			SDL_ExitWithError("Impossible de creer le menu normal");
		if (SDL_RenderFillRect(renderer,&hardcore) !=0 )
			SDL_ExitWithError("Impossible de creer le menu hardcore");
		if (SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE) !=0)
			SDL_ExitWithError("Il n'est pas possible de changer la couleur");
		if (SDL_RenderFillRect(renderer,&quitter) !=0 )
			SDL_ExitWithError("Impossible de creer le menu hardcore");
		
		SDL_Event evenement; //tous nos evenements seront gérés à partir de cette ligne
		while(SDL_PollEvent(&evenement))//fonction qui va capturer, enregistrer tous les evenements
		{
			switch(evenement.type)
			{
				case SDL_KEYDOWN:
					switch(evenement.key.keysym.sym)
					{
						case SDLK_UP:
							if(y<=height/3) {
								y = height/4.3+6*height/15;
							}
							else {
								y-=2*height/15;
							}
						break;

						case SDLK_DOWN:
							if(y>= 8*height/15) {
								y = height/4.3;
							}
							else {
								y+=2*height/15;
							}
						break;
						case SDLK_RETURN:
							if(y>=height/4.3 && y<=height/4.3+2*height/15) {
								choix = 1;
							}
							if(y>=height/4.3+2*height/15 && y<=height/4.3+2*height/15+3*height/15) {
								choix = 2;
							}
							if(y>=height/4.3+4*height/15) {
								choix = 3;
							}
							printf("choix : %d\n", choix);
							continuer = 0;
					}
				break;
			}
		}

        ellipse(renderer, x, y, r, r);


		SDL_RenderPresent(renderer); 

	}
    return choix;
}
