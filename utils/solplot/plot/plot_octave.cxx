#include <octave/oct.h>     // Octave math functions related
#include <octave/octave.h>
#include <octave/parse.h>
#include <octave/toplev.h> /* do_octave_atexit */
#include <rtklib.h>         // for solbuf_t structure definition

void plotRTKtraj3d(solbuf_t *sol)
{
    int i,j;

    const char * argvv [] = {"" /* name of program, not relevant */, "--silent"};

    octave_main(2, (char **) argvv, true /**/);

    octave_value_list funcArg;

    /* Create a matrix with 4 rows(xyz stat or enu stat) and sol->n colums 
     * position(1, :) ------ ECEF x or ENU east
     * position(2, :) ------ ECEF y or ENU north
     * position(3, :) ------ ECEF z or ENU up
     * position(4, :) ------ GPS quality indicator
     * sol->n         ------ the number of solution
     */
    Matrix position(4, sol->n, double(0));

    /* fetch position data and put them into matrix */
    for(i=0; i<3; i++)
    {
        for(j=0; j<sol->n; j++)
        {
            position(i, j) = double(sol->data[j].rr[i]);
        }
    }
    /* fetch solution quality status and put them int matrix*/
    for(j=0; j<sol->n; j++)
        position(3, j) = sol->data[j].stat;

    funcArg(0) = position;

    const octave_value_list result = feval("octplotRTKtraj3d", funcArg, 1);
#ifdef DEBUG
//    fprintf(stderr, "position(0,0) = %f", position(0, 0));
#endif
//    clean_up_and_exit(0);
}
