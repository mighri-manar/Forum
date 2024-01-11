//
// Created by Manar Mighri on 14/11/2023.
//

#ifndef UNTITLED_FORUM_H
#define UNTITLED_FORUM_H
#include "AUTHOR.h"
#include"RUBRIQUE.h"
#include"MESSAGE.h"
#include"PROFIL.h"
#include<stdio.h>


typedef struct
{
char* adresse;
char* email;
AUTHOR* list_of_authors;
int length_of_authors_list;
RUBRIQUE * list_of_rubriques;
int length_of_rubriques_list;
PROFIL* list_of_profils;
int length_of_profils_list;

}FORUM;

void Input_forum(FORUM*); //initializes the forum's fields
void Show_forum(FORUM); //prints the email and the forum's link

FORUM Bring_back_author(FILE*,FORUM*); //reads author data from a file

int Find_profil_index(FORUM, int);  //finds the profil associated to an id
int Login(FORUM,PROFIL*,AUTHOR*,int); //takes an ID and an email and checks if those exist in the forum
int Subscribe(FORUM*,PROFIL* , AUTHOR* ); //adds a new user to the forum

void Print_authors_profiles(RUBRIQUE R,FORUM F); //looks for the profiles of every author that posted a question in a given room

void Delete_msg(AUTHOR*,FORUM*,MESSAGE); //deletes a given msg from an author's lscmsg if it exists, and updates the forum
int Add_message(MESSAGE*, AUTHOR*,FORUM*, int*); //takes a msg inserts it by calling the function insert_msg and updates the data of the author
void Modify_msg(MESSAGE*,FORUM*,AUTHOR*,RUBRIQUE*); //modifies a msg data

void Delete_reply(MESSAGE *, MESSAGE,AUTHOR* , FORUM *); //deletes a given reply from a given msg and updates what must be updated
void Add_reply(MESSAGE* ,AUTHOR* ,FORUM *,MESSAGE *,RUBRIQUE*); //adds a msg to a LSCmsg by calling insert_reply and updates what must be updated

FORUM Bring_back_rub(FILE*, FORUM*);  //reads data from a file and saves it back in the forum
int Find_rubrique_index(FORUM, RUBRIQUE*); //finds the index a given room in the forum
void Modify_rub(RUBRIQUE*, FORUM *F); //modifies a rooms data and updates the forum
void Delete_rub(RUBRIQUE,FORUM*); //deletes a room from the forum
void Add_msg_rub(MESSAGE, RUBRIQUE*,FORUM*); //adds a msg to a given room
RUBRIQUE* Find_Rubrique_Containing_Message(MESSAGE*, FORUM* );  //finds a room containing a given msg


void Modify_personal_details(AUTHOR*,PROFIL*,FORUM*); //modifies an account data
int Delete_account(FORUM*,AUTHOR); //deletes an account from the forum(author+profile) and deletes every posted msg by that author


//statistics

void Posted_msgs_perday(FORUM*); //prints the number of posted questions per day
void Contributers(FORUM*);  //prints the number of posted msgs per author
void Rooms(FORUM*);  //prints the nnumber of posted msgs per room and the average nb msg per room
void Find_message_by_date(FORUM*,char*);  //prints all messages posted on a given date

#endif //UNTITLED_FORUM_H
