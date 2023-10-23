#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

static ListNode *front = NULL;
static ListNode *back = NULL;

ListNode *allocateSpaceForListNode()
{
    ListNode *myNode = (ListNode *)malloc(sizeof(ListNode));
    if (myNode == NULL) {
        printf("Speicher allocation fehlgeschlagen\n");
        return 0;
    }
    return myNode;
}



void addNameToNode(ListNode *myNode, const char *name)
{
    strcmp(myNode->name, name);
}

bool listEmpty()
{
    if(front == NULL)
    {
        return true;
    }
    else{
        return false;
    }
    
}
bool userNameMatch(const char *currentName, const char *searchedName)
{
    if(strcmp(currentName, searchedName) == 0) //means they are equal
    {
        return true; //returns true if we have a username match
    }
    
}
bool validUserName(const char *name)
{
    printf("Betrete validUserName");
    ListNode *current = front;
    while(current != NULL)
    {
        if(userNameMatch(current->name, name) == true)  //nur wenn es einen usernamen schon gibt wird diese verzweigung betreten
        {
            return false; //username not valid
        }
        current = current->next;
    }
    return true;
}
bool userNameNotEmpty(const char *name)
{
    printf("Betrete userNameNotEmpty");
    while(*name)
    {
        if (!isspace((unsigned char)*name))
        {
            return true; //true bestätigt, das ein normales Zeichen im String ist und nicht nur alles Leerzeichen sind bzw der string leer ist
        }
        name++;
    }
    printf("String war leer - verlasse userNameNotEmpty");
    return false; //String war leer
}

ListNode *listAdd(const char *name)
{
    if(validUserName(name) == true && userNameNotEmpty(name) == true)
    {   
        ListNode *myNode = allocateSpaceForListNode();
        printf("Address of allocated Node: [%s] is [%p]\n", name, myNode);
        if(listEmpty())
        {
            front = myNode;
            back =  myNode;    
            myNode->prev = NULL;
            myNode->next = NULL;
        }
        if(!listEmpty())
        {
            myNode->prev = back;
            myNode->next = NULL;
            back = myNode;
        }
        addNameToNode(myNode, name);
        myNode->number[0] = '\0'; //Initialisierung auf leeren String*/ Achtung nicht "\0"
        return myNode;
    }
    else{
        printf("Name bereits vergeben oder ungültig");
        return NULL;
    }
}
/*Hängt einen neuen Eintrag mit dem übergebenen name
an das Ende der Liste. Die Telefonnummer wird auf den
leeren String initialisiert. Gibt einen Zeiger auf den neuen Eintrag in der Liste zurück, oder NULL im Fehlerfall. Bei
einem Fehler wird zudem errno auf einen entsprechenden Wert gesetzt: EEXIST, falls der schon ein Eintrag mit
dem übergebenen name existiert; oder ENOMEM,falls nicht
genügend Speicher zur Verfügung steht.*/

void listForEach(void (* func)(ListNode *))
{
    ListNode *tmp = front;
    while(tmp != NULL)
    {
        func(tmp);
        tmp = tmp->next;
    }
}
/*Iteriert über die komplette Liste und führt dabei die per
Zeiger func übergebene Funktion für jeden Eintrag in der
Liste aus. Dabei wird in jedem Iterationsschritt ein Zeiger auf das jeweilige ListNode-Element an die Funktion
übergeben. Für eine Liste mit n Elementen ergeben sich
dadurch n Aufrufe von func. Durch diesen Mechanismus
können beispielsweise alle Elemente der Liste auf der
Konsole ausgegeben werden.*/



int listRemoveByName(const char *name)
{
    
   
    
    
    
}
/*Löscht den Eintrag mit dem übergebenen name aus der
Liste und gibt den Speicher für den Eintrag frei. Falls es
keinen Eintrag mit dem übergebenen Namen gibt, wird
errno auf ENOENT gesetzt und -1 zurückgegeben. Im Erfolgsfall ist der Rückgabewert 0.
*/

void listRemoveAll(void)
{

}
/*Löscht alle Einträge aus der Liste. Diese Funktion wird
beim Beenden des Programms aufgerufen, um den kompletten Speicher für die Liste wieder freizugeben.*/
