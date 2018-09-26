#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <unistd.h>

#define BUFLEN 256

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    FILE *fw;
    char nume_fisier[100];
    sprintf(nume_fisier,"client-%d.log", getpid());
    fw = fopen(nume_fisier,"w");
    char buffer[BUFLEN];
    if (argc < 3) {
       fprintf(stderr,"Usage %s server_address server_port\n", argv[0]);
       exit(0);
    }  
    
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &serv_addr.sin_addr);
    
    
    if (connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");    
    int flag=0;  // flag, verifica daca e logat
    
    
    while(1){
  		//citesc de la tastatura
    	memset(buffer, 0 , BUFLEN);
    	fgets(buffer, BUFLEN, stdin); //aici era -1
        buffer[strlen(buffer)-1]='\0';
        char comand[10], c1[10], c2[10];
        memset(comand,0,10);
        sscanf(buffer,"%s %s %s", comand, c1, c2);

          
        if(strncmp(comand, "login", 5) == 0){ //vrei sa te loghezi
            
            if(flag==1){  //esti logat
                printf("-2 : Sesiune deja deschisa\n");
                fprintf(fw,"-2 : Sesiune deja deschisa\n");
            }
            else{
                n = send(sockfd,buffer,strlen(buffer), 0);
    	        if (n < 0) {
        	        error("ERROR writing to socket");    
                }
                memset(buffer, 0 , BUFLEN);
                n = recv(sockfd, buffer, sizeof(buffer), 0);
                if(buffer[7]=='W'){
                    flag=1;
                }
                if(n < 0)
                    error("ERROR receiving");
                printf("%s\n", buffer);
                fprintf(fw,"%s\n", buffer);
            }        
        }
        else if(strncmp(comand,"logout",6)==0){
            if(flag==1){
                flag=0;
                send(sockfd,buffer,strlen(buffer),0);
                memset(buffer,0,BUFLEN);
                recv(sockfd,buffer, sizeof(buffer),0);
                printf("%s\n",buffer);
                fprintf(fw,"%s\n",buffer);
            }
            else{
                printf("-1: Clientul nu este autentificat\n");
                fprintf(fw,"-1: Clientul nu este autentificat\n");
            }
        }
        else if(strncmp(comand,"listsold",8)==0){
            if(flag==1){
                send(sockfd,buffer,strlen(buffer),0);
                memset(buffer,0,BUFLEN);
                recv(sockfd,buffer, sizeof(buffer),0);
                double afist;
                afist= atof(buffer);
                printf("%.2lf\n",afist);
                fprintf(fw,"%.2lf\n",afist);
            }
            else{
                printf("-1: Clientul nu este autentificat\n");
                fprintf(fw,"-1: Clientul nu este autentificat\n");
            }
        }
        else if(strncmp(comand,"transfer",8)==0){
            if(flag==1){
                send(sockfd,buffer,strlen(buffer),0);
                memset(buffer,0,BUFLEN);
                recv(sockfd,buffer,sizeof(buffer),0);
                printf("%s\n",buffer);
                fprintf(fw,"%s\n",buffer);
                if(buffer[7]=='T'){   //verific daca e ok
                    memset(buffer, 0 , BUFLEN);
    	            fgets(buffer, BUFLEN, stdin); //aici era -1
                    buffer[strlen(buffer)-1]='\0';
                    send(sockfd,buffer,strlen(buffer),0);
                    memset(buffer,0,BUFLEN);
                    recv(sockfd,buffer, sizeof(buffer),0);
                    printf("%s\n",buffer);
                    fprintf(fw,"%s\n",buffer);
                }

            }
            else{
                printf("-1: Clientul nu este autentificat\n");
                fprintf(fw,"-1: Clientul nu este autentificat\n");
            }
        }
        else if(strncmp(comand,"quit",4)==0){
            return 0;
        }        
    }
    fclose(fw);
    return 0;
}



