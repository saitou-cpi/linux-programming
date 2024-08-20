/* play_again0.c
* 目的: ユーザーがほかのトランザクションを望んているかどうかを尋ねる
* 方法: 質問をしてイエス/ノーの回答を待つ
* 戻り値: 0=> イエス、　1=>ノー
* 改善点: いちいちEnterを押さなくても済むようにする
*/
#include <stdio.h>
#include <termios.h>
#define QUESTION "Do you want another transaction"

int get_response( char * );

int main()
{
    int response;

    response = get_response(QUESTION);  /* 何らかの答えを得る */
    return response;
}
int get_response(char *question)
/*
* 目的: 質問をしてイエス/ノーの回答を待つ
* 方法: getcharを使ってy/n以外の回答を無視する
* 戻り値: 0=> イエス、1=> ノー
*/
{
    printf("%s (y/n)?", question);
    while(1){
        switch( getchar() ){
            case 'y':
            case 'Y': return 0;
            case 'n':
            case 'N':
            case EOF: return 1;
        }
    }
}