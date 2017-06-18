#ifdef __MINGW32__

char *stpcpy (char *dest, char *src)
{
  while ((*dest++ = *src++) != '\0')
    /* Do nothing. */ ;
  return dest - 1;
}

#endif
