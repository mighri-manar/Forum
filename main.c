
// created by Manar Mighri and Mehdi Rejeb Kaabia and Rania fathallah on 16/11/2023

#include"FORUM.h"
#include"MENU.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

int main()
{   //the value of each choice must be re-initialized to 0 once tho loop is broken so the user can re-enter the loop again
    int choice1,choice2=0,choice3=0,choice4=0,choice5=0,choice6=0,choice7=0,choice8=0,choice9=0,choice10,choice11=0,
    choice12=0,choice13=0,choice14=0,choice15=0,choice16=0,choice17=0,choice18=0;
    int room; //index of the chosen room to open
    int question; // index of the chosen msg to open
    int reply; //index of the reply to delete
    int deleteflag=0; // this flag helps with breaking the login loop to disconnect the user once he deletes his account (line 222)
    int flag=0; // this flag is meant to indicate to the login function if it's an old or new user, its value will be updated once the subscribe function is called (line 330)
    FORUM F;
    AUTHOR A;
    PROFIL P;
    RUBRIQUE R;
    MESSAGE M,rep;
    char date[11];

    FILE *pf,*fp;
    char nomfichpf[100];
    char nomfichfp[100];

    Input_forum(&F); //initializes the forum's fields

    //open file to read author data
    printf("\nGive the filename you want to open(author): ");
    fflush(stdin);
    fgets(nomfichpf, sizeof(nomfichpf), stdin);
    nomfichpf[strcspn(nomfichpf, "\n")] = '\0';

    if (access(nomfichpf, F_OK) == -1) {
        printf("Author file does not exist.\n");
    }
    pf = fopen(nomfichpf, "a+");
    if (pf == NULL)
    {
        perror("Error opening author file");
        return EXIT_FAILURE;
    }

    // Check if the file is empty
    fseek(pf, 0, SEEK_END); // Move to the end of the file
    long size_auth = ftell(pf);  // Get the current position, which is the size of the file

    if (size_auth!=0) {
        fseek(pf, 0, SEEK_SET);   // Move the file position indicator to the beginning
        Bring_back_author(pf, &F);
        printf("\nAuthors successfully loaded!\n");
    }
    // open file to read rubrique data
    printf("\nGive the filename you want to open(rooms): ");
    fflush(stdin);
    fgets(nomfichfp, sizeof(nomfichfp), stdin);
    nomfichfp[strcspn(nomfichfp, "\n")] = '\0';
    if (access(nomfichfp, F_OK) == -1) {
        printf("room file does not exist.\n");
    }

    fp = fopen(nomfichfp, "a+");

    if (fp == NULL)
    {
        perror("Error opening room file");
        return EXIT_FAILURE;
    }
    // Check if the file is empty
    fseek(fp, 0, SEEK_END); // Move to the end of the file
    long size_room = ftell(fp);  // Get the current position, which is the size of the file

    if (size_room!=0) {
        fseek(fp, 0, SEEK_SET);  // Move the file position indicator to the beginning
        Bring_back_rub(fp,&F);
        printf("\nRooms successfully loaded!\n");
    }

    while (1) {
        choice1 = Menu();
        switch (choice1) {

            case 1 :

                if (Login(F,&P,&A,flag) == 1) {

                    while ((choice2!=4) && (deleteflag!=1)) {
                        choice10=0; // if the user deletes his account and logs out, the value of choice10 must be reinitialized in case he wants to delete another account he creates later
                        choice2 = Welcome();
                        switch (choice2) {
                            case 1:
                                while(choice3!=4){
                                    choice3 = Menu_login_explore();
                                    switch (choice3) {
                                        case 1 :
                                            Input_rubrique(&R, A);
                                            Add_rubrique_to_base(R, &F.list_of_rubriques, &F.length_of_rubriques_list);
                                            while (choice4 != 4) {
                                                choice4 = Menu_login_explore_add_new_room();
                                                switch (choice4) {
                                                    case 1 :
                                                        Input_message(&M);
                                                        Add_message(&M, &A, &F, &A.number_of_posted_messages);
                                                        Add_msg_rub(M, &R, &F);
                                                        break;
                                                    case 2 :
                                                        Modify_rub(&R, &F);
                                                        break;
                                                    case 3:
                                                        Delete_rub(R,&F);
                                                        break;
                                                    default:
                                                        break;
                                                }
                                            }
                                            choice4=0;
                                            break;

                                        case 2 :

                                            while (choice5 != 2) {
                                                Show_list_rub(F.list_of_rubriques, F.length_of_rubriques_list);
                                                choice5 = Menu_login_explore_rooms();
                                                if (choice5 == 1) {
                                                    printf("\nchose a room you want to open\n");
                                                    scanf("%d", &room);
                                                    printf("\n-----------------------------------------------%s----------------------------------------------------\n",F.list_of_rubriques[room-1].theme);
                                                    Show_linked_list_questions(F.list_of_rubriques[room-1].LSCmsg);
                                                    while (choice6 != 4) {
                                                        choice6 = Menu_login_explore_rooms_select_room();
                                                        switch (choice6) {
                                                            case 1 :

                                                                while (choice7 != 3)
                                                                {
                                                                    printf("\nSelect a question you want to open\n");
                                                                    scanf("%d", &question);
                                                                    MESSAGE msg;
                                                                    msg=*Select_message(F.list_of_rubriques[room-1].LSCmsg,question);
                                                                    Show_explicit_msg(msg);
                                                                    choice7 = Menu_login_explore_rooms_select_room_select_quest();
                                                                    if (choice7 == 1) {
                                                                        Input_reply(&rep);
                                                                        Add_reply(&msg, &A, &F, &rep,&R);
                                                                    }
                                                                    else
                                                                        if(choice7==2)
                                                                        {
                                                                            char* word;
                                                                            word=(char*)malloc(sizeof(char)*100);
                                                                            printf("\nType something to look for!\n");
                                                                            scanf("%s",word);
                                                                            Search_word_in_message(word,&msg);
                                                                        }
                                                                }
                                                                choice7=0;

                                                                break;

                                                            case 2 :
                                                                Input_message(&M);
                                                                Add_message(&M, &A, &F,&A.number_of_posted_messages);
                                                                Add_msg_rub(M, &F.list_of_rubriques[room-1], &F);
                                                                break;

                                                            case 3 :

                                                                Print_authors_profiles(F.list_of_rubriques[room-1],F);
                                                                break;
                                                            default :
                                                                break;
                                                        }
                                                    }
                                                    choice6=0;
                                                }
                                            }
                                            choice5=0;
                                            break;

                                        case 3 :
                                            printf("\nType the date you want to search for!\n");
                                            printf("\nPlease respect this Format Ddd Mmm xx\nexemple: Fri Dec 01\n");
                                            fflush(stdin);
                                            fgets(date,11,stdin);
                                            deleteNewline(date);
                                            Find_message_by_date(&F,date);
                                            break;
                                        default : break;
                                    }}
                                choice3=0;
                                break;
                            case 2 :
                                while(choice8!=3){
                                    choice8=Menu_login_settings();
                                    switch(choice8)
                                    {
                                        case 1 :
                                            while(choice9!=4)
                                            {
                                                choice9=Menu_login_settings_account();
                                                switch(choice9)
                                                {
                                                    case 1 :
                                                        Show_author(A);
                                                        break;
                                                    case 2 :
                                                        Modify_personal_details(&A,&P,&F);
                                                        break;

                                                    case 3 :
                                                            choice10=Menu_delete_account();
                                                            if(choice10==1)
                                                            {
                                                                Delete_account(&F,A);
                                                                choice9=4;
                                                                deleteflag=1; break;
                                                            }
                                                            else if (choice10==2)
                                                            {break;}
                                                            break;
                                                    default : break;
                                                }
                                            }
                                            choice9=0;
                                            break;
                                        case 2 :
                                            while(choice11!=2)
                                            {
                                                choice11=Menu_login_settings_posts();
                                                if(choice11==1)
                                                {
                                                    while(choice12!=2)
                                                    {
                                                        Show_linked_list_questions(A.LSCmsg);
                                                        choice12=Menu_login_settings_posts_questions();
                                                        if (choice12==1){
                                                            printf("\nchose a question you want to open!\n");
                                                            scanf("%d",&question);
                                                            while(choice14!=4)
                                                            {
                                                                MESSAGE msg;
                                                                msg=*Select_message(A.LSCmsg,question);
                                                                Show_explicit_msg(msg);
                                                                choice14=Menu_login_settings_posts_questions_select();
                                                                switch(choice14)
                                                                {
                                                                    case 1 :
                                                                        Modify_msg(&msg,&F,&A,&R);
                                                                        break;
                                                                    case 2 :
                                                                        Delete_msg(&A,&F, msg);
                                                                        Show_rubrique(R);

                                                                        break;
                                                                    case 3 :
                                                                        printf("\nchose a reply you want to delete\n");
                                                                        scanf("%d",&reply);
                                                                        MESSAGE rep1;
                                                                        rep1=*Select_message(msg.LSCreplies,reply);
                                                                        Delete_reply(&msg,rep1,&A,&F);
                                                                        printf("\ndelete done!!\n");
                                                                        Save_modified_msg_rubrique(&R,msg);
                                                                        break;
                                                                    default : break;
                                                                }
                                                            }
                                                            choice14=0;
                                                        }
                                                    }
                                                    choice12=0;
                                                }
                                            }
                                            choice11=0;
                                            break;
                                        default : break;
                                    }
                                }
                                choice8=0;
                                break;

                            case 3 :
                                while(choice15!=4)
                                {
                                    choice15=Menu_login_about();
                                    switch(choice15)
                                    {
                                        case 1 :
                                            Show_list_author(F.list_of_authors,F.length_of_authors_list);
                                            while(choice13!=2)
                                            {
                                                choice13=Menu_login_about_users();
                                                if(choice13==1)
                                                {
                                                    int author;
                                                    printf("\nchose an author you want to stalk! ;)\n");
                                                    scanf("%d",&author);

                                                    Show_linked_list_questions(F.list_of_authors[author-1].LSCmsg);
                                                }
                                            }
                                            choice13=0;
                                            break;
                                        case 2 :
                                            Posted_msgs_perday(&F);
                                            Contributers(&F);
                                            Rooms(&F);
                                            break;
                                        case 3 :
                                            Show_forum(F);
                                            break;
                                        default : break;
                                    }
                                }
                                choice15=0;
                                break;
                            default : break;
                        }
                    }
                choice2=0;
                }
                break;
            case 2 :
                Subscribe(&F, &P, &A);
                flag=1;
                break;


            case 3 :
                while(choice16!=2) {
                    choice16=Menu_visit();
                    if (choice16==1)
                    {
                        while(choice17!=2) {
                            Show_list_rub(F.list_of_rubriques,F.length_of_rubriques_list);
                            choice17 = Menu_visit_explore();
                            if(choice17==1)
                            {
                                printf("\nchose a room you want to open\n");
                                scanf("%d",&room);
                                Show_linked_list_questions(F.list_of_rubriques[room - 1].LSCmsg);
                                while(choice18!=2)
                                {
                                    choice18=Menu_visit_rooms_select_room_select_quest() ;
                                    if (choice18==1) {
                                        choice18 = Menu_visit_rooms_select_room();
                                        printf("\nchose a question you want to open\n");
                                        scanf("%d", &question);
                                        MESSAGE msg;
                                        msg = *Select_message(F.list_of_rubriques[room - 1].LSCmsg, question);
                                        Show_explicit_msg(msg);
                                    }
                                }
                                choice18=0;
                            }
                        }
                        choice17=0;
                    }
                }
                choice16=0;
                break;

            case 4 :
                printf("\nBacking up authors...\n");
                Backup_author(F.list_of_authors, F.length_of_authors_list, pf);
                printf("\nBackup done!!\n");

                printf("\nBacking up rooms...\n");
                Backup_rub(F.list_of_rubriques,F.length_of_rubriques_list,fp);
                printf("\nBackup done!\n");
                fclose(fp);
                fclose(pf);


                free(F.email);
                free(F.adresse);
                for (int i = 0; i < F.length_of_authors_list; i++) {
                    free(F.list_of_authors[i].pseudo);
                    free(F.list_of_authors[i].date_of_the_first_posted_message);
                    free(F.list_of_authors[i].date_of_the_last_posted_message);
                    free(F.list_of_authors[i].profil_author.email);
                    free(F.list_of_authors[i].profil_author.adresse);
                    free(F.list_of_authors[i].profil_author.first_name);
                    free(F.list_of_authors[i].profil_author.last_name);

                    // Free messages for the current author
                    nodemsg* current_message = F.list_of_authors[i].LSCmsg;
                    while (current_message != NULL) {
                        free(current_message->datamsg.title);
                        free(current_message->datamsg.text);
                        free(current_message->datamsg.type);
                        free(current_message->datamsg.pseudo_author);

                        // Free replies for the current message
                        nodemsg* current_reply = current_message->datamsg.LSCreplies;
                        while (current_reply != NULL) {
                            nodemsg* temp = current_reply;
                            current_reply = current_reply->next;
                            free(temp->datamsg.title);
                            free(temp->datamsg.text);
                            free(temp->datamsg.type);
                            free(temp->datamsg.pseudo_author);
                            free(temp);
                        }
                        nodemsg* temp_message = current_message;
                        current_message = current_message->next;
                        free(temp_message);
                    }
                }

                free(F.list_of_authors);
                free(F.list_of_profils);
                return 0;
            default: break;
        }
    }
}
