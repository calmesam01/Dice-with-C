// Team Lannisters
// Sanyam Sareen (105192200)
// Lavish Handa (110006198)

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

void servicePlayers(int, int);

void servicePlayers(int playerOne, int playerTwo){

	int playerOnePoints[2], playerTwoPoints[2];
  	playerOnePoints[0]=0;														//Initialize playerOne's current score to 0
  	playerOnePoints[1]=0;														//Initialize the playerOne's final score to 0
  	playerTwoPoints[0]=0;														//Initialize playerTwo's current score to 0
  	playerTwoPoints[1]=0;														//Initialize playerTwo's final score to 0
	while(1)
		{
		printf("Referee: TOTO plays:\n");
		write(playerOne, "You can now play", 50);								//send the message to playerOne to play his turn
		if(read(playerOne, &playerOnePoints, sizeof(playerOnePoints)) < 0){		//read the points/score from playerOne
			fprintf(stderr, "read() error\n");
			exit(3);
		}
		
		printf("Points earned: %d\n", playerOnePoints[0]);						//print the points earned by playerOne
		printf("Total points earned: %d\n\n", playerOnePoints[1]);				//prints total score of playerOne
		
		if(playerOnePoints[1] >= 100){		
			printf("TOTO won\n");
			write(playerOne, "Game over: you won the game",50);					//Send the message to playerOne
			close(playerOne);													//close the socket
			write(playerTwo, "Game over: you lost the game",50);				//Send the message to playerTwo	
			close(playerTwo);													//close the socket
			exit(5);
		}
		sleep(2);

		printf("Referee: TITI plays:\n");
		write(playerTwo, "You can now play", 50);								//send the message to playerTwo to play his turn
		if(read(playerTwo, &playerTwoPoints, sizeof(playerTwoPoints)) < 0){		//read the points/score from playerTwo
			fprintf(stderr, "read() error\n");
			exit(3);
		}
		
		printf("Points earned: %d\n", playerTwoPoints[0]);						//print the points earned by playerTwo
		printf("Total points earned: %d\n\n", playerTwoPoints[1]);				//prints total score of playerOne
		
		if(playerTwoPoints[1] >= 100){		
			printf("TITI won\n");
			write(playerTwo, "Game over: you won the game",50);					//Send the message to playerTwo	
			close(playerTwo);													//close the socket		
			exit(5);															//Send the message to playerOne
		}																		//close the socket
		sleep(2);		
  }
    exit(1); 
}

int main(int argc, char *argv[]){  
	int sd, portNumber, playerOne, playerTwo;
	struct sockaddr_in servAdd;     											//server socket address
	
	if(argc != 2){
		printf("Call model: %s <Port Number>\n", argv[0]);
		exit(0);
  }

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
		fprintf(stderr, "Could not create a socket\n");
		exit(1);
  }
	servAdd.sin_family = AF_INET; 												//Domain for Internet, AF is the Address Family
	servAdd.sin_addr.s_addr = htonl(INADDR_ANY); 								//host to network or network to host conversions of multibyte integers 
	sscanf(argv[1], "%d", &portNumber);
	servAdd.sin_port = htons((uint16_t)portNumber);
	
	bind(sd, (struct sockaddr *) &servAdd, sizeof(servAdd));
	listen(sd, 6);
	
	while(1){

		playerOne = accept(sd,(struct sockaddr*)NULL,NULL);
		playerTwo = accept(sd,(struct sockaddr*)NULL,NULL);
		
			
			printf("Two Players joined the game\n");							//Two players have joined, now the game will start
		
		
		if(!fork())
		{
		  servicePlayers(playerOne, playerTwo);
		}
	}
	
	return 0;
}

