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
    printf(" --compareName tmp %s, and name %s\n", tmp->name, name);
    if(strcmp(tmp->name, name) == 0) //wenn strcmp 0 zurück liefert sind beide Werte identisch
    {
        printf(" --return tmp %p\n", tmp);
        return tmp; //Falls Name vorhanden liefert return Zeiger auf die node wo der Name steht
    } 
    return NULL; //return NULL falls der Username nicht in der Liste ist
}
ListNode *userNameMatch(const char *name)
{
    printf("Testcase: %s\n", name);
    ListNode *tmp = front;
    printf("--Front tmp: %p\n", tmp);
    ListNode *myNode = NULL;
    printf(" --1tmp node ist: %p\n", tmp);
    printf(" --2my node ist: %p\n", myNode);
    while(tmp != NULL && myNode == NULL) //tmp nicht null: liste noch nicht am Ende; myNode == Null: noch keinen gleichen Namen gefuden
    {
        myNode = compareName(tmp, name);
        tmp = tmp->next;
    }
    printf(" --2tmp node ist: %p\n", tmp);
    printf(" --2my node ist: %p\n", myNode);
    return myNode; //wenn kein doppelter name gefunden wurde bleibt myNode NULL; sonst wird der pointer übergeben wo in der Liste der doppelte name gefunden wurde
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
    printf("%s", name);
    if(userNameMatch(name) == NULL && userNameNotEmpty(name) == true)
    {   
        printf(" user match: [%s]", name);
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
