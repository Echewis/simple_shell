void *our_strcpy(char *dest, const char *src)
{
    char *original = dest;

    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';
}