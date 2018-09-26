#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CLIENTS	10
#define BUFLEN 256

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void eroare_tema(int i, int ero){
	char mesaj_eroare[37];
	
	
	switch (ero){
		case -2:
			strcpy(mesaj_eroare,"IBANK> −2 : Sesiune deja deschisa");
			send(i,mesaj_eroare,sizeof(mesaj_eroare),0);
			break;
		case -3:
			strcpy(mesaj_eroare,"IBANK> −3 : Pin gresit");
			send(i,mesaj_eroare,sizeof(mesaj_eroare),0);
			break;
		case -4:
			strcpy(mesaj_eroare,"IBANK> -4 : Numar card inexistent");
			send(i,mesaj_eroare,sizeof(mesaj_eroare),0);
			break;
		case -5:
			strcpy(mesaj_eroare,"IBANK> −5 : Card blocat");
			send(i,mesaj_eroare,sizeof(mesaj_eroare),0);
			break;
		case -8:
			strcpy(mesaj_eroare,"IBANK> −8 : Fonduri insuficiente");
			send(i,mesaj_eroare,sizeof(mesaj_eroare),0);
			break;
		case -9:
			strcpy(mesaj_eroare,"IBANK> −9 : Operatie anulata");
			send(i,mesaj_eroare,sizeof(mesaj_eroare),0);
			break;
	}
}

struct  Client{
    char nume[13];
    char prenume[13];
    char numar_card[7];
    char pin[5];
    char parola[9];
    double sold;

};

int main(int argc, char *argv[])
{	
	
	FILE *fp;
    fp = fopen (argv[2],"r");
	
	char nume_fisier[100];
	//sprintf (nume_fisier, "client-%s.log", getpid());
	
    int N;
    fscanf(fp,"%d",&N);  // citeste nr clienti
    struct Client clients[N]; //array de clienti 
	int client_logat[N];  //daca clientul e deja logat, are 1 
	int esec_logare[N]; // de cate ori a gresit pinul un client
	const char *client_client[100]; // pe poz i din client_client se afla nr cardului, iar i este fd. 
	
	int k;
	for(k=0;k<100;k++){
		client_client[k]=0;
	}
	for(k=0;k<N;k++){
		esec_logare[k]=0;
	}
    for(k=0; k<N; k++){
        fscanf (fp,"%s",clients[k].nume);
        fscanf (fp,"%s",clients[k].prenume);
        fscanf (fp,"%s",clients[k].numar_card);
        fscanf (fp,"%s",clients[k].pin);
        fscanf (fp,"%s",clients[k].parola);
        fscanf (fp,"%lf",&clients[k].sold);
    }
	 fclose(fp);   
     int sockfd, newsockfd, portno, clilen;
     char buffer[BUFLEN];
     struct sockaddr_in serv_addr, cli_addr;
     int n, i, j;

     fd_set read_fds;	//multimea de citire folosita in select()
     fd_set tmp_fds;	//multime folosita temporar 
     int fdmax;		//valoare maxima file descriptor din multimea read_fds

     if (argc < 2) {
         fprintf(stderr,"Usage : %s port\n", argv[0]);
         exit(1);
     }

     //golim multimea de descriptori de citire (read_fds) si multimea tmp_fds 
     FD_ZERO(&read_fds);
     FD_ZERO(&tmp_fds);
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     
     portno = atoi(argv[1]);

     memset((char *) &serv_addr, 0, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;	// foloseste adresa IP a masinii
     serv_addr.sin_port = htons(portno);
     
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) < 0) 
              error("ERROR on binding");
     
     listen(sockfd, MAX_CLIENTS);

     //adaugam noul file descriptor (socketul pe care se asculta conexiuni) in multimea read_fds
     FD_SET(sockfd, &read_fds);
	 FD_SET(STDIN_FILENO, &read_fds);
     fdmax = sockfd;
	char iesire_server[6];
     // main loop
	char shut_down[50];
	strcpy(shut_down,"Atentie, serverul se va inchide");
	while (1) {
		
		tmp_fds = read_fds; 
		if (select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1) 
			error("ERROR in select");
	
		for(i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp_fds)) {
				/*
				if(i==0){  //n-a venit de pe un socket
					fgets(iesire_server, 6, stdin); 
        			buffer[strlen(iesire_server)-1]='\0';
					if(strcmp(iesire_server,"quit")==0){
						for(i=3;i<=fdmax;i++){
							if(i!=sockfd && FD_ISSET(i, &read_fds)){
								send(i,shut_down,sizeof(shutdown),0);
							}
						}
						return 0;
					}
				}
				*/
				if (i == sockfd) {
					// a venit ceva pe socketul inactiv(cel cu listen) = o noua conexiune
					// actiunea serverului: accept()
					clilen = sizeof(cli_addr);
					if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) == -1) {
						error("ERROR in accept");
					} 
					else {
						//adaug noul socket intors de accept() la multimea descriptorilor de citire
						FD_SET(newsockfd, &read_fds);
						if (newsockfd > fdmax) { 
							fdmax = newsockfd;
						}
					}
					printf("Noua conexiune de la %s, port %d, socket_client %d\n ", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), newsockfd);
				}
					
				else {
					// am primit date pe unul din socketii cu care vorbesc cu clientii
					//actiunea serverului: recv()
					memset(buffer, 0, BUFLEN);
					if ((n = recv(i, buffer, sizeof(buffer), 0)) <= 0) {
						if (n == 0) {
							//conexiunea s-a inchis
							printf("selectserver: socket %d hung up\n", i);
						} else {
							error("ERROR in recv");
						}
						close(i); 
						FD_CLR(i, &read_fds); // scoatem din multimea de citire socketul pe care 
					} 
					
					else { //recv intoarce >0
					
        				char bufferCopy[BUFLEN];
        				strcpy(bufferCopy,buffer);
						char token[10];
						char tok1[10];
						char tok2[10];
						
					
						sscanf(buffer,"%s %s %s", token, tok1, tok2);
						
						if(strcmp(token,"login")==0){
							int gasit=0;				//flag daca gaseste nr cardului		
							for(k=0;k<N;k++){
								if(strcmp(tok1,clients[k].numar_card)==0){ //am gasit nr cardului
									gasit=1;
									if(client_logat[k]==1){ //client deja logat
										eroare_tema(i,-2);
										break;
									}
									else{   //clientul nu e deja logat
										if(esec_logare[k]==3){ // card blocat
											eroare_tema(i,-5);
											break;
										}
										else{    // cardul nu e blocat
											
											if(strcmp(tok2,clients[k].pin)==0){  //pin corect
												client_client[i]=clients[k].numar_card; // retinem pe ce socket e persoana respectiva
												
												char welcome_message[41];  
												strcpy(welcome_message,"IBANK> Welcome ");
												strcat(welcome_message,clients[k].nume);
												strcat(welcome_message," ");
												strcat(welcome_message,clients[k].prenume);
												send(i,welcome_message,sizeof(welcome_message),0);
												client_logat[k]=1;         
												break;
											}
												
											else{   // ai gresit pinul, baiatul meu
												if(esec_logare[k]==2){  // a gresit si a 3-a oara
													eroare_tema(i,-5);
													esec_logare[k]++;
													break;
												}
												else{
													eroare_tema(i,-3);
													esec_logare[k]++;
													printf("%d",esec_logare[k]);
													break;
												}
											}
										}
									}
								}
							}
							if(gasit==0){
								eroare_tema(i,-4);
							}
						}
						
						else if(strncmp(token,"logout",6)==0){ //vrea logout
							char logout_msg[37];
							strcpy(logout_msg,"IBANK> Clientul a fost deconectat");
							send(i,logout_msg,sizeof(logout_msg),0);
							for(k=0;k<N;k++){
								if(strcmp(clients[k].numar_card,client_client[i])==0){ // am gasit numarul cardului care vrea sa se deconecteze
									client_logat[k]=0;
									esec_logare[k]=0;
									break;
								}
							}
						}
						else if(strncmp(token,"listsold",8)==0){ //vrea list sold
							for(k=0;k<N;k++){
								if(strcmp(clients[k].numar_card,client_client[i])==0){
									char what_sold[20];
									snprintf(what_sold, 20, "%.2lf", clients[k].sold);  // punem in what_sold, conversie double->string
									send(i,what_sold,sizeof(what_sold),0);
									break;
								}
							}
						}
						else if(strncmp(token,"transfer",8)==0){
							int gasit2=0;
							for(k=0;k<N;k++){
								if(strcmp(clients[k].numar_card,client_client[i])==0){ //am gasit cine face cererea.
									int l;
									for(l=0;l<N;l++){
										if(strcmp(tok1,clients[l].numar_card)==0){ //am gasit cui vrea sa-i dea
											gasit2=1;
											double de_transferat;
											de_transferat=atof(tok2); //cat vrea sa transfere
											if(de_transferat>clients[l].sold){  //vrei sa-i dai mai mult decat ai
												eroare_tema(i,-8);
											}
											else{
												char question[80];
												strcpy(question,"IBANK> Transfer ");
												strcat(question,tok2);
												strcat(question," catre ");
												strcat(question,clients[l].nume);
												strcat(question," ");
												strcat(question,clients[l].prenume);
												strcat(question,"? [y/n]");
												send(i,question,sizeof(question),0);
                								recv(i,buffer,strlen(buffer),0);
												
												strcpy(token,buffer);
												
												if(buffer[0]=='y'){
													clients[k].sold=clients[k].sold-de_transferat;
													clients[l].sold=clients[l].sold+de_transferat;
													memset(question,0,BUFLEN);
													strcpy(question,"IBANK> Transfer realizat cu succes");													
													send(i,question,sizeof(question),0);
												}
												else{
													eroare_tema(i,-9);
												}
											}
										}
									}
									if(gasit2==0){
										eroare_tema(i,-4);
										break;
									}
								}
							}
							if(gasit2==0){
								eroare_tema(i,-4);
							}
						}
					}
						
						printf ("Am primit de la clientul de pe socketul %d, mesajul: %s\n", i, buffer);
						
						
						
						if(i == STDIN_FILENO && strncmp(buffer, "quit", 4))
							return 0;
					}
			} 
		}
	}
     

	fclose(fp);
     close(sockfd);
   
     return 0; 
}




