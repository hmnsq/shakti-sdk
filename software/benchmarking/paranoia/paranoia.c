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
#وصف_ڪريو NOSIGNAL
#وصف_ڪريو NOPAUSE
#جيڪڏهن_وصف_نه_ٿيل NOSIGNAL
#ضمن <signal.h>
#جيڪڏهن_پورو
#ضمن <setjmp.h>
#جيڪڏهن_وصف_ٿيل Single
#وصف_ڪريو FLOAT عائم
#وصف_ڪريو FABS(x) (عائم)fabs((مزدوج)(x))
#وصف_ڪريو FLOOR(x) (عائم)floor((مزدوج)(x))
#وصف_ڪريو LOG(x) (عائم)لاگرٿم((مزدوج)(x))
#وصف_ڪريو POW(x,y) (عائم)قوت((مزدوج)(x),(مزدوج)(y))
#وصف_ڪريو SQRT(x) (عائم)جذر((مزدوج)(x))
#وإلا
#وصف_ڪريو FLOAT مزدوج
#وصف_ڪريو FABS(x) fabs(x)
#وصف_ڪريو FLOOR(x) floor(x)
#وصف_ڪريو LOG(x) لاگرٿم(x)
#وصف_ڪريو POW(x,y) قوت(x,y)
#وصف_ڪريو SQRT(x) جذر(x)
#جيڪڏهن_پورو

jmp_buf ovfl_buf;
#جيڪڏهن_وصف_ٿيل KR_سرا
#وصف_ڪريو VOID /* void */
#وصف_ڪريو INT /* int */
#وصف_ڪريو FP /* FLOAT */
#وصف_ڪريو CHARP /* char * */
#وصف_ڪريو CHARPP /* char ** */
خارجي مزدوج fabs(), floor(), لاگرٿم(), قوت(), جذر();
خارجي فراغ ٻاهر_نڪرو();
تعريفنوع فراغ (*Sig_type)();
FLOAT Sign(), Random();
خارجي فراغ BadCond();
خارجي فراغ SqXMinX();
خارجي فراغ TstCond();
خارجي فراغ notify();
خارجي صحيح اقرأ();
#وإلا
#وصف_ڪريو VOID فراغ
#وصف_ڪريو INT صحيح
#وصف_ڪريو FP FLOAT
#وصف_ڪريو CHARP حرف *
#وصف_ڪريو CHARPP حرف **
#جيڪڏهن_وصف_ٿيل __STDC__
#ضمن <stdlib.h>
#ضمن <math.h>
#وإلا
#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو
خارجي مزدوج fabs(مزدوج), floor(مزدوج), لاگرٿم(مزدوج);
خارجي مزدوج قوت(مزدوج,مزدوج), جذر(مزدوج);
خارجي فراغ ٻاهر_نڪرو(INT);
#جيڪڏهن_وصف_ٿيل __cplusplus
	}
#جيڪڏهن_پورو
#جيڪڏهن_پورو
تعريفنوع فراغ (*Sig_type)(صحيح);
FLOAT Sign(FLOAT), Random(فراغ);
خارجي فراغ BadCond(صحيح, حرف*);
خارجي فراغ SqXMinX(صحيح);
خارجي فراغ TstCond(صحيح, صحيح, حرف*);
خارجي فراغ notify(حرف*);
خارجي صحيح اقرأ(صحيح, حرف*, صحيح);
#جيڪڏهن_پورو
#وصف_رد V9
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

#وصف_ڪريو KEYBOARD 0

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
#وصف_ڪريو False 0
#وصف_ڪريو True 1

/* Definitions for declared types 
	Guard == (Yes, No);
	Rounding == (Chopped, Rounded, Other);
	Message == packed array [1..40] of char;
	Class == (Flaw, Defect, Serious, Failure);
	  */
#وصف_ڪريو Yes 1
#وصف_ڪريو No  0
#وصف_ڪريو Chopped 2
#وصف_ڪريو Rounded 1
#وصف_ڪريو Other   0
#وصف_ڪريو Flaw    3
#وصف_ڪريو Defect  2
#وصف_ڪريو Serious 1
#وصف_ڪريو Failure 0
تعريفنوع صحيح Guard, Rounding, Class;
تعريفنوع حرف پيغام;

/* Declarations of Variables */
صحيح Indx;
حرف ch[8];
FLOAT AInvrse, A1;
FLOAT C, CInvrse;
FLOAT D, FourD;
FLOAT E0, E1, Exp2, E3, MinSqEr;
FLOAT SqEr, MaxSqEr, E9;
FLOAT ٽيون;
FLOAT F6, F9;
FLOAT H, HInvrse;
صحيح I;
FLOAT Sticky_ٻٽو_انگ, J;
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
صحيح صفحو_No;
صحيح M, N, N1;
Guard GMult, GDiv, GAddSub;
Rounding RMult, RDiv, RAddSub, RSqrt;
صحيح Break, پورو, NotMonot, Monot, Anomaly, IEEE,
		SqRWrng, UfNGrad;
/* Computed constants. */
/*U1  gap below 1.0, i.e, 1.0-U1 is next number below 1.0 */
/*U2  gap above 1.0, i.e, 1.0+U2 is next number above 1.0 */

/* floating point exception receiver */
 فراغ
sigfpe(INT x)
{
	fpecount++;
	لکو("\n* * * FLOATING-POINT ERROR %d * * *\n", x);
	fflush(stdout);
	إذا (sigsave) {
#جيڪڏهن_وصف_نه_ٿيل NOSIGNAL
		إشارة(SIGFPE, sigsave);
#جيڪڏهن_پورو
		sigsave = 0;
		longjmp(ovfl_buf, 1);
		}
	ٻاهر_نڪرو(1);
}

مکيه(VOID)
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
	صفحو_No = 1;
	/*=============================================*/
	Milestone = 0;
	/*=============================================*/
#جيڪڏهن_وصف_نه_ٿيل NOSIGNAL
	إشارة(SIGFPE, sigfpe);
#جيڪڏهن_پورو
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
	لکو("Program is now RUNNING tests on small integers:\n");
	
	TstCond (Failure, (Zero + Zero == Zero) && (One - One == Zero)
		   && (One > Zero) && (One + One == Two),
			"0+0 != 0, 1-1 != 0, 1 <= 0, or 1+1 != 2");
	Z = - Zero;
	إذا (Z != 0.0) {
		ErrCnt[Failure] = ErrCnt[Failure] + 1;
		لکو("Comparison alleges that -0.0 is Non-zero!\n");
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
	/*ورهايو
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
	إذا (ErrCnt[Failure] == 0) {
		لکو("-1, 0, 1/2, 1, 2, 3, 4, 5, 9, 27, 32 & 240 are O.K.\n");
		لکو("\n");
		}
	لکو("Searching for Radix and Precision.\n");
	W = One;
	افعل  {
		W = W + W;
		Y = W + One;
		Z = Y - W;
		Y = Z - One;
		} طالما (MinusOne + FABS(Y) < Zero);
	/*.. now W is just big enough that |((W+1)-W)-1| >= 1 ...*/
	Precision = Zero;
	Y = One;
	افعل  {
		Radix = W + Y;
		Y = Y + Y;
		Radix = Radix - W;
		} طالما ( Radix == Zero);
	إذا (Radix < Two) Radix = One;
	لکو("Radix = %d .\n", Radix);
	إذا (Radix != 1) {
		W = One;
		افعل  {
			Precision = Precision + One;
			W = W * Radix;
			Y = W + One;
			} طالما ((Y - W) == One);
		}
	/*... now W == Radix^Precision is barely too big to satisfy (W+1)-W == 1
			                              ...*/
	U1 = One / W;
	U2 = Radix * U1;
	لکو("Closest relative separation found is U1 = %d .\n\n", U1);
	لکو("Recalculating radix and precision\n ");
	
	/*save old values*/
	E0 = Radix;
	E1 = U1;
	E9 = U2;
	E3 = Precision;
	
	X = Four / Three;
	ٽيون = X - One;
	F6 = Half - ٽيون;
	X = F6 + F6;
	X = FABS(X - ٽيون);
	إذا (X < U2) X = U2;
	
	/*... now X = (unknown no.) ulps of 1+...*/
	افعل  {
		U2 = X;
		Y = Half * U2 + ThirtyTwo * U2 * U2;
		Y = One + Y;
		X = Y - One;
		} طالما ( ! ((U2 <= X) || (X <= Zero)));
	
	/*... now U2 == 1 ulp of 1 + ... */
	X = Two / Three;
	F6 = X - Half;
	ٽيون = F6 + F6;
	X = ٽيون - Half;
	X = FABS(X + F6);
	إذا (X < U1) X = U1;
	
	/*... now  X == (unknown no.) ulps of 1 -... */
	افعل  {
		U1 = X;
		Y = Half * U1 + ThirtyTwo * U1 * U1;
		Y = Half - Y;
		X = Half + Y;
		Y = Half - X;
		X = Half + Y;
		} طالما ( ! ((U1 <= X) || (X <= Zero)));
	/*... now U1 == 1 ulp of 1 - ... */
	إذا (U1 == E1) لکو("confirms closest relative separation U1 .\n");
	وإلا لکو("gets better closest relative separation U1 = %d .\n", U1);
	W = One / U1;
	F9 = (Half - U1) + Half;
	Radix = FLOOR(0.01 + U2 / U1);
	إذا (Radix == E0) لکو("Radix confirmed.\n");
	وإلا لکو("MYSTERY: recalculated Radix = %d .\n", Radix);
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
	إذا (Radix != One)  {
		X = - TwoForty * LOG(U1) / LOG(Radix);
		Y = FLOOR(Half + X);
		إذا (FABS(X - Y) * Four < One) X = Y;
		Precision = X / TwoForty;
		Y = FLOOR(Half + Precision);
		إذا (FABS(Precision - Y) * TwoForty < Half) Precision = Y;
		}
	إذا ((Precision != FLOOR(Precision)) || (Radix == One)) {
		لکو("Precision cannot be characterized by an Integer number\n");
		لکو("of significant digits but, by itself, this is a minor flaw.\n");
		}
	إذا (Radix == One) 
		لکو("logarithmic encoding has precision characterized solely by U1.\n");
	وإلا لکو("The number of significant digits of the Radix is %d .\n",
			Precision);
	TstCond (Serious, U2 * Nine * Nine * TwoForty < One,
		   "Precision worse than 5 decimal figures  ");
	/*=============================================*/
	Milestone = 30;
	/*=============================================*/
	/* Test for extra-precise subepressions */
	X = FABS(((Four / Three - One) - One / Four) * Three - One / Four);
	افعل  {
		Z2 = X;
		X = (One + (Half * Z2 + ThirtyTwo * Z2 * Z2)) - One;
		} طالما ( ! ((Z2 <= X) || (X <= Zero)));
	X = Y = Z = FABS((Three / Four - Two / Three) * Three - One / Four);
	افعل  {
		Z1 = Z;
		Z = (One / Two - ((One / Two - (Half * Z1 + ThirtyTwo * Z1 * Z1))
			+ One / Two)) + One / Two;
		} طالما ( ! ((Z1 <= Z) || (Z <= Zero)));
	افعل  {
		افعل  {
			Y1 = Y;
			Y = (Half - ((Half - (Half * Y1 + ThirtyTwo * Y1 * Y1)) + Half
				)) + Half;
			} طالما ( ! ((Y1 <= Y) || (Y <= Zero)));
		X1 = X;
		X = ((Half * X1 + ThirtyTwo * X1 * X1) - F9) + F9;
		} طالما ( ! ((X1 <= X) || (X <= Zero)));
	إذا ((X1 != Y1) || (X1 != Z1)) {
		BadCond(Serious, "Disagreements among the values X1, Y1, Z1,\n");
		لکو("respectively  %d,  %016x,  %016x,\n", X1, Y1, Z1);
		لکو("are symptoms of inconsistencies introduced\n");
		لکو("by extra-precise evaluation of arithmetic subexpressions.\n");
		notify("Possibly some part of this");
		إذا ((X1 == U1) || (Y1 == U1) || (Z1 == U1))  لکو(
			"That feature is not tested further by this program.\n") ;
		}
	وإلا  {
		إذا ((Z1 != U1) || (Z2 != U2)) {
			إذا ((Z1 >= U1) || (Z2 >= U2)) {
				BadCond(Failure, "");
				notify("Precision");
				لکو("\tU1 = %d, Z1 - U1 = %016x\n",U1,Z1-U1);
				لکو("\tU2 = %d, Z2 - U2 = %016x\n",U2,Z2-U2);
				}
			وإلا {
				إذا ((Z1 <= Zero) || (Z2 <= Zero)) {
					لکو("Because of unusual Radix = %d", Radix);
					لکو(", or exact rational arithmetic a result\n");
					لکو("Z1 = %d, or Z2 = %016x ", Z1, Z2);
					notify("of an\nextra-precision");
					}
				إذا (Z1 != Z2 || Z1 > Zero) {
					X = Z1 / U1;
					Y = Z2 / U2;
					إذا (Y > X) X = Y;
					Q = - LOG(X);
					لکو("Some subexpressions appear to be calculated extra\n");
					لکو("precisely with about %d extra B-digits, i.e.\n",
						(Q / LOG(Radix)));
					لکو("roughly %d extra significant decimals.\n",
						Q / LOG(10.));
					}
				لکو("That feature is not tested further by this program.\n");
				}
			}
		}
	Pause();
	/*=============================================*/
	/*ورهايو
	}
#include "paranoia.h"
void part3(VOID){
*/
	Milestone = 35;
	/*=============================================*/
	إذا (Radix >= Two) {
		X = W / (Radix * Radix);
		Y = X + One;
		Z = Y - X;
		T = Z + U2;
		X = T - Z;
		TstCond (Failure, X == U2,
			"Subtraction is not normalized X=Y,X+Z != Y+Z!");
		إذا (X == U2) لکو(
			"Subtraction appears to be normalized, as it should be.");
		}
	لکو("\nChecking for guard digit in *, /, and -.\n");
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
	إذا ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)) GMult = Yes;
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
	إذا ((X == Zero) && (Y == Zero) && (Z == Zero)) GDiv = Yes;
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
	Sticky_ٻٽو_انگ = T / Radix;
	X = R - X;
	Y = Sticky_ٻٽو_انگ - Y;
	TstCond (Failure, X == Zero && Y == Zero,
			"* and/or / gets too many last digits wrong");
	Y = One - U1;
	X = One - F9;
	Y = One - Y;
	T = Radix - U2;
	Z = Radix - BMinusU2;
	T = Radix - T;
	إذا ((X == U1) && (Y == U1) && (Z == U2) && (T == U2)) GAddSub = Yes;
	وإلا {
		GAddSub = No;
		TstCond (Serious, False,
			"- lacks Guard Digit, so cancellation is obscured");
		}
	إذا (F9 != One && F9 - One >= Zero) {
		BadCond(Serious, "comparison alleges  (1-U1) < 1  although\n");
		لکو("  subtraction yields  (1-U1) - 1 = 0 , thereby vitiating\n");
		لکو("  such precautions against division by zero as\n");
		لکو("  ...  if (X == 1.0) {.....} else {.../(X-1.0)...}\n");
		}
	إذا (GMult == Yes && GDiv == Yes && GAddSub == Yes) لکو(
		"     *, /, and - appear to have guard digits, as they should.\n");
	/*=============================================*/
	Milestone = 40;
	/*=============================================*/
	Pause();
	لکو("Checking rounding on multiply, divide and add/subtract.\n");
	RMult = Other;
	RDiv = Other;
	RAddSub = Other;
	RadixD2 = Radix / Two;
	A1 = Two;
	پورو = False;
	افعل  {
		AInvrse = Radix;
		افعل  {
			X = AInvrse;
			AInvrse = AInvrse / A1;
			} طالما ( ! (FLOOR(AInvrse) != AInvrse));
		پورو = (X == One) || (A1 > Three);
		إذا (! پورو) A1 = Nine + One;
		} طالما ( ! (پورو));
	إذا (X == One) A1 = Radix;
	AInvrse = One / A1;
	X = A1;
	Y = AInvrse;
	پورو = False;
	افعل  {
		Z = X * Y - Half;
		TstCond (Failure, Z == Half,
			"X * (1/X) differs from 1");
		پورو = X == Radix;
		X = Radix;
		Y = One / X;
		} طالما ( ! (پورو));
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
	إذا ((X == Zero) && (Y == Zero) && (Z == Zero) && (T <= Zero)) {
		X = (OneAndHalf + U2) * Y2;
		Y = OneAndHalf - U2 - U2;
		Z = OneAndHalf + U2 + U2;
		T = (OneAndHalf - U2) * Y1;
		X = X - (Z + U2);
		Sticky_ٻٽو_انگ = Y * Y1;
		S = Z * Y2;
		T = T - Y;
		Y = (U2 - Y) + Sticky_ٻٽو_انگ;
		Z = S - (Z + U2 + U2);
		Sticky_ٻٽو_انگ = (Y2 + U2) * Y1;
		Y1 = Y2 * Y1;
		Sticky_ٻٽو_انگ = Sticky_ٻٽو_انگ - Y2;
		Y1 = Y1 - Half;
		إذا ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)
			&& ( Sticky_ٻٽو_انگ == Zero) && (Y1 == Half)) {
			RMult = Rounded;
			لکو("Multiplication appears to round correctly.\n");
			}
		وإلا	إذا ((X + U2 == Zero) && (Y < Zero) && (Z + U2 == Zero)
				&& (T < Zero) && (Sticky_ٻٽو_انگ + U2 == Zero)
				&& (Y1 < Half)) {
				RMult = Chopped;
				لکو("Multiplication appears to chop.\n");
				}
			وإلا لکو("* is neither chopped nor correctly rounded.\n");
		إذا ((RMult == Rounded) && (GMult == No)) notify("Multiplication");
		}
	وإلا لکو("* is neither chopped nor correctly rounded.\n");
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
	إذا (! ((X > Zero) || (Y > Zero) || (Z > Zero) || (T > Zero))) {
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
		إذا ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)
			&& (Y2 == Zero) && (Y2 == Zero)
			&& (Y1 - Half == F9 - Half )) {
			RDiv = Rounded;
			لکو("Division appears to round correctly.\n");
			إذا (GDiv == No) notify("Division");
			}
		وإلا إذا ((X < Zero) && (Y < Zero) && (Z < Zero) && (T < Zero)
			&& (Y2 < Zero) && (Y1 - Half < F9 - Half)) {
			RDiv = Chopped;
			لکو("Division appears to chop.\n");
			}
		}
	إذا (RDiv == Other) لکو("/ is neither chopped nor correctly rounded.\n");
	BInvrse = One / Radix;
	TstCond (Failure, (BInvrse * Radix - Half == Half),
		   "Radix * ( 1 / Radix ) differs from 1");
	/*=============================================*/
	/*ورهايو
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
	إذا ((X == Zero) && (Y == Zero)) {
		RAddSub = Chopped;
		لکو("Add/Subtract appears to be chopped.\n");
		}
	إذا (GAddSub == Yes) {
		X = (Half + U2) * U2;
		Y = (Half - U2) * U2;
		X = One + X;
		Y = One + Y;
		X = (One + U2) - X;
		Y = One - Y;
		إذا ((X == Zero) && (Y == Zero)) {
			X = (Half + U2) * U1;
			Y = (Half - U2) * U1;
			X = One - X;
			Y = One - Y;
			X = F9 - X;
			Y = One - Y;
			إذا ((X == Zero) && (Y == Zero)) {
				RAddSub = Rounded;
				لکو("Addition/Subtraction appears to round correctly.\n");
				إذا (GAddSub == No) notify("Add/Subtract");
				}
			وإلا لکو("Addition/Subtraction neither rounds nor chops.\n");
			}
		وإلا لکو("Addition/Subtraction neither rounds nor chops.\n");
		}
	وإلا لکو("Addition/Subtraction neither rounds nor chops.\n");
	S = One;
	X = One + Half * (One + Half);
	Y = (One + U2) * Half;
	Z = X - Y;
	T = Y - X;
	Sticky_ٻٽو_انگ = Z + T;
	إذا (Sticky_ٻٽو_انگ != Zero) {
		S = Zero;
		BadCond(Flaw, "(X - Y) + (Y - X) is non zero!\n");
		}
	Sticky_ٻٽو_انگ = Zero;
	إذا ((GMult == Yes) && (GDiv == Yes) && (GAddSub == Yes)
		&& (RMult == Rounded) && (RDiv == Rounded)
		&& (RAddSub == Rounded) && (FLOOR(RadixD2) == RadixD2)) {
		لکو("Checking for sticky bit.\n");
		X = (Half + U1) * U2;
		Y = Half * U2;
		Z = One + Y;
		T = One + X;
		إذا ((Z - One <= Zero) && (T - One >= U2)) {
			Z = T + Y;
			Y = Z - X;
			إذا ((Z - T >= U2) && (Y - T == Zero)) {
				X = (Half + U1) * U1;
				Y = Half * U1;
				Z = One - Y;
				T = One - X;
				إذا ((Z - One == Zero) && (T - F9 == Zero)) {
					Z = (Half - U1) * U1;
					T = F9 - Z;
					Q = F9 - Y;
					إذا ((T - F9 == Zero) && (F9 - U1 - Q == Zero)) {
						Z = (One + U2) * OneAndHalf;
						T = (OneAndHalf + U2) - Z + U2;
						X = One + Half / Radix;
						Y = One + Radix * U2;
						Z = X * Y;
						إذا (T == Zero && X + Radix * U2 - Z == Zero) {
							إذا (Radix != Two) {
								X = Two + U2;
								Y = X / Two;
								إذا ((Y - One == Zero)) Sticky_ٻٽو_انگ = S;
								}
							وإلا Sticky_ٻٽو_انگ = S;
							}
						}
					}
				}
			}
		}
	إذا (Sticky_ٻٽو_انگ == One) لکو("Sticky bit apparently used correctly.\n");
	وإلا لکو("Sticky bit used incorrectly or not at all.\n");
	TstCond (Flaw, !(GMult == No || GDiv == No || GAddSub == No ||
			RMult == Other || RDiv == Other || RAddSub == Other),
		"lack(s) جو guard digits or failure(s) منزل correctly round or chop\n\
(noted above) ڳڻپ as one flaw اندريون the final tally هيٺ");
	/*=============================================*/
	Milestone = 60;
	/*=============================================*/
	لکو("\n");
	لکو("Does Multiplication commute?  ");
	لکو("Testing on %d random pairs.\n", NoTrials);
	Random9 = SQRT(3.0);
	Random1 = ٽيون;
	I = 1;
	افعل  {
		X = Random();
		Y = Random();
		Z9 = Y * X;
		Z = X * Y;
		Z9 = Z - Z9;
		I = I + 1;
		} طالما ( ! ((I > NoTrials) || (Z9 != Zero)));
	إذا (I == NoTrials) {
		Random1 = One + Half / Three;
		Random2 = (U2 + U1) + One;
		Z = Random1 * Random2;
		Y = Random2 * Random1;
		Z9 = (One + Half / Three) * ((U2 + U1) + One) - (One + Half /
			Three) * ((U2 + U1) + One);
		}
	إذا (! ((I == NoTrials) || (Z9 == Zero)))
		BadCond(Defect, "X * Y == Y * X trial fails.\n");
	وإلا لکو("     No failures found in %d integer pairs.\n", NoTrials);
	/*=============================================*/
	Milestone = 70;
	/*=============================================*/
	لکو("\nRunning test of square root(x).\n");
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
	إذا (J != Zero) Pause();
	لکو("Testing if sqrt(X * X) == X for %d Integers X.\n", NoTrials);
	J = Zero;
	X = Two;
	Y = Radix;
	إذا ((Radix != One)) افعل  {
		X = Y;
		Y = Radix * Y;
		} طالما ( ! ((Y - X >= NoTrials)));
	OneUlp = X * U2;
	I = 1;
	طالما (I <= NoTrials) {
		X = X + One;
		SqXMinX (Defect);
		إذا (J > Zero) اكسر;
		I = I + 1;
		}
	لکو("Test for sqrt monotonicity.\n");
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
		إذا ((X > Q) || (Q > Z)) NotMonot = True;
		وإلا {
			Q = FLOOR(Q + Half);
			إذا (!(I > 0 || Radix == Q * Q)) Monot = True;
			وإلا إذا (I > 0) {
			إذا (I > 1) Monot = True;
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
	إذا (Monot) لکو("sqrt has passed a test for Monotonicity.\n");
	وإلا {
		BadCond(Defect, "");
		لکو("sqrt(X) is non-monotonic for X near %d .\n", Y);
		}
	/*=============================================*/
	/*ورهايو
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
	إذا (SqEr > MaxSqEr) MaxSqEr = SqEr;
	SqEr = Y + U2 / Eight;
	إذا (SqEr < MinSqEr) MinSqEr = SqEr;
	Y = ((SQRT(F9) - U2) - (One - U2)) / U1;
	SqEr = Y + U1 / Eight;
	إذا (SqEr > MaxSqEr) MaxSqEr = SqEr;
	SqEr = (Y + One) + U1 / Eight;
	إذا (SqEr < MinSqEr) MinSqEr = SqEr;
	OneUlp = U2;
	X = OneUlp;
	لكل( Indx = 1; Indx <= 3; ++Indx) {
		Y = SQRT((X + U1 + X) + F9);
		Y = ((Y - U2) - ((One - U2) + X)) / OneUlp;
		Z = ((U1 - X) + F9) * Half * X * X / OneUlp;
		SqEr = (Y + Half) + Z;
		إذا (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = (Y - Half) + Z;
		إذا (SqEr > MaxSqEr) MaxSqEr = SqEr;
		إذا (((Indx == 1) || (Indx == 3))) 
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
	إذا (Radix != One) {
		لکو("Testing whether sqrt is rounded or chopped.\n");
		D = FLOOR(Half + POW(Radix, One + Precision - FLOOR(Precision)));
	/* ... == Radix^(1 + fract) if (Precision == Integer + fract. */
		X = D / Radix;
		Y = D / A1;
		إذا ((X != FLOOR(X)) || (Y != FLOOR(Y))) {
			Anomaly = True;
			}
		وإلا {
			X = Zero;
			Z2 = X;
			Y = One;
			Y2 = Y;
			Z1 = Radix - One;
			FourD = Four * D;
			افعل  {
				إذا (Y2 > Z2) {
					Q = Radix;
					Y1 = Y;
					افعل  {
						X1 = FABS(Q + FLOOR(Half - Q / Y1) * Y1);
						Q = Y1;
						Y1 = X1;
						} طالما ( ! (X1 <= Zero));
					إذا (Q <= One) {
						Z2 = Y2;
						Z = Y;
						}
					}
				Y = Y + Two;
				X = X + Eight;
				Y2 = Y2 + X;
				إذا (Y2 >= FourD) Y2 = Y2 - FourD;
				} طالما ( ! (Y >= D));
			X8 = FourD - Z2;
			Q = (X8 + Z * Z) / FourD;
			X8 = X8 / Eight;
			إذا (Q != FLOOR(Q)) Anomaly = True;
			وإلا {
				Break = False;
				افعل  {
					X = Z1 * Z;
					X = X - FLOOR(X / Radix) * Radix;
					إذا (X == One) 
						Break = True;
					وإلا
						Z1 = Z1 - One;
					} طالما ( ! (Break || (Z1 <= Zero)));
				إذا ((Z1 <= Zero) && (! Break)) Anomaly = True;
				وإلا {
					إذا (Z1 > RadixD2) Z1 = Z1 - Radix;
					افعل  {
						NewD();
						} طالما ( ! (U2 * D >= F9));
					إذا (D * Radix - D != W - D) Anomaly = True;
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
						إذا (D - Z2 != W - Z2) Anomaly = True;
						وإلا {
							Y = (D - Z2) + (Z2 + (One - Z) * Half);
							X = (D - Z2) + (Z2 - Z + Q);
							SR3750();
							Y = (One + Z) * Half;
							X = Q;
							SR3750();
							إذا (I == 0) Anomaly = True;
							}
						}
					}
				}
			}
		إذا ((I == 0) || Anomaly) {
			BadCond(Failure, "Anomalous arithmetic with Integer < ");
			لکو("Radix^Precision = %d\n", W);
			لکو(" fails test whether sqrt rounds or chops.\n");
			SqRWrng = True;
			}
		}
	إذا (! Anomaly) {
		إذا (! ((MinSqEr < Zero) || (MaxSqEr > Zero))) {
			RSqrt = Rounded;
			لکو("Square root appears to be correctly rounded.\n");
			}
		وإلا  {
			إذا ((MaxSqEr + U2 > U2 - Half) || (MinSqEr > Half)
				|| (MinSqEr + Radix < Half)) SqRWrng = True;
			وإلا {
				RSqrt = Chopped;
				لکو("Square root appears to be chopped.\n");
				}
			}
		}
	إذا (SqRWrng) {
		لکو("Square root is neither chopped nor correctly rounded.\n");
		لکو("Observed errors run from %d ", MinSqEr - Half);
		لکو("to %d ulps.\n", Half + MaxSqEr);
		TstCond (Serious, MaxSqEr - MinSqEr < Radix * Radix,
			"sqrt gets too many last digits wrong");
		}
	/*=============================================*/
	Milestone = 90;
	/*=============================================*/
	Pause();
	لکو("Testing powers Z^i for small Integers Z and i.\n");
	N = 0;
	/* ... test powers of zero. */
	I = 0;
	Z = -Zero;
	M = 3;
	Break = False;
	افعل  {
		X = One;
		SR3980();
		إذا (I <= 10) {
			I = 1023;
			SR3980();
			}
		إذا (Z == MinusOne) Break = True;
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
	افعل  {
		X = Z;
		I = 1;
		SR3980();
		إذا (Z == AInvrse) Break = True;
		وإلا Z = AInvrse;
		} طالما ( ! (Break));
	/*=============================================*/
		Milestone = 100;
	/*=============================================*/
	/*  Powers of Radix have been tested, */
	/*         next try a few primes     */
	M = NoTrials;
	Z = Three;
	افعل  {
		X = Z;
		I = 1;
		SR3980();
		افعل  {
			Z = Z + Two;
			} طالما ( Three * FLOOR(Z / Three) == Z );
		} طالما ( Z < Eight * Three );
	إذا (N > 0) {
		لکو("Errors like this may invalidate financial calculations\n");
		لکو("\tinvolving interest rates.\n");
		}
	PrintIfNPositive();
	N += N1;
	إذا (N == 0) لکو("... no discrepancies found.\n");
	إذا (N > 0) Pause();
	وإلا لکو("\n");
	/*=============================================*/
	/*ورهايو
	}
#include "paranoia.h"
void part6(VOID){
*/
	Milestone = 110;
	/*=============================================*/
	لکو("Seeking Underflow thresholds UfThold and E0.\n");
	D = U1;
	إذا (Precision != FLOOR(Precision)) {
		D = BInvrse;
		X = Precision;
		افعل  {
			D = D * BInvrse;
			X = X - One;
			} طالما ( X > Zero);
		}
	Y = One;
	Z = D;
	/* ... D is power of 1/Radix < 1. */
	افعل  {
		C = Y;
		Y = Z;
		Z = Y * Y;
		} طالما ((Y > Z) && (Z + Z > Z));
	Y = C;
	Z = Y * D;
	افعل  {
		C = Y;
		Y = Z;
		Z = Y * D;
		} طالما ((Y > Z) && (Z + Z > Z));
	إذا (Radix < Two) HInvrse = Two;
	وإلا HInvrse = Radix;
	H = One / HInvrse;
	/* ... 1/HInvrse == H == Min(1/Radix, 1/2) */
	CInvrse = One / C;
	E0 = C;
	Z = E0 * H;
	/* ...1/Radix^(BIG Integer) << 1 << CInvrse == 1/C */
	افعل  {
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
	إذا (D <= C) {
		E9 = Radix * U2;
		S = One + E9;
		D = C * S;
		إذا (D <= C) {
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
		افعل  {
			Y1 = Underflow;
			Underflow = PseudoZero;
			إذا (E1 + E1 <= E1) {
				Y2 = Underflow * HInvrse;
				E1 = FABS(Y1 - Y2);
				Q = Y1;
				إذا ((UfThold == Zero) && (Y1 != Y2)) UfThold = Y1;
				}
			PseudoZero = PseudoZero * H;
			} طالما ((Underflow > PseudoZero)
				&& (PseudoZero + PseudoZero > PseudoZero));
		}
	/* Comment line 4530 .. 4560 */
	إذا (PseudoZero != Zero) {
		لکو("\n");
		Z = PseudoZero;
	/* ... Test PseudoZero for "phoney- zero" violates */
	/* ... PseudoZero < Underflow or PseudoZero < PseudoZero + PseudoZero
		   ... */
		إذا (PseudoZero <= Zero) {
			BadCond(Failure, "Positive expressions can underflow to an\n");
			لکو("allegedly negative value\n");
			لکو("PseudoZero that prints out as: %d .\n", PseudoZero);
			X = - PseudoZero;
			إذا (X <= Zero) {
				لکو("But -PseudoZero, which should be\n");
				لکو("positive, isn't; it prints out as  %d .\n", X);
				}
			}
		وإلا {
			BadCond(Flaw, "Underflow can stick at an allegedly positive\n");
			لکو("value PseudoZero that prints out as %d .\n", PseudoZero);
			}
		TstPtUf();
		}
	/*=============================================*/
	Milestone = 120;
	/*=============================================*/
	إذا (CInvrse * Y > CInvrse * Y1) {
		S = H * S;
		E0 = Underflow;
		}
	إذا (! ((E1 == Zero) || (E1 == E0))) {
		BadCond(Defect, "");
		إذا (E1 < E0) {
			لکو("Products underflow at a higher");
			لکو(" threshold than differences.\n");
			إذا (PseudoZero == Zero) 
			E0 = E1;
			}
		وإلا {
			لکو("Difference underflows at a higher");
			لکو(" threshold than products.\n");
			}
		}
	لکو("Smallest strictly positive number found is E0 = %d .\n", E0);
	Z = E0;
	TstPtUf();
	Underflow = E0;
	إذا (N == 1) Underflow = Y;
	I = 4;
	إذا (E1 == Zero) I = 3;
	إذا (UfThold == Zero) I = I - 2;
	UfNGrad = True;
	بدل (I)  {
		حالة	1:
		UfThold = Underflow;
		إذا ((CInvrse * Q) != ((CInvrse * Y) * S)) {
			UfThold = Y;
			BadCond(Failure, "Either accuracy deteriorates as numbers\n");
			لکو("approach a threshold = %d\n", UfThold);;
			لکو(" coming down from %d\n", C);
			لکو(" or else multiplication gets too many last digits wrong.\n");
			}
		Pause();
		اكسر;
	
		حالة	2:
		BadCond(Failure, "Underflow confuses Comparison, which alleges that\n");
		لکو("Q == Y while denying that |Q - Y| == 0; these values\n");
		لکو("print out as Q = %d, Y = %016x .\n", Q, Y2);
		لکو ("|Q - Y| = %d .\n" , FABS(Q - Y2));
		UfThold = Q;
		اكسر;
	
		حالة	3:
		X = X;
		اكسر;
	
		حالة	4:
		إذا ((Q == UfThold) && (E1 == E0)
			&& (FABS( UfThold - E1 / E9) <= E1)) {
			UfNGrad = False;
			لکو("Underflow is gradual; it incurs Absolute Error =\n");
			لکو("(roundoff in UfThold) < E0.\n");
			Y = E0 * CInvrse;
			Y = Y * (OneAndHalf + U2);
			X = CInvrse * (One + U2);
			Y = Y / X;
			IEEE = (Y == E0);
			}
		}
	إذا (UfNGrad) {
		لکو("\n");
		sigsave = sigfpe;
		إذا (setjmp(ovfl_buf)) {
			لکو("Underflow / UfThold failed!\n");
			R = H + H;
			}
		وإلا R = SQRT(Underflow / UfThold);
		sigsave = 0;
		إذا (R <= H) {
			Z = R * UfThold;
			X = Z * (One + R * H * (One + H));
			}
		وإلا {
			Z = UfThold;
			X = Z * (One + H * H * (One + H));
			}
		إذا (! ((X == Z) || (X - Z != Zero))) {
			BadCond(Flaw, "");
			لکو("X = %d\n\tis not equal to Z = %016x .\n", X, Z);
			Z9 = X - Z;
			لکو("yet X - Z yields %d .\n", Z9);
			لکو("    Should this NOT signal Underflow, ");
			لکو("this is a SERIOUS DEFECT\nthat causes ");
			لکو("confusion when innocent statements like\n");;
			لکو("    if (X == Z)  ...  else");
			لکو("  ... (f(X) - f(Z)) / (X - Z) ...\n");
			لکو("encounter Division by Zero although actually\n");
			sigsave = sigfpe;
			إذا (setjmp(ovfl_buf)) لکو("X / Z fails!\n");
			وإلا لکو("X / Z = 1 + %d .\n", (X / Z - Half) - Half);
			sigsave = 0;
			}
		}
	لکو("The Underflow threshold is %d, %s\n", UfThold,
		   " below which");
	لکو("calculation may suffer larger Relative error than ");
	لکو("merely roundoff.\n");
	Y2 = U1 * U1;
	Y = Y2 * Y2;
	Y2 = Y * U1;
	إذا (Y2 <= UfThold) {
		إذا (Y > E0) {
			BadCond(Defect, "");
			I = 5;
			}
		وإلا {
			BadCond(Serious, "");
			I = 4;
			}
		لکو("Range is too narrow; U1^%d Underflows.\n", I);
		}
	/*=============================================*/
	/*ورهايو
	}
#include "paranoia.h"
void part7(VOID){
*/
	Milestone = 130;
	/*=============================================*/
	Y = - FLOOR(Half - TwoForty * LOG(UfThold) / LOG(HInvrse)) / TwoForty;
	Y2 = Y + Y;
	لکو("Since underflow occurs below the threshold\n");
	لکو("UfThold = (%d) ^ (%016x)\nonly underflow ", HInvrse, Y);
	لکو("should afflict the expression\n\t(%d) ^ (%016x);\n",
		HInvrse, Y2);
	لکو("actually calculating yields:");
	إذا (setjmp(ovfl_buf)) {
		sigsave = 0;
		BadCond(Serious, "trap on underflow.\n");
		}
	وإلا {
		sigsave = sigfpe;
		V9 = POW(HInvrse, Y2);
		sigsave = 0;
		لکو(" %d .\n", V9);
		إذا (! ((V9 >= Zero) && (V9 <= (Radix + Radix + E9) * UfThold))) {
			BadCond(Serious, "this is not between 0 and underflow\n");
		لکو("   threshold = %d .\n", UfThold);
		}
		وإلا إذا (! (V9 > UfThold * (One + E9)))
			لکو("This computed value is O.K.\n");
		وإلا {
			BadCond(Defect, "this is not between 0 and underflow\n");
			لکو("   threshold = %d .\n", UfThold);
			}
		}
	/*=============================================*/
	Milestone = 140;
	/*=============================================*/
	لکو("\n");
	/* ...calculate Exp2 == exp(2) == 7.389056099... */
	X = Zero;
	I = 2;
	Y = Two * Three;
	Q = Zero;
	N = 0;
	افعل  {
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
	لکو("Testing X^((X + 1) / (X - 1)) vs. exp(2) = %d as X -> 1.\n",
		Exp2);
	لكل(I = 1;;) {
		Z = X - BInvrse;
		Z = (X + One) / (Z - (One - BInvrse));
		Q = POW(X, Z) - Exp2;
		إذا (FABS(Q) > TwoForty * U2) {
			N = 1;
	 		V9 = (X - BInvrse) - (One - BInvrse);
			BadCond(Defect, "Calculated");
			لکو(" %d for\n", POW(X,Z));
			لکو("\t(1 + (%d) ^ (%016x);\n", V9, Z);
			لکو("\tdiffers from correct value by %d .\n", Q);
			لکو("\tThis much error may spoil financial\n");
			لکو("\tcalculations involving tiny interest rates.\n");
			اكسر;
			}
		وإلا {
			Z = (Y - X) * Two + Y;
			X = Y;
			Y = Z;
			Z = One + (X - F9)*(X - F9);
			إذا (Z > One && I < NoTrials) I++;
			وإلا  {
				إذا (X > One) {
					إذا (N == 0)
					   لکو("Accuracy seems adequate.\n");
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
	لکو("Testing powers Z^Q at four nearly extreme values.\n");
	N = 0;
	Z = A1;
	Q = FLOOR(Half - LOG(C) / LOG(A1));
	Break = False;
	افعل  {
		X = CInvrse;
		Y = POW(Z, Q);
		IsYeqX();
		Q = - Q;
		X = C;
		Y = POW(Z, Q);
		IsYeqX();
		إذا (Z < One) Break = True;
		وإلا Z = AInvrse;
		} طالما ( ! (Break));
	PrintIfNPositive();
	إذا (N == 0) لکو(" ... no discrepancies found.\n");
	لکو("\n");
	
	/*=============================================*/
	Milestone = 160;
	/*=============================================*/
	Pause();
	لکو("Searching for Overflow threshold:\n");
	لکو("This may generate an error.\n");
	Y = - CInvrse;
	V9 = HInvrse * Y;
	sigsave = sigfpe;
	إذا (setjmp(ovfl_buf)) { I = 0; V9 = Y; اذهب حد_کان_مٿي; }
	افعل {
		V = Y;
		Y = V9;
		V9 = HInvrse * Y;
		} طالما(V9 < Y);
	I = 1;
حد_کان_مٿي:
	sigsave = 0;
	Z = V9;
	لکو("Can `Z = -Y' overflow?\n");
	لکو("Trying it on Y = %d .\n", Y);
	V9 = - Y;
	V0 = V9;
	إذا (V - Y == V + V0) لکو("Seems O.K.\n");
	وإلا {
		لکو("finds a ");
		BadCond(Flaw, "-(-Y) differs from Y.\n");
		}
	إذا (Z != Y) {
		BadCond(Serious, "");
		لکو("overflow past %d\n\tshrinks to %016x .\n", Y, Z);
		}
	إذا (I) {
		Y = V * (HInvrse * U2 - HInvrse);
		Z = Y + ((One - HInvrse) * U2) * V;
		إذا (Z < V0) Y = Z;
		إذا (Y < V0) V = Y;
		إذا (V0 - V < V0) V = V0;
		}
	وإلا {
		V = Y * (HInvrse * U2 - HInvrse);
		V = V + ((One - HInvrse) * U2) * Y;
		}
	لکو("Overflow threshold is V  = %d .\n", V);
	إذا (I) لکو("Overflow saturates at V0 = %d .\n", V0);
	وإلا لکو("There is no saturation قدر because \
the system traps on حد_کان_مٿي.\n");
	V9 = V * One;
	لکو("No Overflow should be signaled for V * 1 = %d\n", V9);
	V9 = V / One;
	لکو("                           nor for V / 1 = %d .\n", V9);
	لکو("Any overflow signal separating this * from the one\n");
	لکو("above is a DEFECT.\n");
	/*=============================================*/
	Milestone = 170;
	/*=============================================*/
	إذا (!(-V < V && -V0 < V0 && -UfThold < V && UfThold < V)) {
		BadCond(Failure, "Comparisons involving ");
		لکو("+-%d, +-%016x\nand +-%016x are confused by Overflow.",
			V, V0, UfThold);
		}
	/*=============================================*/
	Milestone = 175;
	/*=============================================*/
	لکو("\n");
	لكل(Indx = 1; Indx <= 3; ++Indx) {
		بدل (Indx)  {
			حالة 1: Z = UfThold; اكسر;
			حالة 2: Z = E0; اكسر;
			حالة 3: Z = PseudoZero; اكسر;
			}
		إذا (Z != Zero) {
			V9 = SQRT(Z);
			Y = V9 * V9;
			إذا (Y / (One - Radix * E9) < Z
			   || Y > (One + Radix * E9) * Z) { /* dgh: + E9 --> * E9 */
				إذا (V9 > U1) BadCond(Serious, "");
				وإلا BadCond(Defect, "");
				لکو("Comparison alleges that what prints as Z = %d\n", Z);
				لکو(" is too far from sqrt(Z) ^ 2 = %d .\n", Y);
				}
			}
		}
	/*=============================================*/
	Milestone = 180;
	/*=============================================*/
	لكل(Indx = 1; Indx <= 2; ++Indx) {
		إذا (Indx == 1) Z = V;
		وإلا Z = V0;
		V9 = SQRT(Z);
		X = (One - Radix * E9) * V9;
		V9 = V9 * X;
		إذا (((V9 < (One - Two * Radix * E9) * Z) || (V9 > Z))) {
			Y = V9;
			إذا (X < W) BadCond(Serious, "");
			وإلا BadCond(Defect, "");
			لکو("Comparison alleges that Z = %d\n", Z);
			لکو(" is too far from sqrt(Z) ^ 2 (%d) .\n", Y);
			}
		}
	/*=============================================*/
	/*ورهايو
	}
#include "paranoia.h"
int part8(VOID){
*/
	Milestone = 190;
	/*=============================================*/
	Pause();
	X = UfThold * V;
	Y = Radix * Radix;
	إذا (X*Y < One || X > Y) {
		إذا (X * Y < U1 || X > Y/U1) BadCond(Defect, "Badly");
		وإلا BadCond(Flaw, "");
			
		لکو(" unbalanced range; UfThold * V = %d\n\t%s\n",
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
		إذا (setjmp(ovfl_buf))
			لکو("  X / X  traps when X = %d\n", X);
		وإلا {
			V9 = (Y / X - Half) - Half;
			إذا (V9 == Zero) استمر;
			إذا (V9 == - U1 && Indx < 5) BadCond(Flaw, "");
			وإلا BadCond(Serious, "");
			لکو("  X / X differs from 1 when X = %d\n", X);
			لکو("  instead, X / X - 1/2 - 1/2 = %d .\n", V9);
			}
		sigsave = 0;
		}
	/*=============================================*/
	Milestone = 210;
	/*=============================================*/
	MyZero = Zero;
	لکو("\n");
	لکو("What message and/or values does Division by Zero produce?\n") ;
#جيڪڏهن_وصف_نه_ٿيل NOPAUSE
	لکو("This can interupt your program.  You can ");
	لکو("skip this part if you wish.\n");
	لکو("Do you wish to compute 1 / 0? ");
	fflush(stdout);
	اقرأ (KEYBOARD, ch, 8);
	إذا ((ch[0] == 'Y') || (ch[0] == 'y')) {
#جيڪڏهن_پورو
		sigsave = sigfpe;
		لکو("    Trying to compute 1 / 0 produces ...");
		إذا (!setjmp(ovfl_buf)) لکو("  %d .\n", One / MyZero);
		sigsave = 0;
#جيڪڏهن_وصف_نه_ٿيل NOPAUSE
		}
	وإلا لکو("O.K.\n");
	لکو("\nDo you wish to compute 0 / 0? ");
	fflush(stdout);
	اقرأ (KEYBOARD, ch, 80);
	إذا ((ch[0] == 'Y') || (ch[0] == 'y')) {
#جيڪڏهن_پورو
		sigsave = sigfpe;
		لکو("\n    Trying to compute 0 / 0 produces ...");
		إذا (!setjmp(ovfl_buf)) لکو("  %d .\n", Zero / MyZero);
		sigsave = 0;
#جيڪڏهن_وصف_نه_ٿيل NOPAUSE
		}
	وإلا لکو("O.K.\n");
#جيڪڏهن_پورو
	/*=============================================*/
	Milestone = 220;
	/*=============================================*/
	Pause();
	لکو("\n");
	{
		ساكن حرف *نياپو[] = {
			"FAILUREs  encountered =",
			"SERIOUS DEFECTs  discovered =",
			"DEFECTs  discovered =",
			"FLAWs  discovered =" };
		صحيح i;
		لكل(i = 0; i < 4; i++) إذا (ErrCnt[i])
			لکو("The number of  %-29s %d.\n",
				نياپو[i], ErrCnt[i]);
		}
	لکو("\n");
	إذا ((ErrCnt[Failure] + ErrCnt[Serious] + ErrCnt[Defect]
			+ ErrCnt[Flaw]) > 0) {
		إذا ((ErrCnt[Failure] + ErrCnt[Serious] + ErrCnt[
			Defect] == 0) && (ErrCnt[Flaw] > 0)) {
			لکو("The arithmetic diagnosed seems ");
			لکو("Satisfactory though flawed.\n");
			}
		إذا ((ErrCnt[Failure] + ErrCnt[Serious] == 0)
			&& ( ErrCnt[Defect] > 0)) {
			لکو("The arithmetic diagnosed may be Acceptable\n");
			لکو("despite inconvenient Defects.\n");
			}
		إذا ((ErrCnt[Failure] + ErrCnt[Serious]) > 0) {
			لکو("The arithmetic diagnosed has ");
			لکو("unacceptable Serious Defects.\n");
			}
		إذا (ErrCnt[Failure] > 0) {
			لکو("Potentially fatal FAILURE may have spoiled this");
			لکو(" program's subsequent diagnoses.\n");
			}
		}
	وإلا {
		لکو("No failures, defects nor flaws have been discovered.\n");
		إذا (! ((RMult == Rounded) && (RDiv == Rounded)
			&& (RAddSub == Rounded) && (RSqrt == Rounded))) 
			لکو("The arithmetic diagnosed seems Satisfactory.\n");
		وإلا {
			إذا (Sticky_ٻٽو_انگ >= One &&
				(Radix - Two) * (Radix - Nine - One) == Zero) {
				لکو("Rounding appears to conform to ");
				لکو("the proposed IEEE standard P");
				إذا ((Radix == Two) &&
					 ((Precision - Four * Three * Two) *
					  ( Precision - TwentySeven -
					   TwentySeven + One) == Zero)) 
					لکو("754");
				وإلا لکو("854");
				إذا (IEEE) لکو(".\n");
				وإلا {
					لکو(",\nexcept for possibly Double Rounding");
					لکو(" during Gradual Underflow.\n");
					}
				}
			لکو("The arithmetic diagnosed appears to be Excellent!\n");
			}
		}
	إذا (fpecount)
		لکو("\nA total of %d floating point exceptions were registered.\n",
			fpecount);
	لکو("END OF TEST $\n");
  __asm__("ebreak");
	//return 0;
	}

/*SPLIT subs.c
#include "paranoia.h"
*/

 FLOAT
Sign (FP X)
#جيڪڏهن_وصف_ٿيل KR_سرا
FLOAT X;
#جيڪڏهن_پورو
{ أرجع X >= 0. ? 1.0 : -1.0; }

 فراغ
Pause(VOID)
{
#جيڪڏهن_وصف_نه_ٿيل NOPAUSE
	حرف ch[8];

	لکو("\nTo continue, press RETURN");
	fflush(stdout);
	اقرأ(KEYBOARD, ch, 8);
#جيڪڏهن_پورو
	لکو("\nDiagnosis resumes after milestone Number %d", Milestone);
	لکو("          Page: %d\n\n", صفحو_No);
	++Milestone;
	++صفحو_No;
	}

 فراغ
TstCond (INT K, INT Valid, CHARP T)
#جيڪڏهن_وصف_ٿيل KR_سرا
صحيح K, Valid;
حرف *T;
#جيڪڏهن_پورو
{ إذا (! Valid) { BadCond(K,T); لکو(".\n"); } }

 فراغ
BadCond(INT K, CHARP T)
#جيڪڏهن_وصف_ٿيل KR_سرا
صحيح K;
حرف *T;
#جيڪڏهن_پورو
{
	ساكن حرف *نياپو[] = { "FAILURE", "SERIOUS DEFECT", "DEFECT", "FLAW" };

	ErrCnt [K] = ErrCnt [K] + 1;
	لکو("%s:  %s", نياپو[K], T);
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
SqXMinX (INT Err_قسم)
#جيڪڏهن_وصف_ٿيل KR_سرا
صحيح Err_قسم;
#جيڪڏهن_پورو
{
	FLOAT XA, XB;
	
	XB = X * BInvrse;
	XA = X - XB;
	SqEr = ((SQRT(X * X) - XB) - XA) / OneUlp;
	إذا (SqEr != Zero) {
		إذا (SqEr < MinSqEr) MinSqEr = SqEr;
		إذا (SqEr > MaxSqEr) MaxSqEr = SqEr;
		J = J + 1.0;
		BadCond(Err_قسم, "\n");
		لکو("sqrt( %d) - %016x  = %016x\n", X * X, X, OneUlp * SqEr);
		لکو("\tinstead of correct value 0 .\n");
		}
	}

 فراغ
NewD(VOID)
{
	X = Z1 * Q;
	X = FLOOR(Half - X / Radix) * Radix + X;
	Q = (Q - X * Z) / Radix + X * X * (D / Radix);
	Z = Z - Two * X * D;
	إذا (Z <= Zero) {
		Z = - Z;
		Z1 = - Z1;
		}
	D = Radix * D;
	}

 فراغ
SR3750(VOID)
{
	إذا (! ((X - Radix < Z2 - Radix) || (X - Z2 > W - Z2))) {
		I = I + 1;
		X2 = SQRT(X * D);
		Y2 = (X2 - Z2) - (Y - Z2);
		X2 = X8 / (Y - Half);
		X2 = X2 - Half * X2 * X2;
		SqEr = (Y2 + Half) + (Half - X2);
		إذا (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = Y2 - X2;
		إذا (SqEr > MaxSqEr) MaxSqEr = SqEr;
		}
	}

 فراغ
IsYeqX(VOID)
{
	إذا (Y != X) {
		إذا (N <= 0) {
			إذا (Z == Zero && Q <= Zero)
				لکو("WARNING:  computing\n");
			وإلا BadCond(Defect, "computing\n");
			لکو("\t(%d) ^ (%016x)\n", Z, Q);
			لکو("\tyielded %d;\n", Y);
			لکو("\twhich compared unequal to correct %d ;\n",
				X);
			لکو("\t\tthey differ by %d .\n", Y - X);
			}
		N = N + 1; /* ... count discrepancies. */
		}
	}

 فراغ
SR3980(VOID)
{
	افعل {
		Q = (FLOAT) I;
		Y = POW(Z, Q);
		IsYeqX();
		إذا (++I > M) اكسر;
		X = Z * X;
		} طالما ( X < W );
	}

 فراغ
PrintIfNPositive(VOID)
{
	إذا (N > 0) لکو("Similar discrepancies have occurred %d times.\n", N);
	}

 فراغ
TstPtUf(VOID)
{
	N = 0;
	إذا (Z != Zero) {
		لکو("Since comparison denies Z = 0, evaluating ");
		لکو("(Z + Z) / Z should be safe.\n");
		sigsave = sigfpe;
		إذا (setjmp(ovfl_buf)) اذهب very_serious;
		Q9 = (Z + Z) / Z;
		لکو("What the machine gets for (Z + Z) / Z is  %d .\n",
			Q9);
		إذا (FABS(Q9 - Two) < Radix * U2) {
			لکو("This is O.K., provided Over/Underflow");
			لکو(" has NOT just been signaled.\n");
			}
		وإلا {
			إذا ((Q9 < One) || (Q9 > Two)) {
very_serious:
				N = 1;
				ErrCnt [Serious] = ErrCnt [Serious] + 1;
				لکو("This is a VERY SERIOUS DEFECT!\n");
				}
			وإلا {
				N = 1;
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				لکو("This is a DEFECT!\n");
				}
			}
		sigsave = 0;
		V9 = Z * One;
		Random1 = V9;
		V9 = One * Z;
		Random2 = V9;
		V9 = Z / One;
		إذا ((Z == Random1) && (Z == Random2) && (Z == V9)) {
			إذا (N > 0) Pause();
			}
		وإلا {
			N = 1;
			BadCond(Defect, "What prints as Z = ");
			لکو("%d\n\tcompares different from  ", Z);
			إذا (Z != Random1) لکو("Z * 1 = %d ", Random1);
			إذا (! ((Z == Random2)
				|| (Random2 == Random1)))
				لکو("1 * Z == %d\n", Random2);
			إذا (! (Z == V9)) لکو("Z / 1 = %d\n", V9);
			إذا (Random2 != Random1) {
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				BadCond(Defect, "Multiplication does not commute!\n");
				لکو("\tComparison alleges that 1 * Z = %d\n",
					Random2);
				لکو("\tdiffers from Z * 1 = %d\n", Random1);
				}
			Pause();
			}
		}
	}

 فراغ
notify(CHARP s)
#جيڪڏهن_وصف_ٿيل KR_سرا
 حرف *s;
#جيڪڏهن_پورو
{
	لکو("%s test appears to be inconsistent...\n", s);
	لکو("   PLEASE NOTIFY KARPINKSI!\n");
	}

/*SPLIT msgs.c
#include "paranoia.h"
*/

 فراغ
msglist(CHARPP s)
#جيڪڏهن_وصف_ٿيل KR_سرا
حرف **s;
#جيڪڏهن_پورو
{ طالما(*s) لکو("%s\n", *s++); }

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
  ساكن حرف *سر[] = {
	"Users are invited to help debug and augment this program so it will",
	"cope with unanticipated and newly uncovered arithmetic pathologies.\n",
	"Please send suggestions and interesting results to",
	"\tRichard Karpinski",
	"\tComputer Center U-76",
	"\tUniversity of California",
	"\tSan Francisco, CA 94143-0704, USA\n",
	"In doing so, please include the following information:",
#جيڪڏهن_وصف_ٿيل Single
	"\tPrecision:\tsingle;",
#وإلا
	"\tPrecision:\tdouble;",
#جيڪڏهن_پورو
	"\tVersion:\t10 February 1989;",
	"\tComputer:\n",
	"\tCompiler:\n",
	"\tOptimization level:\n",
	"\tOther relevant compiler options:",
	0};

	msglist(سر);
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
