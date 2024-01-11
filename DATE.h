//
// Created by manar mighri and Mehdi Rejeb Kaabia and Rania Fathallah on 14/11/2023.
//

#ifndef STRUCTUREMESSAGE_DATE_H
#define STRUCTUREMESSAGE_DATE_H

typedef struct
{
    int day, month, year;
}DATE;
void Input_date(DATE*);
void Show_date(DATE);

//these functions were replaced with time.h library
char* Return_date(DATE);
DATE Read_date(char*);
void Initialize_date(DATE*);

#endif //STRUCTUREMESSAGE_DATE_H
