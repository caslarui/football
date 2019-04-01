
#ifndef TEAM_EXTRACTOR_H_
#define TEAM_EXTRACTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FootballClub.h"

Player *get_players_by_position(FootballClub *clubs, char *position);





// Functia insereaza un jucator nou in lista tinand cont de scorul acestuia
//	va adauga jucatorul nou dupa principiul ca daca scorul jucatorului curent
//	este mai mic decat al jucatorului nou, jucatorul nou va fi adaugat in fata acestuia
//	sau daca jucatorul curent este ultimul in lista iar scorul acestuia este mai mare
//	decat al jucatorului nou, atunci jucatorul nou va fi inserat dupa curent. Acelasi principiu
// 	si cand scorul e acelasi, insa e nevoie sa-l inseram alfabetic

void insert_by_score(Player** list, Player* new_player) {
	Player* current = NULL;

	if(*list == NULL){
		*list = new_player;
		return ;
	} else {
		current = (*list);
		if (new_player->score > (*list)->score) {
			InsertBefore(list, *list, new_player);
		}
		if (new_player->score == (*list)->score) {
			while(current != NULL && current->score == new_player->score) {
				if(strcmp(current->name, new_player->name) > 0) {
					InsertBefore(list, current, new_player);
					return;
				}
				if(strcmp(current->name, new_player->name) < 0) {
					if (current->next == NULL || current->next->score != current->score) {
						InsertAfter(current, new_player);
						return ;
					}
				} else
					return ;
				current = current->next; 
			} 
		}
		if(current->score > new_player->score) {
			for(; current != NULL; current = current->next) {
				if(current->score < new_player->score) {
					InsertBefore(list, current, new_player);
					return ;
				}else
				if(current->score > new_player->score) {
					if(current->next == NULL) {
						InsertAfter(current, new_player);
						return ;
					} else {
						continue ;
						}
				}else 
				if(current->score == new_player->score) {
					if(strcmp(current->name, new_player->name) > 0) {
						InsertBefore(list, current, new_player);
						return;
					}
					if(strcmp(current->name, new_player->name) < 0) {
						if (current->next == NULL || current->next->score != current->score) {
							InsertAfter(current, new_player);
							return ;
						}
					} 
				}else 
						return ;
			}
		}
	} 
}


// Functia sort_by_score sorteaza o lista de playeri descrescator dupa scor si
//	respectiv crescator alfabetic utilizand insert-ul implementat anterior

Player* sort_by_score(Player* list) {
	Player* sorted_list = NULL;
	Player* current = NULL;
	Player* tmp= NULL;

	if(list) {
		current = list;
		while(current != NULL) {
			tmp = cpy_player(current);
			insert_by_score(&sorted_list, tmp);
			current = current->next;
		}
	}
	return sorted_list;
}






Player *union_teams(FootballClub *clubs, char *club_A, char *club_B) {
	FootballClub* curr_club;
	Player* curr_player;
	Player* tmp = NULL;
	Player* list = NULL;

	if( (curr_club = goto_club(clubs, club_A)) != NULL) {
		curr_player = curr_club->players;
		while(curr_player != NULL){
			tmp = cpy_player(curr_player);
			Sorted_insert(&list, tmp);
			curr_player = curr_player->next;
		}
	}
	if( (curr_club = goto_club(clubs, club_B)) != NULL) {
		curr_player = curr_club->players;
		while(curr_player != NULL){
			tmp = cpy_player(curr_player);
			Sorted_insert(&list, tmp);
			curr_player = curr_player->next;
		}
	}
	return list;
}

// Genereaza lista cu toti jucatorii care joaca pe positia ceruta
// sortata dupa scor si alfabetic. Dupa extrage primul jucator 
// neaccidentat, respectiv acesta si va avea cel mai mare scor


Player *get_best_player(FootballClub *clubs, char *position) {
	Player *best_player = NULL;
	Player* list = NULL;
	Player* curr = NULL;
	
	if(clubs != NULL) {
		list = get_players_by_position(clubs, position);
		curr = list;
		while (curr != NULL) {
			if(curr->injured == 0) {
				best_player = cpy_player(curr);
				destroy_player_list(list);
				return best_player;
			}
			curr = curr->next;
		}
		destroy_player_list(list);
	}
	return best_player;
}

Player *get_top_players(FootballClub *clubs, int N) {
	FootballClub* curr_club;
	Player* curr_player=NULL;
	Player* tmp_list;
	Player* ret = NULL;
	int i = 0;

	if(clubs && N > 0) {
		curr_club = clubs;
		while(curr_club != NULL) { // Parcurg Fiecare club
			tmp_list = sort_by_score(curr_club->players); // Generez o lista sortata dupa scori a jucatorilor din clubul curent
			while(i < N) {
				if(tmp_list == NULL) { // In cazul in care lista deja e Nula asta inseamna ca nr jucatori < N si inchidem ciclul, trecem la urm. club
					i = 0;
					break ;
				}
				curr_player = cpy_player(tmp_list); // copiem jucatorul
				insert_by_score(&ret, curr_player); // Il inseram tinand cont de scor, nume
				i++;
				tmp_list = tmp_list->next;
			}
			i = 0;
			destroy_player_list(tmp_list); // distrugem lista generata
			curr_club = curr_club->next; // trecem la urmatorul scor
		}
	}
	return ret;
}

// Parcurge toate cluburile si toti jucatorii atat accidentati cat si neaccidentati
// si ii insereaza corespunzator dupa scor si alfabetic daca scorul acestora este 
// cel putin egal cu parametrul "score"

Player *get_players_by_score(FootballClub *clubs, int score) {
	FootballClub* curr_club;
	Player* curr_player;
	Player* tmp = NULL;
	Player* ret = NULL;


	if(clubs != NULL) {
		curr_club = clubs;
		while(curr_club != NULL) {
			curr_player = curr_club->players;
			while(curr_player != NULL) {
				if(curr_player->score >= score) {
					tmp = cpy_player(curr_player);
					insert_by_score(&ret, tmp);
				}
				curr_player = curr_player->next;
			}
			if(curr_club->injured_players != NULL) {
				curr_player = curr_club->injured_players;
				while(curr_player != NULL) {
					if(curr_player->score >= score){
						tmp = cpy_player(curr_player);
						insert_by_score(&ret, tmp);
					}
					curr_player = curr_player->next;
				}
			}
			curr_club = curr_club->next;
		}
	}
	return ret;
}

// Parcurge toate cluburile si toti jucatorii atat accidentati cat si neaccidentati
// si genereaza o lista sortata dupa scor cu toti jucatorii corespunzator parametrului
// "position"

Player *get_players_by_position(FootballClub *clubs, char *position) {
	FootballClub* curr_club;
	Player* curr_player;
	Player* tmp = NULL;
	Player* ret = NULL;

	if(clubs != NULL) {
		curr_club = clubs;
		while(curr_club != NULL) {
			if( (curr_player = goto_position(curr_club->players, position)) != NULL) {
				while(curr_player != NULL && strcmp(curr_player->position, position) == 0) {
					tmp = cpy_player(curr_player);
					insert_by_score(&ret, tmp);
					curr_player = curr_player->next;
				}
			}
			if(curr_club->injured_players != NULL) {
				if( (curr_player = goto_position(curr_club->injured_players, position)) != NULL) {
					while(curr_player != NULL && strcmp(curr_player->position, position) == 0) {
						tmp = cpy_player(curr_player);
						insert_by_score(&ret, tmp);
						curr_player = curr_player->next;
					}
				}
			}
			curr_club = curr_club->next;
		}
	}
	return ret;
}

// Creeaza o ochipa dupa principiu celor mai buni
// 1x portar, 4xfundas, 3xmijlocas, 3xatacant
// Generam in list, lista celor mai buni jucatori de pe positiile respective
// Si ii extragem atatia cati avem nevoie, iar daca ei sunt mai putini, 
//  ii luam doar pe cei de care dispunem.

Player *get_best_team(FootballClub *clubs) {
	Player *team = NULL;
	Player* list = NULL;
	Player* curr_player = NULL;
	Player* tmp = NULL;
	int i = 0;
	
	if(clubs) {
		list = get_players_by_position(clubs, "portar");
		if( (curr_player = goto_position(list, "portar")) != NULL) {
			tmp = cpy_player(curr_player);
			insert_by_score(&team, tmp);
		}
		
		destroy_player_list(list);
		list = get_players_by_position(clubs, "fundas");
		
		if( (curr_player = goto_position(list, "fundas")) != NULL) {
			while(curr_player != NULL && strcmp(curr_player->position, "fundas") == 0 && i < 4) {
				tmp = cpy_player(curr_player);
				insert_by_score(&team, tmp);
				curr_player = curr_player->next;
				i++;
			}
			i = 0;
		}

		destroy_player_list(list);		
		list = get_players_by_position(clubs,"mijlocas");

		if( (curr_player = goto_position(list, "mijlocas")) != NULL) {
			while(curr_player != NULL && strcmp(curr_player->position, "mijlocas") == 0 && i < 3) {
				tmp = cpy_player(curr_player);
				insert_by_score(&team, tmp);
				curr_player = curr_player->next;
				i++;
			}
			i = 0;
		}

		destroy_player_list(list);		
		list = get_players_by_position(clubs,"atacant");

		if( (curr_player = goto_position(list, "atacant")) != NULL) {
			while(curr_player != NULL && strcmp(curr_player->position, "atacant") == 0 && i < 3) {
				tmp = cpy_player(curr_player);
				insert_by_score(&team, tmp);
				curr_player = curr_player->next;
				i++;
			}
			i = 0;
		}
		destroy_player_list(list);		
	}
	return team;
}


#endif // TEAM_EXTRACTOR_H_INCLUDED