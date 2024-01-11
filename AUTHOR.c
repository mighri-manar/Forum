//
// Created by Manar Mighri on 14/11/2023.
//

#include "AUTHOR.h"
#include<stdio.h>
#include<stdlib.h>
#include"PROFIL.h"
#include<string.h>


/*--------------------------------------------------------------------------------------------------------------------*/

void Input_author(AUTHOR* a, PROFIL* P)
{
    Input_profil(P);
    a->profil_author=*P;
    fflush(stdin);
    a->pseudo=(char*)malloc(100*sizeof(char));
    printf("\nPseudo:\n");
    fgets(a->pseudo, 100,stdin);
    deleteNewline(a->pseudo);


    a->number_of_posted_messages=0;
    a->LSCmsg=NULL;
    a->date_of_the_first_posted_message=NULL;
    a->date_of_the_last_posted_message=NULL;

}
/*--------------------------------------------------------------------------------------------------------------------*/
void Show_author(AUTHOR a)
{
    Show_profil(a.profil_author);
    printf("\nPseudo: %s\n",a.pseudo);
    printf("\nFirst message posted on: %s\n",a.date_of_the_first_posted_message);
    printf("\nLast message posted on: %s\n",a.date_of_the_last_posted_message);
    printf("\nNumber of posted messages: %d\n",a.number_of_posted_messages);
}



/*-------------------------------------------------------save author in a file----------------------------------------*/
void Backup_author(AUTHOR* LA, int l, FILE* pf) {
    int  j;

    for (j = 0; j < l; j++) {
        // Backup profile data
        fprintf(pf, "\n%d;%s;%s;%d %d %d;%s;%s;%d",
                LA[j].profil_author.ID, LA[j].profil_author.last_name, LA[j].profil_author.first_name,
                LA[j].profil_author.birth_date.day, LA[j].profil_author.birth_date.month, LA[j].profil_author.birth_date.year,
                LA[j].profil_author.adresse, LA[j].profil_author.email, LA[j].profil_author.phone_number);

        // Backup author data
        fprintf(pf, ";%s;%s;%s;%d",
                LA[j].pseudo, LA[j].date_of_the_first_posted_message,
                LA[j].date_of_the_last_posted_message, LA[j].number_of_posted_messages);

        nodemsg* current_message = LA[j].LSCmsg;

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
/*-------------------------------------------adds a new author to the forum-------------------------------------------*/
int Add_author_to_base(AUTHOR A, AUTHOR** LA, int* l)
{
    (*l)++;
    AUTHOR* temp = (AUTHOR*)realloc(*LA, sizeof(AUTHOR) * (*l));

    // Check if reallocation was successful
    if (temp != NULL)
    {
        *LA = temp;
        (*LA)[*l - 1] = A;
        return 0;
    }
    else
    {
        fprintf(stderr, "\nError: Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

/*-----------------------------------------------------prints the list of authors-------------------------------------*/

void Show_list_author(AUTHOR* LA, int n)
{
    int i;
    printf("\n-----------------------------------------------------------------------------------------------\n");

    printf("\nlist of authors:\n");
    for (i=0;i<n;i++)
    {
        printf("\nAuthor %d:\n",i+1);
        Show_author(LA[i]);
        printf("\n                                  ***************                                       \n");

    }
}

/*--------------------------------------------adds a reply to lscreplies of a given message---------------------------*/
void Insert_reply(nodemsg** LR, MESSAGE *R, AUTHOR* A)
{
    R->pseudo_author = strdup(A->pseudo);
    deleteNewline(R->pseudo_author);

    nodemsg* new_node = (nodemsg*)malloc(sizeof(nodemsg));
    if (new_node == NULL)
    {
        fprintf(stderr, "\nError: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    new_node->datamsg.pseudo_author = strdup(R->pseudo_author);
    new_node->datamsg.title = NULL;
    new_node->datamsg.text = strdup(R->text);
    new_node->datamsg.type = strdup(R->type);
    new_node->datamsg.date_of_creation = strdup(R->date_of_creation);
    new_node->datamsg.number_of_replies=R->number_of_replies;
    new_node->datamsg.LSCreplies = NULL;

    new_node->next = *LR;
    *LR = new_node;
}
/*-----------------------------------------saves changes in the author lscmsg-----------------------------------------*/
void Save_modified_msg(AUTHOR *A, MESSAGE M)
{
    nodemsg* ptr;
    ptr=A->LSCmsg;
    while (ptr!=NULL && ptr->datamsg.title!=M.title) {

        ptr=ptr->next;
    }
    if(ptr==NULL)
    {printf("\nmessage not found!\n");return;}
    else
    {ptr->datamsg=M;return;}
}



