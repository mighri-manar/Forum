//
// Created by Manar Mighri on 18/12/2023.
//

#include "RUBRIQUE.h"
#include"MESSAGE.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"AUTHOR.h"
/*--------------------------------------------------Input a new room---------------------------------------------------*/
void Input_rubrique(RUBRIQUE *R,AUTHOR A)
{
    R->theme = (char *) malloc(sizeof(char)*100);
    printf("\nTheme: ");
    fflush(stdin);
    fgets(R->theme,100,stdin);
    deleteNewline(R->theme);

    time_t t;
    time(&t);
    R->creation_date=(char*)malloc(sizeof(char)*25);
    strncpy(R->creation_date, ctime(&t), 25);
    R->creation_date[25] = '\0';
    deleteNewline(R->creation_date);

    R->animator = strdup(A.pseudo);
    deleteNewline(R->animator);

    R->email_adresse = (char *) malloc(sizeof(char)*100);
    printf("\nE-mail adresse: ");
    fflush(stdin);
    fgets(R->email_adresse,100,stdin);
    deleteNewline(R->email_adresse);

    R->nb_msg=0;
    R->LSCmsg=NULL;

}

/*--------------------------------------------------prints a room------------------------------------------------------*/
void Show_rubrique(RUBRIQUE R)
{
    int i=0;
    printf("\nTheme: %s\n",R.theme);

    printf("\nCreation date: %s\n",R.creation_date);

    printf("\nAnimator: %s             E-mail adresse: %s\n",R.animator,R.email_adresse);

    printf("\nNumber of posts: %d\n",R.nb_msg);

    printf("\nHighlights:\n");

    nodemsg* current_msg;
    for (current_msg=R.LSCmsg; current_msg != NULL; current_msg = current_msg->next)
    {
        printf("\nQ%d: %s\n",i+1,current_msg->datamsg.title);
        i++;
    }
}

/*--------------------------------------------saves a room in a file---------------------------------------------------*/
void Backup_rub(RUBRIQUE *LR, int l, FILE* pf)
{
    int j;

    for (j = 0; j < l; j++) {
        // Backup rubrique data
        fprintf(pf, "\n%s;%s;%s;%s;%d",LR[j].theme,LR[j].creation_date,LR[j].email_adresse,LR[j].animator,LR[j].nb_msg);

        nodemsg* current_message = LR[j].LSCmsg;

        while (current_message != NULL) {
            // Backup message data
            fprintf(pf, ";%s;%s;%s;%s;%s;%d",
                    current_message->datamsg.pseudo_author, current_message->datamsg.title,
                    current_message->datamsg.text, current_message->datamsg.type, current_message->datamsg.date_of_creation,current_message->datamsg.number_of_replies);

            // Backup replies for the current message
            nodemsg* current_reply = current_message->datamsg.LSCreplies;
            while (current_reply != NULL) {
                fprintf(pf, ";%s;%s;%s;%d",
                        current_reply->datamsg.pseudo_author,current_reply->datamsg.text, current_reply->datamsg.date_of_creation,current_reply->datamsg.number_of_replies);
                current_reply = current_reply->next;
            }

            // Move to the next message in the list
            current_message = current_message->next;
        }
    }

}

/*--------------------------------------------------------------------------------------------------------------------*/
int Add_rubrique_to_base(RUBRIQUE R, RUBRIQUE **LR, int *l)
{
    // Increment the size before reallocating
    (*l)++;

    // Allocate memory for the updated array
    RUBRIQUE* temp = (RUBRIQUE*)realloc(*LR, sizeof(RUBRIQUE) * (*l));

    // Check if reallocation was successful
    if (temp != NULL)
    {
        *LR = temp;
        (*LR)[*l - 1] = R;
        return 0;
    }
    else
    {
        fprintf(stderr, "\nError: Memory reallocation failed.\n");

        // Reset the size to its original value
        (*l)--;

        return -1; // Indicate failure
    }
}


/*-----------------------------------saves changes in the room's LSCmsg-----------------------------------------------*/
void Save_modified_msg_rubrique(RUBRIQUE* Ru, MESSAGE M)
{
    nodemsg* ptr;
    ptr = Ru->LSCmsg;
    while (ptr != NULL && ptr->datamsg.title != M.title)
    {
        ptr = ptr->next;
    }
    if (ptr == NULL)
    {
        printf("\nMessage not found in the rubrique!\n");
        return;
    }
    else
    {
        ptr->datamsg = M;
        return;
    }
}

/*---------------------------------------------prints the list of rooms----------------------------------------------*/
void Show_list_rub(RUBRIQUE* LR, int n)
{
    int i;
    printf("\nlist of rooms:\n");
    for (i=0;i<n;i++)
    {
        printf("\n-----------------------------------------------------------------------------------------------\n");
        printf("\nRoom %d\n",i+1);
        Show_rubrique(LR[i]);


    }
}
/* ---------------- checks if a message is in a room based on title and pseudo author --------------------------------*/
int Is_Message_In_Rubrique(MESSAGE* msg, RUBRIQUE* rubrique)
{
    nodemsg* current = rubrique->LSCmsg;

    while (current != NULL) {
        if (strcmp(msg->title, current->datamsg.title) == 0 &&
            strcmp(msg->pseudo_author, current->datamsg.pseudo_author) == 0) {
            // Messages are considered equal
            return 1;
        }

        current = current->next;
    }
    return 0;
}


/* ------------------------- updates a room in the forum -------------------------------------------------------------*/
void Update_rubrique_in_base(RUBRIQUE R, RUBRIQUE** LR, int l)
{
    for (int i = 0; i < l; i++) {
        if ((strcmp((*LR)[i].theme,R.theme)==0) &&(strcmp((*LR)[i].creation_date,R.creation_date)==0)) {
            (*LR)[i] = R;  // Update the rubrique in the list
            return;
        }
    }
}

/*--------------------------------deletes a msg from the active room--------------------------------------------------*/
void Delete_msg_rub(RUBRIQUE* R,MESSAGE M) {
    nodemsg *ptr_R, *previous_R;
    ptr_R = R->LSCmsg;
    previous_R = NULL;

    while ((ptr_R != NULL) && (Check_msg(M, *ptr_R) !=0)) {
        previous_R = ptr_R;
        ptr_R = ptr_R->next;
    }

    if (ptr_R == NULL) {
        printf("\nMessage not found in the active room!\n");
    } else {
        if (previous_R == NULL) {
            // found in the beginning
            R->LSCmsg = ptr_R->next;
            free(ptr_R);
        } else {
            previous_R->next = ptr_R->next;
            free(ptr_R);
        }

        R->nb_msg--;
    }
}

