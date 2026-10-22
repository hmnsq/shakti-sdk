/*	A C version of Kahan's Floating Point Test "Paranoia"

			Thos Sumner, UCSF, Feb. 1985
			David Gay, BTL, Jan. 1986

	This is a rewrite from the Pascal version by

			B. A. Wichmann, 18 Jan. 1985

	(and does NOT exhibit good C programming style).

	Adjusted to use Standard C headers 19 Jan. 1992 (dmg);
	compile with -DKR_headers or insert
#define KR_headers
	at the beginning if you have an old-style C compiler.

(C) Apr 19 1983 in BASIC version by:
	Professor W. M. Kahan,
	567 Evans Hall
	Electrical Engineering & Computer Science Dept.
	University of California
	Berkeley, California 94720
	USA

converted to Pascal by:
	B. A. Wichmann
	National Physical Laboratory
	Teddington Middx
	TW11 OLW
	UK

converted to C by:

	David M. Gay		and	Thos Sumner
	AT&T Bell Labs			Computer Center, Rm. U-76
	600 Mountain Avenue		University of California
	Murray Hill, NJ 07974		San Francisco, CA 94143
	USA				USA

with simultaneous corrections to the Pascal source (reflected
in the Pascal source available over netlib).
[A couple of bug fixes from dgh = sun!dhough incorporated 31 July 1986.]

Reports of results on various systems from all the versions
of Paranoia are being collected by Richard Karpinski at the
same address as Thos Sumner.  This includes sample outputs,
bug reports, and criticisms.

You may copy this program freely if you acknowledge its source.
Comments on the Pascal version to NPL, please.


The C version catches signals from floating-point exceptions.
If signal(SIGFPE,...) is unavailable in your environment, you may
#define NOSIGNAL to comment out the invocations of signal.

This source file is too big for some C compilers, but may be split
into pieces.  Comments containing "SPLIT" suggest convenient places
for this splitting.  At the end of these comments is an "ed script"
(for the UNIX(tm) editor ed) that will do this splitting.

By #defining Single when you compile this source, you may obtain
a single-precision C version of Paranoia.


The following is from the introductory commentary from Wichmann's work:

The BASIC program of Kahan is written in Microsoft BASIC using many
facilities which have no exact analogy in Pascal.  The Pascal
version below cannot therefore be exactly the same.  Rather than be
a minimal transcription of the BASIC program, the Pascal coding
follows the conventional style of block-structured languages.  Hence
the Pascal version could be useful in producing versions in other
structured languages.

Rather than use identifiers of minimal length (which therefore have
little mnemonic significance), the Pascal version uses meaningful
identifiers as follows [Note: A few changes have been made for C]:


BASIC   C               BASIC   C               BASIC   C               

   A                       J                       S    StickyBit
   A1   AInverse           J0   NoErrors           T
   B    Radix                    [Failure]         T0   Underflow
   B1   BInverse           J1   NoErrors           T2   ThirtyTwo
   B2   RadixD2                  [SeriousDefect]   T5   OneAndHalf
   B9   BMinusU2           J2   NoErrors           T7   TwentySeven
   C                             [Defect]          T8   TwoForty
   C1   CInverse           J3   NoErrors           U    OneUlp
   D                             [Flaw]            U0   UnderflowThreshold
   D4   FourD              K    PageNo             U1
   E0                      L    Milestone          U2
   E1                      M                       V
   E2   Exp2               N                       V0
   E3                      N1                      V8
   E5   MinSqEr            O    Zero               V9
   E6   SqEr               O1   One                W
   E7   MaxSqEr            O2   Two                X
   E8                      O3   Three              X1
   E9                      O4   Four               X8
   F1   MinusOne           O5   Five               X9   Random1
   F2   Half               O8   Eight              Y
   F3   Third              O9   Nine               Y1
   F6                      P    Precision          Y2
   F9                      Q                       Y9   Random2
   G1   GMult              Q8                      Z
   G2   GDiv               Q9                      Z0   PseudoZero
   G3   GAddSub            R                       Z1
   H                       R1   RMult              Z2
   H1   HInverse           R2   RDiv               Z9
   I                       R3   RAddSub
   IO   NoTrials           R4   RSqrt
   I3   IEEE               R9   Random9

   SqRWrng

All the variables in BASIC are true variables and in consequence,
the program is more difficult to follow since the "constants" must
be determined (the glossary is very helpful).  The Pascal version
uses Real constants, but checks are added to ensure that the values
are correctly converted by the compiler.

The major textual change to the Pascal version apart from the
identifiersis that named procedures are used, inserting parameters
wherehelpful.  New procedures are also introduced.  The
correspondence is as follows:


BASIC       Pascal
lines 

  90- 140   Pause
 170- 250   Instructions
 380- 460   Heading
 480- 670   Characteristics
 690- 870   History
2940-2950   Random
3710-3740   NewD
4040-4080   DoesYequalX
4090-4110   PrintIfNPositive
4640-4850   TestPartialUnderflow

=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=

Below is an "ed script" that splits para.c into 10 files
of the form part[1-8].c, subs.c, and msgs.c, plus a header
file, paranoia.h, that these files require.

r paranoia.c
$
?SPLIT
 .d
+d
-,$w msgs.c
-,$d
?SPLIT
 .d
+d
-,$w subs.c
-,$d
?part8
+d
?include
 .,$w part8.c
 .,$d
-d
?part7
+d
?include
 .,$w part7.c
 .,$d
-d
?part6
+d
?include
 .,$w part6.c
 .,$d
-d
?part5
+d
?include
 .,$w part5.c
 .,$d
-d
?part4
+d
?include
 .,$w part4.c
 .,$d
-d
?part3
+d
?include
 .,$w part3.c
 .,$d
-d
?part2
+d
?include
 .,$w part2.c
 .,$d
?SPLIT
 .d
1,/^#include/-1d
1,$w part1.c
/Computed constants/,$d
1,$s/^int/extern &/
1,$s/^FLOAT/extern &/
1,$s/^char/extern &/
1,$s! = .*!;!
/^Guard/,/^Round/s/^/extern /
/^jmp_buf/s/^/extern /
/^Sig_type/s/^/extern /
s/$/\
extern void sigfpe(INT);/
w paranoia.h
q

*/

#ضمن <stdio.h>
#define NOSIGNAL
#define NOPAUSE
#ifndef NOSIGNAL
#ضمن <signal.h>
#endif
#ضمن <setjmp.h>
#ifdef Single
#define FLOAT عائم
#define FABS(x) (عائم)fabs((مزدوج)(x))
#define FLOOR(x) (عائم)floor((مزدوج)(x))
#define LOG(x) (عائم)log((مزدوج)(x))
#define POW(x,y) (عائم)pow((مزدوج)(x),(مزدوج)(y))
#define SQRT(x) (عائم)sqrt((مزدوج)(x))
#وإلا
#define FLOAT مزدوج
#define FABS(x) fabs(x)
#define FLOOR(x) floor(x)
#define LOG(x) log(x)
#define POW(x,y) pow(x,y)
#define SQRT(x) sqrt(x)
#endif

jmp_buf ovfl_buf;
#ifdef KR_headers
#define VOID /* void */
#define INT /* int */
#define FP /* FLOAT */
#define CHARP /* char * */
#define CHARPP /* char ** */
خارجي مزدوج fabs(), floor(), log(), pow(), sqrt();
خارجي فراغ exit();
تعريفنوع فراغ (*Sig_type)();
FLOAT Sign(), Random();
خارجي فراغ BadCond();
خارجي فراغ SqXMinX();
خارجي فراغ TstCond();
خارجي فراغ notify();
خارجي صحيح اقرأ();
#وإلا
#define VOID فراغ
#define INT صحيح
#define FP FLOAT
#define CHARP حرف *
#define CHARPP حرف **
#ifdef __STDC__
#ضمن <stdlib.h>
#ضمن <math.h>
#وإلا
#ifdef __cplusplus
خارجي "C" {
#endif
خارجي مزدوج fabs(مزدوج), floor(مزدوج), log(مزدوج);
خارجي مزدوج pow(مزدوج,مزدوج), sqrt(مزدوج);
خارجي فراغ exit(INT);
#ifdef __cplusplus
	}
#endif
#endif
تعريفنوع فراغ (*Sig_type)(صحيح);
FLOAT Sign(FLOAT), Random(فراغ);
خارجي فراغ BadCond(صحيح, حرف*);
خارجي فراغ SqXMinX(صحيح);
خارجي فراغ TstCond(صحيح, صحيح, حرف*);
خارجي فراغ notify(حرف*);
خارجي صحيح اقرأ(صحيح, حرف*, صحيح);
#endif
#undef V9
خارجي فراغ Characteristics(VOID);
خارجي فراغ Heading(VOID);
خارجي فراغ History(VOID);
خارجي فراغ Instructions(VOID);
خارجي فراغ IsYeqX(VOID);
خارجي فراغ NewD(VOID);
خارجي فراغ Pause(VOID);
خارجي فراغ PrintIfNPositive(VOID);
خارجي فراغ SR3750(VOID);
خارجي فراغ SR3980(VOID);
خارجي فراغ TstPtUf(VOID);

Sig_type sigsave;

#define KEYBOARD 0

FLOAT Radix, BInvrse, RadixD2, BMinusU2;

/*Small floating point constants.*/
FLOAT Zero = 0.0;
FLOAT Half = 0.5;
FLOAT One = 1.0;
FLOAT Two = 2.0;
FLOAT Three = 3.0;
FLOAT Four = 4.0;
FLOAT Five = 5.0;
FLOAT Eight = 8.0;
FLOAT Nine = 9.0;
FLOAT TwentySeven = 27.0;
FLOAT ThirtyTwo = 32.0;
FLOAT TwoForty = 240.0;
FLOAT MinusOne = -1.0;
FLOAT OneAndHalf = 1.5;
/*Integer constants*/
صحيح NoTrials = 20; /*Number of tests for commutativity. */
#define False 0
#define True 1

/* Definitions for declared types 
	Guard == (Yes, No);
	Rounding == (Chopped, Rounded, Other);
	Message == packed array [1..40] of char;
	Class == (Flaw, Defect, Serious, Failure);
	  */
#define Yes 1
#define No  0
#define Chopped 2
#define Rounded 1
#define Other   0
#define Flaw    3
#define Defect  2
#define Serious 1
#define Failure 0
تعريفنوع صحيح Guard, Rounding, Class;
تعريفنوع حرف Message;

/* Declarations of Variables */
صحيح Indx;
حرف ch[8];
FLOAT AInvrse, A1;
FLOAT C, CInvrse;
FLOAT D, FourD;
FLOAT E0, E1, Exp2, E3, MinSqEr;
FLOAT SqEr, MaxSqEr, E9;
FLOAT Third;
FLOAT F6, F9;
FLOAT H, HInvrse;
صحيح I;
FLOAT StickyBit, J;
FLOAT MyZero;
FLOAT Precision;
FLOAT Q, Q9;
FLOAT R, Random9;
FLOAT T, Underflow, S;
FLOAT OneUlp, UfThold, U1, U2;
FLOAT V, V0, V9;
FLOAT W;
FLOAT X, X1, X2, X8, Random1;
FLOAT Y, Y1, Y2, Random2;
FLOAT Z, PseudoZero, Z1, Z2, Z9;
صحيح ErrCnt[4];
صحيح fpecount;
صحيح Milestone;
صحيح PageNo;
صحيح M, N, N1;
Guard GMult, GDiv, GAddSub;
Rounding RMult, RDiv, RAddSub, RSqrt;
صحيح Break, Done, NotMonot, Monot, Anomaly, IEEE,
		SqRWrng, UfNGrad;
/* Computed constants. */
/*U1  gap below 1.0, i.e, 1.0-U1 is next number below 1.0 */
/*U2  gap above 1.0, i.e, 1.0+U2 is next number above 1.0 */

/* floating point exception receiver */
 فراغ
sigfpe(INT x)
{
	fpecount++;
	printf("\n* * * FLOATING-POINT ERROR %d * * *\n", x);
	fflush(stdout);
	𐡄𐡍 (sigsave) {
#ifndef NOSIGNAL
		إشارة(SIGFPE, sigsave);
#endif
		sigsave = 0;
		longjmp(ovfl_buf, 1);
		}
	exit(1);
}

main(VOID)
{
	/* First two assignments use integer right-hand sides. */
  uart_init();
	Zero = 0;
	One = 1;
	Two = One + One;
	Three = Two + One;
	Four = Three + One;
	Five = Four + One;
	Eight = Four + Four;
	Nine = Three * Three;
	TwentySeven = Nine * Three;
	ThirtyTwo = Four * Eight;
	TwoForty = Four * Five * Three * Four;
	MinusOne = -One;
	Half = One / Two;
	OneAndHalf = One + Half;
	ErrCnt[Failure] = 0;
	ErrCnt[Serious] = 0;
	ErrCnt[Defect] = 0;
	ErrCnt[Flaw] = 0;
	PageNo = 1;
	/*=============================================*/
	Milestone = 0;
	/*=============================================*/
#ifndef NOSIGNAL
	إشارة(SIGFPE, sigfpe);
#endif
	Instructions();
	Pause();
	Heading();
	Pause();
	Characteristics();
	Pause();
	History();
	Pause();
	/*=============================================*/
	Milestone = 7;
	/*=============================================*/
	printf("Program is now RUNNING tests on small integers:\n");
	
	TstCond (Failure, (Zero + Zero == Zero) && (One - One == Zero)
		   && (One > Zero) && (One + One == Two),
			"0+0 != 0, 1-1 != 0, 1 <= 0, or 1+1 != 2");
	Z = - Zero;
	𐡄𐡍 (Z != 0.0) {
		ErrCnt[Failure] = ErrCnt[Failure] + 1;
		printf("Comparison alleges that -0.0 is Non-zero!\n");
		U2 = 0.001;
		Radix = 1;
		TstPtUf();
		}
	TstCond (Failure, (Three == Two + One) && (Four == Three + One)
		   && (Four + Two * (- Two) == Zero)
		   && (Four - Three - One == Zero),
		   "3 != 2+1, 4 != 3+1, 4+2*(-2) != 0, or 4-3-1 != 0");
	TstCond (Failure, (MinusOne == (0 - One))
		   && (MinusOne + One == Zero ) && (One + MinusOne == Zero)
		   && (MinusOne + FABS(One) == Zero)
		   && (MinusOne + MinusOne * MinusOne == Zero),
		   "-1+1 != 0, (-1)+abs(1) != 0, or -1+(-1)*(-1) != 0");
	TstCond (Failure, Half + MinusOne + Half == Zero,
		  "1/2 + (-1) + 1/2 != 0");
	/*=============================================*/
	/*SPLIT
	{
		extern void part2(VOID), part3(VOID), part4(VOID),
			part5(VOID), part6(VOID), part7(VOID);
		int part8(VOID);

		part2();
		part3();
		part4();
		part5();
		part6();
		part7();
		return part8();
		}
	}
#include "paranoia.h"
void part2(VOID){
*/
	Milestone = 10;
	/*=============================================*/
	TstCond (Failure, (Nine == Three * Three)
		   && (TwentySeven == Nine * Three) && (Eight == Four + Four)
		   && (ThirtyTwo == Eight * Four)
		   && (ThirtyTwo - TwentySeven - Four - One == Zero),
		   "9 != 3*3, 27 != 9*3, 32 != 8*4, or 32-27-4-1 != 0");
	TstCond (Failure, (Five == Four + One) &&
			(TwoForty == Four * Five * Three * Four)
		   && (TwoForty / Three - Four * Four * Five == Zero)
		   && ( TwoForty / Four - Five * Three * Four == Zero)
		   && ( TwoForty / Five - Four * Three * Four == Zero),
		  "5 != 4+1, 240/3 != 80, 240/4 != 60, or 240/5 != 48");
	𐡄𐡍 (ErrCnt[Failure] == 0) {
		printf("-1, 0, 1/2, 1, 2, 3, 4, 5, 9, 27, 32 & 240 are O.K.\n");
		printf("\n");
		}
	printf("Searching for Radix and Precision.\n");
	W = One;
	𐡏𐡁𐡃  {
		W = W + W;
		Y = W + One;
		Z = Y - W;
		Y = Z - One;
		} طالما (MinusOne + FABS(Y) < Zero);
	/*.. now W is just big enough that |((W+1)-W)-1| >= 1 ...*/
	Precision = Zero;
	Y = One;
	𐡏𐡁𐡃  {
		Radix = W + Y;
		Y = Y + Y;
		Radix = Radix - W;
		} طالما ( Radix == Zero);
	𐡄𐡍 (Radix < Two) Radix = One;
	printf("Radix = %d .\n", Radix);
	𐡄𐡍 (Radix != 1) {
		W = One;
		𐡏𐡁𐡃  {
			Precision = Precision + One;
			W = W * Radix;
			Y = W + One;
			} طالما ((Y - W) == One);
		}
	/*... now W == Radix^Precision is barely too big to satisfy (W+1)-W == 1
			                              ...*/
	U1 = One / W;
	U2 = Radix * U1;
	printf("Closest relative separation found is U1 = %d .\n\n", U1);
	printf("Recalculating radix and precision\n ");
	
	/*save old values*/
	E0 = Radix;
	E1 = U1;
	E9 = U2;
	E3 = Precision;
	
	X = Four / Three;
	Third = X - One;
	F6 = Half - Third;
	X = F6 + F6;
	X = FABS(X - Third);
	𐡄𐡍 (X < U2) X = U2;
	
	/*... now X = (unknown no.) ulps of 1+...*/
	𐡏𐡁𐡃  {
		U2 = X;
		Y = Half * U2 + ThirtyTwo * U2 * U2;
		Y = One + Y;
		X = Y - One;
		} طالما ( ! ((U2 <= X) || (X <= Zero)));
	
	/*... now U2 == 1 ulp of 1 + ... */
	X = Two / Three;
	F6 = X - Half;
	Third = F6 + F6;
	X = Third - Half;
	X = FABS(X + F6);
	𐡄𐡍 (X < U1) X = U1;
	
	/*... now  X == (unknown no.) ulps of 1 -... */
	𐡏𐡁𐡃  {
		U1 = X;
		Y = Half * U1 + ThirtyTwo * U1 * U1;
		Y = Half - Y;
		X = Half + Y;
		Y = Half - X;
		X = Half + Y;
		} طالما ( ! ((U1 <= X) || (X <= Zero)));
	/*... now U1 == 1 ulp of 1 - ... */
	𐡄𐡍 (U1 == E1) printf("confirms closest relative separation U1 .\n");
	وإلا printf("gets better closest relative separation U1 = %d .\n", U1);
	W = One / U1;
	F9 = (Half - U1) + Half;
	Radix = FLOOR(0.01 + U2 / U1);
	𐡄𐡍 (Radix == E0) printf("Radix confirmed.\n");
	وإلا printf("MYSTERY: recalculated Radix = %d .\n", Radix);
	TstCond (Defect, Radix <= Eight + Eight,
		   "Radix is too big: roundoff problems");
	TstCond (Flaw, (Radix == Two) || (Radix == 10)
		   || (Radix == One), "Radix is not as good as 2 or 10");
	/*=============================================*/
	Milestone = 20;
	/*=============================================*/
	TstCond (Failure, F9 - Half < Half,
		   "(1-U1)-1/2 < 1/2 is FALSE, prog. fails?");
	X = F9;
	I = 1;
	Y = X - Half;
	Z = Y - Half;
	TstCond (Failure, (X != One)
		   || (Z == Zero), "Comparison is fuzzy,X=1 but X-1/2-1/2 != 0");
	X = One + U2;
	I = 0;
	/*=============================================*/
	Milestone = 25;
	/*=============================================*/
	/*... BMinusU2 = nextafter(Radix, 0) */
	BMinusU2 = Radix - One;
	BMinusU2 = (BMinusU2 - U2) + One;
	/* Purify Integers */
	𐡄𐡍 (Radix != One)  {
		X = - TwoForty * LOG(U1) / LOG(Radix);
		Y = FLOOR(Half + X);
		𐡄𐡍 (FABS(X - Y) * Four < One) X = Y;
		Precision = X / TwoForty;
		Y = FLOOR(Half + Precision);
		𐡄𐡍 (FABS(Precision - Y) * TwoForty < Half) Precision = Y;
		}
	𐡄𐡍 ((Precision != FLOOR(Precision)) || (Radix == One)) {
		printf("Precision cannot be characterized by an Integer number\n");
		printf("of significant digits but, by itself, this is a minor flaw.\n");
		}
	𐡄𐡍 (Radix == One) 
		printf("logarithmic encoding has precision characterized solely by U1.\n");
	وإلا printf("The number of significant digits of the Radix is %d .\n",
			Precision);
	TstCond (Serious, U2 * Nine * Nine * TwoForty < One,
		   "Precision worse than 5 decimal figures  ");
	/*=============================================*/
	Milestone = 30;
	/*=============================================*/
	/* Test for extra-precise subepressions */
	X = FABS(((Four / Three - One) - One / Four) * Three - One / Four);
	𐡏𐡁𐡃  {
		Z2 = X;
		X = (One + (Half * Z2 + ThirtyTwo * Z2 * Z2)) - One;
		} طالما ( ! ((Z2 <= X) || (X <= Zero)));
	X = Y = Z = FABS((Three / Four - Two / Three) * Three - One / Four);
	𐡏𐡁𐡃  {
		Z1 = Z;
		Z = (One / Two - ((One / Two - (Half * Z1 + ThirtyTwo * Z1 * Z1))
			+ One / Two)) + One / Two;
		} طالما ( ! ((Z1 <= Z) || (Z <= Zero)));
	𐡏𐡁𐡃  {
		𐡏𐡁𐡃  {
			Y1 = Y;
			Y = (Half - ((Half - (Half * Y1 + ThirtyTwo * Y1 * Y1)) + Half
				)) + Half;
			} طالما ( ! ((Y1 <= Y) || (Y <= Zero)));
		X1 = X;
		X = ((Half * X1 + ThirtyTwo * X1 * X1) - F9) + F9;
		} طالما ( ! ((X1 <= X) || (X <= Zero)));
	𐡄𐡍 ((X1 != Y1) || (X1 != Z1)) {
		BadCond(Serious, "Disagreements among the values X1, Y1, Z1,\n");
		printf("respectively  %d,  %016x,  %016x,\n", X1, Y1, Z1);
		printf("are symptoms of inconsistencies introduced\n");
		printf("by extra-precise evaluation of arithmetic subexpressions.\n");
		notify("Possibly some part of this");
		𐡄𐡍 ((X1 == U1) || (Y1 == U1) || (Z1 == U1))  printf(
			"That feature is not tested further by this program.\n") ;
		}
	وإلا  {
		𐡄𐡍 ((Z1 != U1) || (Z2 != U2)) {
			𐡄𐡍 ((Z1 >= U1) || (Z2 >= U2)) {
				BadCond(Failure, "");
				notify("Precision");
				printf("\tU1 = %d, Z1 - U1 = %016x\n",U1,Z1-U1);
				printf("\tU2 = %d, Z2 - U2 = %016x\n",U2,Z2-U2);
				}
			وإلا {
				𐡄𐡍 ((Z1 <= Zero) || (Z2 <= Zero)) {
					printf("Because of unusual Radix = %d", Radix);
					printf(", or exact rational arithmetic a result\n");
					printf("Z1 = %d, or Z2 = %016x ", Z1, Z2);
					notify("of an\nextra-precision");
					}
				𐡄𐡍 (Z1 != Z2 || Z1 > Zero) {
					X = Z1 / U1;
					Y = Z2 / U2;
					𐡄𐡍 (Y > X) X = Y;
					Q = - LOG(X);
					printf("Some subexpressions appear to be calculated extra\n");
					printf("precisely with about %d extra B-digits, i.e.\n",
						(Q / LOG(Radix)));
					printf("roughly %d extra significant decimals.\n",
						Q / LOG(10.));
					}
				printf("That feature is not tested further by this program.\n");
				}
			}
		}
	Pause();
	/*=============================================*/
	/*SPLIT
	}
#include "paranoia.h"
void part3(VOID){
*/
	Milestone = 35;
	/*=============================================*/
	𐡄𐡍 (Radix >= Two) {
		X = W / (Radix * Radix);
		Y = X + One;
		Z = Y - X;
		T = Z + U2;
		X = T - Z;
		TstCond (Failure, X == U2,
			"Subtraction is not normalized X=Y,X+Z != Y+Z!");
		𐡄𐡍 (X == U2) printf(
			"Subtraction appears to be normalized, as it should be.");
		}
	printf("\nChecking for guard digit in *, /, and -.\n");
	Y = F9 * One;
	Z = One * F9;
	X = F9 - Half;
	Y = (Y - Half) - X;
	Z = (Z - Half) - X;
	X = One + U2;
	T = X * Radix;
	R = Radix * X;
	X = T - Radix;
	X = X - Radix * U2;
	T = R - Radix;
	T = T - Radix * U2;
	X = X * (Radix - One);
	T = T * (Radix - One);
	𐡄𐡍 ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)) GMult = Yes;
	وإلا {
		GMult = No;
		TstCond (Serious, False,
			"* lacks a Guard Digit, so 1*X != X");
		}
	Z = Radix * U2;
	X = One + Z;
	Y = FABS((X + Z) - X * X) - U2;
	X = One - U2;
	Z = FABS((X - U2) - X * X) - U1;
	TstCond (Failure, (Y <= Zero)
		   && (Z <= Zero), "* gets too many final digits wrong.\n");
	Y = One - U2;
	X = One + U2;
	Z = One / Y;
	Y = Z - X;
	X = One / Three;
	Z = Three / Nine;
	X = X - Z;
	T = Nine / TwentySeven;
	Z = Z - T;
	TstCond(Defect, X == Zero && Y == Zero && Z == Zero,
		"Division lacks a Guard Digit, so error can exceed 1 ulp\n\
or  1/3  and  3/9  and  9/27 may disagree");
	Y = F9 / One;
	X = F9 - Half;
	Y = (Y - Half) - X;
	X = One + U2;
	T = X / One;
	X = T - X;
	𐡄𐡍 ((X == Zero) && (Y == Zero) && (Z == Zero)) GDiv = Yes;
	وإلا {
		GDiv = No;
		TstCond (Serious, False,
			"Division lacks a Guard Digit, so X/1 != X");
		}
	X = One / (One + U2);
	Y = X - Half - Half;
	TstCond (Serious, Y < Zero,
		   "Computed value of 1/1.000..1 >= 1");
	X = One - U2;
	Y = One + Radix * U2;
	Z = X * Radix;
	T = Y * Radix;
	R = Z / Radix;
	StickyBit = T / Radix;
	X = R - X;
	Y = StickyBit - Y;
	TstCond (Failure, X == Zero && Y == Zero,
			"* and/or / gets too many last digits wrong");
	Y = One - U1;
	X = One - F9;
	Y = One - Y;
	T = Radix - U2;
	Z = Radix - BMinusU2;
	T = Radix - T;
	𐡄𐡍 ((X == U1) && (Y == U1) && (Z == U2) && (T == U2)) GAddSub = Yes;
	وإلا {
		GAddSub = No;
		TstCond (Serious, False,
			"- lacks Guard Digit, so cancellation is obscured");
		}
	𐡄𐡍 (F9 != One && F9 - One >= Zero) {
		BadCond(Serious, "comparison alleges  (1-U1) < 1  although\n");
		printf("  subtraction yields  (1-U1) - 1 = 0 , thereby vitiating\n");
		printf("  such precautions against division by zero as\n");
		printf("  ...  if (X == 1.0) {.....} else {.../(X-1.0)...}\n");
		}
	𐡄𐡍 (GMult == Yes && GDiv == Yes && GAddSub == Yes) printf(
		"     *, /, and - appear to have guard digits, as they should.\n");
	/*=============================================*/
	Milestone = 40;
	/*=============================================*/
	Pause();
	printf("Checking rounding on multiply, divide and add/subtract.\n");
	RMult = Other;
	RDiv = Other;
	RAddSub = Other;
	RadixD2 = Radix / Two;
	A1 = Two;
	Done = False;
	𐡏𐡁𐡃  {
		AInvrse = Radix;
		𐡏𐡁𐡃  {
			X = AInvrse;
			AInvrse = AInvrse / A1;
			} طالما ( ! (FLOOR(AInvrse) != AInvrse));
		Done = (X == One) || (A1 > Three);
		𐡄𐡍 (! Done) A1 = Nine + One;
		} طالما ( ! (Done));
	𐡄𐡍 (X == One) A1 = Radix;
	AInvrse = One / A1;
	X = A1;
	Y = AInvrse;
	Done = False;
	𐡏𐡁𐡃  {
		Z = X * Y - Half;
		TstCond (Failure, Z == Half,
			"X * (1/X) differs from 1");
		Done = X == Radix;
		X = Radix;
		Y = One / X;
		} طالما ( ! (Done));
	Y2 = One + U2;
	Y1 = One - U2;
	X = OneAndHalf - U2;
	Y = OneAndHalf + U2;
	Z = (X - U2) * Y2;
	T = Y * Y1;
	Z = Z - X;
	T = T - X;
	X = X * Y2;
	Y = (Y + U2) * Y1;
	X = X - OneAndHalf;
	Y = Y - OneAndHalf;
	𐡄𐡍 ((X == Zero) && (Y == Zero) && (Z == Zero) && (T <= Zero)) {
		X = (OneAndHalf + U2) * Y2;
		Y = OneAndHalf - U2 - U2;
		Z = OneAndHalf + U2 + U2;
		T = (OneAndHalf - U2) * Y1;
		X = X - (Z + U2);
		StickyBit = Y * Y1;
		S = Z * Y2;
		T = T - Y;
		Y = (U2 - Y) + StickyBit;
		Z = S - (Z + U2 + U2);
		StickyBit = (Y2 + U2) * Y1;
		Y1 = Y2 * Y1;
		StickyBit = StickyBit - Y2;
		Y1 = Y1 - Half;
		𐡄𐡍 ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)
			&& ( StickyBit == Zero) && (Y1 == Half)) {
			RMult = Rounded;
			printf("Multiplication appears to round correctly.\n");
			}
		وإلا	𐡄𐡍 ((X + U2 == Zero) && (Y < Zero) && (Z + U2 == Zero)
				&& (T < Zero) && (StickyBit + U2 == Zero)
				&& (Y1 < Half)) {
				RMult = Chopped;
				printf("Multiplication appears to chop.\n");
				}
			وإلا printf("* is neither chopped nor correctly rounded.\n");
		𐡄𐡍 ((RMult == Rounded) && (GMult == No)) notify("Multiplication");
		}
	وإلا printf("* is neither chopped nor correctly rounded.\n");
	/*=============================================*/
	Milestone = 45;
	/*=============================================*/
	Y2 = One + U2;
	Y1 = One - U2;
	Z = OneAndHalf + U2 + U2;
	X = Z / Y2;
	T = OneAndHalf - U2 - U2;
	Y = (T - U2) / Y1;
	Z = (Z + U2) / Y2;
	X = X - OneAndHalf;
	Y = Y - T;
	T = T / Y1;
	Z = Z - (OneAndHalf + U2);
	T = (U2 - OneAndHalf) + T;
	𐡄𐡍 (! ((X > Zero) || (Y > Zero) || (Z > Zero) || (T > Zero))) {
		X = OneAndHalf / Y2;
		Y = OneAndHalf - U2;
		Z = OneAndHalf + U2;
		X = X - Y;
		T = OneAndHalf / Y1;
		Y = Y / Y1;
		T = T - (Z + U2);
		Y = Y - Z;
		Z = Z / Y2;
		Y1 = (Y2 + U2) / Y2;
		Z = Z - OneAndHalf;
		Y2 = Y1 - Y2;
		Y1 = (F9 - U1) / F9;
		𐡄𐡍 ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)
			&& (Y2 == Zero) && (Y2 == Zero)
			&& (Y1 - Half == F9 - Half )) {
			RDiv = Rounded;
			printf("Division appears to round correctly.\n");
			𐡄𐡍 (GDiv == No) notify("Division");
			}
		وإلا 𐡄𐡍 ((X < Zero) && (Y < Zero) && (Z < Zero) && (T < Zero)
			&& (Y2 < Zero) && (Y1 - Half < F9 - Half)) {
			RDiv = Chopped;
			printf("Division appears to chop.\n");
			}
		}
	𐡄𐡍 (RDiv == Other) printf("/ is neither chopped nor correctly rounded.\n");
	BInvrse = One / Radix;
	TstCond (Failure, (BInvrse * Radix - Half == Half),
		   "Radix * ( 1 / Radix ) differs from 1");
	/*=============================================*/
	/*SPLIT
	}
#include "paranoia.h"
void part4(VOID){
*/
	Milestone = 50;
	/*=============================================*/
	TstCond (Failure, ((F9 + U1) - Half == Half)
		   && ((BMinusU2 + U2 ) - One == Radix - One),
		   "Incomplete carry-propagation in Addition");
	X = One - U1 * U1;
	Y = One + U2 * (One - U2);
	Z = F9 - Half;
	X = (X - Half) - Z;
	Y = Y - One;
	𐡄𐡍 ((X == Zero) && (Y == Zero)) {
		RAddSub = Chopped;
		printf("Add/Subtract appears to be chopped.\n");
		}
	𐡄𐡍 (GAddSub == Yes) {
		X = (Half + U2) * U2;
		Y = (Half - U2) * U2;
		X = One + X;
		Y = One + Y;
		X = (One + U2) - X;
		Y = One - Y;
		𐡄𐡍 ((X == Zero) && (Y == Zero)) {
			X = (Half + U2) * U1;
			Y = (Half - U2) * U1;
			X = One - X;
			Y = One - Y;
			X = F9 - X;
			Y = One - Y;
			𐡄𐡍 ((X == Zero) && (Y == Zero)) {
				RAddSub = Rounded;
				printf("Addition/Subtraction appears to round correctly.\n");
				𐡄𐡍 (GAddSub == No) notify("Add/Subtract");
				}
			وإلا printf("Addition/Subtraction neither rounds nor chops.\n");
			}
		وإلا printf("Addition/Subtraction neither rounds nor chops.\n");
		}
	وإلا printf("Addition/Subtraction neither rounds nor chops.\n");
	S = One;
	X = One + Half * (One + Half);
	Y = (One + U2) * Half;
	Z = X - Y;
	T = Y - X;
	StickyBit = Z + T;
	𐡄𐡍 (StickyBit != Zero) {
		S = Zero;
		BadCond(Flaw, "(X - Y) + (Y - X) is non zero!\n");
		}
	StickyBit = Zero;
	𐡄𐡍 ((GMult == Yes) && (GDiv == Yes) && (GAddSub == Yes)
		&& (RMult == Rounded) && (RDiv == Rounded)
		&& (RAddSub == Rounded) && (FLOOR(RadixD2) == RadixD2)) {
		printf("Checking for sticky bit.\n");
		X = (Half + U1) * U2;
		Y = Half * U2;
		Z = One + Y;
		T = One + X;
		𐡄𐡍 ((Z - One <= Zero) && (T - One >= U2)) {
			Z = T + Y;
			Y = Z - X;
			𐡄𐡍 ((Z - T >= U2) && (Y - T == Zero)) {
				X = (Half + U1) * U1;
				Y = Half * U1;
				Z = One - Y;
				T = One - X;
				𐡄𐡍 ((Z - One == Zero) && (T - F9 == Zero)) {
					Z = (Half - U1) * U1;
					T = F9 - Z;
					Q = F9 - Y;
					𐡄𐡍 ((T - F9 == Zero) && (F9 - U1 - Q == Zero)) {
						Z = (One + U2) * OneAndHalf;
						T = (OneAndHalf + U2) - Z + U2;
						X = One + Half / Radix;
						Y = One + Radix * U2;
						Z = X * Y;
						𐡄𐡍 (T == Zero && X + Radix * U2 - Z == Zero) {
							𐡄𐡍 (Radix != Two) {
								X = Two + U2;
								Y = X / Two;
								𐡄𐡍 ((Y - One == Zero)) StickyBit = S;
								}
							وإلا StickyBit = S;
							}
						}
					}
				}
			}
		}
	𐡄𐡍 (StickyBit == One) printf("Sticky bit apparently used correctly.\n");
	وإلا printf("Sticky bit used incorrectly or not at all.\n");
	TstCond (Flaw, !(GMult == No || GDiv == No || GAddSub == No ||
			RMult == Other || RDiv == Other || RAddSub == Other),
		"lack(s) of guard digits or failure(s) to correctly round or chop\n\
(noted above) count as one flaw in the final tally below");
	/*=============================================*/
	Milestone = 60;
	/*=============================================*/
	printf("\n");
	printf("Does Multiplication commute?  ");
	printf("Testing on %d random pairs.\n", NoTrials);
	Random9 = SQRT(3.0);
	Random1 = Third;
	I = 1;
	𐡏𐡁𐡃  {
		X = Random();
		Y = Random();
		Z9 = Y * X;
		Z = X * Y;
		Z9 = Z - Z9;
		I = I + 1;
		} طالما ( ! ((I > NoTrials) || (Z9 != Zero)));
	𐡄𐡍 (I == NoTrials) {
		Random1 = One + Half / Three;
		Random2 = (U2 + U1) + One;
		Z = Random1 * Random2;
		Y = Random2 * Random1;
		Z9 = (One + Half / Three) * ((U2 + U1) + One) - (One + Half /
			Three) * ((U2 + U1) + One);
		}
	𐡄𐡍 (! ((I == NoTrials) || (Z9 == Zero)))
		BadCond(Defect, "X * Y == Y * X trial fails.\n");
	وإلا printf("     No failures found in %d integer pairs.\n", NoTrials);
	/*=============================================*/
	Milestone = 70;
	/*=============================================*/
	printf("\nRunning test of square root(x).\n");
	TstCond (Failure, (Zero == SQRT(Zero))
		   && (- Zero == SQRT(- Zero))
		   && (One == SQRT(One)), "Square root of 0.0, -0.0 or 1.0 wrong");
	MinSqEr = Zero;
	MaxSqEr = Zero;
	J = Zero;
	X = Radix;
	OneUlp = U2;
	SqXMinX (Serious);
	X = BInvrse;
	OneUlp = BInvrse * U1;
	SqXMinX (Serious);
	X = U1;
	OneUlp = U1 * U1;
	SqXMinX (Serious);
	𐡄𐡍 (J != Zero) Pause();
	printf("Testing if sqrt(X * X) == X for %d Integers X.\n", NoTrials);
	J = Zero;
	X = Two;
	Y = Radix;
	𐡄𐡍 ((Radix != One)) 𐡏𐡁𐡃  {
		X = Y;
		Y = Radix * Y;
		} طالما ( ! ((Y - X >= NoTrials)));
	OneUlp = X * U2;
	I = 1;
	طالما (I <= NoTrials) {
		X = X + One;
		SqXMinX (Defect);
		𐡄𐡍 (J > Zero) اكسر;
		I = I + 1;
		}
	printf("Test for sqrt monotonicity.\n");
	I = - 1;
	X = BMinusU2;
	Y = Radix;
	Z = Radix + Radix * U2;
	NotMonot = False;
	Monot = False;
	طالما ( ! (NotMonot || Monot)) {
		I = I + 1;
		X = SQRT(X);
		Q = SQRT(Y);
		Z = SQRT(Z);
		𐡄𐡍 ((X > Q) || (Q > Z)) NotMonot = True;
		وإلا {
			Q = FLOOR(Q + Half);
			𐡄𐡍 (!(I > 0 || Radix == Q * Q)) Monot = True;
			وإلا 𐡄𐡍 (I > 0) {
			𐡄𐡍 (I > 1) Monot = True;
			وإلا {
				Y = Y * BInvrse;
				X = Y - U1;
				Z = Y + U1;
				}
			}
			وإلا {
				Y = Q;
				X = Y - U2;
				Z = Y + U2;
				}
			}
		}
	𐡄𐡍 (Monot) printf("sqrt has passed a test for Monotonicity.\n");
	وإلا {
		BadCond(Defect, "");
		printf("sqrt(X) is non-monotonic for X near %d .\n", Y);
		}
	/*=============================================*/
	/*SPLIT
	}
#include "paranoia.h"
void part5(VOID){
*/
	Milestone = 80;
	/*=============================================*/
	MinSqEr = MinSqEr + Half;
	MaxSqEr = MaxSqEr - Half;
	Y = (SQRT(One + U2) - One) / U2;
	SqEr = (Y - One) + U2 / Eight;
	𐡄𐡍 (SqEr > MaxSqEr) MaxSqEr = SqEr;
	SqEr = Y + U2 / Eight;
	𐡄𐡍 (SqEr < MinSqEr) MinSqEr = SqEr;
	Y = ((SQRT(F9) - U2) - (One - U2)) / U1;
	SqEr = Y + U1 / Eight;
	𐡄𐡍 (SqEr > MaxSqEr) MaxSqEr = SqEr;
	SqEr = (Y + One) + U1 / Eight;
	𐡄𐡍 (SqEr < MinSqEr) MinSqEr = SqEr;
	OneUlp = U2;
	X = OneUlp;
	لكل( Indx = 1; Indx <= 3; ++Indx) {
		Y = SQRT((X + U1 + X) + F9);
		Y = ((Y - U2) - ((One - U2) + X)) / OneUlp;
		Z = ((U1 - X) + F9) * Half * X * X / OneUlp;
		SqEr = (Y + Half) + Z;
		𐡄𐡍 (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = (Y - Half) + Z;
		𐡄𐡍 (SqEr > MaxSqEr) MaxSqEr = SqEr;
		𐡄𐡍 (((Indx == 1) || (Indx == 3))) 
			X = OneUlp * Sign (X) * FLOOR(Eight / (Nine * SQRT(OneUlp)));
		وإلا {
			OneUlp = U1;
			X = - OneUlp;
			}
		}
	/*=============================================*/
	Milestone = 85;
	/*=============================================*/
	SqRWrng = False;
	Anomaly = False;
	RSqrt = Other; /* ~dgh */
	𐡄𐡍 (Radix != One) {
		printf("Testing whether sqrt is rounded or chopped.\n");
		D = FLOOR(Half + POW(Radix, One + Precision - FLOOR(Precision)));
	/* ... == Radix^(1 + fract) if (Precision == Integer + fract. */
		X = D / Radix;
		Y = D / A1;
		𐡄𐡍 ((X != FLOOR(X)) || (Y != FLOOR(Y))) {
			Anomaly = True;
			}
		وإلا {
			X = Zero;
			Z2 = X;
			Y = One;
			Y2 = Y;
			Z1 = Radix - One;
			FourD = Four * D;
			𐡏𐡁𐡃  {
				𐡄𐡍 (Y2 > Z2) {
					Q = Radix;
					Y1 = Y;
					𐡏𐡁𐡃  {
						X1 = FABS(Q + FLOOR(Half - Q / Y1) * Y1);
						Q = Y1;
						Y1 = X1;
						} طالما ( ! (X1 <= Zero));
					𐡄𐡍 (Q <= One) {
						Z2 = Y2;
						Z = Y;
						}
					}
				Y = Y + Two;
				X = X + Eight;
				Y2 = Y2 + X;
				𐡄𐡍 (Y2 >= FourD) Y2 = Y2 - FourD;
				} طالما ( ! (Y >= D));
			X8 = FourD - Z2;
			Q = (X8 + Z * Z) / FourD;
			X8 = X8 / Eight;
			𐡄𐡍 (Q != FLOOR(Q)) Anomaly = True;
			وإلا {
				Break = False;
				𐡏𐡁𐡃  {
					X = Z1 * Z;
					X = X - FLOOR(X / Radix) * Radix;
					𐡄𐡍 (X == One) 
						Break = True;
					وإلا
						Z1 = Z1 - One;
					} طالما ( ! (Break || (Z1 <= Zero)));
				𐡄𐡍 ((Z1 <= Zero) && (! Break)) Anomaly = True;
				وإلا {
					𐡄𐡍 (Z1 > RadixD2) Z1 = Z1 - Radix;
					𐡏𐡁𐡃  {
						NewD();
						} طالما ( ! (U2 * D >= F9));
					𐡄𐡍 (D * Radix - D != W - D) Anomaly = True;
					وإلا {
						Z2 = D;
						I = 0;
						Y = D + (One + Z) * Half;
						X = D + Z + Q;
						SR3750();
						Y = D + (One - Z) * Half + D;
						X = D - Z + D;
						X = X + Q + X;
						SR3750();
						NewD();
						𐡄𐡍 (D - Z2 != W - Z2) Anomaly = True;
						وإلا {
							Y = (D - Z2) + (Z2 + (One - Z) * Half);
							X = (D - Z2) + (Z2 - Z + Q);
							SR3750();
							Y = (One + Z) * Half;
							X = Q;
							SR3750();
							𐡄𐡍 (I == 0) Anomaly = True;
							}
						}
					}
				}
			}
		𐡄𐡍 ((I == 0) || Anomaly) {
			BadCond(Failure, "Anomalous arithmetic with Integer < ");
			printf("Radix^Precision = %d\n", W);
			printf(" fails test whether sqrt rounds or chops.\n");
			SqRWrng = True;
			}
		}
	𐡄𐡍 (! Anomaly) {
		𐡄𐡍 (! ((MinSqEr < Zero) || (MaxSqEr > Zero))) {
			RSqrt = Rounded;
			printf("Square root appears to be correctly rounded.\n");
			}
		وإلا  {
			𐡄𐡍 ((MaxSqEr + U2 > U2 - Half) || (MinSqEr > Half)
				|| (MinSqEr + Radix < Half)) SqRWrng = True;
			وإلا {
				RSqrt = Chopped;
				printf("Square root appears to be chopped.\n");
				}
			}
		}
	𐡄𐡍 (SqRWrng) {
		printf("Square root is neither chopped nor correctly rounded.\n");
		printf("Observed errors run from %d ", MinSqEr - Half);
		printf("to %d ulps.\n", Half + MaxSqEr);
		TstCond (Serious, MaxSqEr - MinSqEr < Radix * Radix,
			"sqrt gets too many last digits wrong");
		}
	/*=============================================*/
	Milestone = 90;
	/*=============================================*/
	Pause();
	printf("Testing powers Z^i for small Integers Z and i.\n");
	N = 0;
	/* ... test powers of zero. */
	I = 0;
	Z = -Zero;
	M = 3;
	Break = False;
	𐡏𐡁𐡃  {
		X = One;
		SR3980();
		𐡄𐡍 (I <= 10) {
			I = 1023;
			SR3980();
			}
		𐡄𐡍 (Z == MinusOne) Break = True;
		وإلا {
			Z = MinusOne;
			/* .. if(-1)^N is invalid, replace MinusOne by One. */
			I = - 4;
			}
		} طالما ( ! Break);
	PrintIfNPositive();
	N1 = N;
	N = 0;
	Z = A1;
	M = (صحيح)FLOOR(Two * LOG(W) / LOG(A1));
	Break = False;
	𐡏𐡁𐡃  {
		X = Z;
		I = 1;
		SR3980();
		𐡄𐡍 (Z == AInvrse) Break = True;
		وإلا Z = AInvrse;
		} طالما ( ! (Break));
	/*=============================================*/
		Milestone = 100;
	/*=============================================*/
	/*  Powers of Radix have been tested, */
	/*         next try a few primes     */
	M = NoTrials;
	Z = Three;
	𐡏𐡁𐡃  {
		X = Z;
		I = 1;
		SR3980();
		𐡏𐡁𐡃  {
			Z = Z + Two;
			} طالما ( Three * FLOOR(Z / Three) == Z );
		} طالما ( Z < Eight * Three );
	𐡄𐡍 (N > 0) {
		printf("Errors like this may invalidate financial calculations\n");
		printf("\tinvolving interest rates.\n");
		}
	PrintIfNPositive();
	N += N1;
	𐡄𐡍 (N == 0) printf("... no discrepancies found.\n");
	𐡄𐡍 (N > 0) Pause();
	وإلا printf("\n");
	/*=============================================*/
	/*SPLIT
	}
#include "paranoia.h"
void part6(VOID){
*/
	Milestone = 110;
	/*=============================================*/
	printf("Seeking Underflow thresholds UfThold and E0.\n");
	D = U1;
	𐡄𐡍 (Precision != FLOOR(Precision)) {
		D = BInvrse;
		X = Precision;
		𐡏𐡁𐡃  {
			D = D * BInvrse;
			X = X - One;
			} طالما ( X > Zero);
		}
	Y = One;
	Z = D;
	/* ... D is power of 1/Radix < 1. */
	𐡏𐡁𐡃  {
		C = Y;
		Y = Z;
		Z = Y * Y;
		} طالما ((Y > Z) && (Z + Z > Z));
	Y = C;
	Z = Y * D;
	𐡏𐡁𐡃  {
		C = Y;
		Y = Z;
		Z = Y * D;
		} طالما ((Y > Z) && (Z + Z > Z));
	𐡄𐡍 (Radix < Two) HInvrse = Two;
	وإلا HInvrse = Radix;
	H = One / HInvrse;
	/* ... 1/HInvrse == H == Min(1/Radix, 1/2) */
	CInvrse = One / C;
	E0 = C;
	Z = E0 * H;
	/* ...1/Radix^(BIG Integer) << 1 << CInvrse == 1/C */
	𐡏𐡁𐡃  {
		Y = E0;
		E0 = Z;
		Z = E0 * H;
		} طالما ((E0 > Z) && (Z + Z > Z));
	UfThold = E0;
	E1 = Zero;
	Q = Zero;
	E9 = U2;
	S = One + E9;
	D = C * S;
	𐡄𐡍 (D <= C) {
		E9 = Radix * U2;
		S = One + E9;
		D = C * S;
		𐡄𐡍 (D <= C) {
			BadCond(Failure, "multiplication gets too many last digits wrong.\n");
			Underflow = E0;
			Y1 = Zero;
			PseudoZero = Z;
			Pause();
			}
		}
	وإلا {
		Underflow = D;
		PseudoZero = Underflow * H;
		UfThold = Zero;
		𐡏𐡁𐡃  {
			Y1 = Underflow;
			Underflow = PseudoZero;
			𐡄𐡍 (E1 + E1 <= E1) {
				Y2 = Underflow * HInvrse;
				E1 = FABS(Y1 - Y2);
				Q = Y1;
				𐡄𐡍 ((UfThold == Zero) && (Y1 != Y2)) UfThold = Y1;
				}
			PseudoZero = PseudoZero * H;
			} طالما ((Underflow > PseudoZero)
				&& (PseudoZero + PseudoZero > PseudoZero));
		}
	/* Comment line 4530 .. 4560 */
	𐡄𐡍 (PseudoZero != Zero) {
		printf("\n");
		Z = PseudoZero;
	/* ... Test PseudoZero for "phoney- zero" violates */
	/* ... PseudoZero < Underflow or PseudoZero < PseudoZero + PseudoZero
		   ... */
		𐡄𐡍 (PseudoZero <= Zero) {
			BadCond(Failure, "Positive expressions can underflow to an\n");
			printf("allegedly negative value\n");
			printf("PseudoZero that prints out as: %d .\n", PseudoZero);
			X = - PseudoZero;
			𐡄𐡍 (X <= Zero) {
				printf("But -PseudoZero, which should be\n");
				printf("positive, isn't; it prints out as  %d .\n", X);
				}
			}
		وإلا {
			BadCond(Flaw, "Underflow can stick at an allegedly positive\n");
			printf("value PseudoZero that prints out as %d .\n", PseudoZero);
			}
		TstPtUf();
		}
	/*=============================================*/
	Milestone = 120;
	/*=============================================*/
	𐡄𐡍 (CInvrse * Y > CInvrse * Y1) {
		S = H * S;
		E0 = Underflow;
		}
	𐡄𐡍 (! ((E1 == Zero) || (E1 == E0))) {
		BadCond(Defect, "");
		𐡄𐡍 (E1 < E0) {
			printf("Products underflow at a higher");
			printf(" threshold than differences.\n");
			𐡄𐡍 (PseudoZero == Zero) 
			E0 = E1;
			}
		وإلا {
			printf("Difference underflows at a higher");
			printf(" threshold than products.\n");
			}
		}
	printf("Smallest strictly positive number found is E0 = %d .\n", E0);
	Z = E0;
	TstPtUf();
	Underflow = E0;
	𐡄𐡍 (N == 1) Underflow = Y;
	I = 4;
	𐡄𐡍 (E1 == Zero) I = 3;
	𐡄𐡍 (UfThold == Zero) I = I - 2;
	UfNGrad = True;
	بدل (I)  {
		حالة	1:
		UfThold = Underflow;
		𐡄𐡍 ((CInvrse * Q) != ((CInvrse * Y) * S)) {
			UfThold = Y;
			BadCond(Failure, "Either accuracy deteriorates as numbers\n");
			printf("approach a threshold = %d\n", UfThold);;
			printf(" coming down from %d\n", C);
			printf(" or else multiplication gets too many last digits wrong.\n");
			}
		Pause();
		اكسر;
	
		حالة	2:
		BadCond(Failure, "Underflow confuses Comparison, which alleges that\n");
		printf("Q == Y while denying that |Q - Y| == 0; these values\n");
		printf("print out as Q = %d, Y = %016x .\n", Q, Y2);
		printf ("|Q - Y| = %d .\n" , FABS(Q - Y2));
		UfThold = Q;
		اكسر;
	
		حالة	3:
		X = X;
		اكسر;
	
		حالة	4:
		𐡄𐡍 ((Q == UfThold) && (E1 == E0)
			&& (FABS( UfThold - E1 / E9) <= E1)) {
			UfNGrad = False;
			printf("Underflow is gradual; it incurs Absolute Error =\n");
			printf("(roundoff in UfThold) < E0.\n");
			Y = E0 * CInvrse;
			Y = Y * (OneAndHalf + U2);
			X = CInvrse * (One + U2);
			Y = Y / X;
			IEEE = (Y == E0);
			}
		}
	𐡄𐡍 (UfNGrad) {
		printf("\n");
		sigsave = sigfpe;
		𐡄𐡍 (setjmp(ovfl_buf)) {
			printf("Underflow / UfThold failed!\n");
			R = H + H;
			}
		وإلا R = SQRT(Underflow / UfThold);
		sigsave = 0;
		𐡄𐡍 (R <= H) {
			Z = R * UfThold;
			X = Z * (One + R * H * (One + H));
			}
		وإلا {
			Z = UfThold;
			X = Z * (One + H * H * (One + H));
			}
		𐡄𐡍 (! ((X == Z) || (X - Z != Zero))) {
			BadCond(Flaw, "");
			printf("X = %d\n\tis not equal to Z = %016x .\n", X, Z);
			Z9 = X - Z;
			printf("yet X - Z yields %d .\n", Z9);
			printf("    Should this NOT signal Underflow, ");
			printf("this is a SERIOUS DEFECT\nthat causes ");
			printf("confusion when innocent statements like\n");;
			printf("    if (X == Z)  ...  else");
			printf("  ... (f(X) - f(Z)) / (X - Z) ...\n");
			printf("encounter Division by Zero although actually\n");
			sigsave = sigfpe;
			𐡄𐡍 (setjmp(ovfl_buf)) printf("X / Z fails!\n");
			وإلا printf("X / Z = 1 + %d .\n", (X / Z - Half) - Half);
			sigsave = 0;
			}
		}
	printf("The Underflow threshold is %d, %s\n", UfThold,
		   " below which");
	printf("calculation may suffer larger Relative error than ");
	printf("merely roundoff.\n");
	Y2 = U1 * U1;
	Y = Y2 * Y2;
	Y2 = Y * U1;
	𐡄𐡍 (Y2 <= UfThold) {
		𐡄𐡍 (Y > E0) {
			BadCond(Defect, "");
			I = 5;
			}
		وإلا {
			BadCond(Serious, "");
			I = 4;
			}
		printf("Range is too narrow; U1^%d Underflows.\n", I);
		}
	/*=============================================*/
	/*SPLIT
	}
#include "paranoia.h"
void part7(VOID){
*/
	Milestone = 130;
	/*=============================================*/
	Y = - FLOOR(Half - TwoForty * LOG(UfThold) / LOG(HInvrse)) / TwoForty;
	Y2 = Y + Y;
	printf("Since underflow occurs below the threshold\n");
	printf("UfThold = (%d) ^ (%016x)\nonly underflow ", HInvrse, Y);
	printf("should afflict the expression\n\t(%d) ^ (%016x);\n",
		HInvrse, Y2);
	printf("actually calculating yields:");
	𐡄𐡍 (setjmp(ovfl_buf)) {
		sigsave = 0;
		BadCond(Serious, "trap on underflow.\n");
		}
	وإلا {
		sigsave = sigfpe;
		V9 = POW(HInvrse, Y2);
		sigsave = 0;
		printf(" %d .\n", V9);
		𐡄𐡍 (! ((V9 >= Zero) && (V9 <= (Radix + Radix + E9) * UfThold))) {
			BadCond(Serious, "this is not between 0 and underflow\n");
		printf("   threshold = %d .\n", UfThold);
		}
		وإلا 𐡄𐡍 (! (V9 > UfThold * (One + E9)))
			printf("This computed value is O.K.\n");
		وإلا {
			BadCond(Defect, "this is not between 0 and underflow\n");
			printf("   threshold = %d .\n", UfThold);
			}
		}
	/*=============================================*/
	Milestone = 140;
	/*=============================================*/
	printf("\n");
	/* ...calculate Exp2 == exp(2) == 7.389056099... */
	X = Zero;
	I = 2;
	Y = Two * Three;
	Q = Zero;
	N = 0;
	𐡏𐡁𐡃  {
		Z = X;
		I = I + 1;
		Y = Y / (I + I);
		R = Y + Q;
		X = Z + R;
		Q = (Z - X) + R;
		} طالما(X > Z);
	Z = (OneAndHalf + One / Eight) + X / (OneAndHalf * ThirtyTwo);
	X = Z * Z;
	Exp2 = X * X;
	X = F9;
	Y = X - U1;
	printf("Testing X^((X + 1) / (X - 1)) vs. exp(2) = %d as X -> 1.\n",
		Exp2);
	لكل(I = 1;;) {
		Z = X - BInvrse;
		Z = (X + One) / (Z - (One - BInvrse));
		Q = POW(X, Z) - Exp2;
		𐡄𐡍 (FABS(Q) > TwoForty * U2) {
			N = 1;
	 		V9 = (X - BInvrse) - (One - BInvrse);
			BadCond(Defect, "Calculated");
			printf(" %d for\n", POW(X,Z));
			printf("\t(1 + (%d) ^ (%016x);\n", V9, Z);
			printf("\tdiffers from correct value by %d .\n", Q);
			printf("\tThis much error may spoil financial\n");
			printf("\tcalculations involving tiny interest rates.\n");
			اكسر;
			}
		وإلا {
			Z = (Y - X) * Two + Y;
			X = Y;
			Y = Z;
			Z = One + (X - F9)*(X - F9);
			𐡄𐡍 (Z > One && I < NoTrials) I++;
			وإلا  {
				𐡄𐡍 (X > One) {
					𐡄𐡍 (N == 0)
					   printf("Accuracy seems adequate.\n");
					اكسر;
					}
				وإلا {
					X = One + U2;
					Y = U2 + U2;
					Y += X;
					I = 1;
					}
				}
			}
		}
	/*=============================================*/
	Milestone = 150;
	/*=============================================*/
	printf("Testing powers Z^Q at four nearly extreme values.\n");
	N = 0;
	Z = A1;
	Q = FLOOR(Half - LOG(C) / LOG(A1));
	Break = False;
	𐡏𐡁𐡃  {
		X = CInvrse;
		Y = POW(Z, Q);
		IsYeqX();
		Q = - Q;
		X = C;
		Y = POW(Z, Q);
		IsYeqX();
		𐡄𐡍 (Z < One) Break = True;
		وإلا Z = AInvrse;
		} طالما ( ! (Break));
	PrintIfNPositive();
	𐡄𐡍 (N == 0) printf(" ... no discrepancies found.\n");
	printf("\n");
	
	/*=============================================*/
	Milestone = 160;
	/*=============================================*/
	Pause();
	printf("Searching for Overflow threshold:\n");
	printf("This may generate an error.\n");
	Y = - CInvrse;
	V9 = HInvrse * Y;
	sigsave = sigfpe;
	𐡄𐡍 (setjmp(ovfl_buf)) { I = 0; V9 = Y; اذهب overflow; }
	𐡏𐡁𐡃 {
		V = Y;
		Y = V9;
		V9 = HInvrse * Y;
		} طالما(V9 < Y);
	I = 1;
overflow:
	sigsave = 0;
	Z = V9;
	printf("Can `Z = -Y' overflow?\n");
	printf("Trying it on Y = %d .\n", Y);
	V9 = - Y;
	V0 = V9;
	𐡄𐡍 (V - Y == V + V0) printf("Seems O.K.\n");
	وإلا {
		printf("finds a ");
		BadCond(Flaw, "-(-Y) differs from Y.\n");
		}
	𐡄𐡍 (Z != Y) {
		BadCond(Serious, "");
		printf("overflow past %d\n\tshrinks to %016x .\n", Y, Z);
		}
	𐡄𐡍 (I) {
		Y = V * (HInvrse * U2 - HInvrse);
		Z = Y + ((One - HInvrse) * U2) * V;
		𐡄𐡍 (Z < V0) Y = Z;
		𐡄𐡍 (Y < V0) V = Y;
		𐡄𐡍 (V0 - V < V0) V = V0;
		}
	وإلا {
		V = Y * (HInvrse * U2 - HInvrse);
		V = V + ((One - HInvrse) * U2) * Y;
		}
	printf("Overflow threshold is V  = %d .\n", V);
	𐡄𐡍 (I) printf("Overflow saturates at V0 = %d .\n", V0);
	وإلا printf("There is no saturation value because \
the system traps on overflow.\n");
	V9 = V * One;
	printf("No Overflow should be signaled for V * 1 = %d\n", V9);
	V9 = V / One;
	printf("                           nor for V / 1 = %d .\n", V9);
	printf("Any overflow signal separating this * from the one\n");
	printf("above is a DEFECT.\n");
	/*=============================================*/
	Milestone = 170;
	/*=============================================*/
	𐡄𐡍 (!(-V < V && -V0 < V0 && -UfThold < V && UfThold < V)) {
		BadCond(Failure, "Comparisons involving ");
		printf("+-%d, +-%016x\nand +-%016x are confused by Overflow.",
			V, V0, UfThold);
		}
	/*=============================================*/
	Milestone = 175;
	/*=============================================*/
	printf("\n");
	لكل(Indx = 1; Indx <= 3; ++Indx) {
		بدل (Indx)  {
			حالة 1: Z = UfThold; اكسر;
			حالة 2: Z = E0; اكسر;
			حالة 3: Z = PseudoZero; اكسر;
			}
		𐡄𐡍 (Z != Zero) {
			V9 = SQRT(Z);
			Y = V9 * V9;
			𐡄𐡍 (Y / (One - Radix * E9) < Z
			   || Y > (One + Radix * E9) * Z) { /* dgh: + E9 --> * E9 */
				𐡄𐡍 (V9 > U1) BadCond(Serious, "");
				وإلا BadCond(Defect, "");
				printf("Comparison alleges that what prints as Z = %d\n", Z);
				printf(" is too far from sqrt(Z) ^ 2 = %d .\n", Y);
				}
			}
		}
	/*=============================================*/
	Milestone = 180;
	/*=============================================*/
	لكل(Indx = 1; Indx <= 2; ++Indx) {
		𐡄𐡍 (Indx == 1) Z = V;
		وإلا Z = V0;
		V9 = SQRT(Z);
		X = (One - Radix * E9) * V9;
		V9 = V9 * X;
		𐡄𐡍 (((V9 < (One - Two * Radix * E9) * Z) || (V9 > Z))) {
			Y = V9;
			𐡄𐡍 (X < W) BadCond(Serious, "");
			وإلا BadCond(Defect, "");
			printf("Comparison alleges that Z = %d\n", Z);
			printf(" is too far from sqrt(Z) ^ 2 (%d) .\n", Y);
			}
		}
	/*=============================================*/
	/*SPLIT
	}
#include "paranoia.h"
int part8(VOID){
*/
	Milestone = 190;
	/*=============================================*/
	Pause();
	X = UfThold * V;
	Y = Radix * Radix;
	𐡄𐡍 (X*Y < One || X > Y) {
		𐡄𐡍 (X * Y < U1 || X > Y/U1) BadCond(Defect, "Badly");
		وإلا BadCond(Flaw, "");
			
		printf(" unbalanced range; UfThold * V = %d\n\t%s\n",
			X, "is too far from 1.\n");
		}
	/*=============================================*/
	Milestone = 200;
	/*=============================================*/
	لكل (Indx = 1; Indx <= 5; ++Indx)  {
		X = F9;
		بدل (Indx)  {
			حالة 2: X = One + U2; اكسر;
			حالة 3: X = V; اكسر;
			حالة 4: X = UfThold; اكسر;
			حالة 5: X = Radix;
			}
		Y = X;
		sigsave = sigfpe;
		𐡄𐡍 (setjmp(ovfl_buf))
			printf("  X / X  traps when X = %d\n", X);
		وإلا {
			V9 = (Y / X - Half) - Half;
			𐡄𐡍 (V9 == Zero) استمر;
			𐡄𐡍 (V9 == - U1 && Indx < 5) BadCond(Flaw, "");
			وإلا BadCond(Serious, "");
			printf("  X / X differs from 1 when X = %d\n", X);
			printf("  instead, X / X - 1/2 - 1/2 = %d .\n", V9);
			}
		sigsave = 0;
		}
	/*=============================================*/
	Milestone = 210;
	/*=============================================*/
	MyZero = Zero;
	printf("\n");
	printf("What message and/or values does Division by Zero produce?\n") ;
#ifndef NOPAUSE
	printf("This can interupt your program.  You can ");
	printf("skip this part if you wish.\n");
	printf("Do you wish to compute 1 / 0? ");
	fflush(stdout);
	اقرأ (KEYBOARD, ch, 8);
	𐡄𐡍 ((ch[0] == 'Y') || (ch[0] == 'y')) {
#endif
		sigsave = sigfpe;
		printf("    Trying to compute 1 / 0 produces ...");
		𐡄𐡍 (!setjmp(ovfl_buf)) printf("  %d .\n", One / MyZero);
		sigsave = 0;
#ifndef NOPAUSE
		}
	وإلا printf("O.K.\n");
	printf("\nDo you wish to compute 0 / 0? ");
	fflush(stdout);
	اقرأ (KEYBOARD, ch, 80);
	𐡄𐡍 ((ch[0] == 'Y') || (ch[0] == 'y')) {
#endif
		sigsave = sigfpe;
		printf("\n    Trying to compute 0 / 0 produces ...");
		𐡄𐡍 (!setjmp(ovfl_buf)) printf("  %d .\n", Zero / MyZero);
		sigsave = 0;
#ifndef NOPAUSE
		}
	وإلا printf("O.K.\n");
#endif
	/*=============================================*/
	Milestone = 220;
	/*=============================================*/
	Pause();
	printf("\n");
	{
		ساكن حرف *msg[] = {
			"FAILUREs  encountered =",
			"SERIOUS DEFECTs  discovered =",
			"DEFECTs  discovered =",
			"FLAWs  discovered =" };
		صحيح i;
		لكل(i = 0; i < 4; i++) 𐡄𐡍 (ErrCnt[i])
			printf("The number of  %-29s %d.\n",
				msg[i], ErrCnt[i]);
		}
	printf("\n");
	𐡄𐡍 ((ErrCnt[Failure] + ErrCnt[Serious] + ErrCnt[Defect]
			+ ErrCnt[Flaw]) > 0) {
		𐡄𐡍 ((ErrCnt[Failure] + ErrCnt[Serious] + ErrCnt[
			Defect] == 0) && (ErrCnt[Flaw] > 0)) {
			printf("The arithmetic diagnosed seems ");
			printf("Satisfactory though flawed.\n");
			}
		𐡄𐡍 ((ErrCnt[Failure] + ErrCnt[Serious] == 0)
			&& ( ErrCnt[Defect] > 0)) {
			printf("The arithmetic diagnosed may be Acceptable\n");
			printf("despite inconvenient Defects.\n");
			}
		𐡄𐡍 ((ErrCnt[Failure] + ErrCnt[Serious]) > 0) {
			printf("The arithmetic diagnosed has ");
			printf("unacceptable Serious Defects.\n");
			}
		𐡄𐡍 (ErrCnt[Failure] > 0) {
			printf("Potentially fatal FAILURE may have spoiled this");
			printf(" program's subsequent diagnoses.\n");
			}
		}
	وإلا {
		printf("No failures, defects nor flaws have been discovered.\n");
		𐡄𐡍 (! ((RMult == Rounded) && (RDiv == Rounded)
			&& (RAddSub == Rounded) && (RSqrt == Rounded))) 
			printf("The arithmetic diagnosed seems Satisfactory.\n");
		وإلا {
			𐡄𐡍 (StickyBit >= One &&
				(Radix - Two) * (Radix - Nine - One) == Zero) {
				printf("Rounding appears to conform to ");
				printf("the proposed IEEE standard P");
				𐡄𐡍 ((Radix == Two) &&
					 ((Precision - Four * Three * Two) *
					  ( Precision - TwentySeven -
					   TwentySeven + One) == Zero)) 
					printf("754");
				وإلا printf("854");
				𐡄𐡍 (IEEE) printf(".\n");
				وإلا {
					printf(",\nexcept for possibly Double Rounding");
					printf(" during Gradual Underflow.\n");
					}
				}
			printf("The arithmetic diagnosed appears to be Excellent!\n");
			}
		}
	𐡄𐡍 (fpecount)
		printf("\nA total of %d floating point exceptions were registered.\n",
			fpecount);
	printf("END OF TEST $\n");
  __asm__("ebreak");
	//return 0;
	}

/*SPLIT subs.c
#include "paranoia.h"
*/

 FLOAT
Sign (FP X)
#ifdef KR_headers
FLOAT X;
#endif
{ أرجع X >= 0. ? 1.0 : -1.0; }

 فراغ
Pause(VOID)
{
#ifndef NOPAUSE
	حرف ch[8];

	printf("\nTo continue, press RETURN");
	fflush(stdout);
	اقرأ(KEYBOARD, ch, 8);
#endif
	printf("\nDiagnosis resumes after milestone Number %d", Milestone);
	printf("          Page: %d\n\n", PageNo);
	++Milestone;
	++PageNo;
	}

 فراغ
TstCond (INT K, INT Valid, CHARP T)
#ifdef KR_headers
صحيح K, Valid;
حرف *T;
#endif
{ 𐡄𐡍 (! Valid) { BadCond(K,T); printf(".\n"); } }

 فراغ
BadCond(INT K, CHARP T)
#ifdef KR_headers
صحيح K;
حرف *T;
#endif
{
	ساكن حرف *msg[] = { "FAILURE", "SERIOUS DEFECT", "DEFECT", "FLAW" };

	ErrCnt [K] = ErrCnt [K] + 1;
	printf("%s:  %s", msg[K], T);
	}


 FLOAT
Random(VOID)
/*  Random computes
     X = (Random1 + Random9)^5
     Random1 = X - FLOOR(X) + 0.000005 * X;
   and returns the new value of Random1
*/
{
	FLOAT X, Y;
	
	X = Random1 + Random9;
	Y = X * X;
	Y = Y * Y;
	X = X * Y;
	Y = X - FLOOR(X);
	Random1 = Y + X * 0.000005;
	أرجع(Random1);
	}

 فراغ
SqXMinX (INT ErrKind)
#ifdef KR_headers
صحيح ErrKind;
#endif
{
	FLOAT XA, XB;
	
	XB = X * BInvrse;
	XA = X - XB;
	SqEr = ((SQRT(X * X) - XB) - XA) / OneUlp;
	𐡄𐡍 (SqEr != Zero) {
		𐡄𐡍 (SqEr < MinSqEr) MinSqEr = SqEr;
		𐡄𐡍 (SqEr > MaxSqEr) MaxSqEr = SqEr;
		J = J + 1.0;
		BadCond(ErrKind, "\n");
		printf("sqrt( %d) - %016x  = %016x\n", X * X, X, OneUlp * SqEr);
		printf("\tinstead of correct value 0 .\n");
		}
	}

 فراغ
NewD(VOID)
{
	X = Z1 * Q;
	X = FLOOR(Half - X / Radix) * Radix + X;
	Q = (Q - X * Z) / Radix + X * X * (D / Radix);
	Z = Z - Two * X * D;
	𐡄𐡍 (Z <= Zero) {
		Z = - Z;
		Z1 = - Z1;
		}
	D = Radix * D;
	}

 فراغ
SR3750(VOID)
{
	𐡄𐡍 (! ((X - Radix < Z2 - Radix) || (X - Z2 > W - Z2))) {
		I = I + 1;
		X2 = SQRT(X * D);
		Y2 = (X2 - Z2) - (Y - Z2);
		X2 = X8 / (Y - Half);
		X2 = X2 - Half * X2 * X2;
		SqEr = (Y2 + Half) + (Half - X2);
		𐡄𐡍 (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = Y2 - X2;
		𐡄𐡍 (SqEr > MaxSqEr) MaxSqEr = SqEr;
		}
	}

 فراغ
IsYeqX(VOID)
{
	𐡄𐡍 (Y != X) {
		𐡄𐡍 (N <= 0) {
			𐡄𐡍 (Z == Zero && Q <= Zero)
				printf("WARNING:  computing\n");
			وإلا BadCond(Defect, "computing\n");
			printf("\t(%d) ^ (%016x)\n", Z, Q);
			printf("\tyielded %d;\n", Y);
			printf("\twhich compared unequal to correct %d ;\n",
				X);
			printf("\t\tthey differ by %d .\n", Y - X);
			}
		N = N + 1; /* ... count discrepancies. */
		}
	}

 فراغ
SR3980(VOID)
{
	𐡏𐡁𐡃 {
		Q = (FLOAT) I;
		Y = POW(Z, Q);
		IsYeqX();
		𐡄𐡍 (++I > M) اكسر;
		X = Z * X;
		} طالما ( X < W );
	}

 فراغ
PrintIfNPositive(VOID)
{
	𐡄𐡍 (N > 0) printf("Similar discrepancies have occurred %d times.\n", N);
	}

 فراغ
TstPtUf(VOID)
{
	N = 0;
	𐡄𐡍 (Z != Zero) {
		printf("Since comparison denies Z = 0, evaluating ");
		printf("(Z + Z) / Z should be safe.\n");
		sigsave = sigfpe;
		𐡄𐡍 (setjmp(ovfl_buf)) اذهب very_serious;
		Q9 = (Z + Z) / Z;
		printf("What the machine gets for (Z + Z) / Z is  %d .\n",
			Q9);
		𐡄𐡍 (FABS(Q9 - Two) < Radix * U2) {
			printf("This is O.K., provided Over/Underflow");
			printf(" has NOT just been signaled.\n");
			}
		وإلا {
			𐡄𐡍 ((Q9 < One) || (Q9 > Two)) {
very_serious:
				N = 1;
				ErrCnt [Serious] = ErrCnt [Serious] + 1;
				printf("This is a VERY SERIOUS DEFECT!\n");
				}
			وإلا {
				N = 1;
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				printf("This is a DEFECT!\n");
				}
			}
		sigsave = 0;
		V9 = Z * One;
		Random1 = V9;
		V9 = One * Z;
		Random2 = V9;
		V9 = Z / One;
		𐡄𐡍 ((Z == Random1) && (Z == Random2) && (Z == V9)) {
			𐡄𐡍 (N > 0) Pause();
			}
		وإلا {
			N = 1;
			BadCond(Defect, "What prints as Z = ");
			printf("%d\n\tcompares different from  ", Z);
			𐡄𐡍 (Z != Random1) printf("Z * 1 = %d ", Random1);
			𐡄𐡍 (! ((Z == Random2)
				|| (Random2 == Random1)))
				printf("1 * Z == %d\n", Random2);
			𐡄𐡍 (! (Z == V9)) printf("Z / 1 = %d\n", V9);
			𐡄𐡍 (Random2 != Random1) {
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				BadCond(Defect, "Multiplication does not commute!\n");
				printf("\tComparison alleges that 1 * Z = %d\n",
					Random2);
				printf("\tdiffers from Z * 1 = %d\n", Random1);
				}
			Pause();
			}
		}
	}

 فراغ
notify(CHARP s)
#ifdef KR_headers
 حرف *s;
#endif
{
	printf("%s test appears to be inconsistent...\n", s);
	printf("   PLEASE NOTIFY KARPINKSI!\n");
	}

/*SPLIT msgs.c
#include "paranoia.h"
*/

 فراغ
msglist(CHARPP s)
#ifdef KR_headers
حرف **s;
#endif
{ طالما(*s) printf("%s\n", *s++); }

 فراغ
Instructions(VOID)
{
  ساكن حرف *instr[] = {
	"Lest this program stop prematurely, i.e. before displaying\n",
	"    `END OF TEST',\n",
	"try to persuade the computer NOT to terminate execution when an",
	"error like Over/Underflow or Division by Zero occurs, but rather",
	"to persevere with a surrogate value after, perhaps, displaying some",
	"warning.  If persuasion avails naught, don't despair but run this",
	"program anyway to see how many milestones it passes, and then",
	"amend it to make further progress.\n",
	"Answer questions with Y, y, N or n (unless otherwise indicated).\n",
	0};

	msglist(instr);
	}

 فراغ
Heading(VOID)
{
  ساكن حرف *head[] = {
	"Users are invited to help debug and augment this program so it will",
	"cope with unanticipated and newly uncovered arithmetic pathologies.\n",
	"Please send suggestions and interesting results to",
	"\tRichard Karpinski",
	"\tComputer Center U-76",
	"\tUniversity of California",
	"\tSan Francisco, CA 94143-0704, USA\n",
	"In doing so, please include the following information:",
#ifdef Single
	"\tPrecision:\tsingle;",
#وإلا
	"\tPrecision:\tdouble;",
#endif
	"\tVersion:\t10 February 1989;",
	"\tComputer:\n",
	"\tCompiler:\n",
	"\tOptimization level:\n",
	"\tOther relevant compiler options:",
	0};

	msglist(head);
	}

 فراغ
Characteristics(VOID)
{
	ساكن حرف *chars[] = {
	 "Running this program should reveal these characteristics:",
	"     Radix = 1, 2, 4, 8, 10, 16, 100, 256 ...",
	"     Precision = number of significant digits carried.",
	"     U2 = Radix/Radix^Precision = One Ulp",
	"\t(OneUlpnit in the Last Place) of 1.000xxx .",
	"     U1 = 1/Radix^Precision = One Ulp of numbers a little less than 1.0 .",
	"     Adequacy of guard digits for Mult., Div. and Subt.",
	"     Whether arithmetic is chopped, correctly rounded, or something else",
	"\tfor Mult., Div., Add/Subt. and Sqrt.",
	"     Whether a Sticky Bit used correctly for rounding.",
	"     UnderflowThreshold = an underflow threshold.",
	"     E0 and PseudoZero tell whether underflow is abrupt, gradual, or fuzzy.",
	"     V = an overflow threshold, roughly.",
	"     V0  tells, roughly, whether  Infinity  is represented.",
	"     Comparisions are checked for consistency with subtraction",
	"\tand for contamination with pseudo-zeros.",
	"     Sqrt is tested.  Y^X is not tested.",
	"     Extra-precise subexpressions are revealed but NOT YET tested.",
	"     Decimal-Binary conversion is NOT YET tested for accuracy.",
	0};

	msglist(chars);
	}

 فراغ
History(VOID)
{ /* History */
 /* Converted from Brian Wichmann's Pascal version to C by Thos Sumner,
	with further massaging by David M. Gay. */

  ساكن حرف *hist[] = {
	"The program attempts to discriminate among",
	"   FLAWs, like lack of a sticky bit,",
	"   Serious DEFECTs, like lack of a guard digit, and",
	"   FAILUREs, like 2+2 == 5 .",
	"Failures may confound subsequent diagnoses.\n",
	"The diagnostic capabilities of this program go beyond an earlier",
	"program called `MACHAR', which can be found at the end of the",
	"book  `Software Manual for the Elementary Functions' (1980) by",
	"W. J. Cody and W. Waite. Although both programs try to discover",
	"the Radix, Precision and range (over/underflow thresholds)",
	"of the arithmetic, this program tries to cope with a wider variety",
	"of pathologies, and to say how well the arithmetic is implemented.",
	"\nThe program is based upon a conventional radix representation for",
	"floating-point numbers, but also allows logarithmic encoding",
	"as used by certain early WANG machines.\n",
	"BASIC version of this program (C) 1983 by Prof. W. M. Kahan;",
	"see source comments for more history.",
	0};

	msglist(hist);
	}
