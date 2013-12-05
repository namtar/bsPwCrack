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

/***** Passwords *****/

char *aalles = "0Y5vGFrD8uNxc"; // 2 chars
char *bbutter = "C.j.k/uXnSBoQ:12352"; // 3 chars
char *ccarviar = "BxsNoy21Sx2.E"; // 4 chars
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
int loopsStarted = 0;

/** Prototypes **/

void getSalt(char *encryptedPassword, char *salt);
void getChar(char *character, int index);

void doLoop(int numberOfPlaces, int loopNumber, char *tryPassword, char *passwordToCrack);

void doCrypting(char *encryptedPW, int numberOfPlaces) {

    //    char *salt;
    //
    //    getSalt(encryptedPW, salt);
    // TODO: kann sein dass man statt dem salt das verschlüsselte password übergeben darf.
    // numberOfPlaces determines how much loops are to open.
    int loopsStarted = 0;
    char tryPassword[numberOfPlaces];
    int placeIndexes[numberOfPlaces];

    // rekursion

    //    char result = crypt(tryPassword, encryptedPW);
    //    if (strcmp(result, encryptedPW) == 0) {
    // password matched
    // stop threads
    // display matched password
    //    }
}

/*
 * Main function.
 * Use fork(II), wait(II), signal(II),
 * kill(II) sowie pipe(II)
 */
int main(int argc, char** argv) {

    printf("Start shiny password crackin'\n");

    // nur a-z A-Z 0-9

    // time import to measure the time in seconds
    int LOOP_ZERO = 0;

    char tryPassword[5]; // remember, this must be by one greater than the lenght of the password to check.
    tryPassword[sizeof (tryPassword) - 1] = '\0';
//    (sizeof (tryPassword) - 1)
    doLoop(4, LOOP_ZERO, tryPassword, ccarviar);
    printf("Loops done: %i\n", loopsStarted);
    printf("Number of chars: %i\n", places);

    return (EXIT_SUCCESS);
}

/**
 * Extract the salt from the given encrypted passwords
 * 
 * @param encryptedPassword the encrypted password
 * @param salt the salt extracted from the given encrypted password
 */
void getSalt(char *encryptedPassword, char *salt) {

    // TODO: get the first two chars of the given encrypted password

}

void getChar(char *character, int index) {

    *character = characters[index];

}

void doLoop(int numberOfPlaces, int loopNumber, char *tryPassword, char *passwordToCrack) {

    char salt[3];
    salt[0] = passwordToCrack[0];
    salt[1] = passwordToCrack[1];
    salt[2] = '\0';

    int i;
    for (i = 0; i < sizeof (characters); i++) {

        loopsStarted++;

        // if password was found exit loop
        if (passwordFound == 1) {
            break;
        }

        tryPassword[loopNumber] = characters[i];

        if ((loopNumber + 1) < numberOfPlaces) {
            // if loop number is less than number of places then start new loop.
            int newLoopNumber = loopNumber + 1;
            doLoop(numberOfPlaces, newLoopNumber, tryPassword, passwordToCrack);
        }
        if (numberOfPlaces == (loopNumber + 1)) {
            // do crypting
            char *result = strdup(crypt(tryPassword, salt));

            if (strcmp(result, passwordToCrack) == 0) {
                printf("Das gesuchte Passwort ist: %s\n\n", tryPassword);
                passwordFound = 1;
            }
        }
    }

}
