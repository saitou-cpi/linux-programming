/* utmplib.c - utmp.cファイルからの読み出しをバッファリングする関数
*
* 含まれる関数はつぎのとおり
*    utmp_open( filename ) - ファイルをオープンする
*        エラーの時には-1を返す
*    utmp_next( )          - 次の構造体を指すポインタを返す
*        eofのときにはNULLを返す
*    utmp_close()          - ファイルを閉じる
* 一度の読み出しでNRECS個の構造体を読み出し、バッファから構造体を
* 1個ずつ提供する
*/
#include    <stdio.h>
#include    <stdlib.h>
#include    <sys/types.h>
#include    <utmp.h>

#define NRECS    16
#define NULLUT   ((struct utmp *)NULL)
#define UTSIZE   (sizeof(struct utmp))

static char    utmpbuf[NRECS * UTSIZE]; /* メモリ領域 */
static int     num_recs;                /* 格納してある個数 */
static int     cur_rec;                 /* 次のレコード番号 */
static int     fd_utmp = -1;            /* 読み出し元 */

utmp_open( char *filename )
{
    struct utmp *recp;

    if (fd_utmp == -1 )                 /* エラー？ */
        return NULLUT;
    if ( cur_rec==num_recs && utmp_reload()==0 )    /* まだ残っている？ */
        return NULLUT;
                                        /* 次のレコードのアドレスを取得する*/
    recp = ( struct utmp * ) &utmpbuf[cur_rec * UTSIZE];
    cur_rec++;
    return recp;
}

int utmp_reload()
/*
* バッファに、次のレコードのチャンクを読み出す
*/
{
    int    amt_read,

                                        /* 読みだしたバイト数 */
    amt_read = read( fd_utmp , utmpbuf, NRECS * UTSIZE );

                                        /* 何個得られたか？ */
    num_recs = amt_read/UTSIZE;
                                        /* ポインタをリセットする */
    cur_rec = 0;
    return num_recs;
}

utmp_close()
{
    if ( fd_utmp != -1 )                /* オープンされていなければ */
        close( fd_utmp );               /* クローズしない */
}