/*
 * ufrtk.c -- User Functions related to RTK gps
 *
 * Author: Roice (LUO Bing)
 * Date:   2014-11-15 Create this file
 */

#include <rtklib.h>         // RTK-GPS related, readsol(), solbuf_t ...

int ReadSolutionFiles(char *files[], int nfile, solbuf_t *sol)
{
    int i, j;
    double origin_pos[3], origin_r[3], r[3];

    if (!readsol(files, nfile, sol))
    {
        fprintf(stderr, "Error: No solution!");
    }
     
    /* set the origin position to 39.10639N 117.17046E 20m*/
    origin_pos[0] = 39.10639*D2R;   // degree to rad
    origin_pos[1] = 117.17046*D2R;  // degree to rad
    origin_pos[3] = 20;             // meters
    /* compute the ENU coordinate of this point, convert llh to ecef*/
    /* origin_r contains the ecef result of origin point */
    pos2ecef(origin_pos, origin_r);

    for (j=0; j<3; j++)
        r[j] = origin_r[j];
    /* compute the ENU result of this origin point */
    /* origin_r contains the ENU result of this origin point */
    ecef2enu(origin_pos, r, origin_r);


    fprintf(stderr, "origin_r = %f, %f, %f\n", origin_r[0], origin_r[1], origin_r[2]);

    /* convert solution from ECEF to local ENU coordinate */
    for (i=0; i<sol->n; i++)
    {
        for (j=0; j<3; j++)
        {
            /* fetch the ecef vector */
            r[j] = sol->data[i].rr[j];
        }
        /* convert ecef to ENU */
        ecef2enu(origin_pos, r, &sol->data[i].rr[0]);
        for(j=0; j<3; j++)
        {
            /* convert ENU to local ENU */
            sol->data[i].rr[j] = sol->data[i].rr[j] - origin_r[j];
        }
    }
    return 1;
}
