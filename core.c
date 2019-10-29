#include "def.h"

//Commands accepted: start, quit, go, pick, use, look, inventory, move, talk.

void call_next_command(char* input){
	//Start game
	if (strcmp(input,"start")==0){
		//Starting game
		if (!game_started){
			game_started=1;
			color_matrix();
			print_room_moved(map,0,0,1);
		}
		//Failed to start 
		else {
			print_failed_start();
		}
		return;
	} else if (strcmp(input,"quit")==0){
		quit_game();
		return;
	} else if (strcmp(input,"help")==0){
		print_help();
		return;
	}
	if (game_started){
		//Handle joystick input
		if (strcmp(input,"-")==0){
			//up
			if (dir_move_js==1){
				move_direction(map,inventory,curr_rm_x,curr_rm_y,-1,0,mirror_flag,skeleton_flag);
			} 
			//down
			else if (dir_move_js==2){
				move_direction(map,inventory,curr_rm_x,curr_rm_y,1,0,mirror_flag,skeleton_flag);
			} 
			//left
			else if (dir_move_js==3){
				move_direction(map,inventory,curr_rm_x,curr_rm_y,0,-1,mirror_flag,skeleton_flag);
			} 
			//right
			else if (dir_move_js==4){
				move_direction(map,inventory,curr_rm_x,curr_rm_y,0,1,mirror_flag,skeleton_flag);
			} 
			//down (look)
			else if (dir_move_js==5){
				print_room_moved(map,current_rm,skeleton_flag,1);
			}
			dir_move_js=0;
			return;
		}
		//Quit game
		else if (strcmp(input,"quit")==0){
			quit_game();
		}
		//Help
		else if (strcmp(input,"help")==0){
			print_help();
		}
		//Inventory
		else if (strcmp(input,"inventory")==0 || strcmp(input,"i")==0){
			print_inventory(inventory);
		}
		//Look
		else if (strcmp(input,"look")==0 || dir_move_js==5){
			print_room_moved(map,current_rm,skeleton_flag,1);
			dir_move_js=0;
		}
		//Talk
		else if (strcmp(input,"talk")==0){
			//giant
			if (current_rm==0){
				talk_giant();
				lose_game();
			} 
			//cat
			else if (current_rm==3){
				talk_cat();
			}
			//mirror
			else if (current_rm==12){
				talk_mirror();
			}
			//other cases
			else {
				talk_self();
			}
		}
		//All others to be tokenized
		else {
			char *token=NULL;
			token = strtok(input," ");
			//Move to direction
			if (strcmp(token,"go")==0 || strcmp(token,"move")==0){
				token = strtok(NULL," ");
				//Move left
				if (strcmp(token,"left")==0 || strcmp(token,"west")==0 || dir_move_js==3){
					move_direction(map,inventory,curr_rm_x,curr_rm_y,0,-1,mirror_flag,skeleton_flag);
					dir_move_js=0;
				}
				//Move right
				else if (strcmp(token,"right")==0 || strcmp(token,"east")==0 || dir_move_js==4){
					move_direction(map,inventory,curr_rm_x,curr_rm_y,0,1,mirror_flag,skeleton_flag);
					dir_move_js=0;
				}
				//Move up
				else if (strcmp(token,"up")==0 || strcmp(token,"north")==0 || dir_move_js==1){
					move_direction(map,inventory,curr_rm_x,curr_rm_y,-1,0,mirror_flag,skeleton_flag);
					dir_move_js=0;
				}
				//Move down
				else if (strcmp(token,"down")==0 || strcmp(token,"south")==0 || dir_move_js==2){
					move_direction(map,inventory,curr_rm_x,curr_rm_y,1,0,mirror_flag,skeleton_flag);
					dir_move_js=0;
				}
				//Else
				else {
					printf("I can't understand you, adventurer.\n>");
				}
			}
			//Pick item
			else if (strcmp(token,"pick")==0){
				printf("token 1:%s\n",token);
				token = strtok(NULL," ");
				printf("token 2:%s\n",token);
				//Butter knife
				if (strcmp(token,"knife")==0 || strcmp(token,"butterknife")==0 || strcmp(token,"butter")==0){
					if (!pick_item(0,current_rm)){
						printf("You cannot pick that up, adventurer.\n>");
					} else {
						printf("Picked up the butter knife.\n>");
					}
				}
				//Pencil case
				else if (strcmp(token,"pencilcase")==0 || strcmp(token,"pencil")==0 || strcmp(token,"case")==0){
					if (!pick_item(1,current_rm)){
						printf("You cannot pick that up, adventurer.\n>");
					} else {
						printf("Picked up the pencil case.\n>");
					}
				}
				//Rock eye
				else if (strcmp(token,"rockeye")==0 || strcmp(token,"eye")==0 || strcmp(token,"rock")==0){
					if (!pick_item(2,current_rm)){
						printf("You cannot pick that up, adventurer.\n>");
					} else {
						printf("Picked up the rock eye.\n>");
					}
				}
				//Teapot
				else if (strcmp(token,"tea")==0 || strcmp(token,"teapot")==0 || strcmp(token,"pot")==0){
					if (!pick_item(3,current_rm)){
						printf("You cannot pick that up, adventurer.\n>");
					} else {
						printf("Picked up the teapot.\n>");
					}
				}
				//Help me paper
				else if (strcmp(token,"paper")==0 || strcmp(token,"helpme")==0 || strcmp(token,"help")==0){
					printf("You already have the paper!\n>");
				}
				//Loaf of bread
				else if (strcmp(token,"bread")==0 || strcmp(token,"loaf")==0 || strcmp(token,"breadloaf")==0){
					printf("You already have the loaf of bread!\n>");
				}
				//Other cases
				else {
					printf("You cannot pick that up, adventurer.\n>");
				}
			}
			//Use item
			else if (strcmp(token,"use")==0){
				token = strtok(NULL," ");
				//Butter knife
				if (strcmp(token,"knife")==0 || strcmp(token,"butterknife")==0 || strcmp(token,"butter")==0){
					if (use_item(inventory,0,current_rm,brewed_tea)){
						printf("You cannot use that, adventurer.\n>");
					}
				}
				//Pencil case
				else if (strcmp(token,"pencilcase")==0 || strcmp(token,"pencil")==0 || strcmp(token,"case")==0){
					if (use_item(inventory,1,current_rm,brewed_tea)){
						printf("You cannot use that, adventurer.\n>");
					}
				}
				//Rock eye
				else if (strcmp(token,"rockeye")==0 || strcmp(token,"eye")==0 || strcmp(token,"rock")==0){
					if (use_item(inventory,2,current_rm,brewed_tea)){
						printf("You cannot use that, adventurer.\n>");
					}
				}
				//Teapot
				else if (strcmp(token,"tea")==0 || strcmp(token,"teapot")==0 || strcmp(token,"pot")==0){
					if (use_item(inventory,3,current_rm,brewed_tea)){
						printf("You cannot use that, adventurer.\n>");
					}
				}
				//Help me paper
				else if (strcmp(token,"paper")==0 || strcmp(token,"helpme")==0 || strcmp(token,"help")==0){
					if (use_item(inventory,4,current_rm,brewed_tea)){
						printf("You cannot use that, adventurer.\n>");
					}
				}
				//Loaf of bread
				else if (strcmp(token,"bread")==0 || strcmp(token,"loaf")==0 || strcmp(token,"breadloaf")==0){
					if (use_item(inventory,5,current_rm,brewed_tea)){
						printf("You cannot use that, adventurer.\n>");
					}
				}
				//other cases
				else {
					printf("What are you trying to use, adventurer?\n>");
				}

			}
			//Other cases
			else {
				printf("I can't understand you, adventurer.\n>");
			}
		}
	} else {
		printf("You haven't even started the game yet, adventurer!\n>");
	}

	return;
}

void* move_joystick(void* arg){
	struct js_event ev;
	open_joystick_device();
	for(;;){
		ev = read_joystick_input();
		if (ev.type == JOYSTICK_PRESS) {
			if (ev.direction == DIRECTION_NORTH) {
				dir_move_js=1;
			} else if (ev.direction == DIRECTION_SOUTH) {
				dir_move_js=2;
			} else if (ev.direction == DIRECTION_WEST) {
				dir_move_js=3;
			} else if (ev.direction == DIRECTION_EAST) {
				dir_move_js=4;
			} else if (ev.direction == DIRECTION_DOWN) {
				dir_move_js=5;
			}
		} else continue; //ignore action
	}

	//should be reached once shutdown_flag=1
	close_joystick_device();
	return (void*)0;
}

void init_items(){
	int i=0;
	for (;i<6;i++){
		inventory->item_list[i]=(item_t*)malloc(sizeof(item_t));
		inventory->item_list[i]->item_name=(char*)malloc(sizeof(char)*10);
		inventory->item_list[i]->item_desc=(char*)malloc(sizeof(char)*30);
		inventory->item_list[i]->item_index=i;
		inventory->item_list[i]->user_hold=0;
		inventory->item_list[i]->item_used=0;
		inventory->item_list[i]->item_final=0;
		inventory->item_list[i]->item_hidden=0;
	}

	//Butter knife
	strcpy(inventory->item_list[0]->item_name,"knife");
	strcpy(inventory->item_list[0]->item_desc,"Rusty Butter Knife");
	inventory->item_list[0]->item_src_rm=7;
	inventory->item_list[0]->curr_loc_rm=7;

	//Pencil case
	strcpy(inventory->item_list[1]->item_name,"pencilcase");
	strcpy(inventory->item_list[1]->item_desc,"Brown Pencil Case");
	inventory->item_list[1]->item_src_rm=5;
	inventory->item_list[1]->curr_loc_rm=5;

	//Rock Eye
	strcpy(inventory->item_list[2]->item_name,"eye");
	strcpy(inventory->item_list[2]->item_desc,"Weird Skeleton's Rock Eye");
	inventory->item_list[2]->item_src_rm=11;
	inventory->item_list[2]->curr_loc_rm=11;
	inventory->item_list[2]->item_hidden=1;

	//Teapot
	strcpy(inventory->item_list[3]->item_name,"teapot");
	strcpy(inventory->item_list[3]->item_desc,"Teapot made of Porcelain");
	inventory->item_list[3]->item_src_rm=11;
	inventory->item_list[3]->curr_loc_rm=11;
	inventory->item_list[3]->item_hidden=1;

	//Paper
	strcpy(inventory->item_list[4]->item_name,"paper");
	strcpy(inventory->item_list[4]->item_desc,"Paper");
	inventory->item_list[4]->item_src_rm=0;
	inventory->item_list[4]->curr_loc_rm=0;
	inventory->item_list[4]->user_hold=1;

	//Bread
	strcpy(inventory->item_list[5]->item_name,"bread");
	strcpy(inventory->item_list[5]->item_desc,"Loaf of Bread");
	inventory->item_list[5]->item_src_rm=0;
	inventory->item_list[5]->curr_loc_rm=0;
	inventory->item_list[5]->user_hold=1;

}

//Item text buffers. Pick one accordingly. Interactions:
//0: no item/npc
//1: giant frog interaction
//2: cat interaction
//3: skeleton interaction
//4: office interaction
//5: kitchen interaction
//6: mirror interaction
char butter_knife_text[7][300]={
	"You take a good look at the rusty butter knife, then at your surroundings. You realize the knife cannot be used here. Bummer.\n",
	"You approach the giant monster in front of you, butter knife in hand. The frog looks at you, eats the butter knife and instantly becomes hungrier. Your last memory is a humongous tongue grabbing you into the giant frog's mouth.\n",
	"Why would you even want to kill the only living creature in this maze? For all I know, YOU are the monster.\n",
	"You take the knife and slowly begin carving the skeleton. You manage to salvage his rock eye, and for some weird reason, a teapot hidden where the belly is supposed to be. You definitely don't want to think how this humanoid died.\n",
	"It takes you a while, but you manage to open a small hole in the wall behind the big office. And there, you find.. nothing. What did you expect?\n",
	"Searching in the kitchen, you find some disgusting solid thing which vaguely resembles butter. You try to get some on your knife, but to no avail.\n",
	"You try to stab the weird mirror. You hear a screaming sound, then multiple laughs from the people in the mirror.\n"
};

char pencil_case_text[7][300]={
	"You try your best, but cannot open the pencil case.\n",
	"You throw the pencil case at the monster. It opens it with its tongue, takes out a spoon that was inside and proceeds to kill you with it, slowly but painfully.\n",
	"You give the pencil case to the cat. The cat responds exactly how a cat should- it plays with it for a second, then kicks it away.\n",
	"You find no use for the pencil case on the skeleton.\n",
	"You get the pencil case out of your pockets. It magically opens, and a pen comes out, which starts writing on a paper \"Use the mirror, young'un! Or the force.\"",
	"You can't find a use for the pencil case in the kitchen.\n",
	"The people in the mirror start looking at you. You're acting weirdly. Stop it.\n"
};

char rock_eye_text[7][300]={
	"You take the rock eye out and wonder, how will I be able to use this here. You have no idea.\n",
	"You try to throw the rock eye to the cyclops. The giant monstrosity takes a look at it, decides to replace its own eye with the rock eye, and proceeds to throw the old eye at you. You die in disgust, as the acid from its eye corrodes your skin.\n",
	"You give the eye at the cat. Cats love small balls, and that's the case that applies for this particular cat too. It plays with it for a bit, then throws it back at you.\n",
	"You take a look at the rock eye. You realize this was one of the skeleton's eyes, and wonder how its live could have been.\n",
	"You take the rock eye out. It starts bouncing around the room like an uncontrollable rubber ball. It eventually breaks one of the legs of a chair in the room. A loud thumping sound is heard, and the eye rolls back to you.\n",
	"You take the rock eye out. It starts bouncing, and ends up stuck in one of the cupboards, and replaces its handle. The cupboard is now looking at you.\n",
	"As you take the rock eye out of your pockets, the guys in the mirror turn to you. You can hear one of them saying \"You should not eat that.\"\n"
};

//4: after interaction, wait for warm sensor interaction
char teapot_text[7][300]={
	"You take the teapot out. You have a hunch this is way too important to break.\n",
	"You throw the teapot at the giant. The porcelain breaks on his skin making a horrid sound, and you see small drops of liquid destroying the frog's skin. The cyclops lets out a screaming sound, and angrily proceeds to kill you using its tongue.\n",
	"You show the teapot to your cat. She gets excited. \"Yes! Yes! Throw tea at the giant! The frog hates chamomile tea, did I tell you that?\"\n",
	"The only thing that comes to your mind is how, and why did the skeleton have a teapot in his belly.\n",
	"You take the teapot out. You think that it would have been great to have a cup of tea while studying. Especially if you are a Brit.\n",
	"You take the teapot out in the kitchen. You find a couple of packs of chamomile tea, and some water near you. You suddenly think of a warm cup of tea, and think of how you could warm the water.\n",
	"The guys at the mirror nod in understanding while you take the teapot out. You hear the one in the middle saying, \"Did you try making a cup, or are you just stealing loot?\"\n"
};

char bread_text[7][300]={
	"You don't feel hungry right now.\n",
	"You throw the bread at the giant. It ignores it, and eats you instead. What did you expect?\n",
	"You feed the bread to your cat. It is hard, but it manages to eat it. You feel good as the cat regains some of its energy.\n",
	"Trying to feed the skeleton has absolutely no effect.\n",
	"You don't feel hungry right now.\n",
	"Being in the kitchen makes you instantly hungry, so you eat the bread. You suddenly get a glimpse into the future, and for a second you see the frog screaming and hear the sound of porcelain breaking.\n",
	"You take the bread out, determined to eat it. The guys in the mirror look at you and decide to flex, showing you the pizza they are eating at the moment. You feel jealous and decide not to eat anything.\n"
};

char paper_text[7][300]={
	"You find no use for the paper you found next to you.\n",
	"You throw the paper at the giant frog. The cyclops reads \"Help me!\" out loud, and immediately answers back \"No puedo hablar español señor\", before he proceeds to eat you.\n",
	"You show the paper to your cat. She immediately recognizes it, after all she is the one who wrote it. She purrs, and then decides to talk to you. \"You know, when the frog brought me here, I saw a weird skeleton walking in the Dark Hallway holding something. Maybe this can help.\"\n",
	"You show the paper to the skeleton. It is dead. It does not care.\n",
	"You take the paper out in the office. It feels like it should have been written here, yet you can't find the source of the red material anywhere.\n",
	"While taking out the paper in the kitchen, you realize you are hungry and want to eat it. Yet something tells you it is important. You decide not to.\n",
	"You take the paper out in front of the mirror. The guys in the mirror look at you, and start making fun of you. \"Who writes on papers now? Welcome to the digital age, old man! Get a laptop.\"\n"
};

int allow_use_item(int item_ind,int curr_rm){
	if (inventory->item_list[item_ind]->user_hold || (inventory->item_list[item_ind]->curr_loc_rm==curr_rm && !inventory->item_list[item_ind]->item_hidden))
		return 1;
	return 0;
}

int pick_item(int item_ind,int curr_rm){
	if (!inventory->item_list[item_ind]->user_hold && inventory->item_list[item_ind]->curr_loc_rm==curr_rm && !inventory->item_list[item_ind]->item_hidden){
		inventory->item_list[item_ind]->user_hold=1;
		return 1;
	}
	return 0;
}

//Call this function to use an item in your inventory or in a room.
//Interactions are drawn from the text arrays above, and conditions of critical items are
//updated if the item is used in the right place.
int use_item(inventory_t* inv,int item_ind,int curr_rm,int tea_brewed){
	if (!allow_use_item(item_ind,curr_rm)) {
		return 1;
	}
	int interaction_rm_index;
	
	//find interaction_rm_index according to current room
	switch (curr_rm){
		//giant room
		case 0:{
			interaction_rm_index=1;
			break;
		}

		//prison cell + cat room
		case 3:{
			interaction_rm_index=2;
			break;
		}

		//office room
		case 5:{
			interaction_rm_index=4;
			break;
		}

		//kitchen room
		case 7:{
			interaction_rm_index=5;
			break;
		}

		//skeleton room
		case 11:{
			interaction_rm_index=3;
			break;
		}

		//wardrobe + mirror room
		case 12:{
			interaction_rm_index=6;
			break;
		}

		//anything else
		default: 
			interaction_rm_index=0;
	}

	switch (item_ind){
		//butter knife
		case 0:{
			printf("%s",butter_knife_text[interaction_rm_index]);
			if (curr_rm==11){
				inv->item_list[item_ind]->item_used=1;
				inv->item_list[item_ind]->item_final=1;
				inv->item_list[2]->item_hidden=0;
				inv->item_list[3]->item_hidden=0;
				skeleton_flag=1;
			}
			if (interaction_rm_index==1){
				lose_game();
			}
			break;
		}

		//pencil case
		case 1:{
			printf("%s",pencil_case_text[interaction_rm_index]);
			if (curr_rm==5){
				inv->item_list[item_ind]->item_used=1;
				inv->item_list[item_ind]->item_final=1;
			}
			if (interaction_rm_index==1){
				lose_game();
			}
			break;
		}

		//rock eye
		case 2:{
			printf("%s",rock_eye_text[interaction_rm_index]);
			if (curr_rm==7){
				inv->item_list[item_ind]->item_used=1;
				inv->item_list[item_ind]->item_final=1;
			}
			if (interaction_rm_index==1){
				lose_game();
			}
			break;
		}

		//teapot
		case 3:{
			if (tea_brewed && curr_rm==0){
				endgame();
			} else if (tea_brewed && curr_rm==7){
				printf("You have already brewed tea. Making it feels good, doesn't it?\n");
			} else {
				printf("%s",teapot_text[interaction_rm_index]);
				if (!tea_brewed && interaction_rm_index==1){
					lose_game();
				}
				if (!tea_brewed && curr_rm==7){
					brew_tea();
				}
			}
			break;
		}

		//paper
		case 4:{
			printf("%s",paper_text[interaction_rm_index]);
			if (curr_rm==3){
				inv->item_list[item_ind]->item_final=1;
			}
			if (interaction_rm_index==1){
				lose_game();
			}
			break;
		}

		//bread
		case 5:{
			printf("%s",paper_text[interaction_rm_index]);
			if (curr_rm==7){
				inv->item_list[item_ind]->item_used=1;
				inv->item_list[item_ind]->item_final=1;
			}
			if (interaction_rm_index==1){
				lose_game();
			}
			break;
		}

		//Wrong input, to be ignored.
		default: break;
	}
	return 0;
}

void print_inventory(inventory_t* inv){
	int i=0;
	printf("\nInventory:\n--------------------\n");
	for (;i<6;i++){
		if (inv->item_list[i]->user_hold && !inv->item_list[i]->item_final){
			printf("%s (%s)\n",inv->item_list[i]->item_desc,inv->item_list[i]->item_name);
		}
	}
	printf("\n>");
}

char post_skeleton_text[120]=
	"You see the room where the skeleton used to be, full of scattered bones. You see paths to the north and south.\n";

//Initial map structure. Changes on moving direction.
//Map signs: S=starting, X=current, O=visited, -=not visited, ~=mirror flag
//S=red, X=green, O=yellow, -=no color, ~=blue
char map_struct[4][4]={
	{'X', '-', '-', '-'},
	{'-', '-', '-', '-'},
	{'-', '-', '-', '-'},
	{'-', '-', '-', '-'}
};


//Initializes map.
room_t** init_map(){
	room_t** map=(room_t**)malloc(sizeof(room_t*)*16);
	int i=0;
	for (;i<16;i++){
		map[i]=(room_t*)malloc(sizeof(room_t));
		map[i]->room_name=(char*)malloc(sizeof(char)*50);
		map[i]->room_desc=(char*)malloc(sizeof(char)*500);
		map[i]->rm_index=i;
		map[i]->rm_visited=0;
		map[i]->in_room_now=0;
		map[i]->rm_has_item=0;
		map[i]->rm_can_interact=0;
		map[i]->rm_has_npc=0;
		if (i%4==0)
			map[i]->can_go_left=0;
		if (i%4==3)
			map[i]->can_go_right=0;
		if (i<4)
			map[i]->can_go_up=0;
		if (i>=8)
			map[i]->can_go_down=0;

	}

	//Room (0,0)
	map[0]->in_room_now=1;
	strcpy(map[0]->room_name,"Giant's Pit");
	strcpy(map[0]->room_desc,"In the far end of the room stands a giant cyclops. The more you look at it, the more it seems to resemble Kermit the Frog for some reason. You apparently woke him up, so you have to do something quickly. You see an open door to the east and walls on the other sides- your instincts scream running. You can't defeat everything after all.\n");
	map[0]->rm_can_interact=1;
	map[0]->rm_visited=1;
	map[0]->rm_has_npc=1;
	map[0]->can_go_right=1;
	map[0]->can_go_down=0;

	//Room (0,1)
	strcpy(map[1]->room_name,"Outside the Pit");
	strcpy(map[1]->room_desc,"You are just outside of the giant's room. You see around you a dimly lit hallway expanding to your east, and the room leading to the giant's room to the west. Other than that, it's just walls.\n");
	map[1]->can_go_right=1;
	map[1]->can_go_left=1;
	map[1]->can_go_down=0;

	//Room (0,2)
	strcpy(map[2]->room_name,"Pit Entrance");
	strcpy(map[2]->room_desc,"Walking into this room, you feel a cold breeze and some light coming from the east side of the room. You realize there's some kind of a window to the east. Also, just to the south of you lies yet another corridor, inviting you to visit it.\n");
	map[2]->can_go_right=1;
	map[2]->can_go_left=1;
	map[2]->can_go_down=1;

	//Room (0,3)
	strcpy(map[3]->room_name,"Cells");
	strcpy(map[3]->room_desc,"The first thing that catches your eye is the window on the far end of the room. It seems to be shiny outside. Approaching closer, you can see some kind of metallic bars, and realize it is some kind of a prison. On the ground you see a creature lying down- it seems to be breathing, but it doesn't really move.\n");
	map[3]->can_go_left=1;
	map[3]->can_go_down=0;
	map[3]->rm_has_npc=1;

	//Room (1,0)
	strcpy(map[4]->room_name,"Curtain Room");
	strcpy(map[4]->room_desc,"Walking into this room, you notice a weird red and blue curtain hanging from the stone ceiling, right to your east. Nothing else is of importance though.\n");
	map[4]->can_go_right=1;
	map[4]->can_go_up=0;
	map[4]->can_go_down=1;
	map[4]->rm_has_npc=0;

	//Room (1,1)
	strcpy(map[5]->room_name,"Office");
	strcpy(map[5]->room_desc,"You move the curtain and go into the room it was hiding. It seems to be some kind of a study room- you can see a desk full of weird scientific notes and chemical reactions, and a pencil case. The only way to move though, is to go back west behind the curtain.\n");
	map[5]->can_go_right=0;
	map[5]->can_go_left=1;
	map[5]->can_go_up=0;
	map[5]->can_go_down=0;
	map[5]->rm_has_npc=0;

	//Room (1,2)
	strcpy(map[6]->room_name,"Spike room");
	strcpy(map[6]->room_desc,"Moving down the corridor, you notice spikes on the walls left and right of you. Curiosity killed the cat, and so it would have done to you, if the spikes were actually not pillows. They don't do any harm- instead, it's a nice little pastime bouncing off them. The corridor continues to your south.\n");
	map[6]->can_go_left=0;
	map[6]->can_go_right=0;
	map[6]->can_go_up=1;
	map[6]->can_go_down=1;
	map[6]->rm_has_npc=0;

	//Room (1,3)
	strcpy(map[7]->room_name,"Kitchen");
	strcpy(map[7]->room_desc,"You walk into something that reminds you of your own house: a kitchen. You look around to see anything useful to slay the beast, and find a small, rusty butter knife. Might be useful- who knows?\n");
	map[7]->can_go_up=0;
	map[7]->can_go_down=1;
	map[7]->can_go_left=0;
	map[7]->rm_has_npc=0;

	//Room (2,0)
	strcpy(map[8]->room_name,"Choices");
	strcpy(map[8]->room_desc,"You reach the end of the corridor. There's two paths to choose from: one facing north, the other facing south.\n");
	map[8]->can_go_right=1;
	map[8]->can_go_up=1;
	map[8]->can_go_down=1;
	map[8]->rm_has_npc=0;

	//Room (2,1)
	strcpy(map[9]->room_name,"Hole Room");
	strcpy(map[9]->room_desc,"As you are walking in the corridor, you see a small hole in the ground. It has nothing inside, and does not seem to be useful. Upon closer inspection though, there seems to be some kind of acid on the bottom. Fortunate is the fact that your feet don't really fit. To your south seems to be another path, and the corridor you were taking continues to your west.\n");
	map[9]->can_go_right=1;
	map[9]->can_go_left=1;
	map[9]->can_go_up=0;
	map[9]->can_go_down=1;
	map[9]->rm_has_npc=0;

	//Room (2,2)
	strcpy(map[10]->room_name,"Hallway End");
	strcpy(map[10]->room_desc,"There is literally nothing here except walls. And yet another corridor to your west. Empty rooms are usually scarier than they actually look though.\n");
	map[10]->can_go_right=0;
	map[10]->can_go_left=1;
	map[10]->can_go_up=1;
	map[10]->can_go_down=0;
	map[10]->rm_has_npc=0;

	//Room (2,3)
	strcpy(map[11]->room_name,"Skeleton Room");
	strcpy(map[11]->room_desc,"Opening the door and getting out of the dark hallway, your eyes take some time to adjust to the faint light in this room. And lo and behold- a skeleton, lying on the ground. It gives you the creeps. Stepping over it, you can see another room on your north.\n");
	map[11]->can_go_up=1;
	map[11]->can_go_down=1;
	map[11]->can_go_left=0;
	map[11]->rm_has_npc=0;

	//Room (3,0)
	strcpy(map[12]->room_name,"Bedroom");
	strcpy(map[12]->room_desc,"You step into what seems to be a bedroom. There seems to be a bed, remains of burnt clothes on the ground, and most importantly, a weird mirror in the far end of the room. Looking through the mirror, you can see three humans looking at their computers. (It is the digital age. Of course you know what a computer is.) They suddenly sense the presence in the room, look up at you, and point towards you. You feel a strange force indicating where you need to go.\n");
	map[12]->can_go_up=1;
	map[12]->can_go_right=0;
	map[12]->rm_has_npc=1;

	//Room (3,1)
	strcpy(map[13]->room_name,"Entering the Dark Hallway");
	strcpy(map[13]->room_desc,"You enter a very dark hallway. There is still some light coming from the previous room, but not much. You touch the walls around to see if there's anything, but the only way you can really move is back, and to the east, where the darkness continues.\n");
	map[13]->can_go_up=1;
	map[13]->can_go_left=0;
	map[13]->can_go_right=1;
	map[13]->rm_has_npc=0;

	//Room (3,2)
	strcpy(map[14]->room_name,"Middle of Dark Hallway");
	strcpy(map[14]->room_desc,"Continuing blind and clueless into the darkness, you trip over something and fall down! You feel the ground, then yourself. You are alive, don't worry. Yet there seems to be nothing around you. You get up, and realize the hallway still continues to your east.\n");
	map[14]->can_go_up=0;
	map[14]->can_go_left=1;
	map[14]->can_go_right=1;
	map[14]->rm_has_npc=0;

	//Room (3,3)
	strcpy(map[15]->room_name,"End of Dark Hallway");
	strcpy(map[15]->room_desc,"The darkness continues, and afraid you are indeed, desperately trying to find something or somebody. You move your hands frantically trying to find something, and you seem to touch a wall. And another wall. And another one. And then, just to your north, you feel a door.\n");
	map[15]->can_go_up=1;
	map[15]->can_go_left=1;
	map[15]->rm_has_npc=0;

	return map;
}


//Assumes check_valid_mov is true.
//Map signs: S=starting, X=current, O=visited, -=not visited, ~=mirror flag
void change_map_struct(int init_x, int init_y, int dx, int dy, int flag_num){
	//mirror gets replaced afterwards
	if (flag_num){
		map_struct[1][3]='~';
	}

	if (init_x==0 && init_y==0){
		map_struct[0][0]='S';
		map_struct[init_x+dx][init_y+dy]='X';
	} else {
		if (flag_num && init_x==1 && init_y==3){
			map_struct[1][3]='~';
		} else {
			map_struct[init_x][init_y]='O';
		}
		map_struct[init_x+dx][init_y+dy]='X';
	}
}

void color_matrix(){
	uint16_t led_color = RGB565_CYAN;
	clear_leds();

	for(int i=0;i<4;i++){
		for (int j=0;j<4;j++){
	    //S=red, X=green, O=yellow, -=no color, ~=blue
			if (map_struct[i][j]=='X'){ 
				led_color = RGB565_GREEN;
			}
			else if (map_struct[i][j]=='S'){ 
				led_color = RGB565_RED;
			}
			else if (map_struct[i][j]=='O'){ 
				led_color = RGB565_YELLOW;
			} 
			else if (map_struct[i][j]=='~'){ 
				led_color = RGB565_BLUE;
			}    
			else{ 
				led_color = RGB565_WHITE;
			}

			set_led(i*2,j*2,led_color);
			set_led(i*2+1,j*2+1,led_color);		
			set_led(i*2+1,j*2,led_color);
			set_led(i*2,j*2+1,led_color);

		}	
	}
}

void print_room_moved(room_t** map,int move_rm,int skel_flag,int first_visit){
	if (first_visit){
		printf("%s\n",map[move_rm]->room_name);
		printf("%s\n>",map[move_rm]->room_desc);
		return;
	}
	if (skel_flag && move_rm==11){
		printf("%s\n>",post_skeleton_text);
	} else {
		printf("%s\n%s",map[move_rm]->room_name,((map[move_rm]->rm_visited)?">":""));
		if ((!map[move_rm]->rm_visited))
			printf("%s\n>",map[move_rm]->room_desc);
	}

}

//Function called to move. Flag_num is always the global mirror interaction.
int move_direction(room_t** map,inventory_t* inv,int init_x,int init_y,int dx,int dy,int mirr_flag,int skel_flag){
	int curr_rm=init_x*4+init_y;
	int move_rm=(init_x+dx)*4+init_y+dy;

	//Check for not allowed move on giant's room: If failed to move, call game loss.
	if (curr_rm==0 && !(dx==0 || dy==1)){
		lose_game();
		return 2;
	}

	//Check if move from current room is allowed on map
	//Right move:
	if (dx==0 && dy==1){
		if (!map[curr_rm]->can_go_right){
			printf("You cannot go there, adventurer!\n>");
			return 1;
		}
	}
	//Left move:
	else if (dx==0 && dy==-1){
		if (!map[curr_rm]->can_go_left){
			printf("You cannot go there, adventurer!\n>");
			return 1;
		}
	}
	//Up move:
	else if (dx==-1 && dy==0){
		if (!map[curr_rm]->can_go_up) {
			printf("You cannot go there, adventurer!\n>");
			return 1;
		}
	}
	//Up move:
	else if (dx==1 && dy==0){
		if (!map[curr_rm]->can_go_down){
			printf("You cannot go there, adventurer!\n>");
			return 1;
		} 
	}
	else; //ignore, this should NOT happen if programmed correctly, right?

	//Here, the move is allowed. Update global variable for current room
	current_rm=move_rm;
	curr_rm_x=init_x+dx;
	curr_rm_y=init_y+dy;
	//Move all items that are carried on inventory
	int i=0;
	for(;i<6;i++){
		if (inv->item_list[i]->user_hold)
			inv->item_list[i]->curr_loc_rm=move_rm;
	}
	//Update mirror flag if room visited is wardrobe/mirror
	if (move_rm==12)
		mirror_flag=1;
	//Update map structure for new room
	change_map_struct(init_x,init_y,dx,dy,mirr_flag);
	//Update LED matrix for new room.
	color_matrix();
	//Print text for room moved
	print_room_moved(map,move_rm,skel_flag,0);
	//Update room to visited
	map[move_rm]->rm_visited=1;
	return 0;
}


void print_intro(){
	printf("\n%s\n%s\n>",intro_text[0],intro_text[1]);
}

void print_failed_start(){
	printf("\n%s\n>",failed_start_text);
}

void print_start(){
	printf("\n%s\n",start_text);
}

void print_help(){
	printf("\n%s",help_text);
}

void talk_cat(){
	printf("\n%s\n",talk_cat_text);
}

void talk_mirror(){
	printf("\n%s\n",talk_mirror_text);
}

void talk_self(){
	printf("\n%s\n",talk_self_text);
}

void talk_giant(){
	printf("\n%s\n",talk_giant_text);
}

void init_inventory(){
	inventory=(inventory_t*)malloc(sizeof(inventory));
	inventory->item_list=(item_t**)malloc(sizeof(item_t*)*6);
	init_items();
}

//init structures for game
void init_structures(){
	//clear matrices here
	clear_leds();

	init_inventory();
	map=init_map();
}

//init the game: init global variables, init items/rooms/maps, init matrices and sensors
void initgame(){
	//init matrices, sensors here
	open_led_matrix();

	init_structures();
	
	//init global variables
	dir_move_js=0;
	game_started=0;
	brewed_tea=0;
	current_rm=0;
	mirror_flag=0;
	curr_rm_x=0;
	curr_rm_y=0;
	skeleton_flag=0;
}

//endgame: print stuff, call quit
void endgame(){
	printf("%s\n",endgame_text);
	quit_game();
}

//end the game (loss): print "you died", reset global variables, inventory, map
void lose_game(){
	printf("%s\n>",losing_text);
	dir_move_js=0;
	game_started=0;
	brewed_tea=0;
	current_rm=0;
	mirror_flag=0;	
	curr_rm_x=0;
	curr_rm_y=0;
	skeleton_flag=0;
	init_structures();
}

//quit game
void quit_game(){
	//close led matrices etc here
	clear_leds();
	close_led_matrix();

	exit(0);
}

//brew tea todo
void brew_tea(){
	//supposedly waits for user input
	brewed_tea=1;
}


//Main function, runs on a loop and waits for commands.
int main(){
	//open joystick thread
	pthread_t js_thr;
	struct thread_arg_t js_thr_arg;
	if (pthread_create(&js_thr, NULL, move_joystick, &js_thr_arg)) {
		fprintf(stderr, "Error creating joystick thread\n");
		exit(1);
	}

	initgame();
	print_intro();
	int j_flag=1;
	//Game loop
	for (;;){
		//get initial time
		time_t sec1; 
      	sec1 = time(NULL);
      	j_flag=1;
      	double joy_time=0;
      	//Waiting 4s for input from joystick. If nothing happens, move on.
      	do{
      		if (dir_move_js!=0){
	      		if (game_started){
	      			j_flag=0;
					call_next_command("-");
				} else {
					printf("The game has not even started yet!\n");
					j_flag=0;
					dir_move_js=0;
				}
			}
			time_t sec2;
			sec2=time(NULL);
			double diff=difftime(sec2,sec1);
			joy_time+=diff;
      	} while(joy_time<4);

		//Waiting for user input since joystick 
		if (j_flag!=0){
			char* buf=(char*)malloc(sizeof(char)*50);
			size_t bufsize=50;
			getline(&buf,&bufsize,stdin);
			buf[strcspn(buf,"\n")] = 0;
			call_next_command(buf);
			free(buf);
		}
	}
	quit_game();
	return 0;
}
