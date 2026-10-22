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

#అన్తర్భావ <stdio.h>
#నిర్వచించు NOSIGNAL
#నిర్వచించు NOPAUSE
#నిర్వచితం_కాకపోతే NOSIGNAL
#అన్తర్భావ <signal.h>
#అయితే_ముగింపు
#అన్తర్భావ <setjmp.h>
#నిర్వచితమైతే Single
#నిర్వచించు FLOAT దశాంశం
#నిర్వచించు FABS(x) (దశాంశం)fabs((ద్విగుణ)(x))
#నిర్వచించు FLOOR(x) (దశాంశం)floor((ద్విగుణ)(x))
#నిర్వచించు LOG(x) (దశాంశం)సంవర్గమానం((ద్విగుణ)(x))
#నిర్వచించు POW(x,y) (దశాంశం)ఘాతం((ద్విగుణ)(x),(ద్విగుణ)(y))
#నిర్వచించు SQRT(x) (దశాంశం)వర్గమూలం((ద్విగుణ)(x))
#లేకపోతే
#నిర్వచించు FLOAT ద్విగుణ
#నిర్వచించు FABS(x) fabs(x)
#నిర్వచించు FLOOR(x) floor(x)
#నిర్వచించు LOG(x) సంవర్గమానం(x)
#నిర్వచించు POW(x,y) ఘాతం(x,y)
#నిర్వచించు SQRT(x) వర్గమూలం(x)
#అయితే_ముగింపు

jmp_buf ovfl_buf;
#నిర్వచితమైతే KR_శీర్షికలు
#నిర్వచించు VOID /* void */
#నిర్వచించు INT /* int */
#నిర్వచించు FP /* FLOAT */
#నిర్వచించు CHARP /* char * */
#నిర్వచించు CHARPP /* char ** */
బాహ్య ద్విగుణ fabs(), floor(), సంవర్గమానం(), ఘాతం(), వర్గమూలం();
బాహ్య శూన్య నిష్క్రమించు();
రకనిర్వచనం శూన్య (*Sig_type)();
FLOAT Sign(), Random();
బాహ్య శూన్య BadCond();
బాహ్య శూన్య SqXMinX();
బాహ్య శూన్య TstCond();
బాహ్య శూన్య notify();
బాహ్య పూర్ణాంకం పఠ();
#లేకపోతే
#నిర్వచించు VOID శూన్య
#నిర్వచించు INT పూర్ణాంకం
#నిర్వచించు FP FLOAT
#నిర్వచించు CHARP అక్షరం *
#నిర్వచించు CHARPP అక్షరం **
#నిర్వచితమైతే __STDC__
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <math.h>
#లేకపోతే
#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు
బాహ్య ద్విగుణ fabs(ద్విగుణ), floor(ద్విగుణ), సంవర్గమానం(ద్విగుణ);
బాహ్య ద్విగుణ ఘాతం(ద్విగుణ,ద్విగుణ), వర్గమూలం(ద్విగుణ);
బాహ్య శూన్య నిష్క్రమించు(INT);
#నిర్వచితమైతే __cplusplus
	}
#అయితే_ముగింపు
#అయితే_ముగింపు
రకనిర్వచనం శూన్య (*Sig_type)(పూర్ణాంకం);
FLOAT Sign(FLOAT), Random(శూన్య);
బాహ్య శూన్య BadCond(పూర్ణాంకం, అక్షరం*);
బాహ్య శూన్య SqXMinX(పూర్ణాంకం);
బాహ్య శూన్య TstCond(పూర్ణాంకం, పూర్ణాంకం, అక్షరం*);
బాహ్య శూన్య notify(అక్షరం*);
బాహ్య పూర్ణాంకం పఠ(పూర్ణాంకం, అక్షరం*, పూర్ణాంకం);
#అయితే_ముగింపు
#నిర్వచనం_రద్దు V9
బాహ్య శూన్య Characteristics(VOID);
బాహ్య శూన్య Heading(VOID);
బాహ్య శూన్య History(VOID);
బాహ్య శూన్య Instructions(VOID);
బాహ్య శూన్య IsYeqX(VOID);
బాహ్య శూన్య NewD(VOID);
బాహ్య శూన్య Pause(VOID);
బాహ్య శూన్య PrintIfNPositive(VOID);
బాహ్య శూన్య SR3750(VOID);
బాహ్య శూన్య SR3980(VOID);
బాహ్య శూన్య TstPtUf(VOID);

Sig_type sigsave;

#నిర్వచించు KEYBOARD 0

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
పూర్ణాంకం NoTrials = 20; /*Number of tests for commutativity. */
#నిర్వచించు False 0
#నిర్వచించు True 1

/* Definitions for declared types 
	Guard == (Yes, No);
	Rounding == (Chopped, Rounded, Other);
	Message == packed array [1..40] of char;
	Class == (Flaw, Defect, Serious, Failure);
	  */
#నిర్వచించు Yes 1
#నిర్వచించు No  0
#నిర్వచించు Chopped 2
#నిర్వచించు Rounded 1
#నిర్వచించు Other   0
#నిర్వచించు Flaw    3
#నిర్వచించు Defect  2
#నిర్వచించు Serious 1
#నిర్వచించు Failure 0
రకనిర్వచనం పూర్ణాంకం Guard, Rounding, Class;
రకనిర్వచనం అక్షరం సందేశం;

/* Declarations of Variables */
పూర్ణాంకం Indx;
అక్షరం ch[8];
FLOAT AInvrse, A1;
FLOAT C, CInvrse;
FLOAT D, FourD;
FLOAT E0, E1, Exp2, E3, MinSqEr;
FLOAT SqEr, MaxSqEr, E9;
FLOAT మూడవ;
FLOAT F6, F9;
FLOAT H, HInvrse;
పూర్ణాంకం I;
FLOAT Sticky_బిట్టు, J;
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
పూర్ణాంకం ErrCnt[4];
పూర్ణాంకం fpecount;
పూర్ణాంకం Milestone;
పూర్ణాంకం పుట_No;
పూర్ణాంకం M, N, N1;
Guard GMult, GDiv, GAddSub;
Rounding RMult, RDiv, RAddSub, RSqrt;
పూర్ణాంకం Break, పూర్తి, NotMonot, Monot, Anomaly, IEEE,
		SqRWrng, UfNGrad;
/* Computed constants. */
/*U1  gap below 1.0, i.e, 1.0-U1 is next number below 1.0 */
/*U2  gap above 1.0, i.e, 1.0+U2 is next number above 1.0 */

/* floating point exception receiver */
 శూన్య
sigfpe(INT x)
{
	fpecount++;
	రాయి("\n* * * FLOATING-POINT ERROR %d * * *\n", x);
	fflush(stdout);
	ఒకవేళ (sigsave) {
#నిర్వచితం_కాకపోతే NOSIGNAL
		సంకేతం(SIGFPE, sigsave);
#అయితే_ముగింపు
		sigsave = 0;
		longjmp(ovfl_buf, 1);
		}
	నిష్క్రమించు(1);
}

ప్రధాన(VOID)
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
	పుట_No = 1;
	/*=============================================*/
	Milestone = 0;
	/*=============================================*/
#నిర్వచితం_కాకపోతే NOSIGNAL
	సంకేతం(SIGFPE, sigfpe);
#అయితే_ముగింపు
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
	రాయి("Program is now RUNNING tests on small integers:\n");
	
	TstCond (Failure, (Zero + Zero == Zero) && (One - One == Zero)
		   && (One > Zero) && (One + One == Two),
			"0+0 != 0, 1-1 != 0, 1 <= 0, or 1+1 != 2");
	Z = - Zero;
	ఒకవేళ (Z != 0.0) {
		ErrCnt[Failure] = ErrCnt[Failure] + 1;
		రాయి("Comparison alleges that -0.0 is Non-zero!\n");
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
	/*విభజించు
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
	ఒకవేళ (ErrCnt[Failure] == 0) {
		రాయి("-1, 0, 1/2, 1, 2, 3, 4, 5, 9, 27, 32 & 240 are O.K.\n");
		రాయి("\n");
		}
	రాయి("Searching for Radix and Precision.\n");
	W = One;
	చేయి  {
		W = W + W;
		Y = W + One;
		Z = Y - W;
		Y = Z - One;
		} అయితే (MinusOne + FABS(Y) < Zero);
	/*.. now W is just big enough that |((W+1)-W)-1| >= 1 ...*/
	Precision = Zero;
	Y = One;
	చేయి  {
		Radix = W + Y;
		Y = Y + Y;
		Radix = Radix - W;
		} అయితే ( Radix == Zero);
	ఒకవేళ (Radix < Two) Radix = One;
	రాయి("Radix = %d .\n", Radix);
	ఒకవేళ (Radix != 1) {
		W = One;
		చేయి  {
			Precision = Precision + One;
			W = W * Radix;
			Y = W + One;
			} అయితే ((Y - W) == One);
		}
	/*... now W == Radix^Precision is barely too big to satisfy (W+1)-W == 1
			                              ...*/
	U1 = One / W;
	U2 = Radix * U1;
	రాయి("Closest relative separation found is U1 = %d .\n\n", U1);
	రాయి("Recalculating radix and precision\n ");
	
	/*save old values*/
	E0 = Radix;
	E1 = U1;
	E9 = U2;
	E3 = Precision;
	
	X = Four / Three;
	మూడవ = X - One;
	F6 = Half - మూడవ;
	X = F6 + F6;
	X = FABS(X - మూడవ);
	ఒకవేళ (X < U2) X = U2;
	
	/*... now X = (unknown no.) ulps of 1+...*/
	చేయి  {
		U2 = X;
		Y = Half * U2 + ThirtyTwo * U2 * U2;
		Y = One + Y;
		X = Y - One;
		} అయితే ( ! ((U2 <= X) || (X <= Zero)));
	
	/*... now U2 == 1 ulp of 1 + ... */
	X = Two / Three;
	F6 = X - Half;
	మూడవ = F6 + F6;
	X = మూడవ - Half;
	X = FABS(X + F6);
	ఒకవేళ (X < U1) X = U1;
	
	/*... now  X == (unknown no.) ulps of 1 -... */
	చేయి  {
		U1 = X;
		Y = Half * U1 + ThirtyTwo * U1 * U1;
		Y = Half - Y;
		X = Half + Y;
		Y = Half - X;
		X = Half + Y;
		} అయితే ( ! ((U1 <= X) || (X <= Zero)));
	/*... now U1 == 1 ulp of 1 - ... */
	ఒకవేళ (U1 == E1) రాయి("confirms closest relative separation U1 .\n");
	లేకపోతే రాయి("gets better closest relative separation U1 = %d .\n", U1);
	W = One / U1;
	F9 = (Half - U1) + Half;
	Radix = FLOOR(0.01 + U2 / U1);
	ఒకవేళ (Radix == E0) రాయి("Radix confirmed.\n");
	లేకపోతే రాయి("MYSTERY: recalculated Radix = %d .\n", Radix);
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
	ఒకవేళ (Radix != One)  {
		X = - TwoForty * LOG(U1) / LOG(Radix);
		Y = FLOOR(Half + X);
		ఒకవేళ (FABS(X - Y) * Four < One) X = Y;
		Precision = X / TwoForty;
		Y = FLOOR(Half + Precision);
		ఒకవేళ (FABS(Precision - Y) * TwoForty < Half) Precision = Y;
		}
	ఒకవేళ ((Precision != FLOOR(Precision)) || (Radix == One)) {
		రాయి("Precision cannot be characterized by an Integer number\n");
		రాయి("of significant digits but, by itself, this is a minor flaw.\n");
		}
	ఒకవేళ (Radix == One) 
		రాయి("logarithmic encoding has precision characterized solely by U1.\n");
	లేకపోతే రాయి("The number of significant digits of the Radix is %d .\n",
			Precision);
	TstCond (Serious, U2 * Nine * Nine * TwoForty < One,
		   "Precision worse than 5 decimal figures  ");
	/*=============================================*/
	Milestone = 30;
	/*=============================================*/
	/* Test for extra-precise subepressions */
	X = FABS(((Four / Three - One) - One / Four) * Three - One / Four);
	చేయి  {
		Z2 = X;
		X = (One + (Half * Z2 + ThirtyTwo * Z2 * Z2)) - One;
		} అయితే ( ! ((Z2 <= X) || (X <= Zero)));
	X = Y = Z = FABS((Three / Four - Two / Three) * Three - One / Four);
	చేయి  {
		Z1 = Z;
		Z = (One / Two - ((One / Two - (Half * Z1 + ThirtyTwo * Z1 * Z1))
			+ One / Two)) + One / Two;
		} అయితే ( ! ((Z1 <= Z) || (Z <= Zero)));
	చేయి  {
		చేయి  {
			Y1 = Y;
			Y = (Half - ((Half - (Half * Y1 + ThirtyTwo * Y1 * Y1)) + Half
				)) + Half;
			} అయితే ( ! ((Y1 <= Y) || (Y <= Zero)));
		X1 = X;
		X = ((Half * X1 + ThirtyTwo * X1 * X1) - F9) + F9;
		} అయితే ( ! ((X1 <= X) || (X <= Zero)));
	ఒకవేళ ((X1 != Y1) || (X1 != Z1)) {
		BadCond(Serious, "Disagreements among the values X1, Y1, Z1,\n");
		రాయి("respectively  %d,  %016x,  %016x,\n", X1, Y1, Z1);
		రాయి("are symptoms of inconsistencies introduced\n");
		రాయి("by extra-precise evaluation of arithmetic subexpressions.\n");
		notify("Possibly some part of this");
		ఒకవేళ ((X1 == U1) || (Y1 == U1) || (Z1 == U1))  రాయి(
			"That feature is not tested further by this program.\n") ;
		}
	లేకపోతే  {
		ఒకవేళ ((Z1 != U1) || (Z2 != U2)) {
			ఒకవేళ ((Z1 >= U1) || (Z2 >= U2)) {
				BadCond(Failure, "");
				notify("Precision");
				రాయి("\tU1 = %d, Z1 - U1 = %016x\n",U1,Z1-U1);
				రాయి("\tU2 = %d, Z2 - U2 = %016x\n",U2,Z2-U2);
				}
			లేకపోతే {
				ఒకవేళ ((Z1 <= Zero) || (Z2 <= Zero)) {
					రాయి("Because of unusual Radix = %d", Radix);
					రాయి(", or exact rational arithmetic a result\n");
					రాయి("Z1 = %d, or Z2 = %016x ", Z1, Z2);
					notify("of an\nextra-precision");
					}
				ఒకవేళ (Z1 != Z2 || Z1 > Zero) {
					X = Z1 / U1;
					Y = Z2 / U2;
					ఒకవేళ (Y > X) X = Y;
					Q = - LOG(X);
					రాయి("Some subexpressions appear to be calculated extra\n");
					రాయి("precisely with about %d extra B-digits, i.e.\n",
						(Q / LOG(Radix)));
					రాయి("roughly %d extra significant decimals.\n",
						Q / LOG(10.));
					}
				రాయి("That feature is not tested further by this program.\n");
				}
			}
		}
	Pause();
	/*=============================================*/
	/*విభజించు
	}
#include "paranoia.h"
void part3(VOID){
*/
	Milestone = 35;
	/*=============================================*/
	ఒకవేళ (Radix >= Two) {
		X = W / (Radix * Radix);
		Y = X + One;
		Z = Y - X;
		T = Z + U2;
		X = T - Z;
		TstCond (Failure, X == U2,
			"Subtraction is not normalized X=Y,X+Z != Y+Z!");
		ఒకవేళ (X == U2) రాయి(
			"Subtraction appears to be normalized, as it should be.");
		}
	రాయి("\nChecking for guard digit in *, /, and -.\n");
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
	ఒకవేళ ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)) GMult = Yes;
	లేకపోతే {
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
	ఒకవేళ ((X == Zero) && (Y == Zero) && (Z == Zero)) GDiv = Yes;
	లేకపోతే {
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
	Sticky_బిట్టు = T / Radix;
	X = R - X;
	Y = Sticky_బిట్టు - Y;
	TstCond (Failure, X == Zero && Y == Zero,
			"* and/or / gets too many last digits wrong");
	Y = One - U1;
	X = One - F9;
	Y = One - Y;
	T = Radix - U2;
	Z = Radix - BMinusU2;
	T = Radix - T;
	ఒకవేళ ((X == U1) && (Y == U1) && (Z == U2) && (T == U2)) GAddSub = Yes;
	లేకపోతే {
		GAddSub = No;
		TstCond (Serious, False,
			"- lacks Guard Digit, so cancellation is obscured");
		}
	ఒకవేళ (F9 != One && F9 - One >= Zero) {
		BadCond(Serious, "comparison alleges  (1-U1) < 1  although\n");
		రాయి("  subtraction yields  (1-U1) - 1 = 0 , thereby vitiating\n");
		రాయి("  such precautions against division by zero as\n");
		రాయి("  ...  if (X == 1.0) {.....} else {.../(X-1.0)...}\n");
		}
	ఒకవేళ (GMult == Yes && GDiv == Yes && GAddSub == Yes) రాయి(
		"     *, /, and - appear to have guard digits, as they should.\n");
	/*=============================================*/
	Milestone = 40;
	/*=============================================*/
	Pause();
	రాయి("Checking rounding on multiply, divide and add/subtract.\n");
	RMult = Other;
	RDiv = Other;
	RAddSub = Other;
	RadixD2 = Radix / Two;
	A1 = Two;
	పూర్తి = False;
	చేయి  {
		AInvrse = Radix;
		చేయి  {
			X = AInvrse;
			AInvrse = AInvrse / A1;
			} అయితే ( ! (FLOOR(AInvrse) != AInvrse));
		పూర్తి = (X == One) || (A1 > Three);
		ఒకవేళ (! పూర్తి) A1 = Nine + One;
		} అయితే ( ! (పూర్తి));
	ఒకవేళ (X == One) A1 = Radix;
	AInvrse = One / A1;
	X = A1;
	Y = AInvrse;
	పూర్తి = False;
	చేయి  {
		Z = X * Y - Half;
		TstCond (Failure, Z == Half,
			"X * (1/X) differs from 1");
		పూర్తి = X == Radix;
		X = Radix;
		Y = One / X;
		} అయితే ( ! (పూర్తి));
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
	ఒకవేళ ((X == Zero) && (Y == Zero) && (Z == Zero) && (T <= Zero)) {
		X = (OneAndHalf + U2) * Y2;
		Y = OneAndHalf - U2 - U2;
		Z = OneAndHalf + U2 + U2;
		T = (OneAndHalf - U2) * Y1;
		X = X - (Z + U2);
		Sticky_బిట్టు = Y * Y1;
		S = Z * Y2;
		T = T - Y;
		Y = (U2 - Y) + Sticky_బిట్టు;
		Z = S - (Z + U2 + U2);
		Sticky_బిట్టు = (Y2 + U2) * Y1;
		Y1 = Y2 * Y1;
		Sticky_బిట్టు = Sticky_బిట్టు - Y2;
		Y1 = Y1 - Half;
		ఒకవేళ ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)
			&& ( Sticky_బిట్టు == Zero) && (Y1 == Half)) {
			RMult = Rounded;
			రాయి("Multiplication appears to round correctly.\n");
			}
		లేకపోతే	ఒకవేళ ((X + U2 == Zero) && (Y < Zero) && (Z + U2 == Zero)
				&& (T < Zero) && (Sticky_బిట్టు + U2 == Zero)
				&& (Y1 < Half)) {
				RMult = Chopped;
				రాయి("Multiplication appears to chop.\n");
				}
			లేకపోతే రాయి("* is neither chopped nor correctly rounded.\n");
		ఒకవేళ ((RMult == Rounded) && (GMult == No)) notify("Multiplication");
		}
	లేకపోతే రాయి("* is neither chopped nor correctly rounded.\n");
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
	ఒకవేళ (! ((X > Zero) || (Y > Zero) || (Z > Zero) || (T > Zero))) {
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
		ఒకవేళ ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)
			&& (Y2 == Zero) && (Y2 == Zero)
			&& (Y1 - Half == F9 - Half )) {
			RDiv = Rounded;
			రాయి("Division appears to round correctly.\n");
			ఒకవేళ (GDiv == No) notify("Division");
			}
		లేకపోతే ఒకవేళ ((X < Zero) && (Y < Zero) && (Z < Zero) && (T < Zero)
			&& (Y2 < Zero) && (Y1 - Half < F9 - Half)) {
			RDiv = Chopped;
			రాయి("Division appears to chop.\n");
			}
		}
	ఒకవేళ (RDiv == Other) రాయి("/ is neither chopped nor correctly rounded.\n");
	BInvrse = One / Radix;
	TstCond (Failure, (BInvrse * Radix - Half == Half),
		   "Radix * ( 1 / Radix ) differs from 1");
	/*=============================================*/
	/*విభజించు
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
	ఒకవేళ ((X == Zero) && (Y == Zero)) {
		RAddSub = Chopped;
		రాయి("Add/Subtract appears to be chopped.\n");
		}
	ఒకవేళ (GAddSub == Yes) {
		X = (Half + U2) * U2;
		Y = (Half - U2) * U2;
		X = One + X;
		Y = One + Y;
		X = (One + U2) - X;
		Y = One - Y;
		ఒకవేళ ((X == Zero) && (Y == Zero)) {
			X = (Half + U2) * U1;
			Y = (Half - U2) * U1;
			X = One - X;
			Y = One - Y;
			X = F9 - X;
			Y = One - Y;
			ఒకవేళ ((X == Zero) && (Y == Zero)) {
				RAddSub = Rounded;
				రాయి("Addition/Subtraction appears to round correctly.\n");
				ఒకవేళ (GAddSub == No) notify("Add/Subtract");
				}
			లేకపోతే రాయి("Addition/Subtraction neither rounds nor chops.\n");
			}
		లేకపోతే రాయి("Addition/Subtraction neither rounds nor chops.\n");
		}
	లేకపోతే రాయి("Addition/Subtraction neither rounds nor chops.\n");
	S = One;
	X = One + Half * (One + Half);
	Y = (One + U2) * Half;
	Z = X - Y;
	T = Y - X;
	Sticky_బిట్టు = Z + T;
	ఒకవేళ (Sticky_బిట్టు != Zero) {
		S = Zero;
		BadCond(Flaw, "(X - Y) + (Y - X) is non zero!\n");
		}
	Sticky_బిట్టు = Zero;
	ఒకవేళ ((GMult == Yes) && (GDiv == Yes) && (GAddSub == Yes)
		&& (RMult == Rounded) && (RDiv == Rounded)
		&& (RAddSub == Rounded) && (FLOOR(RadixD2) == RadixD2)) {
		రాయి("Checking for sticky bit.\n");
		X = (Half + U1) * U2;
		Y = Half * U2;
		Z = One + Y;
		T = One + X;
		ఒకవేళ ((Z - One <= Zero) && (T - One >= U2)) {
			Z = T + Y;
			Y = Z - X;
			ఒకవేళ ((Z - T >= U2) && (Y - T == Zero)) {
				X = (Half + U1) * U1;
				Y = Half * U1;
				Z = One - Y;
				T = One - X;
				ఒకవేళ ((Z - One == Zero) && (T - F9 == Zero)) {
					Z = (Half - U1) * U1;
					T = F9 - Z;
					Q = F9 - Y;
					ఒకవేళ ((T - F9 == Zero) && (F9 - U1 - Q == Zero)) {
						Z = (One + U2) * OneAndHalf;
						T = (OneAndHalf + U2) - Z + U2;
						X = One + Half / Radix;
						Y = One + Radix * U2;
						Z = X * Y;
						ఒకవేళ (T == Zero && X + Radix * U2 - Z == Zero) {
							ఒకవేళ (Radix != Two) {
								X = Two + U2;
								Y = X / Two;
								ఒకవేళ ((Y - One == Zero)) Sticky_బిట్టు = S;
								}
							లేకపోతే Sticky_బిట్టు = S;
							}
						}
					}
				}
			}
		}
	ఒకవేళ (Sticky_బిట్టు == One) రాయి("Sticky bit apparently used correctly.\n");
	లేకపోతే రాయి("Sticky bit used incorrectly or not at all.\n");
	TstCond (Flaw, !(GMult == No || GDiv == No || GAddSub == No ||
			RMult == Other || RDiv == Other || RAddSub == Other),
		"lack(s) యొక్క guard digits or failure(s) గమ్యం correctly round or chop\n\
(noted above) లెక్క as one flaw లోపల the final tally క్రింద");
	/*=============================================*/
	Milestone = 60;
	/*=============================================*/
	రాయి("\n");
	రాయి("Does Multiplication commute?  ");
	రాయి("Testing on %d random pairs.\n", NoTrials);
	Random9 = SQRT(3.0);
	Random1 = మూడవ;
	I = 1;
	చేయి  {
		X = Random();
		Y = Random();
		Z9 = Y * X;
		Z = X * Y;
		Z9 = Z - Z9;
		I = I + 1;
		} అయితే ( ! ((I > NoTrials) || (Z9 != Zero)));
	ఒకవేళ (I == NoTrials) {
		Random1 = One + Half / Three;
		Random2 = (U2 + U1) + One;
		Z = Random1 * Random2;
		Y = Random2 * Random1;
		Z9 = (One + Half / Three) * ((U2 + U1) + One) - (One + Half /
			Three) * ((U2 + U1) + One);
		}
	ఒకవేళ (! ((I == NoTrials) || (Z9 == Zero)))
		BadCond(Defect, "X * Y == Y * X trial fails.\n");
	లేకపోతే రాయి("     No failures found in %d integer pairs.\n", NoTrials);
	/*=============================================*/
	Milestone = 70;
	/*=============================================*/
	రాయి("\nRunning test of square root(x).\n");
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
	ఒకవేళ (J != Zero) Pause();
	రాయి("Testing if sqrt(X * X) == X for %d Integers X.\n", NoTrials);
	J = Zero;
	X = Two;
	Y = Radix;
	ఒకవేళ ((Radix != One)) చేయి  {
		X = Y;
		Y = Radix * Y;
		} అయితే ( ! ((Y - X >= NoTrials)));
	OneUlp = X * U2;
	I = 1;
	అయితే (I <= NoTrials) {
		X = X + One;
		SqXMinX (Defect);
		ఒకవేళ (J > Zero) ఆపు;
		I = I + 1;
		}
	రాయి("Test for sqrt monotonicity.\n");
	I = - 1;
	X = BMinusU2;
	Y = Radix;
	Z = Radix + Radix * U2;
	NotMonot = False;
	Monot = False;
	అయితే ( ! (NotMonot || Monot)) {
		I = I + 1;
		X = SQRT(X);
		Q = SQRT(Y);
		Z = SQRT(Z);
		ఒకవేళ ((X > Q) || (Q > Z)) NotMonot = True;
		లేకపోతే {
			Q = FLOOR(Q + Half);
			ఒకవేళ (!(I > 0 || Radix == Q * Q)) Monot = True;
			లేకపోతే ఒకవేళ (I > 0) {
			ఒకవేళ (I > 1) Monot = True;
			లేకపోతే {
				Y = Y * BInvrse;
				X = Y - U1;
				Z = Y + U1;
				}
			}
			లేకపోతే {
				Y = Q;
				X = Y - U2;
				Z = Y + U2;
				}
			}
		}
	ఒకవేళ (Monot) రాయి("sqrt has passed a test for Monotonicity.\n");
	లేకపోతే {
		BadCond(Defect, "");
		రాయి("sqrt(X) is non-monotonic for X near %d .\n", Y);
		}
	/*=============================================*/
	/*విభజించు
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
	ఒకవేళ (SqEr > MaxSqEr) MaxSqEr = SqEr;
	SqEr = Y + U2 / Eight;
	ఒకవేళ (SqEr < MinSqEr) MinSqEr = SqEr;
	Y = ((SQRT(F9) - U2) - (One - U2)) / U1;
	SqEr = Y + U1 / Eight;
	ఒకవేళ (SqEr > MaxSqEr) MaxSqEr = SqEr;
	SqEr = (Y + One) + U1 / Eight;
	ఒకవేళ (SqEr < MinSqEr) MinSqEr = SqEr;
	OneUlp = U2;
	X = OneUlp;
	కొరకు( Indx = 1; Indx <= 3; ++Indx) {
		Y = SQRT((X + U1 + X) + F9);
		Y = ((Y - U2) - ((One - U2) + X)) / OneUlp;
		Z = ((U1 - X) + F9) * Half * X * X / OneUlp;
		SqEr = (Y + Half) + Z;
		ఒకవేళ (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = (Y - Half) + Z;
		ఒకవేళ (SqEr > MaxSqEr) MaxSqEr = SqEr;
		ఒకవేళ (((Indx == 1) || (Indx == 3))) 
			X = OneUlp * Sign (X) * FLOOR(Eight / (Nine * SQRT(OneUlp)));
		లేకపోతే {
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
	ఒకవేళ (Radix != One) {
		రాయి("Testing whether sqrt is rounded or chopped.\n");
		D = FLOOR(Half + POW(Radix, One + Precision - FLOOR(Precision)));
	/* ... == Radix^(1 + fract) if (Precision == Integer + fract. */
		X = D / Radix;
		Y = D / A1;
		ఒకవేళ ((X != FLOOR(X)) || (Y != FLOOR(Y))) {
			Anomaly = True;
			}
		లేకపోతే {
			X = Zero;
			Z2 = X;
			Y = One;
			Y2 = Y;
			Z1 = Radix - One;
			FourD = Four * D;
			చేయి  {
				ఒకవేళ (Y2 > Z2) {
					Q = Radix;
					Y1 = Y;
					చేయి  {
						X1 = FABS(Q + FLOOR(Half - Q / Y1) * Y1);
						Q = Y1;
						Y1 = X1;
						} అయితే ( ! (X1 <= Zero));
					ఒకవేళ (Q <= One) {
						Z2 = Y2;
						Z = Y;
						}
					}
				Y = Y + Two;
				X = X + Eight;
				Y2 = Y2 + X;
				ఒకవేళ (Y2 >= FourD) Y2 = Y2 - FourD;
				} అయితే ( ! (Y >= D));
			X8 = FourD - Z2;
			Q = (X8 + Z * Z) / FourD;
			X8 = X8 / Eight;
			ఒకవేళ (Q != FLOOR(Q)) Anomaly = True;
			లేకపోతే {
				Break = False;
				చేయి  {
					X = Z1 * Z;
					X = X - FLOOR(X / Radix) * Radix;
					ఒకవేళ (X == One) 
						Break = True;
					లేకపోతే
						Z1 = Z1 - One;
					} అయితే ( ! (Break || (Z1 <= Zero)));
				ఒకవేళ ((Z1 <= Zero) && (! Break)) Anomaly = True;
				లేకపోతే {
					ఒకవేళ (Z1 > RadixD2) Z1 = Z1 - Radix;
					చేయి  {
						NewD();
						} అయితే ( ! (U2 * D >= F9));
					ఒకవేళ (D * Radix - D != W - D) Anomaly = True;
					లేకపోతే {
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
						ఒకవేళ (D - Z2 != W - Z2) Anomaly = True;
						లేకపోతే {
							Y = (D - Z2) + (Z2 + (One - Z) * Half);
							X = (D - Z2) + (Z2 - Z + Q);
							SR3750();
							Y = (One + Z) * Half;
							X = Q;
							SR3750();
							ఒకవేళ (I == 0) Anomaly = True;
							}
						}
					}
				}
			}
		ఒకవేళ ((I == 0) || Anomaly) {
			BadCond(Failure, "Anomalous arithmetic with Integer < ");
			రాయి("Radix^Precision = %d\n", W);
			రాయి(" fails test whether sqrt rounds or chops.\n");
			SqRWrng = True;
			}
		}
	ఒకవేళ (! Anomaly) {
		ఒకవేళ (! ((MinSqEr < Zero) || (MaxSqEr > Zero))) {
			RSqrt = Rounded;
			రాయి("Square root appears to be correctly rounded.\n");
			}
		లేకపోతే  {
			ఒకవేళ ((MaxSqEr + U2 > U2 - Half) || (MinSqEr > Half)
				|| (MinSqEr + Radix < Half)) SqRWrng = True;
			లేకపోతే {
				RSqrt = Chopped;
				రాయి("Square root appears to be chopped.\n");
				}
			}
		}
	ఒకవేళ (SqRWrng) {
		రాయి("Square root is neither chopped nor correctly rounded.\n");
		రాయి("Observed errors run from %d ", MinSqEr - Half);
		రాయి("to %d ulps.\n", Half + MaxSqEr);
		TstCond (Serious, MaxSqEr - MinSqEr < Radix * Radix,
			"sqrt gets too many last digits wrong");
		}
	/*=============================================*/
	Milestone = 90;
	/*=============================================*/
	Pause();
	రాయి("Testing powers Z^i for small Integers Z and i.\n");
	N = 0;
	/* ... test powers of zero. */
	I = 0;
	Z = -Zero;
	M = 3;
	Break = False;
	చేయి  {
		X = One;
		SR3980();
		ఒకవేళ (I <= 10) {
			I = 1023;
			SR3980();
			}
		ఒకవేళ (Z == MinusOne) Break = True;
		లేకపోతే {
			Z = MinusOne;
			/* .. if(-1)^N is invalid, replace MinusOne by One. */
			I = - 4;
			}
		} అయితే ( ! Break);
	PrintIfNPositive();
	N1 = N;
	N = 0;
	Z = A1;
	M = (పూర్ణాంకం)FLOOR(Two * LOG(W) / LOG(A1));
	Break = False;
	చేయి  {
		X = Z;
		I = 1;
		SR3980();
		ఒకవేళ (Z == AInvrse) Break = True;
		లేకపోతే Z = AInvrse;
		} అయితే ( ! (Break));
	/*=============================================*/
		Milestone = 100;
	/*=============================================*/
	/*  Powers of Radix have been tested, */
	/*         next try a few primes     */
	M = NoTrials;
	Z = Three;
	చేయి  {
		X = Z;
		I = 1;
		SR3980();
		చేయి  {
			Z = Z + Two;
			} అయితే ( Three * FLOOR(Z / Three) == Z );
		} అయితే ( Z < Eight * Three );
	ఒకవేళ (N > 0) {
		రాయి("Errors like this may invalidate financial calculations\n");
		రాయి("\tinvolving interest rates.\n");
		}
	PrintIfNPositive();
	N += N1;
	ఒకవేళ (N == 0) రాయి("... no discrepancies found.\n");
	ఒకవేళ (N > 0) Pause();
	లేకపోతే రాయి("\n");
	/*=============================================*/
	/*విభజించు
	}
#include "paranoia.h"
void part6(VOID){
*/
	Milestone = 110;
	/*=============================================*/
	రాయి("Seeking Underflow thresholds UfThold and E0.\n");
	D = U1;
	ఒకవేళ (Precision != FLOOR(Precision)) {
		D = BInvrse;
		X = Precision;
		చేయి  {
			D = D * BInvrse;
			X = X - One;
			} అయితే ( X > Zero);
		}
	Y = One;
	Z = D;
	/* ... D is power of 1/Radix < 1. */
	చేయి  {
		C = Y;
		Y = Z;
		Z = Y * Y;
		} అయితే ((Y > Z) && (Z + Z > Z));
	Y = C;
	Z = Y * D;
	చేయి  {
		C = Y;
		Y = Z;
		Z = Y * D;
		} అయితే ((Y > Z) && (Z + Z > Z));
	ఒకవేళ (Radix < Two) HInvrse = Two;
	లేకపోతే HInvrse = Radix;
	H = One / HInvrse;
	/* ... 1/HInvrse == H == Min(1/Radix, 1/2) */
	CInvrse = One / C;
	E0 = C;
	Z = E0 * H;
	/* ...1/Radix^(BIG Integer) << 1 << CInvrse == 1/C */
	చేయి  {
		Y = E0;
		E0 = Z;
		Z = E0 * H;
		} అయితే ((E0 > Z) && (Z + Z > Z));
	UfThold = E0;
	E1 = Zero;
	Q = Zero;
	E9 = U2;
	S = One + E9;
	D = C * S;
	ఒకవేళ (D <= C) {
		E9 = Radix * U2;
		S = One + E9;
		D = C * S;
		ఒకవేళ (D <= C) {
			BadCond(Failure, "multiplication gets too many last digits wrong.\n");
			Underflow = E0;
			Y1 = Zero;
			PseudoZero = Z;
			Pause();
			}
		}
	లేకపోతే {
		Underflow = D;
		PseudoZero = Underflow * H;
		UfThold = Zero;
		చేయి  {
			Y1 = Underflow;
			Underflow = PseudoZero;
			ఒకవేళ (E1 + E1 <= E1) {
				Y2 = Underflow * HInvrse;
				E1 = FABS(Y1 - Y2);
				Q = Y1;
				ఒకవేళ ((UfThold == Zero) && (Y1 != Y2)) UfThold = Y1;
				}
			PseudoZero = PseudoZero * H;
			} అయితే ((Underflow > PseudoZero)
				&& (PseudoZero + PseudoZero > PseudoZero));
		}
	/* Comment line 4530 .. 4560 */
	ఒకవేళ (PseudoZero != Zero) {
		రాయి("\n");
		Z = PseudoZero;
	/* ... Test PseudoZero for "phoney- zero" violates */
	/* ... PseudoZero < Underflow or PseudoZero < PseudoZero + PseudoZero
		   ... */
		ఒకవేళ (PseudoZero <= Zero) {
			BadCond(Failure, "Positive expressions can underflow to an\n");
			రాయి("allegedly negative value\n");
			రాయి("PseudoZero that prints out as: %d .\n", PseudoZero);
			X = - PseudoZero;
			ఒకవేళ (X <= Zero) {
				రాయి("But -PseudoZero, which should be\n");
				రాయి("positive, isn't; it prints out as  %d .\n", X);
				}
			}
		లేకపోతే {
			BadCond(Flaw, "Underflow can stick at an allegedly positive\n");
			రాయి("value PseudoZero that prints out as %d .\n", PseudoZero);
			}
		TstPtUf();
		}
	/*=============================================*/
	Milestone = 120;
	/*=============================================*/
	ఒకవేళ (CInvrse * Y > CInvrse * Y1) {
		S = H * S;
		E0 = Underflow;
		}
	ఒకవేళ (! ((E1 == Zero) || (E1 == E0))) {
		BadCond(Defect, "");
		ఒకవేళ (E1 < E0) {
			రాయి("Products underflow at a higher");
			రాయి(" threshold than differences.\n");
			ఒకవేళ (PseudoZero == Zero) 
			E0 = E1;
			}
		లేకపోతే {
			రాయి("Difference underflows at a higher");
			రాయి(" threshold than products.\n");
			}
		}
	రాయి("Smallest strictly positive number found is E0 = %d .\n", E0);
	Z = E0;
	TstPtUf();
	Underflow = E0;
	ఒకవేళ (N == 1) Underflow = Y;
	I = 4;
	ఒకవేళ (E1 == Zero) I = 3;
	ఒకవేళ (UfThold == Zero) I = I - 2;
	UfNGrad = True;
	ఎంపిక (I)  {
		స్థితి	1:
		UfThold = Underflow;
		ఒకవేళ ((CInvrse * Q) != ((CInvrse * Y) * S)) {
			UfThold = Y;
			BadCond(Failure, "Either accuracy deteriorates as numbers\n");
			రాయి("approach a threshold = %d\n", UfThold);;
			రాయి(" coming down from %d\n", C);
			రాయి(" or else multiplication gets too many last digits wrong.\n");
			}
		Pause();
		ఆపు;
	
		స్థితి	2:
		BadCond(Failure, "Underflow confuses Comparison, which alleges that\n");
		రాయి("Q == Y while denying that |Q - Y| == 0; these values\n");
		రాయి("print out as Q = %d, Y = %016x .\n", Q, Y2);
		రాయి ("|Q - Y| = %d .\n" , FABS(Q - Y2));
		UfThold = Q;
		ఆపు;
	
		స్థితి	3:
		X = X;
		ఆపు;
	
		స్థితి	4:
		ఒకవేళ ((Q == UfThold) && (E1 == E0)
			&& (FABS( UfThold - E1 / E9) <= E1)) {
			UfNGrad = False;
			రాయి("Underflow is gradual; it incurs Absolute Error =\n");
			రాయి("(roundoff in UfThold) < E0.\n");
			Y = E0 * CInvrse;
			Y = Y * (OneAndHalf + U2);
			X = CInvrse * (One + U2);
			Y = Y / X;
			IEEE = (Y == E0);
			}
		}
	ఒకవేళ (UfNGrad) {
		రాయి("\n");
		sigsave = sigfpe;
		ఒకవేళ (setjmp(ovfl_buf)) {
			రాయి("Underflow / UfThold failed!\n");
			R = H + H;
			}
		లేకపోతే R = SQRT(Underflow / UfThold);
		sigsave = 0;
		ఒకవేళ (R <= H) {
			Z = R * UfThold;
			X = Z * (One + R * H * (One + H));
			}
		లేకపోతే {
			Z = UfThold;
			X = Z * (One + H * H * (One + H));
			}
		ఒకవేళ (! ((X == Z) || (X - Z != Zero))) {
			BadCond(Flaw, "");
			రాయి("X = %d\n\tis not equal to Z = %016x .\n", X, Z);
			Z9 = X - Z;
			రాయి("yet X - Z yields %d .\n", Z9);
			రాయి("    Should this NOT signal Underflow, ");
			రాయి("this is a SERIOUS DEFECT\nthat causes ");
			రాయి("confusion when innocent statements like\n");;
			రాయి("    if (X == Z)  ...  else");
			రాయి("  ... (f(X) - f(Z)) / (X - Z) ...\n");
			రాయి("encounter Division by Zero although actually\n");
			sigsave = sigfpe;
			ఒకవేళ (setjmp(ovfl_buf)) రాయి("X / Z fails!\n");
			లేకపోతే రాయి("X / Z = 1 + %d .\n", (X / Z - Half) - Half);
			sigsave = 0;
			}
		}
	రాయి("The Underflow threshold is %d, %s\n", UfThold,
		   " below which");
	రాయి("calculation may suffer larger Relative error than ");
	రాయి("merely roundoff.\n");
	Y2 = U1 * U1;
	Y = Y2 * Y2;
	Y2 = Y * U1;
	ఒకవేళ (Y2 <= UfThold) {
		ఒకవేళ (Y > E0) {
			BadCond(Defect, "");
			I = 5;
			}
		లేకపోతే {
			BadCond(Serious, "");
			I = 4;
			}
		రాయి("Range is too narrow; U1^%d Underflows.\n", I);
		}
	/*=============================================*/
	/*విభజించు
	}
#include "paranoia.h"
void part7(VOID){
*/
	Milestone = 130;
	/*=============================================*/
	Y = - FLOOR(Half - TwoForty * LOG(UfThold) / LOG(HInvrse)) / TwoForty;
	Y2 = Y + Y;
	రాయి("Since underflow occurs below the threshold\n");
	రాయి("UfThold = (%d) ^ (%016x)\nonly underflow ", HInvrse, Y);
	రాయి("should afflict the expression\n\t(%d) ^ (%016x);\n",
		HInvrse, Y2);
	రాయి("actually calculating yields:");
	ఒకవేళ (setjmp(ovfl_buf)) {
		sigsave = 0;
		BadCond(Serious, "trap on underflow.\n");
		}
	లేకపోతే {
		sigsave = sigfpe;
		V9 = POW(HInvrse, Y2);
		sigsave = 0;
		రాయి(" %d .\n", V9);
		ఒకవేళ (! ((V9 >= Zero) && (V9 <= (Radix + Radix + E9) * UfThold))) {
			BadCond(Serious, "this is not between 0 and underflow\n");
		రాయి("   threshold = %d .\n", UfThold);
		}
		లేకపోతే ఒకవేళ (! (V9 > UfThold * (One + E9)))
			రాయి("This computed value is O.K.\n");
		లేకపోతే {
			BadCond(Defect, "this is not between 0 and underflow\n");
			రాయి("   threshold = %d .\n", UfThold);
			}
		}
	/*=============================================*/
	Milestone = 140;
	/*=============================================*/
	రాయి("\n");
	/* ...calculate Exp2 == exp(2) == 7.389056099... */
	X = Zero;
	I = 2;
	Y = Two * Three;
	Q = Zero;
	N = 0;
	చేయి  {
		Z = X;
		I = I + 1;
		Y = Y / (I + I);
		R = Y + Q;
		X = Z + R;
		Q = (Z - X) + R;
		} అయితే(X > Z);
	Z = (OneAndHalf + One / Eight) + X / (OneAndHalf * ThirtyTwo);
	X = Z * Z;
	Exp2 = X * X;
	X = F9;
	Y = X - U1;
	రాయి("Testing X^((X + 1) / (X - 1)) vs. exp(2) = %d as X -> 1.\n",
		Exp2);
	కొరకు(I = 1;;) {
		Z = X - BInvrse;
		Z = (X + One) / (Z - (One - BInvrse));
		Q = POW(X, Z) - Exp2;
		ఒకవేళ (FABS(Q) > TwoForty * U2) {
			N = 1;
	 		V9 = (X - BInvrse) - (One - BInvrse);
			BadCond(Defect, "Calculated");
			రాయి(" %d for\n", POW(X,Z));
			రాయి("\t(1 + (%d) ^ (%016x);\n", V9, Z);
			రాయి("\tdiffers from correct value by %d .\n", Q);
			రాయి("\tThis much error may spoil financial\n");
			రాయి("\tcalculations involving tiny interest rates.\n");
			ఆపు;
			}
		లేకపోతే {
			Z = (Y - X) * Two + Y;
			X = Y;
			Y = Z;
			Z = One + (X - F9)*(X - F9);
			ఒకవేళ (Z > One && I < NoTrials) I++;
			లేకపోతే  {
				ఒకవేళ (X > One) {
					ఒకవేళ (N == 0)
					   రాయి("Accuracy seems adequate.\n");
					ఆపు;
					}
				లేకపోతే {
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
	రాయి("Testing powers Z^Q at four nearly extreme values.\n");
	N = 0;
	Z = A1;
	Q = FLOOR(Half - LOG(C) / LOG(A1));
	Break = False;
	చేయి  {
		X = CInvrse;
		Y = POW(Z, Q);
		IsYeqX();
		Q = - Q;
		X = C;
		Y = POW(Z, Q);
		IsYeqX();
		ఒకవేళ (Z < One) Break = True;
		లేకపోతే Z = AInvrse;
		} అయితే ( ! (Break));
	PrintIfNPositive();
	ఒకవేళ (N == 0) రాయి(" ... no discrepancies found.\n");
	రాయి("\n");
	
	/*=============================================*/
	Milestone = 160;
	/*=============================================*/
	Pause();
	రాయి("Searching for Overflow threshold:\n");
	రాయి("This may generate an error.\n");
	Y = - CInvrse;
	V9 = HInvrse * Y;
	sigsave = sigfpe;
	ఒకవేళ (setjmp(ovfl_buf)) { I = 0; V9 = Y; వెళ్ళు అధికప్రవాహం; }
	చేయి {
		V = Y;
		Y = V9;
		V9 = HInvrse * Y;
		} అయితే(V9 < Y);
	I = 1;
అధికప్రవాహం:
	sigsave = 0;
	Z = V9;
	రాయి("Can `Z = -Y' overflow?\n");
	రాయి("Trying it on Y = %d .\n", Y);
	V9 = - Y;
	V0 = V9;
	ఒకవేళ (V - Y == V + V0) రాయి("Seems O.K.\n");
	లేకపోతే {
		రాయి("finds a ");
		BadCond(Flaw, "-(-Y) differs from Y.\n");
		}
	ఒకవేళ (Z != Y) {
		BadCond(Serious, "");
		రాయి("overflow past %d\n\tshrinks to %016x .\n", Y, Z);
		}
	ఒకవేళ (I) {
		Y = V * (HInvrse * U2 - HInvrse);
		Z = Y + ((One - HInvrse) * U2) * V;
		ఒకవేళ (Z < V0) Y = Z;
		ఒకవేళ (Y < V0) V = Y;
		ఒకవేళ (V0 - V < V0) V = V0;
		}
	లేకపోతే {
		V = Y * (HInvrse * U2 - HInvrse);
		V = V + ((One - HInvrse) * U2) * Y;
		}
	రాయి("Overflow threshold is V  = %d .\n", V);
	ఒకవేళ (I) రాయి("Overflow saturates at V0 = %d .\n", V0);
	లేకపోతే రాయి("There is no saturation విలువ because \
the system traps on అధికప్రవాహం.\n");
	V9 = V * One;
	రాయి("No Overflow should be signaled for V * 1 = %d\n", V9);
	V9 = V / One;
	రాయి("                           nor for V / 1 = %d .\n", V9);
	రాయి("Any overflow signal separating this * from the one\n");
	రాయి("above is a DEFECT.\n");
	/*=============================================*/
	Milestone = 170;
	/*=============================================*/
	ఒకవేళ (!(-V < V && -V0 < V0 && -UfThold < V && UfThold < V)) {
		BadCond(Failure, "Comparisons involving ");
		రాయి("+-%d, +-%016x\nand +-%016x are confused by Overflow.",
			V, V0, UfThold);
		}
	/*=============================================*/
	Milestone = 175;
	/*=============================================*/
	రాయి("\n");
	కొరకు(Indx = 1; Indx <= 3; ++Indx) {
		ఎంపిక (Indx)  {
			స్థితి 1: Z = UfThold; ఆపు;
			స్థితి 2: Z = E0; ఆపు;
			స్థితి 3: Z = PseudoZero; ఆపు;
			}
		ఒకవేళ (Z != Zero) {
			V9 = SQRT(Z);
			Y = V9 * V9;
			ఒకవేళ (Y / (One - Radix * E9) < Z
			   || Y > (One + Radix * E9) * Z) { /* dgh: + E9 --> * E9 */
				ఒకవేళ (V9 > U1) BadCond(Serious, "");
				లేకపోతే BadCond(Defect, "");
				రాయి("Comparison alleges that what prints as Z = %d\n", Z);
				రాయి(" is too far from sqrt(Z) ^ 2 = %d .\n", Y);
				}
			}
		}
	/*=============================================*/
	Milestone = 180;
	/*=============================================*/
	కొరకు(Indx = 1; Indx <= 2; ++Indx) {
		ఒకవేళ (Indx == 1) Z = V;
		లేకపోతే Z = V0;
		V9 = SQRT(Z);
		X = (One - Radix * E9) * V9;
		V9 = V9 * X;
		ఒకవేళ (((V9 < (One - Two * Radix * E9) * Z) || (V9 > Z))) {
			Y = V9;
			ఒకవేళ (X < W) BadCond(Serious, "");
			లేకపోతే BadCond(Defect, "");
			రాయి("Comparison alleges that Z = %d\n", Z);
			రాయి(" is too far from sqrt(Z) ^ 2 (%d) .\n", Y);
			}
		}
	/*=============================================*/
	/*విభజించు
	}
#include "paranoia.h"
int part8(VOID){
*/
	Milestone = 190;
	/*=============================================*/
	Pause();
	X = UfThold * V;
	Y = Radix * Radix;
	ఒకవేళ (X*Y < One || X > Y) {
		ఒకవేళ (X * Y < U1 || X > Y/U1) BadCond(Defect, "Badly");
		లేకపోతే BadCond(Flaw, "");
			
		రాయి(" unbalanced range; UfThold * V = %d\n\t%s\n",
			X, "is too far from 1.\n");
		}
	/*=============================================*/
	Milestone = 200;
	/*=============================================*/
	కొరకు (Indx = 1; Indx <= 5; ++Indx)  {
		X = F9;
		ఎంపిక (Indx)  {
			స్థితి 2: X = One + U2; ఆపు;
			స్థితి 3: X = V; ఆపు;
			స్థితి 4: X = UfThold; ఆపు;
			స్థితి 5: X = Radix;
			}
		Y = X;
		sigsave = sigfpe;
		ఒకవేళ (setjmp(ovfl_buf))
			రాయి("  X / X  traps when X = %d\n", X);
		లేకపోతే {
			V9 = (Y / X - Half) - Half;
			ఒకవేళ (V9 == Zero) కొనసాగు;
			ఒకవేళ (V9 == - U1 && Indx < 5) BadCond(Flaw, "");
			లేకపోతే BadCond(Serious, "");
			రాయి("  X / X differs from 1 when X = %d\n", X);
			రాయి("  instead, X / X - 1/2 - 1/2 = %d .\n", V9);
			}
		sigsave = 0;
		}
	/*=============================================*/
	Milestone = 210;
	/*=============================================*/
	MyZero = Zero;
	రాయి("\n");
	రాయి("What message and/or values does Division by Zero produce?\n") ;
#నిర్వచితం_కాకపోతే NOPAUSE
	రాయి("This can interupt your program.  You can ");
	రాయి("skip this part if you wish.\n");
	రాయి("Do you wish to compute 1 / 0? ");
	fflush(stdout);
	పఠ (KEYBOARD, ch, 8);
	ఒకవేళ ((ch[0] == 'Y') || (ch[0] == 'y')) {
#అయితే_ముగింపు
		sigsave = sigfpe;
		రాయి("    Trying to compute 1 / 0 produces ...");
		ఒకవేళ (!setjmp(ovfl_buf)) రాయి("  %d .\n", One / MyZero);
		sigsave = 0;
#నిర్వచితం_కాకపోతే NOPAUSE
		}
	లేకపోతే రాయి("O.K.\n");
	రాయి("\nDo you wish to compute 0 / 0? ");
	fflush(stdout);
	పఠ (KEYBOARD, ch, 80);
	ఒకవేళ ((ch[0] == 'Y') || (ch[0] == 'y')) {
#అయితే_ముగింపు
		sigsave = sigfpe;
		రాయి("\n    Trying to compute 0 / 0 produces ...");
		ఒకవేళ (!setjmp(ovfl_buf)) రాయి("  %d .\n", Zero / MyZero);
		sigsave = 0;
#నిర్వచితం_కాకపోతే NOPAUSE
		}
	లేకపోతే రాయి("O.K.\n");
#అయితే_ముగింపు
	/*=============================================*/
	Milestone = 220;
	/*=============================================*/
	Pause();
	రాయి("\n");
	{
		స్థిర అక్షరం *సందేశం_2[] = {
			"FAILUREs  encountered =",
			"SERIOUS DEFECTs  discovered =",
			"DEFECTs  discovered =",
			"FLAWs  discovered =" };
		పూర్ణాంకం i;
		కొరకు(i = 0; i < 4; i++) ఒకవేళ (ErrCnt[i])
			రాయి("The number of  %-29s %d.\n",
				సందేశం_2[i], ErrCnt[i]);
		}
	రాయి("\n");
	ఒకవేళ ((ErrCnt[Failure] + ErrCnt[Serious] + ErrCnt[Defect]
			+ ErrCnt[Flaw]) > 0) {
		ఒకవేళ ((ErrCnt[Failure] + ErrCnt[Serious] + ErrCnt[
			Defect] == 0) && (ErrCnt[Flaw] > 0)) {
			రాయి("The arithmetic diagnosed seems ");
			రాయి("Satisfactory though flawed.\n");
			}
		ఒకవేళ ((ErrCnt[Failure] + ErrCnt[Serious] == 0)
			&& ( ErrCnt[Defect] > 0)) {
			రాయి("The arithmetic diagnosed may be Acceptable\n");
			రాయి("despite inconvenient Defects.\n");
			}
		ఒకవేళ ((ErrCnt[Failure] + ErrCnt[Serious]) > 0) {
			రాయి("The arithmetic diagnosed has ");
			రాయి("unacceptable Serious Defects.\n");
			}
		ఒకవేళ (ErrCnt[Failure] > 0) {
			రాయి("Potentially fatal FAILURE may have spoiled this");
			రాయి(" program's subsequent diagnoses.\n");
			}
		}
	లేకపోతే {
		రాయి("No failures, defects nor flaws have been discovered.\n");
		ఒకవేళ (! ((RMult == Rounded) && (RDiv == Rounded)
			&& (RAddSub == Rounded) && (RSqrt == Rounded))) 
			రాయి("The arithmetic diagnosed seems Satisfactory.\n");
		లేకపోతే {
			ఒకవేళ (Sticky_బిట్టు >= One &&
				(Radix - Two) * (Radix - Nine - One) == Zero) {
				రాయి("Rounding appears to conform to ");
				రాయి("the proposed IEEE standard P");
				ఒకవేళ ((Radix == Two) &&
					 ((Precision - Four * Three * Two) *
					  ( Precision - TwentySeven -
					   TwentySeven + One) == Zero)) 
					రాయి("754");
				లేకపోతే రాయి("854");
				ఒకవేళ (IEEE) రాయి(".\n");
				లేకపోతే {
					రాయి(",\nexcept for possibly Double Rounding");
					రాయి(" during Gradual Underflow.\n");
					}
				}
			రాయి("The arithmetic diagnosed appears to be Excellent!\n");
			}
		}
	ఒకవేళ (fpecount)
		రాయి("\nA total of %d floating point exceptions were registered.\n",
			fpecount);
	రాయి("END OF TEST $\n");
  __asm__("ebreak");
	//return 0;
	}

/*SPLIT subs.c
#include "paranoia.h"
*/

 FLOAT
Sign (FP X)
#నిర్వచితమైతే KR_శీర్షికలు
FLOAT X;
#అయితే_ముగింపు
{ తిరిగి X >= 0. ? 1.0 : -1.0; }

 శూన్య
Pause(VOID)
{
#నిర్వచితం_కాకపోతే NOPAUSE
	అక్షరం ch[8];

	రాయి("\nTo continue, press RETURN");
	fflush(stdout);
	పఠ(KEYBOARD, ch, 8);
#అయితే_ముగింపు
	రాయి("\nDiagnosis resumes after milestone Number %d", Milestone);
	రాయి("          Page: %d\n\n", పుట_No);
	++Milestone;
	++పుట_No;
	}

 శూన్య
TstCond (INT K, INT Valid, CHARP T)
#నిర్వచితమైతే KR_శీర్షికలు
పూర్ణాంకం K, Valid;
అక్షరం *T;
#అయితే_ముగింపు
{ ఒకవేళ (! Valid) { BadCond(K,T); రాయి(".\n"); } }

 శూన్య
BadCond(INT K, CHARP T)
#నిర్వచితమైతే KR_శీర్షికలు
పూర్ణాంకం K;
అక్షరం *T;
#అయితే_ముగింపు
{
	స్థిర అక్షరం *సందేశం_2[] = { "FAILURE", "SERIOUS DEFECT", "DEFECT", "FLAW" };

	ErrCnt [K] = ErrCnt [K] + 1;
	రాయి("%s:  %s", సందేశం_2[K], T);
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
	తిరిగి(Random1);
	}

 శూన్య
SqXMinX (INT Err_రకం)
#నిర్వచితమైతే KR_శీర్షికలు
పూర్ణాంకం Err_రకం;
#అయితే_ముగింపు
{
	FLOAT XA, XB;
	
	XB = X * BInvrse;
	XA = X - XB;
	SqEr = ((SQRT(X * X) - XB) - XA) / OneUlp;
	ఒకవేళ (SqEr != Zero) {
		ఒకవేళ (SqEr < MinSqEr) MinSqEr = SqEr;
		ఒకవేళ (SqEr > MaxSqEr) MaxSqEr = SqEr;
		J = J + 1.0;
		BadCond(Err_రకం, "\n");
		రాయి("sqrt( %d) - %016x  = %016x\n", X * X, X, OneUlp * SqEr);
		రాయి("\tinstead of correct value 0 .\n");
		}
	}

 శూన్య
NewD(VOID)
{
	X = Z1 * Q;
	X = FLOOR(Half - X / Radix) * Radix + X;
	Q = (Q - X * Z) / Radix + X * X * (D / Radix);
	Z = Z - Two * X * D;
	ఒకవేళ (Z <= Zero) {
		Z = - Z;
		Z1 = - Z1;
		}
	D = Radix * D;
	}

 శూన్య
SR3750(VOID)
{
	ఒకవేళ (! ((X - Radix < Z2 - Radix) || (X - Z2 > W - Z2))) {
		I = I + 1;
		X2 = SQRT(X * D);
		Y2 = (X2 - Z2) - (Y - Z2);
		X2 = X8 / (Y - Half);
		X2 = X2 - Half * X2 * X2;
		SqEr = (Y2 + Half) + (Half - X2);
		ఒకవేళ (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = Y2 - X2;
		ఒకవేళ (SqEr > MaxSqEr) MaxSqEr = SqEr;
		}
	}

 శూన్య
IsYeqX(VOID)
{
	ఒకవేళ (Y != X) {
		ఒకవేళ (N <= 0) {
			ఒకవేళ (Z == Zero && Q <= Zero)
				రాయి("WARNING:  computing\n");
			లేకపోతే BadCond(Defect, "computing\n");
			రాయి("\t(%d) ^ (%016x)\n", Z, Q);
			రాయి("\tyielded %d;\n", Y);
			రాయి("\twhich compared unequal to correct %d ;\n",
				X);
			రాయి("\t\tthey differ by %d .\n", Y - X);
			}
		N = N + 1; /* ... count discrepancies. */
		}
	}

 శూన్య
SR3980(VOID)
{
	చేయి {
		Q = (FLOAT) I;
		Y = POW(Z, Q);
		IsYeqX();
		ఒకవేళ (++I > M) ఆపు;
		X = Z * X;
		} అయితే ( X < W );
	}

 శూన్య
PrintIfNPositive(VOID)
{
	ఒకవేళ (N > 0) రాయి("Similar discrepancies have occurred %d times.\n", N);
	}

 శూన్య
TstPtUf(VOID)
{
	N = 0;
	ఒకవేళ (Z != Zero) {
		రాయి("Since comparison denies Z = 0, evaluating ");
		రాయి("(Z + Z) / Z should be safe.\n");
		sigsave = sigfpe;
		ఒకవేళ (setjmp(ovfl_buf)) వెళ్ళు very_serious;
		Q9 = (Z + Z) / Z;
		రాయి("What the machine gets for (Z + Z) / Z is  %d .\n",
			Q9);
		ఒకవేళ (FABS(Q9 - Two) < Radix * U2) {
			రాయి("This is O.K., provided Over/Underflow");
			రాయి(" has NOT just been signaled.\n");
			}
		లేకపోతే {
			ఒకవేళ ((Q9 < One) || (Q9 > Two)) {
very_serious:
				N = 1;
				ErrCnt [Serious] = ErrCnt [Serious] + 1;
				రాయి("This is a VERY SERIOUS DEFECT!\n");
				}
			లేకపోతే {
				N = 1;
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				రాయి("This is a DEFECT!\n");
				}
			}
		sigsave = 0;
		V9 = Z * One;
		Random1 = V9;
		V9 = One * Z;
		Random2 = V9;
		V9 = Z / One;
		ఒకవేళ ((Z == Random1) && (Z == Random2) && (Z == V9)) {
			ఒకవేళ (N > 0) Pause();
			}
		లేకపోతే {
			N = 1;
			BadCond(Defect, "What prints as Z = ");
			రాయి("%d\n\tcompares different from  ", Z);
			ఒకవేళ (Z != Random1) రాయి("Z * 1 = %d ", Random1);
			ఒకవేళ (! ((Z == Random2)
				|| (Random2 == Random1)))
				రాయి("1 * Z == %d\n", Random2);
			ఒకవేళ (! (Z == V9)) రాయి("Z / 1 = %d\n", V9);
			ఒకవేళ (Random2 != Random1) {
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				BadCond(Defect, "Multiplication does not commute!\n");
				రాయి("\tComparison alleges that 1 * Z = %d\n",
					Random2);
				రాయి("\tdiffers from Z * 1 = %d\n", Random1);
				}
			Pause();
			}
		}
	}

 శూన్య
notify(CHARP s)
#నిర్వచితమైతే KR_శీర్షికలు
 అక్షరం *s;
#అయితే_ముగింపు
{
	రాయి("%s test appears to be inconsistent...\n", s);
	రాయి("   PLEASE NOTIFY KARPINKSI!\n");
	}

/*SPLIT msgs.c
#include "paranoia.h"
*/

 శూన్య
msglist(CHARPP s)
#నిర్వచితమైతే KR_శీర్షికలు
అక్షరం **s;
#అయితే_ముగింపు
{ అయితే(*s) రాయి("%s\n", *s++); }

 శూన్య
Instructions(VOID)
{
  స్థిర అక్షరం *instr[] = {
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

 శూన్య
Heading(VOID)
{
  స్థిర అక్షరం *తల[] = {
	"Users are invited to help debug and augment this program so it will",
	"cope with unanticipated and newly uncovered arithmetic pathologies.\n",
	"Please send suggestions and interesting results to",
	"\tRichard Karpinski",
	"\tComputer Center U-76",
	"\tUniversity of California",
	"\tSan Francisco, CA 94143-0704, USA\n",
	"In doing so, please include the following information:",
#నిర్వచితమైతే Single
	"\tPrecision:\tsingle;",
#లేకపోతే
	"\tPrecision:\tdouble;",
#అయితే_ముగింపు
	"\tVersion:\t10 February 1989;",
	"\tComputer:\n",
	"\tCompiler:\n",
	"\tOptimization level:\n",
	"\tOther relevant compiler options:",
	0};

	msglist(తల);
	}

 శూన్య
Characteristics(VOID)
{
	స్థిర అక్షరం *chars[] = {
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

 శూన్య
History(VOID)
{ /* History */
 /* Converted from Brian Wichmann's Pascal version to C by Thos Sumner,
	with further massaging by David M. Gay. */

  స్థిర అక్షరం *hist[] = {
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
