/* play_again1.c
* 目的: ユーザーが他のトランザクションを望んでいるかどうかを尋ねる
* 方法: ttyをcrモードにして文字を読み、結果を返す
* 戻り値: 0=>イエス、　1=>ノー
* 改善点: 不適切な入力に対して、エコーを返さないようにする
*/
#include <stdio.h>
#include <termios.h>

#define QUESTION "Do you want another transaction?"

int get_response(char *question);
void set_crmode();
void tty_mode(int how);

int main()
{
    int response;

    tty_mode(0);                        /* ttyモードを保存 */
    set_crmode();                       /* crモードに設定 */
    response = get_response(QUESTION);  /* 回答を取得 */
    tty_mode(1);                        /* ttyモードを復元 */
    return response;
}

int get_response(char *question)
/*
* 目的: 質問をしてイエス/ノーの回答を得る
* 方法: getcharを使ってy/n以外の回答に文句を言う
* 戻り値: 0=>イエス、1=>ノー
*/
{
    int input;
    printf("%s (y/n)?", question);
    while(1){
        switch(input = getchar()){
            case 'y':
            case 'Y': return 0;
            case 'n':
            case 'N':
            case EOF: return 1;
            default:
                printf("\ncannot understand %c, ", input);
                printf("Please type y or n\n");
        }
    }
}

void set_crmode()
/*
* 目的: ファイルディスクリプタ0(標準入力)をcrモードにする
* 方法: termios のビットを操作する
*/
{
    struct termios ttystate;

    tcgetattr(0, &ttystate);            /* 現在の設定を読み出す */
    ttystate.c_lflag &= ~ICANON;        /* バッファリングなし */
    ttystate.c_cc[VMIN] = 1;            /* 一度に一文字ずつ取得する */
    tcsetattr(0, TCSANOW, &ttystate);   /* 設定を組み込む */
}

/* how == 0 =>現在のモードをセーブ, how == 1 =>モードを復元 */
void tty_mode(int how)
{
    static struct termios original_mode;
    if(how == 0)
        tcgetattr(0, &original_mode);   /* 現在のttyモードを保存 */
    else
        tcsetattr(0, TCSANOW, &original_mode); /* ttyモードを復元 */
}
