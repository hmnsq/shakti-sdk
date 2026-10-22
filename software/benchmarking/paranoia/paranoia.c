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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NOSIGNAL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NOPAUSE
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NOSIGNAL
#ਅਨ੍ਤਰ੍ਭਾਵ <signal.h>
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <setjmp.h>
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ Single
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FLOAT ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FABS(x) (ਦਸ਼ਮਲਵ)fabs((ਦੁੱਗਣਾ)(x))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FLOOR(x) (ਦਸ਼ਮਲਵ)floor((ਦੁੱਗਣਾ)(x))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOG(x) (ਦਸ਼ਮਲਵ)ਲਘੂਗਣਕ((ਦੁੱਗਣਾ)(x))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ POW(x,y) (ਦਸ਼ਮਲਵ)ਘਾਤ((ਦੁੱਗਣਾ)(x),(ਦੁੱਗਣਾ)(y))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SQRT(x) (ਦਸ਼ਮਲਵ)ਵਰਗਮੂਲ((ਦੁੱਗਣਾ)(x))
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FLOAT ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FABS(x) fabs(x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FLOOR(x) floor(x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOG(x) ਲਘੂਗਣਕ(x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ POW(x,y) ਘਾਤ(x,y)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SQRT(x) ਵਰਗਮੂਲ(x)
#ਜੇ_ਅੰਤ

jmp_buf ovfl_buf;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KR_ਸਿਰਲੇਖਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VOID /* void */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT /* int */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FP /* FLOAT */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHARP /* char * */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHARPP /* char ** */
ਬਾਹਰੀ ਦੁੱਗਣਾ fabs(), floor(), ਲਘੂਗਣਕ(), ਘਾਤ(), ਵਰਗਮੂਲ();
ਬਾਹਰੀ ਖਾਲੀ ਬਾਹਰ_ਨਿਕਲੋ();
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*Sig_type)();
FLOAT Sign(), Random();
ਬਾਹਰੀ ਖਾਲੀ BadCond();
ਬਾਹਰੀ ਖਾਲੀ SqXMinX();
ਬਾਹਰੀ ਖਾਲੀ TstCond();
ਬਾਹਰੀ ਖਾਲੀ notify();
ਬਾਹਰੀ ਪੂਰਨ ਪਠ();
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VOID ਖਾਲੀ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT ਪੂਰਨ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FP FLOAT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHARP ਅੱਖਰ *
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHARPP ਅੱਖਰ **
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __STDC__
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>
#ਨਹੀਂਤਾਂ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
ਬਾਹਰੀ ਦੁੱਗਣਾ fabs(ਦੁੱਗਣਾ), floor(ਦੁੱਗਣਾ), ਲਘੂਗਣਕ(ਦੁੱਗਣਾ);
ਬਾਹਰੀ ਦੁੱਗਣਾ ਘਾਤ(ਦੁੱਗਣਾ,ਦੁੱਗਣਾ), ਵਰਗਮੂਲ(ਦੁੱਗਣਾ);
ਬਾਹਰੀ ਖਾਲੀ ਬਾਹਰ_ਨਿਕਲੋ(INT);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
	}
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*Sig_type)(ਪੂਰਨ);
FLOAT Sign(FLOAT), Random(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ BadCond(ਪੂਰਨ, ਅੱਖਰ*);
ਬਾਹਰੀ ਖਾਲੀ SqXMinX(ਪੂਰਨ);
ਬਾਹਰੀ ਖਾਲੀ TstCond(ਪੂਰਨ, ਪੂਰਨ, ਅੱਖਰ*);
ਬਾਹਰੀ ਖਾਲੀ notify(ਅੱਖਰ*);
ਬਾਹਰੀ ਪੂਰਨ ਪਠ(ਪੂਰਨ, ਅੱਖਰ*, ਪੂਰਨ);
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ V9
ਬਾਹਰੀ ਖਾਲੀ Characteristics(VOID);
ਬਾਹਰੀ ਖਾਲੀ Heading(VOID);
ਬਾਹਰੀ ਖਾਲੀ History(VOID);
ਬਾਹਰੀ ਖਾਲੀ Instructions(VOID);
ਬਾਹਰੀ ਖਾਲੀ IsYeqX(VOID);
ਬਾਹਰੀ ਖਾਲੀ NewD(VOID);
ਬਾਹਰੀ ਖਾਲੀ Pause(VOID);
ਬਾਹਰੀ ਖਾਲੀ PrintIfNPositive(VOID);
ਬਾਹਰੀ ਖਾਲੀ SR3750(VOID);
ਬਾਹਰੀ ਖਾਲੀ SR3980(VOID);
ਬਾਹਰੀ ਖਾਲੀ TstPtUf(VOID);

Sig_type sigsave;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KEYBOARD 0

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
ਪੂਰਨ NoTrials = 20; /*Number of tests for commutativity. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ False 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ True 1

/* Definitions for declared types 
	Guard == (Yes, No);
	Rounding == (Chopped, Rounded, Other);
	Message == packed array [1..40] of char;
	Class == (Flaw, Defect, Serious, Failure);
	  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Yes 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ No  0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Chopped 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Rounded 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Other   0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Flaw    3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Defect  2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Serious 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Failure 0
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ Guard, Rounding, Class;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ ਸੁਨੇਹਾ;

/* Declarations of Variables */
ਪੂਰਨ Indx;
ਅੱਖਰ ch[8];
FLOAT AInvrse, A1;
FLOAT C, CInvrse;
FLOAT D, FourD;
FLOAT E0, E1, Exp2, E3, MinSqEr;
FLOAT SqEr, MaxSqEr, E9;
FLOAT ਤੀਜਾ;
FLOAT F6, F9;
FLOAT H, HInvrse;
ਪੂਰਨ I;
FLOAT Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ, J;
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
ਪੂਰਨ ErrCnt[4];
ਪੂਰਨ fpecount;
ਪੂਰਨ Milestone;
ਪੂਰਨ ਪੰਨਾ_No;
ਪੂਰਨ M, N, N1;
Guard GMult, GDiv, GAddSub;
Rounding RMult, RDiv, RAddSub, RSqrt;
ਪੂਰਨ Break, ਪੂਰਾ, NotMonot, Monot, Anomaly, IEEE,
		SqRWrng, UfNGrad;
/* Computed constants. */
/*U1  gap below 1.0, i.e, 1.0-U1 is next number below 1.0 */
/*U2  gap above 1.0, i.e, 1.0+U2 is next number above 1.0 */

/* floating point exception receiver */
 ਖਾਲੀ
sigfpe(INT x)
{
	fpecount++;
	ਲਿਖੋ("\n* * * FLOATING-POINT ERROR %d * * *\n", x);
	fflush(stdout);
	ਜੇ (sigsave) {
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NOSIGNAL
		ਸੰਕੇਤ(SIGFPE, sigsave);
#ਜੇ_ਅੰਤ
		sigsave = 0;
		longjmp(ovfl_buf, 1);
		}
	ਬਾਹਰ_ਨਿਕਲੋ(1);
}

ਮੁੱਖ(VOID)
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
	ਪੰਨਾ_No = 1;
	/*=============================================*/
	Milestone = 0;
	/*=============================================*/
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NOSIGNAL
	ਸੰਕੇਤ(SIGFPE, sigfpe);
#ਜੇ_ਅੰਤ
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
	ਲਿਖੋ("Program is now RUNNING tests on small integers:\n");
	
	TstCond (Failure, (Zero + Zero == Zero) && (One - One == Zero)
		   && (One > Zero) && (One + One == Two),
			"0+0 != 0, 1-1 != 0, 1 <= 0, or 1+1 != 2");
	Z = - Zero;
	ਜੇ (Z != 0.0) {
		ErrCnt[Failure] = ErrCnt[Failure] + 1;
		ਲਿਖੋ("Comparison alleges that -0.0 is Non-zero!\n");
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
	/*ਵੰਡੋ
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
	ਜੇ (ErrCnt[Failure] == 0) {
		ਲਿਖੋ("-1, 0, 1/2, 1, 2, 3, 4, 5, 9, 27, 32 & 240 are O.K.\n");
		ਲਿਖੋ("\n");
		}
	ਲਿਖੋ("Searching for Radix and Precision.\n");
	W = One;
	ਕਰੋ  {
		W = W + W;
		Y = W + One;
		Z = Y - W;
		Y = Z - One;
		} ਜਦੋਂ (MinusOne + FABS(Y) < Zero);
	/*.. now W is just big enough that |((W+1)-W)-1| >= 1 ...*/
	Precision = Zero;
	Y = One;
	ਕਰੋ  {
		Radix = W + Y;
		Y = Y + Y;
		Radix = Radix - W;
		} ਜਦੋਂ ( Radix == Zero);
	ਜੇ (Radix < Two) Radix = One;
	ਲਿਖੋ("Radix = %d .\n", Radix);
	ਜੇ (Radix != 1) {
		W = One;
		ਕਰੋ  {
			Precision = Precision + One;
			W = W * Radix;
			Y = W + One;
			} ਜਦੋਂ ((Y - W) == One);
		}
	/*... now W == Radix^Precision is barely too big to satisfy (W+1)-W == 1
			                              ...*/
	U1 = One / W;
	U2 = Radix * U1;
	ਲਿਖੋ("Closest relative separation found is U1 = %d .\n\n", U1);
	ਲਿਖੋ("Recalculating radix and precision\n ");
	
	/*save old values*/
	E0 = Radix;
	E1 = U1;
	E9 = U2;
	E3 = Precision;
	
	X = Four / Three;
	ਤੀਜਾ = X - One;
	F6 = Half - ਤੀਜਾ;
	X = F6 + F6;
	X = FABS(X - ਤੀਜਾ);
	ਜੇ (X < U2) X = U2;
	
	/*... now X = (unknown no.) ulps of 1+...*/
	ਕਰੋ  {
		U2 = X;
		Y = Half * U2 + ThirtyTwo * U2 * U2;
		Y = One + Y;
		X = Y - One;
		} ਜਦੋਂ ( ! ((U2 <= X) || (X <= Zero)));
	
	/*... now U2 == 1 ulp of 1 + ... */
	X = Two / Three;
	F6 = X - Half;
	ਤੀਜਾ = F6 + F6;
	X = ਤੀਜਾ - Half;
	X = FABS(X + F6);
	ਜੇ (X < U1) X = U1;
	
	/*... now  X == (unknown no.) ulps of 1 -... */
	ਕਰੋ  {
		U1 = X;
		Y = Half * U1 + ThirtyTwo * U1 * U1;
		Y = Half - Y;
		X = Half + Y;
		Y = Half - X;
		X = Half + Y;
		} ਜਦੋਂ ( ! ((U1 <= X) || (X <= Zero)));
	/*... now U1 == 1 ulp of 1 - ... */
	ਜੇ (U1 == E1) ਲਿਖੋ("confirms closest relative separation U1 .\n");
	ਨਹੀਂਤਾਂ ਲਿਖੋ("gets better closest relative separation U1 = %d .\n", U1);
	W = One / U1;
	F9 = (Half - U1) + Half;
	Radix = FLOOR(0.01 + U2 / U1);
	ਜੇ (Radix == E0) ਲਿਖੋ("Radix confirmed.\n");
	ਨਹੀਂਤਾਂ ਲਿਖੋ("MYSTERY: recalculated Radix = %d .\n", Radix);
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
	ਜੇ (Radix != One)  {
		X = - TwoForty * LOG(U1) / LOG(Radix);
		Y = FLOOR(Half + X);
		ਜੇ (FABS(X - Y) * Four < One) X = Y;
		Precision = X / TwoForty;
		Y = FLOOR(Half + Precision);
		ਜੇ (FABS(Precision - Y) * TwoForty < Half) Precision = Y;
		}
	ਜੇ ((Precision != FLOOR(Precision)) || (Radix == One)) {
		ਲਿਖੋ("Precision cannot be characterized by an Integer number\n");
		ਲਿਖੋ("of significant digits but, by itself, this is a minor flaw.\n");
		}
	ਜੇ (Radix == One) 
		ਲਿਖੋ("logarithmic encoding has precision characterized solely by U1.\n");
	ਨਹੀਂਤਾਂ ਲਿਖੋ("The number of significant digits of the Radix is %d .\n",
			Precision);
	TstCond (Serious, U2 * Nine * Nine * TwoForty < One,
		   "Precision worse than 5 decimal figures  ");
	/*=============================================*/
	Milestone = 30;
	/*=============================================*/
	/* Test for extra-precise subepressions */
	X = FABS(((Four / Three - One) - One / Four) * Three - One / Four);
	ਕਰੋ  {
		Z2 = X;
		X = (One + (Half * Z2 + ThirtyTwo * Z2 * Z2)) - One;
		} ਜਦੋਂ ( ! ((Z2 <= X) || (X <= Zero)));
	X = Y = Z = FABS((Three / Four - Two / Three) * Three - One / Four);
	ਕਰੋ  {
		Z1 = Z;
		Z = (One / Two - ((One / Two - (Half * Z1 + ThirtyTwo * Z1 * Z1))
			+ One / Two)) + One / Two;
		} ਜਦੋਂ ( ! ((Z1 <= Z) || (Z <= Zero)));
	ਕਰੋ  {
		ਕਰੋ  {
			Y1 = Y;
			Y = (Half - ((Half - (Half * Y1 + ThirtyTwo * Y1 * Y1)) + Half
				)) + Half;
			} ਜਦੋਂ ( ! ((Y1 <= Y) || (Y <= Zero)));
		X1 = X;
		X = ((Half * X1 + ThirtyTwo * X1 * X1) - F9) + F9;
		} ਜਦੋਂ ( ! ((X1 <= X) || (X <= Zero)));
	ਜੇ ((X1 != Y1) || (X1 != Z1)) {
		BadCond(Serious, "Disagreements among the values X1, Y1, Z1,\n");
		ਲਿਖੋ("respectively  %d,  %016x,  %016x,\n", X1, Y1, Z1);
		ਲਿਖੋ("are symptoms of inconsistencies introduced\n");
		ਲਿਖੋ("by extra-precise evaluation of arithmetic subexpressions.\n");
		notify("Possibly some part of this");
		ਜੇ ((X1 == U1) || (Y1 == U1) || (Z1 == U1))  ਲਿਖੋ(
			"That feature is not tested further by this program.\n") ;
		}
	ਨਹੀਂਤਾਂ  {
		ਜੇ ((Z1 != U1) || (Z2 != U2)) {
			ਜੇ ((Z1 >= U1) || (Z2 >= U2)) {
				BadCond(Failure, "");
				notify("Precision");
				ਲਿਖੋ("\tU1 = %d, Z1 - U1 = %016x\n",U1,Z1-U1);
				ਲਿਖੋ("\tU2 = %d, Z2 - U2 = %016x\n",U2,Z2-U2);
				}
			ਨਹੀਂਤਾਂ {
				ਜੇ ((Z1 <= Zero) || (Z2 <= Zero)) {
					ਲਿਖੋ("Because of unusual Radix = %d", Radix);
					ਲਿਖੋ(", or exact rational arithmetic a result\n");
					ਲਿਖੋ("Z1 = %d, or Z2 = %016x ", Z1, Z2);
					notify("of an\nextra-precision");
					}
				ਜੇ (Z1 != Z2 || Z1 > Zero) {
					X = Z1 / U1;
					Y = Z2 / U2;
					ਜੇ (Y > X) X = Y;
					Q = - LOG(X);
					ਲਿਖੋ("Some subexpressions appear to be calculated extra\n");
					ਲਿਖੋ("precisely with about %d extra B-digits, i.e.\n",
						(Q / LOG(Radix)));
					ਲਿਖੋ("roughly %d extra significant decimals.\n",
						Q / LOG(10.));
					}
				ਲਿਖੋ("That feature is not tested further by this program.\n");
				}
			}
		}
	Pause();
	/*=============================================*/
	/*ਵੰਡੋ
	}
#include "paranoia.h"
void part3(VOID){
*/
	Milestone = 35;
	/*=============================================*/
	ਜੇ (Radix >= Two) {
		X = W / (Radix * Radix);
		Y = X + One;
		Z = Y - X;
		T = Z + U2;
		X = T - Z;
		TstCond (Failure, X == U2,
			"Subtraction is not normalized X=Y,X+Z != Y+Z!");
		ਜੇ (X == U2) ਲਿਖੋ(
			"Subtraction appears to be normalized, as it should be.");
		}
	ਲਿਖੋ("\nChecking for guard digit in *, /, and -.\n");
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
	ਜੇ ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)) GMult = Yes;
	ਨਹੀਂਤਾਂ {
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
	ਜੇ ((X == Zero) && (Y == Zero) && (Z == Zero)) GDiv = Yes;
	ਨਹੀਂਤਾਂ {
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
	Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ = T / Radix;
	X = R - X;
	Y = Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ - Y;
	TstCond (Failure, X == Zero && Y == Zero,
			"* and/or / gets too many last digits wrong");
	Y = One - U1;
	X = One - F9;
	Y = One - Y;
	T = Radix - U2;
	Z = Radix - BMinusU2;
	T = Radix - T;
	ਜੇ ((X == U1) && (Y == U1) && (Z == U2) && (T == U2)) GAddSub = Yes;
	ਨਹੀਂਤਾਂ {
		GAddSub = No;
		TstCond (Serious, False,
			"- lacks Guard Digit, so cancellation is obscured");
		}
	ਜੇ (F9 != One && F9 - One >= Zero) {
		BadCond(Serious, "comparison alleges  (1-U1) < 1  although\n");
		ਲਿਖੋ("  subtraction yields  (1-U1) - 1 = 0 , thereby vitiating\n");
		ਲਿਖੋ("  such precautions against division by zero as\n");
		ਲਿਖੋ("  ...  if (X == 1.0) {.....} else {.../(X-1.0)...}\n");
		}
	ਜੇ (GMult == Yes && GDiv == Yes && GAddSub == Yes) ਲਿਖੋ(
		"     *, /, and - appear to have guard digits, as they should.\n");
	/*=============================================*/
	Milestone = 40;
	/*=============================================*/
	Pause();
	ਲਿਖੋ("Checking rounding on multiply, divide and add/subtract.\n");
	RMult = Other;
	RDiv = Other;
	RAddSub = Other;
	RadixD2 = Radix / Two;
	A1 = Two;
	ਪੂਰਾ = False;
	ਕਰੋ  {
		AInvrse = Radix;
		ਕਰੋ  {
			X = AInvrse;
			AInvrse = AInvrse / A1;
			} ਜਦੋਂ ( ! (FLOOR(AInvrse) != AInvrse));
		ਪੂਰਾ = (X == One) || (A1 > Three);
		ਜੇ (! ਪੂਰਾ) A1 = Nine + One;
		} ਜਦੋਂ ( ! (ਪੂਰਾ));
	ਜੇ (X == One) A1 = Radix;
	AInvrse = One / A1;
	X = A1;
	Y = AInvrse;
	ਪੂਰਾ = False;
	ਕਰੋ  {
		Z = X * Y - Half;
		TstCond (Failure, Z == Half,
			"X * (1/X) differs from 1");
		ਪੂਰਾ = X == Radix;
		X = Radix;
		Y = One / X;
		} ਜਦੋਂ ( ! (ਪੂਰਾ));
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
	ਜੇ ((X == Zero) && (Y == Zero) && (Z == Zero) && (T <= Zero)) {
		X = (OneAndHalf + U2) * Y2;
		Y = OneAndHalf - U2 - U2;
		Z = OneAndHalf + U2 + U2;
		T = (OneAndHalf - U2) * Y1;
		X = X - (Z + U2);
		Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ = Y * Y1;
		S = Z * Y2;
		T = T - Y;
		Y = (U2 - Y) + Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ;
		Z = S - (Z + U2 + U2);
		Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ = (Y2 + U2) * Y1;
		Y1 = Y2 * Y1;
		Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ = Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ - Y2;
		Y1 = Y1 - Half;
		ਜੇ ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)
			&& ( Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ == Zero) && (Y1 == Half)) {
			RMult = Rounded;
			ਲਿਖੋ("Multiplication appears to round correctly.\n");
			}
		ਨਹੀਂਤਾਂ	ਜੇ ((X + U2 == Zero) && (Y < Zero) && (Z + U2 == Zero)
				&& (T < Zero) && (Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ + U2 == Zero)
				&& (Y1 < Half)) {
				RMult = Chopped;
				ਲਿਖੋ("Multiplication appears to chop.\n");
				}
			ਨਹੀਂਤਾਂ ਲਿਖੋ("* is neither chopped nor correctly rounded.\n");
		ਜੇ ((RMult == Rounded) && (GMult == No)) notify("Multiplication");
		}
	ਨਹੀਂਤਾਂ ਲਿਖੋ("* is neither chopped nor correctly rounded.\n");
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
	ਜੇ (! ((X > Zero) || (Y > Zero) || (Z > Zero) || (T > Zero))) {
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
		ਜੇ ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)
			&& (Y2 == Zero) && (Y2 == Zero)
			&& (Y1 - Half == F9 - Half )) {
			RDiv = Rounded;
			ਲਿਖੋ("Division appears to round correctly.\n");
			ਜੇ (GDiv == No) notify("Division");
			}
		ਨਹੀਂਤਾਂ ਜੇ ((X < Zero) && (Y < Zero) && (Z < Zero) && (T < Zero)
			&& (Y2 < Zero) && (Y1 - Half < F9 - Half)) {
			RDiv = Chopped;
			ਲਿਖੋ("Division appears to chop.\n");
			}
		}
	ਜੇ (RDiv == Other) ਲਿਖੋ("/ is neither chopped nor correctly rounded.\n");
	BInvrse = One / Radix;
	TstCond (Failure, (BInvrse * Radix - Half == Half),
		   "Radix * ( 1 / Radix ) differs from 1");
	/*=============================================*/
	/*ਵੰਡੋ
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
	ਜੇ ((X == Zero) && (Y == Zero)) {
		RAddSub = Chopped;
		ਲਿਖੋ("Add/Subtract appears to be chopped.\n");
		}
	ਜੇ (GAddSub == Yes) {
		X = (Half + U2) * U2;
		Y = (Half - U2) * U2;
		X = One + X;
		Y = One + Y;
		X = (One + U2) - X;
		Y = One - Y;
		ਜੇ ((X == Zero) && (Y == Zero)) {
			X = (Half + U2) * U1;
			Y = (Half - U2) * U1;
			X = One - X;
			Y = One - Y;
			X = F9 - X;
			Y = One - Y;
			ਜੇ ((X == Zero) && (Y == Zero)) {
				RAddSub = Rounded;
				ਲਿਖੋ("Addition/Subtraction appears to round correctly.\n");
				ਜੇ (GAddSub == No) notify("Add/Subtract");
				}
			ਨਹੀਂਤਾਂ ਲਿਖੋ("Addition/Subtraction neither rounds nor chops.\n");
			}
		ਨਹੀਂਤਾਂ ਲਿਖੋ("Addition/Subtraction neither rounds nor chops.\n");
		}
	ਨਹੀਂਤਾਂ ਲਿਖੋ("Addition/Subtraction neither rounds nor chops.\n");
	S = One;
	X = One + Half * (One + Half);
	Y = (One + U2) * Half;
	Z = X - Y;
	T = Y - X;
	Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ = Z + T;
	ਜੇ (Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ != Zero) {
		S = Zero;
		BadCond(Flaw, "(X - Y) + (Y - X) is non zero!\n");
		}
	Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ = Zero;
	ਜੇ ((GMult == Yes) && (GDiv == Yes) && (GAddSub == Yes)
		&& (RMult == Rounded) && (RDiv == Rounded)
		&& (RAddSub == Rounded) && (FLOOR(RadixD2) == RadixD2)) {
		ਲਿਖੋ("Checking for sticky bit.\n");
		X = (Half + U1) * U2;
		Y = Half * U2;
		Z = One + Y;
		T = One + X;
		ਜੇ ((Z - One <= Zero) && (T - One >= U2)) {
			Z = T + Y;
			Y = Z - X;
			ਜੇ ((Z - T >= U2) && (Y - T == Zero)) {
				X = (Half + U1) * U1;
				Y = Half * U1;
				Z = One - Y;
				T = One - X;
				ਜੇ ((Z - One == Zero) && (T - F9 == Zero)) {
					Z = (Half - U1) * U1;
					T = F9 - Z;
					Q = F9 - Y;
					ਜੇ ((T - F9 == Zero) && (F9 - U1 - Q == Zero)) {
						Z = (One + U2) * OneAndHalf;
						T = (OneAndHalf + U2) - Z + U2;
						X = One + Half / Radix;
						Y = One + Radix * U2;
						Z = X * Y;
						ਜੇ (T == Zero && X + Radix * U2 - Z == Zero) {
							ਜੇ (Radix != Two) {
								X = Two + U2;
								Y = X / Two;
								ਜੇ ((Y - One == Zero)) Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ = S;
								}
							ਨਹੀਂਤਾਂ Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ = S;
							}
						}
					}
				}
			}
		}
	ਜੇ (Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ == One) ਲਿਖੋ("Sticky bit apparently used correctly.\n");
	ਨਹੀਂਤਾਂ ਲਿਖੋ("Sticky bit used incorrectly or not at all.\n");
	TstCond (Flaw, !(GMult == No || GDiv == No || GAddSub == No ||
			RMult == Other || RDiv == Other || RAddSub == Other),
		"lack(s) ਦਾ guard digits or failure(s) ਮੰਜ਼ਿਲ correctly round or chop\n\
(noted above) ਗਿਣਤੀ_2 as one flaw ਵਿੱਚ_2 the final tally ਹੇਠਾਂ");
	/*=============================================*/
	Milestone = 60;
	/*=============================================*/
	ਲਿਖੋ("\n");
	ਲਿਖੋ("Does Multiplication commute?  ");
	ਲਿਖੋ("Testing on %d random pairs.\n", NoTrials);
	Random9 = SQRT(3.0);
	Random1 = ਤੀਜਾ;
	I = 1;
	ਕਰੋ  {
		X = Random();
		Y = Random();
		Z9 = Y * X;
		Z = X * Y;
		Z9 = Z - Z9;
		I = I + 1;
		} ਜਦੋਂ ( ! ((I > NoTrials) || (Z9 != Zero)));
	ਜੇ (I == NoTrials) {
		Random1 = One + Half / Three;
		Random2 = (U2 + U1) + One;
		Z = Random1 * Random2;
		Y = Random2 * Random1;
		Z9 = (One + Half / Three) * ((U2 + U1) + One) - (One + Half /
			Three) * ((U2 + U1) + One);
		}
	ਜੇ (! ((I == NoTrials) || (Z9 == Zero)))
		BadCond(Defect, "X * Y == Y * X trial fails.\n");
	ਨਹੀਂਤਾਂ ਲਿਖੋ("     No failures found in %d integer pairs.\n", NoTrials);
	/*=============================================*/
	Milestone = 70;
	/*=============================================*/
	ਲਿਖੋ("\nRunning test of square root(x).\n");
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
	ਜੇ (J != Zero) Pause();
	ਲਿਖੋ("Testing if sqrt(X * X) == X for %d Integers X.\n", NoTrials);
	J = Zero;
	X = Two;
	Y = Radix;
	ਜੇ ((Radix != One)) ਕਰੋ  {
		X = Y;
		Y = Radix * Y;
		} ਜਦੋਂ ( ! ((Y - X >= NoTrials)));
	OneUlp = X * U2;
	I = 1;
	ਜਦੋਂ (I <= NoTrials) {
		X = X + One;
		SqXMinX (Defect);
		ਜੇ (J > Zero) ਰੋਕੋ;
		I = I + 1;
		}
	ਲਿਖੋ("Test for sqrt monotonicity.\n");
	I = - 1;
	X = BMinusU2;
	Y = Radix;
	Z = Radix + Radix * U2;
	NotMonot = False;
	Monot = False;
	ਜਦੋਂ ( ! (NotMonot || Monot)) {
		I = I + 1;
		X = SQRT(X);
		Q = SQRT(Y);
		Z = SQRT(Z);
		ਜੇ ((X > Q) || (Q > Z)) NotMonot = True;
		ਨਹੀਂਤਾਂ {
			Q = FLOOR(Q + Half);
			ਜੇ (!(I > 0 || Radix == Q * Q)) Monot = True;
			ਨਹੀਂਤਾਂ ਜੇ (I > 0) {
			ਜੇ (I > 1) Monot = True;
			ਨਹੀਂਤਾਂ {
				Y = Y * BInvrse;
				X = Y - U1;
				Z = Y + U1;
				}
			}
			ਨਹੀਂਤਾਂ {
				Y = Q;
				X = Y - U2;
				Z = Y + U2;
				}
			}
		}
	ਜੇ (Monot) ਲਿਖੋ("sqrt has passed a test for Monotonicity.\n");
	ਨਹੀਂਤਾਂ {
		BadCond(Defect, "");
		ਲਿਖੋ("sqrt(X) is non-monotonic for X near %d .\n", Y);
		}
	/*=============================================*/
	/*ਵੰਡੋ
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
	ਜੇ (SqEr > MaxSqEr) MaxSqEr = SqEr;
	SqEr = Y + U2 / Eight;
	ਜੇ (SqEr < MinSqEr) MinSqEr = SqEr;
	Y = ((SQRT(F9) - U2) - (One - U2)) / U1;
	SqEr = Y + U1 / Eight;
	ਜੇ (SqEr > MaxSqEr) MaxSqEr = SqEr;
	SqEr = (Y + One) + U1 / Eight;
	ਜੇ (SqEr < MinSqEr) MinSqEr = SqEr;
	OneUlp = U2;
	X = OneUlp;
	ਲਈ( Indx = 1; Indx <= 3; ++Indx) {
		Y = SQRT((X + U1 + X) + F9);
		Y = ((Y - U2) - ((One - U2) + X)) / OneUlp;
		Z = ((U1 - X) + F9) * Half * X * X / OneUlp;
		SqEr = (Y + Half) + Z;
		ਜੇ (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = (Y - Half) + Z;
		ਜੇ (SqEr > MaxSqEr) MaxSqEr = SqEr;
		ਜੇ (((Indx == 1) || (Indx == 3))) 
			X = OneUlp * Sign (X) * FLOOR(Eight / (Nine * SQRT(OneUlp)));
		ਨਹੀਂਤਾਂ {
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
	ਜੇ (Radix != One) {
		ਲਿਖੋ("Testing whether sqrt is rounded or chopped.\n");
		D = FLOOR(Half + POW(Radix, One + Precision - FLOOR(Precision)));
	/* ... == Radix^(1 + fract) if (Precision == Integer + fract. */
		X = D / Radix;
		Y = D / A1;
		ਜੇ ((X != FLOOR(X)) || (Y != FLOOR(Y))) {
			Anomaly = True;
			}
		ਨਹੀਂਤਾਂ {
			X = Zero;
			Z2 = X;
			Y = One;
			Y2 = Y;
			Z1 = Radix - One;
			FourD = Four * D;
			ਕਰੋ  {
				ਜੇ (Y2 > Z2) {
					Q = Radix;
					Y1 = Y;
					ਕਰੋ  {
						X1 = FABS(Q + FLOOR(Half - Q / Y1) * Y1);
						Q = Y1;
						Y1 = X1;
						} ਜਦੋਂ ( ! (X1 <= Zero));
					ਜੇ (Q <= One) {
						Z2 = Y2;
						Z = Y;
						}
					}
				Y = Y + Two;
				X = X + Eight;
				Y2 = Y2 + X;
				ਜੇ (Y2 >= FourD) Y2 = Y2 - FourD;
				} ਜਦੋਂ ( ! (Y >= D));
			X8 = FourD - Z2;
			Q = (X8 + Z * Z) / FourD;
			X8 = X8 / Eight;
			ਜੇ (Q != FLOOR(Q)) Anomaly = True;
			ਨਹੀਂਤਾਂ {
				Break = False;
				ਕਰੋ  {
					X = Z1 * Z;
					X = X - FLOOR(X / Radix) * Radix;
					ਜੇ (X == One) 
						Break = True;
					ਨਹੀਂਤਾਂ
						Z1 = Z1 - One;
					} ਜਦੋਂ ( ! (Break || (Z1 <= Zero)));
				ਜੇ ((Z1 <= Zero) && (! Break)) Anomaly = True;
				ਨਹੀਂਤਾਂ {
					ਜੇ (Z1 > RadixD2) Z1 = Z1 - Radix;
					ਕਰੋ  {
						NewD();
						} ਜਦੋਂ ( ! (U2 * D >= F9));
					ਜੇ (D * Radix - D != W - D) Anomaly = True;
					ਨਹੀਂਤਾਂ {
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
						ਜੇ (D - Z2 != W - Z2) Anomaly = True;
						ਨਹੀਂਤਾਂ {
							Y = (D - Z2) + (Z2 + (One - Z) * Half);
							X = (D - Z2) + (Z2 - Z + Q);
							SR3750();
							Y = (One + Z) * Half;
							X = Q;
							SR3750();
							ਜੇ (I == 0) Anomaly = True;
							}
						}
					}
				}
			}
		ਜੇ ((I == 0) || Anomaly) {
			BadCond(Failure, "Anomalous arithmetic with Integer < ");
			ਲਿਖੋ("Radix^Precision = %d\n", W);
			ਲਿਖੋ(" fails test whether sqrt rounds or chops.\n");
			SqRWrng = True;
			}
		}
	ਜੇ (! Anomaly) {
		ਜੇ (! ((MinSqEr < Zero) || (MaxSqEr > Zero))) {
			RSqrt = Rounded;
			ਲਿਖੋ("Square root appears to be correctly rounded.\n");
			}
		ਨਹੀਂਤਾਂ  {
			ਜੇ ((MaxSqEr + U2 > U2 - Half) || (MinSqEr > Half)
				|| (MinSqEr + Radix < Half)) SqRWrng = True;
			ਨਹੀਂਤਾਂ {
				RSqrt = Chopped;
				ਲਿਖੋ("Square root appears to be chopped.\n");
				}
			}
		}
	ਜੇ (SqRWrng) {
		ਲਿਖੋ("Square root is neither chopped nor correctly rounded.\n");
		ਲਿਖੋ("Observed errors run from %d ", MinSqEr - Half);
		ਲਿਖੋ("to %d ulps.\n", Half + MaxSqEr);
		TstCond (Serious, MaxSqEr - MinSqEr < Radix * Radix,
			"sqrt gets too many last digits wrong");
		}
	/*=============================================*/
	Milestone = 90;
	/*=============================================*/
	Pause();
	ਲਿਖੋ("Testing powers Z^i for small Integers Z and i.\n");
	N = 0;
	/* ... test powers of zero. */
	I = 0;
	Z = -Zero;
	M = 3;
	Break = False;
	ਕਰੋ  {
		X = One;
		SR3980();
		ਜੇ (I <= 10) {
			I = 1023;
			SR3980();
			}
		ਜੇ (Z == MinusOne) Break = True;
		ਨਹੀਂਤਾਂ {
			Z = MinusOne;
			/* .. if(-1)^N is invalid, replace MinusOne by One. */
			I = - 4;
			}
		} ਜਦੋਂ ( ! Break);
	PrintIfNPositive();
	N1 = N;
	N = 0;
	Z = A1;
	M = (ਪੂਰਨ)FLOOR(Two * LOG(W) / LOG(A1));
	Break = False;
	ਕਰੋ  {
		X = Z;
		I = 1;
		SR3980();
		ਜੇ (Z == AInvrse) Break = True;
		ਨਹੀਂਤਾਂ Z = AInvrse;
		} ਜਦੋਂ ( ! (Break));
	/*=============================================*/
		Milestone = 100;
	/*=============================================*/
	/*  Powers of Radix have been tested, */
	/*         next try a few primes     */
	M = NoTrials;
	Z = Three;
	ਕਰੋ  {
		X = Z;
		I = 1;
		SR3980();
		ਕਰੋ  {
			Z = Z + Two;
			} ਜਦੋਂ ( Three * FLOOR(Z / Three) == Z );
		} ਜਦੋਂ ( Z < Eight * Three );
	ਜੇ (N > 0) {
		ਲਿਖੋ("Errors like this may invalidate financial calculations\n");
		ਲਿਖੋ("\tinvolving interest rates.\n");
		}
	PrintIfNPositive();
	N += N1;
	ਜੇ (N == 0) ਲਿਖੋ("... no discrepancies found.\n");
	ਜੇ (N > 0) Pause();
	ਨਹੀਂਤਾਂ ਲਿਖੋ("\n");
	/*=============================================*/
	/*ਵੰਡੋ
	}
#include "paranoia.h"
void part6(VOID){
*/
	Milestone = 110;
	/*=============================================*/
	ਲਿਖੋ("Seeking Underflow thresholds UfThold and E0.\n");
	D = U1;
	ਜੇ (Precision != FLOOR(Precision)) {
		D = BInvrse;
		X = Precision;
		ਕਰੋ  {
			D = D * BInvrse;
			X = X - One;
			} ਜਦੋਂ ( X > Zero);
		}
	Y = One;
	Z = D;
	/* ... D is power of 1/Radix < 1. */
	ਕਰੋ  {
		C = Y;
		Y = Z;
		Z = Y * Y;
		} ਜਦੋਂ ((Y > Z) && (Z + Z > Z));
	Y = C;
	Z = Y * D;
	ਕਰੋ  {
		C = Y;
		Y = Z;
		Z = Y * D;
		} ਜਦੋਂ ((Y > Z) && (Z + Z > Z));
	ਜੇ (Radix < Two) HInvrse = Two;
	ਨਹੀਂਤਾਂ HInvrse = Radix;
	H = One / HInvrse;
	/* ... 1/HInvrse == H == Min(1/Radix, 1/2) */
	CInvrse = One / C;
	E0 = C;
	Z = E0 * H;
	/* ...1/Radix^(BIG Integer) << 1 << CInvrse == 1/C */
	ਕਰੋ  {
		Y = E0;
		E0 = Z;
		Z = E0 * H;
		} ਜਦੋਂ ((E0 > Z) && (Z + Z > Z));
	UfThold = E0;
	E1 = Zero;
	Q = Zero;
	E9 = U2;
	S = One + E9;
	D = C * S;
	ਜੇ (D <= C) {
		E9 = Radix * U2;
		S = One + E9;
		D = C * S;
		ਜੇ (D <= C) {
			BadCond(Failure, "multiplication gets too many last digits wrong.\n");
			Underflow = E0;
			Y1 = Zero;
			PseudoZero = Z;
			Pause();
			}
		}
	ਨਹੀਂਤਾਂ {
		Underflow = D;
		PseudoZero = Underflow * H;
		UfThold = Zero;
		ਕਰੋ  {
			Y1 = Underflow;
			Underflow = PseudoZero;
			ਜੇ (E1 + E1 <= E1) {
				Y2 = Underflow * HInvrse;
				E1 = FABS(Y1 - Y2);
				Q = Y1;
				ਜੇ ((UfThold == Zero) && (Y1 != Y2)) UfThold = Y1;
				}
			PseudoZero = PseudoZero * H;
			} ਜਦੋਂ ((Underflow > PseudoZero)
				&& (PseudoZero + PseudoZero > PseudoZero));
		}
	/* Comment line 4530 .. 4560 */
	ਜੇ (PseudoZero != Zero) {
		ਲਿਖੋ("\n");
		Z = PseudoZero;
	/* ... Test PseudoZero for "phoney- zero" violates */
	/* ... PseudoZero < Underflow or PseudoZero < PseudoZero + PseudoZero
		   ... */
		ਜੇ (PseudoZero <= Zero) {
			BadCond(Failure, "Positive expressions can underflow to an\n");
			ਲਿਖੋ("allegedly negative value\n");
			ਲਿਖੋ("PseudoZero that prints out as: %d .\n", PseudoZero);
			X = - PseudoZero;
			ਜੇ (X <= Zero) {
				ਲਿਖੋ("But -PseudoZero, which should be\n");
				ਲਿਖੋ("positive, isn't; it prints out as  %d .\n", X);
				}
			}
		ਨਹੀਂਤਾਂ {
			BadCond(Flaw, "Underflow can stick at an allegedly positive\n");
			ਲਿਖੋ("value PseudoZero that prints out as %d .\n", PseudoZero);
			}
		TstPtUf();
		}
	/*=============================================*/
	Milestone = 120;
	/*=============================================*/
	ਜੇ (CInvrse * Y > CInvrse * Y1) {
		S = H * S;
		E0 = Underflow;
		}
	ਜੇ (! ((E1 == Zero) || (E1 == E0))) {
		BadCond(Defect, "");
		ਜੇ (E1 < E0) {
			ਲਿਖੋ("Products underflow at a higher");
			ਲਿਖੋ(" threshold than differences.\n");
			ਜੇ (PseudoZero == Zero) 
			E0 = E1;
			}
		ਨਹੀਂਤਾਂ {
			ਲਿਖੋ("Difference underflows at a higher");
			ਲਿਖੋ(" threshold than products.\n");
			}
		}
	ਲਿਖੋ("Smallest strictly positive number found is E0 = %d .\n", E0);
	Z = E0;
	TstPtUf();
	Underflow = E0;
	ਜੇ (N == 1) Underflow = Y;
	I = 4;
	ਜੇ (E1 == Zero) I = 3;
	ਜੇ (UfThold == Zero) I = I - 2;
	UfNGrad = True;
	ਚੋਣ (I)  {
		ਹਾਲਤ	1:
		UfThold = Underflow;
		ਜੇ ((CInvrse * Q) != ((CInvrse * Y) * S)) {
			UfThold = Y;
			BadCond(Failure, "Either accuracy deteriorates as numbers\n");
			ਲਿਖੋ("approach a threshold = %d\n", UfThold);;
			ਲਿਖੋ(" coming down from %d\n", C);
			ਲਿਖੋ(" or else multiplication gets too many last digits wrong.\n");
			}
		Pause();
		ਰੋਕੋ;
	
		ਹਾਲਤ	2:
		BadCond(Failure, "Underflow confuses Comparison, which alleges that\n");
		ਲਿਖੋ("Q == Y while denying that |Q - Y| == 0; these values\n");
		ਲਿਖੋ("print out as Q = %d, Y = %016x .\n", Q, Y2);
		ਲਿਖੋ ("|Q - Y| = %d .\n" , FABS(Q - Y2));
		UfThold = Q;
		ਰੋਕੋ;
	
		ਹਾਲਤ	3:
		X = X;
		ਰੋਕੋ;
	
		ਹਾਲਤ	4:
		ਜੇ ((Q == UfThold) && (E1 == E0)
			&& (FABS( UfThold - E1 / E9) <= E1)) {
			UfNGrad = False;
			ਲਿਖੋ("Underflow is gradual; it incurs Absolute Error =\n");
			ਲਿਖੋ("(roundoff in UfThold) < E0.\n");
			Y = E0 * CInvrse;
			Y = Y * (OneAndHalf + U2);
			X = CInvrse * (One + U2);
			Y = Y / X;
			IEEE = (Y == E0);
			}
		}
	ਜੇ (UfNGrad) {
		ਲਿਖੋ("\n");
		sigsave = sigfpe;
		ਜੇ (setjmp(ovfl_buf)) {
			ਲਿਖੋ("Underflow / UfThold failed!\n");
			R = H + H;
			}
		ਨਹੀਂਤਾਂ R = SQRT(Underflow / UfThold);
		sigsave = 0;
		ਜੇ (R <= H) {
			Z = R * UfThold;
			X = Z * (One + R * H * (One + H));
			}
		ਨਹੀਂਤਾਂ {
			Z = UfThold;
			X = Z * (One + H * H * (One + H));
			}
		ਜੇ (! ((X == Z) || (X - Z != Zero))) {
			BadCond(Flaw, "");
			ਲਿਖੋ("X = %d\n\tis not equal to Z = %016x .\n", X, Z);
			Z9 = X - Z;
			ਲਿਖੋ("yet X - Z yields %d .\n", Z9);
			ਲਿਖੋ("    Should this NOT signal Underflow, ");
			ਲਿਖੋ("this is a SERIOUS DEFECT\nthat causes ");
			ਲਿਖੋ("confusion when innocent statements like\n");;
			ਲਿਖੋ("    if (X == Z)  ...  else");
			ਲਿਖੋ("  ... (f(X) - f(Z)) / (X - Z) ...\n");
			ਲਿਖੋ("encounter Division by Zero although actually\n");
			sigsave = sigfpe;
			ਜੇ (setjmp(ovfl_buf)) ਲਿਖੋ("X / Z fails!\n");
			ਨਹੀਂਤਾਂ ਲਿਖੋ("X / Z = 1 + %d .\n", (X / Z - Half) - Half);
			sigsave = 0;
			}
		}
	ਲਿਖੋ("The Underflow threshold is %d, %s\n", UfThold,
		   " below which");
	ਲਿਖੋ("calculation may suffer larger Relative error than ");
	ਲਿਖੋ("merely roundoff.\n");
	Y2 = U1 * U1;
	Y = Y2 * Y2;
	Y2 = Y * U1;
	ਜੇ (Y2 <= UfThold) {
		ਜੇ (Y > E0) {
			BadCond(Defect, "");
			I = 5;
			}
		ਨਹੀਂਤਾਂ {
			BadCond(Serious, "");
			I = 4;
			}
		ਲਿਖੋ("Range is too narrow; U1^%d Underflows.\n", I);
		}
	/*=============================================*/
	/*ਵੰਡੋ
	}
#include "paranoia.h"
void part7(VOID){
*/
	Milestone = 130;
	/*=============================================*/
	Y = - FLOOR(Half - TwoForty * LOG(UfThold) / LOG(HInvrse)) / TwoForty;
	Y2 = Y + Y;
	ਲਿਖੋ("Since underflow occurs below the threshold\n");
	ਲਿਖੋ("UfThold = (%d) ^ (%016x)\nonly underflow ", HInvrse, Y);
	ਲਿਖੋ("should afflict the expression\n\t(%d) ^ (%016x);\n",
		HInvrse, Y2);
	ਲਿਖੋ("actually calculating yields:");
	ਜੇ (setjmp(ovfl_buf)) {
		sigsave = 0;
		BadCond(Serious, "trap on underflow.\n");
		}
	ਨਹੀਂਤਾਂ {
		sigsave = sigfpe;
		V9 = POW(HInvrse, Y2);
		sigsave = 0;
		ਲਿਖੋ(" %d .\n", V9);
		ਜੇ (! ((V9 >= Zero) && (V9 <= (Radix + Radix + E9) * UfThold))) {
			BadCond(Serious, "this is not between 0 and underflow\n");
		ਲਿਖੋ("   threshold = %d .\n", UfThold);
		}
		ਨਹੀਂਤਾਂ ਜੇ (! (V9 > UfThold * (One + E9)))
			ਲਿਖੋ("This computed value is O.K.\n");
		ਨਹੀਂਤਾਂ {
			BadCond(Defect, "this is not between 0 and underflow\n");
			ਲਿਖੋ("   threshold = %d .\n", UfThold);
			}
		}
	/*=============================================*/
	Milestone = 140;
	/*=============================================*/
	ਲਿਖੋ("\n");
	/* ...calculate Exp2 == exp(2) == 7.389056099... */
	X = Zero;
	I = 2;
	Y = Two * Three;
	Q = Zero;
	N = 0;
	ਕਰੋ  {
		Z = X;
		I = I + 1;
		Y = Y / (I + I);
		R = Y + Q;
		X = Z + R;
		Q = (Z - X) + R;
		} ਜਦੋਂ(X > Z);
	Z = (OneAndHalf + One / Eight) + X / (OneAndHalf * ThirtyTwo);
	X = Z * Z;
	Exp2 = X * X;
	X = F9;
	Y = X - U1;
	ਲਿਖੋ("Testing X^((X + 1) / (X - 1)) vs. exp(2) = %d as X -> 1.\n",
		Exp2);
	ਲਈ(I = 1;;) {
		Z = X - BInvrse;
		Z = (X + One) / (Z - (One - BInvrse));
		Q = POW(X, Z) - Exp2;
		ਜੇ (FABS(Q) > TwoForty * U2) {
			N = 1;
	 		V9 = (X - BInvrse) - (One - BInvrse);
			BadCond(Defect, "Calculated");
			ਲਿਖੋ(" %d for\n", POW(X,Z));
			ਲਿਖੋ("\t(1 + (%d) ^ (%016x);\n", V9, Z);
			ਲਿਖੋ("\tdiffers from correct value by %d .\n", Q);
			ਲਿਖੋ("\tThis much error may spoil financial\n");
			ਲਿਖੋ("\tcalculations involving tiny interest rates.\n");
			ਰੋਕੋ;
			}
		ਨਹੀਂਤਾਂ {
			Z = (Y - X) * Two + Y;
			X = Y;
			Y = Z;
			Z = One + (X - F9)*(X - F9);
			ਜੇ (Z > One && I < NoTrials) I++;
			ਨਹੀਂਤਾਂ  {
				ਜੇ (X > One) {
					ਜੇ (N == 0)
					   ਲਿਖੋ("Accuracy seems adequate.\n");
					ਰੋਕੋ;
					}
				ਨਹੀਂਤਾਂ {
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
	ਲਿਖੋ("Testing powers Z^Q at four nearly extreme values.\n");
	N = 0;
	Z = A1;
	Q = FLOOR(Half - LOG(C) / LOG(A1));
	Break = False;
	ਕਰੋ  {
		X = CInvrse;
		Y = POW(Z, Q);
		IsYeqX();
		Q = - Q;
		X = C;
		Y = POW(Z, Q);
		IsYeqX();
		ਜੇ (Z < One) Break = True;
		ਨਹੀਂਤਾਂ Z = AInvrse;
		} ਜਦੋਂ ( ! (Break));
	PrintIfNPositive();
	ਜੇ (N == 0) ਲਿਖੋ(" ... no discrepancies found.\n");
	ਲਿਖੋ("\n");
	
	/*=============================================*/
	Milestone = 160;
	/*=============================================*/
	Pause();
	ਲਿਖੋ("Searching for Overflow threshold:\n");
	ਲਿਖੋ("This may generate an error.\n");
	Y = - CInvrse;
	V9 = HInvrse * Y;
	sigsave = sigfpe;
	ਜੇ (setjmp(ovfl_buf)) { I = 0; V9 = Y; ਜਾਓ ਉਛਾਲ; }
	ਕਰੋ {
		V = Y;
		Y = V9;
		V9 = HInvrse * Y;
		} ਜਦੋਂ(V9 < Y);
	I = 1;
ਉਛਾਲ:
	sigsave = 0;
	Z = V9;
	ਲਿਖੋ("Can `Z = -Y' overflow?\n");
	ਲਿਖੋ("Trying it on Y = %d .\n", Y);
	V9 = - Y;
	V0 = V9;
	ਜੇ (V - Y == V + V0) ਲਿਖੋ("Seems O.K.\n");
	ਨਹੀਂਤਾਂ {
		ਲਿਖੋ("finds a ");
		BadCond(Flaw, "-(-Y) differs from Y.\n");
		}
	ਜੇ (Z != Y) {
		BadCond(Serious, "");
		ਲਿਖੋ("overflow past %d\n\tshrinks to %016x .\n", Y, Z);
		}
	ਜੇ (I) {
		Y = V * (HInvrse * U2 - HInvrse);
		Z = Y + ((One - HInvrse) * U2) * V;
		ਜੇ (Z < V0) Y = Z;
		ਜੇ (Y < V0) V = Y;
		ਜੇ (V0 - V < V0) V = V0;
		}
	ਨਹੀਂਤਾਂ {
		V = Y * (HInvrse * U2 - HInvrse);
		V = V + ((One - HInvrse) * U2) * Y;
		}
	ਲਿਖੋ("Overflow threshold is V  = %d .\n", V);
	ਜੇ (I) ਲਿਖੋ("Overflow saturates at V0 = %d .\n", V0);
	ਨਹੀਂਤਾਂ ਲਿਖੋ("There is no saturation ਮੁੱਲ because \
the system traps on ਉਛਾਲ.\n");
	V9 = V * One;
	ਲਿਖੋ("No Overflow should be signaled for V * 1 = %d\n", V9);
	V9 = V / One;
	ਲਿਖੋ("                           nor for V / 1 = %d .\n", V9);
	ਲਿਖੋ("Any overflow signal separating this * from the one\n");
	ਲਿਖੋ("above is a DEFECT.\n");
	/*=============================================*/
	Milestone = 170;
	/*=============================================*/
	ਜੇ (!(-V < V && -V0 < V0 && -UfThold < V && UfThold < V)) {
		BadCond(Failure, "Comparisons involving ");
		ਲਿਖੋ("+-%d, +-%016x\nand +-%016x are confused by Overflow.",
			V, V0, UfThold);
		}
	/*=============================================*/
	Milestone = 175;
	/*=============================================*/
	ਲਿਖੋ("\n");
	ਲਈ(Indx = 1; Indx <= 3; ++Indx) {
		ਚੋਣ (Indx)  {
			ਹਾਲਤ 1: Z = UfThold; ਰੋਕੋ;
			ਹਾਲਤ 2: Z = E0; ਰੋਕੋ;
			ਹਾਲਤ 3: Z = PseudoZero; ਰੋਕੋ;
			}
		ਜੇ (Z != Zero) {
			V9 = SQRT(Z);
			Y = V9 * V9;
			ਜੇ (Y / (One - Radix * E9) < Z
			   || Y > (One + Radix * E9) * Z) { /* dgh: + E9 --> * E9 */
				ਜੇ (V9 > U1) BadCond(Serious, "");
				ਨਹੀਂਤਾਂ BadCond(Defect, "");
				ਲਿਖੋ("Comparison alleges that what prints as Z = %d\n", Z);
				ਲਿਖੋ(" is too far from sqrt(Z) ^ 2 = %d .\n", Y);
				}
			}
		}
	/*=============================================*/
	Milestone = 180;
	/*=============================================*/
	ਲਈ(Indx = 1; Indx <= 2; ++Indx) {
		ਜੇ (Indx == 1) Z = V;
		ਨਹੀਂਤਾਂ Z = V0;
		V9 = SQRT(Z);
		X = (One - Radix * E9) * V9;
		V9 = V9 * X;
		ਜੇ (((V9 < (One - Two * Radix * E9) * Z) || (V9 > Z))) {
			Y = V9;
			ਜੇ (X < W) BadCond(Serious, "");
			ਨਹੀਂਤਾਂ BadCond(Defect, "");
			ਲਿਖੋ("Comparison alleges that Z = %d\n", Z);
			ਲਿਖੋ(" is too far from sqrt(Z) ^ 2 (%d) .\n", Y);
			}
		}
	/*=============================================*/
	/*ਵੰਡੋ
	}
#include "paranoia.h"
int part8(VOID){
*/
	Milestone = 190;
	/*=============================================*/
	Pause();
	X = UfThold * V;
	Y = Radix * Radix;
	ਜੇ (X*Y < One || X > Y) {
		ਜੇ (X * Y < U1 || X > Y/U1) BadCond(Defect, "Badly");
		ਨਹੀਂਤਾਂ BadCond(Flaw, "");
			
		ਲਿਖੋ(" unbalanced range; UfThold * V = %d\n\t%s\n",
			X, "is too far from 1.\n");
		}
	/*=============================================*/
	Milestone = 200;
	/*=============================================*/
	ਲਈ (Indx = 1; Indx <= 5; ++Indx)  {
		X = F9;
		ਚੋਣ (Indx)  {
			ਹਾਲਤ 2: X = One + U2; ਰੋਕੋ;
			ਹਾਲਤ 3: X = V; ਰੋਕੋ;
			ਹਾਲਤ 4: X = UfThold; ਰੋਕੋ;
			ਹਾਲਤ 5: X = Radix;
			}
		Y = X;
		sigsave = sigfpe;
		ਜੇ (setjmp(ovfl_buf))
			ਲਿਖੋ("  X / X  traps when X = %d\n", X);
		ਨਹੀਂਤਾਂ {
			V9 = (Y / X - Half) - Half;
			ਜੇ (V9 == Zero) ਜਾਰੀ;
			ਜੇ (V9 == - U1 && Indx < 5) BadCond(Flaw, "");
			ਨਹੀਂਤਾਂ BadCond(Serious, "");
			ਲਿਖੋ("  X / X differs from 1 when X = %d\n", X);
			ਲਿਖੋ("  instead, X / X - 1/2 - 1/2 = %d .\n", V9);
			}
		sigsave = 0;
		}
	/*=============================================*/
	Milestone = 210;
	/*=============================================*/
	MyZero = Zero;
	ਲਿਖੋ("\n");
	ਲਿਖੋ("What message and/or values does Division by Zero produce?\n") ;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NOPAUSE
	ਲਿਖੋ("This can interupt your program.  You can ");
	ਲਿਖੋ("skip this part if you wish.\n");
	ਲਿਖੋ("Do you wish to compute 1 / 0? ");
	fflush(stdout);
	ਪਠ (KEYBOARD, ch, 8);
	ਜੇ ((ch[0] == 'Y') || (ch[0] == 'y')) {
#ਜੇ_ਅੰਤ
		sigsave = sigfpe;
		ਲਿਖੋ("    Trying to compute 1 / 0 produces ...");
		ਜੇ (!setjmp(ovfl_buf)) ਲਿਖੋ("  %d .\n", One / MyZero);
		sigsave = 0;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NOPAUSE
		}
	ਨਹੀਂਤਾਂ ਲਿਖੋ("O.K.\n");
	ਲਿਖੋ("\nDo you wish to compute 0 / 0? ");
	fflush(stdout);
	ਪਠ (KEYBOARD, ch, 80);
	ਜੇ ((ch[0] == 'Y') || (ch[0] == 'y')) {
#ਜੇ_ਅੰਤ
		sigsave = sigfpe;
		ਲਿਖੋ("\n    Trying to compute 0 / 0 produces ...");
		ਜੇ (!setjmp(ovfl_buf)) ਲਿਖੋ("  %d .\n", Zero / MyZero);
		sigsave = 0;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NOPAUSE
		}
	ਨਹੀਂਤਾਂ ਲਿਖੋ("O.K.\n");
#ਜੇ_ਅੰਤ
	/*=============================================*/
	Milestone = 220;
	/*=============================================*/
	Pause();
	ਲਿਖੋ("\n");
	{
		ਸਥਿਰ ਅੱਖਰ *ਸੁਨੇਹਾ_2[] = {
			"FAILUREs  encountered =",
			"SERIOUS DEFECTs  discovered =",
			"DEFECTs  discovered =",
			"FLAWs  discovered =" };
		ਪੂਰਨ i;
		ਲਈ(i = 0; i < 4; i++) ਜੇ (ErrCnt[i])
			ਲਿਖੋ("The number of  %-29s %d.\n",
				ਸੁਨੇਹਾ_2[i], ErrCnt[i]);
		}
	ਲਿਖੋ("\n");
	ਜੇ ((ErrCnt[Failure] + ErrCnt[Serious] + ErrCnt[Defect]
			+ ErrCnt[Flaw]) > 0) {
		ਜੇ ((ErrCnt[Failure] + ErrCnt[Serious] + ErrCnt[
			Defect] == 0) && (ErrCnt[Flaw] > 0)) {
			ਲਿਖੋ("The arithmetic diagnosed seems ");
			ਲਿਖੋ("Satisfactory though flawed.\n");
			}
		ਜੇ ((ErrCnt[Failure] + ErrCnt[Serious] == 0)
			&& ( ErrCnt[Defect] > 0)) {
			ਲਿਖੋ("The arithmetic diagnosed may be Acceptable\n");
			ਲਿਖੋ("despite inconvenient Defects.\n");
			}
		ਜੇ ((ErrCnt[Failure] + ErrCnt[Serious]) > 0) {
			ਲਿਖੋ("The arithmetic diagnosed has ");
			ਲਿਖੋ("unacceptable Serious Defects.\n");
			}
		ਜੇ (ErrCnt[Failure] > 0) {
			ਲਿਖੋ("Potentially fatal FAILURE may have spoiled this");
			ਲਿਖੋ(" program's subsequent diagnoses.\n");
			}
		}
	ਨਹੀਂਤਾਂ {
		ਲਿਖੋ("No failures, defects nor flaws have been discovered.\n");
		ਜੇ (! ((RMult == Rounded) && (RDiv == Rounded)
			&& (RAddSub == Rounded) && (RSqrt == Rounded))) 
			ਲਿਖੋ("The arithmetic diagnosed seems Satisfactory.\n");
		ਨਹੀਂਤਾਂ {
			ਜੇ (Sticky_ਦੋਆਧਾਰੀ_ਅੰਕ >= One &&
				(Radix - Two) * (Radix - Nine - One) == Zero) {
				ਲਿਖੋ("Rounding appears to conform to ");
				ਲਿਖੋ("the proposed IEEE standard P");
				ਜੇ ((Radix == Two) &&
					 ((Precision - Four * Three * Two) *
					  ( Precision - TwentySeven -
					   TwentySeven + One) == Zero)) 
					ਲਿਖੋ("754");
				ਨਹੀਂਤਾਂ ਲਿਖੋ("854");
				ਜੇ (IEEE) ਲਿਖੋ(".\n");
				ਨਹੀਂਤਾਂ {
					ਲਿਖੋ(",\nexcept for possibly Double Rounding");
					ਲਿਖੋ(" during Gradual Underflow.\n");
					}
				}
			ਲਿਖੋ("The arithmetic diagnosed appears to be Excellent!\n");
			}
		}
	ਜੇ (fpecount)
		ਲਿਖੋ("\nA total of %d floating point exceptions were registered.\n",
			fpecount);
	ਲਿਖੋ("END OF TEST $\n");
  __asm__("ebreak");
	//return 0;
	}

/*SPLIT subs.c
#include "paranoia.h"
*/

 FLOAT
Sign (FP X)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KR_ਸਿਰਲੇਖਾਂ
FLOAT X;
#ਜੇ_ਅੰਤ
{ ਵਾਪਸ X >= 0. ? 1.0 : -1.0; }

 ਖਾਲੀ
Pause(VOID)
{
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NOPAUSE
	ਅੱਖਰ ch[8];

	ਲਿਖੋ("\nTo continue, press RETURN");
	fflush(stdout);
	ਪਠ(KEYBOARD, ch, 8);
#ਜੇ_ਅੰਤ
	ਲਿਖੋ("\nDiagnosis resumes after milestone Number %d", Milestone);
	ਲਿਖੋ("          Page: %d\n\n", ਪੰਨਾ_No);
	++Milestone;
	++ਪੰਨਾ_No;
	}

 ਖਾਲੀ
TstCond (INT K, INT Valid, CHARP T)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KR_ਸਿਰਲੇਖਾਂ
ਪੂਰਨ K, Valid;
ਅੱਖਰ *T;
#ਜੇ_ਅੰਤ
{ ਜੇ (! Valid) { BadCond(K,T); ਲਿਖੋ(".\n"); } }

 ਖਾਲੀ
BadCond(INT K, CHARP T)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KR_ਸਿਰਲੇਖਾਂ
ਪੂਰਨ K;
ਅੱਖਰ *T;
#ਜੇ_ਅੰਤ
{
	ਸਥਿਰ ਅੱਖਰ *ਸੁਨੇਹਾ_2[] = { "FAILURE", "SERIOUS DEFECT", "DEFECT", "FLAW" };

	ErrCnt [K] = ErrCnt [K] + 1;
	ਲਿਖੋ("%s:  %s", ਸੁਨੇਹਾ_2[K], T);
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
	ਵਾਪਸ(Random1);
	}

 ਖਾਲੀ
SqXMinX (INT Err_ਕਿਸਮ)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KR_ਸਿਰਲੇਖਾਂ
ਪੂਰਨ Err_ਕਿਸਮ;
#ਜੇ_ਅੰਤ
{
	FLOAT XA, XB;
	
	XB = X * BInvrse;
	XA = X - XB;
	SqEr = ((SQRT(X * X) - XB) - XA) / OneUlp;
	ਜੇ (SqEr != Zero) {
		ਜੇ (SqEr < MinSqEr) MinSqEr = SqEr;
		ਜੇ (SqEr > MaxSqEr) MaxSqEr = SqEr;
		J = J + 1.0;
		BadCond(Err_ਕਿਸਮ, "\n");
		ਲਿਖੋ("sqrt( %d) - %016x  = %016x\n", X * X, X, OneUlp * SqEr);
		ਲਿਖੋ("\tinstead of correct value 0 .\n");
		}
	}

 ਖਾਲੀ
NewD(VOID)
{
	X = Z1 * Q;
	X = FLOOR(Half - X / Radix) * Radix + X;
	Q = (Q - X * Z) / Radix + X * X * (D / Radix);
	Z = Z - Two * X * D;
	ਜੇ (Z <= Zero) {
		Z = - Z;
		Z1 = - Z1;
		}
	D = Radix * D;
	}

 ਖਾਲੀ
SR3750(VOID)
{
	ਜੇ (! ((X - Radix < Z2 - Radix) || (X - Z2 > W - Z2))) {
		I = I + 1;
		X2 = SQRT(X * D);
		Y2 = (X2 - Z2) - (Y - Z2);
		X2 = X8 / (Y - Half);
		X2 = X2 - Half * X2 * X2;
		SqEr = (Y2 + Half) + (Half - X2);
		ਜੇ (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = Y2 - X2;
		ਜੇ (SqEr > MaxSqEr) MaxSqEr = SqEr;
		}
	}

 ਖਾਲੀ
IsYeqX(VOID)
{
	ਜੇ (Y != X) {
		ਜੇ (N <= 0) {
			ਜੇ (Z == Zero && Q <= Zero)
				ਲਿਖੋ("WARNING:  computing\n");
			ਨਹੀਂਤਾਂ BadCond(Defect, "computing\n");
			ਲਿਖੋ("\t(%d) ^ (%016x)\n", Z, Q);
			ਲਿਖੋ("\tyielded %d;\n", Y);
			ਲਿਖੋ("\twhich compared unequal to correct %d ;\n",
				X);
			ਲਿਖੋ("\t\tthey differ by %d .\n", Y - X);
			}
		N = N + 1; /* ... count discrepancies. */
		}
	}

 ਖਾਲੀ
SR3980(VOID)
{
	ਕਰੋ {
		Q = (FLOAT) I;
		Y = POW(Z, Q);
		IsYeqX();
		ਜੇ (++I > M) ਰੋਕੋ;
		X = Z * X;
		} ਜਦੋਂ ( X < W );
	}

 ਖਾਲੀ
PrintIfNPositive(VOID)
{
	ਜੇ (N > 0) ਲਿਖੋ("Similar discrepancies have occurred %d times.\n", N);
	}

 ਖਾਲੀ
TstPtUf(VOID)
{
	N = 0;
	ਜੇ (Z != Zero) {
		ਲਿਖੋ("Since comparison denies Z = 0, evaluating ");
		ਲਿਖੋ("(Z + Z) / Z should be safe.\n");
		sigsave = sigfpe;
		ਜੇ (setjmp(ovfl_buf)) ਜਾਓ very_serious;
		Q9 = (Z + Z) / Z;
		ਲਿਖੋ("What the machine gets for (Z + Z) / Z is  %d .\n",
			Q9);
		ਜੇ (FABS(Q9 - Two) < Radix * U2) {
			ਲਿਖੋ("This is O.K., provided Over/Underflow");
			ਲਿਖੋ(" has NOT just been signaled.\n");
			}
		ਨਹੀਂਤਾਂ {
			ਜੇ ((Q9 < One) || (Q9 > Two)) {
very_serious:
				N = 1;
				ErrCnt [Serious] = ErrCnt [Serious] + 1;
				ਲਿਖੋ("This is a VERY SERIOUS DEFECT!\n");
				}
			ਨਹੀਂਤਾਂ {
				N = 1;
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				ਲਿਖੋ("This is a DEFECT!\n");
				}
			}
		sigsave = 0;
		V9 = Z * One;
		Random1 = V9;
		V9 = One * Z;
		Random2 = V9;
		V9 = Z / One;
		ਜੇ ((Z == Random1) && (Z == Random2) && (Z == V9)) {
			ਜੇ (N > 0) Pause();
			}
		ਨਹੀਂਤਾਂ {
			N = 1;
			BadCond(Defect, "What prints as Z = ");
			ਲਿਖੋ("%d\n\tcompares different from  ", Z);
			ਜੇ (Z != Random1) ਲਿਖੋ("Z * 1 = %d ", Random1);
			ਜੇ (! ((Z == Random2)
				|| (Random2 == Random1)))
				ਲਿਖੋ("1 * Z == %d\n", Random2);
			ਜੇ (! (Z == V9)) ਲਿਖੋ("Z / 1 = %d\n", V9);
			ਜੇ (Random2 != Random1) {
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				BadCond(Defect, "Multiplication does not commute!\n");
				ਲਿਖੋ("\tComparison alleges that 1 * Z = %d\n",
					Random2);
				ਲਿਖੋ("\tdiffers from Z * 1 = %d\n", Random1);
				}
			Pause();
			}
		}
	}

 ਖਾਲੀ
notify(CHARP s)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KR_ਸਿਰਲੇਖਾਂ
 ਅੱਖਰ *s;
#ਜੇ_ਅੰਤ
{
	ਲਿਖੋ("%s test appears to be inconsistent...\n", s);
	ਲਿਖੋ("   PLEASE NOTIFY KARPINKSI!\n");
	}

/*SPLIT msgs.c
#include "paranoia.h"
*/

 ਖਾਲੀ
msglist(CHARPP s)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KR_ਸਿਰਲੇਖਾਂ
ਅੱਖਰ **s;
#ਜੇ_ਅੰਤ
{ ਜਦੋਂ(*s) ਲਿਖੋ("%s\n", *s++); }

 ਖਾਲੀ
Instructions(VOID)
{
  ਸਥਿਰ ਅੱਖਰ *instr[] = {
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

 ਖਾਲੀ
Heading(VOID)
{
  ਸਥਿਰ ਅੱਖਰ *ਸਿਰ[] = {
	"Users are invited to help debug and augment this program so it will",
	"cope with unanticipated and newly uncovered arithmetic pathologies.\n",
	"Please send suggestions and interesting results to",
	"\tRichard Karpinski",
	"\tComputer Center U-76",
	"\tUniversity of California",
	"\tSan Francisco, CA 94143-0704, USA\n",
	"In doing so, please include the following information:",
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ Single
	"\tPrecision:\tsingle;",
#ਨਹੀਂਤਾਂ
	"\tPrecision:\tdouble;",
#ਜੇ_ਅੰਤ
	"\tVersion:\t10 February 1989;",
	"\tComputer:\n",
	"\tCompiler:\n",
	"\tOptimization level:\n",
	"\tOther relevant compiler options:",
	0};

	msglist(ਸਿਰ);
	}

 ਖਾਲੀ
Characteristics(VOID)
{
	ਸਥਿਰ ਅੱਖਰ *chars[] = {
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

 ਖਾਲੀ
History(VOID)
{ /* History */
 /* Converted from Brian Wichmann's Pascal version to C by Thos Sumner,
	with further massaging by David M. Gay. */

  ਸਥਿਰ ਅੱਖਰ *hist[] = {
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
