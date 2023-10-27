#include <assert.h>     // Assertion for truth testing
#include <ctype.h>      // Characters typing methods
#include <errno.h>      // Error handling
#include <fenv.h>       // File environment handling
#include <float.h>      // Float conversion (more spesific)
#include <limits.h>     // Limitations per data types
#include <locale.h>     // Local variables handling (more spesific)
#include <math.h>       // Mathematical functions
#include <stdbool.h>    // Standard boolean values handling
#include <stddef.h>     // Standard definitions for certain types
#include <stdint.h>     // Standard integers handling (more spesific)
#include <stdio.h>      // Standard stream handling
#include <stdlib.h>     // Standard library (more spesific)
#include <string.h>     // String manipulation and handling
#include <time.h>       // Time conversion
#include <uchar.h>      // Character conversion (U type conversion)
#include <unistd.h>     // Giving POSIX syntaxes operating system API
#include <wchar.h>      // Wide character conversion (W type conversion)
#include <wctype.h>     // Wide character typing method (String type conversion)
#include <windows.h>    // Windows header file (apps and notifications)

#define BUFSIZE10   1024
#define BUFSIZE11   2048
#define BUFSIZE12   4096
#define BUFSIZE13   8192
#define BUFSIZE14   16384
#define BUFSIZE15   32768
#define BUFSIZE16   65536

// ClearScreen() method, works for both Windows and UNIX.
void ClearScreen(void) {
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
#else
    #error "ERROR: Unsupported platform for performing clear screen!"
#endif
}

/* ERROR HANDLING METHOD */
// Working with various errors, mostly defined here as global variables

const char* SOURCEFILENULLERROR = "SourceFileNotExists";
const char* DESTINATIONFILENULLERROR = "DestinationFileNotExists";

void ErrorHandling(const char* ErrorType, const char* ErrorSource) {
    if (strcmp(ErrorType, SOURCEFILENULLERROR) == 0)
        printf("Unable to open the source file named '%s'!\n           > Make sure you have the file names '%s' ready to be opened,\n      and not some empty folder or none specified beforehand.\n\nErrorCode: %s", ErrorSource, ErrorSource, ErrorType);
    if (strcmp(ErrorType, DESTINATIONFILENULLERROR) == 0)
        printf("Unable to create the destination file named '%s'!\n    > This maybe an error that occured if there's an error for having\n      permission to make and write to a file, error in naming the file,\n      and many more. Try to troubleshoot for the errors and try again!\n\nErrorCode: %s", ErrorSource, ErrorType);
}

/* PROTOTYPE FUNCTIONS DEFINITION */
// Important Starting Features (CORE FEATURES)
// Core features available: 5
void MainMenu(void);
void HelpMenu(void);
void EncryptTxtFile(const char*, const char*, int, bool);
void DecryptTxtFile(const char*, bool, int, char ReadDecryptedKeyString[BUFSIZE16]);
char *TrimWhiteSpaces(char*);

// Notifications Features (CORE FEATURES)
// Notification features available: 4
int INFO_OK_NOTIFICATION(const char*, const char*);
int QUESTION_YESNOCANCEL_NOTIFICATION(const char*, const char*);
int WARNING_CANCELTRYCONTINUE_NOTIFICATION(const char*, const char*);
int ERROR_OKCANCEL_NOTIFICATION(const char*, const char*);

// Available main application features: 6
void F1_MoneytoryTransactionsRegister(void);    // Easy     (PRIORITY)
void F2_MoneytoryGroupingPerCategory(void);     // Medium   (LATER)
void F3_BudgetCreationAndMonitoring(void);      // Easy     (PRIORITY)
void F4_FilterSearchingData(void);              // Medium   (LATER)
void F5_ReminderAndSetNotifications(void);      // Hard     (LAST BUT NOT LEAST)
void F6_DataVisualization(void);                // Harder   (LAST BUT NOT LEAST)

/* STARTING THE DECLARATIONS: REMINDER AND NOTIFICATIONS */
/* Initialize functions and classes (if needed) */

char* Title, Message, Description;
int INFO_OK_NOTIFICATION(const char* Title, const char* Message) {
    int msgbox = MessageBox( \
        NULL, \
        (LPCWSTR) Message, \
        (LPCWSTR) Title, MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON1);
    
    switch (msgbox) {
        case IDOK: return; break;
        default: return; break;
    }
    return msgbox;
}

int QUESTION_YESNOCANCEL_NOTIFICATION(const char* Title, const char* Message) {
    int msgboxID = MessageBox( \
        NULL, \
        (LPCWSTR) Message, \
        (LPCWSTR) Title, MB_ICONQUESTION | MB_YESNOCANCEL | MB_DEFBUTTON2);

    switch (msgboxID) {
    case IDYES: break;
    case IDNO: break;
    case IDCANCEL: break;
    }

    return msgboxID;
}

int WARNING_CANCELTRYCONTINUE_NOTIFICATION(const char* Title, const char* Message) {
    int msgboxID = MessageBox( \
        NULL, \
        (LPCWSTR) Message, \
        (LPCWSTR) Title, MB_ICONEXCLAMATION | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);

    switch (msgboxID) {
    case IDCANCEL: break;
    case IDTRYAGAIN: break;
    case IDCONTINUE: break;
    }

    return msgboxID;
}

int ERROR_OKCANCEL_NOTIFICATION(const char* Title, const char* Message) {
    int msgboxID = MessageBox( \
        NULL, \
        (LPCWSTR) Message, \
        (LPCWSTR) Title, MB_ICONERROR | MB_OKCANCEL | MB_DEFBUTTON1);

    switch (msgboxID) {
    case IDOK: break;
    case IDCANCEL: break;
    }

    return msgboxID;
}

/* STARTING THE DECLARATIONS: ENCRYPTION AND DECRYPTION DATA */
/* Initialize functions and classes (if needed) */

char *TrimWhiteSpaces(char *SourceString) {
    char *EndString;

    while (isspace((unsigned char) *SourceString)) SourceString++;  // Trim leading space
    if (*SourceString == 0) return SourceString;                    // All spaces?
    EndString = SourceString + strlen(SourceString) - 1;            // Trim trailing space
    while (EndString > SourceString && isspace((unsigned char) *EndString)) EndString--;

    EndString[1] = '\0'; // Write new null terminator character
    return SourceString;
}

/* Abbreviation of "Encrypt Text File" is one of the CORE FEATURES here in this application,
and the return type function is `void()`, and requires the program to accept:
`>>>` FOUR (4) arguments, accordingly as explained below.

`> const char *SourceTextFile`: A source text file that needs to be the source before being encrypted.
`> const char *DestinationTextFile`: A destination text file that needs to be the place of the after-encrypted.
`> int EncryptionKey`: A MUST required encryption key in order the text file to be encrypted. The code is spesific, and MUST be set in the program code before runtime, or included in the `**argv` parameter at command line before runtime. The encryption key HAS TO BE THE SAME for the decryption key, because one different in a single number will resulted in a non-correct encryption/decryption method.
`> bool SourceTextFileDeletion`: Mode for deleting the source text file right after the encryption, so the copy of the data will not get leaked if the source that's not get encrypted is stil intact on the folder.

`[Format: 4th argument] <TRUE> || <FALSE>`
*/
void EncryptTxtFile(const char* SourceTextFile, const char* DestinationTextFile, int EncryptionKey, bool SourceTextFileDeletion) {
    FILE *FSource, *FDestination;
    int BufLen;
    char BUFFER[BUFSIZE16], DeleteSourceTxtFile[128];

    FSource         = fopen(SourceTextFile, "r");
    FDestination    = fopen(DestinationTextFile, "w");
    if (FSource == NULL)        ErrorHandling(SOURCEFILENULLERROR, SourceTextFile);
    if (FDestination == NULL)   ErrorHandling(DESTINATIONFILENULLERROR, DestinationTextFile);
    
    while (fgets(BUFFER, sizeof(BUFFER), FSource) != 0) {
        BufLen = strlen(BUFFER);
        for (int i = 0; i < BufLen; i++) BUFFER[i] -= EncryptionKey;
        fputs(BUFFER, FDestination);
    }
    fclose(FSource); fclose(FDestination);

    if (SourceTextFileDeletion) {
        strcpy(DeleteSourceTxtFile, "del ");
        strcat(DeleteSourceTxtFile, SourceTextFile);
        system(DeleteSourceTxtFile);
    } else NULL;
}

/* Abbreviation of "Decrypt Text File" is one of the CORE FEATURES here in this application,
and the return type function is `void()`, and requires the program to accept:
`>>>` FOUR (4) arguments, accordingly as explained below.

`> const char *DestinationTextFile`: A destination text file that needs to be decrypted.
`> bool ReadDecryptedFile`: Mode for reading the whole contents of the decrypted file.
`> int DecryptionKey`: A MUST required decryption key in order the text file to be decrypted. The code is spesific, and MUST be set in the program code before runtime, or included in the `**argv` parameter at command line before runtime. The encryption key HAS TO BE THE SAME for the decryption key, because one different in a single number will resulted in a non-correct encryption/decryption method.
`> char ReadDecryptedKeyString[BUFSIZE16]`: Use to search and find a certain key of strings in the decrypted text file, and this argumen have a spesific format and delimiters, and this argument can be used to find more than one key strings, but in the same time can be only one text file at a time, and that's the file you chose to decrypted when assigning it to this argument. This argument has `65,536` or `2^16` buffer size, meaning you can input a total of `65,536` characters inside as a string. 

`[Format: 2nd argument] <TRUE> || <FALSE>`
`[Format: 4th argument] <TEXTFILE.txt> > <STRINGKEYLIST>`
*/
void DecryptTxtFile(const char* DestinationTextFile, bool ReadDecryptedFile, int DecryptionKey, char ReadDecryptedKeyString[BUFSIZE16]) {
    FILE *FDestination, *FTempDestination;
    int BufLen, Ptr = 0, KeyTracker = 0, LineTracker = 0, FTDPos = 0;
    char C, BUFFER[BUFSIZE16], DeleteTempDestinationTxtFile[128], TxtFileName[128];
    char *SourceTextFileName, *SourceKeyStringValue, *SelectedKeyString;
    char *SourceKeyStringValues[BUFSIZE16], FTDestination[BUFSIZE10][BUFSIZE10];

    FDestination = fopen(DestinationTextFile, "r");
    if (FDestination == NULL) ErrorHandling(DESTINATIONFILENULLERROR, DestinationTextFile);
    if (ReadDecryptedFile) {
        while (fgets(BUFFER, sizeof(BUFFER), FDestination) != 0) {
            BufLen = strlen(BUFFER);
            for (int i = 0; i < BufLen; i++) BUFFER[i] += DecryptionKey;
            fputs(BUFFER, stdout);
        }
    } fclose(FDestination);

    if (strcmp(ReadDecryptedKeyString, "None") == 0) NULL;
    else {
        FDestination     = fopen(DestinationTextFile, "r");
        FTempDestination = fopen("TempDestination.txt", "w");

        while (fgets(BUFFER, sizeof(BUFFER), FDestination) != 0) {
            BufLen = strlen(BUFFER);
            for (int i = 0; i < BufLen; i++) BUFFER[i] += DecryptionKey;
            fputs(BUFFER, FTempDestination);
        } fclose(FDestination); fclose(FTempDestination);

        strcpy(TxtFileName, ReadDecryptedKeyString);
        strtok_r(TxtFileName, ">", &SelectedKeyString);
        SelectedKeyString = TrimWhiteSpaces(SelectedKeyString);
        SourceKeyStringValue = strtok(SelectedKeyString, ",");
        KeyTracker++;

        while (SourceKeyStringValue != NULL) {
            SourceKeyStringValues[Ptr] = SourceKeyStringValue;
            SourceKeyStringValues[Ptr] = TrimWhiteSpaces(SourceKeyStringValues[Ptr]);
            SourceKeyStringValue = strtok(NULL, ",");
            Ptr++; KeyTracker++;
        } SourceTextFileName = TrimWhiteSpaces(TxtFileName);
        
        if (strcmp(SourceTextFileName, DestinationTextFile) == 0) {
            if ((TxtFileName != NULL) && (SelectedKeyString != NULL)) {
                if ((strchr(TxtFileName, ':') == NULL) && (strchr(SelectedKeyString, ':') == NULL)) {
                    int FTDIndex = 0, SKSVIndex = 0;

                    FDestination = fopen("TempDestination.txt", "r");
                    for (C = getc(FDestination); C != EOF; C = getc(FDestination))
                        if (C == '\n') LineTracker++;
                    fclose(FDestination);

                    FDestination = fopen("TempDestination.txt", "r");
                    while(fgets(FTDestination[FTDPos], BUFSIZE10, FDestination) != NULL) {
                        if (FTDPos < LineTracker)
                            FTDestination[FTDPos][strlen(FTDestination[FTDPos]) - 1] = '\0';
                        FTDPos++;
                    } fclose(FDestination);

                    while (FTDIndex <= LineTracker) {
                        while (SKSVIndex <= KeyTracker - 2) {
                            if (strstr(FTDestination[FTDIndex], SourceKeyStringValues[SKSVIndex]) != NULL) {
                                printf("%s\n", FTDestination[FTDIndex]); break;
                            } else if (strstr(FTDestination[FTDIndex], SourceKeyStringValues[SKSVIndex]) == NULL)
                                SKSVIndex++;
                        } FTDIndex++; SKSVIndex = 0;
                    }
                    strcpy(DeleteTempDestinationTxtFile, "del ");
                    strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
                    system(DeleteTempDestinationTxtFile);
                }
            }
        } else {
            strcpy(DeleteTempDestinationTxtFile, "del ");
            strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
            system(DeleteTempDestinationTxtFile);
        }
    }
}

/* STARTING THE DECLARATIONS: RANDOM NUMBER GENERATOR */
/* Initialize functions and classes (if needed) */

int RandomNumberGenerator(int _Lower, int _Upper) {
    int _Num = (rand() % ((_Upper - _Lower) + 1)) + _Lower;
    return _Num;
}

/* DRIVER MAIN PROGRAM */
/* NOTE: MUST USE FILE HANDLING IN ORDER TO BE WORKING */

/*
Requirements:
    1. File Handling                    (save-load file handling)           ???
    2. Windows Header File              ('windows.h')                       ???
    3. Time Conversion                  (real-time conversion/tracking)     ???
    4. Array and String Manipulations   ('string.h' 'wchar.h' 'wctype.h')   ???
    5. Functions and Classes            (if needed, mostly private)         ???
    6. Mathematical Visual Graph        (still looking for the library)     ???
    7. Windows GUI for Several Usages   (if needed, complicated)            ???
*/

// WinMain only now.
// [SUCCESS] Testing 4 different Windows Notifications.         ===
//           Few warnings on incompatibilities for pointers.    ???

const int EncryptionKey = 776853;
int main(int argc, char **argv) {
    /* List of notifications, 4 on present */
    // INFO_OK_NOTIFICATION("Info", "This is a Info Test Message.");
    // WARNING_CANCELTRYCONTINUE_NOTIFICATION("Warning", "This is a Warning Test Message.");
    // QUESTION_YESNOCANCEL_NOTIFICATION("Question", "This is a Question Test Message.");
    // ERROR_OKCANCEL_NOTIFICATION("Error", "This is a Error Test Message.");

    puts("Hello, World!\n");
    
    /* Need more works to be done, 'source.txt' may be a problem */;
    EncryptTxtFile("Source.txt", "Destination.txt", EncryptionKey, false);
    DecryptTxtFile("Destination.txt", false, EncryptionKey, "Destination.txt > E-mail, Password, Encryption Key");
    return 0;
}

void MainMenu(void) {
    // TODO: Build a main menu interface.
}

void HelpMenu(void) {
    // TODO: Build a help menu interface.
}