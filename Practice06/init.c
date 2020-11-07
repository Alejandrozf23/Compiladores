#include "hoc.h"
#include "y.tab.h"
extern double Log(), Log10(), Sqrt(), Exp(), integer ();

static struct /*Palabras clave*/
{
	char   *name;
	int    kval;
}
keywords[] =
{
	"_if",		IF,
	"else",		ELSE,
	"while",	WHILE,
	"print",	PRINT,
	"for", 		FOR,
	0,			0
};

static struct /*Constantes*/
{
	char *name;
	double cval;
}
consts[] =
{
	"PI",		3.14159265358979323846,
	"E",		2.71828182845904523536,
	"GAMMA",	0.57721566490153286060,  /* Euler */
	"DEG",		57.29577951308232087680,  /* grado/radian */
	"PHI",		1.6180339887498948*820,  /* proporcion dorada */
	0,			0
};

static struct /*	Predefinidos */
{
	char *name;
	complex *(*func)();
}
builtins[] =
{
	"sin",		complexSin,
	"cos",		complexCos,
	"atan",		complexTan,
	"log",		complexLog,
	"log10",	complexLog10,
	"exp",		complexExp,
	"sqrt",		complexSqrt,
	"abs",		complexAbs,
	"quit",		complexQuit,
	0,	0
};

void init()  /*instalar constantes y predefinidos en la tabla*/
{
	int i;
	Symbol *s;

	for (i = 0; keywords[i].name; i++)
		install(keywords[i].name, keywords[i].kval, 0.0, 0);
	for (i = 0; consts[i].name; i++)
		install(consts[i].name, VAR, consts[i].cval, 1);
	for (i = 0; builtins[i].name; i++)
	{
		s = install(builtins[i].name, BLTIN, 0.0, 0);
		s->u.ptr = builtins[i].func;
	}
}