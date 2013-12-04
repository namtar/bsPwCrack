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

char *aalles = "0Y5vGFrD8uNxc";
char *bbutter = "C.j.k/uXnSBoQ:12352";
char *bmesser = "Zzums2/rOSvk05s";
char *ccarviar = "BxsNoy21Sx2.E";
char *ddosseh = "I8kHQttv3SK9s";
char *eentenh = "i72jb/7VtyMng";
char *ffunsb = "j6v/ER.8YW2hA";
char *gganzt = "RD/IQH5Dpfumk";
char *hheisen = "SZLTuTUzqsgT6";

/**** constants ****/
// 6 * 2 + 10
int places = 26 * 2 + 10;
char *characters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

/** Prototypes **/

void getSalt(char *encryptedPassword, char *salt);
void getChar(char *character, int index);

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

    char result = crypt(tryPassword, encryptedPW);
    if (strcmp(result, encryptedPW) == 0) {
        // password matched
        // stop threads
        // display matched password
    }
}

/*
 * Main function.
 * Use fork(II), wait(II), signal(II),
 * kill(II) sowie pipe(II)
 */
int main(int argc, char** argv) {

    // nur a-z A-Z 0-9

    // time import to measure the time in seconds

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