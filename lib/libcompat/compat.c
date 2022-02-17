#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "compat.h"
#include "threads.h"

hrtime_t gethrtime(void)
{
	return 0;
}

hrtime_t gethrvtime(void)
{
	return 0;
}

size_t
strlcat(char *dst, const char *src, size_t dsize)
{
	const char *odst = dst;
	const char *osrc = src;
	size_t n = dsize;
	size_t dlen;

	/* Find the end of dst and adjust bytes left but don't go past end. */
	while (n-- != 0 && *dst != '\0')
		dst++;
	dlen = dst - odst;
	n = dsize - dlen;

	if (n-- == 0)
		return(dlen + strlen(src));
	while (*src != '\0') {
		if (n != 0) {
			*dst++ = *src;
			n--;
		}
		src++;
	}
	*dst = '\0';

	return(dlen + (src - osrc));	/* count does not include NUL */
}

size_t
strlcpy(char *dst, const char *src, size_t dsize)
{
	const char *osrc = src;
	size_t nleft = dsize;

	/* Copy as many bytes as will fit. */
	if (nleft != 0) {
		while (--nleft != 0) {
			if ((*dst++ = *src++) == '\0')
				break;
		}
	}

	/* Not enough room in dst, add NUL and traverse rest of src. */
	if (nleft == 0) {
		if (dsize != 0)
			*dst = '\0';		/* NUL-terminate dst */
		while (*src++)
			;
	}

	return(src - osrc - 1);	/* count does not include NUL */
}


static char *simplify(const char *str);

int
mkdirp(const char *d, mode_t mode)
{
	char  *endptr, *ptr, *slash, *str;

	str = simplify(d);

	/* If space couldn't be allocated for the simplified names, return. */

	if (str == NULL)
		return (-1);

		/* Try to make the directory */

	if (mkdir(str, mode) == 0) {
		free(str);
		return (0);
	}
	if (errno != ENOENT) {
		free(str);
		return (-1);
	}
	endptr = strrchr(str, '\0');
	slash = strrchr(str, '/');

		/* Search upward for the non-existing parent */

	while (slash != NULL) {

		ptr = slash;
		*ptr = '\0';

			/* If reached an existing parent, break */

		if (access(str, F_OK) == 0)
			break;

			/* If non-existing parent */

		else {
			slash = strrchr(str, '/');

				/* If under / or current directory, make it. */

			if (slash == NULL || slash == str) {
				if (mkdir(str, mode) != 0 && errno != EEXIST) {
					free(str);
					return (-1);
				}
				break;
			}
		}
	}

	/* Create directories starting from upmost non-existing parent */

	while ((ptr = strchr(str, '\0')) != endptr) {
		*ptr = '/';
		if (mkdir(str, mode) != 0 && errno != EEXIST) {
			/*
			 *  If the mkdir fails because str already
			 *  exists (EEXIST), then str has the form
			 *  "existing-dir/..", and this is really
			 *  ok. (Remember, this loop is creating the
			 *  portion of the path that didn't exist)
			 */
			free(str);
			return (-1);
		}
	}
	free(str);
	return (0);
}

/*
 *	simplify - given a pathname, simplify that path by removing
 *		   duplicate contiguous slashes.
 *
 *		   A simplified copy of the argument is returned to the
 *		   caller, or NULL is returned on error.
 *
 *		   The caller should handle error reporting based upon the
 *		   returned vlaue, and should free the returned value,
 *		   when appropriate.
 */

static char *
simplify(const char *str)
{
	int i;
	size_t mbPathlen;	/* length of multi-byte path */
	size_t wcPathlen;	/* length of wide-character path */
	wchar_t *wptr;		/* scratch pointer */
	wchar_t *wcPath;	/* wide-character version of the path */
	char *mbPath;		/* The copy fo the path to be returned */

	/*
	 *  bail out if there is nothing there.
	 */

	if (!str)
		return (NULL);

	/*
	 *  Get a copy of the argument.
	 */

	if ((mbPath = strdup(str)) == NULL) {
		return (NULL);
	}

	/*
	 *  convert the multi-byte version of the path to a
	 *  wide-character rendering, for doing our figuring.
	 */

	mbPathlen = strlen(mbPath);

	if ((wcPath = calloc(sizeof (wchar_t), mbPathlen+1)) == NULL) {
		free(mbPath);
		return (NULL);
	}

	if ((wcPathlen = mbstowcs(wcPath, mbPath, mbPathlen)) == (size_t)-1) {
		free(mbPath);
		free(wcPath);
		return (NULL);
	}

	/*
	 *  remove duplicate slashes first ("//../" -> "/")
	 */

	for (wptr = wcPath, i = 0; i < wcPathlen; i++) {
		*wptr++ = wcPath[i];

		if (wcPath[i] == '/') {
			i++;

			while (wcPath[i] == '/') {
				i++;
			}

			i--;
		}
	}

	*wptr = '\0';

	/*
	 *  now convert back to the multi-byte format.
	 */

	if (wcstombs(mbPath, wcPath, mbPathlen) == (size_t)-1) {
		free(mbPath);
		free(wcPath);
		return (NULL);
	}

	free(wcPath);
	return (mbPath);
}