// error.c
// Meteor Pi, Cambridge Science Centre
// Dominic Ford

// -------------------------------------------------
// Copyright 2016 Cambridge Science Centre.

// This file is part of Meteor Pi.

// Meteor Pi is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Meteor Pi is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Meteor Pi.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils/asciiDouble.h"
#include "utils/error.h"
#include "settings.h"
#include "str_constants.h"

static char temp_stringA[LSTR_LENGTH], temp_stringB[LSTR_LENGTH], temp_stringC[LSTR_LENGTH], temp_stringD[LSTR_LENGTH], temp_stringE[LSTR_LENGTH];
char temp_err_string[LSTR_LENGTH];

void gnom_error(int ErrType, char *msg) {
    int i = 0;

    if (msg != temp_stringA) {
        strcpy(temp_stringA, msg);
        msg = temp_stringA;
    }

    temp_stringB[i] = '\0';

    if (ErrType != ERR_PREFORMED) // Do not prepend anything to pre-formed errors
    {
        // Prepend error type
        switch (ErrType) {
            case ERR_INTERNAL:
                sprintf(temp_stringB + i, "Internal Error: ");
                break;
            case ERR_MEMORY  :
            case ERR_GENERAL :
                sprintf(temp_stringB + i, "Error: ");
                break;
            case ERR_SYNTAX  :
                sprintf(temp_stringB + i, "Syntax Error: ");
                break;
            case ERR_NUMERIC :
                sprintf(temp_stringB + i, "Numerical Error: ");
                break;
            case ERR_FILE    :
                sprintf(temp_stringB + i, "File Error: ");
                break;
        }
        i += strlen(temp_stringB + i);
    }

    strcpy(temp_stringB + i, msg);
    if (DEBUG) { gnom_log(temp_stringB); }
    sprintf(temp_stringC, "%s\n", temp_stringB);
    fputs(temp_stringC, stderr);
    return;
}

void gnom_fatal(char *file, int line, char *msg) {
    char introline[FNAME_LENGTH];
    if (msg != temp_stringE) strcpy(temp_stringE, msg);
    sprintf(introline, "Fatal Error encountered in %s at line %d: %s", file, line, temp_stringE);
    gnom_error(ERR_PREFORMED, introline);
    if (DEBUG) gnom_log("Terminating with error condition 1.");
    exit(1);
}

void gnom_warning(int ErrType, char *msg) {
    int i = 0;

    if (msg != temp_stringA) {
        strcpy(temp_stringA, msg);
        msg = temp_stringA;
    }

    temp_stringB[i] = '\0';

    if (ErrType != ERR_PREFORMED) // Do not prepend anything to pre-formed errors
    {
        // Prepend error type
        switch (ErrType) {
            case ERR_INTERNAL:
                sprintf(temp_stringB + i, "Internal Warning: ");
                break;
            case ERR_MEMORY  :
            case ERR_GENERAL :
                sprintf(temp_stringB + i, "Warning: ");
                break;
            case ERR_SYNTAX  :
                sprintf(temp_stringB + i, "Syntax Warning: ");
                break;
            case ERR_NUMERIC :
                sprintf(temp_stringB + i, "Numerical Warning: ");
                break;
            case ERR_FILE    :
                sprintf(temp_stringB + i, "File Warning: ");
                break;
        }
        i += strlen(temp_stringB + i);
    }

    strcpy(temp_stringB + i, msg);
    if (DEBUG) { gnom_log(temp_stringB); }
    sprintf(temp_stringC, "%s\n", temp_stringB);
    fputs(temp_stringC, stderr);
    return;
}

void gnom_report(char *msg) {
    if (msg != temp_stringA) strcpy(temp_stringA, msg);
    if (DEBUG) {
        sprintf(temp_stringC, "%s%s", "Reporting:\n", temp_stringA);
        gnom_log(temp_stringC);
    }
    sprintf(temp_stringC, "%s\n", temp_stringA);
    fputs(temp_stringC, stdout);
    return;
}

void gnom_log(char *msg) {
    static FILE *logfile = NULL;
    static int latch = 0;
    char linebuffer[LSTR_LENGTH];

    if (latch) return; // Do not allow recursive calls, which might be generated by the call to gnom_fatal below
    latch = 1;
    if (logfile == NULL) {
        if ((logfile = fopen(OUTPUT_PATH "/meteorPi.log", "a")) == NULL) {
            gnom_fatal(__FILE__, __LINE__, "Could not open log file to write.");
            exit(1);
        }
        setvbuf(logfile, NULL, _IOLBF, 0); // Set log file to be line-buffered, so that log file is always up-to-date
    }

    if (msg != temp_stringD) strcpy(temp_stringD, msg);
    fprintf(logfile, "[%s c ] %s\n", strStrip(friendlyTimestring(0), linebuffer), temp_stringD);
    fflush(logfile);
    latch = 0;
    return;
}

void dcffread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    if (fread(ptr, size, nmemb, stream) != nmemb) gnom_fatal(__FILE__, __LINE__, "file read fail");
    return;
}

