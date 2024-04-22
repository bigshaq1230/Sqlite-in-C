#include <stdio.h>
int valid_date(date* d) {
    do
    {
        printf("day: ");
        scanf("%d",d-> jour)
    } while (/* condition */);
    
}
typedef struct
{
    int jour;
    int moins;
    int annee;
} date;
typedef struct
{
    char prenom[15];
    date date_naissance;
    char sexe;
} enfant;
typedef struct 
{
    char nom_pere[15];
    char prenom_mere[10];
    date date_mariage;
    enfant enf[10];
    
}famille;


void repmir(famille* f) {
    printf("nom de pere: ");
    scanf("%s",f->nom_pere);
    printf("prenom de mere: ");
    scanf("%s",f -> prenom_mere);
    
    printf("date de marriage: ");


}

int main()
{
    printf("test");
    return 0;
}
