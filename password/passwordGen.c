#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PWD_LEN 8

#define CONTAIN_LOWER 1 << 0
#define CONTAIN_UPPER 1 << 1
#define CONTAIN_NUM   1 << 2
#define CONTAIN_SIGN  1 << 3

#define CONTAIN_ALL (CONTAIN_LOWER | CONTAIN_UPPER | CONTAIN_NUM | CONTAIN_SIGN)

const char visibleChar[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%$'()*+,-./:;<=>?@[\\]^_`{|}~";
const int visCharLen = sizeof(visibleChar) / sizeof(char);

void clearArray(int *ary, int len)
{
    int idx = 0;
    for (; idx < len; idx++)
    {
        *(ary + idx) = 0;
    }
}

int main(int argc, char *argv)
{
    int complexCheck = 0;
    int dupChkIdx = 0;
    int idx = 0;
    int rnd = 0;
    int value = 0;
    int pwdIdx[PWD_LEN] = {0};
    char pwd[PWD_LEN + 1] = {0};

    srand(time(NULL));
    do
    {
        complexCheck = 0;
        idx = 0;
        clearArray(pwdIdx, PWD_LEN);

        do
        {
REGEN_IDX:
            rnd = rand() % visCharLen;
            for (dupChkIdx = 0; dupChkIdx < idx; dupChkIdx++)
            {
                if (pwdIdx[dupChkIdx] == rnd)
                {
                    goto REGEN_IDX;
                }
            }
            pwdIdx[idx] = rnd;
        } while (idx++ < PWD_LEN);

        for(idx = 0; idx < PWD_LEN; idx++)
        {
            value = pwdIdx[idx];
            if (value < 10) /* Number */
            {
                complexCheck |= CONTAIN_NUM;
            }
            else if (value < 36) /* lower */
            {
                complexCheck |= CONTAIN_LOWER;
            }
            else if (value < 62) /* upper */
            {
                complexCheck |= CONTAIN_UPPER;
            }
            else
            {
                complexCheck |= CONTAIN_SIGN;
            }
        }
    } while (complexCheck != CONTAIN_ALL);

    for (idx = 0; idx < PWD_LEN; idx++)
    {
        pwd[idx] = visibleChar[pwdIdx[idx]];
    }

    printf("%s\n", pwd);

    return EXIT_SUCCESS;
}
