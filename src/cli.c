#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

int main () {

	int cliSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in servAddr;

	servAddr.sin_family = PF_INET;
	servAddr.sin_port = htons(8080);
	servAddr.sin_addr.s_addr = INADDR_ANY;

	connect(cliSocket, (struct sockaddr*)&servAddr, sizeof(servAddr));

	char message[1024];
	printf("Enter message: ");
	scanf("%[^\t\n]s",message);

	send(cliSocket, message, strlen(message), 0);

	close(cliSocket);

	return 0;
}
