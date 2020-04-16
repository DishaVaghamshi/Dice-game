#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>

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
		write(client1,"client1 has joined....game is starting...stay tuned:)",100);
		write(client2,"you are TITI(clietn2),client1 has already joined...\n game is starting...stay tuned:)",100);
		printf("game is starting");
		if(fork()==0)
		{
			players(client1,client2);
		}
	}
}