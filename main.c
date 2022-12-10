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


void triRapid(int tab[],int tab1[],int tab2[],int first, int last) {
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
                permuter(&tab2[i], &tab2[j]);         
            }
        }
        permuter(&tab[pivot], &tab[j]);
        permuter(&tab1[pivot], &tab1[j]);
        permuter(&tab2[pivot], &tab2[j]);
        triRapid(tab,tab1,tab2, first, j - 1);
        triRapid(tab,tab1,tab2, j + 1, last);
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
	fgets(pid,255,fichier); //enlever le mot uid
	fgets(time,255,fichier1);//enlever le mot time
	double somme[nbligne+1];
	char * colonne = strtok (time, ":" );
	
	struct processus ps[nbligne+1];
	struct ordonnanceur ordo[nbligne+1];
    	
    	for(i=0;i<nbligne;i++)
	{
		fgets(pid,255,fichier); //premiere donnee uid
		fgets(time,255,fichier1);//premiere donnee time
		ps[i].PID=atoi(pid);
		ordo[i].ordrearrivee=i;//enregistre le rang d'arrivée de chaque ps	
        	strcpy(ordo[i].tempsexecution,time);//copier le contenu du time dans ordo[i].tempsexecution
        	strcpy(ps[i].TIME,time);//copier le contenu du time dans ordo[i].tempsexecution  
        	colonne = strtok (ordo[i].tempsexecution, ":" );//les données à couper pour les heures 
        	somme[i]=atoi(colonne)*100000; 
        	colonne =strtok (NULL, ":" );//les données à couper pour les heures
        	somme[i]=somme[i]+atoi(colonne)*100;
        	colonne = strtok (NULL, ":" );//les données à couper pour les heures
        	somme[i]=somme[i]+atoi(colonne);
        	somme[i]=(double)somme[i]+(ordo[i].ordrearrivee+1)*(1.0/1000);//sommer avec le rang qui sera en décimale pour les doublons de temps    	
        	}  
        
//-------------------------------------------------------------remettre le PID dans l'ordre-------------------------------------------------------------------------------------------------     
        printf("Rang   PID   Time\n");
        int PID[nbligne];//on va ranger le pid pour éviter des erreurs absurdes lors du tri    
        int rang[nbligne];//on va ranger le rang pour éviter des erreurs absurdes lors du tri
        int sommeint[nbligne];//on va multiplier par 100 pour les trier par la suite
        for(i = 0; i < nbligne; i++)  {
        PID[i]=ps[i].PID;
        rang[i]=ordo[i].ordrearrivee+1;
        sommeint[i]=round(somme[i]*1000);
        printf("%d   %d      %s\n",ordo[i].ordrearrivee+1,ps[i].PID,ps[i].TIME); 
        }
        printf("\nAprès le tri:\n");	
        triRapid(sommeint,PID,rang,0,nbligne-1);//ranger dans l'ordre croissant
        
        printf("Rang   PID   Time\n");                                          
   	for(i = 0; i < nbligne; i++)  {
        printf("%d   %d      %s\n",rang[i],PID[i],ps[rang[i]-1].TIME);
        }
	printf("\nAinsi le rang de priorité pour l'ordonnanceur est:\n");
	printf("Rang   PID   Time\n");
	for(i = 0; i < nbligne; i++)  {
        printf("%d   %d      %s\n",i+1,PID[i],ps[rang[i]-1].TIME);
        }	
    
    	fclose(fichier);
    	fclose(fichier1);
    	return 0;


}



	
	
	
	


