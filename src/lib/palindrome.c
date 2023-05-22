#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include <palindrome.h>

/* Функция processing обрабатывает переданное ей предложение до вида одного слова, без знаков препинания, пробелов, символов и в нижнем регистре
Возвращает длину получившейся строки */
int processing(wchar_t *text)
{
    wchar_t *buffer = malloc(sizeof(wchar_t) * MAX_LENGTH); // Динамическое выделение памяти под buffer

    int i = 0;
    int j = 0;

    while ( text[i] != '\0' )   // Если встречается конец строки
    {
        if ( iswalpha(text[i]) )    // Если text[i] - буква
        {
            buffer[j] = towlower(text[i]);
            j++;
        }
        else if ( iswdigit(text[i]) )   // Если text[i] - цифра
        {
            swprintf(&buffer[j], 2, L"%lc", text[i]);
            j++;
        }
        i++;
    }
    wmemcpy(text, buffer, sizeof(wchar_t) * (j - 1));   // Копируем значение buffer в text
    free(buffer);   // Освобождение памяти, выделенной под buffer
    return j;
}

/* Функция is_palindrome принимает строку и её длину, а затем проверяет её на свойство зеркальности
Возвращает 1, если строка зеркальна, иначе 0 */
int is_palindrome(wchar_t *text, int len)
{
    if ( len < 3 )
        return 0;
    for ( int i = 0; i < len / 2; i++ )
    {
        if ( text[i] != text[len - i - 1] ) // Попарное сравнение символов
            return 0;
    }
    return 1;
}

/* Функция split_file принимает название файла с текстом, после чего посимвольно его считывает в буффер, если встречает символ окончания 
предложения, то вызывает функцию processing, а затем is_palindrome, после чего очищает буффер и считывает новое предложение (если оно есть)
Возвращает 0, если файл обработан успешно, -1 если возникли ошибки */
int split_file(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if ( f == NULL )    // Если произошла ошибка при открытии файла
    {
        printf("Cannot open file\n");
        return -1;
    }
    int sentences = 0;

    while ( 1 )
    {
        wchar_t *buffer = malloc(sizeof(wchar_t) * MAX_LENGTH); 
        wchar_t *text = malloc(sizeof(wchar_t) * MAX_LENGTH);
        wchar_t ch;
        int i = 0;

        while ( 1 )
        {
            ch = fgetwc(f);
            if ( i >= MAX_LENGTH - 2 )  // Если длина предложения больше максимальной установленной
            {
                printf("Sentence is too large, max %d symbols\n", MAX_LENGTH);
                free(buffer);
                free(text);
                return -1;
            }
            if ( ch == '.' || ch == '?' || ch == '!' || ch == WEOF )    // Если ch - символ конца файла или предложения
                break;
            swprintf(&buffer[i], 2, L"%lc", ch);
            i++;
        }

        if ( ch == WEOF ) // Если ch - символ конца файла
        {
            free(buffer);
            free(text);
            break;
        }
        fgetwc(f);
        wmemcpy(text, buffer, sizeof(wchar_t) * (i + 1));   // Копируем содержимое buffer в text
        int len = processing(text);
        sentences++;
        if ( is_palindrome(text, len) )
            wprintf(L"%ls\n", buffer);
        free(buffer);
        free(text);
        i = 0;
    }

    if ( sentences ) // Если есть хоть одно предложение
        wprintf(L"\nOverall: %d sentences\n", sentences);   // Общее кол-во обработанных предложений
    else
        wprintf(L"File does not contain any sentences\n");
    return 0; 
}
