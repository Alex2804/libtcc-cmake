/****************************************************************************
**
** Copyright John Schember <john@nachtimwald.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of
** this software and associated documentation files (the "Software"), to deal in
** the Software without restriction, including without limitation the rights to
** use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
** of the Software, and to permit persons to whom the Software is furnished to do
** so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/

#include "../filesystem.h"

#include <string.h>
#include <stdio.h>

#include "../str_builder.h"
#include "../utility.h"

#ifdef _WIN32
# include <windows.h>
const char SEP = '\\';
#else
# include <sys/stat.h>
# include <sys/errno.h>
const char SEP = '/';
#endif

int atcc_create_dir_recursive(const char* path)
{
    str_builder_t* sb;
    char** parts;
    size_t i;
    int ret = 0;

    if (path == NULL || *path == '\0')
        return -1;

    parts = atcc_split_string(path, '/');
    if (parts == NULL || parts[0] == NULL) {
        atcc_free_splitted_string(parts);
        return -1;
    }

    sb = str_builder_create();
    i  = 0;
#ifdef _WIN32
    /* If the first part has a ':' it's a drive. E.g 'C:'. We don't
     * want to try creating it because we can't. We'll add it to base
     * and move forward. The next part will be a directory we need
     * to try creating. */
    if (strchr(parts[0], ':')) {
        i++;
        str_builder_add_str(sb, parts[0], strlen(parts[0]));
        str_builder_add_char(sb, SEP);
    }
#else
    if (*path == '/') {
        str_builder_add_char(sb, SEP);
    }
#endif

    for ( ; parts[i] != NULL; i++) {
        if (*(parts[i]) == '\0') {
            continue;
        }

        str_builder_add_str(sb, parts[i], strlen(parts[i]));
        str_builder_add_char(sb, SEP);

#ifdef _WIN32
        if (CreateDirectory(str_builder_peek(sb), NULL) == FALSE) {
            if (GetLastError() != ERROR_ALREADY_EXISTS) {
                ret = -1;
                goto done;
            }
        }
#else
        if (mkdir(str_builder_peek(sb), 0774) != 0)
            if (errno != EEXIST) {
                ret = -1;
                goto done;
            }
#endif
    }

    done:
    atcc_free_splitted_string(parts);
    str_builder_destroy(sb);
    return ret;
}
