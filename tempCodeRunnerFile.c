#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int main(void) {
    time_t Time = time(NULL);
    struct tm ManageTime = *localtime(&Time);

    int DateOfMonths[12]      = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int DateOfMonths_LEAP[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int Date, Month, Year;
    
    while (1) {
        scanf("%d %d %d", &Date, &Month, &Year);

        size_t FinalDate  = (long long unsigned)(((1900 + Year) % 4 != 0) ? ((((Date + 30) - DateOfMonths[Month - 1]) != 0) ? ((Date + 30) - DateOfMonths[Month - 1]) : 31) : ((((Date + 30) - DateOfMonths_LEAP[Month - 1]) != 0) ? ((Date + 30) - DateOfMonths_LEAP[Month - 1]) : 31));
        size_t FinalMonth = (FinalDate != 31) ? ((Month != 12) ? (Month + 1) : 1) : ((Month == 12) ? (Month) : 1);
        size_t FinalYear  = (long long unsigned)((Month != 12) ? (Year) : (Year + 1));

        printf("%02lld-%02lld-%04lld\n", FinalDate, FinalMonth, FinalYear);

    } return 0;
}