#ifndef _DEF_H_
#define _DEF_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "joystick.h"
#include "led_matrix.h"

typedef struct _room_t{
	int rm_index;
	int rm_visited; 		//needed to color the map
	int in_room_now;		//-''-
	int rm_has_item;
	int rm_can_interact;
	int rm_has_npc;
	char* room_name;
	char* room_desc;
	int can_go_left;
	int can_go_right;
	int can_go_up;
	int can_go_down;
}room_t;

typedef struct _item_t{
	int item_index;			//index
	char* item_name;		//name
	char* item_desc;		//description
	int item_src_rm;		//source location
	int curr_loc_rm;		//current location
	int user_hold;			//item is in inventory
	int item_used;			//is used
	int item_hidden;		//is hidden
	int item_final;			//in final place
}item_t;

typedef struct _invent_t{
	item_t** item_list;		//TODO: define once story finalized.
}inventory_t;

struct thread_arg_t {
	unsigned int index;
};


//GLOBAL VARIABLES GO HERE
int game_started;
int brewed_tea;
int current_rm;
int curr_rm_x;
int curr_rm_y;
int mirror_flag;
int skeleton_flag;
inventory_t* inventory;
room_t** map;
int dir_move_js;

//TEXTS GO HERE
char intro_text[2][300]={
	"You wake up inside a dimly lit room from the loud shrieks of a never seen before creature. In a state of panic, you realize all of your belongings are gone, and your only possessions are a loaf of bread and a seemingly burnt piece of paper, on it written in red letters \"Help me\".\n\n",
	"Write \"start\" to begin your adventure, or \"quit\" to escape this world of madness. Write \"help\" at any time to see the available commands.\n"
};

char help_text[630]=
	"Help is on the way, adventurer!\n\nTo move towards a direction: \"go <direction>\". Directions accepted: north, south, west, east. You can also move the Raspberry Pi's joystick towards that particular direction.\nTo have the room text shown again: \"look\".\nCheck your belongings: \"inventory\".\nUse an item: \"use <item>\", but of course you need to be able to see the particular item.\nSame to pick up said item:\"pick <item>\".\nTalk to someone: \"talk\". You can always try talking to yourself where there is nobody else around, but you may appear to be a lunatic.\nTo escape this world of madness: \"quit\".\n>";
;

char losing_text[50]=
	"You died! To restart, enter \"start\"\n";

char endgame_text[1200]=
	"As the hot chamomile tea touches the giant frog, you hear a scream louder than a volcano eruption- at least it sounds that bad to you. The creature is shrieking, as the tea corrodes its skin and turns it into water. When this mess is done, you see a puddle of water in the middle of the room, in it sitting some weird kind of trousers. You search them, and find a key. You can also see an unlocked door in the distance, behind where the giant used to be standing. The first thing that's on your mind: of course, free the prisoners! And so you rush to the prison cells. As you unlock the doors, you see the cat jumping towards you and rushing towards the giant room. You both run towards the door in the giant's room. The cat, fast as it is, jumps over the puddle and runs out the door. As you are just ready to escape, you hear the cat talking to you: \"Thank you, Bond. And goodbye. Forever.\" She closes the door right behind you. No matter what you do, you can't open it. You get enraged, and use all of your human power to try to find a way to open it, but to no avail. Eventually, you realize you will be trapped in here. Forever.\nGood job, Bond! You won!\nYet nobody won.\n";

char start_text[45]=
	"Your adventure begins here, brave one!\n";

char failed_start_text[75]=
	"Your adventure has already begun! To restart, one first has to quit.\n";

char talk_giant_text[140]=
	"You try talking to the giant. He answers \"No entiendo español, señor!\" and proceeds to grab you with his giant tongue and eat you.\n";

char talk_self_text[160]=
	"You try talking to yourself, for no reason whatsoever. You officially are a lunatic. Understandable though- it must be getting tiring roaming around.\n";

char talk_cat_text[453]=
	"\"Hello?\" you mutter, as out of the shadows jumps a feline creature, which you recognize instantly- it is your magical talking cat, Sharona. \"My my my my Sharona\" is the only thing that comes out of your mouth. \"What happened?\" \"You don't remember a thing, do you? I've been captured by the giant frog- it wants to use my magical powers to transform ground into zucchini. No idea why. You have to stop him! And feed me. I am hungry. Meow.\"\n";

char talk_mirror_text[420]=
	"\"Hello?\", you say, and the guys turn to you, answering \"Oh hey! Do you want some of that pizza we're having?\" \"No\", you reply. \"Do you know anything about the giant?\" \"Obviously you dummy, we are thes who coded the game. You have to find it out on your own, or look at the source code. But that just takes all the fun away, doesn't it?\" They then turn away back to their computers, busy as they are.\n";


//DEFINITIONS FOR ALL FUNCTIONS GO HERE
void print_intro();
void print_failed_start();
void print_start();
void print_help();
void talk_cat();
void talk_mirror();
void talk_self();
void talk_giant();

room_t** init_map();
void change_map_struct(int init_x, int init_y, int dx, int dy, int flag_num);
void color_matrix();
void print_room_moved(room_t** map,int move_rm,int skel_flag,int first_visit);
int move_direction(room_t** map,inventory_t* inv,int init_x,int init_y,int dx,int dy,int mirr_flag,int skel_flag);

void init_items();
int allow_use_item(int item_ind,int curr_rm);
int pick_item(int item_ind,int curr_rm);
int use_item(inventory_t* inv,int item_ind,int curr_rm,int tea_brewed);
void print_inventory(inventory_t* inv);

void call_next_command(char* input);
void* move_joystick(void* arg);

void init_inventory();
void init_structures();
void initgame();
void endgame();
void lose_game();
void quit_game();
void brew_tea();

#endif
