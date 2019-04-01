#ifndef FOOTBALL_CLUB_H_
#define FOOTBALL_CLUB_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define __STRICT_ANSI__

char* strdup(char* str);

// List node which contains information about one football player.
typedef struct Player {
	char *name;					// player's name
	char *position;				// player's game position
	int score;					// player's score
	int injured;				// indicator for injury (1 true, 0 false)
	struct Player *next;		// next list node
	struct Player *prev;		// previous list node
} Player;

// Structure which contains information about one football club.
typedef struct FootballClub {
	char *name;					// club's name
	Player *players;			// list with players in good shape
	Player *injured_players;	// list with injured players
	struct FootballClub *next;	// next list node
} FootballClub;

void remove_player(FootballClub *clubs, char *club_name, char *player_name);

int valid_score(int score) {
	if (score >= -100 && score <= 100)
		return score;
	else if (score > 100)
		return 100;
	return -100;
}

void new_player(Player **player, char* name, char *position,
								int score, int injure) {
	(*player) = (Player *)malloc(sizeof(Player));
	(*player)->name = strdup(name);
	(*player)->position = strdup(position);
	(*player)->score = valid_score(score);
	(*player)->injured = injure;
	(*player)->next = (*player)->prev = NULL;
}

void free_player(Player **player) {
	free((*player)->name);
	free((*player)->position);
	free((*player));
	*player = NULL;
}

Player* cpy_player(Player* player) {
	Player* ret = NULL;

	ret = (Player* )malloc(sizeof(Player));
	ret->injured = player->injured;
	ret->position = strdup(player->position);
	ret->name = strdup(player->name);
	ret->score = player->score;
	ret->next = NULL;
	ret->prev = NULL;
	
	return ret;
	
}

void InsertAfter(Player* prev_node, Player* new_player) {
	if(prev_node == NULL)
		return ;

	new_player->next = prev_node->next;
	prev_node->next = new_player;
	new_player->prev = prev_node;
	if(new_player->next != NULL)
		new_player->next->prev = new_player;
}

void InsertBefore(Player** head, Player* current_node, Player* new_player) {
	new_player->prev = current_node->prev;
	current_node->prev = new_player;
	new_player->next = current_node;
	if(new_player->prev!= NULL)
		new_player->prev->next = new_player;
	else
		(*head) = new_player;
}
int NrPos(Player* player, char* position){
	int count = 0;

	if (player != NULL) {
		Player* tmp = player;
		while(tmp != NULL){
			if(strcmp(tmp->position, position) == 0){
				count ++;
			}
			tmp = tmp->next;	
		}
	}
	return count;
}

FootballClub* goto_club(FootballClub* clubs, char* club_name) {
	FootballClub* current = NULL;

	if(clubs) {
		current = clubs;
		while(current != NULL && !(strcmp(club_name, current->name) == 0)){
			current = current->next;
		}
	}
	return current;
}

Player* goto_player(FootballClub* club, char* player_name) {
	Player* current_player = NULL;

	if(club != NULL ) {
		if(club->players != NULL) {
			current_player = club->players;
			while(current_player != NULL && !(strcmp(current_player->name, player_name) == 0))
				current_player = current_player->next;
		}
		if(current_player == NULL && club->injured_players != NULL) {
			current_player = club->injured_players;
			while(current_player != NULL && !(strcmp(current_player->name, player_name) == 0))
				current_player = current_player->next;
		}
	}
	return current_player;
}

Player* goto_position(Player* players, char* position) {
	Player* current_player = NULL;

	if(players != NULL) {
		current_player = players;
		while(current_player != NULL && !(strcmp(current_player->position, position) == 0))
			current_player = current_player->next;
	}
	return current_player;
}

void Sorted_insert(Player** head, Player* new_player) {
	Player* curent;
	int n, i;

	if(new_player->injured == 1) {
		if (*head == NULL) 
			*head = new_player;
		else {
			curent = *head;
			while(curent != NULL){
				if(strcmp(curent->name, new_player->name) < 0) {
					if(curent->next == NULL) {
						InsertAfter(curent,new_player);
						return ;
					}
				}
				if(strcmp(curent->name, new_player->name) > 0){
					InsertBefore(head, curent, new_player);
					return ;
				}
				curent = curent->next;
			}
		}

	} else {
	if (*head == NULL) {
		*head = new_player;
	}
	else {
		curent = *head;
		if((n = NrPos(curent, new_player->position)) == 0){
			while(curent != NULL){
				if(strcmp(curent->position, new_player->position) < 0) {
					if(curent->next == NULL) {

						InsertAfter(curent,new_player);
						return ;
					}
				}
				if(strcmp(curent->position, new_player->position) > 0){
					InsertBefore(head, curent, new_player);
					return ;
				}
				curent = curent->next;
			}
		}
		else{
			while(strcmp(curent->position,new_player->position) != 0 && curent != NULL)
				curent = curent->next;
			for(i = 0; i < n; i++, curent = curent->next){
				if(curent->score > new_player->score) {
					if (i == n - 1) {
						InsertAfter(curent, new_player);
						return ;
					} else
						continue ;
				}
				if(curent->score < new_player->score){
					InsertBefore(head, curent, new_player);
					return ;
				}
				if(curent->score == new_player->score){
					if(strcmp(curent->name, new_player->name) < 0){
						if(i == n - 1) {
							InsertAfter(curent, new_player);
							return ;
						}
					} else 
					if(strcmp(curent->name, new_player->name) > 0){
						InsertBefore(head, curent, new_player);
						return ;
					}
				}
			}
		}
	}
	
}

	
}

FootballClub* add_club(FootballClub *clubs, char *name) {
	FootballClub* new_club = (FootballClub *)malloc(sizeof(FootballClub));
	new_club->name = strdup(name);
	new_club->next = NULL;
	new_club->players = new_club->injured_players = NULL;

	if(clubs == NULL) {
		return new_club;
	} else {
		FootballClub* head = clubs;
		while(head->next != NULL)
			head = head->next;
		head->next = new_club;
		return clubs;	
	}
}


FootballClub *initialize_clubs(int clubs_no, char **names) {
	int i;
	FootballClub* clubs = NULL;

	for (i = 0; i < clubs_no; i++) {
		clubs = add_club(clubs, names[i]);
	}
	return(clubs);
}


void add_player(FootballClub *clubs, char *club_name,
				char *player_name, char *position, int score) {
	FootballClub* curr_club; //club head
	Player* player;

	if (clubs) {
		if((curr_club = goto_club(clubs, club_name)) != NULL) {
			new_player(&player, player_name, position, score, 0);
			Sorted_insert(&(curr_club)->players, player);		
		}
	}
}
//Functia data gaseste playerul pe care urmeaza sa-l transfere,
// Creeaza o copie a acestuia dupa care il sterge din club si 
// il insereaza din nou doar ca in clubul nou 
void transfer_player(FootballClub *clubs, char *player_name,
					char *old_club, char *new_club) {
	FootballClub* curr_old_club;
	FootballClub* curr_new_club;
	Player *tmp;
	Player* curr_player;

	if(clubs != NULL) {
		if( (curr_old_club = goto_club(clubs, old_club)) != NULL) {
			if ( (curr_new_club = goto_club(clubs, new_club)) != NULL ) {
				if( (curr_player = goto_player(curr_old_club, player_name)) != NULL) {
					tmp = cpy_player(curr_player);
					remove_player(clubs, old_club, player_name);
					if(tmp->injured == 0)
						Sorted_insert(&(curr_new_club->players), tmp);
					else
						Sorted_insert(&(curr_new_club->injured_players), tmp);
				}
			}
		}
	} else
		return ;
}



void remove_player(FootballClub *clubs, char *club_name, char *player_name) {
	FootballClub *curr_club;
	Player *curr_player;
	int injured = 0;

	if(clubs != NULL){
		if( (curr_club = goto_club(clubs, club_name)) != NULL) {
			if( (curr_player = goto_player(curr_club, player_name)) != NULL) {
				injured = curr_player->injured;
				if(curr_player->prev == NULL) { // Daca playerul pe care il stergem este capul listei
					if(curr_player->next != NULL) { // Daca avem mai mult de un element in lista
						curr_player = curr_player->next; // Trecem pe urmatorul jucator
						free_player(&(curr_player->prev)); // Stergem precedentul, adica capul
					} else {
						free_player(&curr_player); // Altfel avem doar un jucator si-l stergem
					}
					if(injured == 0) {
						curr_club->players = curr_player; // Actualizam lista de jucatori in dependenta
					} else {  							// De lista din care l-am sters, ca a fost jucator accinentat sau ne ....
						curr_club->injured_players = curr_player;
						}
				} else {						// Daca playerul nu era capul listei :
					curr_player->prev->next = curr_player->next; // jucatorul curent din lista devine urmatorul jucator
				if(curr_player->next != NULL)
					curr_player->next->prev = curr_player->prev;
				free_player(&(curr_player)); // Eliberam spatiul de memorie pentru jucatorul pe care il stergem
				}
			}
		}
		
	} else
		return ;
}


// Pentru a actualiza scorul unui utilizator mai intai il identific cu goto_club 
// si goto_player, dupa ce il depistez, ii fac o copie care are deja scorul actaulizat
// il sterg din club si-l adaug din nou, insa cu noul scor

void update_score(FootballClub *clubs, char *club_name,
					char *player_name, int score) {
	FootballClub* curr_club;
	Player* curr_player;
	Player* copy_player;

	if(clubs) {
		if((curr_club = goto_club(clubs,club_name)) != NULL) {
			if((curr_player = goto_player(curr_club, player_name)) != NULL) {
				copy_player = cpy_player(curr_player);
				copy_player->score = valid_score(score);
				remove_player(clubs, club_name, player_name);
				if(copy_player->injured == 0) {
					Sorted_insert(&(curr_club)->players, copy_player);
				} else
					Sorted_insert(&(curr_club)->injured_players, copy_player);
			}
		}
	} else 
		return ;
}

// Actualizarea pozitiei are loc dupa acelasi princiu ca si a scorului
// doar ca schimbam si pozitia si scorul jucatorului, il stergem si-l
// inseram din nou

void update_game_position(FootballClub *clubs, char *club_name,
							char *player_name, char *position, int score) {
	FootballClub* curr_club;
	Player* curr_player;
	Player* copy_player;

	if(clubs) {
		if((curr_club = goto_club(clubs, club_name)) != NULL){
			if((curr_player = goto_player(curr_club, player_name))!= NULL) {
				copy_player = cpy_player(curr_player);
				free(copy_player->position);
				copy_player->position = strdup(position);
				copy_player->score = valid_score(score);
				remove_player(clubs, club_name, player_name);
				if(copy_player->injured == 0)
					Sorted_insert(&(curr_club)->players, copy_player);
				else
					Sorted_insert(&(curr_club)->injured_players, copy_player);
			}
		}
	} else 
		return ;
}

// Pentru a muta jucatorul in lista jucatorilor accidentati mai intai
// il identificam, ii schimbam scorul in functie de numarul de zile
// in care va fi accidentat, ii facem o copie, il stergem si-l inseram
// in lista jucatorilor accidentati din clubul curent

void add_injury(FootballClub *clubs, char *club_name,
				char *player_name, int days_no) {
	FootballClub* curr_club;
	Player* curr_player;
	Player* tmp;

	if(clubs) {
		if( (curr_club = goto_club(clubs, club_name)) != NULL) {
			if( (curr_player = goto_player(curr_club, player_name)) != NULL) {
				curr_player->score = curr_player->score - (0.1 * days_no);
				tmp = cpy_player(curr_player);
				tmp->injured = 1;
				tmp->score = valid_score(tmp->score);
				remove_player(clubs, club_name, player_name);
				Sorted_insert( &(curr_club->injured_players), tmp);
			}
		}
		
			
	} else
		return ;

}

// Ca sa intoarcem jucatorul in lista playerilor neaccidentati ii actualizam
// parametrul injured, il copiem, il stergem din lista jucatorilor accidentati
// si il inseram in lista jucatorilor neaccidentati ai clubului curent

void recover_from_injury(FootballClub *clubs, char *club_name,
							char *player_name) {
	FootballClub * curr_club;
	Player* curr_player;
	Player* tmp;

	if(clubs) {
		if( (curr_club = goto_club(clubs, club_name)) != NULL) {
			if( (curr_player = goto_player(curr_club, player_name)) != NULL) {
				tmp = cpy_player(curr_player);				
				tmp->injured = 0;
				remove_player(clubs, club_name, player_name);
				Sorted_insert(&(curr_club->players), tmp);
			}
		}
	} else
		return ;
}

// Frees memory for a list of Player.
void destroy_player_list(Player *player) {
	Player *curr = player;
	Player *next;

	while(curr != NULL) {
		next = curr->next;
		free_player(&curr);
		curr = next;
	}
	// player = NULL;
}

// Frees memory for a list of FootballClub.
void destroy_club_list(FootballClub *clubs) {
	FootballClub* next;
	FootballClub* curr = clubs;


	while(curr != NULL) {
		next = curr->next;
		free(curr->name);
		if(curr->injured_players != NULL)
			destroy_player_list(curr->injured_players);
		if(curr->players!= NULL)
			destroy_player_list(curr->players);
		free(curr);
		curr = next;
	}
}

// Displays a list of players.
void show_list(FILE *f, Player *players, int free_memory) {
	fprintf(f, "P: ");
	Player *player = players;
	while (player) {
		fprintf(f, "(%s, %s, %d, %c) ",
			player->name,
			player->position,
			player->score,
			player->injured ? 'Y' : '_');
		player = player->next;
	}
	if (free_memory) {
		destroy_player_list(players);
	}
	fprintf(f, "\n");
}

// Displays a list of players in reverse.
void show_list_reverse(FILE *f, Player *players, int free_memory) {
	fprintf(f, "P: ");
	Player *player = players;
	if (player) {
		while (player->next) {
			player = player->next;
		}
		while (player) {
			fprintf(f, "(%s, %s, %d, %c) ",
				player->name,
				player->position,
				player->score,
				player->injured ? 'Y' : '_');
			player = player->prev;
		}
	}
	if (free_memory) {
		destroy_player_list(players);
	}
	fprintf(f, "\n");
}


// Displays information about a football club.
void show_clubs_info(FILE *f, FootballClub *clubs) {
	fprintf(f, "FCs:\n");
	while (clubs) {
		fprintf(f, "%s\n", clubs->name);
		fprintf(f, "\t");
		show_list(f, clubs->players, 0);
		fprintf(f, "\t");
		show_list(f, clubs->injured_players, 0);
		clubs = clubs->next;
	}
}

#endif // FOOTBALL_CLUB_H_INCLUDED