#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

struct Point
{
    int x;
    int y;
};

void get_playfair_keymatrix(char *key, char keymatrix[SIZE][SIZE])
{
    int i, j, k, flag = 0, *arr;

    arr = (int *)calloc(26, sizeof(int));
    for (i = 0; i < strlen(key); i++)
    {
        if (key[i] != ' ')
        {
            if (arr[key[i] - 65] == 0)
            {
                keymatrix[flag / SIZE][flag % SIZE] = toupper(key[i]);
                arr[key[i] - 65] = 1;
                flag++;
            }
        }
    }

    for (i = 0, k = flag; i < 26; i++)
    {
        if (arr[i] == 0)
        {
            keymatrix[k / SIZE][k % SIZE] = (char)(i + 65);
            k++;
        }
    }
}

struct Point get_playfair_position(char keymatrix[SIZE][SIZE], char ch, struct Point *pos)
{
    if (ch == 'J')
        ch = 'I';

    int i, j;

    if (ch == ' ')
    {
        pos->x = -1;
        pos->y = -1;
    }

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (keymatrix[i][j] == ch)
            {
                pos->x = i;
                pos->y = j;
                break;
            }
        }
    }
}

void playfair_cipher_encrypt(char *plaintext, char *key)
{
    char keymatrix[SIZE][SIZE];
    get_playfair_keymatrix(key, keymatrix);

    int i, len = strlen(plaintext), j;
    struct Point pos1, pos2;

    for (i = 0; i < len; i += 2)
    {
        get_playfair_position(keymatrix, plaintext[i], &pos1);
        get_playfair_position(keymatrix, plaintext[i + 1], &pos2);

        if (pos1.x == pos2.x)
        {
            plaintext[i] = keymatrix[pos1.x][(pos1.y + 1) % SIZE];
            plaintext[i + 1] = keymatrix[pos2.x][(pos2.y + 1) % SIZE];
        }
        else if (pos1.y == pos2.y)
        {
            plaintext[i] = keymatrix[(pos1.x + 1) % SIZE][pos1.y];
            plaintext[i + 1] = keymatrix[(pos2.x + 1) % SIZE][pos2.y];
        }
        else
        {
            plaintext[i] = keymatrix[pos1.x][pos2.y];
            plaintext[i + 1] = keymatrix[pos2.x][pos1.y];
        }
    }
}

void playfair_cipher_decrypt(char *ciphertext, char *key)
{
    char keymatrix[SIZE][SIZE];
    get_playfair_keymatrix(key, keymatrix);

    int i, len = strlen(ciphertext), j;
    struct Point pos1, pos2;

    for (i = 0; i < len; i += 2)
    {
        get_playfair_position(keymatrix, ciphertext[i], &pos1);
        get_playfair_position(keymatrix, ciphertext[i + 1], &pos2);

        if (pos1.x == pos2.x)
        {
            ciphertext[i] = keymatrix[pos1.x][(pos1.y - 1 + SIZE) % SIZE];
            ciphertext[i + 1] = keymatrix[pos2.x][(pos2.y - 1 + SIZE) % SIZE];
        }
        else if (pos1.y == pos2.y)
        {
            ciphertext[i] = keymatrix[(pos1.x - 1 + SIZE) % SIZE][pos1.y];
            ciphertext[i + 1] = keymatrix[(pos2.x - 1 + SIZE) % SIZE][pos2.y];
        }
        else
        {
            ciphertext[i] = keymatrix[pos1.x][pos2.y];
            ciphertext[i + 1] = keymatrix[pos2.x][pos1.y];
        }
    }
}

int main()
{
    char plaintext[] = "HELLOWORLD";
    char key[] = "KEYWORD";

    printf("Original text: %s\n", plaintext);

    playfair_cipher_encrypt(plaintext, key);
    printf("Encrypted text: %s\n", plaintext);

    playfair_cipher_decrypt(plaintext, key);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}
