#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

int main () {

	int servSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in servAddr;

	servAddr.sin_family = PF_INET;
	servAddr.sin_port = htons(8080);
	servAddr.sin_addr.s_addr = INADDR_ANY;


	bind(servSocket, (struct sockaddr*)&servAddr, sizeof(servAddr));

	listen(servSocket, 5);

	int clientSocket = accept(servSocket, 0, 0);

	char buffer[1024] = {0};
	recv(clientSocket, buffer, sizeof(buffer), 0);

	printf("Message from client: %s\n", buffer);

	FILE *file = fopen("log.txt", "a+");

	if (file) {

		for (short i = 0; i < 1024; i++)
			putc(buffer[i], file);
		putc(' ', file);

		fclose(file);
		printf("Message be writed in log.txt\n");

	}


	close(servSocket);

	return 0;
}
