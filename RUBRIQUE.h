//
// Created by Manar Mighri  on 18/12/2023.
//

#ifndef TEST3_RUBRIQUE_H
#define TEST3_RUBRIQUE_H
#include"MESSAGE.h"
#include"AUTHOR.h"
typedef struct
{
    char* theme;
    char* creation_date;
    char* email_adresse, *animator;
    int nb_msg;
    nodemsg* LSCmsg;

}RUBRIQUE;

void Input_rubrique(RUBRIQUE*,AUTHOR); //input a room's data when adding a new one
void Show_rubrique(RUBRIQUE); //prints a room's data
void Show_list_rub(RUBRIQUE*,int); //prints each room's data saved in a table
int Add_rubrique_to_base(RUBRIQUE, RUBRIQUE**,int*); //adds a room the database of the forum
void Backup_rub(RUBRIQUE* , int,FILE*); //saves every room's data in a text file
void Save_modified_msg_rubrique(RUBRIQUE* , MESSAGE ); //saves a modified msg back to its room

int Is_Message_In_Rubrique(MESSAGE*, RUBRIQUE*); //checks if a room contains a given msg
void Update_rubrique_in_base(RUBRIQUE, RUBRIQUE**, int ); //takes a modified room and saves it in the forum
void Delete_msg_rub(RUBRIQUE*, MESSAGE); //deletes a given msg from the active room if it exists there

#endif //TEST3_RUBRIQUE_H
