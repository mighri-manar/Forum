//
// Created by manar mighri on 14/11/2023.
//

#ifndef STRUCTUREMESSAGE_MESSAGE_H
#define STRUCTUREMESSAGE_MESSAGE_H
#include"DATE.h"
#include<time.h>
struct nodemsg;
struct MESSAGE
{
    char* title;
    char* text;
    char* date_of_creation;
    char* pseudo_author;
    char* type;
    int number_of_replies;
    struct nodemsg* LSCreplies;

};
typedef struct MESSAGE MESSAGE;


struct nodemsg
{
    MESSAGE datamsg ;
    struct nodemsg * next ;
};
typedef struct nodemsg nodemsg;


void Input_message(MESSAGE*); //input message data when adding a new one
void Input_reply(MESSAGE*);   //input repply data when adding a new one
void Show_message(MESSAGE);    //prints a message data

void Insert_msg(MESSAGE, nodemsg**);  //inserts a reply in a LSCreplies of a given msg
void Show_linked_list_replies(nodemsg*); // prints a list of replies

void Show_reply(MESSAGE); //prints data of a single reply
void Show_linked_list_questions(nodemsg*); //prints data of a LSCmsg
void Show_explicit_msg(MESSAGE); //prints replies of a given msg
int Check_msg(MESSAGE,nodemsg); //checks if a msg is equal to another given msg
MESSAGE* Select_message(nodemsg*, int);  //takes an index of a message and returns the corresponding msg
void Free_Replies(nodemsg *);
void Free_Message(MESSAGE *);

void Search_word_in_message(const char *, const MESSAGE *);  //takes a word and looks if it exists in a text of a given msg


#endif //STRUCTUREMESSAGE_MESSAGE_H
