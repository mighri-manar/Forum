//
// Created by Manar Mighri and Mehdi Rejeb Kaabia and Rania Fathallah on 14/11/2023.
//

#ifndef STRUCTAUTHOR_AUTHOR_H
#define STRUCTAUTHOR_AUTHOR_H
#include"DATE.h"
#include"PROFIL.h"
#include<time.h>
#include"MESSAGE.h"
#include<stdio.h>



struct AUTHOR
{
    PROFIL profil_author;
    char* pseudo;
    char* date_of_the_last_posted_message ;
    char* date_of_the_first_posted_message;
    int number_of_posted_messages;
    struct nodemsg* LSCmsg;

};
typedef struct AUTHOR AUTHOR;
void Input_author(AUTHOR*, PROFIL* P); //input author data when subscribing
void Show_author(AUTHOR); //prints author details
void Backup_author(AUTHOR* ,int, FILE*); //saves every author's data in a text file
int Add_author_to_base(AUTHOR , AUTHOR**, int*);    //adds an author to the database
void Show_list_author(AUTHOR*,int);       //prints the list of authors
void Insert_reply(nodemsg**, MESSAGE*, AUTHOR*); //inserts a reply at the beginning of LSCreplies of a given msg
void Save_modified_msg(AUTHOR*,MESSAGE); //saves a modified message in the author's LSCmsg
#endif //STRUCTAUTHOR_AUTHOR_H
