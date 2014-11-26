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

    /* Create a matrix with 3 rows(xyz or enu) and sol->n colums
     * sol->n is the number of solution */
    Matrix position(3, sol->n, double(0));

    /* fetch position data and put them into matrix */
    for(i=0; i<3; i++)
    {
        for(j=0; j<sol->n; j++)
        {
            position(i, j) = double(sol->data[j].rr[i]);
        }
    }

    funcArg(0) = position;

    const octave_value_list result = feval("octplotRTKtraj3d", funcArg, 1);
#ifdef DEBUG
    fprintf(stderr, "position(0,0) = %f", position(0, 0));
#endif
//    clean_up_and_exit(0);
}
