#include <stdio.h>
#include <locale.h>

#include <palindrome.h>

int main(int argc, char **argv)
{
    if ( argc != 2 )    // Если количество аргументов не равно 2
    {
        printf("Usage: \n./palindrome name.txt\nwhere name.txt - name of file with text\n");
        return -1;
    }
    setlocale(LC_ALL, "");  // Устанавливаем локаль
    
    return split_file(argv[1]);
}
