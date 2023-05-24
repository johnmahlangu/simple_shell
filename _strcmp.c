#include "main.h"
/**
 * _strcmp - compare string
 * @s1: char1
 * @s2: char2
 * Return: compare
 */
int _strcmp(char *s1, char *s2)
{
        int i;
        int result;

        for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
        {
                if (s1[i] > s2[i])
                {
                        result = (s1[i] - s2[i]);
                        break;
                }
                else if (s2[i] > s1[i])
                {
                        result = (s1[i] - s2[i]);
                        break;
                }
                else
                {
                        result = (0);
                }
        }
        return (result);
}
