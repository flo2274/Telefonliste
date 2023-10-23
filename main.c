#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

static int xgetchar(void)
{
	const int ch = getchar();

	if(ch == EOF)
	{
		if(ferror(stdin))
			perror("Fehler beim Lesen von der Standardeingabe");
		else
			fputs("Unerwartetes Dateiende beim Lesen von der Standardeingabe\n", stderr);

		exit(EXIT_FAILURE);
	}

	return ch;
}

static void swallow(void)
{
	while(xgetchar() != '\n')
		;
}

static void swallowWhitespace(void)
{
	int input;

	while((input = xgetchar()) != '\n' && isspace(input))
		;

	ungetc(input, stdin);
}

static int menu(void)
{
	for(;;)
	{
		puts("[N]euen Eintrag anlegen");
		puts("[L]iste ausgeben");
		puts("Eintrag entfe[r]nen");
		puts("B[e]enden");

		fputs("Was möchten Sie tun: ", stdout);

		swallowWhitespace();

		int selection = xgetchar();
		if(selection != '\n')
		{
			swallow();

			selection = toupper(selection);
			if(selection != '\0' && strchr("NLRE", selection) != NULL)
				return selection;
		}

		puts("Falsche Eingabe!");
	}
}

static void prompt(const char *msg, char *buffer, size_t size)
{
	assert(msg != NULL);
	assert(buffer != NULL);
	assert(size > 0);

	for(;;)
	{
		fputs(msg, stdout);
		fputs(": ", stdout);

		for(size_t i=0; i<size; ++i)
		{
			int ch = xgetchar();
			if(ch == '\n')
			{
				buffer[i] = '\0';
				return;
			}
			else
				buffer[i] = (char)ch;
		}

		printf("Eingabe zu lang, maximal %zu Bytes!\n", size-1U);
		swallow();
	}
}

/*
 * TODO: Add static helper functions as needed.
 */

int main(void)
{
	//TODO: un-comment when you have implemented listRemoveAll()
	//atexit(listRemoveAll);

	bool running = true;
	while(running)
	{
		const int selection = menu();
		switch(selection)
		{
			case 'N':
				char buffer[32];
				const char msg[] = "Bitte Namen eingeben:";
				prompt(msg, buffer, 32);
				const char *name = buffer;
				listAdd(name);
				/*Es wird zunächst der Name für den neuen Eintrag in der Liste abgefragt.
				Anschließend wird ein neuer Eintrag in der Liste mit einer leeren Telefonnummer erzeugt. Falls
				im Zuge dessen festgestellt wird, dass der Name bereits vergeben wurde, erscheint eine 
				entsprechende Fehlermeldung und das Programm kehrt in das Menü zurück. Leere Namen sind ebenfalls
				unzulässig. Danach wird die Telefonnummer abgefragt und in dem neuen Listeneintrag gespeichert.*/
				break;
			case 'L':
				//TODO: handle command
				break;
			case 'R':
				//TODO: handle command
				break;
			case 'E':
				puts("Programm wird beendet.");
				running = false;
				break;
			default:
				abort();	//should never be reached, menu() never returns something else
				break;
		}
	}

	return EXIT_SUCCESS;
}
