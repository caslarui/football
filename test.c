#include "FootballClub.h"


int main() {

  char **names = calloc(3, sizeof(char*));
	for (int i = 0; i < 3; i++) {
		names[i] = calloc(20, sizeof(char));
		sprintf(names[i], "club%d", i+1);
	}
	FootballClub *clubs = initialize_clubs(3, names);
	clubs = add_club(clubs, "club4");

  FootballClub* head = clubs;
	add_player(clubs, "club1", "n1", "atacant", 1);
	add_player(clubs, "club1", "n7", "atacant", -100);
	add_player(clubs, "club2", "n2", "fundas", 2);
	add_player(clubs, "club3", "n3", "mijlocas", 3);
	add_player(clubs, "club4", "n4", "portar", 4);
	add_player(clubs, "club4", "n5", "portar", 0);

    while(head != NULL)
    {
        printf("===================%s\n", head->name);
        if(head->players) {
        Player* player = head->players;
            while (player) {
		printf("(%s, %s, %d, %c)   \n",
			player->name,
			player->position,
			player->score,
			player->injured ? 'Y' : '_');
		player = player->next;
	        }
        }
        head = head->next;
        // printf("\n");
    }



  
    while(head != NULL)
    {
        printf("===================%s\n", head->name);
        if(head->players) {
        Player* player = head->injured_players;
            while (player) {
		printf("(%s, %s, %d, %c)   \n",
			player->name,
			player->position,
			player->score,
			player->injured ? 'Y' : '_');
		player = player->next;
	        }
        }
        head = head->next;
        // printf("\n");
    }
    head = clubs;
    // recover_from_injury(clubs, "club1", "n1");
    // printf("%d\n",strcmp("mijlocas","atacant"));
    return 0;
}
