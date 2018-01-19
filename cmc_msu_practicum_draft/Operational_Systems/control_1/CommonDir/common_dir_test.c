#include<stdio.h>
#include<limits.h>

void
common_dir(const char *d1, const char *d2, char *out)
{
	char *slash = out + 1;
	for (*out++ = *d1++, d2++; *d1 != '\0' && *d2 != '\0' && *d1 == *d2; *out++ = *d1++, d2++)
		if (*d1 == '/') slash = out;
	if ((*d1 == '/' && *d2 == '\0') || (*d2 == '/' && *d1 == '\0') || (*d1 == *d2)) *out = '\0';
	else *slash = '\0';
}

int
main(int argc, char *argv[])
{
	if (argc < 3) {
		perror("not enough arguments");
		return 1;
	}
	char out[PATH_MAX];
	common_dir(argv[1], argv[2], out);
	printf("%s\n", out);
	return 0;
}
