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
ListNode *compareName(ListNode *tmp, const char *name)
{
    if(strcmp(tmp->name, name) == true)
    {
        return tmp; //Falls Name vorhanden liefert return Zeiger auf die node wo der Name steht
    } 
    return NULL; //return NULL falls der Username nicht in der Liste ist
}
ListNode *userNameMatch(const char *name)
{
    ListNode *tmp = front;
    ListNode *myNode = NULL;
    while(tmp != NULL && myNode == NULL) //tmp nicht null: liste noch nicht am Ende; myNode == Null: noch keinen gleichen Namen gefuden
    {
        myNode = compareName(tmp, name);
        tmp = tmp->next;
    }
    return myNode;
}
bool userNameNotEmpty(const char *name)
{
    while (*name)           //Schleife wird solange ausgeführt wird, wie der aktuelle Zeiger name nicht auf das Nullzeichen ('\0') zeigt
    {
        if (!isspace((unsigned char)*name)) { //überprüft, ob das aktuelle Zeichen im String input ein nicht-Leerzeichen-Zeichen ist (einschließlich Tabulatorzeichen, Zeilenumbrüche usw.)
            return true; // Der String enthält mindestens ein nicht-Leerzeichen-Zeichen
        }
        name++;
    }
    return false;
}
void addNameToNode(char *destName, const char *sourceName)
{
    strcpy(destName, sourceName);
}

bool listEmpty()
{
    if(front == NULL)
    {
        return true;
    }
}

ListNode *listAdd(const char *name)
{
    if(userNameMatch(name) == NULL && userNameNotEmpty(name) == true)
    {   
        ListNode *myNode = allocateSpaceForListNode();
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
        addNameToNode(myNode->name, name);
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



int listRemoveByName(const char *name)
{
    ListNode *myNode = userNameMatch(name);
    //todo: remove myNode
    
    
    
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
