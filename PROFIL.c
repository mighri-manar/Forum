//
// Created by Manar Mighri and Mehdi Rejeb Kaabia and Rania Fathallah on 15/11/2023.
//

#include "PROFIL.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*----------------------------------------*/
void deleteNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void Input_profil(PROFIL* P)
{
    printf("\nSubscription ID:\n");
    fflush(stdin);
    scanf("%d",&P->ID);

    P->last_name=(char*)malloc(100*sizeof(char));
    printf("\nLast name:\n");
    fflush(stdin);
    fgets(P->last_name,100,stdin);
    deleteNewline(P->last_name);

    P->first_name=(char*)malloc(100*sizeof(char));
    printf("\nFirst name:\n");
    fflush(stdin);
    fgets(P->first_name,100,stdin);
    deleteNewline(P->first_name);

    printf("\nBirth date:");
    fflush(stdin);
    Input_date(&P->birth_date);

    P->adresse=(char*)malloc(100*sizeof(char));
    printf("\nCurrent adresse:\n");
    fflush(stdin);
    fgets(P->adresse,100,stdin);
    deleteNewline(P->adresse);

    P->email=(char*)malloc(100*sizeof(char));
    printf("\nE-mail adresse:\n");
    fflush(stdin);
    fgets(P->email,100,stdin);
    deleteNewline(P->email);

    printf("\nPhone number:\n");
    fflush(stdin);
    scanf("%d",&P->phone_number);

}
/*----------------------------------------*/

void Show_profil(PROFIL P)
{
    printf("\nInscription ID: %d\n",P.ID);
    printf("\nLast name: %s\n", P.last_name);
    printf("\nFirst name: %s\n",P.first_name);
    printf("\nBirth date:\n");
    Show_date(P.birth_date);
    printf("\nCurrent adresse: %s\n", P.adresse);
    printf("\nE-mail adresse: %s\n",P.email);
    printf("\nPhone number: %d\n",P.phone_number);

}

/*-------------------adds a new profil to the forum---------------------*/

int Add_profil_to_base(PROFIL P, PROFIL** LP, int* l)
{
    (*l)++;
    PROFIL* temp = (PROFIL*)realloc(*LP, sizeof(PROFIL) * (*l));

    // Check if reallocation was successful
    if (temp != NULL)
    {
        *LP = temp;
        (*LP)[*l - 1] = P;
        return 0;
    }
    else
    {
        fprintf(stderr, "\nError: Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }
}
/*-------------------prints the list of profils---------------------*/
void Show_list_profils(PROFIL* LP, int n)
{
    int i;
    printf("\nlist of profils:\n");
    for (i=0;i<n;i++)
    {
        printf("\nProfile %d\n",i+1);
        Show_profil(LP[i]);
        printf("\n-----------------------------------------------------------------------------------------------\n");

    }
}
