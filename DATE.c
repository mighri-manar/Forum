//
// Created by manar mighri and Mehdi Rejeb Kaabia and Rania Fathallah on 14/11/2023.
//

#include "DATE.h"
#include<stdio.h>

void Input_date(DATE* D)
{
    printf("\nDay\n");
    fflush(stdin);
    scanf("%d",&D->day);
    printf("\nMonth\n");
    scanf("%d",&D->month);
    printf("\nYear\n");
    scanf("%d",&D->year);
}
/*----------------------------------------*/
void Show_date(DATE D)
{
    printf("\n%d/",D.day);
    printf("%d/",D.month);
    printf("%d\n",D.year);
}
/*----------------------------------------*/
 char *Return_date(DATE D)
{

    static char date_string[11];
    sprintf(date_string, "%02d/%02d/%04d", D.day, D.month, D.year);
    return date_string;
}
/*----------------------------------------*/
DATE Read_date( char* D)
{
    DATE date;
    sscanf(D, "%d/%d/%d", &date.day, &date.month, &date.year);
    return date;
}
/*----------------------------------------*/
void initialize_date(DATE* D)
{
    D->day=0;
    D->month=0;
    D->year=0;
}



