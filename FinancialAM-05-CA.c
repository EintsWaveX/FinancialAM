#include <assert.h>             // Assertion for truth testing
#include <ctype.h>              // Characters typing methods
#include <errno.h>              // Error handling
#include <fenv.h>               // File environment handling
#include <float.h>              // Float conversion (more spesific)
#include <limits.h>             // Limitations per data types
#include <math.h>               // Mathematical functions
#include <stdbool.h>            // Standard boolean values handling
#include <stddef.h>             // Standard definitions for certain types
#include <stdint.h>             // Standard integers handling (more spesific)
#include <stdio.h>              // Standard stream handling
#include <stdlib.h>             // Standard library (more spesific)
#include <string.h>             // String manipulation and handling
#include <time.h>               // Time conversion
#include <uchar.h>              // Character conversion (U type conversion)
#include <unistd.h>             // Giving POSIX syntaxes operating system API
#include <wchar.h>              // Wide character conversion (W type conversion)
#include <wctype.h>             // Wide character typing method (String type conversion)

// #include <gtk-4.0/gtk/gtk.h>    // GTK-4.0+ Application Implementation
#include <conio.h>              // Windows handling compatibility
// #include <raylib.h>             // Raylib library to display graphs and more
// #include <SDL2/SDL.h>           // SDL2 library to support more with Raylib
#include <windows.h>            // Windows header file (apps and notifications)

/*
DEFINE::BUFFERSIZE
Usage:  Used for setting a certain spesific buffer for
        spesific variables that might have to work with
        more than just a basic variables (pointers,
        structs, and more).
*/
#define BUFSIZE10   1024        // 2^10 buffer size (min. defined)
#define BUFSIZE11   2048        // 2^11 buffer size
#define BUFSIZE12   4096        // 2^12 buffer size
#define BUFSIZE13   8192        // 2^13 buffer size
#define BUFSIZE14   16384       // 2^14 buffer size
#define BUFSIZE15   32768       // 2^15 buffer size
#define BUFSIZE16   65536       // 2^16 buffer size (max. defined)

/*
DEFINE::APPLANGUAGE
Usage:  Determining the whole application language that
        mostly the user have to interact with. Given two
        languages registered on the system, that is ENG
        for (English) and IND for (Indonesian).
*/
#define ENG "English"
#define IND "Bahasa Indonesia"

/*
DEFINE::ARROWKEYWORD
Usage:  For more safe-choice input session, so the user
        can't make any rousy inputs that can interrupt
        the whole core of the app functionality by some
        unexpected errors or bugs.
*/
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_RIGHT   77
#define KEY_LEFT    75
#define KEY_ENTER   '\r'

/*
DEFINE::ANSICOLORFONTMODE
Usage:  Creating a spesific colored font to highlight the
        ARROWKEYWORD defining session for helping the user
        to know spesifically the choice they're on while
        in the restricted input mode.
*/
#define ANSI_COLOR_RESET           "\x1b[0;0m"
#define ANSI_COLOR_DARKGRAY        "\x1b[0;30m"
#define ANSI_COLOR_RED             "\x1b[0;31m"
#define ANSI_COLOR_GREEN           "\x1b[0;32m"
#define ANSI_COLOR_YELLOW          "\x1b[0;33m"
#define ANSI_COLOR_BLUE            "\x1b[0;34m"
#define ANSI_COLOR_MAGENTA         "\x1b[0;35m"
#define ANSI_COLOR_CYAN            "\x1b[0;36m"
#define ANSI_COLOR_WHITE           "\x1b[0;37m"
#define ANSI_COLOR_LIGHTRESET      "\x1b[1;0m"
#define ANSI_COLOR_LIGHTGRAY       "\x1b[1;30m"
#define ANSI_COLOR_LIGHTRED        "\x1b[1;31m"
#define ANSI_COLOR_LIGHTGREEN      "\x1b[1;32m"
#define ANSI_COLOR_LIGHTYELLOW     "\x1b[1;33m"
#define ANSI_COLOR_LIGHTBLUE       "\x1b[1;34m"
#define ANSI_COLOR_LIGHTMAGENTA    "\x1b[1;35m"
#define ANSI_COLOR_LIGHTCYAN       "\x1b[1;36m"
#define ANSI_COLOR_LIGHTWHITE      "\x1b[1;37m"
#define ANSI_STYLE_BOLD            "\x0b[1m"
#define ANSI_STYLE_FAINT           "\x0b[2m"
#define ANSI_STYLE_ITALIC          "\x0b[3m"
#define ANSI_STYLE_UNDERLINE       "\x0b[4m"
#define ANSI_STYLE_BLINK           "\x0b[5m"
#define ANSI_STYLE_NEGATIVE        "\x0b[7m"
#define ANSI_STYLE_CROSSED         "\x0b[9m"

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

bool TruthConfirmation;
const char* UserApplicationLanguage;
const char* SOURCEFILENULLERROR = "SourceFileNotExists";
const char* DESTINATIONFILENULLERROR = "DestinationFileNotExists";

const char* ArrowKeyChoiceDialogModes[] = {
    "Trial Mode", "Truth Confirmation",
    "Language Mode", "Account Register Mode", "Account Login Mode",
    "Main Menu", "Help Menu", "About Menu", "Recovery Menu", "Settings Menu"
};
char* MessagesShown_ArrowKeyChoiceDialog[BUFSIZE10] = {};

void ErrorHandling(const char* ErrorType, const char* ErrorSource) {
    if (strcmp(ErrorType, SOURCEFILENULLERROR) == 0)
        printf("Unable to open the source file named '%s'!\n           > Make sure you have the file names '%s' ready to be opened,\n      and not some empty folder or none specified beforehand.\n\nErrorCode: %s", ErrorSource, ErrorSource, ErrorType);
    if (strcmp(ErrorType, DESTINATIONFILENULLERROR) == 0)
        printf("Unable to create the destination file named '%s'!\n    > This maybe an error that occured if there's an error for having\n      permission to make and write to a file, error in naming the file,\n      and many more. Try to troubleshoot for the errors and try again!\n\nErrorCode: %s", ErrorSource, ErrorType);
}

/* PROTOTYPE FUNCTIONS DEFINITION */
// Important Starting Features (CORE FEATURES)
// Core features available: 5

void LanguageMenu(void);
void AccountRegistrationMenu(void);
void AccountLoginMenu(void);
void AccountRecoveryMenu(void);
void MainMenu(void);
void HelpMenu(void);

void EncryptTxtFile(const char*, const char*, int, bool);
void DecryptTxtFile(const char*, bool, int, char ReadDecryptedKeyString[BUFSIZE16]);
void StartApplication(void);
int  ArrowKeyChoiceDialog(const char*, char* MessagesShown[]);
int  RandInt(int, int);
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
    int MessageBoxID = MessageBox( \
        NULL, \
        (LPCWSTR) Message, \
        (LPCWSTR) Title, MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON1);
    
    switch (MessageBoxID) {
        case IDOK: return; break;
        default: return; break;
    }
    return MessageBoxID;
}

int QUESTION_YESNOCANCEL_NOTIFICATION(const char* Title, const char* Message) {
    int MessageBoxID = MessageBox( \
        NULL, \
        (LPCWSTR) Message, \
        (LPCWSTR) Title, MB_ICONQUESTION | MB_YESNOCANCEL | MB_DEFBUTTON2);

    switch (MessageBoxID) {
    case IDYES: break;
    case IDNO: break;
    case IDCANCEL: break;
    }

    return MessageBoxID;
}

int WARNING_CANCELTRYCONTINUE_NOTIFICATION(const char* Title, const char* Message) {
    int MessageBoxID = MessageBox( \
        NULL, \
        (LPCWSTR) Message, \
        (LPCWSTR) Title, MB_ICONEXCLAMATION | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);

    switch (MessageBoxID) {
    case IDCANCEL: break;
    case IDTRYAGAIN: break;
    case IDCONTINUE: break;
    }

    return MessageBoxID;
}

int ERROR_OKCANCEL_NOTIFICATION(const char* Title, const char* Message) {
    int MessageBoxID = MessageBox( \
        NULL, \
        (LPCWSTR) Message, \
        (LPCWSTR) Title, MB_ICONERROR | MB_OKCANCEL | MB_DEFBUTTON1);

    switch (MessageBoxID) {
    case IDOK: break;
    case IDCANCEL: break;
    }

    return MessageBoxID;
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

int ArrowKeyChoiceDialog(const char* AppModeMenu, char* MessagesShown[]) {
    if (strcmp(AppModeMenu, ArrowKeyChoiceDialogModes[0]) == 0) {
        // int Selected = 0;
        // int AvailableOptions = 3;
        // bool Selecting = true, Updated = false, FirstRun = true;
        // char AKDC;

        // while (Selecting) {
        //     if (!FirstRun) {
        //         if ((Selected + 1) == 1) {
        //             puts("Available Options:\n" ANSI_COLOR_BLUE"  1. Option 1\n"ANSI_COLOR_RESET  "  2. Option 2\n  3. Option 3\n");
        //             printf("Which one is your preferable input: ");
        //         } else if ((Selected + 1) == 2) {
        //             puts("Available Options:\n  1. Option 1\n" ANSI_COLOR_BLUE"  2. Option 2\n" ANSI_COLOR_RESET"  3. Option 3\n");
        //             printf("Which one is your preferable input: ");
        //         } else if ((Selected + 1) == 3) {
        //             puts("Available Options:\n  1. Option 1\n  2. Option 2\n" ANSI_COLOR_BLUE"  3. Option 3\n"ANSI_COLOR_RESET);
        //             printf("Which one is your preferable input: ");
        //         }
        //     } else {
        //         FirstRun = false;
        //         printf(ANSI_COLOR_GREEN"INFO: Option %d is selected by the user.\n"ANSI_COLOR_RESET, (Selected + 1));
        //         puts("Available Options:\n" ANSI_COLOR_BLUE"  1. Option 1\n"ANSI_COLOR_RESET  "  2. Option 2\n  3. Option 3\n");
        //         printf("Which one is your preferable input: ");
        //     }

        //     switch (AKDC = _getch()) {
        //         case KEY_LEFT:
        //             if (Selected > 0 && Selected < AvailableOptions) {
        //                 --Selected; Updated = true;
        //             } else if (Selected <= 0) {
        //                 Selected = (AvailableOptions - 1); Updated = true;
        //             } break;
        //         case KEY_RIGHT:
        //             if (Selected >= 0 && Selected < AvailableOptions - 1) {
        //                 ++Selected; Updated = true;
        //             } else if (Selected >= AvailableOptions - 1) {
        //                 Selected = 0; Updated = true;
        //             } break;
        //         case KEY_ENTER:
        //             Selecting = false; Updated = true;
        //             break;
                    
        //         case 49: Selected = 0; Updated = true; break;
        //         case 50: Selected = 1; Updated = true; break;
        //         case 51: Selected = 2; Updated = true; break;
        //         default: break;
        //     } ClearScreen();

        //     if (Updated) {
        //         printf(ANSI_COLOR_GREEN"INFO: Option %d is selected by the user.\n"ANSI_COLOR_RESET, (Selected + 1));
        //         Updated = false;
        //     } else {
        //         printf(ANSI_COLOR_YELLOW"INFO: Option %d is STILL being selected by the user.\n"ANSI_COLOR_RESET, (Selected + 1));
        //     }
        // } printf(ANSI_COLOR_WHITE"INFO: Final arrow input selection: Option %d.\n"ANSI_COLOR_RESET, (Selected + 1));
    
    } else if (strcmp(AppModeMenu, ArrowKeyChoiceDialogModes[1]) == 0) {
        int Selected = 0;
        int AvailableOptions = 2;
        bool Selecting = true, Updated = false, FirstRun = true;
        char AKDC;

        while (Selecting) {
            if (!FirstRun) {
                if ((Selected + 1) == 1) {
                    for (int i = 0; i < BUFSIZE10; i++) {
                        puts(MessagesShown_ArrowKeyChoiceDialog[i]);
                    } puts("\t\t\t\t\t         " ANSI_COLOR_LIGHTGREEN"[Yes, I confirm.] <"ANSI_COLOR_RESET "> [No, I cancel.]");
                } else if ((Selected + 1) == 2) {
                    for (int i = 0; i < BUFSIZE10; i++) {
                        puts(MessagesShown_ArrowKeyChoiceDialog[i]);
                    } puts("\t\t\t\t\t         [Yes, I confirm.] <" ANSI_COLOR_LIGHTRED"> [No, I cancel.]"ANSI_COLOR_RESET);
                }
            } else {
                FirstRun = false;
                puts("\t\t\t\t\t         " ANSI_COLOR_LIGHTGREEN"[Yes, I confirm.] <"ANSI_COLOR_RESET "> [No, I cancel.]");
            }

            switch (AKDC = _getch()) {
                case KEY_RIGHT:
                    if (Selected > 0 && Selected < AvailableOptions) {
                        --Selected; Updated = true;
                    } else if (Selected <= 0) {
                        Selected = (AvailableOptions - 1); Updated = true;
                    } break;
                case KEY_LEFT:
                    if (Selected >= 0 && Selected < AvailableOptions - 1) {
                        ++Selected; Updated = true;
                    } else if (Selected >= AvailableOptions - 1) {
                        Selected = 0; Updated = true;
                    } break;
                case KEY_ENTER:
                    Selecting = false; Updated = true;
                    break;
                    
                case 49: Selected = 0; Updated = true; break;
                case 50: Selected = 1; Updated = true; break;
                default: break;
            } (Selecting) ? ClearScreen() : NULL;

            if (Updated) {
                Updated = false;
            } else {
                NULL;
            }
        } if (Selected == 0) { return true;  }
          else               { return false; }

    } else if (strcmp(AppModeMenu, ArrowKeyChoiceDialogModes[2]) == 0) {
        int Selected = 0;
        int AvailableOptions = 2;
        bool Selecting = true, Updated = false, FirstRun = true;
        char AKDC;

        while (Selecting) {
            if (!FirstRun) {
                if ((Selected + 1) == 1) {
                    puts("\t\t\t\t\t      Please select your prefered language mode:\n\t\t\t\t\t\t Silakan memilih mode bahasa berikut:\n\n\t\t\t\t\t\t    " ANSI_COLOR_BLUE"> English"ANSI_COLOR_RESET "\t\tIndonesian\n\t\t\t\t\t             " ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET);
                } else if ((Selected + 1) == 2) {
                    puts("\t\t\t\t\t      Please select your prefered language mode:\n\t\t\t\t\t\t Silakan memilih mode bahasa berikut:\n\n\t\t\t\t\t\t      English\t      " ANSI_COLOR_BLUE"> Indonesian\n\t\t\t\t\t             "ANSI_COLOR_RESET ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET);
                }
            } else {
                FirstRun = false;
                puts("\t\t\t\t\t      Please select your prefered language mode:\n\t\t\t\t\t\t Silakan memilih mode bahasa berikut:\n\n\t\t\t\t\t\t    " ANSI_COLOR_BLUE"> English"ANSI_COLOR_RESET "\t\tIndonesian\n\t\t\t\t\t             " ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET);
            }

            switch (AKDC = _getch()) {
                case KEY_RIGHT:
                    if (Selected > 0 && Selected < AvailableOptions) {
                        --Selected; Updated = true;
                    } else if (Selected <= 0) {
                        Selected = (AvailableOptions - 1); Updated = true;
                    } break;
                case KEY_LEFT:
                    if (Selected >= 0 && Selected < AvailableOptions - 1) {
                        ++Selected; Updated = true;
                    } else if (Selected >= AvailableOptions - 1) {
                        Selected = 0; Updated = true;
                    } break;
                case KEY_ENTER:
                    Selecting = false; Updated = true;
                    break;
                    
                case 49: Selected = 0; Updated = true; break;
                case 50: Selected = 1; Updated = true; break;
                default: break;
            } (Selecting) ? ClearScreen() : NULL;

            if (Updated) {
                Updated = false;
            } else {
                NULL;
            }
        } if (Selected == 0) {
            puts(ANSI_COLOR_WHITE"\n\t\t\t\t Are you sure that's your prefered language for the whole app usages?\n\t\t\t\t Language mode choice is: English.\n"ANSI_COLOR_RESET);
        } else {
            puts(ANSI_COLOR_WHITE"\n\t\t\t\t  Apakah Anda yakin penggunaan bahasa ini pada seluruh isi aplikasi?\n\t\t\t\t  Mode bahasa pilihan adalah: Bahasa Indonesia.\n"ANSI_COLOR_RESET);
        }
        MessagesShown_ArrowKeyChoiceDialog[0] = \
            (Selected == 0) ? \
            "\t\t\t\t\t      Please select your prefered language mode:\n\t\t\t\t\t\t Silakan memilih mode bahasa berikut:\n\n\t\t\t\t\t\t    " ANSI_COLOR_BLUE"> English"ANSI_COLOR_RESET "\t\tIndonesian\n\t\t\t\t\t             " ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET : \
            "\t\t\t\t\t      Please select your prefered language mode:\n\t\t\t\t\t\t Silakan memilih mode bahasa berikut:\n\n\t\t\t\t\t\t      English\t      " ANSI_COLOR_BLUE"> Indonesian\n\t\t\t\t\t             "ANSI_COLOR_RESET ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET;
        MessagesShown_ArrowKeyChoiceDialog[1] = \
            (Selected == 0) ? \
            ANSI_COLOR_WHITE"\n\t\t\t\t Are you sure that's your prefered language for the whole app usages?\n\t\t\t\t Language mode choice is: English.\n"ANSI_COLOR_RESET : \
            ANSI_COLOR_WHITE"\n\t\t\t\t  Apakah Anda yakin penggunaan bahasa ini pada seluruh isi aplikasi?\n\t\t\t\t  Mode bahasa pilihan adalah: Bahasa Indonesia.\n"ANSI_COLOR_RESET;

        TruthConfirmation = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog);
        if (!TruthConfirmation) { ClearScreen(); LanguageMenu(); }
        else {
            puts((Selected == 0) ? \
                "\n\t\t\t\t\t   " ANSI_COLOR_MAGENTA"Please kindly wait while we setting up things..."ANSI_COLOR_RESET : \
                "\n\t\t\t\t     " ANSI_COLOR_MAGENTA"Mohon bersabar untuk menunggu selagi kami mempersiapkannya..."ANSI_COLOR_RESET);
            
            sleep(RandInt(1, 3));
            puts((Selected == 0) ? \
                ANSI_COLOR_MAGENTA"\t\t\t\t\t   User Application Language: #ENG [English]"ANSI_COLOR_RESET : \
                ANSI_COLOR_MAGENTA"\t\t\t\t     Bahasa Aplikasi Pengguna: #IND [Bahasa Indonesia]"ANSI_COLOR_RESET);
            
            getchar();
            AccountRegistrationMenu();
        }
    }
}

/* STARTING THE DECLARATIONS: RANDOM NUMBER GENERATOR */
/* Initialize functions and classes (if needed) */

int RandInt(int Lower, int Upper) {
    return (int)(rand() % ((Upper - Lower) + 1)) + Lower;
}

/*
void StartApplication(void) {
    system("gcc `pkg-config --cflags sdl2 gtk4` EL4705Fin-A-ALPRO-Title5.c -o EL4705Fin-A-ALPRO-Title5 `pkg-config --libs sdl2 gtk4`")
}
*/

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
void MainMenu(void) {
    // TODO: Build a main menu interface.
}

void HelpMenu(void) {
    // TODO: Build a help menu interface.
}

int main(int argc, char **argv) {
    /* List of notifications, 4 on present */
    // INFO_OK_NOTIFICATION("Info Message: Update Changes in The Category 'Investments'.", "You have updated the limit of the money that you'd to spent on investments from Rp2.000.000.000,00 into Rp5.000.000.000,00. Make sure that you've enabled the limit on your debit/credit card transactions before doing some more investments in some company stocks, personal branding shares, and more.\n\nWe only manage your well-being financial managing personally in this app, and may not into the other main parties with your companies and such, so no obligation from us to take care of your \"punishments\" if there's ever a wrong doing thing happens!");
    // WARNING_CANCELTRYCONTINUE_NOTIFICATION("Warning Message: D-3 Reminder for Paying Full of 'Debts'", "You have received a warning message about getting your hand to pay the full of your decieve debts far-far ago on November 7, 2023; and now ONLY THREE DAYS LEFT before the debt collector might be coming to you with your personal card bank manager to considering things over you.\nSo please, DO NOT FORGET THE DATE FOR FULL PAYMENTS FOR:\n\n\tRp290.172.984,19;\n\twith a total interest of: 6.58%.\n\nNOTE: Ignore this warning message if you had already pay the full debts, or if there's maybe a caught up error when finishing up your deletion over this warning message before!");
    // QUESTION_YESNOCANCEL_NOTIFICATION("Question Message: Confirmation on Deletion Over a 'Transactions'.", "We've noticed that you want to delete all currently recorded transactions on:\n\tDate (by month): October 2022,\n\tTotal Recorded Transactions: 87 Transactions.\n\nAre you sure to continue and delete all transactions that happening in October 2022, from the October 1st until 31st October?\n\nNOTE: Anything after the deletions will be PERMANENTLY deleted and NEVER BE ABLE TO BE RECOVERED by any means and such. Please think twice, that you may have to know all the recorded transactions over the past month so you can do the budget monitoring better than before ever was!");
    // ERROR_OKCANCEL_NOTIFICATION("Error Message: Default 'Category' Changings Error.", "You may have received this error pop-up message because you've been trying to do some changes on a system's default categories made in this app's core already. Several times before you only get knocked out from the menu, and because now you've been trying so badly to do it so even though you already knew that ALL default variables CANNOT EVER BE CHANGED WHATSOEVER!\n\nPlease keep in mind to not spamming this error messages, because from the first you got this messages within three days will always pop-up this. If you insist, then unfortunately you have to be banned from this menu for a temporary time!");

    ClearScreen();
    puts("Hello, World!");
    
    // if (access("RegisteredAccountData.txt", F_OK) != 0) { LanguageMenu(); }
    // else { AccountLoginMenu(); }
    
    /* Need more works to be done, 'source.txt' may be a problem */;
    // EncryptTxtFile("TemporaryDecProfile.txt", "TemporaryEncProfile.txt", EncryptionKey, false);
    // DecryptTxtFile("TemporaryEncProfile.txt", false, EncryptionKey, "None");
    // // ArrowKeyChoiceDialog("Main Menu");
    return 0;
}

void LanguageMenu(void) {
    // TODO: Build a language menu interface.
    ArrowKeyChoiceDialog("Language Mode", MessagesShown_ArrowKeyChoiceDialog);
}

void AccountRegistrationMenu(void) {
    // TODO: Build a registration menu interface.
}

void AccountLoginMenu(void) {
    // TODO: Build a login menu interface.
}

void AccountRecoveryMenu(void) {
    // TODO: Build a recovery menu interface.
}

void F1_MoneytoryTransactionsRegister(void) {
    
}