/* rotate.c: a->b,b->c, .. z->aの変換を行う
* 目的: ttyモードを示すために役に立つ
*/
#include <stdio.h>
#include <ctype.h>
int main()
{
    int c;
    while ( ( c=getchar() ) != EOF ){
        if ( c == 'z' )
            c = 'a';
        else if (islower(c))
            c++;
        putchar(c);
    }
}