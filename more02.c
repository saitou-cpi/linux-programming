/* more02.c - more version0.2
* ファイルを読みだして24行出力したら、一時停止して、つぎのコマンドを待つ
* バージョン0.2の機能：コマンドは/dev/ttyから読み出す
*/

#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more(FILE *);

int main( int ac , char *av[])
{
    FILE    *fp;

    if ( ac == 1 )
        do_more( stdin );
    else
        while ( --ac )
            if ( (fp = fopen( *++av , "r" )) != NULL )
            {
                do_more( fp );
                fclose( fp );
            }
            else
                exit(1);
    return 0;
}

void do_more( FILE *fp )
/*
 * PAGELEN行の情報を読み、see_more()を呼び出して命令を待つ
 */
 {
    char    line[LINELEN];
    int     num_of_lines = 0;
    int     see_more(FILE *), reply;
    FILE    *fp_tty;

    fp_tty = fopen( "/dev/tty", "r");
    if ( fp_tty == NULL )
        exit(1);

    while ( fgets( line, LINELEN, fp ) ){
        if ( num_of_lines == PAGELEN ) {
            reply = see_more(fp_tty);
            if ( reply == 0 )
                break;
            num_of_lines -= reply;
        }
        if ( fputs( line, stdout ) == EOF )
            exit(1);
        num_of_lines++;
    }
 }

 int see_more(FILE *cmd)
 /*
  * メッセージを出力して応答を待つ。先に進める行数を返す。
  * qならノー、スペースならイエス、CRなら1行
  */
  {
    int    c;

    printf("\033[7m more? \033[m");
    while ( (c=getc(cmd)) != EOF )
    {
        if ( c == 'q' )
            return 0;
        if ( c == ' ' )
            return PAGELEN;
        if ( c == '\n' )
            return 1;
    }
    return 0;
  }