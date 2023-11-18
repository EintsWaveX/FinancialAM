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
#define BUFSIZE07   128         // 2^7  buffer size (min. defined)
#define BUFSIZE08   256         // 2^8  buffer size
#define BUFSIZE09   512         // 2^9  buffer size
#define BUFSIZE10   1024        // 2^10 buffer size
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
size_t GlobalRegisteredAccounts = 0;
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
    if (strcmp(ErrorType, SOURCEFILENULLERROR) == 0) {
        printf("Unable to open the source file named '%s'!\n           > Make sure you have the file names '%s' ready to be opened,\n      and not some empty folder or none specified beforehand.\n\nErrorCode: %s", ErrorSource, ErrorSource, ErrorType);
        getchar();
    } if (strcmp(ErrorType, DESTINATIONFILENULLERROR) == 0) {
        printf("Unable to create the destination file named '%s'!\n    > This maybe an error that occured if there's an error for having\n      permission to make and write to a file, error in naming the file,\n      and many more. Try to troubleshoot for the errors and try again!\n\nErrorCode: %s", ErrorSource, ErrorType);
        getchar();
    }
}

/* Program's CORE Functions Separator */
// NOTE: All structures and global variables below are initialized
//       ONLY for the CORE function, naming as: AccountRegistrationMenu.

struct AccountRegistrationMenuInputs {
    char FirstName[BUFSIZE07], LastName[BUFSIZE07], Email[BUFSIZE07], Username[BUFSIZE07], Password[BUFSIZE07], CSPFinancialAMEncryptionKey[BUFSIZE07];
    char DateOfBirth[BUFSIZE07], AgeOnPresent[BUFSIZE07], PhoneNumber[BUFSIZE07], Sex[BUFSIZE07], CareerProfiling[BUFSIZE07], AboutMe[BUFSIZE10];
    char AttendingCollege[BUFSIZE07], CompanyWorking[BUFSIZE07], DegreeIn[BUFSIZE07];
    char HiddenPasswordShown[BUFSIZE07];
} ARMInputs[BUFSIZE10];
bool FN = false, LN = false, E = false, U = false, P = false;
bool B = false, A = false, PN = false, S = false, CP = false, PD = false;
bool AC = false, CW = false, DI = false;
int ARMSelected = 0;

struct AccountLoginMenuInputs {
    char Email[BUFSIZE07], PhoneNumber[BUFSIZE07], Username[BUFSIZE07], Password[BUFSIZE07];
    char HiddenPasswordShown[BUFSIZE07];
} ALMInputs[BUFSIZE10];
bool LE = false, LPN = false, LU = false, LP = false;
int ALMSelected = 0;

struct AccountRecoveryMenuInputs {
    char Email[BUFSIZE07], PhoneNumber[0], Username[BUFSIZE07], Password[BUFSIZE07];
    char HiddenPasswordShown[BUFSIZE07];
} ACMInputs[BUFSIZE10];

struct MoneytoryTransactionsRegister {
    char *BankCharge[BUFSIZE10], *BillPayment[BUFSIZE10];
    char *CardRefund[BUFSIZE10], *CardTopUp[BUFSIZE10], *CashWithdrawal[BUFSIZE10], *CurrencyExchange[BUFSIZE10];
    char *FeePayment[BUFSIZE10], *IncomingCash[BUFSIZE10], *IncomingTransfer[BUFSIZE10], *Interest[BUFSIZE10];
    char *Loan[BUFSIZE10], *Loans[BUFSIZE10];
    char *OutgoingTransfer[BUFSIZE10];
    char *PaymentWithCard[BUFSIZE10], *PrepaidTopUp[BUFSIZE10], *PrincipalPlacement[BUFSIZE10], PrincipalRepayment[BUFSIZE10];
    char *QRPayment[BUFSIZE10], *QRPaymentRefund[BUFSIZE10];
    char *Reversal[BUFSIZE10];
    char *SalaryPayroll[BUFSIZE10], *SavingsWithdrawal[BUFSIZE10];
    char *TaxOnInterest[BUFSIZE10], *TopUpSavingsBalances[BUFSIZE10], *WalletCashback[BUFSIZE10];

    char TransactionDate[BUFSIZE07], IncomeOrExpenses[BUFSIZE07], TotalSpentMoney[BUFSIZE07];
    char FinancialUsesCategory[BUFSIZE07], MonthlyTotalBalance[BUFSIZE07], TransactionDescription[BUFSIZE07];
    char LocalTimeTransactionMade[BUFSIZE07];
} MTRInputs[BUFSIZE10];

struct MoneytoryGroupingPerCategory {
    char *AccountReceiveable[BUFSIZE10], *AcdditionalIncome[BUFSIZE10], *Allowance[BUFSIZE10];
    char *ElectricityWaterGas[BUFSIZE10], *HouseAndAppartmentRent[BUFSIZE10], *Household[BUFSIZE10], *Insurance[BUFSIZE10], *MobileAndData[BUFSIZE10], *HandheldElectricDevice[BUFSIZE10], *TVAndInternet[BUFSIZE10];
    char *Bonus[BUFSIZE10], *BusinessProfit[BUFSIZE10];
    char *ClassesAndWorkshops[BUFSIZE10], SchoolSupplies[BUFSIZE10], TuitionFee[BUFSIZE10];
    char *ChildrenFamilyNeeds[BUFSIZE10], *ParentFamilyNeeds[BUFSIZE10];
    char *DailyMeal[BUFSIZE10], *SnacksAndDrinks[BUFSIZE10];
    char *Gifting[BUFSIZE10], *Charity[BUFSIZE10];
    char *Groceries[BUFSIZE10];
    char *DoctorAndHospital[BUFSIZE10], *Medicines[BUFSIZE10], PersonalCare[BUFSIZE10];
    char *Books[BUFSIZE10], *DiningOut[BUFSIZE10], *Games[BUFSIZE10], *Hobby[BUFSIZE10], *MoviesAndMusic[BUFSIZE10], *Pets[BUFSIZE10];
    char *Incomes[BUFSIZE10], *Incomings[BUFSIZE10], *Interests[BUFSIZE10], *InvestmentsWithdrawal[BUFSIZE10];
    char *LoanDisbursements[BUFSIZE10];
    char *CarInstallments[BUFSIZE10], *CreditCard[BUFSIZE10], *SKYRCash[BUFSIZE10], *HomeMortgage[BUFSIZE10];
    char *Refunds[BUFSIZE10], *Reimbursements[BUFSIZE10];
    char *Salary[BUFSIZE10];
    char *Investments[BUFSIZE10], *Savings[BUFSIZE10];
    char *Fashions[BUFSIZE10], *GadgetAndElectronics[BUFSIZE10], *HomeAppliances[BUFSIZE10];
    char *SportActivities[BUFSIZE10], *SportEquipments[BUFSIZE10];
    char *DailyTransportations[BUFSIZE10], *Gasolines[BUFSIZE10], *ParkingAndTollFee[BUFSIZE10], *VehicleMaintenance[BUFSIZE10];
    char *AttractionsAndTours[BUFSIZE10], *HotelAndVilla[BUFSIZE10], *TransportsOnVacations[BUFSIZE10];
    char *CashWithdrawal[BUFSIZE10], *CostAndTaxes[BUFSIZE10], *SendToBusiness[BUFSIZE10], *SendToPersonal[BUFSIZE10], *TopUpEWallet[BUFSIZE10], *TopUpCards[BUFSIZE10];
    
    char *UncategorizedByUsers[BUFSIZE10];
    char *Others[BUFSIZE10];
} MGPCInputs[BUFSIZE10];

struct BudgetCreationAndMonitoring {
    char *BudgetCreationPerMonth[BUFSIZE10], *BudgetCreationPerYear[BUFSIZE10];
    char *MonthlyFinancialCreationCategory[BUFSIZE10], *YearlyFinancialCreationCategory[BUFSIZE10];
    char *MonthlyLimitBudgetCreation[BUFSIZE10], *YearlyLimitBudgetCreation[BUFSIZE10];
    char *MonthlyBudgetCreationDescription[BUFSIZE10], *YearlyBudgetCreationDescription[BUFSIZE10];
    char *MonthlyBudgetTargeting[BUFSIZE10], *YearlyBudgetTargeting[BUFSIZE10];
    bool AlwaysCheckForReminders;
} BCAMInputs[BUFSIZE10];

struct FilterSearchingData {
    /*
    For now, there's no need to filter by the structures, since all the variables
    are already handled by the core program itself in a function call:
        > void DecryptTxtFile(const char*, bool, int, char ReadDecryptedKeyString[BUFSIZE16]);

    Need some future and furthermore updates on this structure, since basically the
    filtering and searching methods are just implemented already while decrypting the
    text file for more safety over valueable personal data.

    How this feature works, is just really open a text file that needs to be filtered
    or searched by letters or words or categories and more, even when being filtered
    is already unconciously being sorted along the way, and can be searched through
    anywhere, especially when the reading system is line-by-line, and the whole file
    being read without any filtering if the user wants to.
    */
    
    char FileName[BUFSIZE07];
} FSDInputs[BUFSIZE10];
    
struct ReminderAndSetNotifications {
    /*
    For now, there's no need to filter by the structures, since all the variables
    are already handled by the core program itself in a function call:
        > int InfoMessageBox_OK(const char*, const char*);
        > int QuestionMessageBox_YESNOCANCEL(const char*, const char*);
        > int WarningMessageBox_CANCELTRYCONTINUE(const char*, const char*);
        > int ErrorMessageBox_OKCANCEL(const char*, const char*);

    1. The first one is an INFO MESSAGE BOX that appears with the tile of the info
    popup notification window and the messages written in, and it provides only
    a single OK button.
    2. The second one is a QUESTION MESSAGE BOX that appears with the title of the
    question popup notification window and the messages written in, and it provides
    three buttons, respectively naming as YES button, NO button, and CANCEL button.
    3. The third one is a WARNING MESSAGE BOX that appears with the title of the
    warning popup notification window and the messages written in, and it provides
    three buttons, respectively naming as CANCEL button, TRY button, and CONTINUE
    button.
    4. The fourth (last but not least) is a ERROR MESSAGE BOX that appears with the
    title of the error popup notification window and the messages written in, and it
    provides twoo buttons, respectively naming as OK button and CANCEL button.

    Need some future and furthermore updates on this structure, since basically the
    popup notification windows for all of those four describes above are already being
    implemented inside their own functions, with globally and locally accessible
    variables to handle each titles of the windows and the messages in it, based on
    the purpose of why the popup notification appears before the users, since that might
    be telling them for what to do and what to confirms based on what it takes to
    validate the required parameters of each notifications active within.

    How this feature works, is just really a written specific title of each notifications
    and the messages written in, as for example the popup notification about:
        a) Info about default changes and updates,
        b) Confirming the users on trying to changing something that may affects other
           configurations as well,
        c) Giving the users warnings about something they accidentally took a wrong turn
           over the program that might give them bugs and even un-encrypted written textfile
           data, and
        d) Catching all errors that the users made (like changing the core factors of the
           program) and telling the users that they're not allowed to do so, or might get
           banned if they keep ignoring the error messages.
    */

    char PopUpNotificationTitleWindow[BUFSIZE07];
    char PopUpNotificationMessageWindow[BUFSIZE10];
} RASNInputs[BUFSIZE10];

struct DataVisualization {
    /*
    This feature is on development and not even being experimentally implemented yet,
    but the consideration of what could be displayed on a graph for something economically
    and statistically better to give the users more about the informations about their
    demanded search of configuration in displaying over their selected features, like
    a graph over a spesific whole month, a whole day recorded transactions, and more.

    How this works is by reading and filtered over a transaction history from a spesific
    text file, and sorted each by the transactions that had been made on that day or month
    or maybe even a year, and how many budgets or money that had been spent on into those
    transactions, and make a graph (by a line or long upward rectangles).
    */

    char FileName[BUFSIZE07];
    char XAxisTransactions[BUFSIZE07], YAxisMoneyOnSpent[BUFSIZE07];
    char GraphTitle[BUFSIZE07], GraphDescription[BUFSIZE07], GraphDefinitions[BUFSIZE07];
    char OtherAdditionalInformation[BUFSIZE07];
} DVInputs[BUFSIZE10];

/* PROTOTYPE FUNCTIONS DEFINITION */
// Important Starting Features (CORE FEATURES)
// Core features available: 5

void LanguageMenu(void);
void AccountRegistrationMenu(int);
void AccountLoginMenu(int);
void AccountRecoveryMenu(int);
void MainMenu(int);
void HelpMenu(int);

void EncryptTxtFile(const char*, const char*, int, bool);
void DecryptTxtFile(const char*, bool, int, char ReadDecryptedKeyString[BUFSIZE16]);
int  ArrowKeyChoiceDialog(const char*, char* MessagesShown[], size_t, size_t);
int  RandInt(int, int);
int  FindOccurences(const char*, char);
char *TrimWhiteSpaces(char*);
char *StringUppercase(char*);
char *ReadAndPrintLine(const char*, intmax_t);

// Notifications Features (CORE FEATURES)
// Notification features available: 4

int InfoMessageBox_OK(const char*, const char*);
int QuestionMessageBox_YESNOCANCEL(const char*, const char*);
int WarningMessageBox_CANCELTRYCONTINUE(const char*, const char*);
int ErrorMessageBox_OKCANCEL(const char*, const char*);

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
int InfoMessageBox_OK(const char* Title, const char* Message) {
    int MessageBoxID = MessageBox( \
        NULL, \
        (LPCSTR) Message, \
        (LPCSTR) Title, MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON1);
    
    switch (MessageBoxID) {
        case IDOK: break;
        default: break;
    } return MessageBoxID;
}

int QuestionMessageBox_YESNOCANCEL(const char* Title, const char* Message) {
    int MessageBoxID = MessageBox( \
        NULL, \
        (LPCSTR) Message, \
        (LPCSTR) Title, MB_ICONQUESTION | MB_YESNOCANCEL | MB_DEFBUTTON2);

    switch (MessageBoxID) {
        case IDYES: break;
        case IDNO: break;
        case IDCANCEL: break;
    } return MessageBoxID;
}

int WarningMessageBox_CANCELTRYCONTINUE(const char* Title, const char* Message) {
    int MessageBoxID = MessageBox( \
        NULL, \
        (LPCSTR) Message, \
        (LPCSTR) Title, MB_ICONEXCLAMATION | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);

    switch (MessageBoxID) {
        case IDCANCEL: break;
        case IDTRYAGAIN: break;
        case IDCONTINUE: break;
    } return MessageBoxID;
}

int ErrorMessageBox_OKCANCEL(const char* Title, const char* Message) {
    int MessageBoxID = MessageBox( \
        NULL, \
        (LPCSTR) Message, \
        (LPCSTR) Title, MB_ICONERROR | MB_OKCANCEL | MB_DEFBUTTON1);

    switch (MessageBoxID) {
        case IDOK: break;
        case IDCANCEL: break;
    } return MessageBoxID;
}

/* STARTING THE DECLARATIONS: ENCRYPTION AND DECRYPTION DATA */
/* Initialize functions and classes (if needed) */

char *TrimWhiteSpaces(char* SourceString) {
    char *EndString;

    while (isspace((unsigned char) *SourceString)) SourceString++;  // Trim leading space
    if (*SourceString == 0) return SourceString;                    // All spaces?
    EndString = SourceString + strlen(SourceString) - 1;            // Trim trailing space
    while (EndString > SourceString && isspace((unsigned char) *EndString)) EndString--;

    EndString[1] = '\0'; // Write new null terminator character
    return SourceString;
}

char *ReadAndPrintLine(const char* SourceTextFile, intmax_t Line) {
    FILE *FSource = fopen(SourceTextFile, "r");
    char Buffer[BUFSIZE10], *ReturnBuffer = malloc(BUFSIZE10);
    intmax_t Lines = 0;
    do {
        if (++Lines == Line) {
            fgets(Buffer, BUFSIZE10, FSource);
            break;
        }
    } while((fscanf(FSource, "%*[^\n]"), fscanf(FSource, "%*c")) != EOF);
    if (Lines == Line) { strcpy(ReturnBuffer, Buffer); fclose(FSource); return ReturnBuffer; }
    fclose(FSource);
}

char *StringUppercase(char* SourceString) {
    for (int i = 0; SourceString[i] != '\0'; i++) {
        if (SourceString[i] >= 'a' && SourceString[i] <= 'z') { SourceString[i] -= 32; }
    } return SourceString;
}

int FindOccurences(const char* SourceString, char SearchedOccurence) {
    int CountOccurences;
    for (int i = 0; i < strlen(SourceString) - 1; i++) {
        if (SourceString[i] == SearchedOccurence) CountOccurences++;
    } return CountOccurences;
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
        } else {
            strcpy(DeleteTempDestinationTxtFile, "del ");
            strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
            system(DeleteTempDestinationTxtFile);
        }
    }
}

int ArrowKeyChoiceDialog(const char* AppModeMenu, char* MessagesShown[], size_t MessagesIndexBegin, size_t MessagesIndexEnd) {
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
                    for (int i = MessagesIndexBegin; i < MessagesIndexEnd; i++) {
                        puts(MessagesShown_ArrowKeyChoiceDialog[i]);
                    } puts("\t" ANSI_COLOR_LIGHTGREEN"[Yes, I confirm.] <"ANSI_COLOR_RESET "> [No, I cancel.]");
                } else if ((Selected + 1) == 2) {
                    for (int i = MessagesIndexBegin; i < MessagesIndexEnd; i++) {
                        puts(MessagesShown_ArrowKeyChoiceDialog[i]);
                    } puts("\t[Yes, I confirm.] <" ANSI_COLOR_LIGHTRED"> [No, I cancel.]"ANSI_COLOR_RESET);
                }
            } else {
                FirstRun = false;
                puts("\t" ANSI_COLOR_LIGHTGREEN"[Yes, I confirm.] <"ANSI_COLOR_RESET "> [No, I cancel.]");
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
                    puts("\n\n\n\n\tPlease select your prefered language mode:\n\tSilakan memilih mode bahasa berikut:\n\n\t" ANSI_COLOR_BLUE"> English"ANSI_COLOR_RESET "\tIndonesian\n\t" ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET);
                } else if ((Selected + 1) == 2) {
                    puts("\n\n\n\n\tPlease select your prefered language mode:\n\tSilakan memilih mode bahasa berikut:\n\n\tEnglish" ANSI_COLOR_BLUE"\t\t> Indonesian\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET);
                }
            } else {
                FirstRun = false;
                puts("\n\n\n\n\tPlease select your prefered language mode:\n\tSilakan memilih mode bahasa berikut:\n\n\t" ANSI_COLOR_BLUE"> English"ANSI_COLOR_RESET "\tIndonesian\n\t" ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET);
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
            puts(ANSI_COLOR_WHITE"\n\tAre you sure that's your prefered language for the whole app usages?\n\tLanguage mode choice is: English.\n"ANSI_COLOR_RESET);
        } else {
            puts(ANSI_COLOR_WHITE"\n\tApakah Anda yakin penggunaan bahasa ini pada seluruh isi aplikasi?\n\tMode bahasa pilihan adalah: Bahasa Indonesia.\n"ANSI_COLOR_RESET);
        }

        MessagesShown_ArrowKeyChoiceDialog[0] = \
            (Selected == 0) ? \
            "\n\n\n\n\tPlease select your prefered language mode:\n\tSilakan memilih mode bahasa berikut:\n\n\t" ANSI_COLOR_BLUE"> English"ANSI_COLOR_RESET "\tIndonesian\n\t" ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET : \
            "\n\n\n\n\tPlease select your prefered language mode:\n\tSilakan memilih mode bahasa berikut:\n\n\tEnglish" ANSI_COLOR_BLUE"\t\t> Indonesian\n\t" ANSI_COLOR_RESET ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET;
        MessagesShown_ArrowKeyChoiceDialog[1] = \
            (Selected == 0) ? \
            ANSI_COLOR_WHITE"\n\tAre you sure that's your prefered language for the whole app usages?\n\tLanguage mode choice is: English.\n"ANSI_COLOR_RESET : \
            ANSI_COLOR_WHITE"\n\tApakah Anda yakin penggunaan bahasa ini pada seluruh isi aplikasi?\n\tMode bahasa pilihan adalah: Bahasa Indonesia.\n"ANSI_COLOR_RESET;

        TruthConfirmation = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 0, 2);
        if (!TruthConfirmation) { ClearScreen(); LanguageMenu(); }
        else {
            puts((Selected == 0) ? \
                "\n\t" ANSI_COLOR_LIGHTMAGENTA"Please kindly wait while we setting up things..."ANSI_COLOR_RESET : \
                "\n\t" ANSI_COLOR_LIGHTMAGENTA"Mohon bersabar untuk menunggu selagi kami mempersiapkannya..."ANSI_COLOR_RESET);
            
            sleep(RandInt(1, 3));
            puts((Selected == 0) ? \
                ANSI_COLOR_LIGHTMAGENTA"\tUser Application Language: #ENG [English]"ANSI_COLOR_RESET : \
                ANSI_COLOR_LIGHTMAGENTA"\tBahasa Aplikasi Pengguna: #IND [Bahasa Indonesia]"ANSI_COLOR_RESET);
            
            getchar();
            AccountRegistrationMenu(0);
        }
    } return 0;
}

/* STARTING THE DECLARATIONS: RANDOM NUMBER GENERATOR */
/* Initialize functions and classes (if needed) */

int RandInt(int Lower, int Upper) {
    return (int)(rand() % ((Upper - Lower) + 1)) + Lower;
}

/* DRIVER MAIN PROGRAM */
/* NOTE: MUST USE FILE HANDLING IN ORDER TO BE WORKING */

/*
Requirements:
    1. File Handling                    (save-load file handling)           VVV
    2. Windows Header File              ('windows.h')                       VVV
    3. Time Conversion                  (real-time conversion/tracking)     ???
    4. Array and String Manipulations   ('string.h' 'wchar.h' 'wctype.h')   VVV
    5. Functions and Classes            (if needed, mostly private)         ???
    6. Mathematical Visual Graph        (still looking for the library)     ???
    7. Windows GUI for Several Usages   (if needed, complicated)            ???
*/

// WinMain only now.
// [SUCCESS] Testing 4 different Windows Notifications.         ===
//           Few warnings on incompatibilities for pointers.    ???

const int EncryptionKey = 776853;
void MainMenu(int MMSelected) {
    ClearScreen();
    puts("\n\n\n\n\tThis will be the main menu of the program.");
    printf("\t%d\n", GlobalRegisteredAccounts);
    getchar(); exit(0);
}

void HelpMenu(int HMSelected) {
    // TODO: Build a help menu interface.
}

int main(int argc, char **argv) {
    /* List of notifications, 4 on present */
    // InfoMessageBox_OK("Info Message: Update Changes in The Category 'Investments'.", "You have updated the limit of the money that you'd to spent on investments from Rp2.000.000.000,00 into Rp5.000.000.000,00. Make sure that you've enabled the limit on your debit/credit card transactions before doing some more investments in some company stocks, personal branding shares, and more.\n\nWe only manage your well-being financial managing personally in this app, and may not into the other main parties with your companies and such, so no obligation from us to take care of your \"punishments\" if there's ever a wrong doing thing happens!");
    // WarningMessageBox_CANCELTRYCONTINUE("Warning Message: D-3 Reminder for Paying Full of 'Debts'", "You have received a warning message about getting your hand to pay the full of your decieve debts far-far ago on November 7, 2023; and now ONLY THREE DAYS LEFT before the debt collector might be coming to you with your personal card bank manager to considering things over you.\nSo please, DO NOT FORGET THE DATE FOR FULL PAYMENTS FOR:\n\n\tRp290.172.984,19;\n\twith a total interest of: 6.58%.\n\nNOTE: Ignore this warning message if you had already pay the full debts, or if there's maybe a caught up error when finishing up your deletion over this warning message before!");
    // QuestionMessageBox_YESNOCANCEL("Question Message: Confirmation on Deletion Over a 'Transactions'.", "We've noticed that you want to delete all currently recorded transactions on:\n\tDate (by month): October 2022,\n\tTotal Recorded Transactions: 87 Transactions.\n\nAre you sure to continue and delete all transactions that happening in October 2022, from the October 1st until 31st October?\n\nNOTE: Anything after the deletions will be PERMANENTLY deleted and NEVER BE ABLE TO BE RECOVERED by any means and such. Please think twice, that you may have to know all the recorded transactions over the past month so you can do the budget monitoring better than before ever was!");
    // ErrorMessageBox_OKCANCEL("Error Message: Default 'Category' Changings Error.", "You may have received this error pop-up message because you've been trying to do some changes on a system's default categories made in this app's core already. Several times before you only get knocked out from the menu, and because now you've been trying so badly to do it so even though you already knew that ALL default variables CANNOT EVER BE CHANGED WHATSOEVER!\n\nPlease keep in mind to not spamming this error messages, because from the first you got this messages within three days will always pop-up this. If you insist, then unfortunately you have to be banned from this menu for a temporary time!");

    // ClearScreen();
    // puts("Hello, World!");
    
    if (access("RegisteredAccounts.txt", F_OK) != 0) { fflush(stdout); LanguageMenu(); }
    else { fflush(stdout); AccountLoginMenu(0); }
    
    // Just adding a newline padding to the console while pre-testing encryption data file here.
    puts("");
    // EncryptTxtFile("TemporaryDecProfile.txt", "TemporaryEncProfile.txt", EncryptionKey, false);
    DecryptTxtFile("RegisteredAccounts.txt", true, EncryptionKey, "None");
    return 0;
}

void LanguageMenu(void) {
    ArrowKeyChoiceDialog("Language Mode", MessagesShown_ArrowKeyChoiceDialog, 0, 2);
}

void AccountRegistrationMenu(int ARMSelected) {
    ClearScreen();

    time_t Time = time(NULL);
    struct tm ManageTime = *localtime(&Time);

    FILE *FDestination, *FTempDestination;
    int BufLen, Ptr = 0, KeyTracker = 0, LineTracker = 0, FTDPos = 0;
    char C, BUFFER[BUFSIZE16], DeleteTempDestinationTxtFile[128], TxtFileName[128] = "RegisteredAccounts.txt > Accounts";
    char *SourceTextFileName, *SourceKeyStringValue, *SelectedKeyString;
    char *SourceKeyStringValues[BUFSIZE07], FTDestination[1][BUFSIZE07];

    int AvailableOptions = 5, SubmitOrContinue, ExistingAccounts;
    bool Selecting = true, Updated = false, FirstRun = true;
    bool FirstARMUpgrade = false, SecondARMUpgrade = false;
    bool ConfirmOrBackARM = false;
    char *TempEA, AKDC;

    if (access("RegisteredAccounts.txt", F_OK) != 0) { GlobalRegisteredAccounts = 0; }
    else {
        FDestination     = fopen("RegisteredAccounts.txt", "r");
        FTempDestination = fopen("TempDestination.txt", "w");

        while (fgets(BUFFER, sizeof(BUFFER), FDestination) != 0) {
            BufLen = strlen(BUFFER);
            for (int i = 0; i < BufLen; i++) BUFFER[i] += EncryptionKey;
            fputs(BUFFER, FTempDestination);
        } fclose(FDestination); fclose(FTempDestination);

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
        
        if (strcmp(SourceTextFileName, "RegisteredAccounts") == 0) {
            if ((strchr(TxtFileName, ':') == NULL) && (strchr(SelectedKeyString, ':') == NULL)) {
                int FTDIndex = 0, SKSVIndex = 0;

                FDestination = fopen("TempDestination.txt", "r");
                for (C = getc(FDestination); C != EOF; C = getc(FDestination)) { if (C == '\n') LineTracker++; }
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
                            TempEA = FTDestination[FTDIndex]; break;
                        } else if (strstr(FTDestination[FTDIndex], SourceKeyStringValues[SKSVIndex]) == NULL)
                            SKSVIndex++;
                    } FTDIndex++; SKSVIndex = 0;
                }
                strcpy(DeleteTempDestinationTxtFile, "del ");
                strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
                system(DeleteTempDestinationTxtFile);
            }
        } else {
            strcpy(DeleteTempDestinationTxtFile, "del ");
            strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
            system(DeleteTempDestinationTxtFile);
        }
        
        TempEA = TrimWhiteSpaces(TempEA);
        ExistingAccounts = atoi(TempEA);
        GlobalRegisteredAccounts += ExistingAccounts;
    }
    
    if ((FN && LN && E && U && P) && !FirstARMUpgrade) { AvailableOptions += 4; FirstARMUpgrade = true; }
    if ((FN && LN && E && U && P) && (B && A && PN && S) && !SecondARMUpgrade) {
        AvailableOptions += 5; SecondARMUpgrade = true;
    }

    while (Selecting) {
        if (!FirstRun) {
            /*  Separated by one line to another, handling only the first
                FIVE (5) rows each parts.
            >   First Name, Last Name, Personal E-mail, SKYR Username, SKYR Password
            */

            /*  Separated by one line to another, handling both the first and second
                FOUR (4) + FIVE (5) rows both parts.
            >   Date of Birth, Age on Present, Phone  Number, Sex/Gender
            */

            if ((ARMSelected + 1) > 0 && (ARMSelected + 1) <= 5 && (AvailableOptions == 5)) {
                if ((ARMSelected + 1) == 1) {
                    if (!FN) { printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else     { printf("\n\n\n\n      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ARMSelected + 1) == 2) {
                    if (!LN) { printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ARMSelected + 1) == 3) {
                    if (!E)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ARMSelected + 1) == 4) {
                    if (!U)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ARMSelected + 1) == 5) {
                    if (!P)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                }
            }
            
            if ((ARMSelected + 1) > 0 && (ARMSelected + 1) <= 9 && (AvailableOptions == 9)) {
                if ((ARMSelected + 1) == 1) {
                    if (!FN) { printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 2) {
                    if (!LN) { printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 3) {
                    if (!E)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 4) {
                    if (!U)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 5) {
                    if (!P)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 6) {
                    if (!B)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTYELLOW"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTGREEN"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 7) {
                    if (!A)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 8) {
                    if (!PN) { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 9) {
                    if (!S)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                }
            }

            if ((ARMSelected + 1) > 0 && (ARMSelected + 1) <= 14 && (AvailableOptions == 14)) {
                if ((ARMSelected + 1) == 1) {
                    if (!FN) { printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 2) {
                    if (!LN) { printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 3) {
                    if (!E)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 4) {
                    if (!U)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 5) {
                    if (!P)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 6) {
                    if (!B)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTYELLOW"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTGREEN"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 7) {
                    if (!A)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 8) {
                    if (!PN) { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 9) {
                    if (!S)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                }
                
                if ((ARMSelected + 1) > 9) {
                    printf("\n\n\n\n\tInfo: You have all the main required information listing above of all \n\t      nine (9) personal infos, and you may proceed to the final step, and \n\t      it's about giving optional information about your career profiling, \n\t      degree of experience, and such else.\n");
                    printf("\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour personal profile infos?\n\n");
                    MessagesShown_ArrowKeyChoiceDialog[2] = "\n\n\n\n\tInfo: You have all the main required information listing above of all \n\t      nine (9) personal infos, and you may proceed to the final step, and \n\t      it's about giving optional information about your career profiling, \n\t      degree of experience, and such else.";
                    MessagesShown_ArrowKeyChoiceDialog[3] = "\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour personal profile infos?\n";
                    SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 2, 4);

                    if (SubmitOrContinue) {
                        FILE *TempARMInputs;
                        char RegAccInsider[BUFSIZE07], GRA[BUFSIZE07];
                        char FirstName[BUFSIZE07], LastName[BUFSIZE07], Email[BUFSIZE07], Username[BUFSIZE07], Password[BUFSIZE07];
                        char DateOfBirth[BUFSIZE07], AgeOnPresent[BUFSIZE07], PhoneNumber[BUFSIZE07], Sex[BUFSIZE07];
                        char UpdateLocalTime[BUFSIZE07], LocalTime[BUFSIZE07], AccountMadeTime[BUFSIZE07], MadeTime[BUFSIZE07];

                        TempARMInputs = fopen("TempRegisteredAccount.txt", "w");
                        itoa((GlobalRegisteredAccounts + 1), GRA, 10);
                        snprintf(LocalTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                        snprintf(MadeTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                        
                        strcpy(RegAccInsider, "Registered Accounts: "); strcat(RegAccInsider, GRA); strcat(RegAccInsider, " account(s) in total.\n");
                        strcpy(UpdateLocalTime, "PersonalFMSA | Last Updated: ");
                        strcat(UpdateLocalTime, LocalTime); strcat(UpdateLocalTime, "\n");
                        strcpy(AccountMadeTime, "Profile Account :: No. "); strcat(AccountMadeTime, GRA); strcat(AccountMadeTime, "\n");
                        strcat(AccountMadeTime, "Created on: "); strcat(AccountMadeTime, MadeTime); strcat(AccountMadeTime, "\n");

                        fputs("----------------------------------------------------------------------------------------------------\n", TempARMInputs);
                        fputs("SKYR Corp. Foundation Inc. :: @V1.0_beta1600 (November, 2023)\n", TempARMInputs);
                        fputs("Built-in Console Application [CLI-Win32], fundamentally C (100%%)\n", TempARMInputs);
                        fputs(UpdateLocalTime, TempARMInputs); fputs("\n", TempARMInputs);
                        fputs("SKYR Corp. :: Personal Financial Management System [CLI-Win32] Application\n", TempARMInputs);
                        fputs("----------------------------------------------------------------------------------------------------\n", TempARMInputs);
                        fputs(RegAccInsider, TempARMInputs);
                        fputs("----------------------------------------------------------------------------------------------------\n", TempARMInputs);
                        fputs(AccountMadeTime, TempARMInputs); fputs("\n", TempARMInputs);

                        for (int i = 0; i < (GlobalRegisteredAccounts + 1); i++) {
                            strcpy(FirstName, "First Name:\t\t\t");          strcat(FirstName, ARMInputs[GlobalRegisteredAccounts].FirstName);         strcat(FirstName, "\n");
                            strcpy(LastName, "Lase Name:\t\t\t");            strcat(LastName, ARMInputs[GlobalRegisteredAccounts].LastName);           strcat(LastName, "\n");
                            strcpy(Email, "Personal E-mail:\t");           strcat(Email, ARMInputs[GlobalRegisteredAccounts].Email);               strcat(Email, "\n");
                            strcpy(Username, "SKYR Username:\t\t");        strcat(Username, ARMInputs[GlobalRegisteredAccounts].Username);         strcat(Username, "\n");
                            strcpy(Password, "SKYR Password:\t\t");        strcat(Password, ARMInputs[GlobalRegisteredAccounts].Password);         strcat(Password, "\n");
                            strcpy(DateOfBirth, "\nDate of Birth:\t\t");   strcat(DateOfBirth, ARMInputs[GlobalRegisteredAccounts].DateOfBirth);   strcat(DateOfBirth, "\n");
                            strcpy(AgeOnPresent, "Age on Present:\t\t");   strcat(AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent); strcat(AgeOnPresent, "\n");
                            strcpy(PhoneNumber, "Phone Number:\t\t");      strcat(PhoneNumber, ARMInputs[GlobalRegisteredAccounts].PhoneNumber);   strcat(PhoneNumber, "\n");
                            strcpy(Sex, "Sex/Gender:\t\t\t");                strcat(Sex, ARMInputs[GlobalRegisteredAccounts].Sex);                     strcat(Sex, "\n");

                            fputs(FirstName, TempARMInputs); fputs(LastName, TempARMInputs); fputs(Email, TempARMInputs); fputs(Username, TempARMInputs); fputs(Password, TempARMInputs);
                            fputs(DateOfBirth, TempARMInputs); fputs(AgeOnPresent, TempARMInputs); fputs(PhoneNumber, TempARMInputs); fputs(Sex, TempARMInputs);
                            fputs("----------------------------------------------------------------------------------------------------\n", TempARMInputs);
                        } fclose(TempARMInputs);

                        EncryptTxtFile("TempRegisteredAccount.txt", "RegisteredAccounts.txt", EncryptionKey, true);
                        puts(ANSI_COLOR_LIGHTBLUE"\n\tInfo: Your account profile has been saved and ecrypted."ANSI_COLOR_RESET);
                        puts(ANSI_COLOR_LIGHTMAGENTA"\t      Now you may proceed to logged in from your existing account(s) right after you \n\t      press the [ENTER] button key."ANSI_COLOR_RESET);
                        getchar();
                        AccountLoginMenu(0); GlobalRegisteredAccounts++;

                    } else { ARMSelected = 0; AccountRegistrationMenu(ARMSelected); }
                }
            }

        } else {
            FirstRun = false;

            if ((ARMSelected + 1) > 0 && (ARMSelected + 1) <= 5 && (AvailableOptions == 5)) {
                if ((ARMSelected + 1) == 1) {
                    if (!FN) { printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else     { printf("\n\n\n\n      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ARMSelected + 1) == 2) {
                    if (!LN) { printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ARMSelected + 1) == 3) {
                    if (!E)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ARMSelected + 1) == 4) {
                    if (!U)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ARMSelected + 1) == 5) {
                    if (!P)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                }
            }
            
            if ((ARMSelected + 1) > 0 && (ARMSelected + 1) <= 9 && (AvailableOptions == 9)) {
                if ((ARMSelected + 1) == 1) {
                    if (!FN) { printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 2) { 
                    if (!LN) { printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 3) {
                    if (!E)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 4) {
                    if (!U)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 5) {
                    if (!P)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 6) {
                    if (!B)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTYELLOW"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTGREEN"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 7) {
                    if (!A)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 8) {
                    if (!PN) { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 9) {
                    if (!S)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                }
            }

            if ((ARMSelected + 1) > 0 && (ARMSelected + 1) <= 14 && (AvailableOptions == 14)) {
                if ((ARMSelected + 1) == 1) {
                    if (!FN) { printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 2) {
                    if (!LN) { printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 3) {
                    if (!E)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 4) {
                    if (!U)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 5) {
                    if (!P)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 6) {
                    if (!B)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTYELLOW"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTGREEN"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 7) {
                    if (!A)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 8) {
                    if (!PN) { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                } else if ((ARMSelected + 1) == 9) {
                    if (!S)  { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                    else     { printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex); }
                }
                
                if ((ARMSelected + 1) > 9) {
                    printf("\n\n\n\n\tInfo: You have all the main required information listing above of all \n\t      nine (9) personal infos, and you may proceed to the final step, and \n\t      it's about giving optional information about your career profiling, \n\t      degree of experience, and such else.\n");
                    printf("\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour personal profile infos?\n\n");
                    MessagesShown_ArrowKeyChoiceDialog[2] = "\n\n\n\n\tInfo: You have all the main required information listing above of all \n\t      nine (9) personal infos, and you may proceed to the final step, and \n\t      it's about giving optional information about your career profiling, \n\t      degree of experience, and such else.";
                    MessagesShown_ArrowKeyChoiceDialog[3] = "\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour personal profile infos?\n";
                    SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 2, 4);

                    if (SubmitOrContinue) {
                        FILE *TempARMInputs;
                        char RegAccInsider[BUFSIZE07], GRA[BUFSIZE07];
                        char FirstName[BUFSIZE07], LastName[BUFSIZE07], Email[BUFSIZE07], Username[BUFSIZE07], Password[BUFSIZE07];
                        char DateOfBirth[BUFSIZE07], AgeOnPresent[BUFSIZE07], PhoneNumber[BUFSIZE07], Sex[BUFSIZE07];
                        char UpdateLocalTime[BUFSIZE07], LocalTime[BUFSIZE07], AccountMadeTime[BUFSIZE07], MadeTime[BUFSIZE07];

                        for (int i = 0; i < (GlobalRegisteredAccounts + 1); i++) {
                            TempARMInputs = fopen("TempRegisteredAccount.txt", "w");
                            itoa((GlobalRegisteredAccounts + 1), GRA, 10);
                            snprintf(LocalTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                            snprintf(MadeTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                            
                            strcpy(RegAccInsider, "Registered Accounts: "); strcat(RegAccInsider, GRA); strcat(RegAccInsider, " account(s) in total.\n");
                            strcpy(UpdateLocalTime, "PersonalFMSA | Last Updated: ");
                            strcat(UpdateLocalTime, LocalTime); strcat(UpdateLocalTime, "\n");
                            strcpy(AccountMadeTime, "Profile Account :: No. "); strcat(AccountMadeTime, GRA); strcat(AccountMadeTime, "\n");
                            strcat(AccountMadeTime, "Created on: "); strcat(AccountMadeTime, MadeTime); strcat(AccountMadeTime, "\n");

                            fputs("----------------------------------------------------------------------------------------------------\n", TempARMInputs);
                            fputs("SKYR Corp. Foundation Inc. :: @V1.0_beta1600 (November, 2023)\n", TempARMInputs);
                            fputs("Built-in Console Application [CLI-Win32], fundamentally C (100%%)\n", TempARMInputs);
                            fputs(UpdateLocalTime, TempARMInputs); fputs("\n", TempARMInputs);
                            fputs("SKYR Corp. :: Personal Financial Management System [CLI-Win32] Application\n", TempARMInputs);
                            fputs("----------------------------------------------------------------------------------------------------\n", TempARMInputs);
                            fputs(RegAccInsider, TempARMInputs);
                            fputs("----------------------------------------------------------------------------------------------------\n", TempARMInputs);
                            fputs(AccountMadeTime, TempARMInputs); fputs("\n", TempARMInputs);

                            strcpy(FirstName, "First Name:\t\t\t");          strcat(FirstName, ARMInputs[GlobalRegisteredAccounts].FirstName);       strcat(FirstName, "\n");
                            strcpy(LastName, "Lase Name:\t\t\t");            strcat(LastName, ARMInputs[GlobalRegisteredAccounts].LastName);         strcat(LastName, "\n");
                            strcpy(Email, "Personal E-mail:\t");           strcat(Email, ARMInputs[GlobalRegisteredAccounts].Email);               strcat(Email, "\n");
                            strcpy(Username, "SKYR Username:\t\t");        strcat(Username, ARMInputs[GlobalRegisteredAccounts].Username);         strcat(Username, "\n");
                            strcpy(Password, "SKYR Password:\t\t");        strcat(Password, ARMInputs[GlobalRegisteredAccounts].Password);         strcat(Password, "\n");
                            strcpy(DateOfBirth, "\nDate of Birth:\t\t");   strcat(DateOfBirth, ARMInputs[GlobalRegisteredAccounts].DateOfBirth);   strcat(DateOfBirth, "\n");
                            strcpy(AgeOnPresent, "Age on Present:\t\t");   strcat(AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent); strcat(AgeOnPresent, "\n");
                            strcpy(PhoneNumber, "Phone Number:\t\t");      strcat(PhoneNumber, ARMInputs[GlobalRegisteredAccounts].PhoneNumber);   strcat(PhoneNumber, "\n");
                            strcpy(Sex, "Sex/Gender:\t\t\t");                strcat(Sex, ARMInputs[GlobalRegisteredAccounts].Sex);                   strcat(Sex, "\n");

                            fputs(FirstName, TempARMInputs); fputs(LastName, TempARMInputs); fputs(Email, TempARMInputs); fputs(Username, TempARMInputs); fputs(Password, TempARMInputs);
                            fputs(DateOfBirth, TempARMInputs); fputs(AgeOnPresent, TempARMInputs); fputs(PhoneNumber, TempARMInputs); fputs(Sex, TempARMInputs);
                            fputs("----------------------------------------------------------------------------------------------------\n", TempARMInputs);
                        } fclose(TempARMInputs);

                        EncryptTxtFile("TempRegisteredAccount.txt", "RegisteredAccounts.txt", EncryptionKey, true);
                        puts(ANSI_COLOR_LIGHTBLUE"\n\tInfo: Your account profile has been saved and ecrypted."ANSI_COLOR_RESET);
                        puts(ANSI_COLOR_LIGHTMAGENTA"\t      Now you may proceed to logged in from your existing account(s) right after you \n\t      press the [ENTER] button key."ANSI_COLOR_RESET);
                        getchar();
                        AccountLoginMenu(0); GlobalRegisteredAccounts++;

                    } else { ARMSelected = 0; AccountRegistrationMenu(ARMSelected); }
                }
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (ARMSelected > 0 && ARMSelected < AvailableOptions) {
                    --ARMSelected; Updated = true;
                } else if (ARMSelected <= 0) {
                    ARMSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (ARMSelected >= 0 && ARMSelected < AvailableOptions - 1) {
                    ++ARMSelected; Updated = true;
                } else if (ARMSelected >= AvailableOptions - 1) {
                    ARMSelected = 0; Updated = true;
                } break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } (Selecting) ? ClearScreen() : NULL;
        
        fflush(stdin);
        if (Updated) {
            Updated = false;
        } else {
            NULL;
        }
    }

    if (ARMSelected == 0) {
        ClearScreen();
        char InputFirstName[BUFSIZE07];

        if (FN) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already insert your first name as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName);
            printf("      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"First Name."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the first name of your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The first name of yours can be more than one or two words."ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"First Name."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the first name of your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The first name of yours can be more than one or two words."ANSI_COLOR_RESET);
        }
        
        printf("\nFirst Name: ");
        fgets(InputFirstName, BUFSIZE07, stdin);

        while (strlen(InputFirstName) <= 3) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must have to insert your first name at least a single word (min. 3 characters)!\n"ANSI_COLOR_RESET);
            printf("      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"First Name."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the first name of your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The first name of yours can be more than one or two words."ANSI_COLOR_RESET);

            printf("\nFirst Name: ");
            fgets(InputFirstName, BUFSIZE07, stdin);
        }
        
        InputFirstName[strlen(InputFirstName) - 1] = '\0';
        FN = true;
        strcpy(ARMInputs[GlobalRegisteredAccounts].FirstName, InputFirstName);
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 1) {
        ClearScreen();
        char InputLastName[BUFSIZE07];

        if (LN) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already insert your last name as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].LastName);
            printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Last Name."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the last name of your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The last name of yours can be more than one or two words."ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Last Name."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the last name of your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The last name of yours can be more than one or two words."ANSI_COLOR_RESET);
        }

        printf("\nLast Name: ");
        fgets(InputLastName, BUFSIZE07, stdin);

        while (strlen(InputLastName) <= 3) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must have to insert your last name at least a single word (min. 3 characters)!\n"ANSI_COLOR_RESET);
            printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Last Name."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the first name of your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The last name of yours can be more than one or two words."ANSI_COLOR_RESET);

            printf("\nLast Name: ");
            fgets(InputLastName, BUFSIZE07, stdin);
        }
        
        InputLastName[strlen(InputLastName) - 1] = '\0';
        LN = true;
        strcpy(ARMInputs[GlobalRegisteredAccounts].LastName, InputLastName);
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 2) {
        ClearScreen();
        char InputEmail[BUFSIZE07];

        if (E) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already insert your personal e-mail as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].Email);
            printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating \n\t      your own e-mail."ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating \n\t      your own e-mail."ANSI_COLOR_RESET);
        }

        printf("\nPersonal E-mail: ");
        fgets(InputEmail, BUFSIZE07, stdin);

        while (strlen(InputEmail) <= 3 || strchr(InputEmail, '@') == NULL || strchr(InputEmail, '.') == NULL) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must have to insert your last name at least a single word (min. 3 characters)!\n\t         The valid E-mail format must have a '@' symbol, and the provider (authorized by) \n\t         with the domain itself.\n"ANSI_COLOR_RESET);
            printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating \n\t      your own e-mail."ANSI_COLOR_RESET);

            printf("\nPersonal E-mail: ");
            fgets(InputEmail, BUFSIZE07, stdin);
        }
        
        InputEmail[strlen(InputEmail) - 1] = '\0';
        E = true;
        strcpy(ARMInputs[GlobalRegisteredAccounts].Email, InputEmail);
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 3) {
        ClearScreen();
        char InputUsername[BUFSIZE07];

        if (U) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already insert your username as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].Username);
            printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, \n\t      so use underscores or dashes to represents the next characters."ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, \n\t      so use underscores or dashes to represents the next characters."ANSI_COLOR_RESET);
        }

        printf("\nSKYR Username: ");
        fgets(InputUsername, BUFSIZE07, stdin);

        while (strlen(InputUsername) <= 3) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must have to insert your username at least a single word (min. 3 characters)!\n"ANSI_COLOR_RESET);
            printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, \n\t      so use underscores or dashes to represents the next characters."ANSI_COLOR_RESET);

            printf("\nSKYR Username: ");
            fgets(InputUsername, BUFSIZE07, stdin);
        }
        
        InputUsername[strlen(InputUsername) - 1] = '\0';
        U = true;
        strcpy(ARMInputs[GlobalRegisteredAccounts].Username, InputUsername);
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 4) {
        ClearScreen();
        char InputPassword[BUFSIZE07], HiddenPassword[BUFSIZE07];

        if (P) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already insert your password as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations \n\t      you'd like to insert with. The password insertion is censored, and you can peek \n\t      the password you've inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations \n\t      you'd like to insert with. The password insertion is censored, and you can peek \n\t      the password you've inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);
        }

        printf("\nSKYR Password: ");
        fgets(InputPassword, BUFSIZE07, stdin);

        while (strlen(InputPassword) <= 8) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must have to insert your password in any unique way possible (min. 8 characters)!\n"ANSI_COLOR_RESET);
            printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].FirstName, ARMInputs[GlobalRegisteredAccounts].LastName, ARMInputs[GlobalRegisteredAccounts].Email, ARMInputs[GlobalRegisteredAccounts].Username, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations \n\t      you'd like to insert with. The password insertion is censored, and you can peek \n\t      the password you've inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);

            printf("\nSKYR Password: ");
            fgets(InputPassword, BUFSIZE07, stdin);
        }
        
        InputPassword[strlen(InputPassword) - 1] = '\0';
        P = true;

        for (int i = 0; i < strlen(InputPassword); i++) {
            if (i == 0) { strcpy(HiddenPassword, "*"); }
            else        { strcat(HiddenPassword, "*"); }
        } strcpy(ARMInputs[GlobalRegisteredAccounts].Password, InputPassword);
        strcpy(ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, HiddenPassword);
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 5) {
        ClearScreen();
        char   InputDateOfBirth[BUFSIZE07], InputDOBTemp[BUFSIZE07], NumericalPattern[BUFSIZE07];
        char   *TempDOBTempD, *TempDOBTempM, *TempDOBTempY, *DOBTempD, *DOBTempM, *DOBTempY;
        char   DaysOfWeek[7][BUFSIZE07]      = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        char   MonthsOfYear[12][BUFSIZE07]   = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        int    TimeCounterNumeric[12]        = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        int    DashesOccurences = 0;
        bool   EmptyDOBInput = false;
        size_t TempDay, TempDate, TempMonth, TempYear, Day, Date, Month, Year;

        if (B) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already insert your date of birth as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].DateOfBirth);
            printf("      " ANSI_COLOR_LIGHTGREEN"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Date of Birth."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your date of birth profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The date of birth of yours must be a valid format as written down below: \n\t      <DATE>-<MONTH>-<YEAR> ... NO SPACES NEEDED! \n\t      The valid example of date of birth format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Date of Birth."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your date of birth profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The date of birth of yours must be a valid format as written down below: \n\t      <DATE>-<MONTH>-<YEAR> ... NO SPACES NEEDED! \n\t      The valid example of date of birth format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);
        }

        printf("\nDate of Birth: ");
        fgets(InputDateOfBirth, BUFSIZE07, stdin);

        if (strlen(InputDateOfBirth) < 2) { EmptyDOBInput = true; }
        else {
            strcpy(InputDOBTemp, InputDateOfBirth);
            InputDOBTemp[strlen(InputDOBTemp) - 1] = '\0';
            DashesOccurences = FindOccurences(InputDOBTemp, '-');
            if (DashesOccurences == 2) {
                TempDOBTempD = strtok(InputDOBTemp, "-"); TempDOBTempM = strtok(NULL, "-"); TempDOBTempY = strtok(NULL, "-");
                TempDate = atoi(TempDOBTempD); TempMonth = atoi(TempDOBTempM); TempYear = atoi(TempDOBTempY);
            } EmptyDOBInput = false;
        }

        while (EmptyDOBInput || DashesOccurences != 2 || (((TempYear % 4) == 0 && (TempMonth == 2)) && TempDate > 29) || (((TempYear % 4) != 0 && (TempMonth == 2)) && TempDate > 28) || (TempDate < 1 || TempDate > 31) || (TempMonth < 1 || TempMonth > 12) || (TempYear < 1)) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must have to insert your birth of date as what the pre-requisites requested for!\n"ANSI_COLOR_RESET);
            printf("      " ANSI_COLOR_LIGHTYELLOW"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Date of Birth."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your date of birth profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The date of birth of yours must be a valid format as written down below: \n\t      <DATE>-<MONTH>-<YEAR> ... NO SPACES NEEDED! \n\t      The valid example of date of birth format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);

            printf("\nDate of Birth: ");
            fgets(InputDateOfBirth, BUFSIZE07, stdin);

            if (strlen(InputDateOfBirth) < 2) { EmptyDOBInput = true; }
            else {
                strcpy(InputDOBTemp, InputDateOfBirth);
                InputDOBTemp[strlen(InputDOBTemp) - 1] = '\0';
                DashesOccurences = FindOccurences(InputDOBTemp, '-');
                if (DashesOccurences == 2) {
                    TempDOBTempD = strtok(InputDOBTemp, "-"); TempDOBTempM = strtok(NULL, "-"); TempDOBTempY = strtok(NULL, "-");
                    TempDate = atoi(TempDOBTempD); TempMonth = atoi(TempDOBTempM); TempYear = atoi(TempDOBTempY);
                } EmptyDOBInput = false;
            }
        }
        
        InputDateOfBirth[strlen(InputDateOfBirth) - 1] = '\0';
        B = true;
        DOBTempD = strtok(InputDateOfBirth, "-"); DOBTempM = strtok(NULL, "-"); DOBTempY = strtok(NULL, "-");
        DOBTempD = TrimWhiteSpaces(DOBTempD); DOBTempM = TrimWhiteSpaces(DOBTempM); DOBTempY = TrimWhiteSpaces(DOBTempY);
        Date = atoi(DOBTempD); Month = atoi(DOBTempM); Year = atoi(DOBTempY);

        Year -= Month < 3;
        Day = (Year + (Year / 4) - (Year / 100) + (Year / 400) + TimeCounterNumeric[Month - 1] + Date) % 7;
        if (Date >= 11 && Date < 21)      { strcpy(NumericalPattern, "th"); }
        else {
            if (strlen(DOBTempD) < 2) {
                if      (DOBTempD[0] == '1') { strcpy(NumericalPattern, "st"); }
                else if (DOBTempD[0] == '2') { strcpy(NumericalPattern, "nd"); }
                else if (DOBTempD[0] == '3') { strcpy(NumericalPattern, "rd"); }
                else                         { strcpy(NumericalPattern, "th"); }
            } else {
                if      (DOBTempD[1] == '1') { strcpy(NumericalPattern, "st"); }
                else if (DOBTempD[1] == '2') { strcpy(NumericalPattern, "nd"); }
                else if (DOBTempD[1] == '3') { strcpy(NumericalPattern, "rd"); }
                else                         { strcpy(NumericalPattern, "th"); }
            }
        }

        strcpy(ARMInputs[GlobalRegisteredAccounts].DateOfBirth, DaysOfWeek[Day]);
        strcat(ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ", ");
        strcat(ARMInputs[GlobalRegisteredAccounts].DateOfBirth, DOBTempD);
        strcat(ARMInputs[GlobalRegisteredAccounts].DateOfBirth, NumericalPattern);
        strcat(ARMInputs[GlobalRegisteredAccounts].DateOfBirth, " of ");
        strcat(ARMInputs[GlobalRegisteredAccounts].DateOfBirth, MonthsOfYear[Month - 1]);
        strcat(ARMInputs[GlobalRegisteredAccounts].DateOfBirth, " ");
        strcat(ARMInputs[GlobalRegisteredAccounts].DateOfBirth, DOBTempY);
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 6) {
        if (!B) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: Before inserting your present age in here, make sure to fill in your \n\t\t date of birth, considering that there'll be a checking if your present \n\t\t age is a valid!\n\n"ANSI_COLOR_RESET);
            printf(ANSI_COLOR_LIGHTYELLOW"\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            printf(ANSI_COLOR_LIGHTMAGENTA"\n\tPlease proceed back to the registration menu by pressing your [ENTER] button \n\tkey on the keyboard. "ANSI_COLOR_RESET); getchar();
            AccountRegistrationMenu(ARMSelected);
        } ClearScreen();

        char   InputAgeOnPresent[BUFSIZE07], StatedBirthDate[BUFSIZE07];
        char   *TempStatedBirthYear;
        size_t InputAOP, StatedBirthYear;
        
        strcpy(StatedBirthDate, ARMInputs[GlobalRegisteredAccounts].DateOfBirth);
        TempStatedBirthYear = strtok(StatedBirthDate, " ");
        TempStatedBirthYear = strtok(NULL, " "); TempStatedBirthYear = strtok(NULL, " ");
        TempStatedBirthYear = strtok(NULL, " "); TempStatedBirthYear = strtok(NULL, " ");

        if (A) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already insert your present age as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent);
            printf("\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Age on Present."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your present age profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The present age must be a rightful age as the same in your personal date of birth, \n\t      and it will be checked whether if your current age make up to your birth year until \n\t      the current year in the calendar system."ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Age on Present."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your present age profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The present age must be a rightful age as the same in your personal date of birth, \n\t      and it will be checked whether if your current age make up to your birth year until \n\t      the current year in the calendar system."ANSI_COLOR_RESET);
        }

        printf("\nAge on Present: ");
        fgets(InputAgeOnPresent, BUFSIZE07, stdin);
        InputAOP        = atoi(InputAgeOnPresent);
        StatedBirthYear = atoi(TempStatedBirthYear);

        while (strlen(InputAgeOnPresent) < 1 || InputAOP < 13 || (StatedBirthYear + InputAOP != 2023)) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must have to insert your present age rightfully and honestly (min. 13 years old)!\n"ANSI_COLOR_RESET);
            printf("\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Age on Present."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your present age profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The present age must be a rightful age as the same in your personal date of birth, \n\t      and it will be checked whether if your current age make up to your birth year until \n\t      the current year in the calendar system."ANSI_COLOR_RESET);

            printf("\nAge on Present: ");
            fgets(InputAgeOnPresent, BUFSIZE07, stdin);
            InputAOP        = atoi(InputAgeOnPresent);
            StatedBirthYear = atoi(TempStatedBirthYear);
        }
        
        InputAgeOnPresent[strlen(InputAgeOnPresent) - 1] = '\0';
        A = true;
        strcpy(ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, InputAgeOnPresent);
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 7) {
        ClearScreen();
        char InputPhoneNumber[BUFSIZE07], TempCountryCode[BUFSIZE07], TempDigitsNumber[BUFSIZE07], TempDigitsNumberTemp[BUFSIZE07], TempFinalPhoneNumber[BUFSIZE07];
        char *CountryCode, *DigitsNumber, *FinalPhoneNumber;

        if (PN) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already insert your phone number as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].PhoneNumber);
            printf("\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +<COUNTRY_CODE> XXXXXXXXXXX \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +<COUNTRY_CODE> XXXXXXXXXXX \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);
        }

        printf("\nPhone Number: ");
        fgets(InputPhoneNumber, BUFSIZE07, stdin);

        strcpy(TempCountryCode, InputPhoneNumber);
        TempCountryCode[strlen(TempCountryCode) - 1] = '\0';
        if (strchr(TempCountryCode, ' ') != NULL) {
            CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
            CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
        }

        while ((strlen(DigitsNumber) <= 4 || strlen(DigitsNumber) > 13) || CountryCode[0] != '+' || strchr(InputPhoneNumber, ' ') == NULL) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must have to insert your with a starting phone country code and \n\t      for at least 4 to 13 digits (min. 4 digits)!\n"ANSI_COLOR_RESET);
            printf("\n\n\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +<COUNTRY_CODE> XXXXXXXXXXX \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);

            printf("\nPhone Number: ");
            fgets(InputPhoneNumber, BUFSIZE07, stdin);

            strcpy(TempCountryCode, InputPhoneNumber);
            TempCountryCode[strlen(TempCountryCode) - 1] = '\0';
            if (strchr(TempCountryCode, ' ') != NULL) {
                CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
                CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
            }
        }
        
        InputPhoneNumber[strlen(InputPhoneNumber) - 1] = '\0';
        PN = true;

        strcpy(TempDigitsNumber, DigitsNumber);
        strcpy(TempFinalPhoneNumber, CountryCode);
        strcpy(TempDigitsNumberTemp, " ");
        for (int i = 1; i <= strlen(TempDigitsNumber); i++) {
            if (i == 3)                        { strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); strcat(TempDigitsNumberTemp, "-"); }
            else if ((i % 4) == 0 && (i != 4)) { strcat(TempDigitsNumberTemp, "-"); strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); }
            else                               { strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); }
        } strcat(TempFinalPhoneNumber, TempDigitsNumberTemp);
        strcpy(ARMInputs[GlobalRegisteredAccounts].PhoneNumber, TempFinalPhoneNumber);
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 8) {
        ClearScreen();
        char InputSex[BUFSIZE07];

        if (S) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already asserted your sex as: %s.\n\t      But don't worry, if you want to make a change, then please don't be stupid enough to be confused.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].Sex);
            printf("\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Sex/Gender."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your biological sex (or not), into the profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: ONLY two (2) sexes that defines the human biology, and that is whether a \n\t      'Male' or a 'Female'. But nothing to worry, if you prefer not to say about it, \n\t      so just leave the input on blank."ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Sex/Gender."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your biological sex (or not), into the profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: ONLY two (2) sexes that defines the human biology, and that is whether a \n\t      'Male' or a 'Female'. But nothing to worry, if you prefer not to say about it, \n\t      so just leave the input on blank."ANSI_COLOR_RESET);
        }

        printf("\nSex/Gender: ");
        fgets(InputSex, BUFSIZE07, stdin);
        if (strlen(InputSex) == 1) {
            S = true;
            strcpy(ARMInputs[GlobalRegisteredAccounts].Sex, "'Prefer not to say'");
            AccountRegistrationMenu(ARMSelected);
        } strcpy(InputSex, StringUppercase(InputSex));
        InputSex[strlen(InputSex) - 1] = '\0';

        while (strcmp(InputSex, "MALE") != 0 && strcmp(InputSex, "FEMALE") != 0) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must assert your biological sex as either a 'Male' or 'Female' \n\t         (leave blank for prefering not to say)!\n"ANSI_COLOR_RESET);
            printf("\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].DateOfBirth, ARMInputs[GlobalRegisteredAccounts].AgeOnPresent, ARMInputs[GlobalRegisteredAccounts].PhoneNumber, ARMInputs[GlobalRegisteredAccounts].Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Sex/Gender."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your biological sex (or not), into the profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: ONLY two (2) sexes that defines the human biology, and that is whether a \n\t      'Male' or a 'Female'. But nothing to worry, if you prefer not to say about it, \n\t      so just leave the input on blank."ANSI_COLOR_RESET);

            printf("\nSex/Gender: ");
            fgets(InputSex, BUFSIZE07, stdin);
            if (strlen(InputSex) == 1) {
                S = true;
                strcpy(ARMInputs[GlobalRegisteredAccounts].Sex, "'Prefer not to say'");
                AccountRegistrationMenu(ARMSelected);
            } strcpy(InputSex, StringUppercase(InputSex));
            InputSex[strlen(InputSex) - 1] = '\0';
        }
        
        S = true;
        if (strcmp(InputSex, "MALE") == 0)   { strcpy(InputSex, "Male"); }
        if (strcmp(InputSex, "FEMALE") == 0) { strcpy(InputSex, "Female"); }
        strcpy(ARMInputs[GlobalRegisteredAccounts].Sex, InputSex);
        AccountRegistrationMenu(ARMSelected);
    }
}

void AccountLoginMenu(int ALMSelected) {
    ClearScreen();

    FILE *FDestination, *FTempDestination;
    int BufLen, Ptr = 0, KeyTracker = 0, LineTracker = 0, FTDPos = 0;
    char C, BUFFER[BUFSIZE16], DeleteTempDestinationTxtFile[128], TxtFileName[128] = "RegisteredAccounts.txt > First Name, Last Name, Personal E-mail, Phone Number, SKYR Username, SKYR Password";
    char *SourceTextFileName, *SourceKeyStringValue, *SelectedKeyString;
    char *SourceKeyStringValues[BUFSIZE07], FTDestination[6][BUFSIZE07];

    int AvailableOptions = 4, SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    bool ConfirmOrBackALM = false, ALMUpgrade = false;
    char AKDC, MessageID5[BUFSIZE10];
    char FirstName[BUFSIZE07], LastName[BUFSIZE07], Email[BUFSIZE07], PhoneNumber[BUFSIZE07], Username[BUFSIZE07], Password[BUFSIZE07];
    char *ShowFirstName, *ShowLastName;

    if ((LE && LPN && LU && LP) && !ALMUpgrade) { AvailableOptions += 1; ALMUpgrade = true; }

    while (Selecting) {
        if (!FirstRun) {
        /*  Separated by one line to another, handling ONLY THREE (3) rows each parts.
        >   Personal E-mail, SKYR Username, SKYR Password
        */

        if ((ALMSelected + 1) > 0 && (ALMSelected + 1) <= 4 && (AvailableOptions == 4)) {
            if ((ALMSelected + 1) == 1) {
                if (!LE)  { printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                else      { printf("\n\n\n\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
            } else if ((ALMSelected + 1) == 2) {
                if (!LPN) { printf("\n\n\n\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                else      { printf("\n\n\n\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
            } else if ((ALMSelected + 1) == 3) {
                if (!LU)  { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                else      { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
            } else if ((ALMSelected + 1) == 4) {
                if (!LP)  { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                else      { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
            }
        }
        
        else if ((ALMSelected + 1) > 0 && (ALMSelected + 1) <= 5 && (AvailableOptions == 5)) {
            if ((ALMSelected + 1) == 1) {
                if (!LE)  { printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                else      { printf("\n\n\n\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
            } else if ((ALMSelected + 1) == 2) {
                if (!LPN) { printf("\n\n\n\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                else      { printf("\n\n\n\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
            } else if ((ALMSelected + 1) == 3) {
                if (!LU)  { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                else      { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
            } else if ((ALMSelected + 1) == 4) {
                if (!LP)  { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                else      { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
            }
            
            if ((ALMSelected + 1) == 5) {
                printf("\n\n\n\n\tInfo: You've completed inserting the required main data about your profile  \n\t      account, and now you're ready to login into your account.\n");
                printf(ANSI_COLOR_BLUE"\n\tProceed to give a rightful checking on your inserted profile data \n\tright here and there before get logged in? \n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"Account to be linked: %s\n\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email);
                snprintf(MessageID5, BUFSIZE10, ANSI_COLOR_BLUE"\n\tProceed to give a rightful checking on your inserted profile data \n\tright here and there before get logged in? \n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"Account to be linked: %s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email);
                
                MessagesShown_ArrowKeyChoiceDialog[4] = "\n\n\n\n\tInfo: You've completed inserting the required main data about your profile  \n\t      account, and now you're ready to login into your account.";
                MessagesShown_ArrowKeyChoiceDialog[5] = MessageID5;
                SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 4, 6);

                if (SubmitOrContinue) {
                    FDestination     = fopen("RegisteredAccounts.txt", "r");
                    FTempDestination = fopen("TempDestination.txt", "w");

                    while (fgets(BUFFER, sizeof(BUFFER), FDestination) != 0) {
                        BufLen = strlen(BUFFER);
                        for (int i = 0; i < BufLen; i++) BUFFER[i] += EncryptionKey;
                        fputs(BUFFER, FTempDestination);
                    } fclose(FDestination); fclose(FTempDestination);

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
                    
                    strcpy(FirstName,   ReadAndPrintLine("TempDestination.txt", 13 * (GlobalRegisteredAccounts + 1)));
                    strcpy(LastName,    ReadAndPrintLine("TempDestination.txt", 14 * (GlobalRegisteredAccounts + 1)));
                    strcpy(Email,       ReadAndPrintLine("TempDestination.txt", 15 * (GlobalRegisteredAccounts + 1)));
                    strcpy(Username,    ReadAndPrintLine("TempDestination.txt", 16 * (GlobalRegisteredAccounts + 1)));
                    strcpy(Password,    ReadAndPrintLine("TempDestination.txt", 17 * (GlobalRegisteredAccounts + 1)));
                    strcpy(PhoneNumber, ReadAndPrintLine("TempDestination.txt", 21 * (GlobalRegisteredAccounts + 1)));

                    strcpy(DeleteTempDestinationTxtFile, "del ");
                    strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
                    system(DeleteTempDestinationTxtFile);

                    FirstName[strlen(FirstName) - 1] = '\0'; LastName[strlen(LastName) - 1] = '\0';
                    strtok_r(FirstName, ":", &ShowFirstName); ShowFirstName = TrimWhiteSpaces(ShowFirstName);
                    strtok_r(LastName, ":", &ShowLastName); ShowLastName = TrimWhiteSpaces(ShowLastName);

                    if ((strstr(Email, ALMInputs[GlobalRegisteredAccounts].Email)             != NULL) && \
                        (strstr(PhoneNumber, ALMInputs[GlobalRegisteredAccounts].PhoneNumber) != NULL) && \
                        (strstr(Username, ALMInputs[GlobalRegisteredAccounts].Username)       != NULL) && \
                        (strstr(Password, ALMInputs[GlobalRegisteredAccounts].Password)       != NULL)) {
                            puts(ANSI_COLOR_LIGHTBLUE"\n\tNote: You've successfully logged into your profile account!"ANSI_COLOR_RESET);
                            puts(ANSI_COLOR_LIGHTBLUE"\t      Welcome to: Personal Financial Management System [CLI-Win32] Application!"ANSI_COLOR_RESET);
                            printf(ANSI_COLOR_LIGHTGREEN"\n\tLogged in as: %s %s.\n", ShowFirstName, ShowLastName);
                            puts(ANSI_COLOR_LIGHTMAGENTA"\tNow you may proceed to the main menu by pressing the [ENTER] button key on \n\tyour keyboard right away."ANSI_COLOR_RESET);
                            getchar();
                            MainMenu(0);
                        } else {
                            puts(ANSI_COLOR_LIGHTRED"\n\tError: We checked that it seems like one or more inserted profile account(s) you \n\t       provide before isn't validating the same as the original registered \n\t       profile account(s) of yours that you're trying to logged in as by now.\n"ANSI_COLOR_RESET ANSI_COLOR_LIGHTYELLOW"\n\tConsider to re-check your logged in profile data and make sure that if you forget \n\tsomething, then you may to look for a recovery account by tapping [9] button \n\tkey on your keyboard, then proceed to fulfill-in important things afterwards.\n"ANSI_COLOR_RESET);
                            getchar();
                            ALMSelected = 0; AccountLoginMenu(ALMSelected);
                        }
                    } else { ALMSelected = 0; AccountLoginMenu(ALMSelected); }
                }
            }

        } else {
            FirstRun = false;

            if ((ALMSelected + 1) > 0 && (ALMSelected + 1) <= 4 && (AvailableOptions == 4)) {
                if ((ALMSelected + 1) == 1) {
                    if (!LE)  { printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else      { printf("\n\n\n\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ALMSelected + 1) == 2) {
                    if (!LPN) { printf("\n\n\n\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else      { printf("\n\n\n\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ALMSelected + 1) == 3) {
                    if (!LU)  { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else      { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ALMSelected + 1) == 4) {
                    if (!LP)  { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else      { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                }
            }
            
            else if ((ALMSelected + 1) > 0 && (ALMSelected + 1) <= 5 && (AvailableOptions == 5)) {
                if ((ALMSelected + 1) == 1) {
                    if (!LE)  { printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else      { printf("\n\n\n\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ALMSelected + 1) == 2) {
                    if (!LPN) { printf("\n\n\n\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else      { printf("\n\n\n\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ALMSelected + 1) == 3) {
                    if (!LU)  { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else      { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                } else if ((ALMSelected + 1) == 4) {
                    if (!LP)  { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                    else      { printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown); }
                }
                
                if ((ALMSelected + 1) == 5) {
                printf("\n\n\n\n\tInfo: You've completed inserting the required main data about your profile  \n\t      account, and now you're ready to login into your account.\n");
                printf(ANSI_COLOR_BLUE"\n\tProceed to give a rightful checking on your inserted profile data \n\tright here and there before get logged in? \n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"Account to be linked: %s\n\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email);
                snprintf(MessageID5, BUFSIZE10, ANSI_COLOR_BLUE"\n\tProceed to give a rightful checking on your inserted profile data \n\tright here and there before get logged in? \n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"Account to be linked: %s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email);
                
                MessagesShown_ArrowKeyChoiceDialog[4] = "\n\n\n\n\tInfo: You've completed inserting the required main data about your profile  \n\t      account, and now you're ready to login into your account.";
                MessagesShown_ArrowKeyChoiceDialog[5] = MessageID5;
                SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 4, 6);

                if (SubmitOrContinue) {
                    FDestination     = fopen("RegisteredAccounts.txt", "r");
                    FTempDestination = fopen("TempDestination.txt", "w");

                    while (fgets(BUFFER, sizeof(BUFFER), FDestination) != 0) {
                        BufLen = strlen(BUFFER);
                        for (int i = 0; i < BufLen; i++) BUFFER[i] += EncryptionKey;
                        fputs(BUFFER, FTempDestination);
                    } fclose(FDestination); fclose(FTempDestination);

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
                    
                    strcpy(FirstName,   ReadAndPrintLine("TempDestination.txt", 13 * (GlobalRegisteredAccounts + 1)));
                    strcpy(LastName,    ReadAndPrintLine("TempDestination.txt", 14 * (GlobalRegisteredAccounts + 1)));
                    strcpy(Email,       ReadAndPrintLine("TempDestination.txt", 15 * (GlobalRegisteredAccounts + 1)));
                    strcpy(Username,    ReadAndPrintLine("TempDestination.txt", 16 * (GlobalRegisteredAccounts + 1)));
                    strcpy(Password,    ReadAndPrintLine("TempDestination.txt", 17 * (GlobalRegisteredAccounts + 1)));
                    strcpy(PhoneNumber, ReadAndPrintLine("TempDestination.txt", 21 * (GlobalRegisteredAccounts + 1)));

                    strcpy(DeleteTempDestinationTxtFile, "del ");
                    strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
                    system(DeleteTempDestinationTxtFile);

                    FirstName[strlen(FirstName) - 1] = '\0'; LastName[strlen(LastName) - 1] = '\0';
                    strtok_r(FirstName, ":", &ShowFirstName); ShowFirstName = TrimWhiteSpaces(ShowFirstName);
                    strtok_r(LastName, ":", &ShowLastName); ShowLastName = TrimWhiteSpaces(ShowLastName);

                    if ((strstr(Email, ALMInputs[GlobalRegisteredAccounts].Email)             != NULL) && \
                        (strstr(PhoneNumber, ALMInputs[GlobalRegisteredAccounts].PhoneNumber) != NULL) && \
                        (strstr(Username, ALMInputs[GlobalRegisteredAccounts].Username)       != NULL) && \
                        (strstr(Password, ALMInputs[GlobalRegisteredAccounts].Password)       != NULL)) {
                            puts(ANSI_COLOR_LIGHTBLUE"\n\tNote: You've successfully logged into your profile account!"ANSI_COLOR_RESET);
                            puts(ANSI_COLOR_LIGHTBLUE"\t      Welcome to: Personal Financial Management System [CLI-Win32] Application!"ANSI_COLOR_RESET);
                            printf(ANSI_COLOR_LIGHTGREEN"\n\tLogged in as: %s %s.\n", ShowFirstName, ShowLastName);
                            puts(ANSI_COLOR_LIGHTMAGENTA"\tNow you may proceed to the main menu by pressing the [ENTER] button key on \n\tyour keyboard right away."ANSI_COLOR_RESET);
                            getchar();
                            MainMenu(0);
                        } else {
                            puts(ANSI_COLOR_LIGHTRED"\n\tError: We checked that it seems like one or more inserted profile account(s) you \n\t       provide before isn't validating the same as the original registered \n\t       profile account(s) of yours that you're trying to logged in as by now.\n"ANSI_COLOR_RESET ANSI_COLOR_LIGHTYELLOW"\n\tConsider to re-check your logged in profile data and make sure that if you forget \n\tsomething, then you may to look for a recovery account by tapping [9] button \n\tkey on your keyboard, then proceed to fulfill-in important things afterwards.\n"ANSI_COLOR_RESET);
                            getchar();
                            ALMSelected = 0; AccountLoginMenu(ALMSelected);
                        }
                    } else { ALMSelected = 0; AccountLoginMenu(ALMSelected); }
                }
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (ALMSelected > 0 && ALMSelected < AvailableOptions) {
                    --ALMSelected; Updated = true;
                } else if (ALMSelected <= 0) {
                    ALMSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (ALMSelected >= 0 && ALMSelected < AvailableOptions - 1) {
                    ++ALMSelected; Updated = true;
                } else if (ALMSelected >= AvailableOptions - 1) {
                    ALMSelected = 0; Updated = true;
                } break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } (Selecting) ? ClearScreen() : NULL;
        
        fflush(stdin);
        if (Updated) {
            Updated = false;
        } else {
            NULL;
        }
    }

    if (ALMSelected == 0) {
        ClearScreen();
        char InputEmail[BUFSIZE07];

        if (LE) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already insert your personal e-mail as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].Email);
            printf("      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating \n\t      your own e-mail."ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating \n\t      your own e-mail."ANSI_COLOR_RESET);
        }

        printf("\nPersonal E-mail: ");
        fgets(InputEmail, BUFSIZE07, stdin);

        while (strlen(InputEmail) <= 3 || strchr(InputEmail, '@') == NULL || strchr(InputEmail, '.') == NULL) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must have to insert your last name at least a single word (min. 3 characters)!\n\t         The valid E-mail format must have a '@' symbol, and the provider (authorized by) \n\t         with the domain itself.\n"ANSI_COLOR_RESET);
            printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating \n\t      your own e-mail."ANSI_COLOR_RESET);

            printf("\nPersonal E-mail: ");
            fgets(InputEmail, BUFSIZE07, stdin);
        }
        
        InputEmail[strlen(InputEmail) - 1] = '\0';
        LE = true;
        strcpy(ALMInputs[GlobalRegisteredAccounts].Email, InputEmail);
        AccountLoginMenu(ALMSelected);
    }

    else if (ALMSelected == 1) {
        ClearScreen();
        char InputPhoneNumber[BUFSIZE07], TempCountryCode[BUFSIZE07], TempDigitsNumber[BUFSIZE07], TempDigitsNumberTemp[BUFSIZE07], TempFinalPhoneNumber[BUFSIZE07];
        char *CountryCode, *DigitsNumber, *FinalPhoneNumber;

        if (LPN) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already insert your phone number as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].PhoneNumber);
            printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +<COUNTRY_CODE> XXXXXXXXXXX \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +<COUNTRY_CODE> XXXXXXXXXXX \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);
        }

        printf("\nPhone Number: ");
        fgets(InputPhoneNumber, BUFSIZE07, stdin);

        strcpy(TempCountryCode, InputPhoneNumber);
        TempCountryCode[strlen(TempCountryCode) - 1] = '\0';
        if (strchr(TempCountryCode, ' ') != NULL) {
            CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
            CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
        }

        while ((strlen(DigitsNumber) <= 4 || strlen(DigitsNumber) > 13) || CountryCode[0] != '+' || strchr(InputPhoneNumber, ' ') == NULL) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must have to insert your with a starting phone country code and \n\t         for at least 4 to 13 digits (min. 4 digits)!\n"ANSI_COLOR_RESET);
            printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +<COUNTRY_CODE> XXXXXXXXXXX \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);

            printf("\nPhone Number: ");
            fgets(InputPhoneNumber, BUFSIZE07, stdin);

            strcpy(TempCountryCode, InputPhoneNumber);
            TempCountryCode[strlen(TempCountryCode) - 1] = '\0';
            if (strchr(TempCountryCode, ' ') != NULL) {
                CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
                CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
            }
        }
        
        InputPhoneNumber[strlen(InputPhoneNumber) - 1] = '\0';
        LPN = true;

        strcpy(TempDigitsNumber, DigitsNumber);
        strcpy(TempFinalPhoneNumber, CountryCode);
        strcpy(TempDigitsNumberTemp, " ");
        for (int i = 1; i <= strlen(TempDigitsNumber); i++) {
            if (i == 3)                        { strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); strcat(TempDigitsNumberTemp, "-"); }
            else if ((i % 4) == 0 && (i != 4)) { strcat(TempDigitsNumberTemp, "-"); strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); }
            else                               { strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); }
        } strcat(TempFinalPhoneNumber, TempDigitsNumberTemp);
        strcpy(ALMInputs[GlobalRegisteredAccounts].PhoneNumber, TempFinalPhoneNumber);
        AccountLoginMenu(ALMSelected);
    }

    else if (ALMSelected == 2) {
        ClearScreen();
        char InputUsername[BUFSIZE07];

        if (LU) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already insert your username as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].Username);
            printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, \n\t      so use underscores or dashes to represents the next characters."ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, \n\t      so use underscores or dashes to represents the next characters."ANSI_COLOR_RESET);
        }

        printf("\nSKYR Username: ");
        fgets(InputUsername, BUFSIZE07, stdin);

        while (strlen(InputUsername) <= 3) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must have to insert your username at least a single word (min. 3 characters)!\n"ANSI_COLOR_RESET);
            printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, \n\t      so use underscores or dashes to represents the next characters."ANSI_COLOR_RESET);

            printf("\nSKYR Username: ");
            fgets(InputUsername, BUFSIZE07, stdin);
        }
        
        InputUsername[strlen(InputUsername) - 1] = '\0';
        LU = true;
        strcpy(ALMInputs[GlobalRegisteredAccounts].Username, InputUsername);
        AccountLoginMenu(ALMSelected);
    }

    else if (ALMSelected == 3) {
        ClearScreen();
        char InputPassword[BUFSIZE07], HiddenPassword[BUFSIZE07];

        if (LP) {
            printf(ANSI_COLOR_GREEN"\n\n\n\n\tInfo: We'd checked that you earlier had already insert your password as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations \n\t      you'd like to insert with. The password insertion is censored, and you can peek \n\t      the password you've inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);
        } else {
            printf("\n\n\n\n\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations \n\t      you'd like to insert with. The password insertion is censored, and you can peek \n\t      the password you've inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);
        }

        printf("\nSKYR Password: ");
        fgets(InputPassword, BUFSIZE07, stdin);

        while (strlen(InputPassword) <= 8) {
            ClearScreen();
            puts(ANSI_COLOR_LIGHTRED"\n\n\n\n\tWarning: You must have to insert your password in any unique way possible (min. 8 characters)!\n"ANSI_COLOR_RESET);
            printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs[GlobalRegisteredAccounts].Email, ALMInputs[GlobalRegisteredAccounts].PhoneNumber, ALMInputs[GlobalRegisteredAccounts].Username, ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations \n\t      you'd like to insert with. The password insertion is censored, and you can peek \n\t      the password you've inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);

            printf("\nSKYR Password: ");
            fgets(InputPassword, BUFSIZE07, stdin);
        }
        
        InputPassword[strlen(InputPassword) - 1] = '\0';
        LP = true;

        for (int i = 0; i < strlen(InputPassword); i++) {
            if (i == 0) { strcpy(HiddenPassword, "*"); }
            else        { strcat(HiddenPassword, "*"); }
        } strcpy(ALMInputs[GlobalRegisteredAccounts].Password, InputPassword);
        strcpy(ALMInputs[GlobalRegisteredAccounts].HiddenPasswordShown, HiddenPassword);
        AccountLoginMenu(ALMSelected);
    }
}

void AccountRecoveryMenu(int ACMSelected) {
    // TODO: Build a recovery menu interface.
}

void F1_MoneytoryTransactionsRegister(void) {
    // TODO: Build a transaction list interface.
}