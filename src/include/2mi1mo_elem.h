#include "kernel.h"
#include "matrix.h"


#ifndef _2MI1MO_ELEM_H
#define _2MI1MO_ELEM_H

#ifdef __cplusplus
extern "C"
{
#endif

	void matrix_opp2mi1mo(kernel *kernel_data, matrix *input_1, matrix *input_2, matrix *output_1, int *error);

#ifdef __cplusplus
}
#endif

#endif // MATRIX_ADD_H