// BEZ_compiler_bug.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdint>

typedef double			FpLong;

typedef FpLong			M_Float;

typedef struct {
	M_Float				x, y;
} M_Vector2;

#define	W_DEGREE 5			/*  Degree of eqn to find roots of */

/*
*  Bezier :
*	Evaluate a Bezier curve at a particular parameter value
*      Fill in control points for resulting sub-curves if "Left" and
*	"Right" are non-null.
*
*/
M_Vector2 Bezier(
	std::int32_t				degreeL,				/* Degree of bezier curve	*/
	const M_Vector2 	*pts,				/* Control pts			*/
	FpLong 				tF,					/* Parameter value		*/
	M_Vector2		 	*left_ptsA0,		/* RETURN left half ctl pts	*/
	M_Vector2 			*right_ptsA0)		/* RETURN right half ctl pts	*/
{
	std::int32_t 		i, j;		/* Index variables	*/
	M_Vector2 	Vtemp[W_DEGREE + 1][W_DEGREE + 1];

	/* Copy control points	*/
	for (j = 0; j <= degreeL; j++) {
		Vtemp[0][j] = pts[j];
	}

	/* Triangle computation	*/
	for (i = 1; i <= degreeL; i++) {
		for (j = 0; j <= degreeL - i; j++) {
			Vtemp[i][j].x =
				(1.0 - tF) * Vtemp[i - 1][j].x + tF * Vtemp[i - 1][j + 1].x;
			Vtemp[i][j].y =
				(1.0 - tF) * Vtemp[i - 1][j].y + tF * Vtemp[i - 1][j + 1].y;
		}
	}

	if (left_ptsA0 != NULL) {
		for (j = 0; j <= degreeL; j++) {
			left_ptsA0[j] = Vtemp[j][0];
		}
	}
	if (right_ptsA0 != NULL) {
		for (j = 0; j <= degreeL; j++) {
			right_ptsA0[j] = Vtemp[degreeL - j][j];
		}
	}

	return (Vtemp[degreeL][0]);
}

int _tmain(int argc, _TCHAR* argv[])
{
	M_Vector2 input[6] = {
		{ 0.00000000000000000, -232.77365083019993 },
		{ 0.20000000000000001, -36.493078186561959 },
		{ 0.40000000000000002, 121.70863250835092 },
		{ 0.59999999999999998, 333.60600310750453 },
		{ 0.80000000000000004, 516.81734961172151 },
		{ 1.0000000000000000, 705.56251619032480 }
	};

	M_Vector2 result = Bezier(5, input, 0.5f, 0, 0);

	printf("result: %.2f %.2f", result.x, result.y);

	return 0;
}

