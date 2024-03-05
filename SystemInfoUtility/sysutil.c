#include <stdio.h>
#include <time.h>
#include <sys/sysinfo.h>

int main(int argc, char *argv[]) {
    
   printf("*****************************\n");
   printf("*** ACO350 - Cole Johnson ***\n");
   printf("***  System Info Utility  ***\n");
   printf("*****************************\n\n");
    
    time_t currentTime;
    time(&currentTime);
    
    struct tm *timeConverter = localtime(&currentTime);
    
    int dayOfWk = timeConverter->tm_wday;
    const char *day = "";
    switch (dayOfWk) {
        case 0:
            day = "Sunday";
            break;
        case 1:
            day = "Monday";
            break;
        case 2:
            day = "Tuesday";
            break;
        case 3:
            day = "Wednesday";
            break;
        case 4:
            day = "Thursday";
            break;
        case 5:
            day = "Friday";
            break;
        case 6:
            day = "Saturday";
            break;
        default:
            day = "";
            break;
    }
    
    int monthActual = timeConverter->tm_mon;
    const char *month = "";
    
    switch (monthActual) {
        case 0:
            month = "January";
            break;
        case 1:
            month = "February";
            break;
        case 2:
            month = "March";
            break;
        case 3:
            month = "April";
            break;
        case 4:
            month = "May";
            break;
        case 5:
            month = "June";
            break;
        case 6:
            month =  "July";
            break;
        case 7:
            month = "August";
            break;
        case 8:
            month = "September";
            break;
        case 9:
            month = "October";
            break;
        case 10:
            month = "November";
            break;
        case 11:
            month = "December";
            break;
        default:
            month = "";
            break;
    }
    
    printf("Current Date: %s, %s %d, %d\n", day, month, timeConverter->tm_mday, timeConverter-> tm_year + 1900);
    printf("Current Time: %.02d:%.02d:%.02d\n", timeConverter->tm_hour, timeConverter->tm_min, timeConverter->tm_sec);
    
    
    #define TO_MB(X) ((X) / 1000000.00)
    #define TO_GB(X) ((X) / 1000000000.000)
    
    struct sysinfo info;
    sysinfo(&info);
    
    printf("Last Reboot : %d seconds (%.2f days)\n\n", info.uptime, (info.uptime/86400.00));

    int configured = get_nprocs_conf();
    printf("Number of processors configured: %d\n", configured);
    
    int avail = get_nprocs();
    printf("Number of processors available : %d\n", avail);
    
    printf("Number of current processes    : %d\n\n", info.procs);
    
    
    
    
    printf("Total usable memory size: %.3f GB\n", TO_GB(info.totalram));
    
    printf("Available memory size   : %.3f GB\n", TO_GB(info.freeram));

    printf("Amount of shared memory : %.2f MB\n", info.sharedram); //only returns 12 bytes ~ feels weird
    
    float bufferMem = TO_MB(info.bufferram); //unsure why returning incorrect values
    printf("Memory used by buffers  : %.2f MB\n", bufferMem);
    
    float swapSpace = TO_MB(info.totalswap);
    printf("Total swap space size   : %.2f MB\n", swapSpace);
    
    float swapAvail = TO_MB(info.freeswap);
    printf("Swap space available    : %.2f MB\n", swapAvail);
    
    
    
   return 0;
}
