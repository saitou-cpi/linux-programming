/* who2.c - /etc/utmpを読み出し、その中の情報のリストを表示する
 * 空レコードが出力されないようにし、時刻を適切に整形する
 */
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define SHOWHOST    /* 出力にリモートマシン名を組み込む */

void showtime(long);
void show_info(struct utmp *utbufp);

int main()
{
    struct utmp current_record;
    int utmpfd;
    ssize_t reclen = sizeof(current_record);

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);
        exit(1);
    }

    while( read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf) )
        show_info( &utbuf );
    close(utmpfd);
    return 0;

}

/*
 * show_info()
 * utmp構造体の内容を人間が読めるように表示する
 * *注意* サイズ情報をハードコードしてはならない
 */
void show_info(struct utmp *utbufp)
{
    if ( utbufp->ut_type != USER_PROCESS )
        return;

    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    printf("%10ld", utbufp->ut_time);
#ifdef SHOWHOST
    if ( utbufp->ut_host[0] != '\0' )
        printf("(%s)", utbufp->ut_host);
#endif
    printf("\n");
}

void showtime( long timeval )
/*
* 人間が理解しやすい形式で時刻を表示する。
* ctimeを使って文字列を組み立ててから、その一部を抜き出す
*
*
*/