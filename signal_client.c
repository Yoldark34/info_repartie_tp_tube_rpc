/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "signal.h"
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

reponse* signal_1(char *host, data send_signal_1_arg)
{
	CLIENT* clnt;
	reponse* result_1;

#ifndef	DEBUG
	clnt = clnt_create (host, SIGNAL, VERSION_UN, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	result_1 = send_signal_1(&send_signal_1_arg, clnt);
	if (result_1 == (reponse *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
	return result_1;
}


int main (int argc, char *argv[])
{
	char tampon [30];
	int nbOctets;
	char *host;
	int tube1[2];
	int tube2[2];
	char buf[20];
	char taille;
	char espace[15];

	pipe(tube1);
	pipe(tube2);

	data  send_signal_1_arg;
	data  send_signal_2_arg;



	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];

	switch (fork())
	{
		case -1 : printf ("Erreur dans la creation du processus fils.\n"); perror ("Erreur");
		break;
		case  0 : printf ("               ");
			printf ("Fils : PID=%d\n", getpid());
			printf ("               ");
			printf ("Fils : close tube1 1\n"); 
			close(tube1[1]);
			printf ("               ");
			printf ("Fils : close tube2 0\n");
			close(tube2[0]);
			
			printf ("               ");
			while(1) {
				printf ("Fils : Lecture...\n");
				read(tube1[0], &taille, 1);
				printf ("               ");
				printf("Fils : taille %c bien recu\n", taille);
				read(tube1[0], buf, (int)(taille));
				printf ("               ");
				printf("Fils : %s bien recu\n", buf);
				send_signal_1_arg.process = getpid();
				send_signal_1_arg.timestamp = (unsigned)time(NULL);
				strcpy(send_signal_1_arg.action, "Fils Lecture : ");
				strcat(send_signal_1_arg.action, buf);
				signal_1 (host, send_signal_1_arg);

				sleep(2);

				printf ("Fils : envoi de Bonjour\n");
				write(tube2[1], "7", 1);
				write(tube2[1], "Bonjour", 7);
				send_signal_1_arg.process = getpid();
				send_signal_1_arg.timestamp = (unsigned)time(NULL);
				strcpy(send_signal_1_arg.action, "Fils Ecriture : Bonjour");
				signal_1 (host, send_signal_1_arg);
			}
			
		break;
		default : printf ("Pere : PID=%d\n", getpid());
			printf ("Pere : close tube1 0\n");
			close(tube1[0]);
			printf ("Pere : close tube2 1\n");
			close(tube2[1]);

			while(1) {
			sleep(2);

			printf ("Pere : envoi de Bonjour\n");
			write(tube1[1], "7", 1);
			write(tube1[1], "Bonjour", 7);
			send_signal_2_arg.process = getpid();
			send_signal_2_arg.timestamp = (unsigned)time(NULL);
			strcpy(send_signal_2_arg.action, "Pere Ecriture : Bonjour");
			signal_1 (host, send_signal_2_arg);

			

			printf ("Pere : Lecture...\n");
			read(tube2[0], &taille, 1);
			printf("taille %c bien recu\n", taille);
			read(tube2[0], buf, (int)(taille));
			printf("%s bien recu\n", buf);
			send_signal_2_arg.process = getpid();
			send_signal_2_arg.timestamp = (unsigned)time(NULL);
			strcpy(send_signal_2_arg.action, "Pere Lecture : ");
			strcat(send_signal_2_arg.action, buf);
			signal_1 (host, send_signal_2_arg);			
			}
		return 0;
		break;
	}


exit (0);
}
