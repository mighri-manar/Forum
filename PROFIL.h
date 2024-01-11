//
// Created by Manar Mighri and Mehdi Rejeb Kaabia and Rania Fathallah on 15/11/2023.
//

#ifndef STRUCTUREMESSAGE_PROFIL_H
#define STRUCTUREMESSAGE_PROFIL_H
#include "DATE.h"
 typedef struct
 {
  int ID;
  char* last_name,*first_name;
  DATE birth_date;
  char* adresse, *email;
  int phone_number;
 }PROFIL;


void Input_profil(PROFIL*); //input profile data when subscribing
void Show_profil(PROFIL); //prints profile data
void deleteNewline(char*); //deletes the character \n after using fgets or strdup
int Add_profil_to_base(PROFIL, PROFIL**,int*);    //adds a profil to the database
void Show_list_profils(PROFIL*,int);

#endif //STRUCTUREMESSAGE_PROFIL_H
