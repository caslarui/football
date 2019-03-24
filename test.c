#include "FootballClub.h"


int main() {

    char **names = calloc(3, sizeof(char*));
	for (int i = 0; i < 3; i++) {
		names[i] = calloc(20, sizeof(char));
		sprintf(names[i], "club%d", i+1);
	}
	FootballClub *clubs = initialize_clubs(3, names);
	clubs = add_club(clubs, "club5");
	clubs = add_club(clubs, "clubw");
	clubs = add_club(clubs, "club6");

    FootballClub* head = clubs;
    // printf("aici\n");
    add_player(clubs, "club1", "n3", "mijlocas", 1);

    add_player(clubs, "club1", "n1", "atacant", 1);
	// add_player(clubs, "club1", "n2", "atacant", -100);
  // printf("%d\n",strcmp("n2","n7"));
	add_player(clubs, "club1", "n4", "atacant", 50);
  // printf("aici\n");
  add_player(clubs, "club1", "n7", "atacant", -100);
    while(head != NULL)
    {
        printf("*%s\n", head->name);
        if(head->players) {
        Player* player = head->players;
            while (player) {
		printf("(%s, %s, %d, %c) \n",
			player->name,
			player->position,
			player->score,
			player->injured ? 'Y' : '_');
		player = player->next;
	        }
        }
        head = head->next;
    }
    // printf("%d\n",strcmp("mijlocas","atacant"));
    return 0;
}
