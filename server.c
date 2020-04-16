#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>

void players(int client1, int client2)
{
	int c1_points, c2_points;
	int32_t c1_total_points, c2_total_points;
	char buffer[255];
	char msg[255];

	while(1)
	{
		//for c1_points of client1
		sleep(1);
		write(client1,"You can now play TOTO",100); 
		if(read(client1,&c1_total_points,size)<0)
			printf("Read Error from client1");
		c1_points+=ntohl(c1_total_points);
		snprintf(buffer, 100, "Your Score is :: %d \nOpponent Score is :: %d\n\n", c1_points, c2_points);
		write(client1,buffer,100);
		
		if(c1_points>=100)
		{
			write(client1,"Game over: You won the game",100);
			write(client2,"Game over: You lost the game",100);
			break;
		}
		sleep(2);
		//for c2_points of client2
		write(client2,"You can now play TITI",100);
		if(read(client2,&c2_total_points,size)<0)
			printf("Read Error from Player 2");
		c2_points+=ntohl(c2_total_points);
		snprintf(buffer, 100, "Your Score is :: %d \nOpponent Score is :: %d\n\n", c2_points, c1_points);
		write(client2,buffer,100);
		if(c2_points>=100){
			write(client2,"Game over: You won the game",100);
			write(client1,"Game over: You lost the game",100);
			break;
		}
	}
	close(client1);
	close(client2);
}

int main(int argc, char *argv[])
{
	//char *myTime;
	int sd, client1,client2,portNumber;
	socklen_t len;
	struct sockaddr_in servAdd;
	int points;
	int32_t conv_points;
	int size = sizeof(conv_points);

    if(argc != 2)
    {
		fprintf(stderr,"Call model: %s <Port#>\n",argv[0]);
		exit(0);
	}

	if((sd = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
		fprintf(stderr, "[-] Could not create socket\n");
		exit(1);
	}
	else
    {
		fprintf(stderr, "[+] Socket Created\n");
	}

	servAdd.sin_family = AF_INET;
	servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
	sscanf(argv[1], "%d", &portNumber);
	servAdd.sin_port = htons((uint16_t)portNumber);
	bind(sd, (struct sockaddr *) &servAdd,sizeof(servAdd));
	
	if(listen(sd, 6) == 0)
    {
		printf("[+]Listening...\n");
	}else
    {
		printf("[-]Error in binding.\n");
	}
	while(1)
	{
		client1=accept(sd,(struct sockaddr*)NULL,NULL);
		write(client1,"you are TOTO(client1)...waiting for TITI(client2)....",100);
		client2=accept(sd,(struct sockaddr*)NULL,NULL);
		write(client1,"client2 has joined....game is starting...stay tuned:)",100);
		write(client2,"you are TITI(clietn2),client1 has already joined...\n game is starting...stay tuned:)",100);
		printf("game is starting");
		if(fork()==0)
		{
			players(client1,client2);
		}
	}
}