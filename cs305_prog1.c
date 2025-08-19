#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* encrypt(char *text, int key) {
    int len = strlen(text);
    char *result = (char *) malloc ((len + 1) * sizeof(char)); 

    for (int i = 0; i < len; i++) 
    {
        char c = text[i];

        if (isupper(c)) 
        {
            result[i] = ((c - 'A' + key) % 26) + 'A';
        } 
        else if (islower(c)) 
        {
            result[i] = ((c - 'a' + key) % 26) + 'a';
        } 
        else 
        {
            result[i] = c; 
        }
    }

    result[len] = '\0'; 
    return result;
}

char* decrypt(char *text, int key) 
{
    return encrypt(text, 26 - (key % 26));
}

void newline_ignore(char* text)
{
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }
}

int main() {
    char text[1000];
    int key;
    char choice;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    newline_ignore(text);

    printf("The entered text is : %s\n", text);

    printf("Enter the key (0-25): ");
    scanf("%d", &key);

    char *result = NULL;

    result = encrypt(text, key);

    printf("The encrypted text is : %s\n", result);
    
    result = decrypt(result, key);

    printf("The decrypted text is : %s\n", result);

    free(result);
    return 0;
}
