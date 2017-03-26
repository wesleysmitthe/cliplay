/************************************************
 * Autor: Wesley Smitthe						*
 * Descrição: Reprodutor de áudio CLI usando SDL* 
 * Linguagem: C									*
 * Data:  X/12/2016								*
 * **********************************************/

/// Headers
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


int main(int argc, char *argv[]){
	Uint16 formato = AUDIO_S16SYS;							/**  Variaveis para as 		*/
	int frequencia = 44100, canal = 2, buffer = 4096;		/**  Configuracoes de som 	*/

	int contador = 1;	/// Usado para contar as musicas


	SDL_Init(SDL_INIT_AUDIO);  ///  Inicializa a SDL_main
	Mix_Music *musica;	       ///  Cria a instacia para receber a musica


	/// 			44100	 AUDIO_S16_SYS    2     4096
	Mix_OpenAudio(frequencia,   formato,    canal, buffer);


	if(argc == 1){
		perror("\nerro");
		printf("Passe as musicas que deseja tocar como argumento. ex: ./cliplay musica.mp3");
		
		exit(1);
		}


	Mix_VolumeMusic(128);  /// Coloca o volume da musica no maximo
	
	
	/****************************************************
	 * Verfica se foi passado o argumento -r(random)	*
	 *  caso tenha passado muda a sequencia de			*
	 *  reprodução das musicas - "toca aleatoriamente"  *
	 * **************************************************/
	if(!strcmp(argv[1],"-r")){
		printf("\nReproduzir aleatoriamnte\n");
		
		for(int cont = 1; cont < argc; cont++)
			argv[cont] = argv[cont+1];
		
		argc--;
		
		char *auxiliar;
		int aleatorio;
		
		srand(time(NULL));		/// Planta a semente 
		
		for(int cont = 1; cont < argc; cont++){
			aleatorio = rand() % argc;
		
			if(aleatorio == 0)
				continue;
		
			auxiliar = argv[cont];
			argv[cont] = argv[cont];
			argv[aleatorio] = auxiliar;
			}
		}
	
	printf("\nTotal de Musicas na fila: %d", argc);

	/// Repete enquanto ainda estiver musicas na fila para tocar
	while(contador <= argc){
		musica = Mix_LoadMUS(argv[contador]);	/// Carrega a musica

		Mix_PlayMusic(musica, 0);	/// Reproduz a Musica

		printf("\nReproduzindo %s\n", argv[contador]);


		while(Mix_PlayingMusic()){
			/// Roda ate a musica chegar ao fim ou seja interrompida
			}

		contador++;
		}


	Mix_FreeMusic(musica);	/// Libera a memória usada pela instâcia de SDL_mix
	SDL_Quit();				/// Fecha SDL_main
	
	return 0;
	}
