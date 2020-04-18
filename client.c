// Team Lannisters
// Sanyam Sareen (105192200)
// Lavish Handa (110006198)

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> 
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>

int main(int argc, char *argv[])
{	
	srand(time(NULL));
	signal(SIGINT, SIG_IGN);
	int server, portNo, fp;
	int playerPoints[2];
	struct sockaddr_in servAdd;     											// server socket address
	char message[255];
	
	if(argc != 3){
		printf("Call model: %s <IP Address> <Port Number>\n", argv[0]);
		exit(0);
	}
	
	if((server = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		fprintf(stderr, "Cannot create a socket\n");
		exit(1);
	}
	
	servAdd.sin_family = AF_INET;
	sscanf(argv[2], "%d", &portNo);
	servAdd.sin_port = htons((uint16_t)portNo);

	if(inet_pton(AF_INET, argv[1], &servAdd.sin_addr) < 0){						//converts an address from presentation to network format
		fprintf(stderr, " inet_pton() has failed\n");
		exit(2);
	}
	if(connect(server, (struct sockaddr *) &servAdd, sizeof(servAdd))<0){
		fprintf(stderr, "connect() has failed\n");
		exit(3);
	}
	
	playerPoints[0] = 0;
	playerPoints[1] = 0;
	
	while(1){ 
	
		if(fp=read(server, message, 50)){ 										//read the message from the server
			message[fp]= 0;

			if(!strcasecmp(message, "You can now play")){						//check for the player's turn
				printf(">>> Your Turn <<<\n");
				playerPoints[0] = (rand() % 6 ) + 1;
				playerPoints[1] +=  playerPoints[0];
				printf("Points earned by me: %d\n", playerPoints[0]);			//Display the points/score
				printf("Total points earned by me: %d\n", playerPoints[1]);
				printf("\n");	
				write(server, &playerPoints, sizeof(playerPoints));				//write the points to the server 
			} 
			
			else if(!strcasecmp(message, "Game over: you won the game")){		//check the server message if some player has won the game
				fprintf(stderr, "%s\n","$$$$ Yeah! I won the game $$$$");
				close(server);
				exit(4);
			}
			
			else if(!strcasecmp(message, "Game over: you lost the game")){		//check the server message if some player has lost the game
				fprintf(stderr, "%s\n","#### Oops! I lost the game ####");
				close(server);
				exit(5);
			}
		}
		
	}	
}