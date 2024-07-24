/* ls1.c
* 目的: ディレクトリ(複数の場合も含む)の内容をリストアップする
* 動作: 引数がない場合には、"."、そうでなければ引数のディレクトリ
* に含まれるファイルを出力する
*/
#include    <stdio.h>
#include    <sys/types.h>
#include    <dirent.h>

void do_ls(char []);

main(int ac, char *av[])
{
    if ( ac == 1 )
        do_ls( "." );
    else
        while ( --ac ){
            printf("%s:\n", *++av );
            do_ls( *av );
        }
}

void do_ls( char dirname[] )
/*
* dirnameというディレクトリのファイルをリストアップする
*/
{
    DIR *dir_ptr;
    struct dirent    *direntp;

    if ( ( dir_ptr = opendir( dirname ) ) == NULL )
        fprintf(stderr,"ls1: cannot open %s\n", diname);
    else{
        while ( ( dirname = readdir( dir_ptr ) ) != NULL )
            printf("%s\n", direntp->d_name );
        closedir(dir_ptr)
    }
}