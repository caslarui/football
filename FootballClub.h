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

void remove_player(FootballClub *clubs, char *club_name, char *player_name);

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

void Sorted_insert(Player** head, Player* new_player) {
	Player* curent;
	int n, i;

	if (*head == NULL) {
		*head = new_player;
	}
	else {
		curent = *head;
		if((n = NrPos(curent, new_player->position)) == 0){
			while(curent != NULL){
				// Player_Info(new_player);

  				// printf("aici\n");
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
			while(strcmp(curent->position,new_player->position) != 0)
				curent = curent->next;
				// Player_Info(curent);
				// printf("\n%d\n",n);
			for(i = 0; curent != NULL && i < n; i++, curent = curent->next){
				if(curent->score > new_player->score && curent->next == NULL){
					InsertAfter(curent, new_player);
					return ; 
				}
				if(curent->score > new_player->score && (i == n - 1)) {
					InsertAfter(curent, new_player);
					return ;
				}
				// if(curent->score > new_player->score){
					// curent = curent->next;
				// }
				if(curent->score < new_player->score){
					InsertBefore(head, curent, new_player);
					return ;
				}
				if(curent->score == new_player->score){
					if(strcmp(curent->name, new_player->name) < 0){
						if(i == n - 1){
							if(strcmp(curent->name, new_player->name) < 0){
								InsertAfter(curent, new_player);
								return ; 
							}
							else{
								InsertBefore(head, curent, new_player);
								return ;
							}

						}
					}
					if(strcmp(curent->name, new_player->name) > 0){
						InsertBefore(head, curent, new_player);
						return ;
					}

				}
			}
		}
	}
	
}

FootballClub* add_club(FootballClub *clubs, char *name) {
	if(clubs == NULL) {
		clubs = (FootballClub* )malloc(sizeof(FootballClub));
		clubs->name = strdup(name);
		clubs->next = NULL;
		clubs->players = clubs->injured_players = NULL;
	} else {
		FootballClub* head = clubs;
		while(head->next != NULL)
			head = head->next;
		head->next = (FootballClub* )malloc(sizeof(FootballClub));
		head->next->name = strdup(name);
		head->next->players = head->next->injured_players = NULL;
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
		while(c_head != NULL) {
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
	FootballClub* curr_club;
	Player *tmp;
	Player* player;

	if(clubs != NULL) {
		curr_club = clubs;
		while(curr_club->next != NULL && !(strcmp(curr_club->name, old_club) == 0) )
			curr_club = curr_club->next;
		// printf("\n---------------------%s\n",curr_club->name);
		player = curr_club->players;
		while(player->next != NULL && !(strcmp(player->name, player_name) == 0) )
			player = player->next;
//   printf("aici\n");
		if(strcmp(player->name, player_name) == 0) {
			tmp = player;
			if(player->prev != NULL)
				player->prev->next = player->next;
			if(player->next != NULL) {
				player->next->prev = player->prev;
				while(player->prev != NULL)
					player = player->prev;
				curr_club->players = player;
			}
			curr_club = clubs;
			while(curr_club->next != NULL && !(strcmp(curr_club->name, new_club) == 0) )
				curr_club = curr_club->next;
			if(strcmp(curr_club->name, new_club) == 0)
				Sorted_insert(&(curr_club)->players, tmp);
			else
			{
				return ;
			}
			
		} else
			return;
	}
}

void remove_player(FootballClub *clubs, char *club_name, char *player_name) {
	Player *curr_player;
	FootballClub *curr_club;

	if(clubs != NULL){
		curr_club = clubs;
		while(curr_club->next != NULL && !(strcmp(curr_club->name, club_name) == 0) )
			curr_club = curr_club->next;
		curr_player = curr_club->players;
		while(curr_player->next != NULL && !(strcmp(curr_player->name, player_name) == 0) )
			curr_player = curr_player->next;
		if(strcmp(curr_player->name, player_name) == 0) {
			Player *tmp = curr_player;
			if(curr_player->prev != NULL)
				curr_player->prev->next = curr_player->next;
			if(curr_player->next != NULL) {
				curr_player->next->prev = curr_player->prev;
				while(curr_player->prev != NULL)
					curr_player = curr_player->prev;
				free(tmp->name);
				free(tmp->position);
				free(tmp);
				tmp = NULL;
				curr_club->players = curr_player;
			}
		} else
			return ;
	}
}

void update_score(FootballClub *clubs, char *club_name,
					char *player_name, int score) {
	FootballClub* curr_club;
	Player* curr_player;
	Player* copy_player = (Player *)malloc(sizeof(Player));

	if(clubs) {
		curr_club = clubs;
		while(curr_club->next != NULL && !(strcmp(curr_club->name, club_name) == 0) )
			curr_club = curr_club->next;
		curr_player = curr_club->players;
		while(curr_player->next != NULL && !(strcmp(curr_player->name, player_name) == 0) )
			curr_player = curr_player->next;
		if (strcmp(curr_player->name, player_name) == 0) {
			copy_player->name = strdup(player_name);
			copy_player->position = strdup(curr_player->position);
			copy_player->score = score;
			copy_player->injured = curr_player->injured;
			remove_player(clubs, club_name, player_name);
			Sorted_insert(&(curr_club)->players, copy_player);
		}
	} else {
		return ;
	}
}

void update_game_position(FootballClub *clubs, char *club_name,
							char *player_name, char *position, int score) {
	FootballClub* curr_club;
	Player* curr_player;
	Player* copy_player = (Player *)malloc(sizeof(Player));

	if(clubs) {
		curr_club = clubs;
		while(curr_club->next != NULL && !(strcmp(curr_club->name, club_name) == 0) )
			curr_club = curr_club->next;
		curr_player = curr_club->players;
		while(curr_player->next != NULL && !(strcmp(curr_player->name, player_name) == 0) )
			curr_player = curr_player->next;
		if (strcmp(curr_player->name, player_name) == 0) {
			copy_player->name = strdup(player_name);
			copy_player->position = strdup(position);
			copy_player->score = score;
			copy_player->injured = curr_player->injured;
			remove_player(clubs, club_name, player_name);
			Sorted_insert(&(curr_club)->players, copy_player);
		}
	} else {
		return ;
	}
}

void add_injury(FootballClub *clubs, char *club_name,
				char *player_name, int days_no) {
	FootballClub* curr_club;
	Player* curr_player;
	Player* copy_player = (Player *)malloc(sizeof(Player));

	if(clubs) {
		curr_club = clubs;
		while(curr_club->next != NULL && !(strcmp(curr_club->name, club_name) == 0) )
			curr_club = curr_club->next;
		curr_player = curr_club->players;
		while(curr_player->next != NULL && !(strcmp(curr_player->name, player_name) == 0) )
			curr_player = curr_player->next;
		if (strcmp(curr_player->name, player_name) == 0) {
			copy_player->name = strdup(player_name);
			copy_player->position = strdup(curr_player->position);
			copy_player->score = valid_score(curr_player->score - (0.1 * days_no));
			copy_player->injured = 1;
			copy_player->next = copy_player->prev = NULL;
			remove_player(clubs, club_name, player_name);
			curr_player = curr_club->injured_players;
			if(curr_player == NULL)
				curr_club->injured_players = copy_player;
			else {
				while (curr_player->next != NULL) {
				if(strcmp(curr_player->name, player_name) > 0)
					InsertBefore(&(curr_club->injured_players),curr_player,copy_player);
					return ;
				}
				if(strcmp(curr_player->name, player_name) < 0) {
					if(curr_player->next == NULL) {

						InsertAfter(curr_player, copy_player);
						return ;
					}
				}
			}
		}
	} else {
		return ;
	}

}

void recover_from_injury(FootballClub *clubs, char *club_name,
							char *player_name) {
	FootballClub * curr_club;
	Player* curr_player;
	Player* cpy_player = (Player *)malloc(sizeof(Player));

	if(clubs) {
		curr_club = clubs;
		while(curr_club->next != NULL && !(strcmp(curr_club->name, club_name) == 0) )
			curr_club = curr_club->next;
		curr_player = curr_club->injured_players;
		while(curr_player->next != NULL && !(strcmp(curr_player->name, player_name) == 0) )
			curr_player = curr_player->next;
			if (strcmp(curr_player->name, player_name) == 0) {
			cpy_player->name = strdup(player_name);
			cpy_player->position = strdup(curr_player->position);
			cpy_player->score = curr_player->score;
			cpy_player->injured = 0;
			remove_player(clubs, club_name, player_name);
			Sorted_insert(&(curr_club)->players, cpy_player);
		}

	} else
		return ;


}

// Frees memory for a list of Player.
void destroy_player_list(Player *player) {
	while(player->next != NULL) {
		player = player->next;
		free(player->prev->name);
		free(player->prev->position);
		free(player->prev->name);
	}
	free(player->name);
	free(player->position);
	free(player);
}

// Frees memory for a list of FootballClub.
void destroy_club_list(FootballClub *clubs) {
	FootballClub* tmp;

	while(clubs->next != NULL) {
		tmp = clubs;
		free(tmp->name);
		destroy_player_list(tmp->injured_players);
		destroy_player_list(tmp->players);
		clubs = clubs->next;
	}
	destroy_player_list(clubs->injured_players);
	destroy_player_list(clubs->players);
	free(clubs);
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