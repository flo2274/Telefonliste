#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>
#include <stdbool.h>

static ListNode *front = NULL;
static ListNode *back = NULL;

ListNode *allocateSpaceForListNode()
{
    ListNode *myNode = (ListNode *)malloc(sizeof(ListNode));
    if (myNode == NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }
    return myNode;
}
void nameNotUsed(const char *name)
{

}
void addNameToNode(const char *destName, const char *sourceName)
{
    strcpy(destName, sourceName);
}

bool isListEmpty()
{
    if(front == NULL)
    {
        return true;
    }
}

ListNode *listAdd(const char *name)
{
    ListNode *myNode = allocateSpaceForListNode();
    if(isListEmpty())
    {
        front = myNode;
        back =  myNode;        
        myNode->prev = NULL;
        myNode->next = NULL;
    }
    if(!isListEmpty())
    {
        myNode->prev = back;
        myNode->next = NULL;
        back = myNode;
    }
    addNameToNode(myNode->name, name);
    myNode->number = {'\0'}; //initialisierung auf leeren String*/
    return myNode;
}
/*Hängt einen neuen Eintrag mit dem übergebenen name
an das Ende der Liste. Die Telefonnummer wird auf den
leeren String initialisiert. Gibt einen Zeiger auf den neuen Eintrag in der Liste zurück, oder NULL im Fehlerfall. Bei
einem Fehler wird zudem errno auf einen entsprechenden Wert gesetzt: EEXIST, falls der schon ein Eintrag mit
dem übergebenen name existiert; oder ENOMEM,falls nicht
genügend Speicher zur Verfügung steht.*/

void listForEach(void (* func)(ListNode *))
{
    ListNode *temp = front;
    while(temp != NULL)
    {
        func(temp);
        temp = temp->next;
    }
}
/*Iteriert über die komplette Liste und führt dabei die per
Zeiger func übergebene Funktion für jeden Eintrag in der
Liste aus. Dabei wird in jedem Iterationsschritt ein Zeiger auf das jeweilige ListNode-Element an die Funktion
übergeben. Für eine Liste mit n Elementen ergeben sich
dadurch n Aufrufe von func. Durch diesen Mechanismus
können beispielsweise alle Elemente der Liste auf der
Konsole ausgegeben werden.*/


void checkIfNameMatch(ListNode *temp, const char *name)
{
    if(strcmp(temp-> name, name) == true)
    {
        /*removeNode();*/
    } 
}
void iterateList(const char *name)
{
    ListNode *temp = front;
    while(temp != NULL)
    {
        checkIfNameMatch(temp, name);
        temp = temp->next;
        }
}
int listRemoveByName(const char *name)
{
 
    iterateList(name);
    
    
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
