#include <stdio.h>
#include <stdlib.h>
#include <locale>
#define ENG 26
void encrypt(int k, char file1[80], char file2[80]), decrypt(int k, char file1[80], char file2[80]);

int main(int argc, char* argv[])
{
    char rew[] = "-encode";
    char reww[] = "-decode";
    char rewww[] = "-help";
    int k = atoi(argv[2]);
    if (_strcmpi(argv[1], rew) == 0) {
        printf("%i\n", k);
        encrypt(k, argv[3], argv[4]);
    }
    else if (_strcmpi(argv[1], reww) == 0)
        decrypt(k, argv[3], argv[4]);
    else if (_strcmpi(argv[1], rewww) == 0)
        printf("Help\n");
    return 0;
}

void encrypt(int k, char file1[80], char file2[80])
{
    FILE* fp1, * fp2;
    fopen_s(&fp1, file1, "r");
    if (fp1 == NULL)
        printf("Error:File1\n");
    else printf("File1 is opened\n");
    fopen_s(&fp2, file2, "w");
    if (fp2 == NULL)
        printf("Error:File2\n");
    else printf("File2 is opened\n");
    int flag;
    char c;
    c = getc(fp1);
    while (!feof(fp1))
    {
        flag = 0;
        if (c >= 'A' && c <= 'Z')
        {
            c = c + k;
            if (c > 'Z') c = 'A' + c - 'Z' - 1;
            fprintf(fp2, "%c", c);
            flag = 1;
        }
        if (c >= 'a' && c <= 'z')
        {
            c = c + k;
            if (c > 'z') c = 'a' + c - 'z' - 1;
            fprintf(fp2, "%c", c);
            flag = 1;
        }
        if (!flag) fprintf(fp2, "%c", c);
        c = getc(fp1);
    }
    fclose(fp1);
    fclose(fp2);
}

void decrypt(int k, char file1[80], char file2[80])
{
    FILE* fp1, * fp2;
    fopen_s(&fp1, file1, "r");
    if (fp1 == NULL)
        printf("Error:File1\n");
    else printf("File1 is opened\n");
    fopen_s(&fp2, file2, "w");
    if (fp2 == NULL)
        printf("Error:File2\n");
    else printf("File2 is opened\n");
    int flag;
    char c;
    c = getc(fp1);
    while (!feof(fp1))
    {
        flag = 0;
        if (c >= 'A' && c <= 'Z')
        {
            c = c - k;
            if (c < 'A') c = 'Z' + c - 'A' + 1;
            fprintf(fp2, "%c", c);
            flag = 1;
        }
        if (c >= 'a' && c <= 'z')
        {
            c = c - k;
            if (c < 'a') c = 'z' + c - 'a' + 1;
            fprintf(fp2, "%c", c);
            flag = 1;
        }
        if (!flag) fprintf(fp2, "%c", c);
        c = getc(fp1);
    }
    fclose(fp1);
    fclose(fp2);
}

