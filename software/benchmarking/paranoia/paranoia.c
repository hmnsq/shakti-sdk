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

#شامل <stdio.h>
#تعریف_کرو NOSIGNAL
#تعریف_کرو NOPAUSE
#اگر_غیر_تعریف_شدہ NOSIGNAL
#شامل <signal.h>
#اگر_ختم
#شامل <setjmp.h>
#اگر_تعریف_شدہ Single
#تعریف_کرو FLOAT اعشاری
#تعریف_کرو FABS(x) (اعشاری)fabs((دوہرا)(x))
#تعریف_کرو FLOOR(x) (اعشاری)floor((دوہرا)(x))
#تعریف_کرو LOG(x) (اعشاری)لوگارتھم((دوہرا)(x))
#تعریف_کرو POW(x,y) (اعشاری)قوت((دوہرا)(x),(دوہرا)(y))
#تعریف_کرو SQRT(x) (اعشاری)جذر((دوہرا)(x))
#ورنہ
#تعریف_کرو FLOAT دوہرا
#تعریف_کرو FABS(x) fabs(x)
#تعریف_کرو FLOOR(x) floor(x)
#تعریف_کرو LOG(x) لوگارتھم(x)
#تعریف_کرو POW(x,y) قوت(x,y)
#تعریف_کرو SQRT(x) جذر(x)
#اگر_ختم

jmp_buf ovfl_buf;
#اگر_تعریف_شدہ KR_سرخیاں
#تعریف_کرو VOID /* void */
#تعریف_کرو INT /* int */
#تعریف_کرو FP /* FLOAT */
#تعریف_کرو CHARP /* char * */
#تعریف_کرو CHARPP /* char ** */
خارجی دوہرا fabs(), floor(), لوگارتھم(), قوت(), جذر();
خارجی خالی باہر_نکلو();
قسمتعریف خالی (*Sig_type)();
FLOAT Sign(), Random();
خارجی خالی BadCond();
خارجی خالی SqXMinX();
خارجی خالی TstCond();
خارجی خالی notify();
خارجی صحیح اقرأ();
#ورنہ
#تعریف_کرو VOID خالی
#تعریف_کرو INT صحیح
#تعریف_کرو FP FLOAT
#تعریف_کرو CHARP حرف *
#تعریف_کرو CHARPP حرف **
#اگر_تعریف_شدہ __STDC__
#شامل <stdlib.h>
#شامل <math.h>
#ورنہ
#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم
خارجی دوہرا fabs(دوہرا), floor(دوہرا), لوگارتھم(دوہرا);
خارجی دوہرا قوت(دوہرا,دوہرا), جذر(دوہرا);
خارجی خالی باہر_نکلو(INT);
#اگر_تعریف_شدہ __cplusplus
	}
#اگر_ختم
#اگر_ختم
قسمتعریف خالی (*Sig_type)(صحیح);
FLOAT Sign(FLOAT), Random(خالی);
خارجی خالی BadCond(صحیح, حرف*);
خارجی خالی SqXMinX(صحیح);
خارجی خالی TstCond(صحیح, صحیح, حرف*);
خارجی خالی notify(حرف*);
خارجی صحیح اقرأ(صحیح, حرف*, صحیح);
#اگر_ختم
#تعریف_منسوخ V9
خارجی خالی Characteristics(VOID);
خارجی خالی Heading(VOID);
خارجی خالی History(VOID);
خارجی خالی Instructions(VOID);
خارجی خالی IsYeqX(VOID);
خارجی خالی NewD(VOID);
خارجی خالی Pause(VOID);
خارجی خالی PrintIfNPositive(VOID);
خارجی خالی SR3750(VOID);
خارجی خالی SR3980(VOID);
خارجی خالی TstPtUf(VOID);

Sig_type sigsave;

#تعریف_کرو KEYBOARD 0

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
صحیح NoTrials = 20; /*Number of tests for commutativity. */
#تعریف_کرو False 0
#تعریف_کرو True 1

/* Definitions for declared types 
	Guard == (Yes, No);
	Rounding == (Chopped, Rounded, Other);
	Message == packed array [1..40] of char;
	Class == (Flaw, Defect, Serious, Failure);
	  */
#تعریف_کرو Yes 1
#تعریف_کرو No  0
#تعریف_کرو Chopped 2
#تعریف_کرو Rounded 1
#تعریف_کرو Other   0
#تعریف_کرو Flaw    3
#تعریف_کرو Defect  2
#تعریف_کرو Serious 1
#تعریف_کرو Failure 0
قسمتعریف صحیح Guard, Rounding, Class;
قسمتعریف حرف پیغام;

/* Declarations of Variables */
صحیح Indx;
حرف ch[8];
FLOAT AInvrse, A1;
FLOAT C, CInvrse;
FLOAT D, FourD;
FLOAT E0, E1, Exp2, E3, MinSqEr;
FLOAT SqEr, MaxSqEr, E9;
FLOAT تیسرا;
FLOAT F6, F9;
FLOAT H, HInvrse;
صحیح I;
FLOAT Sticky_ثنائی_ہندسہ, J;
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
صحیح ErrCnt[4];
صحیح fpecount;
صحیح Milestone;
صحیح صفحہ_No;
صحیح M, N, N1;
Guard GMult, GDiv, GAddSub;
Rounding RMult, RDiv, RAddSub, RSqrt;
صحیح Break, مکمل, NotMonot, Monot, Anomaly, IEEE,
		SqRWrng, UfNGrad;
/* Computed constants. */
/*U1  gap below 1.0, i.e, 1.0-U1 is next number below 1.0 */
/*U2  gap above 1.0, i.e, 1.0+U2 is next number above 1.0 */

/* floating point exception receiver */
 خالی
sigfpe(INT x)
{
	fpecount++;
	لکھو("\n* * * FLOATING-POINT ERROR %d * * *\n", x);
	fflush(stdout);
	اگر (sigsave) {
#اگر_غیر_تعریف_شدہ NOSIGNAL
		اشارہ(SIGFPE, sigsave);
#اگر_ختم
		sigsave = 0;
		longjmp(ovfl_buf, 1);
		}
	باہر_نکلو(1);
}

مین(VOID)
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
	صفحہ_No = 1;
	/*=============================================*/
	Milestone = 0;
	/*=============================================*/
#اگر_غیر_تعریف_شدہ NOSIGNAL
	اشارہ(SIGFPE, sigfpe);
#اگر_ختم
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
	لکھو("Program is now RUNNING tests on small integers:\n");
	
	TstCond (Failure, (Zero + Zero == Zero) && (One - One == Zero)
		   && (One > Zero) && (One + One == Two),
			"0+0 != 0, 1-1 != 0, 1 <= 0, or 1+1 != 2");
	Z = - Zero;
	اگر (Z != 0.0) {
		ErrCnt[Failure] = ErrCnt[Failure] + 1;
		لکھو("Comparison alleges that -0.0 is Non-zero!\n");
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
	/*بانٹو
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
	اگر (ErrCnt[Failure] == 0) {
		لکھو("-1, 0, 1/2, 1, 2, 3, 4, 5, 9, 27, 32 & 240 are O.K.\n");
		لکھو("\n");
		}
	لکھو("Searching for Radix and Precision.\n");
	W = One;
	کرو  {
		W = W + W;
		Y = W + One;
		Z = Y - W;
		Y = Z - One;
		} جب (MinusOne + FABS(Y) < Zero);
	/*.. now W is just big enough that |((W+1)-W)-1| >= 1 ...*/
	Precision = Zero;
	Y = One;
	کرو  {
		Radix = W + Y;
		Y = Y + Y;
		Radix = Radix - W;
		} جب ( Radix == Zero);
	اگر (Radix < Two) Radix = One;
	لکھو("Radix = %d .\n", Radix);
	اگر (Radix != 1) {
		W = One;
		کرو  {
			Precision = Precision + One;
			W = W * Radix;
			Y = W + One;
			} جب ((Y - W) == One);
		}
	/*... now W == Radix^Precision is barely too big to satisfy (W+1)-W == 1
			                              ...*/
	U1 = One / W;
	U2 = Radix * U1;
	لکھو("Closest relative separation found is U1 = %d .\n\n", U1);
	لکھو("Recalculating radix and precision\n ");
	
	/*save old values*/
	E0 = Radix;
	E1 = U1;
	E9 = U2;
	E3 = Precision;
	
	X = Four / Three;
	تیسرا = X - One;
	F6 = Half - تیسرا;
	X = F6 + F6;
	X = FABS(X - تیسرا);
	اگر (X < U2) X = U2;
	
	/*... now X = (unknown no.) ulps of 1+...*/
	کرو  {
		U2 = X;
		Y = Half * U2 + ThirtyTwo * U2 * U2;
		Y = One + Y;
		X = Y - One;
		} جب ( ! ((U2 <= X) || (X <= Zero)));
	
	/*... now U2 == 1 ulp of 1 + ... */
	X = Two / Three;
	F6 = X - Half;
	تیسرا = F6 + F6;
	X = تیسرا - Half;
	X = FABS(X + F6);
	اگر (X < U1) X = U1;
	
	/*... now  X == (unknown no.) ulps of 1 -... */
	کرو  {
		U1 = X;
		Y = Half * U1 + ThirtyTwo * U1 * U1;
		Y = Half - Y;
		X = Half + Y;
		Y = Half - X;
		X = Half + Y;
		} جب ( ! ((U1 <= X) || (X <= Zero)));
	/*... now U1 == 1 ulp of 1 - ... */
	اگر (U1 == E1) لکھو("confirms closest relative separation U1 .\n");
	ورنہ لکھو("gets better closest relative separation U1 = %d .\n", U1);
	W = One / U1;
	F9 = (Half - U1) + Half;
	Radix = FLOOR(0.01 + U2 / U1);
	اگر (Radix == E0) لکھو("Radix confirmed.\n");
	ورنہ لکھو("MYSTERY: recalculated Radix = %d .\n", Radix);
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
	اگر (Radix != One)  {
		X = - TwoForty * LOG(U1) / LOG(Radix);
		Y = FLOOR(Half + X);
		اگر (FABS(X - Y) * Four < One) X = Y;
		Precision = X / TwoForty;
		Y = FLOOR(Half + Precision);
		اگر (FABS(Precision - Y) * TwoForty < Half) Precision = Y;
		}
	اگر ((Precision != FLOOR(Precision)) || (Radix == One)) {
		لکھو("Precision cannot be characterized by an Integer number\n");
		لکھو("of significant digits but, by itself, this is a minor flaw.\n");
		}
	اگر (Radix == One) 
		لکھو("logarithmic encoding has precision characterized solely by U1.\n");
	ورنہ لکھو("The number of significant digits of the Radix is %d .\n",
			Precision);
	TstCond (Serious, U2 * Nine * Nine * TwoForty < One,
		   "Precision worse than 5 decimal figures  ");
	/*=============================================*/
	Milestone = 30;
	/*=============================================*/
	/* Test for extra-precise subepressions */
	X = FABS(((Four / Three - One) - One / Four) * Three - One / Four);
	کرو  {
		Z2 = X;
		X = (One + (Half * Z2 + ThirtyTwo * Z2 * Z2)) - One;
		} جب ( ! ((Z2 <= X) || (X <= Zero)));
	X = Y = Z = FABS((Three / Four - Two / Three) * Three - One / Four);
	کرو  {
		Z1 = Z;
		Z = (One / Two - ((One / Two - (Half * Z1 + ThirtyTwo * Z1 * Z1))
			+ One / Two)) + One / Two;
		} جب ( ! ((Z1 <= Z) || (Z <= Zero)));
	کرو  {
		کرو  {
			Y1 = Y;
			Y = (Half - ((Half - (Half * Y1 + ThirtyTwo * Y1 * Y1)) + Half
				)) + Half;
			} جب ( ! ((Y1 <= Y) || (Y <= Zero)));
		X1 = X;
		X = ((Half * X1 + ThirtyTwo * X1 * X1) - F9) + F9;
		} جب ( ! ((X1 <= X) || (X <= Zero)));
	اگر ((X1 != Y1) || (X1 != Z1)) {
		BadCond(Serious, "Disagreements among the values X1, Y1, Z1,\n");
		لکھو("respectively  %d,  %016x,  %016x,\n", X1, Y1, Z1);
		لکھو("are symptoms of inconsistencies introduced\n");
		لکھو("by extra-precise evaluation of arithmetic subexpressions.\n");
		notify("Possibly some part of this");
		اگر ((X1 == U1) || (Y1 == U1) || (Z1 == U1))  لکھو(
			"That feature is not tested further by this program.\n") ;
		}
	ورنہ  {
		اگر ((Z1 != U1) || (Z2 != U2)) {
			اگر ((Z1 >= U1) || (Z2 >= U2)) {
				BadCond(Failure, "");
				notify("Precision");
				لکھو("\tU1 = %d, Z1 - U1 = %016x\n",U1,Z1-U1);
				لکھو("\tU2 = %d, Z2 - U2 = %016x\n",U2,Z2-U2);
				}
			ورنہ {
				اگر ((Z1 <= Zero) || (Z2 <= Zero)) {
					لکھو("Because of unusual Radix = %d", Radix);
					لکھو(", or exact rational arithmetic a result\n");
					لکھو("Z1 = %d, or Z2 = %016x ", Z1, Z2);
					notify("of an\nextra-precision");
					}
				اگر (Z1 != Z2 || Z1 > Zero) {
					X = Z1 / U1;
					Y = Z2 / U2;
					اگر (Y > X) X = Y;
					Q = - LOG(X);
					لکھو("Some subexpressions appear to be calculated extra\n");
					لکھو("precisely with about %d extra B-digits, i.e.\n",
						(Q / LOG(Radix)));
					لکھو("roughly %d extra significant decimals.\n",
						Q / LOG(10.));
					}
				لکھو("That feature is not tested further by this program.\n");
				}
			}
		}
	Pause();
	/*=============================================*/
	/*بانٹو
	}
#include "paranoia.h"
void part3(VOID){
*/
	Milestone = 35;
	/*=============================================*/
	اگر (Radix >= Two) {
		X = W / (Radix * Radix);
		Y = X + One;
		Z = Y - X;
		T = Z + U2;
		X = T - Z;
		TstCond (Failure, X == U2,
			"Subtraction is not normalized X=Y,X+Z != Y+Z!");
		اگر (X == U2) لکھو(
			"Subtraction appears to be normalized, as it should be.");
		}
	لکھو("\nChecking for guard digit in *, /, and -.\n");
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
	اگر ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)) GMult = Yes;
	ورنہ {
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
	اگر ((X == Zero) && (Y == Zero) && (Z == Zero)) GDiv = Yes;
	ورنہ {
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
	Sticky_ثنائی_ہندسہ = T / Radix;
	X = R - X;
	Y = Sticky_ثنائی_ہندسہ - Y;
	TstCond (Failure, X == Zero && Y == Zero,
			"* and/or / gets too many last digits wrong");
	Y = One - U1;
	X = One - F9;
	Y = One - Y;
	T = Radix - U2;
	Z = Radix - BMinusU2;
	T = Radix - T;
	اگر ((X == U1) && (Y == U1) && (Z == U2) && (T == U2)) GAddSub = Yes;
	ورنہ {
		GAddSub = No;
		TstCond (Serious, False,
			"- lacks Guard Digit, so cancellation is obscured");
		}
	اگر (F9 != One && F9 - One >= Zero) {
		BadCond(Serious, "comparison alleges  (1-U1) < 1  although\n");
		لکھو("  subtraction yields  (1-U1) - 1 = 0 , thereby vitiating\n");
		لکھو("  such precautions against division by zero as\n");
		لکھو("  ...  if (X == 1.0) {.....} else {.../(X-1.0)...}\n");
		}
	اگر (GMult == Yes && GDiv == Yes && GAddSub == Yes) لکھو(
		"     *, /, and - appear to have guard digits, as they should.\n");
	/*=============================================*/
	Milestone = 40;
	/*=============================================*/
	Pause();
	لکھو("Checking rounding on multiply, divide and add/subtract.\n");
	RMult = Other;
	RDiv = Other;
	RAddSub = Other;
	RadixD2 = Radix / Two;
	A1 = Two;
	مکمل = False;
	کرو  {
		AInvrse = Radix;
		کرو  {
			X = AInvrse;
			AInvrse = AInvrse / A1;
			} جب ( ! (FLOOR(AInvrse) != AInvrse));
		مکمل = (X == One) || (A1 > Three);
		اگر (! مکمل) A1 = Nine + One;
		} جب ( ! (مکمل));
	اگر (X == One) A1 = Radix;
	AInvrse = One / A1;
	X = A1;
	Y = AInvrse;
	مکمل = False;
	کرو  {
		Z = X * Y - Half;
		TstCond (Failure, Z == Half,
			"X * (1/X) differs from 1");
		مکمل = X == Radix;
		X = Radix;
		Y = One / X;
		} جب ( ! (مکمل));
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
	اگر ((X == Zero) && (Y == Zero) && (Z == Zero) && (T <= Zero)) {
		X = (OneAndHalf + U2) * Y2;
		Y = OneAndHalf - U2 - U2;
		Z = OneAndHalf + U2 + U2;
		T = (OneAndHalf - U2) * Y1;
		X = X - (Z + U2);
		Sticky_ثنائی_ہندسہ = Y * Y1;
		S = Z * Y2;
		T = T - Y;
		Y = (U2 - Y) + Sticky_ثنائی_ہندسہ;
		Z = S - (Z + U2 + U2);
		Sticky_ثنائی_ہندسہ = (Y2 + U2) * Y1;
		Y1 = Y2 * Y1;
		Sticky_ثنائی_ہندسہ = Sticky_ثنائی_ہندسہ - Y2;
		Y1 = Y1 - Half;
		اگر ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)
			&& ( Sticky_ثنائی_ہندسہ == Zero) && (Y1 == Half)) {
			RMult = Rounded;
			لکھو("Multiplication appears to round correctly.\n");
			}
		ورنہ	اگر ((X + U2 == Zero) && (Y < Zero) && (Z + U2 == Zero)
				&& (T < Zero) && (Sticky_ثنائی_ہندسہ + U2 == Zero)
				&& (Y1 < Half)) {
				RMult = Chopped;
				لکھو("Multiplication appears to chop.\n");
				}
			ورنہ لکھو("* is neither chopped nor correctly rounded.\n");
		اگر ((RMult == Rounded) && (GMult == No)) notify("Multiplication");
		}
	ورنہ لکھو("* is neither chopped nor correctly rounded.\n");
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
	اگر (! ((X > Zero) || (Y > Zero) || (Z > Zero) || (T > Zero))) {
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
		اگر ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)
			&& (Y2 == Zero) && (Y2 == Zero)
			&& (Y1 - Half == F9 - Half )) {
			RDiv = Rounded;
			لکھو("Division appears to round correctly.\n");
			اگر (GDiv == No) notify("Division");
			}
		ورنہ اگر ((X < Zero) && (Y < Zero) && (Z < Zero) && (T < Zero)
			&& (Y2 < Zero) && (Y1 - Half < F9 - Half)) {
			RDiv = Chopped;
			لکھو("Division appears to chop.\n");
			}
		}
	اگر (RDiv == Other) لکھو("/ is neither chopped nor correctly rounded.\n");
	BInvrse = One / Radix;
	TstCond (Failure, (BInvrse * Radix - Half == Half),
		   "Radix * ( 1 / Radix ) differs from 1");
	/*=============================================*/
	/*بانٹو
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
	اگر ((X == Zero) && (Y == Zero)) {
		RAddSub = Chopped;
		لکھو("Add/Subtract appears to be chopped.\n");
		}
	اگر (GAddSub == Yes) {
		X = (Half + U2) * U2;
		Y = (Half - U2) * U2;
		X = One + X;
		Y = One + Y;
		X = (One + U2) - X;
		Y = One - Y;
		اگر ((X == Zero) && (Y == Zero)) {
			X = (Half + U2) * U1;
			Y = (Half - U2) * U1;
			X = One - X;
			Y = One - Y;
			X = F9 - X;
			Y = One - Y;
			اگر ((X == Zero) && (Y == Zero)) {
				RAddSub = Rounded;
				لکھو("Addition/Subtraction appears to round correctly.\n");
				اگر (GAddSub == No) notify("Add/Subtract");
				}
			ورنہ لکھو("Addition/Subtraction neither rounds nor chops.\n");
			}
		ورنہ لکھو("Addition/Subtraction neither rounds nor chops.\n");
		}
	ورنہ لکھو("Addition/Subtraction neither rounds nor chops.\n");
	S = One;
	X = One + Half * (One + Half);
	Y = (One + U2) * Half;
	Z = X - Y;
	T = Y - X;
	Sticky_ثنائی_ہندسہ = Z + T;
	اگر (Sticky_ثنائی_ہندسہ != Zero) {
		S = Zero;
		BadCond(Flaw, "(X - Y) + (Y - X) is non zero!\n");
		}
	Sticky_ثنائی_ہندسہ = Zero;
	اگر ((GMult == Yes) && (GDiv == Yes) && (GAddSub == Yes)
		&& (RMult == Rounded) && (RDiv == Rounded)
		&& (RAddSub == Rounded) && (FLOOR(RadixD2) == RadixD2)) {
		لکھو("Checking for sticky bit.\n");
		X = (Half + U1) * U2;
		Y = Half * U2;
		Z = One + Y;
		T = One + X;
		اگر ((Z - One <= Zero) && (T - One >= U2)) {
			Z = T + Y;
			Y = Z - X;
			اگر ((Z - T >= U2) && (Y - T == Zero)) {
				X = (Half + U1) * U1;
				Y = Half * U1;
				Z = One - Y;
				T = One - X;
				اگر ((Z - One == Zero) && (T - F9 == Zero)) {
					Z = (Half - U1) * U1;
					T = F9 - Z;
					Q = F9 - Y;
					اگر ((T - F9 == Zero) && (F9 - U1 - Q == Zero)) {
						Z = (One + U2) * OneAndHalf;
						T = (OneAndHalf + U2) - Z + U2;
						X = One + Half / Radix;
						Y = One + Radix * U2;
						Z = X * Y;
						اگر (T == Zero && X + Radix * U2 - Z == Zero) {
							اگر (Radix != Two) {
								X = Two + U2;
								Y = X / Two;
								اگر ((Y - One == Zero)) Sticky_ثنائی_ہندسہ = S;
								}
							ورنہ Sticky_ثنائی_ہندسہ = S;
							}
						}
					}
				}
			}
		}
	اگر (Sticky_ثنائی_ہندسہ == One) لکھو("Sticky bit apparently used correctly.\n");
	ورنہ لکھو("Sticky bit used incorrectly or not at all.\n");
	TstCond (Flaw, !(GMult == No || GDiv == No || GAddSub == No ||
			RMult == Other || RDiv == Other || RAddSub == Other),
		"lack(s) کا guard digits or failure(s) مقصد correctly round or chop\n\
(noted above) گنتی as one flaw اندر the final tally نیچے");
	/*=============================================*/
	Milestone = 60;
	/*=============================================*/
	لکھو("\n");
	لکھو("Does Multiplication commute?  ");
	لکھو("Testing on %d random pairs.\n", NoTrials);
	Random9 = SQRT(3.0);
	Random1 = تیسرا;
	I = 1;
	کرو  {
		X = Random();
		Y = Random();
		Z9 = Y * X;
		Z = X * Y;
		Z9 = Z - Z9;
		I = I + 1;
		} جب ( ! ((I > NoTrials) || (Z9 != Zero)));
	اگر (I == NoTrials) {
		Random1 = One + Half / Three;
		Random2 = (U2 + U1) + One;
		Z = Random1 * Random2;
		Y = Random2 * Random1;
		Z9 = (One + Half / Three) * ((U2 + U1) + One) - (One + Half /
			Three) * ((U2 + U1) + One);
		}
	اگر (! ((I == NoTrials) || (Z9 == Zero)))
		BadCond(Defect, "X * Y == Y * X trial fails.\n");
	ورنہ لکھو("     No failures found in %d integer pairs.\n", NoTrials);
	/*=============================================*/
	Milestone = 70;
	/*=============================================*/
	لکھو("\nRunning test of square root(x).\n");
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
	اگر (J != Zero) Pause();
	لکھو("Testing if sqrt(X * X) == X for %d Integers X.\n", NoTrials);
	J = Zero;
	X = Two;
	Y = Radix;
	اگر ((Radix != One)) کرو  {
		X = Y;
		Y = Radix * Y;
		} جب ( ! ((Y - X >= NoTrials)));
	OneUlp = X * U2;
	I = 1;
	جب (I <= NoTrials) {
		X = X + One;
		SqXMinX (Defect);
		اگر (J > Zero) توڑو;
		I = I + 1;
		}
	لکھو("Test for sqrt monotonicity.\n");
	I = - 1;
	X = BMinusU2;
	Y = Radix;
	Z = Radix + Radix * U2;
	NotMonot = False;
	Monot = False;
	جب ( ! (NotMonot || Monot)) {
		I = I + 1;
		X = SQRT(X);
		Q = SQRT(Y);
		Z = SQRT(Z);
		اگر ((X > Q) || (Q > Z)) NotMonot = True;
		ورنہ {
			Q = FLOOR(Q + Half);
			اگر (!(I > 0 || Radix == Q * Q)) Monot = True;
			ورنہ اگر (I > 0) {
			اگر (I > 1) Monot = True;
			ورنہ {
				Y = Y * BInvrse;
				X = Y - U1;
				Z = Y + U1;
				}
			}
			ورنہ {
				Y = Q;
				X = Y - U2;
				Z = Y + U2;
				}
			}
		}
	اگر (Monot) لکھو("sqrt has passed a test for Monotonicity.\n");
	ورنہ {
		BadCond(Defect, "");
		لکھو("sqrt(X) is non-monotonic for X near %d .\n", Y);
		}
	/*=============================================*/
	/*بانٹو
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
	اگر (SqEr > MaxSqEr) MaxSqEr = SqEr;
	SqEr = Y + U2 / Eight;
	اگر (SqEr < MinSqEr) MinSqEr = SqEr;
	Y = ((SQRT(F9) - U2) - (One - U2)) / U1;
	SqEr = Y + U1 / Eight;
	اگر (SqEr > MaxSqEr) MaxSqEr = SqEr;
	SqEr = (Y + One) + U1 / Eight;
	اگر (SqEr < MinSqEr) MinSqEr = SqEr;
	OneUlp = U2;
	X = OneUlp;
	برائے( Indx = 1; Indx <= 3; ++Indx) {
		Y = SQRT((X + U1 + X) + F9);
		Y = ((Y - U2) - ((One - U2) + X)) / OneUlp;
		Z = ((U1 - X) + F9) * Half * X * X / OneUlp;
		SqEr = (Y + Half) + Z;
		اگر (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = (Y - Half) + Z;
		اگر (SqEr > MaxSqEr) MaxSqEr = SqEr;
		اگر (((Indx == 1) || (Indx == 3))) 
			X = OneUlp * Sign (X) * FLOOR(Eight / (Nine * SQRT(OneUlp)));
		ورنہ {
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
	اگر (Radix != One) {
		لکھو("Testing whether sqrt is rounded or chopped.\n");
		D = FLOOR(Half + POW(Radix, One + Precision - FLOOR(Precision)));
	/* ... == Radix^(1 + fract) if (Precision == Integer + fract. */
		X = D / Radix;
		Y = D / A1;
		اگر ((X != FLOOR(X)) || (Y != FLOOR(Y))) {
			Anomaly = True;
			}
		ورنہ {
			X = Zero;
			Z2 = X;
			Y = One;
			Y2 = Y;
			Z1 = Radix - One;
			FourD = Four * D;
			کرو  {
				اگر (Y2 > Z2) {
					Q = Radix;
					Y1 = Y;
					کرو  {
						X1 = FABS(Q + FLOOR(Half - Q / Y1) * Y1);
						Q = Y1;
						Y1 = X1;
						} جب ( ! (X1 <= Zero));
					اگر (Q <= One) {
						Z2 = Y2;
						Z = Y;
						}
					}
				Y = Y + Two;
				X = X + Eight;
				Y2 = Y2 + X;
				اگر (Y2 >= FourD) Y2 = Y2 - FourD;
				} جب ( ! (Y >= D));
			X8 = FourD - Z2;
			Q = (X8 + Z * Z) / FourD;
			X8 = X8 / Eight;
			اگر (Q != FLOOR(Q)) Anomaly = True;
			ورنہ {
				Break = False;
				کرو  {
					X = Z1 * Z;
					X = X - FLOOR(X / Radix) * Radix;
					اگر (X == One) 
						Break = True;
					ورنہ
						Z1 = Z1 - One;
					} جب ( ! (Break || (Z1 <= Zero)));
				اگر ((Z1 <= Zero) && (! Break)) Anomaly = True;
				ورنہ {
					اگر (Z1 > RadixD2) Z1 = Z1 - Radix;
					کرو  {
						NewD();
						} جب ( ! (U2 * D >= F9));
					اگر (D * Radix - D != W - D) Anomaly = True;
					ورنہ {
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
						اگر (D - Z2 != W - Z2) Anomaly = True;
						ورنہ {
							Y = (D - Z2) + (Z2 + (One - Z) * Half);
							X = (D - Z2) + (Z2 - Z + Q);
							SR3750();
							Y = (One + Z) * Half;
							X = Q;
							SR3750();
							اگر (I == 0) Anomaly = True;
							}
						}
					}
				}
			}
		اگر ((I == 0) || Anomaly) {
			BadCond(Failure, "Anomalous arithmetic with Integer < ");
			لکھو("Radix^Precision = %d\n", W);
			لکھو(" fails test whether sqrt rounds or chops.\n");
			SqRWrng = True;
			}
		}
	اگر (! Anomaly) {
		اگر (! ((MinSqEr < Zero) || (MaxSqEr > Zero))) {
			RSqrt = Rounded;
			لکھو("Square root appears to be correctly rounded.\n");
			}
		ورنہ  {
			اگر ((MaxSqEr + U2 > U2 - Half) || (MinSqEr > Half)
				|| (MinSqEr + Radix < Half)) SqRWrng = True;
			ورنہ {
				RSqrt = Chopped;
				لکھو("Square root appears to be chopped.\n");
				}
			}
		}
	اگر (SqRWrng) {
		لکھو("Square root is neither chopped nor correctly rounded.\n");
		لکھو("Observed errors run from %d ", MinSqEr - Half);
		لکھو("to %d ulps.\n", Half + MaxSqEr);
		TstCond (Serious, MaxSqEr - MinSqEr < Radix * Radix,
			"sqrt gets too many last digits wrong");
		}
	/*=============================================*/
	Milestone = 90;
	/*=============================================*/
	Pause();
	لکھو("Testing powers Z^i for small Integers Z and i.\n");
	N = 0;
	/* ... test powers of zero. */
	I = 0;
	Z = -Zero;
	M = 3;
	Break = False;
	کرو  {
		X = One;
		SR3980();
		اگر (I <= 10) {
			I = 1023;
			SR3980();
			}
		اگر (Z == MinusOne) Break = True;
		ورنہ {
			Z = MinusOne;
			/* .. if(-1)^N is invalid, replace MinusOne by One. */
			I = - 4;
			}
		} جب ( ! Break);
	PrintIfNPositive();
	N1 = N;
	N = 0;
	Z = A1;
	M = (صحیح)FLOOR(Two * LOG(W) / LOG(A1));
	Break = False;
	کرو  {
		X = Z;
		I = 1;
		SR3980();
		اگر (Z == AInvrse) Break = True;
		ورنہ Z = AInvrse;
		} جب ( ! (Break));
	/*=============================================*/
		Milestone = 100;
	/*=============================================*/
	/*  Powers of Radix have been tested, */
	/*         next try a few primes     */
	M = NoTrials;
	Z = Three;
	کرو  {
		X = Z;
		I = 1;
		SR3980();
		کرو  {
			Z = Z + Two;
			} جب ( Three * FLOOR(Z / Three) == Z );
		} جب ( Z < Eight * Three );
	اگر (N > 0) {
		لکھو("Errors like this may invalidate financial calculations\n");
		لکھو("\tinvolving interest rates.\n");
		}
	PrintIfNPositive();
	N += N1;
	اگر (N == 0) لکھو("... no discrepancies found.\n");
	اگر (N > 0) Pause();
	ورنہ لکھو("\n");
	/*=============================================*/
	/*بانٹو
	}
#include "paranoia.h"
void part6(VOID){
*/
	Milestone = 110;
	/*=============================================*/
	لکھو("Seeking Underflow thresholds UfThold and E0.\n");
	D = U1;
	اگر (Precision != FLOOR(Precision)) {
		D = BInvrse;
		X = Precision;
		کرو  {
			D = D * BInvrse;
			X = X - One;
			} جب ( X > Zero);
		}
	Y = One;
	Z = D;
	/* ... D is power of 1/Radix < 1. */
	کرو  {
		C = Y;
		Y = Z;
		Z = Y * Y;
		} جب ((Y > Z) && (Z + Z > Z));
	Y = C;
	Z = Y * D;
	کرو  {
		C = Y;
		Y = Z;
		Z = Y * D;
		} جب ((Y > Z) && (Z + Z > Z));
	اگر (Radix < Two) HInvrse = Two;
	ورنہ HInvrse = Radix;
	H = One / HInvrse;
	/* ... 1/HInvrse == H == Min(1/Radix, 1/2) */
	CInvrse = One / C;
	E0 = C;
	Z = E0 * H;
	/* ...1/Radix^(BIG Integer) << 1 << CInvrse == 1/C */
	کرو  {
		Y = E0;
		E0 = Z;
		Z = E0 * H;
		} جب ((E0 > Z) && (Z + Z > Z));
	UfThold = E0;
	E1 = Zero;
	Q = Zero;
	E9 = U2;
	S = One + E9;
	D = C * S;
	اگر (D <= C) {
		E9 = Radix * U2;
		S = One + E9;
		D = C * S;
		اگر (D <= C) {
			BadCond(Failure, "multiplication gets too many last digits wrong.\n");
			Underflow = E0;
			Y1 = Zero;
			PseudoZero = Z;
			Pause();
			}
		}
	ورنہ {
		Underflow = D;
		PseudoZero = Underflow * H;
		UfThold = Zero;
		کرو  {
			Y1 = Underflow;
			Underflow = PseudoZero;
			اگر (E1 + E1 <= E1) {
				Y2 = Underflow * HInvrse;
				E1 = FABS(Y1 - Y2);
				Q = Y1;
				اگر ((UfThold == Zero) && (Y1 != Y2)) UfThold = Y1;
				}
			PseudoZero = PseudoZero * H;
			} جب ((Underflow > PseudoZero)
				&& (PseudoZero + PseudoZero > PseudoZero));
		}
	/* Comment line 4530 .. 4560 */
	اگر (PseudoZero != Zero) {
		لکھو("\n");
		Z = PseudoZero;
	/* ... Test PseudoZero for "phoney- zero" violates */
	/* ... PseudoZero < Underflow or PseudoZero < PseudoZero + PseudoZero
		   ... */
		اگر (PseudoZero <= Zero) {
			BadCond(Failure, "Positive expressions can underflow to an\n");
			لکھو("allegedly negative value\n");
			لکھو("PseudoZero that prints out as: %d .\n", PseudoZero);
			X = - PseudoZero;
			اگر (X <= Zero) {
				لکھو("But -PseudoZero, which should be\n");
				لکھو("positive, isn't; it prints out as  %d .\n", X);
				}
			}
		ورنہ {
			BadCond(Flaw, "Underflow can stick at an allegedly positive\n");
			لکھو("value PseudoZero that prints out as %d .\n", PseudoZero);
			}
		TstPtUf();
		}
	/*=============================================*/
	Milestone = 120;
	/*=============================================*/
	اگر (CInvrse * Y > CInvrse * Y1) {
		S = H * S;
		E0 = Underflow;
		}
	اگر (! ((E1 == Zero) || (E1 == E0))) {
		BadCond(Defect, "");
		اگر (E1 < E0) {
			لکھو("Products underflow at a higher");
			لکھو(" threshold than differences.\n");
			اگر (PseudoZero == Zero) 
			E0 = E1;
			}
		ورنہ {
			لکھو("Difference underflows at a higher");
			لکھو(" threshold than products.\n");
			}
		}
	لکھو("Smallest strictly positive number found is E0 = %d .\n", E0);
	Z = E0;
	TstPtUf();
	Underflow = E0;
	اگر (N == 1) Underflow = Y;
	I = 4;
	اگر (E1 == Zero) I = 3;
	اگر (UfThold == Zero) I = I - 2;
	UfNGrad = True;
	انتخاب (I)  {
		حالت	1:
		UfThold = Underflow;
		اگر ((CInvrse * Q) != ((CInvrse * Y) * S)) {
			UfThold = Y;
			BadCond(Failure, "Either accuracy deteriorates as numbers\n");
			لکھو("approach a threshold = %d\n", UfThold);;
			لکھو(" coming down from %d\n", C);
			لکھو(" or else multiplication gets too many last digits wrong.\n");
			}
		Pause();
		توڑو;
	
		حالت	2:
		BadCond(Failure, "Underflow confuses Comparison, which alleges that\n");
		لکھو("Q == Y while denying that |Q - Y| == 0; these values\n");
		لکھو("print out as Q = %d, Y = %016x .\n", Q, Y2);
		لکھو ("|Q - Y| = %d .\n" , FABS(Q - Y2));
		UfThold = Q;
		توڑو;
	
		حالت	3:
		X = X;
		توڑو;
	
		حالت	4:
		اگر ((Q == UfThold) && (E1 == E0)
			&& (FABS( UfThold - E1 / E9) <= E1)) {
			UfNGrad = False;
			لکھو("Underflow is gradual; it incurs Absolute Error =\n");
			لکھو("(roundoff in UfThold) < E0.\n");
			Y = E0 * CInvrse;
			Y = Y * (OneAndHalf + U2);
			X = CInvrse * (One + U2);
			Y = Y / X;
			IEEE = (Y == E0);
			}
		}
	اگر (UfNGrad) {
		لکھو("\n");
		sigsave = sigfpe;
		اگر (setjmp(ovfl_buf)) {
			لکھو("Underflow / UfThold failed!\n");
			R = H + H;
			}
		ورنہ R = SQRT(Underflow / UfThold);
		sigsave = 0;
		اگر (R <= H) {
			Z = R * UfThold;
			X = Z * (One + R * H * (One + H));
			}
		ورنہ {
			Z = UfThold;
			X = Z * (One + H * H * (One + H));
			}
		اگر (! ((X == Z) || (X - Z != Zero))) {
			BadCond(Flaw, "");
			لکھو("X = %d\n\tis not equal to Z = %016x .\n", X, Z);
			Z9 = X - Z;
			لکھو("yet X - Z yields %d .\n", Z9);
			لکھو("    Should this NOT signal Underflow, ");
			لکھو("this is a SERIOUS DEFECT\nthat causes ");
			لکھو("confusion when innocent statements like\n");;
			لکھو("    if (X == Z)  ...  else");
			لکھو("  ... (f(X) - f(Z)) / (X - Z) ...\n");
			لکھو("encounter Division by Zero although actually\n");
			sigsave = sigfpe;
			اگر (setjmp(ovfl_buf)) لکھو("X / Z fails!\n");
			ورنہ لکھو("X / Z = 1 + %d .\n", (X / Z - Half) - Half);
			sigsave = 0;
			}
		}
	لکھو("The Underflow threshold is %d, %s\n", UfThold,
		   " below which");
	لکھو("calculation may suffer larger Relative error than ");
	لکھو("merely roundoff.\n");
	Y2 = U1 * U1;
	Y = Y2 * Y2;
	Y2 = Y * U1;
	اگر (Y2 <= UfThold) {
		اگر (Y > E0) {
			BadCond(Defect, "");
			I = 5;
			}
		ورنہ {
			BadCond(Serious, "");
			I = 4;
			}
		لکھو("Range is too narrow; U1^%d Underflows.\n", I);
		}
	/*=============================================*/
	/*بانٹو
	}
#include "paranoia.h"
void part7(VOID){
*/
	Milestone = 130;
	/*=============================================*/
	Y = - FLOOR(Half - TwoForty * LOG(UfThold) / LOG(HInvrse)) / TwoForty;
	Y2 = Y + Y;
	لکھو("Since underflow occurs below the threshold\n");
	لکھو("UfThold = (%d) ^ (%016x)\nonly underflow ", HInvrse, Y);
	لکھو("should afflict the expression\n\t(%d) ^ (%016x);\n",
		HInvrse, Y2);
	لکھو("actually calculating yields:");
	اگر (setjmp(ovfl_buf)) {
		sigsave = 0;
		BadCond(Serious, "trap on underflow.\n");
		}
	ورنہ {
		sigsave = sigfpe;
		V9 = POW(HInvrse, Y2);
		sigsave = 0;
		لکھو(" %d .\n", V9);
		اگر (! ((V9 >= Zero) && (V9 <= (Radix + Radix + E9) * UfThold))) {
			BadCond(Serious, "this is not between 0 and underflow\n");
		لکھو("   threshold = %d .\n", UfThold);
		}
		ورنہ اگر (! (V9 > UfThold * (One + E9)))
			لکھو("This computed value is O.K.\n");
		ورنہ {
			BadCond(Defect, "this is not between 0 and underflow\n");
			لکھو("   threshold = %d .\n", UfThold);
			}
		}
	/*=============================================*/
	Milestone = 140;
	/*=============================================*/
	لکھو("\n");
	/* ...calculate Exp2 == exp(2) == 7.389056099... */
	X = Zero;
	I = 2;
	Y = Two * Three;
	Q = Zero;
	N = 0;
	کرو  {
		Z = X;
		I = I + 1;
		Y = Y / (I + I);
		R = Y + Q;
		X = Z + R;
		Q = (Z - X) + R;
		} جب(X > Z);
	Z = (OneAndHalf + One / Eight) + X / (OneAndHalf * ThirtyTwo);
	X = Z * Z;
	Exp2 = X * X;
	X = F9;
	Y = X - U1;
	لکھو("Testing X^((X + 1) / (X - 1)) vs. exp(2) = %d as X -> 1.\n",
		Exp2);
	برائے(I = 1;;) {
		Z = X - BInvrse;
		Z = (X + One) / (Z - (One - BInvrse));
		Q = POW(X, Z) - Exp2;
		اگر (FABS(Q) > TwoForty * U2) {
			N = 1;
	 		V9 = (X - BInvrse) - (One - BInvrse);
			BadCond(Defect, "Calculated");
			لکھو(" %d for\n", POW(X,Z));
			لکھو("\t(1 + (%d) ^ (%016x);\n", V9, Z);
			لکھو("\tdiffers from correct value by %d .\n", Q);
			لکھو("\tThis much error may spoil financial\n");
			لکھو("\tcalculations involving tiny interest rates.\n");
			توڑو;
			}
		ورنہ {
			Z = (Y - X) * Two + Y;
			X = Y;
			Y = Z;
			Z = One + (X - F9)*(X - F9);
			اگر (Z > One && I < NoTrials) I++;
			ورنہ  {
				اگر (X > One) {
					اگر (N == 0)
					   لکھو("Accuracy seems adequate.\n");
					توڑو;
					}
				ورنہ {
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
	لکھو("Testing powers Z^Q at four nearly extreme values.\n");
	N = 0;
	Z = A1;
	Q = FLOOR(Half - LOG(C) / LOG(A1));
	Break = False;
	کرو  {
		X = CInvrse;
		Y = POW(Z, Q);
		IsYeqX();
		Q = - Q;
		X = C;
		Y = POW(Z, Q);
		IsYeqX();
		اگر (Z < One) Break = True;
		ورنہ Z = AInvrse;
		} جب ( ! (Break));
	PrintIfNPositive();
	اگر (N == 0) لکھو(" ... no discrepancies found.\n");
	لکھو("\n");
	
	/*=============================================*/
	Milestone = 160;
	/*=============================================*/
	Pause();
	لکھو("Searching for Overflow threshold:\n");
	لکھو("This may generate an error.\n");
	Y = - CInvrse;
	V9 = HInvrse * Y;
	sigsave = sigfpe;
	اگر (setjmp(ovfl_buf)) { I = 0; V9 = Y; جاؤ حد_سے_تجاوز; }
	کرو {
		V = Y;
		Y = V9;
		V9 = HInvrse * Y;
		} جب(V9 < Y);
	I = 1;
حد_سے_تجاوز:
	sigsave = 0;
	Z = V9;
	لکھو("Can `Z = -Y' overflow?\n");
	لکھو("Trying it on Y = %d .\n", Y);
	V9 = - Y;
	V0 = V9;
	اگر (V - Y == V + V0) لکھو("Seems O.K.\n");
	ورنہ {
		لکھو("finds a ");
		BadCond(Flaw, "-(-Y) differs from Y.\n");
		}
	اگر (Z != Y) {
		BadCond(Serious, "");
		لکھو("overflow past %d\n\tshrinks to %016x .\n", Y, Z);
		}
	اگر (I) {
		Y = V * (HInvrse * U2 - HInvrse);
		Z = Y + ((One - HInvrse) * U2) * V;
		اگر (Z < V0) Y = Z;
		اگر (Y < V0) V = Y;
		اگر (V0 - V < V0) V = V0;
		}
	ورنہ {
		V = Y * (HInvrse * U2 - HInvrse);
		V = V + ((One - HInvrse) * U2) * Y;
		}
	لکھو("Overflow threshold is V  = %d .\n", V);
	اگر (I) لکھو("Overflow saturates at V0 = %d .\n", V0);
	ورنہ لکھو("There is no saturation قدر because \
the system traps on حد_سے_تجاوز.\n");
	V9 = V * One;
	لکھو("No Overflow should be signaled for V * 1 = %d\n", V9);
	V9 = V / One;
	لکھو("                           nor for V / 1 = %d .\n", V9);
	لکھو("Any overflow signal separating this * from the one\n");
	لکھو("above is a DEFECT.\n");
	/*=============================================*/
	Milestone = 170;
	/*=============================================*/
	اگر (!(-V < V && -V0 < V0 && -UfThold < V && UfThold < V)) {
		BadCond(Failure, "Comparisons involving ");
		لکھو("+-%d, +-%016x\nand +-%016x are confused by Overflow.",
			V, V0, UfThold);
		}
	/*=============================================*/
	Milestone = 175;
	/*=============================================*/
	لکھو("\n");
	برائے(Indx = 1; Indx <= 3; ++Indx) {
		انتخاب (Indx)  {
			حالت 1: Z = UfThold; توڑو;
			حالت 2: Z = E0; توڑو;
			حالت 3: Z = PseudoZero; توڑو;
			}
		اگر (Z != Zero) {
			V9 = SQRT(Z);
			Y = V9 * V9;
			اگر (Y / (One - Radix * E9) < Z
			   || Y > (One + Radix * E9) * Z) { /* dgh: + E9 --> * E9 */
				اگر (V9 > U1) BadCond(Serious, "");
				ورنہ BadCond(Defect, "");
				لکھو("Comparison alleges that what prints as Z = %d\n", Z);
				لکھو(" is too far from sqrt(Z) ^ 2 = %d .\n", Y);
				}
			}
		}
	/*=============================================*/
	Milestone = 180;
	/*=============================================*/
	برائے(Indx = 1; Indx <= 2; ++Indx) {
		اگر (Indx == 1) Z = V;
		ورنہ Z = V0;
		V9 = SQRT(Z);
		X = (One - Radix * E9) * V9;
		V9 = V9 * X;
		اگر (((V9 < (One - Two * Radix * E9) * Z) || (V9 > Z))) {
			Y = V9;
			اگر (X < W) BadCond(Serious, "");
			ورنہ BadCond(Defect, "");
			لکھو("Comparison alleges that Z = %d\n", Z);
			لکھو(" is too far from sqrt(Z) ^ 2 (%d) .\n", Y);
			}
		}
	/*=============================================*/
	/*بانٹو
	}
#include "paranoia.h"
int part8(VOID){
*/
	Milestone = 190;
	/*=============================================*/
	Pause();
	X = UfThold * V;
	Y = Radix * Radix;
	اگر (X*Y < One || X > Y) {
		اگر (X * Y < U1 || X > Y/U1) BadCond(Defect, "Badly");
		ورنہ BadCond(Flaw, "");
			
		لکھو(" unbalanced range; UfThold * V = %d\n\t%s\n",
			X, "is too far from 1.\n");
		}
	/*=============================================*/
	Milestone = 200;
	/*=============================================*/
	برائے (Indx = 1; Indx <= 5; ++Indx)  {
		X = F9;
		انتخاب (Indx)  {
			حالت 2: X = One + U2; توڑو;
			حالت 3: X = V; توڑو;
			حالت 4: X = UfThold; توڑو;
			حالت 5: X = Radix;
			}
		Y = X;
		sigsave = sigfpe;
		اگر (setjmp(ovfl_buf))
			لکھو("  X / X  traps when X = %d\n", X);
		ورنہ {
			V9 = (Y / X - Half) - Half;
			اگر (V9 == Zero) جاری;
			اگر (V9 == - U1 && Indx < 5) BadCond(Flaw, "");
			ورنہ BadCond(Serious, "");
			لکھو("  X / X differs from 1 when X = %d\n", X);
			لکھو("  instead, X / X - 1/2 - 1/2 = %d .\n", V9);
			}
		sigsave = 0;
		}
	/*=============================================*/
	Milestone = 210;
	/*=============================================*/
	MyZero = Zero;
	لکھو("\n");
	لکھو("What message and/or values does Division by Zero produce?\n") ;
#اگر_غیر_تعریف_شدہ NOPAUSE
	لکھو("This can interupt your program.  You can ");
	لکھو("skip this part if you wish.\n");
	لکھو("Do you wish to compute 1 / 0? ");
	fflush(stdout);
	اقرأ (KEYBOARD, ch, 8);
	اگر ((ch[0] == 'Y') || (ch[0] == 'y')) {
#اگر_ختم
		sigsave = sigfpe;
		لکھو("    Trying to compute 1 / 0 produces ...");
		اگر (!setjmp(ovfl_buf)) لکھو("  %d .\n", One / MyZero);
		sigsave = 0;
#اگر_غیر_تعریف_شدہ NOPAUSE
		}
	ورنہ لکھو("O.K.\n");
	لکھو("\nDo you wish to compute 0 / 0? ");
	fflush(stdout);
	اقرأ (KEYBOARD, ch, 80);
	اگر ((ch[0] == 'Y') || (ch[0] == 'y')) {
#اگر_ختم
		sigsave = sigfpe;
		لکھو("\n    Trying to compute 0 / 0 produces ...");
		اگر (!setjmp(ovfl_buf)) لکھو("  %d .\n", Zero / MyZero);
		sigsave = 0;
#اگر_غیر_تعریف_شدہ NOPAUSE
		}
	ورنہ لکھو("O.K.\n");
#اگر_ختم
	/*=============================================*/
	Milestone = 220;
	/*=============================================*/
	Pause();
	لکھو("\n");
	{
		ساکن حرف *پیغام_2[] = {
			"FAILUREs  encountered =",
			"SERIOUS DEFECTs  discovered =",
			"DEFECTs  discovered =",
			"FLAWs  discovered =" };
		صحیح i;
		برائے(i = 0; i < 4; i++) اگر (ErrCnt[i])
			لکھو("The number of  %-29s %d.\n",
				پیغام_2[i], ErrCnt[i]);
		}
	لکھو("\n");
	اگر ((ErrCnt[Failure] + ErrCnt[Serious] + ErrCnt[Defect]
			+ ErrCnt[Flaw]) > 0) {
		اگر ((ErrCnt[Failure] + ErrCnt[Serious] + ErrCnt[
			Defect] == 0) && (ErrCnt[Flaw] > 0)) {
			لکھو("The arithmetic diagnosed seems ");
			لکھو("Satisfactory though flawed.\n");
			}
		اگر ((ErrCnt[Failure] + ErrCnt[Serious] == 0)
			&& ( ErrCnt[Defect] > 0)) {
			لکھو("The arithmetic diagnosed may be Acceptable\n");
			لکھو("despite inconvenient Defects.\n");
			}
		اگر ((ErrCnt[Failure] + ErrCnt[Serious]) > 0) {
			لکھو("The arithmetic diagnosed has ");
			لکھو("unacceptable Serious Defects.\n");
			}
		اگر (ErrCnt[Failure] > 0) {
			لکھو("Potentially fatal FAILURE may have spoiled this");
			لکھو(" program's subsequent diagnoses.\n");
			}
		}
	ورنہ {
		لکھو("No failures, defects nor flaws have been discovered.\n");
		اگر (! ((RMult == Rounded) && (RDiv == Rounded)
			&& (RAddSub == Rounded) && (RSqrt == Rounded))) 
			لکھو("The arithmetic diagnosed seems Satisfactory.\n");
		ورنہ {
			اگر (Sticky_ثنائی_ہندسہ >= One &&
				(Radix - Two) * (Radix - Nine - One) == Zero) {
				لکھو("Rounding appears to conform to ");
				لکھو("the proposed IEEE standard P");
				اگر ((Radix == Two) &&
					 ((Precision - Four * Three * Two) *
					  ( Precision - TwentySeven -
					   TwentySeven + One) == Zero)) 
					لکھو("754");
				ورنہ لکھو("854");
				اگر (IEEE) لکھو(".\n");
				ورنہ {
					لکھو(",\nexcept for possibly Double Rounding");
					لکھو(" during Gradual Underflow.\n");
					}
				}
			لکھو("The arithmetic diagnosed appears to be Excellent!\n");
			}
		}
	اگر (fpecount)
		لکھو("\nA total of %d floating point exceptions were registered.\n",
			fpecount);
	لکھو("END OF TEST $\n");
  __asm__("ebreak");
	//return 0;
	}

/*SPLIT subs.c
#include "paranoia.h"
*/

 FLOAT
Sign (FP X)
#اگر_تعریف_شدہ KR_سرخیاں
FLOAT X;
#اگر_ختم
{ واپس X >= 0. ? 1.0 : -1.0; }

 خالی
Pause(VOID)
{
#اگر_غیر_تعریف_شدہ NOPAUSE
	حرف ch[8];

	لکھو("\nTo continue, press RETURN");
	fflush(stdout);
	اقرأ(KEYBOARD, ch, 8);
#اگر_ختم
	لکھو("\nDiagnosis resumes after milestone Number %d", Milestone);
	لکھو("          Page: %d\n\n", صفحہ_No);
	++Milestone;
	++صفحہ_No;
	}

 خالی
TstCond (INT K, INT Valid, CHARP T)
#اگر_تعریف_شدہ KR_سرخیاں
صحیح K, Valid;
حرف *T;
#اگر_ختم
{ اگر (! Valid) { BadCond(K,T); لکھو(".\n"); } }

 خالی
BadCond(INT K, CHARP T)
#اگر_تعریف_شدہ KR_سرخیاں
صحیح K;
حرف *T;
#اگر_ختم
{
	ساکن حرف *پیغام_2[] = { "FAILURE", "SERIOUS DEFECT", "DEFECT", "FLAW" };

	ErrCnt [K] = ErrCnt [K] + 1;
	لکھو("%s:  %s", پیغام_2[K], T);
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
	واپس(Random1);
	}

 خالی
SqXMinX (INT Err_قسم)
#اگر_تعریف_شدہ KR_سرخیاں
صحیح Err_قسم;
#اگر_ختم
{
	FLOAT XA, XB;
	
	XB = X * BInvrse;
	XA = X - XB;
	SqEr = ((SQRT(X * X) - XB) - XA) / OneUlp;
	اگر (SqEr != Zero) {
		اگر (SqEr < MinSqEr) MinSqEr = SqEr;
		اگر (SqEr > MaxSqEr) MaxSqEr = SqEr;
		J = J + 1.0;
		BadCond(Err_قسم, "\n");
		لکھو("sqrt( %d) - %016x  = %016x\n", X * X, X, OneUlp * SqEr);
		لکھو("\tinstead of correct value 0 .\n");
		}
	}

 خالی
NewD(VOID)
{
	X = Z1 * Q;
	X = FLOOR(Half - X / Radix) * Radix + X;
	Q = (Q - X * Z) / Radix + X * X * (D / Radix);
	Z = Z - Two * X * D;
	اگر (Z <= Zero) {
		Z = - Z;
		Z1 = - Z1;
		}
	D = Radix * D;
	}

 خالی
SR3750(VOID)
{
	اگر (! ((X - Radix < Z2 - Radix) || (X - Z2 > W - Z2))) {
		I = I + 1;
		X2 = SQRT(X * D);
		Y2 = (X2 - Z2) - (Y - Z2);
		X2 = X8 / (Y - Half);
		X2 = X2 - Half * X2 * X2;
		SqEr = (Y2 + Half) + (Half - X2);
		اگر (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = Y2 - X2;
		اگر (SqEr > MaxSqEr) MaxSqEr = SqEr;
		}
	}

 خالی
IsYeqX(VOID)
{
	اگر (Y != X) {
		اگر (N <= 0) {
			اگر (Z == Zero && Q <= Zero)
				لکھو("WARNING:  computing\n");
			ورنہ BadCond(Defect, "computing\n");
			لکھو("\t(%d) ^ (%016x)\n", Z, Q);
			لکھو("\tyielded %d;\n", Y);
			لکھو("\twhich compared unequal to correct %d ;\n",
				X);
			لکھو("\t\tthey differ by %d .\n", Y - X);
			}
		N = N + 1; /* ... count discrepancies. */
		}
	}

 خالی
SR3980(VOID)
{
	کرو {
		Q = (FLOAT) I;
		Y = POW(Z, Q);
		IsYeqX();
		اگر (++I > M) توڑو;
		X = Z * X;
		} جب ( X < W );
	}

 خالی
PrintIfNPositive(VOID)
{
	اگر (N > 0) لکھو("Similar discrepancies have occurred %d times.\n", N);
	}

 خالی
TstPtUf(VOID)
{
	N = 0;
	اگر (Z != Zero) {
		لکھو("Since comparison denies Z = 0, evaluating ");
		لکھو("(Z + Z) / Z should be safe.\n");
		sigsave = sigfpe;
		اگر (setjmp(ovfl_buf)) جاؤ very_serious;
		Q9 = (Z + Z) / Z;
		لکھو("What the machine gets for (Z + Z) / Z is  %d .\n",
			Q9);
		اگر (FABS(Q9 - Two) < Radix * U2) {
			لکھو("This is O.K., provided Over/Underflow");
			لکھو(" has NOT just been signaled.\n");
			}
		ورنہ {
			اگر ((Q9 < One) || (Q9 > Two)) {
very_serious:
				N = 1;
				ErrCnt [Serious] = ErrCnt [Serious] + 1;
				لکھو("This is a VERY SERIOUS DEFECT!\n");
				}
			ورنہ {
				N = 1;
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				لکھو("This is a DEFECT!\n");
				}
			}
		sigsave = 0;
		V9 = Z * One;
		Random1 = V9;
		V9 = One * Z;
		Random2 = V9;
		V9 = Z / One;
		اگر ((Z == Random1) && (Z == Random2) && (Z == V9)) {
			اگر (N > 0) Pause();
			}
		ورنہ {
			N = 1;
			BadCond(Defect, "What prints as Z = ");
			لکھو("%d\n\tcompares different from  ", Z);
			اگر (Z != Random1) لکھو("Z * 1 = %d ", Random1);
			اگر (! ((Z == Random2)
				|| (Random2 == Random1)))
				لکھو("1 * Z == %d\n", Random2);
			اگر (! (Z == V9)) لکھو("Z / 1 = %d\n", V9);
			اگر (Random2 != Random1) {
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				BadCond(Defect, "Multiplication does not commute!\n");
				لکھو("\tComparison alleges that 1 * Z = %d\n",
					Random2);
				لکھو("\tdiffers from Z * 1 = %d\n", Random1);
				}
			Pause();
			}
		}
	}

 خالی
notify(CHARP s)
#اگر_تعریف_شدہ KR_سرخیاں
 حرف *s;
#اگر_ختم
{
	لکھو("%s test appears to be inconsistent...\n", s);
	لکھو("   PLEASE NOTIFY KARPINKSI!\n");
	}

/*SPLIT msgs.c
#include "paranoia.h"
*/

 خالی
msglist(CHARPP s)
#اگر_تعریف_شدہ KR_سرخیاں
حرف **s;
#اگر_ختم
{ جب(*s) لکھو("%s\n", *s++); }

 خالی
Instructions(VOID)
{
  ساکن حرف *instr[] = {
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

 خالی
Heading(VOID)
{
  ساکن حرف *سر[] = {
	"Users are invited to help debug and augment this program so it will",
	"cope with unanticipated and newly uncovered arithmetic pathologies.\n",
	"Please send suggestions and interesting results to",
	"\tRichard Karpinski",
	"\tComputer Center U-76",
	"\tUniversity of California",
	"\tSan Francisco, CA 94143-0704, USA\n",
	"In doing so, please include the following information:",
#اگر_تعریف_شدہ Single
	"\tPrecision:\tsingle;",
#ورنہ
	"\tPrecision:\tdouble;",
#اگر_ختم
	"\tVersion:\t10 February 1989;",
	"\tComputer:\n",
	"\tCompiler:\n",
	"\tOptimization level:\n",
	"\tOther relevant compiler options:",
	0};

	msglist(سر);
	}

 خالی
Characteristics(VOID)
{
	ساکن حرف *chars[] = {
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

 خالی
History(VOID)
{ /* History */
 /* Converted from Brian Wichmann's Pascal version to C by Thos Sumner,
	with further massaging by David M. Gay. */

  ساکن حرف *hist[] = {
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
