/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <time.h>

static const char default_rtc[] = "/dev/rtc0";
static int s_repeat_cnt = 1;

static void usage()
{
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "\t-h: show help message.\n");
    fprintf(stderr, "\t-c: test repeat times.\n");
    fprintf(stderr, "\t-d: rtc device.\n");
}

static void stop_ntp()
{
    fprintf(stderr, "Stopping NTP service ...\n");
    system("/etc/init.d/S50crontabs  stop");
}

static void start_ntp()
{
    fprintf(stderr, "Starting NTP service ...\n");
    system("/etc/init.d/S50crontabs  start");
}

static int rtc_read_tm(int fd, struct tm *ptm)
{
    int ret = 0;
    memset(ptm, 0, sizeof(*ptm));
    ret = ioctl(fd, RTC_RD_TIME, ptm);
    ptm->tm_isdst = -1; /* "not known" */
    return ret;
}

static int rtc_set_tm(int fd, struct tm *ptm)
{
    return ioctl(fd, RTC_SET_TIME, ptm);
}

static time_t rtc_tm2time(struct tm *ptm)
{
    time_t t;
    t = mktime(ptm);
    return t;
}

int main(int argc, char **argv)
{
    int fd, retval;
    unsigned long data;
    struct tm rtc_tm;
    const char *rtc_dev = default_rtc;
    struct timeval tv_start, tv_end;
    unsigned int test_cnt=0;
    int opt;
    time_t rtc_time;
    time_t saved_time1, saved_time2;
    time_t time_diff;
    int test_result = 0;

    while ((opt = getopt(argc, argv, "c:d:h")) != -1) {
        switch (opt) {
            case 'c': /*test repeat count*/
                s_repeat_cnt = atoi(optarg);
                if (s_repeat_cnt <= 0){
                    fprintf(stderr, "invalid repeat count: %d\n", s_repeat_cnt);
                    usage();
                }
                break;
            case 'd': /*rtc device*/
                rtc_dev = optarg;
                break;
            case 'h': /*help*/
            default:
                usage();
                return 1;
        }
    }

    fprintf(stderr, "Starting RTC Test ...\n");
    stop_ntp();
    fd = open(rtc_dev, O_RDONLY);
    if (fd ==  -1) {
        perror(rtc_dev);
        start_ntp();
        return -1;
    }

    fprintf(stderr, "Testing RTC driver on %s.\n", rtc_dev);
    do{
        test_cnt++;
        fprintf(stderr, "Testing Loop: %d\n", test_cnt);
        fprintf(stderr, "Test case 1:\n");
        /* Read the RTC time/date */
        retval = rtc_read_tm(fd, &rtc_tm);
        if (retval == -1) {
            perror("rtc_read_tm");
            fprintf(stderr, "[Failure] @line:%d", __LINE__);
            test_result = 0;
            break;
        }
        rtc_time = rtc_tm2time(&rtc_tm);

        fprintf(stderr, "Current RTC date/time is: \n\t%d-%d-%d, %02d:%02d:%02d.\n",
                rtc_tm.tm_year + 1900, rtc_tm.tm_mon + 1, rtc_tm.tm_mday,
                rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);

        rtc_time += 10;
        saved_time1 = rtc_time;
        localtime_r(&rtc_time, &rtc_tm);

        fprintf(stderr, "Setting RTC date/time to: \n\t%d-%d-%d, %02d:%02d:%02d.\n",
                rtc_tm.tm_year + 1900, rtc_tm.tm_mon + 1, rtc_tm.tm_mday,
                rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
        retval = rtc_set_tm(fd, &rtc_tm);
        if (retval == -1) {
            perror("rtc_set_tm");
            fprintf(stderr, "[Failure] @line:%d", __LINE__);
            test_result = 0;
            break;
        }
        fprintf(stderr, "Waiting 10s ...\n");
        usleep(10*1000*1000);
        retval = rtc_read_tm(fd, &rtc_tm);
        if (retval == -1) {
            perror("rtc_read_tm");
            fprintf(stderr, "[Failure] @line:%d", __LINE__);
            test_result = 0;
            break;
        }
        fprintf(stderr, "Current RTC date/time is: \n\t%d-%d-%d, %02d:%02d:%02d.\n",
                rtc_tm.tm_year + 1900, rtc_tm.tm_mon + 1, rtc_tm.tm_mday,
                rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
        rtc_time = rtc_tm2time(&rtc_tm);
        saved_time2 = rtc_time;
        time_diff = saved_time2 - saved_time1;
        fprintf(stderr, "saved_time1: %ld saved_time2:%ld\n", saved_time1, saved_time2);
        if (!(time_diff>=10 && time_diff <= 12)){
            fprintf(stderr, "[Failure] time_diff: %ld is not in range [10, 12]\n", time_diff);
            test_result = 0;
            break;
        }

        fprintf(stderr, "Test case 2:\n");
        /* Set the RTC time/date to: 2023/12/31 23:59:59*/
        rtc_tm.tm_sec  = 59;
        rtc_tm.tm_min  = 59;
        rtc_tm.tm_hour = 23;
        rtc_tm.tm_mday = 31;
        rtc_tm.tm_mon  = 11;
        rtc_tm.tm_year = 2023-1900;
        fprintf(stderr, "Setting RTC date/time to: %d-%d-%d, %02d:%02d:%02d.\n",
                rtc_tm.tm_year + 1900, rtc_tm.tm_mon + 1, rtc_tm.tm_mday,
                rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);

        retval = rtc_set_tm(fd, &rtc_tm);
        if (retval == -1) {
            perror("rtc_set_tm");
            fprintf(stderr, "[Failure] @line:%d", __LINE__);
            test_result = 0;
            break;
        }

        gettimeofday(&tv_start, NULL);
        fprintf(stderr, "After set current RTC date/time is %d-%d-%d, %02d:%02d:%02d.\n",
                rtc_tm.tm_year + 1900, rtc_tm.tm_mon + 1, rtc_tm.tm_mday,
                rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);

        /* Set the alarm to 15 sec in the future, and check for rollover */
        rtc_time = rtc_tm2time(&rtc_tm);
        saved_time1 = rtc_time;
        fprintf(stderr, "saved_time1: %ld @%d\n", saved_time1, __LINE__);
        rtc_time += 15;
        localtime_r(&rtc_time, &rtc_tm);

        retval = ioctl(fd, RTC_ALM_SET, &rtc_tm);
        if (retval == -1) {
            if (errno == ENOTTY) {
                fprintf(stderr, "Alarm IRQs not supported.\n");
            }
            perror("RTC_ALM_SET ioctl");
            fprintf(stderr, "[Failure] @line:%d", __LINE__);
            test_result = 0;
            break;
        }

        /* Read the current alarm settings */
        retval = ioctl(fd, RTC_ALM_READ, &rtc_tm);
        if (retval == -1) {
            perror("RTC_ALM_READ ioctl");
            fprintf(stderr, "[Failure] @line:%d", __LINE__);
            test_result = 0;
            break;
        }

        fprintf(stderr, "Alarm time now set to: %d-%d-%d, %02d:%02d:%02d.\n",
                rtc_tm.tm_year + 1900, rtc_tm.tm_mon + 1, rtc_tm.tm_mday,
                rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);

        /* Enable alarm interrupts */
        retval = ioctl(fd, RTC_AIE_ON, 0);
        if (retval == -1) {
            perror("RTC_AIE_ON ioctl");
            fprintf(stderr, "[Failure] @line:%d", __LINE__);
            test_result = 0;
            break;
        }

        fprintf(stderr, "Waiting 15 seconds for alarm...\n");
        fflush(stderr);
        /* This blocks until the alarm ring causes an interrupt */
        retval = read(fd, &data, sizeof(unsigned long));
        if (retval == -1) {
            perror("read");
            fprintf(stderr, "[Failure] @line:%d", __LINE__);
            test_result = 0;
            break;
        }
        gettimeofday(&tv_end, NULL);
        fprintf(stderr, "Alarm rang. System elapsed: %ldms\n", 
                (tv_end.tv_sec*1000 + tv_end.tv_usec/1000 - tv_start.tv_sec*1000 - tv_start.tv_usec/1000));

        retval = rtc_read_tm(fd, &rtc_tm);
        if (retval == -1) {
            perror("rtc_read_tm");
            fprintf(stderr, "[Failure] @line:%d", __LINE__);
            test_result = 0;
            break;
        }
        fprintf(stderr, "Current RTC date/time is: \n\t%d-%d-%d, %02d:%02d:%02d.\n",
                rtc_tm.tm_year + 1900, rtc_tm.tm_mon + 1, rtc_tm.tm_mday,
                rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
        rtc_time = rtc_tm2time(&rtc_tm);
        saved_time2 = rtc_time;
        fprintf(stderr, "saved_time1: %ld saved_time2:%ld\n", saved_time1, saved_time2);
        time_diff = saved_time2 - saved_time1;
        if (!(time_diff>=15 && time_diff <= 17)){
            fprintf(stderr, "[Failure] time_diff: %ld is not in range [15, 17]\n", time_diff);
            test_result = 0;
            break;
        }
        /* Disable alarm interrupts */
        retval = ioctl(fd, RTC_AIE_OFF, 0);
        if (retval == -1) {
            perror("RTC_AIE_OFF ioctl");
            fprintf(stderr, "[Failure] @line:%d", __LINE__);
            test_result = 0;
            break;
        }

        test_result = 1;

    }while(--s_repeat_cnt>0);

    if (test_result==1){
        fprintf(stderr, "*** Test complete : Success!!!***\n");
    }else{
        fprintf(stderr, "*** Test Failed!!!***\n");
    }
    close(fd);

    start_ntp();
    return -1;
}
