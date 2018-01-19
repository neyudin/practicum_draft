void
common_dir(const char *d1, const char *d2, char *out)
{
    char *slash = out + 1;
    for (*out++ = *d1++, d2++; *d1 != '\0' && *d2 != '\0' && *d1 == *d2; *out++ = *d1++, d2++)
        if (*d1 == '/') slash = out;
    if ((*d1 == '/' && *d2 == '\0') || (*d2 == '/' && *d1 == '\0') || (*d1 == *d2)) *out = '\0';
    else *slash = '\0';
}
