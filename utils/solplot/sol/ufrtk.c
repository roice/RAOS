/*
 * ufrtk.c -- User Functions related to RTK gps
 *
 * Author: Roice (LUO Bing)
 * Date:   2014-11-15 Create this file
 */

#include <rtklib.h>         // RTK-GPS related, readsol(), solbuf_t ...

int ReadSolutionFiles(char *files[], int nfile, solbuf_t *sol)
{
    return readsol(files, nfile, sol);
}
