//
// Created by Manar Mighri and Mehdi Rejeb Kaabia and Rania Fathallah on 14/11/2023.
//
#include<stdio.h>
#include<stdlib.h>
#include "FORUM.h"
#include"PROFIL.h"
#include<string.h>

/*--------------------------------------------------------------------------------------------------------------------*/

void Input_forum(FORUM* f)
{
    f ->adresse =(char*)malloc(100*sizeof(char));
    printf("\nLink: ");
    fflush(stdin);
    fgets(f->adresse,100, stdin);
    deleteNewline(f->adresse);
    f->email=(char*)malloc(100*sizeof(char));
    printf("\nAdmin: ");
    fgets(f->email,100,stdin);
    deleteNewline(f->email);
    f->length_of_authors_list=0;
    f->length_of_profils_list=0;
    f->length_of_rubriques_list=0;
    f->list_of_authors=NULL;
    f->list_of_profils=NULL;
    f->list_of_rubriques=NULL;

}

/*------------------------------------------prints the forum data-----------------------------------------------------*/

void Show_forum(FORUM f)
{
    printf("\n The organizer's e-mail: %s\n", f.email);
    printf("\n The forum's link: %s\n", f.adresse);
}

/*-------------------------------------------adds a new message to the author's list of messages----------------------*/

int Add_message(MESSAGE *M, AUTHOR* A,FORUM* F, int* l)
{

    M->pseudo_author = strdup(A->pseudo);
    deleteNewline(M->pseudo_author);

    Insert_msg(*M,&A->LSCmsg);   //takes a nodemsg* and a message and adds the message in the beginning of the linked list

    if (A->number_of_posted_messages == 0)
    {
        A->date_of_the_first_posted_message = strdup(M->date_of_creation);
        deleteNewline(A->date_of_the_first_posted_message);
        if (A->date_of_the_first_posted_message == NULL)
        {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    A->date_of_the_last_posted_message = strdup(M->date_of_creation);
    deleteNewline(A->date_of_the_last_posted_message);
    if (A->date_of_the_last_posted_message == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }


    (*l)++;

    // Update the existing author in the forum
    int authorIndex = Find_profil_index(*F, A->profil_author.ID);
    if (authorIndex != -1)
    {
        F->list_of_authors[authorIndex] = *A;
    }

    return 0;
}


/*-----------------------------------looks for a profil, and it returns its index if it exists------------------------*/


int Find_profil_index(FORUM F, int id)
{
    int i=0;
    int pos=-1;

    while(F.list_of_profils[i].ID!=id && i<F.length_of_profils_list)
    {
        i++;
    }

    if(i != F.length_of_profils_list)
        pos = i;
    return pos;
}




/*--------------------------reads the login data and looks if it's saved in the forum---------------------------------*/


int Login(FORUM F,PROFIL *P,AUTHOR *A,int flag) {
    int id, index;
    char* email;

    printf("\nProfil ID: ");
    scanf("%d", &id);

    email = (char*)malloc(100 * sizeof(char));
    printf("\nemail: ");
    fflush(stdin);
    fgets(email, 100, stdin);
    deleteNewline(email);
    index = Find_profil_index(F, id);

    if (index == -1 || strcmp(email, F.list_of_profils[index].email) != 0) {
        printf("\nWrong ID or email! Please check.\n");
        free(email);
        return 0;
    } else {
        printf("-------------------------------------------------------------------------------------------------");

        printf("\n\n                                  Welcome %s %s\n", F.list_of_profils[index].first_name, F.list_of_profils[index].last_name);

        //assigning data if the user was previously subscribed and his data was restored from a txt file
        if (flag==0) {

            P = (PROFIL *) malloc(sizeof(PROFIL));

            P->ID = F.list_of_profils[index].ID;
            P->first_name = strdup(F.list_of_profils[index].first_name);
            deleteNewline(P->first_name);
            P->last_name = strdup(F.list_of_profils[index].last_name);
            deleteNewline(P->last_name);
            P->email = strdup(F.list_of_profils[index].email);
            deleteNewline(P->email);
            P->adresse = strdup(F.list_of_profils[index].adresse);
            deleteNewline(P->adresse);
            P->birth_date.day = F.list_of_profils[index].birth_date.day;
            P->birth_date.month = F.list_of_profils[index].birth_date.month;
            P->birth_date.year = F.list_of_profils[index].birth_date.year;

            A = (AUTHOR *) malloc(sizeof(AUTHOR));
            A->profil_author=*P;
            A->pseudo=strdup(F.list_of_authors[index].pseudo);
            deleteNewline(A->pseudo);
            A->date_of_the_first_posted_message=strdup(F.list_of_authors[index].date_of_the_first_posted_message);
            deleteNewline(A->date_of_the_first_posted_message);
            A->date_of_the_last_posted_message=strdup(F.list_of_authors[index].date_of_the_last_posted_message);
            deleteNewline(A->date_of_the_last_posted_message);
            A->number_of_posted_messages=F.list_of_authors[index].number_of_posted_messages;

        }
        free(email);
        return 1;
    }
}

/*--------------------------input an author with an associated profil and adds it to the forum -----------------------*/

int Subscribe(FORUM* F, PROFIL* P, AUTHOR* A) {

    Input_author(A, P);

    int authorAddResult = Add_author_to_base(*A, &F->list_of_authors, &F->length_of_authors_list);
    int profilAddResult = Add_profil_to_base(A->profil_author, &F->list_of_profils, &F->length_of_profils_list);

    if (authorAddResult == 0 && profilAddResult == 0) {
        printf("-------------------------------------------------------------------------------------------------");

        printf("\n\n                                 Successfully subscribed!\n");
        return 0;
    }

    return -1;
}

/*----------------------------------reads data from a file and stores it in the forum---------------------------------*/

FORUM Bring_back_author(FILE* pf, FORUM* forum) {
    AUTHOR** A;
    int k, j, sizeoftab;
    printf("\nHow many authors do you want to import?\n");
    fflush(stdin);
    scanf("%d", &sizeoftab);
    A = (AUTHOR**)malloc(sizeof(AUTHOR*) * sizeoftab);
    for (j = 0; j < sizeoftab; j++) {
        A[j] = (AUTHOR*)malloc(sizeof(AUTHOR));
        A[j]->profil_author.last_name=(char*)malloc(sizeof(char)*100);
        A[j]->profil_author.first_name=(char*)malloc(sizeof(char)*100);
        A[j]->profil_author.adresse=(char*)malloc(sizeof(char)*100);
        A[j]->profil_author.email=(char*)malloc(sizeof(char)*100);
        // Read profile data
        fscanf(pf, "\n%d;%[^;];%[^;];%d %d %d;%[^;];%[^;];%d",
               &A[j]->profil_author.ID, A[j]->profil_author.last_name, A[j]->profil_author.first_name,
               &A[j]->profil_author.birth_date.day, &A[j]->profil_author.birth_date.month, &A[j]->profil_author.birth_date.year,
               A[j]->profil_author.adresse, A[j]->profil_author.email, &A[j]->profil_author.phone_number);
        // Read author data
        A[j]->pseudo=(char*)malloc(sizeof(char)*100);
        A[j]->date_of_the_first_posted_message=(char*)malloc(sizeof(char)*25);
        A[j]->date_of_the_last_posted_message=(char*)malloc(sizeof(char)*25);
        fscanf(pf, ";%[^;];%[^;];%[^;];%d", A[j]->pseudo, A[j]->date_of_the_first_posted_message,
               A[j]->date_of_the_last_posted_message, &A[j]->number_of_posted_messages);

        A[j]->LSCmsg = NULL;  // Initialize the list of messages to NULL
        for (k = 0; k < A[j]->number_of_posted_messages; k++) {
            nodemsg* new_message = (nodemsg*)malloc(sizeof(nodemsg));

            new_message->datamsg.pseudo_author = (char*)malloc(100 * sizeof(char));
            new_message->datamsg.title = (char*)malloc(100 * sizeof(char));
            new_message->datamsg.text = (char*)malloc(10000 * sizeof(char));
            new_message->datamsg.type = (char*)malloc(2 * sizeof(char));
            new_message->datamsg.date_of_creation = (char*)malloc(25 * sizeof(char));

            // Read message data
            fscanf(pf, ";%[^;];%[^;];%[^;];%[^;];%[^;];%d",
                   new_message->datamsg.pseudo_author, new_message->datamsg.title,
                   new_message->datamsg.text, new_message->datamsg.type, new_message->datamsg.date_of_creation,
                   &new_message->datamsg.number_of_replies);

            new_message->datamsg.LSCreplies = NULL;  // Initialize the list of replies to NULL

            // Read replies for the current message
            for (int reply_index = 0; reply_index < new_message->datamsg.number_of_replies; reply_index++) {
                nodemsg* new_reply = (nodemsg*)malloc(sizeof(nodemsg));

                new_reply->datamsg.pseudo_author = (char*)malloc(100 * sizeof(char));
                new_reply->datamsg.title =NULL;
                new_reply->datamsg.text = (char*)malloc(10000 * sizeof(char));
                new_reply->datamsg.date_of_creation = (char*)malloc(25 * sizeof(char));

                // Read reply data
                fscanf(pf, ";%[^;];%[^;];%[^;]",
                       new_reply->datamsg.pseudo_author,
                       new_reply->datamsg.text, new_reply->datamsg.date_of_creation);
                new_reply->datamsg.type=strdup("R"); //pre-assign type as R(reply)
                // Add the new reply to the beginning of the list
                new_reply->next = new_message->datamsg.LSCreplies;
                new_message->datamsg.LSCreplies = new_reply;
            }

            // Add the new message to the beginning of the list
            new_message->next = A[j]->LSCmsg;
            A[j]->LSCmsg = new_message;
        }
        // Add the profile to the forum's list_of_profils
        Add_profil_to_base(A[j]->profil_author, &(*forum).list_of_profils, &(*forum).length_of_profils_list);
        // Add the author to the forum's list_of_authors
        Add_author_to_base(*A[j], &(*forum).list_of_authors, &(*forum).length_of_authors_list);
    }
    return *forum;
}



/*-------------------------------------------------add reply----------------------------------------------------------*/
void Add_reply(MESSAGE* M, AUTHOR* A, FORUM* F, MESSAGE* R,RUBRIQUE *Ru)
{
    if (M == NULL) {
        printf("\nInvalid message.\n");
        return;
    }
    printf("\ninserting...\n");

    //insert the reply in the lscreplies of the given message
    Insert_reply(&M->LSCreplies, R, A);

    M->number_of_replies++;
    nodemsg* ptr;
    //update the current author if he's replying to himself
    ptr = A->LSCmsg;
    while (ptr != NULL && Check_msg(*M, *ptr) !=0) {
        ptr = ptr->next;
    }
     if (ptr!=NULL) {
        ptr->datamsg = *M;
        // update author and forum
        int authorIndex = Find_profil_index(*F, A->profil_author.ID);
        if (authorIndex != -1) {
            F->list_of_authors[authorIndex] = *A;
        }}
     //if it's a different author, update the forum
     for (int i = 0; i < F->length_of_authors_list; i++) {
         if (strcmp(F->list_of_authors[i].pseudo, M->pseudo_author) == 0) {
             nodemsg* ptr_m;
             ptr_m=F->list_of_authors[i].LSCmsg;
             while(ptr_m != NULL && Check_msg(*M, *ptr_m) !=0) {
                 ptr_m = ptr_m->next;
             }
             if (ptr_m!=NULL) {
                 ptr_m->datamsg = *M;
             }
             break;
         }
     }
     nodemsg* ptr_r;
     ptr_r = Ru->LSCmsg;
     while (ptr_r != NULL && Check_msg(*M, *ptr_r) != 0) {
         ptr_r = ptr_r->next;
        }
     if(ptr_r!=NULL) {
         ptr_r->datamsg=*M;
         //update the existing rubrique in the forum
         int rubriqueIndex = Find_rubrique_index(*F, Ru);
         if (rubriqueIndex != -1)
            {
                Update_rubrique_in_base(*Ru,&F->list_of_rubriques,F->length_of_rubriques_list);
            }
        }

     printf("\ndone!!\n");
}

/*---------------------------------------------------------delete a reply from a given msg----------------------------*/
void Delete_reply(MESSAGE* msg, MESSAGE rep, AUTHOR* A, FORUM* F)
{
    nodemsg* current = msg->LSCreplies;
    nodemsg* previous = NULL;
    printf("\nDeleting a reply...\n");
    while (current != NULL) {
        if ((strcmp(current->datamsg.text, rep.text) == 0 && strcmp(current->datamsg.pseudo_author, rep.pseudo_author) == 0)) {
            // Update the number of replies in the message
            (msg->number_of_replies)--;

            // Delete the reply from the list
            if (previous == NULL) {
                // The reply is the first in the list
                msg->LSCreplies = current->next;
            } else {
                // The reply is somewhere in the middle or at the end
                previous->next = current->next;
            }

            // Free memory for the deleted reply
            free(current);

            // Update author and forum
            Save_modified_msg(A, *msg);
            int authorIndex = Find_profil_index(*F, A->profil_author.ID);
            if (authorIndex != -1)
            {
                F->list_of_authors[authorIndex] = *A;
            }
            // Find the rubrique to which the message belongs
            RUBRIQUE* targetRubrique = Find_Rubrique_Containing_Message(msg, F);
            Save_modified_msg_rubrique(targetRubrique,*msg);
            // Update the number of replies in the rubrique
            if (targetRubrique != NULL) {
                targetRubrique->nb_msg--;
                // Update the rubrique in the forum's list of rubriques
                Update_rubrique_in_base(*targetRubrique, &F->list_of_rubriques, F->length_of_rubriques_list);


                printf("\nReply successfully deleted.\n");
            } else {
                // Handle the case where the rubrique is not found
                printf("\nError: Rubrique not found for the message.\n");
            }

            return;
        }

        previous = current;
        current = current->next;
    }

    // the reply was not found
    printf("\nError: Reply not found.\n");
}

/*-----------------------------------------deletes a given msg from a linked list-------------------------------------*/
void Delete_msg(AUTHOR *A, FORUM *F, MESSAGE M)
{
    printf("\nDeleting a question...\n");
    nodemsg *ptr_auth, *previous_auth, *ptr_R, *previous_R;

    // delete from the author's LSCmsg
    if (!A->LSCmsg)
    {
        printf("\nYou have no messages!\n");
        return;
    }

    ptr_auth = A->LSCmsg;
    previous_auth = NULL;

    while (ptr_auth != NULL && Check_msg(M, *ptr_auth) != 0)
    {
        previous_auth = ptr_auth;
        ptr_auth = ptr_auth->next;
    }

    if (ptr_auth == NULL)
    {
        printf("\nMessage not found in the author's list!\n");
    }
    else
    {
        if (previous_auth == NULL)
        {
            // found in the beginning
            A->LSCmsg = ptr_auth->next;
            free(ptr_auth);
        }
        else
        {
            previous_auth->next = ptr_auth->next;
            free(ptr_auth);
        }

        A->number_of_posted_messages--;

        // update author and forum
        int authorIndex = Find_profil_index(*F, A->profil_author.ID);
        if (authorIndex != -1)
        {
            F->list_of_authors[authorIndex] = *A;
        }
    }

    // delete from the rubrique's LSCmsg
    RUBRIQUE * R;
    R=&F->list_of_rubriques[Find_rubrique_index(*F, Find_Rubrique_Containing_Message(&M,F))];
    ptr_R = R->LSCmsg;
    previous_R = NULL;

    while (ptr_R != NULL && Check_msg(M, *ptr_R) != 0)
    {
        previous_R = ptr_R;
        ptr_R = ptr_R->next;
    }

    if (ptr_R == NULL)
    {
        printf("\nMessage not found in the room's list!\n");
    }
    else
    {
        if (previous_R == NULL)
        {
            // found in the beginning
            R->LSCmsg = ptr_R->next;
            free(ptr_R);
        }
        else
        {
            previous_R->next = ptr_R->next;
            free(ptr_R);
        }

        R->nb_msg--;

        // update rubrique and forum
        int rubriqueIndex = Find_rubrique_index(*F, R);
        if (rubriqueIndex != -1)
        {
            F->list_of_rubriques[rubriqueIndex] = *R;
        }

        printf("\nQuestion deleted!\n");
    }
}

/*---------------------finds a rubrique in the forumand returns its index if it exists--------------------------------*/
int Find_rubrique_index(FORUM F, RUBRIQUE* R)
{

    int i=0;
    int pos=-1;

    while((strcmp(F.list_of_rubriques[i].theme,R->theme)!=0) && (strcmp(F.list_of_rubriques[i].creation_date,R->creation_date)!=0) && (i<F.length_of_profils_list))
    {
        i++;
    }

    if(i != F.length_of_rubriques_list)
        pos = i;
    return pos;

}

/*---------------------------------------------modifies a rubrique info-----------------------------------------------*/
void Modify_rub(RUBRIQUE *R,FORUM* F)
{
    int choice;
    printf("\nWhat do you want to change?\n");
    printf("\n1. Theme\n");
    printf("\n2. Animator\n");
    printf("\n3. E-mail adresse\n");
    printf("-----------------------------------------------------------------------------------------------------");
    printf("\nchoice: \n");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1 :
            fflush(stdin);
            fgets(R->theme,100,stdin);
            deleteNewline(R->theme);break;

        case 2 :
            fflush(stdin);
            fgets(R->animator,100,stdin);
            deleteNewline(R->animator);break;

        case 3 :
            fflush(stdin);
            fgets(R->email_adresse,100,stdin);
            deleteNewline(R->email_adresse);break;

        default :break;

    }
    //update the existing rubrique in the forum
    int rubriqueIndex = Find_rubrique_index(*F, R);
    if (rubriqueIndex != -1)
    {
        F->list_of_rubriques[rubriqueIndex] = *R;
    }
}

/*---------------------------------------modifies a msg data and updates forum, author and rurique--------------------*/
void Modify_msg(MESSAGE* M,FORUM* F,AUTHOR* A,RUBRIQUE* R)
{
    int choice;
    printf("\nWhat do you want to change?\n");
    printf("\n1. Title\n");
    printf("\n2. Text\n");
    printf("\n3. Type\n");
    printf("-----------------------------------------------------------------------------------------------------");
    printf("\nchoice: \n");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1 :
            fflush(stdin);
            fgets(M->title,100,stdin);
            deleteNewline(M->title);break;

        case 2 :
            fflush(stdin);
            fgets(M->text,10000,stdin);
            deleteNewline(M->text);break;

        case 3 :
            fflush(stdin);
            fgets(M->type,2,stdin);
            deleteNewline(M->type);break;

        default :break;

    }
    //update the existing msg in the author's lscmsg
    nodemsg *ptr_R, *ptr_A;
    for (ptr_A=A->LSCmsg;ptr_A!=NULL;ptr_A=ptr_A->next)
    {
        if (Check_msg(*M,*ptr_A)==0)
        {ptr_A->datamsg=*M;break;}
    }
    //update the existing msg in the rub's lscmsg
    for (ptr_R=R->LSCmsg;ptr_R!=NULL;ptr_R=ptr_R->next)
    {
        if (Check_msg(*M,*ptr_R)==0)
        {ptr_R->datamsg=*M;break;}
    }

    //update the existing rubrique in the forum
    int rubriqueIndex = Find_rubrique_index(*F,R);
    if (rubriqueIndex != -1)
    {
        F->list_of_rubriques[rubriqueIndex] = *R;
    }

    // Update the existing author in the forum
    int authorIndex = Find_profil_index(*F, A->profil_author.ID);
    if (authorIndex != -1)
    {
        F->list_of_authors[authorIndex] = *A;
    }
}

/*-----------------------------------reads rubrique data from a file and restores it i the forum----------------------*/
FORUM Bring_back_rub(FILE* pf, FORUM* F) {
    RUBRIQUE **R;
    int k, j, sizeoftab;
    printf("\nHow many rooms do you want to import?\n");
    fflush(stdin);
    scanf("%d", &sizeoftab);
    R = (RUBRIQUE **) malloc(sizeof(RUBRIQUE *));
    for (j = 0; j < sizeoftab; j++)
    {
        R[j] = (RUBRIQUE *) malloc(sizeof(RUBRIQUE));
        R[j]->theme = (char *) malloc(sizeof(char));
        R[j]->creation_date = (char *) malloc(sizeof(char));
        R[j]->animator = (char *) malloc(sizeof(char));
        R[j]->email_adresse = (char *) malloc(sizeof(char));

        //read rubrique data
        fscanf(pf, "\n%[^;];%[^;];%[^;];%[^;];%d", R[j]->theme, R[j]->creation_date,
               R[j]->email_adresse, R[j]->animator, &R[j]->nb_msg);

        R[j]->LSCmsg = NULL;  // Initialize the list of messages to NULL
        for (k = 0; k < R[j]->nb_msg; k++) {
            nodemsg *new_message = (nodemsg *) malloc(sizeof(nodemsg));
            new_message->datamsg.pseudo_author = (char *) malloc(100 * sizeof(char));
            new_message->datamsg.title = (char *) malloc(100 * sizeof(char));
            new_message->datamsg.text = (char *) malloc(10000 * sizeof(char));
            new_message->datamsg.type = (char *) malloc(2 * sizeof(char));
            new_message->datamsg.date_of_creation = (char *) malloc(25 * sizeof(char));


            // Read message data
            fscanf(pf, ";%[^;];%[^;];%[^;];%[^;];%[^;];%d",
                   new_message->datamsg.pseudo_author, new_message->datamsg.title,
                   new_message->datamsg.text, new_message->datamsg.type, new_message->datamsg.date_of_creation,
                   &new_message->datamsg.number_of_replies);

            new_message->datamsg.LSCreplies = NULL;  // Initialize the list of replies to NULL

            // Read replies for the current message
            for (int reply_index = 0; reply_index < new_message->datamsg.number_of_replies; reply_index++) {
                nodemsg *new_reply = (nodemsg *) malloc(sizeof(nodemsg));

                new_reply->datamsg.pseudo_author = (char *) malloc(100 * sizeof(char));
                new_reply->datamsg.title =NULL;
                new_reply->datamsg.text = (char *) malloc(10000 * sizeof(char));

                new_reply->datamsg.date_of_creation = (char *) malloc(25 * sizeof(char));

                // Read reply data
                fscanf(pf, ";%[^;];%[^;];%[^;]",
                       new_reply->datamsg.pseudo_author,
                       new_reply->datamsg.text, new_reply->datamsg.date_of_creation);
                new_reply->datamsg.type = strdup("R");  // Preassign type as "R"

                // Add the new reply to the beginning of the list
                new_reply->next = new_message->datamsg.LSCreplies;
                new_message->datamsg.LSCreplies = new_reply;
            }

            // Add the new message to the beginning of the list
            new_message->next = R[j]->LSCmsg;
            R[j]->LSCmsg = new_message;
        }
        //save the rubrique in the forum
        Add_rubrique_to_base(*R[j],&F->list_of_rubriques,&F->length_of_rubriques_list);
    }
    return *F;
}

/*----------------------------------deletes a rubrique from the forum-------------------------------------------------*/
void Delete_rub(RUBRIQUE R,FORUM* F) {
    int i, j;
    i = Find_rubrique_index(*F, &R);
    if (i == -1) { printf("\nRoom not found!!\n"); }
    else {
        for (j = i; j < F->length_of_rubriques_list-1; j++) {
            F->list_of_rubriques[j] = F->list_of_rubriques[j + 1];
        }
        F->length_of_rubriques_list--;
    }
}
/*---------------------------------adds a given msg to a rubrique-----------------------------------------------------*/
void Add_msg_rub(MESSAGE M, RUBRIQUE* R, FORUM* F)
{
    Insert_msg(M,&R->LSCmsg);
    R->nb_msg++;
    //update the existing rubrique in the forum
    int rubriqueIndex = Find_rubrique_index(*F, R);
    if (rubriqueIndex != -1)
    {
        F->list_of_rubriques[rubriqueIndex] = *R;
    }
}

/*----------------------------------------modifies profile data and nickname------------------------------------------*/

void Modify_personal_details(AUTHOR* A,PROFIL* P,FORUM* F)
{

    int choice;
    printf("\nWhat do you want to change?\n");
    printf("\n1. Nickname\n");
    printf("\n2. First name\n");
    printf("\n3. Last name\n");
    printf("\n4. Birth date\n");
    printf("\n5. Current adresse\n");
    printf("\n6. E-mail adresse\n");
    printf("\n7. Phone number\n");
    printf("-----------------------------------------------------------------------------------------------------");
    printf("\nchoice: \n");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1 :
            fflush(stdin);
            fgets(A->pseudo,100,stdin);
            deleteNewline(A->pseudo);break;

        case 2 :
            fflush(stdin);
            fgets(P->first_name,100,stdin);
            deleteNewline(P->first_name);break;

        case 3 :
            fflush(stdin);
            fgets(P->last_name,100,stdin);
            deleteNewline(P->last_name);break;

        case 4 :
            fflush(stdin);
            Input_date(&P->birth_date);break;

        case 5 :
            fflush(stdin);
            fgets(P->adresse,100,stdin);
            deleteNewline(P->adresse);break;

        case 6 :
            fflush(stdin);
            fgets(P->email,100,stdin);
            deleteNewline(P->email);break;

        case 7 :
            fflush(stdin);
            scanf("%d",&P->phone_number);

        default :break;

    }
    //update the author's profile
    A->profil_author=*P;
    //update the forum
    int Index = Find_profil_index(*F, A->profil_author.ID);
    if (Index != -1)
    {
        F->list_of_authors[Index] = *A;
        F->list_of_profils[Index]=*P;
    }
}
/*---------------------------------------------deletes an account and disconnects-------------------------------------*/
int Delete_account(FORUM *F, AUTHOR A) {
    int index, i, j;
    index = Find_profil_index(*F, A.profil_author.ID);
    if (index == -1) {
        printf("\naccount not found!!\n");
        return 1;
    } else {
        for (i = 0; i < F->length_of_rubriques_list; i++) {
            nodemsg* ptr_R = F->list_of_rubriques[i].LSCmsg;

            while (ptr_R != NULL) {
                if (strcmp(ptr_R->datamsg.pseudo_author, A.pseudo) == 0) {
                    nodemsg* ptr_msg = ptr_R;  // Initialize ptr_msg

                    while (ptr_msg != NULL) {
                        // Keep track of the next message before deleting the current one
                        nodemsg* next_msg = ptr_msg->next;

                        // Delete replies for the current message
                        nodemsg* ptr_rep = ptr_msg->datamsg.LSCreplies;

                        while (ptr_rep != NULL) {
                            // Keep track of the next reply before deleting the current one
                            nodemsg* next_reply = ptr_rep->next;

                            // Delete the current reply
                            Delete_reply(&ptr_msg->datamsg, ptr_rep->datamsg, &A, F);

                            // Move to the next reply
                            if (F->list_of_rubriques[i].LSCmsg->datamsg.number_of_replies==0)
                            {break;}
                            else

                            {ptr_rep = next_reply;}
                        }

                        // Delete the current message
                        Delete_msg(&A, F, ptr_msg->datamsg);

                        // Move to the next message
                        if( F->list_of_rubriques[i].nb_msg==0)
                            break;
                        else {
                            ptr_msg = next_msg;
                        }
                    }
                }

                // Move to the next message in the rubrique
               if( F->list_of_rubriques[i].nb_msg==0)
                   break;
               else
               {ptr_R = ptr_R->next;}
            }
        }

        for (j = index; j < F->length_of_profils_list - 1; j++) {
            F->list_of_authors[j] = F->list_of_authors[j + 1];
            F->list_of_profils[j] = F->list_of_profils[j + 1];
        }

        // free the memory of A
        free(A.pseudo);
        free(A.date_of_the_first_posted_message);
        free(A.date_of_the_last_posted_message);
        free(A.profil_author.email);
        free(A.profil_author.adresse);
        free(A.profil_author.first_name);
        free(A.profil_author.last_name);

        // Free messages for the current author
        nodemsg *current_message = A.LSCmsg;
        while (current_message != NULL) {
            free(current_message->datamsg.title);
            free(current_message->datamsg.text);
            free(current_message->datamsg.type);
            free(current_message->datamsg.pseudo_author);

            // Free replies for the current message
            nodemsg *current_reply = current_message->datamsg.LSCreplies;
            while (current_reply != NULL) {
                nodemsg *temp = current_reply;
                current_reply = current_reply->next;
                free(temp->datamsg.title);
                free(temp->datamsg.text);
                free(temp->datamsg.type);
                free(temp->datamsg.pseudo_author);
                free(temp);
            }

            nodemsg *temp_message = current_message;
            current_message = current_message->next;
            free(temp_message);
        }

        F->length_of_authors_list--;
        F->length_of_profils_list--;
        printf("\naccount deleted!\n");
        return 0;
    }
}

/* -------------- finds the rubrique to which a message belongs in the forum's list of rubriques ---------------------*/
RUBRIQUE* Find_Rubrique_Containing_Message(MESSAGE* msg, FORUM* F)
{
    for (int i = 0; i < F->length_of_rubriques_list; i++) {
        if (Is_Message_In_Rubrique(msg, &F->list_of_rubriques[i])) {
            return &F->list_of_rubriques[i];
        }
    }
    return NULL;
}

/*---------------------------------------------slicing a string-------------------------------------------------------*/
void substring(const char *source, int start, int end, char *result) {
    int j = 0;
    for (int i = start; i < end; i++) {
        result[j++] = source[i];
    }
    result[j] = '\0';
}
/*------------------------------------------prints nb msg posted per day----------------------------------------------*/
void Posted_msgs_perday(FORUM* F)
{
    int days_Count[7] = {0}; // array to store counts for each day

    for (int i = 0; i < F->length_of_rubriques_list; i++) {
        nodemsg *ptrmsg = F->list_of_rubriques[i].LSCmsg;

        while (ptrmsg != NULL) {
            // Extract the day of the week (the first three characters)
            char day_Of_Week[4];
            substring(ptrmsg->datamsg.date_of_creation, 0, 3, day_Of_Week);

            // Update the count based on the day of the week
            if (strcmp("Mon", day_Of_Week) == 0) {
                days_Count[0]++;
            } else if (strcmp("Tue", day_Of_Week) == 0) {
                days_Count[1]++;
            } else if (strcmp("Wed", day_Of_Week) == 0) {
                days_Count[2]++;
            } else if (strcmp("Thu", day_Of_Week) == 0) {
                days_Count[3]++;
            } else if (strcmp("Fri", day_Of_Week) == 0) {
                days_Count[4]++;
            } else if (strcmp("Sat", day_Of_Week) == 0) {
                days_Count[5]++;
            } else if (strcmp("Sun", day_Of_Week) == 0) {
                days_Count[6]++;
            }

            ptrmsg = ptrmsg->next;
        }
    }

    printf("\nPosted messages per day:\n\n");
    printf("Monday: %d\nTuesday: %d\nWednesday: %d\nThursday: %d\nFriday: %d\nSaturday: %d\nSunday: %d\n",
           days_Count[0], days_Count[1], days_Count[2], days_Count[3], days_Count[4], days_Count[5], days_Count[6]);
}


/*---------------------------------------prints nb msgs per author----------------------------------------------------*/
void Contributers(FORUM* F)
{
    int i;
    printf("\nNumber of subscribed authors: %d\n",F->length_of_authors_list);
    printf("\nNumber of questions per author:\n");
    for(i=0;i<F->length_of_authors_list;i++)
    {
        printf("\n%s: %d\n",F->list_of_authors[i].pseudo,F->list_of_authors[i].number_of_posted_messages);
    }
}
/*--------------------------------------prints nb msg per room--------------------------------------------------------*/
void Rooms(FORUM* F)
{
    int i,count_msg=0;
    printf("\nNumber of rooms: %d\n",F->length_of_rubriques_list);
    printf("\nNumber of posted questions per room:\n");
    for(i=0;i<F->length_of_rubriques_list;i++)
    {
        printf("\n%s: %d\n",F->list_of_rubriques[i].theme,F->list_of_rubriques[i].nb_msg);
        count_msg+=F->list_of_rubriques[i].nb_msg;
    }
    if (F->length_of_rubriques_list!=0) {
        printf("\nAverage number of posted questions per room: %d\n", (int) count_msg / F->length_of_rubriques_list);
    }
}
/*----------------------------------finds profiles of authors in a given room-----------------------------------------*/
void Print_authors_profiles(RUBRIQUE R,FORUM F)
{
     int i=0;
     nodemsg* ptr_msg;
     ptr_msg=R.LSCmsg;
     while(ptr_msg!=NULL)
     {
        //look for the correspondent author for each msg
        while((i<F.length_of_authors_list)&&(strcmp(ptr_msg->datamsg.pseudo_author,F.list_of_authors[i].pseudo)!=0))
        {
            i++;
        }
        if (i!=F.length_of_authors_list)
        {
            //prints profile details when found
            Show_profil(F.list_of_authors[i].profil_author);
        }
        ptr_msg=ptr_msg->next;
     }
}
/*----------------------------------prints all messages posted on a given date----------------------------------------*/
void Find_message_by_date(FORUM* F,char* date)
{
    int i, count=0;
    nodemsg* ptr_msg;
    char substr[11];
    for (i=0;i<F->length_of_rubriques_list;i++)
    {
        ptr_msg=F->list_of_rubriques[i].LSCmsg;
        while(ptr_msg!=NULL)
        {
            substring(ptr_msg->datamsg.date_of_creation, 0, 10, substr);
            if (strcmp(substr,date)==0)
            {
                Show_message(ptr_msg->datamsg);
                count++;
            }
            ptr_msg=ptr_msg->next;
        }
    }
    if (count!=0) {
        printf("\n There was(were) %d question(s) posted on this date %s\n", count, date);
    }
    else
    printf("\nNo question(s) posted on this date %s !!\n",date);
}
