#include <stdio.h>
#include <stdlib.h>  // exitを使うために必要
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>  // strncpyを使うために必要
#include <unistd.h>  // chdirを使うために必要

ino_t get_inode(char *);
void printpathto(ino_t);
void inum_to_name(ino_t, char *, int);

int main()
{
    printpathto(get_inode("."));    /* ここまでのパスを出力する */
    putchar('\n');                  /* 最後に改行を追加する */
    return 0;
}

void printpathto(ino_t this_inode)
/*
* this_inodeに対応するディレクトリまでのパスを出力する
* 再帰関数
*/
{
    ino_t parent_inode;
    char its_name[BUFSIZ];

    if (get_inode("..") != this_inode) {
        if (chdir("..") == -1) {  // chdirのエラーチェックを追加
            perror("chdir");
            exit(1);
        }

        inum_to_name(this_inode, its_name, BUFSIZ);  /* 名前を取得 */

        parent_inode = get_inode(".");
        printpathto(parent_inode);  /* 再帰的に上のディレクトリまで辿る */

        printf("/%s", its_name);  /* このディレクトリの名前を出力 */
    } else {
        // ルートディレクトリに到達した場合
        printf("/");
    }
}

void inum_to_name(ino_t inode_to_find, char *namebuf, int buflen)
/*
* カレントディレクトリから引数のiノード番号を持つファイル
* ( サブディレクトリ )　を探し、名前をnamebufにコピーする
*/
{
    DIR *dir_ptr;                       /* ディレクトリ */
    struct dirent *direntp;             /* 各エントリ */

    if ((dir_ptr = opendir(".")) == NULL) {
        perror(".");
        exit(1);
    }

    /*
    * 指定されたiノード番号を持つファイル ( サブディレクトリ )を探す
    */
    while ((direntp = readdir(dir_ptr)) != NULL) {
        if (direntp->d_ino == inode_to_find) {
            snprintf(namebuf, buflen, "%s", direntp->d_name);
            closedir(dir_ptr);
            return;
        }
    }

    fprintf(stderr, "error looking for inode %lu\n", (unsigned long)inode_to_find);
    closedir(dir_ptr);
    exit(1);
}

ino_t get_inode(char *fname)
/*
* ファイルのiノード番号を返す
*/
{
    struct stat info;

    if (stat(fname, &info) == -1) {
        fprintf(stderr, "Cannot stat ");
        perror(fname);
        exit(1);
    }
    return info.st_ino;
}
