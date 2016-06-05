#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t my_timegm(struct tm *tm, char *Timezone)
{
    time_t ret;
    char *tz;

    tz = getenv("TZ");
    setenv("TZ", Timezone, 1);
    tzset();
    ret = mktime(tm);
    if (tz)
        setenv("TZ", tz, 1);
    else
        unsetenv("TZ");
    tzset();
    if (tm->tm_isdst)
        ret -= 3600;
    printf("Timezone[%s]time[%ld]dst[%d]\n", Timezone, ret, tm->tm_isdst);
    return ret;
}

int main(int argc, char **argv)
{
    time_t  now = time(NULL);
    struct tm Tm = {0};

    Tm.tm_year = 2016 - 1900;
    Tm.tm_mday = 5;
    Tm.tm_mon = 5;

    Tm.tm_hour = 17;
    Tm.tm_min = 0;
    Tm.tm_sec = 0;

    printf("Now[%ld]\n", now);
    my_timegm(&Tm, "Asia/Taipei");
    my_timegm(&Tm, "US/Eastern");

    return EXIT_SUCCESS;
}
