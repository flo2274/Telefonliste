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
    strcpy(myNode->name, name);
    printf("What is current name:%s\n", myNode->name);
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
bool userNameMatch(char *currentName, const char *searchedName)
{
    if(strcmp(currentName, searchedName) == 0) //means they are equal
    {
        return true; //returns true if we have a username match
    }
    else{
        return false;
    }
    
}
bool validUserName(const char *name)
{
    ListNode *current = front;  
    while(current != NULL) 
    {                   
        if(userNameMatch(current->name, name) == true)
        {
            return false; //username not valid
        }
        current = current->next;
    }
    return true;
}
bool userNameNotEmpty(const char *name)
{
    while(*name)
    {
        if (!isspace((unsigned char)*name))
        {
            return true; //true bestätigt, das ein normales Zeichen im String ist und nicht nur alles Leerzeichen sind bzw der string leer ist
        }
        name++;
    }
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
        else
        {
            back->next = myNode;
            myNode->prev = back;
            printf("myNode->prev->next: %p\n", myNode->prev->next);
            myNode->next = NULL;
            back = myNode;
            printf("myNode->prev: %p\n", myNode->prev );
            printf("myNode->next: %p\n", myNode->next );
        }
        addNameToNode(myNode, name);
        myNode->number[0] = '\0'; //Initialisierung auf leeren String*/ Achtung nicht "\0"
        return myNode;
    }
    else{
        printf("Name bereits vergeben oder ungültig\n");
        return NULL;
    }
}
/*Hängt einen neuen Eintrag mit dem übergebenen name
an das Ende der Liste. Die Telefonnummer wird auf den
leeren String initialisiert. Gibt einen Zeiger auf den neuen Eintrag in der Liste zurück, oder NULL im Fehlerfall. Bei
einem Fehler wird zudem errno auf einen entsprechenden Wert gesetzt: EEXIST, falls der schon ein Eintrag mit
dem übergebenen name existiert; oder ENOMEM,falls nicht
genügend Speicher zur Verfügung steht.*/

void listForEach(void (* func)(ListNode *)) //übergabeparameter ist eine function mit dem Parameter ListNode * und ohne Rückgabewert 
{
    ListNode *current = front;
    while(current != NULL)
    {
        func(current);
        current = current->next;
    }
}
/*Iteriert über die komplette Liste und führt dabei die per
Zeiger func übergebene Funktion für jeden Eintrag in der
Liste aus. Dabei wird in jedem Iterationsschritt ein Zeiger auf das jeweilige ListNode-Element an die Funktion
übergeben. Für eine Liste mit n Elementen ergeben sich
dadurch n Aufrufe von func. Durch diesen Mechanismus
können beispielsweise alle Elemente der Liste auf der
Konsole ausgegeben werden.*/
bool isOnlyNode(ListNode *current)
{
    if(current == front && current == back)
    {
        return true;     
    }
    else
    {
        return false;
    }
}
bool isFirstNode(ListNode *current)
{
    if(current == front && current != back)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isMiddleNode(ListNode *current)
{
    if(current != front && current != back)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isLastNode(ListNode *current)
{
    if(current != front && current == back)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void removeNode(ListNode *current)
{
    printf("removeNode betreten: %s\n", current->name);
    bool access = true; //Es darf nur ein Node removed werden; to prevent unwanted if case access
    ListNode *tmp = current->next;
    if(isOnlyNode(current) == true && access == true)
    {
        printf("isOnlyNode betreten:");
        front = NULL; //-------------------------------------check pointer initialisation for all
        back = NULL;
        access = false;
    }
    if(isFirstNode(current) == true && access == true)
    {
        printf("isFirstNode betreten: %s\n", current->name);
        front = current->next;
        current->next->prev = NULL;
        access = false;
    }
    if(isMiddleNode(current) == true && access == true)
    {
        printf("isMiddleNode betreten: %s\n", current->name);
        current->next->next->prev = current; //grün
        current->next = current->next->next; //blau
        access = false;
    }
    if(isLastNode(current) == true && access == true)
    {
        printf("isLastNode betreten: %s\n", current->name);
        current->prev->next = NULL;
        back = current->prev;
        access = false;
    }
    free(tmp);
}
ListNode *searchUserName(const char *name)
{
    printf("searchUserName betreten: %s\n", name);
    ListNode *current = front;  
    while(current != NULL) 
    {                   
        if(userNameMatch(current->name, name) == true)
        {
            return current;
        }
        current = current->next;
    }
}
int listRemoveByName(const char *name)
{
    
    printf("listRemoveByName betreten: %s\n", name);
    ListNode *userToBeRemoved = searchUserName(name);
    removeNode(userToBeRemoved);
    

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
