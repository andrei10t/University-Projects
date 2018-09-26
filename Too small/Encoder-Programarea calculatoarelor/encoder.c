#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void codcar(char *t, char *mesaj)
{
	int array[255] = {0}, brray[255]={0}, v; // faci elementele 0, pe v il folosim ca sa evitam un warning
	int i, min, index, xedni, max;
	
	
	for(i = 0; mesaj[i] != 0; i++)
	{
		v=mesaj[i];   		
		++array[v];
	}
	
	min = strlen(mesaj);	// ce a fost folosit cel mai putin
					
	index = 0;
	for(i = 0; mesaj[i] != 0; i++)	
	{
		v=mesaj[i];     		
		if( array[v] < min)
     		{
        		min = array[v];
         		index = i;
     		}
	}

	for(i = 0; mesaj[i] != 0; i++)
	{
		v=mesaj[i];   		
		++brray[v];
	}

	max = brray[0];				//ce a fost folosit cel mai mult
	xedni = 0;
	for(i = 0; mesaj[i] != 0; i++)
	{
		v=mesaj[i];       	
		if( brray[v] > max)
 	    	{
        		max = brray[v];
                	xedni = i;
 	        }
	}
	char invers[50]="\0";
	if(strlen(mesaj)==0)				//daca prima linie citita este un caracter
	{
		strcat(mesaj,t);
	}	
	else	
	{
		invers[0]=mesaj[xedni]; 	
		strcat(mesaj,invers);
		strcat(mesaj,t);
		invers[0]=mesaj[index];
		strcat(mesaj,invers);
	}
}	

void codnumn(char *t, char *mesaj)
{
	int max,k,c,i,j,u,p;	
	k=strlen(t);
	
	for(p=0;p<k-1;p++)			//scap de minusul din fata
		t[p]=t[p+1];
	t[k-1]='\0';
	
	max=atoi(t);
	c=max;
	
	for(i=0;i<k-2;i++)
	{
		u=c%10;
		for(j=1;j<k-1;j++)
			u=u*10;
		c=c/10+u;
		if(max>c)
			max=c;
	}
	
	char str[50]="\0";
	sprintf(str,"%d", max);	
	strcat(mesaj,str);
}


void codnump(char *t, char *mesaj)
{
	int max,k,c,i,j,u;	
	max=atoi(t);
	k=strlen(t);
	c=max;
	for(i=0;i<k-1;i++)
	{
		u=c%10;
		for(j=1;j<k;j++)
			u=u*10;
		c=c/10+u;
		if(max<c)
			max=c;
	}
	char str[50]="\0";
	sprintf(str,"%d", max);  // transform din int in char si duc in str
	strcat(mesaj,str);
}



void codcuv(char *t, char *mesaj)
{
	char s[50];
	memset(s, '\0', sizeof(s)); // e ceva legat de initializare lui s	
	
	if ((strlen(t)>0) && (t[strlen (t) - 1] == '\n')) // elimin \n daca e cazul, pentru ca fgets iti ia si \n 
        	t[strlen (t) - 1] = '\0';
	int l, i, d;
	l=strlen(t);  
	
	for(i=1;i<=l/2;i++)	//determinare cm mare div -d 
		if(l%i==0)
			d=i;
		

	strncpy(s,t,d); // pun in s caracterele pe care le duci la coada.
	
	char *P= t+d;  //pun in P caracterele de la d incolo
	

	char *ret;                          // verific daca t contine caractere numerice
	ret=strpbrk(t,"0123456789");
	if(ret)
	{
		int p = strlen(P) ;
    		int c,j;

    		for (i =0, j=p-1; i<j; i++, j--)   // inversez P-ul.
    		{
        		c = P[i];
        		P[i] = P[j];
        		P[j] = c;
    		}
		char invers[50]="\0";   	 //aduc in mesaj cele doua parti de cuvant lipite
		strcat(invers,P);		//folosesc invers ca sa nu stric adresa lui mesaj
		strcat(invers,s);
		strcat(mesaj, invers);
		                          		
	}	
	else
	{
		char invers[50]="\0";
		strcat(invers,P);
		strcat(invers,s);
		strcat(mesaj, invers);
		
	}
	
}



void citire()
{		
	char *mesaj=malloc(5000);
	int cu=0, ca=0, nu=-1, p; //capacitate , nr cuvinte, nr caractere , nr numere, nr total de chestii
	char *t=malloc(50); //termen ! 		
	fgets(t, 50, stdin);
	
	if ((strlen(t)>0) && (t[strlen (t) - 1] == '\n')) // elimin \n daca e cazul, pentru ca fgets iti ia si \n 
        	t[strlen (t) - 1] = '\0';
						
	while(strcmp(t,"END")!=0) 
	{
		if ((strlen(t)>0) && (t[strlen (t) - 1] == '\n')) // elimin \n daca e cazul, pentru ca fgets iti ia si \n 
        		t[strlen (t) - 1] = '\0';		
		

		if (strspn(t, "0123456789")==strlen(t)) // verific daca contine caractere exclusiv numerice
		{
			nu++;
			codnump(t, mesaj);	
		}
			
		else
		{	p=atoi(t);			//verific daca este negativ
			if(p<0)
			{
				nu++;				
				codnumn(t,mesaj);
			}
			else
			{
				if (strlen(t)==1)  // verific daca este singur pe linie
				{
					ca++;
					codcar(t,mesaj);
				}	
				else
				{
					cu++;
					codcuv(t, mesaj);
				}
			}
		}	
			free(t);			//eliberez memoria alocata lui t si aloc din nou pentru ca ma chinui prea mult cu vectori de termeni
			char *t=malloc(50);
			scanf("%s",t);
	}
		
	
		printf("%d %d %d\n", cu, ca, nu); 	// ce cere la task1
		mesaj[strlen (mesaj) - 1] = '\0';	//sa scapam de numarul citit inainte de end	
		printf("%s\n",mesaj);	
	
}

int main()
{
	citire();
	return 0;
}	
