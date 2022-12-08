#include <stdio.h>
#include "math.h"
#include <string.h>
#include <stdlib.h>
int i;


void permuter(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
void triRapid(int tab[],int tab1[], int first, int last) {
    int pivot, i, j;
    if(first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while(tab[i] <= tab[pivot] && i < last)
                i++;
            while(tab[j] > tab[pivot])
                j--;
            if(i < j) {
                permuter(&tab[i], &tab[j]);
                permuter(&tab1[i], &tab1[j]);
            }
        }
        permuter(&tab[pivot], &tab[j]);
        permuter(&tab1[pivot], &tab1[j]);
        triRapid(tab,tab1, first, j - 1);
        triRapid(tab,tab1, j + 1, last);
    }
}

int main(){
//--------------------------------------------------------------------struct processus et ordonnanceur--------------------------------------------------------------------------  	
    	struct processus{
    	int PID;
    	char TIME[10];
    	};
    	
    	
    	
	struct ordonnanceur{
	char tempsexecution[10];
	int ordrearrivee;
	};
	
//--------------------------------------------------------------------------------------nombre de ligne-----------------------------------------------------------------------------------------
	int nbligne=0;
	FILE * compter=fopen("time.txt","r");  
	char texte[256];
	fgets(texte,255,compter); 
	while(fgets(texte,255,compter)!=NULL)
	{
		nbligne++;
	}
	fclose(compter);
	
//-----------------------------------------------------------------------PID et time à traiter---------------------------------------------------------------------------------------------------------
	FILE * fichier=fopen("PID.txt","r");
	FILE * fichier1=fopen("time.txt","r");
	char pid[256]; 
	char time[256];
	fgets(pid,255,fichier); //enlever uid
	fgets(time,255,fichier1);//enlever time
	int somme[nbligne+1];
	char * colonne = strtok (time, ":" );
	
	struct processus ps[nbligne+1];
	struct ordonnanceur ordo[nbligne+1];
    	
    	for(i=0;i<nbligne;i++)
	{
		fgets(pid,255,fichier); //premiere donnee uid
		fgets(time,255,fichier1);//premiere donnee time
		ps[i].PID=atoi(pid);	
        	strcpy(ordo[i].tempsexecution,time);
        	somme[i]=0; //on va chercher à sommer les heures*10000, les minutes*100 et les seconde*1  
        	colonne = strtok (time, ":" );//les données à couper pour les heures 
        	somme[i]=somme[i]+atoi(colonne)*100000; 
        	colonne =strtok (time, ":" );//les données à couper pour les heures
        	somme[i]=somme[i]+atoi(colonne)*100;
        	colonne = strtok (time, ":" );//les données à couper pour les heures
        	somme[i]=somme[i]+atoi(colonne)*1;       	
        	}  
        
//-------------------------------------------------------------remettre le PID dans l'ordre-------------------------------------------------------------------------------------------------     
        printf("PID\n");
        for(i = 0; i < nbligne; i++)  {
        printf("%d\n",ps[i].PID); //afficher PID
        }
        	
        triRapid(somme,&ps->PID,0,nbligne-1);  
         
        printf("PID\n");                                           
   	for(i = 0; i < nbligne; i++)  {
        printf("%d\n",ps[i].PID);
        }
		
    
    	fclose(fichier);
    	fclose(fichier1);
    	return 0;


}



	
	
	
	



