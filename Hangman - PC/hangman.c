#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/select.h>

#define STR_MAX_LEN 		100
#define KEYBOARD		0
#define SELECT_EVENT		1
#define SELECT_NO_EVENT		0


void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	
	char *choices[] = { 
			"New Game",
			"Resume Game",
			"Quit",
		  };
	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < 3; ++i)
	{	if(highlight == i + 1) 			// high light alegerea curenta 
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}

void new_game(char exp[])
{
	
	srand(time(NULL));	// ca de fiecare data cand folosim functia random sa primim un alt rezultat.
	initscr(); 

	int nfds, sel;       //pentru temporizator
	char s[STR_MAX_LEN];
	fd_set read_descriptors;
	struct timeval timeout;	

	char tc[500];    //absolut toate caracterele folosite
	int j,i;   
	int row,col;
	int startx = 0;
	int starty = 0;
	int lung=0,     	// lungimea expresiei 
       	l=0, 		       
       	gresite=0,           
       	vizibile=0,             // cate caractere sunt vizibile   
       	corecte=0,              // cate caractere sunt ghicite      
       	flag_c=0,               // semnal pentru o litera ghicita        
       	flag_r=0;        	// semnal pentru o litera care s-a mai folosit       
	
// o sa fac eu citirea din fisier aici a unui cuvant
	
	
	char incorecte[255]=" ";     // literele introduse de user care nu fac parte din expresie
	char ch;
	
	lung=strlen(exp);
	char vizibil[lung];          // ce ai ghicit pana acum 
	for(l=0;l<lung;l++)
      	vizibil[l]='_';
	vizibil[lung]='\0';
	
	int r; 			//ce ar trebui sa fie vizibil de la inceput
		
	vizibil[0]=exp[0];
			//prima si ultima litera din expresie
	vizibil[lung-1]=exp[lung-1];
	
	for(r=1;r<lung-1;r++)
	{
		if(exp[r]==32)
		{	vizibil[r-1]=exp[r-1];   //prima si ultima litera a cuvintelor
			vizibil[r+1]=exp[r+1];
		
		}
	}
	for(r=0;r<lung;r++)
	{
		if(exp[r]==32 && exp[r+3]==exp[r])    //asundem a doua litera in cazul cuvintelor de 2 caractere
		{
			vizibil[r+2]='_';
			
		}
		if(exp[r]==32 && exp[r+2]==exp[r])	//pentru cuvintele compuse dintr-un singur caracter
		{
			vizibil[r+1]='_';
			
		}
		if(exp[1]==32)
		{
			vizibil[0]='_';
			
		}
		if(exp[lung-2]==32)
		{
			vizibil[lung-1]='_';
			
		}		
	}

	for(r=0;r<lung;r++)       
	{
		if(exp[r]==32)   //afisam spatiile libere;
		{
			vizibil[r]=exp[r];
			
		}
	} 
	int rr,ll=2,dg=0; //dg e numarul de caractere de ghicit
	for(r=0;r<lung;r++)
	{
		if(vizibil[r]!=32 || vizibil[r]!=95)
                {
			ll++;			
			tc[ll]=vizibil[r];
			for(rr=0;rr<lung;rr++)
			{
				if(exp[rr]==vizibil[r])
					vizibil[rr]=exp[rr];
			}
		}
	}  
	for(r=0;r<lung;r++)
	{
		if(vizibil[r]==95)
			dg++;
	}
	
	
	tc[0]=' ';
	tc[1]='_';   //ar fi ilogic sa generam aleator space,Q sau _
	tc[2]='Q';	
	int ca;
	ca=0;
	do{ca=rand()%126;}//caracter aleator
	while(ca<32);
	
	for(j=3;j<=18;j++)
		mvprintw(1,j,"_");                
	for(i=2;i<=18;i++)
		mvprintw(i,3,"|");  
	mvprintw(17,2,"/");
	mvprintw(18,1,"/");
	mvprintw(17,4,"\\");
	mvprintw(18,5,"\\");
	mvprintw(2,18,"|");
	mvprintw(3,18,"|");
	mvprintw(20,2,"Expresii valide:");
	
	mvprintw(22,3,"Tastati Q pentru a reveni in meniu.");                        //legenda comenzi,instructiuni
	mvprintw(23,3,"Incercati sa ghiciti expresia."); 
	mvprintw(24,3,"Nu va lasati spanzurat. Aveti 6 vieti. Have fun.");
	
	time_t mytime;				//afisare data, timp curent
    	mytime=time(NULL);	
	mvprintw(25,3,ctime(&mytime));
	refresh();                                  // 
	
	int win=0;	
	while(win==0)
   	{
      		mvprintw(3,26, vizibil );
      		mvprintw(19,3,"Incorecte:");
		mvprintw(19,14,incorecte);
      		refresh();
		nfds = 1;
		FD_ZERO(&read_descriptors);
	
		FD_SET(KEYBOARD, &read_descriptors);

		timeout.tv_sec = 7;
		timeout.tv_usec = 0;
		
		int aa;
		aa=0;
		while (1) 
		{	
			
			sel = select(nfds, &read_descriptors, NULL, NULL, &timeout);
	
			switch (sel) 
			{
				case SELECT_EVENT:
					ch=getch();
					aa=1;
				
					break;
					
		
				case SELECT_NO_EVENT:
					while(strchr(tc,ca)!=NULL && ca>=32)
					{	srand(time(NULL));
						ca=rand()%126;			
					}
					ch=ca;
					aa=1;
				
					break;
			}		
			
		FD_SET(KEYBOARD, &read_descriptors);
		
		timeout.tv_sec=7;
		timeout.tv_usec=0;
		if(aa==1)
			break;
		}

		if(ch=='Q')
		{
						
			break;
			
		}
		
		time_t mytime;				//afisare data, timp curent   
    		mytime=time(NULL);	
		mvprintw(25,3,ctime(&mytime));
		refresh(); 

		for(l=0;l<lung;l++)
         	{	if(ch==vizibil[l] || ch==incorecte[l])		
       			{
       				flag_r=1;
            			flag_c=1;
            			break;
         		}
		}
		if(flag_r==0)	                 //verificam daca l-am mai tastat
			for(l=0;l<lung;l++)
         		{
            			if(ch==exp[l])
            			{
               				vizibil[l]=ch;
               				corecte++;
					if(corecte==dg)
               				{
						win=1;
						clear();   
						getmaxyx(stdscr,row,col);
						mvprintw(row/2,(col-32)/2,"Felicitari! Ai ghicit expresia.");
						refresh();
						getch();
						clear();
					
						char *choices[] = {                     
							"New Game",
							"Resume Game",
							"Quit",
							  };
						//int n_choices = sizeof(choices) / sizeof(char *);
				
						WINDOW *menu_win;
						int highlight = 1;
					

						clear();
						noecho();
						cbreak();	                                 
						startx = (80 - 35) / 2;				//niste masuri alese convenabil
						starty = (24 - 15) / 2;
		
						menu_win = newwin(15, 35, starty, startx);
						keypad(menu_win, TRUE);
						mvprintw(0, 0, "Navigati cu sagetile sus-jos, apasati enter sa alegeti");
						refresh();						
						print_menu(menu_win, highlight);              	
						
                  			}
                  			flag_c=1;
				}
               		}

           	  if(flag_c==0 )
     		  {
         	  	incorecte[gresite]=ch;
         		gresite++;
      		  }

     		  flag_r=0;   //resetam flag-urile
          	  flag_c=0;
		 
	          refresh();
	
		  if(gresite>=6)
		  {
			clear();
			mvprintw(19,25,"Daca nu raspundeai gresit de 6 ori, poate castigai..");
			refresh();
			getch(); 
			break; 
		  }      		
	
	      	  			
			
		  switch(gresite)
		  {
			default:	
			{
		                           //stalp
				for(j=3;j<=18;j++)
					mvprintw(1,j,"_");                
				for(i=2;i<=18;i++)
					mvprintw(i,3,"|");  
				mvprintw(17,2,"/");
				mvprintw(18,1,"/");
				mvprintw(17,4,"\\");
				mvprintw(18,5,"\\");
				mvprintw(2,18,"|");
				mvprintw(3,18,"|");
				break;
			}
			case 1:
			{
				                    //stalp
				for(j=3;j<=18;j++)
					mvprintw(1,j,"_");                
				for(i=2;i<=18;i++)
					mvprintw(i,3,"|");  
				mvprintw(17,2,"/");
				mvprintw(18,1,"/");
				mvprintw(17,4,"\\");
				mvprintw(18,5,"\\");
				mvprintw(2,18,"|");
				mvprintw(3,18,"|");			
				mvprintw(4,16,"-----");    // cap
				mvprintw(5,16,"|0 0|");
				mvprintw(6,16,"\\___/");
				break;
			}
			case 2:
			{
				for(j=3;j<=18;j++)
					mvprintw(1,j,"_");                
				for(i=2;i<=18;i++)
					mvprintw(i,3,"|");  
				mvprintw(17,2,"/");
				mvprintw(18,1,"/");
				mvprintw(17,4,"\\");
				mvprintw(18,5,"\\");
				mvprintw(2,18,"|");
				mvprintw(3,18,"|");			
				mvprintw(4,16,"-----");    // cap
				mvprintw(5,16,"|0 0|");
				mvprintw(6,16,"\\___/");			
				mvprintw(7,18,"|");                     //trunchi
				mvprintw(8,15,"+-----+");
				for(i=9;i<=11;i++)	
					mvprintw(i,15,"|     |");
				mvprintw(12,15,"+-----+");
				break;
			}
			case 3:
			{
				for(j=3;j<=18;j++)
					mvprintw(1,j,"_");                
				for(i=2;i<=18;i++)
					mvprintw(i,3,"|");  
				mvprintw(17,2,"/");
				mvprintw(18,1,"/");
				mvprintw(17,4,"\\");
				mvprintw(18,5,"\\");
				mvprintw(2,18,"|");
				mvprintw(3,18,"|");			
				mvprintw(4,16,"-----");    // cap
				mvprintw(5,16,"|0 0|");
				mvprintw(6,16,"\\___/");			
				mvprintw(7,18,"|");                     //trunchi
				mvprintw(8,15,"+-----+");
				for(i=9;i<=11;i++)	
					mvprintw(i,15,"|     |");
				mvprintw(12,15,"+-----+");			
				mvprintw(9,14,"/");        //mana 
				mvprintw(10,13,"/");
				mvprintw(11,12,"/");
				break;
			}	
			case 4:
			{
			
				for(j=3;j<=18;j++)
					mvprintw(1,j,"_");                
				for(i=2;i<=18;i++)
					mvprintw(i,3,"|");  
				mvprintw(17,2,"/");
				mvprintw(18,1,"/");
				mvprintw(17,4,"\\");
				mvprintw(18,5,"\\");
				mvprintw(2,18,"|");
				mvprintw(3,18,"|");			
				mvprintw(4,16,"-----");    // cap
				mvprintw(5,16,"|0 0|");
				mvprintw(6,16,"\\___/");			
				mvprintw(7,18,"|");                     //trunchi
				mvprintw(8,15,"+-----+");
				for(i=9;i<=11;i++)	
					mvprintw(i,15,"|     |");
				mvprintw(12,15,"+-----+");			
				mvprintw(9,14,"/");        //mana 
				mvprintw(10,13,"/");
				mvprintw(11,12,"/");
				mvprintw(9,22,"\\");     //cealalta mana
				mvprintw(10,23,"\\");
				mvprintw(11,24,"\\");
				break;
			}
			case 5:
			{
				for(j=3;j<=18;j++)
					mvprintw(1,j,"_");                
				for(i=2;i<=18;i++)
					mvprintw(i,3,"|");  
				mvprintw(17,2,"/");
				mvprintw(18,1,"/");
				mvprintw(17,4,"\\");
				mvprintw(18,5,"\\");
				mvprintw(2,18,"|");
				mvprintw(3,18,"|");			
				mvprintw(4,16,"-----");    // cap
				mvprintw(5,16,"|0 0|");
				mvprintw(6,16,"\\___/");			
				mvprintw(7,18,"|");                     //trunchi
				mvprintw(8,15,"+-----+");
				for(i=9;i<=11;i++)	
					mvprintw(i,15,"|     |");
				mvprintw(12,15,"+-----+");			
				mvprintw(9,14,"/");        //mana 
				mvprintw(10,13,"/");
				mvprintw(11,12,"/");
				mvprintw(9,22,"\\");     //cealalta mana
				mvprintw(10,23,"\\");
				mvprintw(11,24,"\\");					
				mvprintw(13,15,"//");     //picior 
				mvprintw(14,14,"//");
				mvprintw(15,13,"//");
				break;
			}
			case 6:
			{
				for(j=3;j<=18;j++)
					mvprintw(1,j,"_");                
				for(i=2;i<=18;i++)
					mvprintw(i,3,"|");  
				mvprintw(17,2,"/");
				mvprintw(18,1,"/");
				mvprintw(17,4,"\\");
				mvprintw(18,5,"\\");
				mvprintw(2,18,"|");
				mvprintw(3,18,"|");			
				mvprintw(4,16,"-----");    // cap
				mvprintw(5,16,"|0 0|");
				mvprintw(6,16,"\\___/");			
				mvprintw(7,18,"|");                     //trunchi
				mvprintw(8,15,"+-----+");
					for(i=9;i<=11;i++)	
				mvprintw(i,15,"|     |");
				mvprintw(12,15,"+-----+");			
				mvprintw(9,14,"/");        //mana 
				mvprintw(10,13,"/");
				mvprintw(11,12,"/");
				mvprintw(9,22,"\\");     //cealalta mana
				mvprintw(10,23,"\\");
				mvprintw(11,24,"\\");					
				mvprintw(13,15,"//");     //picior 
				mvprintw(14,14,"//");
				mvprintw(15,13,"//");			
				mvprintw(13,20,"\\\\");     //celalalt picior
				mvprintw(14,21,"\\\\");
				mvprintw(15,22,"\\\\");	
				break;
			}
		}
      		  
   }		            
	

}
meniu(int argc,char **argv,int valoros)
{
	int o,m;  	
	char linie[512]; //linie

	char exp[200];
	int n=1; // numar expresii totale;	
	int i;
	char linii[250][200];
	FILE *p=fopen(argv[1],"r");
	if(p==NULL)
	{
		fprintf(stderr,"[Eroare]: Nu s-au dat argumente de comanda.\n");	 
		valoros=1;
	}
	else			
	{
		for(i=1;i<argc;++i)
		{	
			p=fopen(argv[i], "r");
			if (!p)
			{
				fprintf(stderr, "[Eroare]: Fisierul %d nu poate fi deschis.\n", i);      
				valoros=1;
				break;
						                            
			}
			else
			{
			
			while(fgets(linie,512,p))
			{	
				o=0;
				for(m=0;m<strlen(linie);m++)					
				{	
					if(isprint(linie[m]))
					{
						if(isalpha(linie[m]))
						{	
							linie[m]=tolower(linie[m]);					
							linii[n][o]=linie[m];
							o++;
						}
						else
						{
							linii[n][o]=linie[m];
							o++;				
						}					
					}
				}				
				n++;		
						
			}
			int ii,jj;
			for(ii=0;ii<n;ii++)
			{
				if(strlen(linii[ii])==0)
				{
					for(jj=ii-1;jj<n;jj++)					
						strcpy(linii[ii],linii[ii+1]);
				}
			}
			srand(time(NULL));
			int randomindex=rand()%n;
			int flag=1;   // vreau sa stiu pe ce s-a apasat enter
			int startx = 0;
			int starty = 0;

			char *choices[] = { 
			"New Game",
			"Resume Game",
			"Quit",
				  };
			int n_choices = sizeof(choices) / sizeof(char *);	
	
			WINDOW *menu_win;
			int highlight = 1;
			int choice = 0;
			int c;

			initscr();
			clear();
			noecho();
			cbreak();	                                 
			startx = (80 - 35) / 2;				//niste masuri alese convenabil
			starty = (24 - 15) / 2;	
			start_color();
			init_pair(1,COLOR_RED,COLOR_BLACK);
			menu_win = newwin(15, 35, starty, startx);
			keypad(menu_win, TRUE);
			mvprintw(0, 0, "Navigati cu sagetile sus-jos, apasati enter sa alegeti");
			refresh();
			print_menu(menu_win, highlight);
			while(1)
			{	
				c = wgetch(menu_win);
				switch(c)
				{	case KEY_UP:
					flag--;				//flag retine optiunea la care s-a ajuns(in modulo 3)
					if(highlight == 1)               
						highlight = n_choices;      
					else
						--highlight;
					break;
					case KEY_DOWN:
					flag++;
					if(highlight == n_choices)
						highlight = 1;
					else 
						++highlight;
						break;
					case 10:				
					choice = highlight;
					break;
				}
				print_menu(menu_win, highlight);
				if(choice != 0)	      
					break;	
			}
				
			if(flag%3==1 || flag%3==-2)         //s-a dat enter pe new game
			{
				clear();
				strcpy(exp,linii[randomindex]);		
				new_game(exp); 	
			}
			if(flag%3==0)
				valoros=1;
			if(flag%3==2 || flag%3==-1)
			{
				clear();				 
				pp=2;
				new_game(exp);
					
			}
			}
		}
	}
	return valoros;
}

int main(int argc, char **argv) 
{
	int valoros=0;  //o variabila care sa ma scoata din while(sau nu), in functie de ce se petrece
		
	while(1)
	{	
		
		
		if(meniu(argc,argv,valoros)==1)    //a avut loc o eroare
			break;   
	}
	

	clrtoeol();
	refresh();
	endwin();
	
	return 0;
}


