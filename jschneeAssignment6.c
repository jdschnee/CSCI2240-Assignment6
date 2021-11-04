#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define DELIM ","

typedef struct student
{
    char lname[12];
    char initial;
    char fname[12];
    unsigned long SID;
    float GPA;
} SREC, *SRECP;

typedef SREC DataType;
typedef struct node
{
    DataType value;
    struct node *next; /*struct node *prev;*/
} NodeT, *NodeTP;
typedef struct list
{
    NodeTP first;
    NodeTP last;
    int count;
} ListT, *ListTP;

NodeTP indexOf(const ListTP this, int index)
{
    if (index < 0 || index >= this->count)
        return NULL;
    int i;
    NodeTP temp;
    for (temp = this->first, i = 0; temp != NULL && i < index; temp = temp->next, i++)
        ;
    return temp;
}
int insertFront(ListTP this, DataType d)
{
    NodeTP temp;
    if ((temp = malloc(sizeof(NodeT))) == NULL)
        return 0;
    temp->value = d;
    temp->next = this->first;
    if (this->count == 0)
        this->last = temp;
    this->first = temp;
    this->count++;
    return 1;
}
int insertBack(ListTP this, DataType d)
{
    NodeTP temp;
    if ((temp = malloc(sizeof(NodeT))) == NULL)
        return 0;
    temp->value = d;
    temp->next = NULL;
    this->last->next = temp;
    if (this->count == 0)
        this->first = temp;
    this->last = temp;
    this->count++;
    return 1;
} /*Returns 0 if can't allocate space. If the position given is past the end of the list, will allocate at the end of the list*/
int insertAtPos(ListTP this, DataType d, int pos)
{
    if (pos == 0)
        return insertFront(this, d);
    else if (pos >= this->count)
        return insertBack(this, d);
    NodeTP temp, curr = indexOf(this, pos - 1);
    if ((temp = malloc(sizeof(NodeT))) == NULL)
        return 0;
    temp->value = d;
    temp->next = curr->next;
    curr->next = temp;
    this->count++;
    return 1;
}
int deleteFront(ListTP this)
{
    NodeTP temp = this->first;
    if (temp == NULL)
        return 0;
    this->first = temp->next;
    if (this->count == 1)
        this->last = NULL;
    free(temp);
    temp = NULL;
    this->count--;
    return 1;
}
int deleteBack(ListTP this, DataType *value)
{
    NodeTP temp = this->last;
    if (temp == NULL)
        return 0;
    if (this->count == 1)
    {
        *value = temp->value;
        free(temp);
        this->last = NULL;
        this->first = NULL;
    }
    else
    {
        *value = temp->value;
        NodeTP newLast = indexOf(this, this->count - 2);
        newLast->next = NULL;
        this->last = newLast;
        free(temp);
        temp = NULL;
    }
    this->count--;
    return 1;
}
int deleteAtPosition(ListTP list, int pos)
{
    if (list->count == 0)
        return 0;
    if (pos == 0)
        return deleteFront(list);

    SRECP studRecPtr;
    if (pos == list->count - 1)
        return deleteBack(list, studRecPtr);

    NodeTP temp = indexOf(list, pos + 1);
    free(indexOf(list, pos));
    indexOf(list, pos - 1)->next = temp;
    return 1;
}
void clear(ListTP this)
{
    while (deleteFront(this))
        ;
    this->first = NULL;
    this->last = NULL;
    this->count = 0;
}
ListTP construct()
{
    ListTP lp;
    if ((lp = malloc(sizeof(ListT))) == NULL)
        return NULL;
    lp->first = NULL;
    lp->last = NULL;
    lp->count = 0;
    return lp;
}
void destruct(ListTP *this)
{
    clear(*this);
    free(*this);
    *this = NULL;
}

/* ListTP sortFirst(ListTP list)
{
    if (list.count == 0 || list.count == 1)
        return list;
    size_t minVal;

    for (size_t i = 0; i < list->count; i++)
    {
        minVal = i;
        for (size_t j = i + 1; j < list->count; j++)
        {
            if (strcmp(indexOf(list, minVal)->value.fname, indexOf(list, j)->value.fname) < 0)
            {
                minVal = j;
            }
        }

        if (minVal != i)
        {
            NodeTP temp = indexOf(list, i);
            temp->next = indexOf(list, minVal) -> next;

            if(i == 0){
                deleteFront(list);
                insertAtPos(list, )
            }
            indexOf(list, minVal)->value
        }
    }
} */

void putStudent(char *studentInfo, int commaIndexes[], ListTP list)
{
    size_t lNameSz;
    if (commaIndexes[0] >= 12)
    {
        lNameSz = 11;
    }
    else
    {
        lNameSz = commaIndexes[0];
    }

    char lName[lNameSz + 1];
    lName[lNameSz] = '\0';

    size_t fNameSz;
    if (commaIndexes[1] - commaIndexes[0] > 12)
    {
        fNameSz = commaIndexes[0] + 12;
    }
    else
    {
        fNameSz = commaIndexes[1];
    }

    char fName[fNameSz - commaIndexes[0]];
    fName[fNameSz - commaIndexes[0] - 1] = '\0';
    char mInitial;
    char studentID[6];
    studentID[5] = '\0';
    char GPA[strlen(studentInfo) - commaIndexes[3]];
    GPA[strlen(studentInfo) - commaIndexes[3] - 1] = '\0';

    for (size_t i = 0; i < lNameSz; i++)
    {
        lName[i] = studentInfo[i];
    }

    for (size_t i = 0, j = commaIndexes[0] + 1; j < fNameSz; i++, j++)
    {
        fName[i] = studentInfo[j];
    }

    mInitial = studentInfo[commaIndexes[1] + 1];

    for (size_t i = 0, j = commaIndexes[2] + 1; j < commaIndexes[3]; i++, j++)
    {
        studentID[i] = studentInfo[j];
    }

    for (size_t i = 0, j = commaIndexes[3] + 1; j < strlen(studentInfo); i++, j++)
    {
        GPA[i] = studentInfo[j];
    }

    char *eptr;
    unsigned long newSID = strtoul(studentID, &eptr, 10);
    float newGPA = strtof(GPA, NULL);

    SREC studRec;

    printf("%s\n", fName);
    printf("%s\n", lName);

    strncpy(studRec.fname, fName, strlen(fName) + 1);
    studRec.initial = mInitial;
    strncpy(studRec.lname, lName, strlen(lName) + 1);
    studRec.SID = newSID;
    studRec.GPA = newGPA;

    SRECP studRecPtr = &studRec;
    insertFront(list, studRec);
}

int getInput(char *command, char *commandArg)
{
    unsigned count = 0;
    unsigned loopCount = 0;
    _Bool validCommand = 0;

    while (count != 2 || validCommand == 0)
    {
        if (loopCount++ > 0)
            printf("\n---> INVALID INPUT: REATTEMPT COMMAND ENTRY <---");

        printf("\n[STUDENT DATABASE]\nVALID COMMANDS: get, put, delete, and save\n\te.g. get [Fname], get [Lname], get [SID], get [GPA], delete [SID], put [Lname,Fname,M,SID,GPA], save\nPlease enter a valid command:");
        count = scanf(" %s", command);
        if (!strcasecmp(command, "save"))
            return 1;
        count += scanf(" %s", commandArg);
        while (getchar() != '\n')
            ;
        printf("%s\n%s\n%u\n", command, commandArg, count);

        if (!strcasecmp(command, "get") || !strcasecmp(command, "put") || !strcasecmp(command, "delete"))
            validCommand = 1;
    }

    return count;
}

int delete (char *commandArg, ListTP list)
{
    char *eptr;
    unsigned long SID = strtoul(commandArg, &eptr, 10);

    for (size_t i = 0; i < list->count; i++)
    {
        if (indexOf(list, i)->value.SID == SID)
        {
            return deleteAtPosition(list, i);
        }
    }
    return 0;
}

int differentiateArg(char *command, char *commandArg, ListTP list)
{
    _Bool validArg = 1;

    for (int i = 0; commandArg[i]; i++)
        commandArg[i] = tolower(commandArg[i]);

    if (!strcmp(commandArg, "fname"))
    {
        //getFname(list);
    }
    else if (!strcmp(commandArg, "lname"))
    {
        //getLname(list);
    }
    else if (!strcmp(commandArg, "sid"))
    {
        //getSID(list);
    }
    else if (!strcmp(commandArg, "gpa"))
    {
        //getGPA(list);
    }
    else if (!strcmp(command, "delete"))
    {
        size_t i;
        for (i = 0; i < strlen(commandArg); i++)
        {
            if (!isdigit(*(commandArg + i)))
                break;
        }

        if (i == 5)
        {
            int isDeleted = delete (commandArg, list);

            if (!isDeleted)
            {
                printf("---> ERROR, COULD NOT DELETE: SID %s APPEARS TO BE INVALID <---\n", commandArg);
            }
            else
            {
                printf("---> SUCCESSFUL DELETION OF SID: %s <---\n", commandArg);
            }
        }
        else
        {
            validArg = 0;
        }
    }
    else
    {
        int commaIndexes[4];
        size_t commaCount = 0;
        for (size_t i = 0; i < strlen(commandArg); i++)
        {
            if (',' == *(commandArg + i))
            {
                commaIndexes[commaCount] = i;
                commaCount++;
            }
        }

        if (commaCount == 4)
        {
            putStudent(commandArg, commaIndexes, list);
        }
        else
        {
            validArg = 0;
        }
    }

    return validArg;
}

void save(ListTP list)
{
    FILE *wHandler, *aHandler;
    wHandler = fopen("database.txt", "w");
    fclose(wHandler);
    aHandler = fopen("database.txt", "a");

    for (size_t i = 0; i < list->count; i++)
    {
        SRECP studPtr = &(indexOf(list, i)->value);
        fwrite(studPtr, sizeof(SREC), 1, aHandler);
    }

    fclose(aHandler);
    destruct(&list);
}

int main()
{
    char command[7];
    char commandArg[36];
    ListTP list = construct();
    FILE *rHandler, *aHandler, *wHandler;

    if (rHandler = fopen("database.txt", "r"))
    {
        aHandler = fopen("database.txt", "a");
        if (!aHandler)
        {
            fclose(rHandler);
            fclose(aHandler);
            fprintf(stderr, "Error in opening database.txt");
            return EXIT_FAILURE;
        }

        SRECP studRecPtr;

        while (fread(studRecPtr, sizeof(SREC), 1, rHandler))
        {
            printf("\n%s,", studRecPtr->lname);
            printf("%s,", studRecPtr->fname);
            printf("%c,", studRecPtr->initial);
            printf("%lu,", studRecPtr->SID);
            printf("%.2f\n", studRecPtr->GPA);

            insertFront(list, *studRecPtr);
        }
        printf("\n%d\n\n", list->count);
    }
    else
    {
        wHandler = fopen("database.txt", "w");
        fclose(wHandler);
        rHandler = fopen("database.txt", "r");
        aHandler = fopen("database.txt", "a");

        if (!rHandler || !wHandler || !aHandler)
        {
            printf("something went wrong");
            fclose(rHandler);
            fclose(wHandler);
            fclose(aHandler);
            fprintf(stderr, "Error in opening database.txt");
            return EXIT_FAILURE;
        }
    }

    int sentinel = 1;
    while (sentinel == 1 && getInput(command, commandArg) != 1)
    {
        differentiateArg(command, commandArg, list);
        printf("PRESS ENTER TO CONTINUE: \n");
        char ch;
        ch = getchar();
        if (ch != '\n')
            sentinel = 0;
    }

    fclose(rHandler);
    fclose(aHandler);
    save(list);

    printf("broke out");

    return 0;
}