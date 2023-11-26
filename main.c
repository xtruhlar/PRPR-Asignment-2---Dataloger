#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// typedef for records
typedef struct zaznam
{
    long long idMeranejOsoby;
    char menoOsoby[30];
    char meraciModul[4];
    char meranaVelicina[3];
    float hodnota;
    char casMerania[5];
    long long datumMerania;
    unsigned long long dateAndTime;
    struct zaznam *nextInLine;
} ZAZNAM;

ZAZNAM *vymen(ZAZNAM *ptr1, ZAZNAM *ptr2);

// function nacitaj() -> 'n' input
int nacitaj(ZAZNAM **pHead, int *nor)
{
    int pocitadlo = -1; // rows
    int numOfRecords = 0;
    FILE *fptrR;
    char oneRow[100]; // row for reading

    ZAZNAM *pNow = NULL;
    ZAZNAM *pHelp;

    // dealocate memory in case the list was created already
    if (*pHead != NULL)
    {
        while (*pHead != 0)
        {
            pNow = *pHead;
            *pHead = (*pHead)->nextInLine;
            free(pNow);
        }
    }

    // file open
    fptrR = fopen("C:\\Users\\david\\OneDrive\\Desktop\\zadanie_na_prpr\\P2\\dataloger_V2.txt", "r");
    if (fptrR == NULL)
        printf("Zaznamy neboli nacitane!\n");
    else
    {

        // reading the file row by row
        while (fgets(oneRow, 100, fptrR) != NULL)
        {
            pocitadlo++;
            oneRow[strlen(oneRow)] = '\0';

            if (pocitadlo == 0)
            {
                // memory alocation
                pHelp = (ZAZNAM *)malloc(sizeof(ZAZNAM));
                numOfRecords++;

                // the first node
                if (*pHead == NULL)
                    *pHead = pHelp;

                // nodes
                if (pNow != NULL)
                    pNow->nextInLine = pHelp;

                // the last node
                pNow = pHelp;
                pNow->nextInLine = NULL;

                // insert file into nodes
            }
            else if (pocitadlo == 1)
            {
                oneRow[strlen(oneRow) - 1] = '\0';
                pNow->idMeranejOsoby = atoll(oneRow);
            }
            else if (pocitadlo == 2)
            {
                oneRow[strlen(oneRow) - 1] = '\0';
                strcpy(pNow->menoOsoby, oneRow);
            }
            else if (pocitadlo == 3)
            {
                oneRow[strlen(oneRow) - 1] = '\0';
                strcpy(pNow->meraciModul, oneRow);
            }
            else if (pocitadlo == 4)
            {
                oneRow[strlen(oneRow) - 1] = '\0';
                strcpy(pNow->meranaVelicina, oneRow);
            }
            else if (pocitadlo == 5)
            {
                oneRow[strlen(oneRow) - 1] = '\0';
                pNow->hodnota = atof(oneRow);
            }
            else if (pocitadlo == 6)
            {
                oneRow[strlen(oneRow) - 1] = '\0';
                strcpy(pNow->casMerania, oneRow);
            }
            else if (pocitadlo == 7)
            {
                oneRow[strlen(oneRow)] = '\0';
                pNow->datumMerania = atoll(oneRow);
                // new node
                pocitadlo = -1;
            }
        }
        printf("Nacitalo sa %d zaznamov.\n", numOfRecords);
        *nor = numOfRecords;
        // file close
        fclose(fptrR);
    }
    return numOfRecords;
}

// function vypis() -> 'v' input
void vypis(ZAZNAM *pHead)
{
    ZAZNAM *pNow;
    int n = 0;
    pNow = pHead;

    if (pNow != NULL)
    {
        while (pNow != NULL)
        {
            n++;
            // print nodes
            printf("%d: \n", n);
            printf("ID cislo mer. osoby: %lld\n", pNow->idMeranejOsoby);
            printf("Meno osoby: %s\n", pNow->menoOsoby);
            printf("Mer. modul: %s\n", pNow->meraciModul);
            printf("Typ mer. veliciny: %s\n", pNow->meranaVelicina);
            printf("Hodnota: %f\n", pNow->hodnota);
            printf("Cas merania: %s\n", pNow->casMerania);
            printf("Datum: %lld\n", pNow->datumMerania);
            pNow = pNow->nextInLine;
        }
    }
}

// function zmaz() -> 'z' input
void zmaz(ZAZNAM **pHead)
{
    long long idFromUser = 0;
    ZAZNAM *pNow = *pHead;
    ZAZNAM *pHelp;
    pHelp = NULL;

    // users input
    scanf("%lld", &idFromUser);

    if (pNow != NULL)
    {
        while (pNow != NULL)
        {
            // find nodes with the ID from user
            if (idFromUser == pNow->idMeranejOsoby)
            {
                // delete the first node
                if (pNow == *pHead)
                {
                    if (pNow->nextInLine == NULL)
                    {
                        *pHead = NULL;
                        printf("Zaznam pre ID: %lld pre modul %s bol vymazany.\n", pNow->idMeranejOsoby,
                               pNow->meraciModul);
                    }
                    else
                    {
                        *pHead = pNow->nextInLine;
                        printf("Zaznam pre ID: %lld pre modul %s bol vymazany.\n", pNow->idMeranejOsoby,
                               pNow->meraciModul);
                    }
                    free(pNow);
                    pNow = *pHead;

                    // delete the last node
                }
                else if (pNow->nextInLine == NULL)
                {
                    pHelp->nextInLine = NULL;
                    printf("Zaznam pre ID: %lld pre modul %s bol vymazany.\n", pNow->idMeranejOsoby, pNow->meraciModul);
                    free(pNow);
                    pNow = pHelp;
                }
                else
                {
                    // delete node
                    pHelp->nextInLine = pNow->nextInLine;
                    printf("Zaznam pre ID: %lld pre modul %s bol vymazany.\n", pNow->idMeranejOsoby, pNow->meraciModul);
                    free(pNow);
                    pNow = pHelp->nextInLine;
                }
            }
            else
            {
                // next node
                pHelp = pNow;
                pNow = pNow->nextInLine;
            }
        }
    }
}

// function usporiadaj() -> 'u' input
void usporiadaj(ZAZNAM **pHead, int *nor, int *check)
{
    ZAZNAM *pNow;
    pNow = *pHead;
    // puttint date and time into one unsigned long long
    while (pNow != NULL)
    {
        pNow->dateAndTime =
                (unsigned long long int)pNow->datumMerania * 10000 + (unsigned long long int)atoi(pNow->casMerania);
        pNow = pNow->nextInLine;
    }
    ZAZNAM **h;
    int i, j, swapped;
    // bubblesort list
    for (i = 0; i <= *nor; i++)
    {
        h = pHead;
        swapped = 0;

        for (j = 0; j < *nor - i - 1; j++)
        {
            ZAZNAM *p1 = *h;
            ZAZNAM *p2 = p1->nextInLine;
            if (p1->dateAndTime > p2->dateAndTime)
            {
                // swap nodes
                *h = vymen(p1, p2);
                swapped = 1;
                *check = 1;
            }
            h = &(*h)->nextInLine;
        }
        // break, if there is not swapping
        if (swapped == 0)
            break;
    }
}

// function for swapping nodes
ZAZNAM *vymen(ZAZNAM *ptr1, ZAZNAM *ptr2)
{
    ZAZNAM *tmp = ptr2->nextInLine;
    ptr2->nextInLine = ptr1;
    ptr1->nextInLine = tmp;
    return ptr2;
}

// function pridaj() -> 'p' input
void pridaj(ZAZNAM **pHead)
{
    int position;
    ZAZNAM *pNow;
    ZAZNAM *pUser;
    ZAZNAM *pPrev;

    // position in the list from user
    scanf("%d", &position);

    if (position > 0)
    {
        // memory allocation
        pUser = (ZAZNAM *)malloc(sizeof(ZAZNAM));
        char fullName;
        char lastName[50];
        // users input - new node
        scanf("%lld", &pUser->idMeranejOsoby);
        getchar();
        gets(lastName);
        strcpy(pUser->menoOsoby, lastName);
        scanf("%s/n", pUser->meraciModul);
        scanf("%s/n", pUser->meranaVelicina);
        scanf("%f/n", &pUser->hodnota);
        scanf("%s/n", pUser->casMerania);
        scanf("%lld/n", &pUser->datumMerania);

        // in the case list wasn't created, new node is the first one
        if (*pHead == NULL)
        {
            pUser->nextInLine = NULL;
            (*pHead) = pUser;
        }
        else
            pUser->nextInLine = NULL;

        // add new node in the middle
        for (int i = 1; i <= position; i++)
        {
            if (i == 1)
            {
                pNow = (*pHead);
            }
            else
            {
                if (pNow->nextInLine != NULL)
                {
                    pNow = pNow->nextInLine;
                }

                // add new node in the end
                if (pNow->nextInLine == NULL)
                {
                    pNow->nextInLine = pUser;
                    pNow = NULL;
                    break;
                }
            }

            // previous node
            if (i == (position - 1) && position != 1)
            {
                pPrev = pNow;
            }
        }

        if (pNow != NULL)
        {
            pUser->nextInLine = pNow;
            // nodes in middle
            if (position != 1)
            {
                pPrev->nextInLine = pUser;
            }
            // the first node
            if (position == 1)
            {
                (*pHead) = pUser;
                //  (*pHead)->nextInLine = NULL;
            }
        }
    }
}

// function hladaj() -> 'h' input
void hladaj(ZAZNAM *pHead)
{
    ZAZNAM *pNow = pHead;
    char userInput[5];
    int poradie = 0;

    // users input
    scanf("%s", userInput);

    if (pNow != NULL)
    {
        while (pNow != NULL)
        {
            // compare input from user and the IDs from list
            if (strcmp(userInput, pNow->meraciModul) == 0)
            {
                poradie++;
                // printing nodes with users input
                printf("%d: \n", poradie);
                printf("ID cislo mer. osoby: %lld\n", pNow->idMeranejOsoby);
                printf("Meno osoby: %s\n", pNow->menoOsoby);
                printf("Mer. modul: %s\n", pNow->meraciModul);
                printf("Typ mer. veliciny: %s\n", pNow->meranaVelicina);
                printf("Hodnota: %f\n", pNow->hodnota);
                printf("Cas merania: %s\n", pNow->casMerania);
                printf("Datum: %lld\n", pNow->datumMerania);
            }
            // next node
            pNow = pNow->nextInLine;
        }
    }
    // check
    if (poradie == 0)
        printf("Pre meraci modul %s niesu zaznamy.\n", userInput);
    poradie = 0;
}

// function reorganizuj() -> 'r' input
void reaorganizuj(ZAZNAM *pHead)
{
    int src, des;
    ZAZNAM *pSrc = NULL, *pDes = NULL;
    ZAZNAM *pNow, *tempo;

    tempo = (ZAZNAM *)malloc(sizeof(ZAZNAM));
    pSrc = (ZAZNAM *)malloc(sizeof(ZAZNAM));
    pDes = (ZAZNAM *)malloc(sizeof(ZAZNAM));
    // return if the list is emptry
    if (pHead == NULL)
    {
        return;
    }

    // users input
    scanf("%d %d", &src, &des);

    if (src > 0 && des > 0)
    {
        pNow = pHead;
        int pocitadlo = 0;
        while (pNow != NULL)
        {
            pocitadlo++;
            if (pocitadlo == 1)
            {
                pNow = pHead;
                pNow->nextInLine = pHead->nextInLine;
            }

            if (pocitadlo == src)
            {
                pSrc = pNow;
                pSrc->nextInLine = pNow->nextInLine;
            }

            if (pocitadlo == des)
            {
                pDes = pNow;
                pDes->nextInLine = pNow->nextInLine;
            }
            pNow = pNow->nextInLine;
        }

        // rewrite the nodes
        tempo->idMeranejOsoby = pSrc->idMeranejOsoby;
        strcpy(tempo->menoOsoby, pSrc->menoOsoby);
        strcpy(tempo->meraciModul, pSrc->meraciModul);
        strcpy(tempo->meranaVelicina, pSrc->meranaVelicina);
        tempo->hodnota = pSrc->hodnota;
        strcpy(tempo->casMerania, pSrc->casMerania);
        tempo->datumMerania = pSrc->datumMerania;

        pSrc->idMeranejOsoby = pDes->idMeranejOsoby;
        strcpy(pSrc->menoOsoby, pDes->menoOsoby);
        strcpy(pSrc->meraciModul, pDes->meraciModul);
        strcpy(pSrc->meranaVelicina, pDes->meranaVelicina);
        pSrc->hodnota = pDes->hodnota;
        strcpy(pSrc->casMerania, pDes->casMerania);
        pSrc->datumMerania = pDes->datumMerania;

        pDes->idMeranejOsoby = tempo->idMeranejOsoby;
        strcpy(pDes->menoOsoby, tempo->menoOsoby);
        strcpy(pDes->meraciModul, tempo->meraciModul);
        strcpy(pDes->meranaVelicina, tempo->meranaVelicina);
        pDes->hodnota = tempo->hodnota;
        strcpy(pDes->casMerania, tempo->casMerania);
        pDes->datumMerania = tempo->datumMerania;
    }
}

// main function
int main()
{
    // declarations
    char vstup;
    ZAZNAM *pHead = NULL;
    ZAZNAM *pdealok;
    int numOfRecords = 0;
    int *nor = &numOfRecords;
    int check = 0;
    int *pswapped = &check;

    // users input
    while ((vstup = getchar()) != EOF)
    {
        switch (vstup)
        {
            case 'n': // function nacitaj() -> 'n' input
                nacitaj(&pHead, nor);
                break;
            case 'v': // function vypis() -> 'v' input
                vypis(pHead);
                break;
            case 'z': // function zmaz() -> 'z' input
                zmaz(&pHead);
                break;
            case 'u': // function usporiadaj() -> 'u' input
                usporiadaj(&pHead, nor, pswapped);
                if (*pswapped == 1)
                {
                    printf("Spajany zoznam bol usporiadany.\n");
                }
                else
                    printf("Chyba.\n");
                break;
            case 'p': // function pridaj() -> 'p' input
                pridaj(&pHead);
                break;
            case 'h': // function hladaj() -> 'h' input
                hladaj(pHead);
                break;
            case 'r': // function reorganizuj() -> 'r' input
                reaorganizuj(pHead);
                break;
            case 'k': // input 'k' deallocate memory and return 0
                if (pHead != NULL)
                {
                    while (pHead != 0)
                    {
                        pdealok = pHead;
                        pHead = pHead->nextInLine;
                        free(pdealok);
                    }
                }
                return 0;
        }
    }
}