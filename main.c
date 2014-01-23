/* 
 * File:   main.c
 * Author: Matthias Drummer <s0584234>
 *
 * Created on 4. Dezember 2013, 21:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

#define numberOfCpu 4

/***** Passwords *****/

char *aalles = "0Y5vGFrD8uNxc"; // 2 chars tJ
char *bbutter = "C.j.k/uXnSBoQ"; // 3 chars a7L
char *ccarviar = "BxsNoy21Sx2.E"; // 4 chars Q9vX
char *ddosseh = "I8kHQttv3SK9s"; // 5 chars
char *eentenh = "i72jb/7VtyMng"; // 6 chars
char *ffunsb = "j6v/ER.8YW2hA"; // 7 chars
char *gganzt = "RD/IQH5Dpfumk"; // 8 chars
char *hheisen = "SZLTuTUzqsgT6"; // 9 chars
char *bmesser = "Zzums2/rOSvk05s"; // dont know

/**** constants ****/
// 6 * 2 + 10
int places = 26 * 2 + 10;
char characters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
short passwordFound = 0; // set to 1 if password was found
//int loopsStarted = 0;
char salt[3];


int startValue = 0;
int endValue = 0;
char foundPassword[20];

/** Prototypes **/

void getChar(char *character, int index);

void doLoop(int numberOfPlaces, int loopNumber, char *tryPassword, char *passwordToCrack);
void subLoop(int numberOfPlaces, int loopNumber, char *tryPassword, char *passwordToCrack);

/*
 * Main function.
 * Use fork(II), wait(II), signal(II),
 * kill(II) sowie pipe(II)
 */
int main(int argc, char** argv) {

    printf("Start shiny password crackin'\n");

    // nur a-z A-Z 0-9

    // Was tun:
    // fork liefert dem parent die pid des Kindes zurück
    // pids in einem array speichern
    // durch eine schleife forken
    // vor jedem fork muss der Start und Endwert für die laufweite in einer globalen Variable gespeichert werden
    // diese wird beim Fork mit dupliziert. So kann dem Kind mitgeteilt werden was es prüfen soll.
    // Elternteil muss mit read aus der pipe lesen. Dafür gibt es einen bestimmten Filedescriptor
    // wie lässt man einen Kindprozess terminieren ohne dass das PW gefunden wurde?

    int pids[numberOfCpu];
    int pipeFds[2];
    int returnValue = pipe(pipeFds);
    if (returnValue == -1) {
        printf("Error when creating a pipe\n");
        return EXIT_FAILURE;
    }

    char *passwordToCrack = ddosseh;
    char tryPassword[6]; // remember, this must be by one greater than the lenght of the password to check.
    tryPassword[sizeof (tryPassword) - 1] = '\0';
    int numberOfPlaces = (sizeof (tryPassword) - 1);
    printf("NumberOfPlaces %i\n", numberOfPlaces);

    int interval = sizeof (characters) / numberOfCpu;
    printf("Interval: %i\n", interval);

    int pid;
    int i;
    for (i = 0; i < numberOfCpu; i++) {

        printf("Start forking\n");

        startValue = endValue;
        endValue += interval + 1;
        if (endValue > sizeof (characters)) {
            endValue = sizeof (characters);
        }
        printf("Startvalue General: %i\n", startValue);
        printf("Endvalue General: %i\n", endValue);

        pid = fork();
        pids[i] = pid;
        printf("Fork returned Pid: %i at increment %i\n", pid, i);
        if (pid == 0) {
            printf("Start child\n");
            //            wait(5);
            // i am a child
            // close unneeded pipe read channel
            close(pipeFds[0]);
            // do cracking
            // write in pipe when password was found
            int LOOP_ZERO = 0;

            salt[0] = passwordToCrack[0];
            salt[1] = passwordToCrack[1];
            salt[2] = '\0';
            printf("Salt: %s\n", salt);
            doLoop(numberOfPlaces, LOOP_ZERO, tryPassword, passwordToCrack);

            //            printf("Write found password: %s\n", foundPassword);
            if (strlen(foundPassword) > 0) {
                printf("Write to Pipe\n\n");
                write(pipeFds[1], foundPassword, sizeof (foundPassword));
            }
            close(pipeFds[1]);
            exit(EXIT_SUCCESS);
        } else if (pid < 0) {
            printf("Fehler beim Fork\n");
            return EXIT_FAILURE;
        }
    }

    if (sizeof (pids) / sizeof (int) > 0 && pid != 0) {
        // i am a parent
        //            wait(NULL);
        printf("Pid of Child: %i\n", pid);
        int i;
        printf("Anzahl der Pids: %i\n", sizeof (pids) / sizeof (int));
        //            for(i = 0; i < sizeof(pids) / sizeof(int); i++) {
        //                wait(&pids[i]);
        //            }
        close(pipeFds[1]); // close unneeded write channel
        char returnedPassword[20];
        returnedPassword[0] = '\0';
        // read pipe and terminate childs if password was found
        read(pipeFds[0], &returnedPassword, sizeof (returnedPassword));
        for (i = 0; i < numberOfCpu; i++) {
            kill(pids[i], 1); // send sigterm to childs
        }

        printf("The found password is: %s\n", returnedPassword);
        close(pipeFds[1]);
    }
    return (EXIT_SUCCESS);
}

void getChar(char *character, int index) {

    *character = characters[index];

}

void doLoop(int numberOfPlaces, int loopNumber, char *tryPassword, char *passwordToCrack) {

    printf("Startvalue: %i\n", startValue);
    printf("Endvalue: %i\n", endValue);
    // this is only for loop zero. This loop has to mention the start and end value
    int i;
    for (i = startValue; i < endValue; i++) {

        //        loopsStarted++;

        // if password was found exit loop
        if (passwordFound == 1) {
            break;
        }

        tryPassword[loopNumber] = characters[i];
        printf("Trypassword First Index %c\n", tryPassword[0]);

        if ((loopNumber + 1) < numberOfPlaces) {
            // if loop number is less than number of places then start new loop.
            int newLoopNumber = loopNumber + 1;
            subLoop(numberOfPlaces, newLoopNumber, tryPassword, passwordToCrack);
        }
        if (numberOfPlaces == (loopNumber + 1)) {
            // do crypting
            char *result = strdup(crypt(tryPassword, salt));

            if (strcmp(result, passwordToCrack) == 0) {
                printf("Das gesuchte Passwort ist: %s\n\n", tryPassword);
                strcpy(foundPassword, tryPassword);
                passwordFound = 1;
            } else {
                free(result);
            }
        }
    }

}

void subLoop(int numberOfPlaces, int loopNumber, char* tryPassword, char* passwordToCrack) {

    int i;
    for (i = 0; i < sizeof (characters); i++) {

        //        loopsStarted++;
        //        printf("LoopsStarted %i\n", loopsStarted);

        // if password was found exit loop
        if (passwordFound == 1) {
            break;
        }

        tryPassword[loopNumber] = characters[i];
        //        printf("LoopNumber %i\n", loopNumber);
        //        printf("TryPassword %s\n", tryPassword);

        if ((loopNumber + 1) < numberOfPlaces) {
            // if loop number is less than number of places then start new loop.
            int newLoopNumber = loopNumber + 1;
            subLoop(numberOfPlaces, newLoopNumber, tryPassword, passwordToCrack);
        }
        if (numberOfPlaces == (loopNumber + 1)) {
            // do crypting            
            char *result = strdup(crypt(tryPassword, salt));

            if (strcmp(result, passwordToCrack) == 0) {
                printf("Das gesuchte Passwort ist: %s\n\n", tryPassword);
                strcpy(foundPassword, tryPassword);
                passwordFound = 1;
            } else {
                free(result);
            }
        }
    }
}

