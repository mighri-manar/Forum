//
// Created by Manar Mighri and Mehdi Rejeb Kaabia and Rania Fathallah on 14/11/2023.
//
#include<stdio.h>
#include<stdlib.h>
#include "MESSAGE.h"
#include<string.h>
#include"PROFIL.h"

/*---------------=------------------------------------writes a message------------------------------------------------*/

void Input_message(MESSAGE* M) {
    {
        M->title = (char*)malloc(100 * sizeof(char));
        if (M->title == NULL) {
            fprintf(stderr, "\nError: Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        printf("\nTitle:");
        fflush(stdin);
        if (fgets(M->title, 100, stdin) == NULL) {
            fprintf(stderr, "\nError reading input.\n");
            exit(EXIT_FAILURE);
        }
        M->title[strcspn(M->title, "\n")] = '\0';

        M->text = (char*)malloc(10000 * sizeof(char));
        if (M->text == NULL) {
            fprintf(stderr, "\nError: Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        printf("\nMessage:\n");
        if (fgets(M->text, 10000, stdin) == NULL) {
            fprintf(stderr, "\nError reading input.\n");
            exit(EXIT_FAILURE);
        }
        M->text[strcspn(M->text, "\n")] = '\0';

        M->type = (char*)malloc(2 * sizeof(char));
        if (M->type == NULL) {
            fprintf(stderr, "\nError: Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        printf("\nwhat's the type of the message(Q/R)?\n");
        fflush(stdin);
        if (fgets(M->type, 2, stdin) == NULL) {
            fprintf(stderr, "\nError reading input.\n");
            exit(EXIT_FAILURE);
        }
        M->type[strcspn(M->type, "\n")] = '\0';

        M->date_of_creation = (char*)malloc(25 * sizeof(char));
        if (M->date_of_creation == NULL) {
            fprintf(stderr, "\nError: Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        time_t t;
        time(&t);
        strncpy(M->date_of_creation, ctime(&t), 25);
        M->date_of_creation[25] = '\0';
        deleteNewline(M->date_of_creation);

        M->number_of_replies=0;
        M->LSCreplies=NULL;
    }

/*------------------------------------------------prints a message----------------------------------------------------*/
}
void Show_message(MESSAGE M) {
        printf("\nAuthor: %s\n", M.pseudo_author);
        printf("\nTitle: %s\n", M.title);
        printf("\n%s\n", M.text);
        printf("\nType of the message: %s\n", M.type);
        printf("\nCreation date: %s\n", M.date_of_creation);
        printf("\nNumber of replies: %d\n",M.number_of_replies);
}
/*--------------------------------------------------------------------------------prints a message--------------------*/

void Show_explicit_msg(MESSAGE M)
{
    printf("\n%s\n",M.text);
    Show_linked_list_replies(M.LSCreplies);
    printf("\n\n\n");
}
/*------------------------------------------------------------------------------------finds a msg---------------------*/

int Check_msg(MESSAGE FM, nodemsg M)
{
    return strcmp(M.datamsg.pseudo_author, FM.pseudo_author) != 0 ||
           strcmp(M.datamsg.date_of_creation, FM.date_of_creation) != 0;
}



/*-------------------------------------------------------------insert a msg in the beginning of a linked list---------*/

void Insert_msg(MESSAGE new_message, nodemsg** LSCmsg)
{
    nodemsg* new_node = (nodemsg*)malloc(sizeof(nodemsg));
    if (new_node == NULL)
    {
        fprintf(stderr, "\nError: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    new_node->datamsg.pseudo_author = strdup(new_message.pseudo_author);
    new_node->datamsg.title = strdup(new_message.title);
    new_node->datamsg.text = strdup(new_message.text);
    new_node->datamsg.type = strdup(new_message.type);
    new_node->datamsg.date_of_creation = strdup(new_message.date_of_creation);
    new_node->datamsg.number_of_replies=new_message.number_of_replies;
    new_node->datamsg.LSCreplies = NULL;

    new_node->next = *LSCmsg;
    *LSCmsg = new_node;
}


/*-------------------------------------------------------------------------prints a linked list of replies------------*/
void Show_linked_list_replies(nodemsg*LM)
{
    if (LM== NULL)
    {printf("\nNo replies yet!\n ");}
    else
    {
        nodemsg* ptr;
        int count = 1;

        // Display each message with its number
        for (ptr = LM; ptr != NULL; ptr = ptr->next)
        {
            printf("\nReply %d:\n", count);
            Show_reply(ptr->datamsg);
            count++;
        }
}}
/*--------------------------------------------prints messages with numbers--------------------------------------------*/
void Show_linked_list_questions(nodemsg* LM)
{
    if (LM== NULL)
    {printf("\nNo questions yet!\n ");}
    else
    {
        nodemsg* ptr;
        int count = 1;

        for (ptr = LM; ptr != NULL; ptr = ptr->next)
    {
           printf("\nQuestion %d:\n", count);
           Show_message(ptr->datamsg);
           count++;
    }
}}
/*----------------------------------------------------------------------prints a reply--------------------------------*/
void Show_reply(MESSAGE reply)
{
    printf("\nAuthor: %s\n",reply.pseudo_author);
    printf("\n%s\n",reply.text);
}


/*-----------------------------------------------Input reply-----------------------------------------------------------*/
void Input_reply(MESSAGE* M)
{
    M->text = (char*)malloc(10000 * sizeof(char));
    if (M->text == NULL) {
        fprintf(stderr, "\nError: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    printf("\nReply:\n");
    fflush(stdin);
    if (fgets(M->text, 10000, stdin) == NULL) {
        fprintf(stderr, "\nError reading input.\n");
        exit(EXIT_FAILURE);
    }
    M->text[strcspn(M->text, "\n")] = '\0';

    M->type = strdup("R");  // Preassign type as "R"

    M->date_of_creation = (char*)malloc(25 * sizeof(char));
    if (M->date_of_creation == NULL) {
        fprintf(stderr, "\nError: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    time_t t;
    time(&t);
    strncpy(M->date_of_creation, ctime(&t), 25);
    M->date_of_creation[25] = '\0';
    deleteNewline(M->date_of_creation);
    M->title=NULL;
    M->number_of_replies=0;
    M->LSCreplies=NULL;
}
/*------------------------------------------Select a message from the list--------------------------------------------*/
MESSAGE* Select_message(nodemsg* LM, int selectedNumber)
{
    nodemsg* ptr;
    int count;

    // Find and return the selected message
    count = 1;
    for (ptr = LM; ptr != NULL; ptr = ptr->next)
    {
        if (count == selectedNumber)
        {
            return &(ptr->datamsg);
        }
        count++;
    }

    return NULL;
}

/*--------------------------------------------------------------------------------------------------------------------------*/
void Free_Message(MESSAGE *msg)
{
    free(msg->title);
    free(msg->text);
    free(msg->type);
    free(msg->pseudo_author);

    // Free the replies associated with the message
    Free_Replies(msg->LSCreplies);

    // Free the memory occupied by the message structure itself
    free(msg);
}


void Free_Replies(nodemsg *LSCreplies)
{
    while (LSCreplies != NULL)
    {
        nodemsg *temp = LSCreplies;
        LSCreplies = LSCreplies->next;

        free(temp->datamsg.title);
        free(temp->datamsg.text);
        free(temp->datamsg.type);
        free(temp->datamsg.pseudo_author);

        // Free the reply node itself
        free(temp);
    }
}

/*----------------------------search for a word in a given message and prints the first occurrence--------------------*/

void Search_word_in_message(const char *word, const MESSAGE *msg) {
    const char *found = strstr(msg->text, word);

    if (found != NULL) {
        printf("'%s' found in the message at position %ld\n", word,(long)( found - msg->text));
    } else {
        printf("word not found!!\n");
    }
}







