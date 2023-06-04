#include <stdio.h>
#include <ctype.h>
#include <string.h>

void vigenere_cipher_encrypt(char *plaintext, char *key)
{
    int key_length = strlen(key);
    int key_index = 0;
    char *ptr = plaintext;

    while (*ptr != '\0')
    {
        if (isalpha(*ptr))
        {
            char ascii_offset = isupper(*ptr) ? 'A' : 'a';
            char key_char = toupper(key[key_index % key_length]);
            *ptr = ((*ptr - ascii_offset + (key_char - 'A')) % 26) + ascii_offset;
            key_index++;
        }
        ptr++;
    }
}

int main()
{
    char plaintext[100];
    char key[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    vigenere_cipher_encrypt(plaintext, key);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}
