/* who1.c - whoプログラムの最初のバージョン
 * utmpファイルをオープンし、読み出し結果を表示する
 */
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST    /* 出力にリモートマシン名を組み込む */

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

    while (read(utmpfd, &current_record, reclen) == reclen)
        show_info(&current_record);

    if (close(utmpfd) == -1) {
        perror("close");
        exit(1);
    }
    
    return 0;
}

/*
 * show_info()
 * utmp構造体の内容を人間が読めるように表示する
 * *注意* サイズ情報をハードコードしてはならない
 */
void show_info(struct utmp *utbufp)
{
    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    printf("%10ld", utbufp->ut_time);
    printf(" ");
#ifdef SHOWHOST
    printf("(%s)", utbufp->ut_host);
#endif
    printf("\n");
}
