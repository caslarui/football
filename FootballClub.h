#ifndef FOOTBALL_CLUB_H_
#define FOOTBALL_CLUB_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

int valid_score(int score) {
	if (score >= -100 && score <= 100)
		return score;
	else if (score > 100)
		return 100;
	return -100;
}

void Player_Info(Player* player) {
	printf("(%s, %s, %d, %c) \n",
		player->name,
		player->position,
		player->score,
		player->injured ? 'Y' : '_');
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

int lookup(Player* head, char* str) {
	if (head) {
		Player* crt = head;
		while(crt->next != NULL) {
			if (strcmp(str, head->position) == 0)
				return 1;
				crt = crt->next;
		}
	}
	return 0;
}

void Sort_list(Player** head) {
	Player *crt = *head;

	if(crt != NULL) {
		while (crt->next != NULL) {
		}
	}
}

void InsertAfter(Player* prev_node, Player* new_player) {
	if(prev_node == NULL)
		return ;

	new_player->next = prev_node->next;
	prev_node->next = new_player;
	new_player->prev = prev_node;
	if(new_player->next != NULL)
		new_player->next->prev = prev_node;
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

void Sorted_insert(Player** head, Player* new_player) {
	Player* curent;



	if (*head == NULL) {
		*head = new_player;
	}
	else {
		curent = *head;
		if (strcmp(curent->position, new_player->position) > 0) {
			InsertBefore(head, curent, new_player);
			return ;
		}
		if (strcmp((*head)->position, new_player->position) <= 0 ) {
				while (curent->next != NULL &&
					strcmp(curent->position, new_player->position) != 0)
					curent = curent->next; // Parcugem pana nu depistam aceeasi pozitie
				while (curent->next != NULL) {
					if (strcmp(curent->next->position, new_player->position) != 0) {
						if(curent->score > new_player->score) {
							InsertAfter(curent, new_player);
							return ;
						}
						if(curent->score < new_player->score) {
							InsertBefore(head, curent, new_player);
							return ;
						}
						if(curent->score == new_player->score) {
							while (curent->next != NULL) {
								if (strcmp(curent->name, new_player->name) < 0)
									curent = curent->next;
								else {
									InsertBefore(head, curent, new_player);
									return ;
								}
							}
						}
					}
					if (strcmp(curent->position, new_player->position) == 0 &&
						curent->score < new_player->score) {
							InsertBefore(head, curent, new_player);
							return;
					}
					Player_Info(curent);
					Player_Info(new_player);
					if (strcmp(curent->position, new_player->position) == 0 &&
						curent->score > new_player->score)
						curent = curent->next;
					else if (strcmp(curent->position, new_player->position) == 0 &&
						curent->score == new_player->score) {
							while (curent->next != NULL) {
								if (strcmp(curent->name, new_player->name) >= 0){
									InsertBefore(head, curent, new_player);
									return ;
								}
								if (strcmp(curent->name, new_player->name) < 0 &&
									curent->next!= NULL)
									curent = curent->next;
								if (strcmp(curent->name, new_player->name) < 0 &&
									curent->next == NULL) {
									InsertAfter(curent, new_player);
									return ;
								}
							}
					}
					curent = curent->next;
				}
				// InsertAfter(curent, new_player);
			}
		}
}

FootballClub* add_club(FootballClub *clubs, char *name) {
	if(clubs == NULL) {
		clubs = (FootballClub* )malloc(sizeof(FootballClub));
		clubs->name = strdup(name);
		clubs->next = NULL;
	} else {
		FootballClub* head = clubs;
		while(head->next != NULL)
			head = head->next;
		head->next = (FootballClub* )malloc(sizeof(FootballClub));
		head->next->name = strdup(name);
		head->next->next = NULL;
	}
	return clubs;
}


FootballClub *initialize_clubs(int clubs_no, char **names) {
	int i;
	FootballClub* clubs = NULL;

	for (i = 0; i < clubs_no; i++) {
		clubs = add_club(clubs,names[i]);
	}
	return(clubs);
}


void add_player(FootballClub *clubs, char *club_name,
				char *player_name, char *position, int score) {
	Player* player;
	if (clubs) {
		FootballClub* c_head = clubs; //club head
		new_player(&player, player_name, position, score, 0);
		while(c_head->next != NULL) {
			if(strcmp(c_head->name, club_name) == 0) {
				// printf("!!!!%s\n",c_head->name);
				Sorted_insert(&(c_head)->players, player);
				}
			c_head = c_head->next;
			}
		}
}

void transfer_player(FootballClub *clubs, char *player_name,
					char *old_club, char *new_club) {
}

void remove_player(FootballClub *clubs, char *club_name, char *player_name) {
}

void update_score(FootballClub *clubs, char *club_name,
					char *player_name, int score) {
}

void update_game_position(FootballClub *clubs, char *club_name,
							char *player_name, char *position, int score) {
}

void add_injury(FootballClub *clubs, char *club_name,
				char *player_name, int days_no) {
}

void recover_from_injury(FootballClub *clubs, char *club_name,
							char *player_name) {
}

// Frees memory for a list of Player.
void destroy_player_list(Player *player) {
}

// Frees memory for a list of FootballClub.
void destroy_club_list(FootballClub *clubs) {
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
