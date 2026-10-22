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

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ವ್ಯಾಖ್ಯಾನಿಸು NOSIGNAL
#ವ್ಯಾಖ್ಯಾನಿಸು NOPAUSE
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NOSIGNAL
#ಅನ್ತರ್ಭಾವ <signal.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <setjmp.h>
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ Single
#ವ್ಯಾಖ್ಯಾನಿಸು FLOAT ದಶಮಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು FABS(x) (ದಶಮಾಂಶ)fabs((ದ್ವಿಗುಣ)(x))
#ವ್ಯಾಖ್ಯಾನಿಸು FLOOR(x) (ದಶಮಾಂಶ)floor((ದ್ವಿಗುಣ)(x))
#ವ್ಯಾಖ್ಯಾನಿಸು LOG(x) (ದಶಮಾಂಶ)ಲಘುಗಣಕ((ದ್ವಿಗುಣ)(x))
#ವ್ಯಾಖ್ಯಾನಿಸು POW(x,y) (ದಶಮಾಂಶ)ಘಾತ((ದ್ವಿಗುಣ)(x),(ದ್ವಿಗುಣ)(y))
#ವ್ಯಾಖ್ಯಾನಿಸು SQRT(x) (ದಶಮಾಂಶ)ವರ್ಗಮೂಲ((ದ್ವಿಗುಣ)(x))
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು FLOAT ದ್ವಿಗುಣ
#ವ್ಯಾಖ್ಯಾನಿಸು FABS(x) fabs(x)
#ವ್ಯಾಖ್ಯಾನಿಸು FLOOR(x) floor(x)
#ವ್ಯಾಖ್ಯಾನಿಸು LOG(x) ಲಘುಗಣಕ(x)
#ವ್ಯಾಖ್ಯಾನಿಸು POW(x,y) ಘಾತ(x,y)
#ವ್ಯಾಖ್ಯಾನಿಸು SQRT(x) ವರ್ಗಮೂಲ(x)
#ಆದರೆ_ಅಂತ್ಯ

jmp_buf ovfl_buf;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KR_ಶೀರ್ಷಿಕೆಗಳು
#ವ್ಯಾಖ್ಯಾನಿಸು VOID /* void */
#ವ್ಯಾಖ್ಯಾನಿಸು INT /* int */
#ವ್ಯಾಖ್ಯಾನಿಸು FP /* FLOAT */
#ವ್ಯಾಖ್ಯಾನಿಸು CHARP /* char * */
#ವ್ಯಾಖ್ಯಾನಿಸು CHARPP /* char ** */
ಬಾಹ್ಯ ದ್ವಿಗುಣ fabs(), floor(), ಲಘುಗಣಕ(), ಘಾತ(), ವರ್ಗಮೂಲ();
ಬಾಹ್ಯ ಶೂನ್ಯ ನಿರ್ಗಮಿಸು();
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*Sig_type)();
FLOAT Sign(), Random();
ಬಾಹ್ಯ ಶೂನ್ಯ BadCond();
ಬಾಹ್ಯ ಶೂನ್ಯ SqXMinX();
ಬಾಹ್ಯ ಶೂನ್ಯ TstCond();
ಬಾಹ್ಯ ಶೂನ್ಯ notify();
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಪಠ();
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು VOID ಶೂನ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು INT ಪೂರ್ಣಾಂಕ
#ವ್ಯಾಖ್ಯಾನಿಸು FP FLOAT
#ವ್ಯಾಖ್ಯಾನಿಸು CHARP ಅಕ್ಷರ *
#ವ್ಯಾಖ್ಯಾನಿಸು CHARPP ಅಕ್ಷರ **
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __STDC__
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <math.h>
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ
ಬಾಹ್ಯ ದ್ವಿಗುಣ fabs(ದ್ವಿಗುಣ), floor(ದ್ವಿಗುಣ), ಲಘುಗಣಕ(ದ್ವಿಗುಣ);
ಬಾಹ್ಯ ದ್ವಿಗುಣ ಘಾತ(ದ್ವಿಗುಣ,ದ್ವಿಗುಣ), ವರ್ಗಮೂಲ(ದ್ವಿಗುಣ);
ಬಾಹ್ಯ ಶೂನ್ಯ ನಿರ್ಗಮಿಸು(INT);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
	}
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*Sig_type)(ಪೂರ್ಣಾಂಕ);
FLOAT Sign(FLOAT), Random(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ BadCond(ಪೂರ್ಣಾಂಕ, ಅಕ್ಷರ*);
ಬಾಹ್ಯ ಶೂನ್ಯ SqXMinX(ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ TstCond(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಅಕ್ಷರ*);
ಬಾಹ್ಯ ಶೂನ್ಯ notify(ಅಕ್ಷರ*);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಪಠ(ಪೂರ್ಣಾಂಕ, ಅಕ್ಷರ*, ಪೂರ್ಣಾಂಕ);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು V9
ಬಾಹ್ಯ ಶೂನ್ಯ Characteristics(VOID);
ಬಾಹ್ಯ ಶೂನ್ಯ Heading(VOID);
ಬಾಹ್ಯ ಶೂನ್ಯ History(VOID);
ಬಾಹ್ಯ ಶೂನ್ಯ Instructions(VOID);
ಬಾಹ್ಯ ಶೂನ್ಯ IsYeqX(VOID);
ಬಾಹ್ಯ ಶೂನ್ಯ NewD(VOID);
ಬಾಹ್ಯ ಶೂನ್ಯ Pause(VOID);
ಬಾಹ್ಯ ಶೂನ್ಯ PrintIfNPositive(VOID);
ಬಾಹ್ಯ ಶೂನ್ಯ SR3750(VOID);
ಬಾಹ್ಯ ಶೂನ್ಯ SR3980(VOID);
ಬಾಹ್ಯ ಶೂನ್ಯ TstPtUf(VOID);

Sig_type sigsave;

#ವ್ಯಾಖ್ಯಾನಿಸು KEYBOARD 0

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
ಪೂರ್ಣಾಂಕ NoTrials = 20; /*Number of tests for commutativity. */
#ವ್ಯಾಖ್ಯಾನಿಸು False 0
#ವ್ಯಾಖ್ಯಾನಿಸು True 1

/* Definitions for declared types 
	Guard == (Yes, No);
	Rounding == (Chopped, Rounded, Other);
	Message == packed array [1..40] of char;
	Class == (Flaw, Defect, Serious, Failure);
	  */
#ವ್ಯಾಖ್ಯಾನಿಸು Yes 1
#ವ್ಯಾಖ್ಯಾನಿಸು No  0
#ವ್ಯಾಖ್ಯಾನಿಸು Chopped 2
#ವ್ಯಾಖ್ಯಾನಿಸು Rounded 1
#ವ್ಯಾಖ್ಯಾನಿಸು Other   0
#ವ್ಯಾಖ್ಯಾನಿಸು Flaw    3
#ವ್ಯಾಖ್ಯಾನಿಸು Defect  2
#ವ್ಯಾಖ್ಯಾನಿಸು Serious 1
#ವ್ಯಾಖ್ಯಾನಿಸು Failure 0
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ Guard, Rounding, Class;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ ಸಂದೇಶ;

/* Declarations of Variables */
ಪೂರ್ಣಾಂಕ Indx;
ಅಕ್ಷರ ch[8];
FLOAT AInvrse, A1;
FLOAT C, CInvrse;
FLOAT D, FourD;
FLOAT E0, E1, Exp2, E3, MinSqEr;
FLOAT SqEr, MaxSqEr, E9;
FLOAT ಮೂರನೇ;
FLOAT F6, F9;
FLOAT H, HInvrse;
ಪೂರ್ಣಾಂಕ I;
FLOAT Sticky_ಬಿಟ್, J;
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
ಪೂರ್ಣಾಂಕ ErrCnt[4];
ಪೂರ್ಣಾಂಕ fpecount;
ಪೂರ್ಣಾಂಕ Milestone;
ಪೂರ್ಣಾಂಕ ಪುಟ_No;
ಪೂರ್ಣಾಂಕ M, N, N1;
Guard GMult, GDiv, GAddSub;
Rounding RMult, RDiv, RAddSub, RSqrt;
ಪೂರ್ಣಾಂಕ Break, ಮುಗಿದ, NotMonot, Monot, Anomaly, IEEE,
		SqRWrng, UfNGrad;
/* Computed constants. */
/*U1  gap below 1.0, i.e, 1.0-U1 is next number below 1.0 */
/*U2  gap above 1.0, i.e, 1.0+U2 is next number above 1.0 */

/* floating point exception receiver */
 ಶೂನ್ಯ
sigfpe(INT x)
{
	fpecount++;
	ಬರೆ("\n* * * FLOATING-POINT ERROR %d * * *\n", x);
	fflush(stdout);
	ಆದರೆ (sigsave) {
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NOSIGNAL
		ಸಂಕೇತ(SIGFPE, sigsave);
#ಆದರೆ_ಅಂತ್ಯ
		sigsave = 0;
		longjmp(ovfl_buf, 1);
		}
	ನಿರ್ಗಮಿಸು(1);
}

ಮುಖ್ಯ(VOID)
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
	ಪುಟ_No = 1;
	/*=============================================*/
	Milestone = 0;
	/*=============================================*/
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NOSIGNAL
	ಸಂಕೇತ(SIGFPE, sigfpe);
#ಆದರೆ_ಅಂತ್ಯ
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
	ಬರೆ("Program is now RUNNING tests on small integers:\n");
	
	TstCond (Failure, (Zero + Zero == Zero) && (One - One == Zero)
		   && (One > Zero) && (One + One == Two),
			"0+0 != 0, 1-1 != 0, 1 <= 0, or 1+1 != 2");
	Z = - Zero;
	ಆದರೆ (Z != 0.0) {
		ErrCnt[Failure] = ErrCnt[Failure] + 1;
		ಬರೆ("Comparison alleges that -0.0 is Non-zero!\n");
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
	/*ವಿಭಜಿಸು
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
	ಆದರೆ (ErrCnt[Failure] == 0) {
		ಬರೆ("-1, 0, 1/2, 1, 2, 3, 4, 5, 9, 27, 32 & 240 are O.K.\n");
		ಬರೆ("\n");
		}
	ಬರೆ("Searching for Radix and Precision.\n");
	W = One;
	ಮಾಡು  {
		W = W + W;
		Y = W + One;
		Z = Y - W;
		Y = Z - One;
		} ಆಗ (MinusOne + FABS(Y) < Zero);
	/*.. now W is just big enough that |((W+1)-W)-1| >= 1 ...*/
	Precision = Zero;
	Y = One;
	ಮಾಡು  {
		Radix = W + Y;
		Y = Y + Y;
		Radix = Radix - W;
		} ಆಗ ( Radix == Zero);
	ಆದರೆ (Radix < Two) Radix = One;
	ಬರೆ("Radix = %d .\n", Radix);
	ಆದರೆ (Radix != 1) {
		W = One;
		ಮಾಡು  {
			Precision = Precision + One;
			W = W * Radix;
			Y = W + One;
			} ಆಗ ((Y - W) == One);
		}
	/*... now W == Radix^Precision is barely too big to satisfy (W+1)-W == 1
			                              ...*/
	U1 = One / W;
	U2 = Radix * U1;
	ಬರೆ("Closest relative separation found is U1 = %d .\n\n", U1);
	ಬರೆ("Recalculating radix and precision\n ");
	
	/*save old values*/
	E0 = Radix;
	E1 = U1;
	E9 = U2;
	E3 = Precision;
	
	X = Four / Three;
	ಮೂರನೇ = X - One;
	F6 = Half - ಮೂರನೇ;
	X = F6 + F6;
	X = FABS(X - ಮೂರನೇ);
	ಆದರೆ (X < U2) X = U2;
	
	/*... now X = (unknown no.) ulps of 1+...*/
	ಮಾಡು  {
		U2 = X;
		Y = Half * U2 + ThirtyTwo * U2 * U2;
		Y = One + Y;
		X = Y - One;
		} ಆಗ ( ! ((U2 <= X) || (X <= Zero)));
	
	/*... now U2 == 1 ulp of 1 + ... */
	X = Two / Three;
	F6 = X - Half;
	ಮೂರನೇ = F6 + F6;
	X = ಮೂರನೇ - Half;
	X = FABS(X + F6);
	ಆದರೆ (X < U1) X = U1;
	
	/*... now  X == (unknown no.) ulps of 1 -... */
	ಮಾಡು  {
		U1 = X;
		Y = Half * U1 + ThirtyTwo * U1 * U1;
		Y = Half - Y;
		X = Half + Y;
		Y = Half - X;
		X = Half + Y;
		} ಆಗ ( ! ((U1 <= X) || (X <= Zero)));
	/*... now U1 == 1 ulp of 1 - ... */
	ಆದರೆ (U1 == E1) ಬರೆ("confirms closest relative separation U1 .\n");
	ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("gets better closest relative separation U1 = %d .\n", U1);
	W = One / U1;
	F9 = (Half - U1) + Half;
	Radix = FLOOR(0.01 + U2 / U1);
	ಆದರೆ (Radix == E0) ಬರೆ("Radix confirmed.\n");
	ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("MYSTERY: recalculated Radix = %d .\n", Radix);
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
	ಆದರೆ (Radix != One)  {
		X = - TwoForty * LOG(U1) / LOG(Radix);
		Y = FLOOR(Half + X);
		ಆದರೆ (FABS(X - Y) * Four < One) X = Y;
		Precision = X / TwoForty;
		Y = FLOOR(Half + Precision);
		ಆದರೆ (FABS(Precision - Y) * TwoForty < Half) Precision = Y;
		}
	ಆದರೆ ((Precision != FLOOR(Precision)) || (Radix == One)) {
		ಬರೆ("Precision cannot be characterized by an Integer number\n");
		ಬರೆ("of significant digits but, by itself, this is a minor flaw.\n");
		}
	ಆದರೆ (Radix == One) 
		ಬರೆ("logarithmic encoding has precision characterized solely by U1.\n");
	ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("The number of significant digits of the Radix is %d .\n",
			Precision);
	TstCond (Serious, U2 * Nine * Nine * TwoForty < One,
		   "Precision worse than 5 decimal figures  ");
	/*=============================================*/
	Milestone = 30;
	/*=============================================*/
	/* Test for extra-precise subepressions */
	X = FABS(((Four / Three - One) - One / Four) * Three - One / Four);
	ಮಾಡು  {
		Z2 = X;
		X = (One + (Half * Z2 + ThirtyTwo * Z2 * Z2)) - One;
		} ಆಗ ( ! ((Z2 <= X) || (X <= Zero)));
	X = Y = Z = FABS((Three / Four - Two / Three) * Three - One / Four);
	ಮಾಡು  {
		Z1 = Z;
		Z = (One / Two - ((One / Two - (Half * Z1 + ThirtyTwo * Z1 * Z1))
			+ One / Two)) + One / Two;
		} ಆಗ ( ! ((Z1 <= Z) || (Z <= Zero)));
	ಮಾಡು  {
		ಮಾಡು  {
			Y1 = Y;
			Y = (Half - ((Half - (Half * Y1 + ThirtyTwo * Y1 * Y1)) + Half
				)) + Half;
			} ಆಗ ( ! ((Y1 <= Y) || (Y <= Zero)));
		X1 = X;
		X = ((Half * X1 + ThirtyTwo * X1 * X1) - F9) + F9;
		} ಆಗ ( ! ((X1 <= X) || (X <= Zero)));
	ಆದರೆ ((X1 != Y1) || (X1 != Z1)) {
		BadCond(Serious, "Disagreements among the values X1, Y1, Z1,\n");
		ಬರೆ("respectively  %d,  %016x,  %016x,\n", X1, Y1, Z1);
		ಬರೆ("are symptoms of inconsistencies introduced\n");
		ಬರೆ("by extra-precise evaluation of arithmetic subexpressions.\n");
		notify("Possibly some part of this");
		ಆದರೆ ((X1 == U1) || (Y1 == U1) || (Z1 == U1))  ಬರೆ(
			"That feature is not tested further by this program.\n") ;
		}
	ಇಲ್ಲದಿದ್ದರೆ  {
		ಆದರೆ ((Z1 != U1) || (Z2 != U2)) {
			ಆದರೆ ((Z1 >= U1) || (Z2 >= U2)) {
				BadCond(Failure, "");
				notify("Precision");
				ಬರೆ("\tU1 = %d, Z1 - U1 = %016x\n",U1,Z1-U1);
				ಬರೆ("\tU2 = %d, Z2 - U2 = %016x\n",U2,Z2-U2);
				}
			ಇಲ್ಲದಿದ್ದರೆ {
				ಆದರೆ ((Z1 <= Zero) || (Z2 <= Zero)) {
					ಬರೆ("Because of unusual Radix = %d", Radix);
					ಬರೆ(", or exact rational arithmetic a result\n");
					ಬರೆ("Z1 = %d, or Z2 = %016x ", Z1, Z2);
					notify("of an\nextra-precision");
					}
				ಆದರೆ (Z1 != Z2 || Z1 > Zero) {
					X = Z1 / U1;
					Y = Z2 / U2;
					ಆದರೆ (Y > X) X = Y;
					Q = - LOG(X);
					ಬರೆ("Some subexpressions appear to be calculated extra\n");
					ಬರೆ("precisely with about %d extra B-digits, i.e.\n",
						(Q / LOG(Radix)));
					ಬರೆ("roughly %d extra significant decimals.\n",
						Q / LOG(10.));
					}
				ಬರೆ("That feature is not tested further by this program.\n");
				}
			}
		}
	Pause();
	/*=============================================*/
	/*ವಿಭಜಿಸು
	}
#include "paranoia.h"
void part3(VOID){
*/
	Milestone = 35;
	/*=============================================*/
	ಆದರೆ (Radix >= Two) {
		X = W / (Radix * Radix);
		Y = X + One;
		Z = Y - X;
		T = Z + U2;
		X = T - Z;
		TstCond (Failure, X == U2,
			"Subtraction is not normalized X=Y,X+Z != Y+Z!");
		ಆದರೆ (X == U2) ಬರೆ(
			"Subtraction appears to be normalized, as it should be.");
		}
	ಬರೆ("\nChecking for guard digit in *, /, and -.\n");
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
	ಆದರೆ ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)) GMult = Yes;
	ಇಲ್ಲದಿದ್ದರೆ {
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
	ಆದರೆ ((X == Zero) && (Y == Zero) && (Z == Zero)) GDiv = Yes;
	ಇಲ್ಲದಿದ್ದರೆ {
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
	Sticky_ಬಿಟ್ = T / Radix;
	X = R - X;
	Y = Sticky_ಬಿಟ್ - Y;
	TstCond (Failure, X == Zero && Y == Zero,
			"* and/or / gets too many last digits wrong");
	Y = One - U1;
	X = One - F9;
	Y = One - Y;
	T = Radix - U2;
	Z = Radix - BMinusU2;
	T = Radix - T;
	ಆದರೆ ((X == U1) && (Y == U1) && (Z == U2) && (T == U2)) GAddSub = Yes;
	ಇಲ್ಲದಿದ್ದರೆ {
		GAddSub = No;
		TstCond (Serious, False,
			"- lacks Guard Digit, so cancellation is obscured");
		}
	ಆದರೆ (F9 != One && F9 - One >= Zero) {
		BadCond(Serious, "comparison alleges  (1-U1) < 1  although\n");
		ಬರೆ("  subtraction yields  (1-U1) - 1 = 0 , thereby vitiating\n");
		ಬರೆ("  such precautions against division by zero as\n");
		ಬರೆ("  ...  if (X == 1.0) {.....} else {.../(X-1.0)...}\n");
		}
	ಆದರೆ (GMult == Yes && GDiv == Yes && GAddSub == Yes) ಬರೆ(
		"     *, /, and - appear to have guard digits, as they should.\n");
	/*=============================================*/
	Milestone = 40;
	/*=============================================*/
	Pause();
	ಬರೆ("Checking rounding on multiply, divide and add/subtract.\n");
	RMult = Other;
	RDiv = Other;
	RAddSub = Other;
	RadixD2 = Radix / Two;
	A1 = Two;
	ಮುಗಿದ = False;
	ಮಾಡು  {
		AInvrse = Radix;
		ಮಾಡು  {
			X = AInvrse;
			AInvrse = AInvrse / A1;
			} ಆಗ ( ! (FLOOR(AInvrse) != AInvrse));
		ಮುಗಿದ = (X == One) || (A1 > Three);
		ಆದರೆ (! ಮುಗಿದ) A1 = Nine + One;
		} ಆಗ ( ! (ಮುಗಿದ));
	ಆದರೆ (X == One) A1 = Radix;
	AInvrse = One / A1;
	X = A1;
	Y = AInvrse;
	ಮುಗಿದ = False;
	ಮಾಡು  {
		Z = X * Y - Half;
		TstCond (Failure, Z == Half,
			"X * (1/X) differs from 1");
		ಮುಗಿದ = X == Radix;
		X = Radix;
		Y = One / X;
		} ಆಗ ( ! (ಮುಗಿದ));
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
	ಆದರೆ ((X == Zero) && (Y == Zero) && (Z == Zero) && (T <= Zero)) {
		X = (OneAndHalf + U2) * Y2;
		Y = OneAndHalf - U2 - U2;
		Z = OneAndHalf + U2 + U2;
		T = (OneAndHalf - U2) * Y1;
		X = X - (Z + U2);
		Sticky_ಬಿಟ್ = Y * Y1;
		S = Z * Y2;
		T = T - Y;
		Y = (U2 - Y) + Sticky_ಬಿಟ್;
		Z = S - (Z + U2 + U2);
		Sticky_ಬಿಟ್ = (Y2 + U2) * Y1;
		Y1 = Y2 * Y1;
		Sticky_ಬಿಟ್ = Sticky_ಬಿಟ್ - Y2;
		Y1 = Y1 - Half;
		ಆದರೆ ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)
			&& ( Sticky_ಬಿಟ್ == Zero) && (Y1 == Half)) {
			RMult = Rounded;
			ಬರೆ("Multiplication appears to round correctly.\n");
			}
		ಇಲ್ಲದಿದ್ದರೆ	ಆದರೆ ((X + U2 == Zero) && (Y < Zero) && (Z + U2 == Zero)
				&& (T < Zero) && (Sticky_ಬಿಟ್ + U2 == Zero)
				&& (Y1 < Half)) {
				RMult = Chopped;
				ಬರೆ("Multiplication appears to chop.\n");
				}
			ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("* is neither chopped nor correctly rounded.\n");
		ಆದರೆ ((RMult == Rounded) && (GMult == No)) notify("Multiplication");
		}
	ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("* is neither chopped nor correctly rounded.\n");
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
	ಆದರೆ (! ((X > Zero) || (Y > Zero) || (Z > Zero) || (T > Zero))) {
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
		ಆದರೆ ((X == Zero) && (Y == Zero) && (Z == Zero) && (T == Zero)
			&& (Y2 == Zero) && (Y2 == Zero)
			&& (Y1 - Half == F9 - Half )) {
			RDiv = Rounded;
			ಬರೆ("Division appears to round correctly.\n");
			ಆದರೆ (GDiv == No) notify("Division");
			}
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((X < Zero) && (Y < Zero) && (Z < Zero) && (T < Zero)
			&& (Y2 < Zero) && (Y1 - Half < F9 - Half)) {
			RDiv = Chopped;
			ಬರೆ("Division appears to chop.\n");
			}
		}
	ಆದರೆ (RDiv == Other) ಬರೆ("/ is neither chopped nor correctly rounded.\n");
	BInvrse = One / Radix;
	TstCond (Failure, (BInvrse * Radix - Half == Half),
		   "Radix * ( 1 / Radix ) differs from 1");
	/*=============================================*/
	/*ವಿಭಜಿಸು
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
	ಆದರೆ ((X == Zero) && (Y == Zero)) {
		RAddSub = Chopped;
		ಬರೆ("Add/Subtract appears to be chopped.\n");
		}
	ಆದರೆ (GAddSub == Yes) {
		X = (Half + U2) * U2;
		Y = (Half - U2) * U2;
		X = One + X;
		Y = One + Y;
		X = (One + U2) - X;
		Y = One - Y;
		ಆದರೆ ((X == Zero) && (Y == Zero)) {
			X = (Half + U2) * U1;
			Y = (Half - U2) * U1;
			X = One - X;
			Y = One - Y;
			X = F9 - X;
			Y = One - Y;
			ಆದರೆ ((X == Zero) && (Y == Zero)) {
				RAddSub = Rounded;
				ಬರೆ("Addition/Subtraction appears to round correctly.\n");
				ಆದರೆ (GAddSub == No) notify("Add/Subtract");
				}
			ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("Addition/Subtraction neither rounds nor chops.\n");
			}
		ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("Addition/Subtraction neither rounds nor chops.\n");
		}
	ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("Addition/Subtraction neither rounds nor chops.\n");
	S = One;
	X = One + Half * (One + Half);
	Y = (One + U2) * Half;
	Z = X - Y;
	T = Y - X;
	Sticky_ಬಿಟ್ = Z + T;
	ಆದರೆ (Sticky_ಬಿಟ್ != Zero) {
		S = Zero;
		BadCond(Flaw, "(X - Y) + (Y - X) is non zero!\n");
		}
	Sticky_ಬಿಟ್ = Zero;
	ಆದರೆ ((GMult == Yes) && (GDiv == Yes) && (GAddSub == Yes)
		&& (RMult == Rounded) && (RDiv == Rounded)
		&& (RAddSub == Rounded) && (FLOOR(RadixD2) == RadixD2)) {
		ಬರೆ("Checking for sticky bit.\n");
		X = (Half + U1) * U2;
		Y = Half * U2;
		Z = One + Y;
		T = One + X;
		ಆದರೆ ((Z - One <= Zero) && (T - One >= U2)) {
			Z = T + Y;
			Y = Z - X;
			ಆದರೆ ((Z - T >= U2) && (Y - T == Zero)) {
				X = (Half + U1) * U1;
				Y = Half * U1;
				Z = One - Y;
				T = One - X;
				ಆದರೆ ((Z - One == Zero) && (T - F9 == Zero)) {
					Z = (Half - U1) * U1;
					T = F9 - Z;
					Q = F9 - Y;
					ಆದರೆ ((T - F9 == Zero) && (F9 - U1 - Q == Zero)) {
						Z = (One + U2) * OneAndHalf;
						T = (OneAndHalf + U2) - Z + U2;
						X = One + Half / Radix;
						Y = One + Radix * U2;
						Z = X * Y;
						ಆದರೆ (T == Zero && X + Radix * U2 - Z == Zero) {
							ಆದರೆ (Radix != Two) {
								X = Two + U2;
								Y = X / Two;
								ಆದರೆ ((Y - One == Zero)) Sticky_ಬಿಟ್ = S;
								}
							ಇಲ್ಲದಿದ್ದರೆ Sticky_ಬಿಟ್ = S;
							}
						}
					}
				}
			}
		}
	ಆದರೆ (Sticky_ಬಿಟ್ == One) ಬರೆ("Sticky bit apparently used correctly.\n");
	ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("Sticky bit used incorrectly or not at all.\n");
	TstCond (Flaw, !(GMult == No || GDiv == No || GAddSub == No ||
			RMult == Other || RDiv == Other || RAddSub == Other),
		"lack(s) ದ guard digits or failure(s) ಗಮ್ಯ correctly round or chop\n\
(noted above) ಎಣಿಕೆ_2 as one flaw ಒಳ the final tally ಕೆಳಗೆ");
	/*=============================================*/
	Milestone = 60;
	/*=============================================*/
	ಬರೆ("\n");
	ಬರೆ("Does Multiplication commute?  ");
	ಬರೆ("Testing on %d random pairs.\n", NoTrials);
	Random9 = SQRT(3.0);
	Random1 = ಮೂರನೇ;
	I = 1;
	ಮಾಡು  {
		X = Random();
		Y = Random();
		Z9 = Y * X;
		Z = X * Y;
		Z9 = Z - Z9;
		I = I + 1;
		} ಆಗ ( ! ((I > NoTrials) || (Z9 != Zero)));
	ಆದರೆ (I == NoTrials) {
		Random1 = One + Half / Three;
		Random2 = (U2 + U1) + One;
		Z = Random1 * Random2;
		Y = Random2 * Random1;
		Z9 = (One + Half / Three) * ((U2 + U1) + One) - (One + Half /
			Three) * ((U2 + U1) + One);
		}
	ಆದರೆ (! ((I == NoTrials) || (Z9 == Zero)))
		BadCond(Defect, "X * Y == Y * X trial fails.\n");
	ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("     No failures found in %d integer pairs.\n", NoTrials);
	/*=============================================*/
	Milestone = 70;
	/*=============================================*/
	ಬರೆ("\nRunning test of square root(x).\n");
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
	ಆದರೆ (J != Zero) Pause();
	ಬರೆ("Testing if sqrt(X * X) == X for %d Integers X.\n", NoTrials);
	J = Zero;
	X = Two;
	Y = Radix;
	ಆದರೆ ((Radix != One)) ಮಾಡು  {
		X = Y;
		Y = Radix * Y;
		} ಆಗ ( ! ((Y - X >= NoTrials)));
	OneUlp = X * U2;
	I = 1;
	ಆಗ (I <= NoTrials) {
		X = X + One;
		SqXMinX (Defect);
		ಆದರೆ (J > Zero) ನಿಲ್ಲಿಸು;
		I = I + 1;
		}
	ಬರೆ("Test for sqrt monotonicity.\n");
	I = - 1;
	X = BMinusU2;
	Y = Radix;
	Z = Radix + Radix * U2;
	NotMonot = False;
	Monot = False;
	ಆಗ ( ! (NotMonot || Monot)) {
		I = I + 1;
		X = SQRT(X);
		Q = SQRT(Y);
		Z = SQRT(Z);
		ಆದರೆ ((X > Q) || (Q > Z)) NotMonot = True;
		ಇಲ್ಲದಿದ್ದರೆ {
			Q = FLOOR(Q + Half);
			ಆದರೆ (!(I > 0 || Radix == Q * Q)) Monot = True;
			ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (I > 0) {
			ಆದರೆ (I > 1) Monot = True;
			ಇಲ್ಲದಿದ್ದರೆ {
				Y = Y * BInvrse;
				X = Y - U1;
				Z = Y + U1;
				}
			}
			ಇಲ್ಲದಿದ್ದರೆ {
				Y = Q;
				X = Y - U2;
				Z = Y + U2;
				}
			}
		}
	ಆದರೆ (Monot) ಬರೆ("sqrt has passed a test for Monotonicity.\n");
	ಇಲ್ಲದಿದ್ದರೆ {
		BadCond(Defect, "");
		ಬರೆ("sqrt(X) is non-monotonic for X near %d .\n", Y);
		}
	/*=============================================*/
	/*ವಿಭಜಿಸು
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
	ಆದರೆ (SqEr > MaxSqEr) MaxSqEr = SqEr;
	SqEr = Y + U2 / Eight;
	ಆದರೆ (SqEr < MinSqEr) MinSqEr = SqEr;
	Y = ((SQRT(F9) - U2) - (One - U2)) / U1;
	SqEr = Y + U1 / Eight;
	ಆದರೆ (SqEr > MaxSqEr) MaxSqEr = SqEr;
	SqEr = (Y + One) + U1 / Eight;
	ಆದರೆ (SqEr < MinSqEr) MinSqEr = SqEr;
	OneUlp = U2;
	X = OneUlp;
	ಗಾಗಿ( Indx = 1; Indx <= 3; ++Indx) {
		Y = SQRT((X + U1 + X) + F9);
		Y = ((Y - U2) - ((One - U2) + X)) / OneUlp;
		Z = ((U1 - X) + F9) * Half * X * X / OneUlp;
		SqEr = (Y + Half) + Z;
		ಆದರೆ (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = (Y - Half) + Z;
		ಆದರೆ (SqEr > MaxSqEr) MaxSqEr = SqEr;
		ಆದರೆ (((Indx == 1) || (Indx == 3))) 
			X = OneUlp * Sign (X) * FLOOR(Eight / (Nine * SQRT(OneUlp)));
		ಇಲ್ಲದಿದ್ದರೆ {
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
	ಆದರೆ (Radix != One) {
		ಬರೆ("Testing whether sqrt is rounded or chopped.\n");
		D = FLOOR(Half + POW(Radix, One + Precision - FLOOR(Precision)));
	/* ... == Radix^(1 + fract) if (Precision == Integer + fract. */
		X = D / Radix;
		Y = D / A1;
		ಆದರೆ ((X != FLOOR(X)) || (Y != FLOOR(Y))) {
			Anomaly = True;
			}
		ಇಲ್ಲದಿದ್ದರೆ {
			X = Zero;
			Z2 = X;
			Y = One;
			Y2 = Y;
			Z1 = Radix - One;
			FourD = Four * D;
			ಮಾಡು  {
				ಆದರೆ (Y2 > Z2) {
					Q = Radix;
					Y1 = Y;
					ಮಾಡು  {
						X1 = FABS(Q + FLOOR(Half - Q / Y1) * Y1);
						Q = Y1;
						Y1 = X1;
						} ಆಗ ( ! (X1 <= Zero));
					ಆದರೆ (Q <= One) {
						Z2 = Y2;
						Z = Y;
						}
					}
				Y = Y + Two;
				X = X + Eight;
				Y2 = Y2 + X;
				ಆದರೆ (Y2 >= FourD) Y2 = Y2 - FourD;
				} ಆಗ ( ! (Y >= D));
			X8 = FourD - Z2;
			Q = (X8 + Z * Z) / FourD;
			X8 = X8 / Eight;
			ಆದರೆ (Q != FLOOR(Q)) Anomaly = True;
			ಇಲ್ಲದಿದ್ದರೆ {
				Break = False;
				ಮಾಡು  {
					X = Z1 * Z;
					X = X - FLOOR(X / Radix) * Radix;
					ಆದರೆ (X == One) 
						Break = True;
					ಇಲ್ಲದಿದ್ದರೆ
						Z1 = Z1 - One;
					} ಆಗ ( ! (Break || (Z1 <= Zero)));
				ಆದರೆ ((Z1 <= Zero) && (! Break)) Anomaly = True;
				ಇಲ್ಲದಿದ್ದರೆ {
					ಆದರೆ (Z1 > RadixD2) Z1 = Z1 - Radix;
					ಮಾಡು  {
						NewD();
						} ಆಗ ( ! (U2 * D >= F9));
					ಆದರೆ (D * Radix - D != W - D) Anomaly = True;
					ಇಲ್ಲದಿದ್ದರೆ {
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
						ಆದರೆ (D - Z2 != W - Z2) Anomaly = True;
						ಇಲ್ಲದಿದ್ದರೆ {
							Y = (D - Z2) + (Z2 + (One - Z) * Half);
							X = (D - Z2) + (Z2 - Z + Q);
							SR3750();
							Y = (One + Z) * Half;
							X = Q;
							SR3750();
							ಆದರೆ (I == 0) Anomaly = True;
							}
						}
					}
				}
			}
		ಆದರೆ ((I == 0) || Anomaly) {
			BadCond(Failure, "Anomalous arithmetic with Integer < ");
			ಬರೆ("Radix^Precision = %d\n", W);
			ಬರೆ(" fails test whether sqrt rounds or chops.\n");
			SqRWrng = True;
			}
		}
	ಆದರೆ (! Anomaly) {
		ಆದರೆ (! ((MinSqEr < Zero) || (MaxSqEr > Zero))) {
			RSqrt = Rounded;
			ಬರೆ("Square root appears to be correctly rounded.\n");
			}
		ಇಲ್ಲದಿದ್ದರೆ  {
			ಆದರೆ ((MaxSqEr + U2 > U2 - Half) || (MinSqEr > Half)
				|| (MinSqEr + Radix < Half)) SqRWrng = True;
			ಇಲ್ಲದಿದ್ದರೆ {
				RSqrt = Chopped;
				ಬರೆ("Square root appears to be chopped.\n");
				}
			}
		}
	ಆದರೆ (SqRWrng) {
		ಬರೆ("Square root is neither chopped nor correctly rounded.\n");
		ಬರೆ("Observed errors run from %d ", MinSqEr - Half);
		ಬರೆ("to %d ulps.\n", Half + MaxSqEr);
		TstCond (Serious, MaxSqEr - MinSqEr < Radix * Radix,
			"sqrt gets too many last digits wrong");
		}
	/*=============================================*/
	Milestone = 90;
	/*=============================================*/
	Pause();
	ಬರೆ("Testing powers Z^i for small Integers Z and i.\n");
	N = 0;
	/* ... test powers of zero. */
	I = 0;
	Z = -Zero;
	M = 3;
	Break = False;
	ಮಾಡು  {
		X = One;
		SR3980();
		ಆದರೆ (I <= 10) {
			I = 1023;
			SR3980();
			}
		ಆದರೆ (Z == MinusOne) Break = True;
		ಇಲ್ಲದಿದ್ದರೆ {
			Z = MinusOne;
			/* .. if(-1)^N is invalid, replace MinusOne by One. */
			I = - 4;
			}
		} ಆಗ ( ! Break);
	PrintIfNPositive();
	N1 = N;
	N = 0;
	Z = A1;
	M = (ಪೂರ್ಣಾಂಕ)FLOOR(Two * LOG(W) / LOG(A1));
	Break = False;
	ಮಾಡು  {
		X = Z;
		I = 1;
		SR3980();
		ಆದರೆ (Z == AInvrse) Break = True;
		ಇಲ್ಲದಿದ್ದರೆ Z = AInvrse;
		} ಆಗ ( ! (Break));
	/*=============================================*/
		Milestone = 100;
	/*=============================================*/
	/*  Powers of Radix have been tested, */
	/*         next try a few primes     */
	M = NoTrials;
	Z = Three;
	ಮಾಡು  {
		X = Z;
		I = 1;
		SR3980();
		ಮಾಡು  {
			Z = Z + Two;
			} ಆಗ ( Three * FLOOR(Z / Three) == Z );
		} ಆಗ ( Z < Eight * Three );
	ಆದರೆ (N > 0) {
		ಬರೆ("Errors like this may invalidate financial calculations\n");
		ಬರೆ("\tinvolving interest rates.\n");
		}
	PrintIfNPositive();
	N += N1;
	ಆದರೆ (N == 0) ಬರೆ("... no discrepancies found.\n");
	ಆದರೆ (N > 0) Pause();
	ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("\n");
	/*=============================================*/
	/*ವಿಭಜಿಸು
	}
#include "paranoia.h"
void part6(VOID){
*/
	Milestone = 110;
	/*=============================================*/
	ಬರೆ("Seeking Underflow thresholds UfThold and E0.\n");
	D = U1;
	ಆದರೆ (Precision != FLOOR(Precision)) {
		D = BInvrse;
		X = Precision;
		ಮಾಡು  {
			D = D * BInvrse;
			X = X - One;
			} ಆಗ ( X > Zero);
		}
	Y = One;
	Z = D;
	/* ... D is power of 1/Radix < 1. */
	ಮಾಡು  {
		C = Y;
		Y = Z;
		Z = Y * Y;
		} ಆಗ ((Y > Z) && (Z + Z > Z));
	Y = C;
	Z = Y * D;
	ಮಾಡು  {
		C = Y;
		Y = Z;
		Z = Y * D;
		} ಆಗ ((Y > Z) && (Z + Z > Z));
	ಆದರೆ (Radix < Two) HInvrse = Two;
	ಇಲ್ಲದಿದ್ದರೆ HInvrse = Radix;
	H = One / HInvrse;
	/* ... 1/HInvrse == H == Min(1/Radix, 1/2) */
	CInvrse = One / C;
	E0 = C;
	Z = E0 * H;
	/* ...1/Radix^(BIG Integer) << 1 << CInvrse == 1/C */
	ಮಾಡು  {
		Y = E0;
		E0 = Z;
		Z = E0 * H;
		} ಆಗ ((E0 > Z) && (Z + Z > Z));
	UfThold = E0;
	E1 = Zero;
	Q = Zero;
	E9 = U2;
	S = One + E9;
	D = C * S;
	ಆದರೆ (D <= C) {
		E9 = Radix * U2;
		S = One + E9;
		D = C * S;
		ಆದರೆ (D <= C) {
			BadCond(Failure, "multiplication gets too many last digits wrong.\n");
			Underflow = E0;
			Y1 = Zero;
			PseudoZero = Z;
			Pause();
			}
		}
	ಇಲ್ಲದಿದ್ದರೆ {
		Underflow = D;
		PseudoZero = Underflow * H;
		UfThold = Zero;
		ಮಾಡು  {
			Y1 = Underflow;
			Underflow = PseudoZero;
			ಆದರೆ (E1 + E1 <= E1) {
				Y2 = Underflow * HInvrse;
				E1 = FABS(Y1 - Y2);
				Q = Y1;
				ಆದರೆ ((UfThold == Zero) && (Y1 != Y2)) UfThold = Y1;
				}
			PseudoZero = PseudoZero * H;
			} ಆಗ ((Underflow > PseudoZero)
				&& (PseudoZero + PseudoZero > PseudoZero));
		}
	/* Comment line 4530 .. 4560 */
	ಆದರೆ (PseudoZero != Zero) {
		ಬರೆ("\n");
		Z = PseudoZero;
	/* ... Test PseudoZero for "phoney- zero" violates */
	/* ... PseudoZero < Underflow or PseudoZero < PseudoZero + PseudoZero
		   ... */
		ಆದರೆ (PseudoZero <= Zero) {
			BadCond(Failure, "Positive expressions can underflow to an\n");
			ಬರೆ("allegedly negative value\n");
			ಬರೆ("PseudoZero that prints out as: %d .\n", PseudoZero);
			X = - PseudoZero;
			ಆದರೆ (X <= Zero) {
				ಬರೆ("But -PseudoZero, which should be\n");
				ಬರೆ("positive, isn't; it prints out as  %d .\n", X);
				}
			}
		ಇಲ್ಲದಿದ್ದರೆ {
			BadCond(Flaw, "Underflow can stick at an allegedly positive\n");
			ಬರೆ("value PseudoZero that prints out as %d .\n", PseudoZero);
			}
		TstPtUf();
		}
	/*=============================================*/
	Milestone = 120;
	/*=============================================*/
	ಆದರೆ (CInvrse * Y > CInvrse * Y1) {
		S = H * S;
		E0 = Underflow;
		}
	ಆದರೆ (! ((E1 == Zero) || (E1 == E0))) {
		BadCond(Defect, "");
		ಆದರೆ (E1 < E0) {
			ಬರೆ("Products underflow at a higher");
			ಬರೆ(" threshold than differences.\n");
			ಆದರೆ (PseudoZero == Zero) 
			E0 = E1;
			}
		ಇಲ್ಲದಿದ್ದರೆ {
			ಬರೆ("Difference underflows at a higher");
			ಬರೆ(" threshold than products.\n");
			}
		}
	ಬರೆ("Smallest strictly positive number found is E0 = %d .\n", E0);
	Z = E0;
	TstPtUf();
	Underflow = E0;
	ಆದರೆ (N == 1) Underflow = Y;
	I = 4;
	ಆದರೆ (E1 == Zero) I = 3;
	ಆದರೆ (UfThold == Zero) I = I - 2;
	UfNGrad = True;
	ಆಯ್ಕೆ (I)  {
		ಸ್ಥಿತಿ	1:
		UfThold = Underflow;
		ಆದರೆ ((CInvrse * Q) != ((CInvrse * Y) * S)) {
			UfThold = Y;
			BadCond(Failure, "Either accuracy deteriorates as numbers\n");
			ಬರೆ("approach a threshold = %d\n", UfThold);;
			ಬರೆ(" coming down from %d\n", C);
			ಬರೆ(" or else multiplication gets too many last digits wrong.\n");
			}
		Pause();
		ನಿಲ್ಲಿಸು;
	
		ಸ್ಥಿತಿ	2:
		BadCond(Failure, "Underflow confuses Comparison, which alleges that\n");
		ಬರೆ("Q == Y while denying that |Q - Y| == 0; these values\n");
		ಬರೆ("print out as Q = %d, Y = %016x .\n", Q, Y2);
		ಬರೆ ("|Q - Y| = %d .\n" , FABS(Q - Y2));
		UfThold = Q;
		ನಿಲ್ಲಿಸು;
	
		ಸ್ಥಿತಿ	3:
		X = X;
		ನಿಲ್ಲಿಸು;
	
		ಸ್ಥಿತಿ	4:
		ಆದರೆ ((Q == UfThold) && (E1 == E0)
			&& (FABS( UfThold - E1 / E9) <= E1)) {
			UfNGrad = False;
			ಬರೆ("Underflow is gradual; it incurs Absolute Error =\n");
			ಬರೆ("(roundoff in UfThold) < E0.\n");
			Y = E0 * CInvrse;
			Y = Y * (OneAndHalf + U2);
			X = CInvrse * (One + U2);
			Y = Y / X;
			IEEE = (Y == E0);
			}
		}
	ಆದರೆ (UfNGrad) {
		ಬರೆ("\n");
		sigsave = sigfpe;
		ಆದರೆ (setjmp(ovfl_buf)) {
			ಬರೆ("Underflow / UfThold failed!\n");
			R = H + H;
			}
		ಇಲ್ಲದಿದ್ದರೆ R = SQRT(Underflow / UfThold);
		sigsave = 0;
		ಆದರೆ (R <= H) {
			Z = R * UfThold;
			X = Z * (One + R * H * (One + H));
			}
		ಇಲ್ಲದಿದ್ದರೆ {
			Z = UfThold;
			X = Z * (One + H * H * (One + H));
			}
		ಆದರೆ (! ((X == Z) || (X - Z != Zero))) {
			BadCond(Flaw, "");
			ಬರೆ("X = %d\n\tis not equal to Z = %016x .\n", X, Z);
			Z9 = X - Z;
			ಬರೆ("yet X - Z yields %d .\n", Z9);
			ಬರೆ("    Should this NOT signal Underflow, ");
			ಬರೆ("this is a SERIOUS DEFECT\nthat causes ");
			ಬರೆ("confusion when innocent statements like\n");;
			ಬರೆ("    if (X == Z)  ...  else");
			ಬರೆ("  ... (f(X) - f(Z)) / (X - Z) ...\n");
			ಬರೆ("encounter Division by Zero although actually\n");
			sigsave = sigfpe;
			ಆದರೆ (setjmp(ovfl_buf)) ಬರೆ("X / Z fails!\n");
			ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("X / Z = 1 + %d .\n", (X / Z - Half) - Half);
			sigsave = 0;
			}
		}
	ಬರೆ("The Underflow threshold is %d, %s\n", UfThold,
		   " below which");
	ಬರೆ("calculation may suffer larger Relative error than ");
	ಬರೆ("merely roundoff.\n");
	Y2 = U1 * U1;
	Y = Y2 * Y2;
	Y2 = Y * U1;
	ಆದರೆ (Y2 <= UfThold) {
		ಆದರೆ (Y > E0) {
			BadCond(Defect, "");
			I = 5;
			}
		ಇಲ್ಲದಿದ್ದರೆ {
			BadCond(Serious, "");
			I = 4;
			}
		ಬರೆ("Range is too narrow; U1^%d Underflows.\n", I);
		}
	/*=============================================*/
	/*ವಿಭಜಿಸು
	}
#include "paranoia.h"
void part7(VOID){
*/
	Milestone = 130;
	/*=============================================*/
	Y = - FLOOR(Half - TwoForty * LOG(UfThold) / LOG(HInvrse)) / TwoForty;
	Y2 = Y + Y;
	ಬರೆ("Since underflow occurs below the threshold\n");
	ಬರೆ("UfThold = (%d) ^ (%016x)\nonly underflow ", HInvrse, Y);
	ಬರೆ("should afflict the expression\n\t(%d) ^ (%016x);\n",
		HInvrse, Y2);
	ಬರೆ("actually calculating yields:");
	ಆದರೆ (setjmp(ovfl_buf)) {
		sigsave = 0;
		BadCond(Serious, "trap on underflow.\n");
		}
	ಇಲ್ಲದಿದ್ದರೆ {
		sigsave = sigfpe;
		V9 = POW(HInvrse, Y2);
		sigsave = 0;
		ಬರೆ(" %d .\n", V9);
		ಆದರೆ (! ((V9 >= Zero) && (V9 <= (Radix + Radix + E9) * UfThold))) {
			BadCond(Serious, "this is not between 0 and underflow\n");
		ಬರೆ("   threshold = %d .\n", UfThold);
		}
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (! (V9 > UfThold * (One + E9)))
			ಬರೆ("This computed value is O.K.\n");
		ಇಲ್ಲದಿದ್ದರೆ {
			BadCond(Defect, "this is not between 0 and underflow\n");
			ಬರೆ("   threshold = %d .\n", UfThold);
			}
		}
	/*=============================================*/
	Milestone = 140;
	/*=============================================*/
	ಬರೆ("\n");
	/* ...calculate Exp2 == exp(2) == 7.389056099... */
	X = Zero;
	I = 2;
	Y = Two * Three;
	Q = Zero;
	N = 0;
	ಮಾಡು  {
		Z = X;
		I = I + 1;
		Y = Y / (I + I);
		R = Y + Q;
		X = Z + R;
		Q = (Z - X) + R;
		} ಆಗ(X > Z);
	Z = (OneAndHalf + One / Eight) + X / (OneAndHalf * ThirtyTwo);
	X = Z * Z;
	Exp2 = X * X;
	X = F9;
	Y = X - U1;
	ಬರೆ("Testing X^((X + 1) / (X - 1)) vs. exp(2) = %d as X -> 1.\n",
		Exp2);
	ಗಾಗಿ(I = 1;;) {
		Z = X - BInvrse;
		Z = (X + One) / (Z - (One - BInvrse));
		Q = POW(X, Z) - Exp2;
		ಆದರೆ (FABS(Q) > TwoForty * U2) {
			N = 1;
	 		V9 = (X - BInvrse) - (One - BInvrse);
			BadCond(Defect, "Calculated");
			ಬರೆ(" %d for\n", POW(X,Z));
			ಬರೆ("\t(1 + (%d) ^ (%016x);\n", V9, Z);
			ಬರೆ("\tdiffers from correct value by %d .\n", Q);
			ಬರೆ("\tThis much error may spoil financial\n");
			ಬರೆ("\tcalculations involving tiny interest rates.\n");
			ನಿಲ್ಲಿಸು;
			}
		ಇಲ್ಲದಿದ್ದರೆ {
			Z = (Y - X) * Two + Y;
			X = Y;
			Y = Z;
			Z = One + (X - F9)*(X - F9);
			ಆದರೆ (Z > One && I < NoTrials) I++;
			ಇಲ್ಲದಿದ್ದರೆ  {
				ಆದರೆ (X > One) {
					ಆದರೆ (N == 0)
					   ಬರೆ("Accuracy seems adequate.\n");
					ನಿಲ್ಲಿಸು;
					}
				ಇಲ್ಲದಿದ್ದರೆ {
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
	ಬರೆ("Testing powers Z^Q at four nearly extreme values.\n");
	N = 0;
	Z = A1;
	Q = FLOOR(Half - LOG(C) / LOG(A1));
	Break = False;
	ಮಾಡು  {
		X = CInvrse;
		Y = POW(Z, Q);
		IsYeqX();
		Q = - Q;
		X = C;
		Y = POW(Z, Q);
		IsYeqX();
		ಆದರೆ (Z < One) Break = True;
		ಇಲ್ಲದಿದ್ದರೆ Z = AInvrse;
		} ಆಗ ( ! (Break));
	PrintIfNPositive();
	ಆದರೆ (N == 0) ಬರೆ(" ... no discrepancies found.\n");
	ಬರೆ("\n");
	
	/*=============================================*/
	Milestone = 160;
	/*=============================================*/
	Pause();
	ಬರೆ("Searching for Overflow threshold:\n");
	ಬರೆ("This may generate an error.\n");
	Y = - CInvrse;
	V9 = HInvrse * Y;
	sigsave = sigfpe;
	ಆದರೆ (setjmp(ovfl_buf)) { I = 0; V9 = Y; ಹೋಗು ಅತಿಪ್ರವಾಹ; }
	ಮಾಡು {
		V = Y;
		Y = V9;
		V9 = HInvrse * Y;
		} ಆಗ(V9 < Y);
	I = 1;
ಅತಿಪ್ರವಾಹ:
	sigsave = 0;
	Z = V9;
	ಬರೆ("Can `Z = -Y' overflow?\n");
	ಬರೆ("Trying it on Y = %d .\n", Y);
	V9 = - Y;
	V0 = V9;
	ಆದರೆ (V - Y == V + V0) ಬರೆ("Seems O.K.\n");
	ಇಲ್ಲದಿದ್ದರೆ {
		ಬರೆ("finds a ");
		BadCond(Flaw, "-(-Y) differs from Y.\n");
		}
	ಆದರೆ (Z != Y) {
		BadCond(Serious, "");
		ಬರೆ("overflow past %d\n\tshrinks to %016x .\n", Y, Z);
		}
	ಆದರೆ (I) {
		Y = V * (HInvrse * U2 - HInvrse);
		Z = Y + ((One - HInvrse) * U2) * V;
		ಆದರೆ (Z < V0) Y = Z;
		ಆದರೆ (Y < V0) V = Y;
		ಆದರೆ (V0 - V < V0) V = V0;
		}
	ಇಲ್ಲದಿದ್ದರೆ {
		V = Y * (HInvrse * U2 - HInvrse);
		V = V + ((One - HInvrse) * U2) * Y;
		}
	ಬರೆ("Overflow threshold is V  = %d .\n", V);
	ಆದರೆ (I) ಬರೆ("Overflow saturates at V0 = %d .\n", V0);
	ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("There is no saturation ಮೌಲ್ಯ because \
the system traps on ಅತಿಪ್ರವಾಹ.\n");
	V9 = V * One;
	ಬರೆ("No Overflow should be signaled for V * 1 = %d\n", V9);
	V9 = V / One;
	ಬರೆ("                           nor for V / 1 = %d .\n", V9);
	ಬರೆ("Any overflow signal separating this * from the one\n");
	ಬರೆ("above is a DEFECT.\n");
	/*=============================================*/
	Milestone = 170;
	/*=============================================*/
	ಆದರೆ (!(-V < V && -V0 < V0 && -UfThold < V && UfThold < V)) {
		BadCond(Failure, "Comparisons involving ");
		ಬರೆ("+-%d, +-%016x\nand +-%016x are confused by Overflow.",
			V, V0, UfThold);
		}
	/*=============================================*/
	Milestone = 175;
	/*=============================================*/
	ಬರೆ("\n");
	ಗಾಗಿ(Indx = 1; Indx <= 3; ++Indx) {
		ಆಯ್ಕೆ (Indx)  {
			ಸ್ಥಿತಿ 1: Z = UfThold; ನಿಲ್ಲಿಸು;
			ಸ್ಥಿತಿ 2: Z = E0; ನಿಲ್ಲಿಸು;
			ಸ್ಥಿತಿ 3: Z = PseudoZero; ನಿಲ್ಲಿಸು;
			}
		ಆದರೆ (Z != Zero) {
			V9 = SQRT(Z);
			Y = V9 * V9;
			ಆದರೆ (Y / (One - Radix * E9) < Z
			   || Y > (One + Radix * E9) * Z) { /* dgh: + E9 --> * E9 */
				ಆದರೆ (V9 > U1) BadCond(Serious, "");
				ಇಲ್ಲದಿದ್ದರೆ BadCond(Defect, "");
				ಬರೆ("Comparison alleges that what prints as Z = %d\n", Z);
				ಬರೆ(" is too far from sqrt(Z) ^ 2 = %d .\n", Y);
				}
			}
		}
	/*=============================================*/
	Milestone = 180;
	/*=============================================*/
	ಗಾಗಿ(Indx = 1; Indx <= 2; ++Indx) {
		ಆದರೆ (Indx == 1) Z = V;
		ಇಲ್ಲದಿದ್ದರೆ Z = V0;
		V9 = SQRT(Z);
		X = (One - Radix * E9) * V9;
		V9 = V9 * X;
		ಆದರೆ (((V9 < (One - Two * Radix * E9) * Z) || (V9 > Z))) {
			Y = V9;
			ಆದರೆ (X < W) BadCond(Serious, "");
			ಇಲ್ಲದಿದ್ದರೆ BadCond(Defect, "");
			ಬರೆ("Comparison alleges that Z = %d\n", Z);
			ಬರೆ(" is too far from sqrt(Z) ^ 2 (%d) .\n", Y);
			}
		}
	/*=============================================*/
	/*ವಿಭಜಿಸು
	}
#include "paranoia.h"
int part8(VOID){
*/
	Milestone = 190;
	/*=============================================*/
	Pause();
	X = UfThold * V;
	Y = Radix * Radix;
	ಆದರೆ (X*Y < One || X > Y) {
		ಆದರೆ (X * Y < U1 || X > Y/U1) BadCond(Defect, "Badly");
		ಇಲ್ಲದಿದ್ದರೆ BadCond(Flaw, "");
			
		ಬರೆ(" unbalanced range; UfThold * V = %d\n\t%s\n",
			X, "is too far from 1.\n");
		}
	/*=============================================*/
	Milestone = 200;
	/*=============================================*/
	ಗಾಗಿ (Indx = 1; Indx <= 5; ++Indx)  {
		X = F9;
		ಆಯ್ಕೆ (Indx)  {
			ಸ್ಥಿತಿ 2: X = One + U2; ನಿಲ್ಲಿಸು;
			ಸ್ಥಿತಿ 3: X = V; ನಿಲ್ಲಿಸು;
			ಸ್ಥಿತಿ 4: X = UfThold; ನಿಲ್ಲಿಸು;
			ಸ್ಥಿತಿ 5: X = Radix;
			}
		Y = X;
		sigsave = sigfpe;
		ಆದರೆ (setjmp(ovfl_buf))
			ಬರೆ("  X / X  traps when X = %d\n", X);
		ಇಲ್ಲದಿದ್ದರೆ {
			V9 = (Y / X - Half) - Half;
			ಆದರೆ (V9 == Zero) ಮುಂದುವರಿ;
			ಆದರೆ (V9 == - U1 && Indx < 5) BadCond(Flaw, "");
			ಇಲ್ಲದಿದ್ದರೆ BadCond(Serious, "");
			ಬರೆ("  X / X differs from 1 when X = %d\n", X);
			ಬರೆ("  instead, X / X - 1/2 - 1/2 = %d .\n", V9);
			}
		sigsave = 0;
		}
	/*=============================================*/
	Milestone = 210;
	/*=============================================*/
	MyZero = Zero;
	ಬರೆ("\n");
	ಬರೆ("What message and/or values does Division by Zero produce?\n") ;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NOPAUSE
	ಬರೆ("This can interupt your program.  You can ");
	ಬರೆ("skip this part if you wish.\n");
	ಬರೆ("Do you wish to compute 1 / 0? ");
	fflush(stdout);
	ಪಠ (KEYBOARD, ch, 8);
	ಆದರೆ ((ch[0] == 'Y') || (ch[0] == 'y')) {
#ಆದರೆ_ಅಂತ್ಯ
		sigsave = sigfpe;
		ಬರೆ("    Trying to compute 1 / 0 produces ...");
		ಆದರೆ (!setjmp(ovfl_buf)) ಬರೆ("  %d .\n", One / MyZero);
		sigsave = 0;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NOPAUSE
		}
	ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("O.K.\n");
	ಬರೆ("\nDo you wish to compute 0 / 0? ");
	fflush(stdout);
	ಪಠ (KEYBOARD, ch, 80);
	ಆದರೆ ((ch[0] == 'Y') || (ch[0] == 'y')) {
#ಆದರೆ_ಅಂತ್ಯ
		sigsave = sigfpe;
		ಬರೆ("\n    Trying to compute 0 / 0 produces ...");
		ಆದರೆ (!setjmp(ovfl_buf)) ಬರೆ("  %d .\n", Zero / MyZero);
		sigsave = 0;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NOPAUSE
		}
	ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("O.K.\n");
#ಆದರೆ_ಅಂತ್ಯ
	/*=============================================*/
	Milestone = 220;
	/*=============================================*/
	Pause();
	ಬರೆ("\n");
	{
		ಸ್ಥಿರ ಅಕ್ಷರ *ಸಂದೇಶ_2[] = {
			"FAILUREs  encountered =",
			"SERIOUS DEFECTs  discovered =",
			"DEFECTs  discovered =",
			"FLAWs  discovered =" };
		ಪೂರ್ಣಾಂಕ i;
		ಗಾಗಿ(i = 0; i < 4; i++) ಆದರೆ (ErrCnt[i])
			ಬರೆ("The number of  %-29s %d.\n",
				ಸಂದೇಶ_2[i], ErrCnt[i]);
		}
	ಬರೆ("\n");
	ಆದರೆ ((ErrCnt[Failure] + ErrCnt[Serious] + ErrCnt[Defect]
			+ ErrCnt[Flaw]) > 0) {
		ಆದರೆ ((ErrCnt[Failure] + ErrCnt[Serious] + ErrCnt[
			Defect] == 0) && (ErrCnt[Flaw] > 0)) {
			ಬರೆ("The arithmetic diagnosed seems ");
			ಬರೆ("Satisfactory though flawed.\n");
			}
		ಆದರೆ ((ErrCnt[Failure] + ErrCnt[Serious] == 0)
			&& ( ErrCnt[Defect] > 0)) {
			ಬರೆ("The arithmetic diagnosed may be Acceptable\n");
			ಬರೆ("despite inconvenient Defects.\n");
			}
		ಆದರೆ ((ErrCnt[Failure] + ErrCnt[Serious]) > 0) {
			ಬರೆ("The arithmetic diagnosed has ");
			ಬರೆ("unacceptable Serious Defects.\n");
			}
		ಆದರೆ (ErrCnt[Failure] > 0) {
			ಬರೆ("Potentially fatal FAILURE may have spoiled this");
			ಬರೆ(" program's subsequent diagnoses.\n");
			}
		}
	ಇಲ್ಲದಿದ್ದರೆ {
		ಬರೆ("No failures, defects nor flaws have been discovered.\n");
		ಆದರೆ (! ((RMult == Rounded) && (RDiv == Rounded)
			&& (RAddSub == Rounded) && (RSqrt == Rounded))) 
			ಬರೆ("The arithmetic diagnosed seems Satisfactory.\n");
		ಇಲ್ಲದಿದ್ದರೆ {
			ಆದರೆ (Sticky_ಬಿಟ್ >= One &&
				(Radix - Two) * (Radix - Nine - One) == Zero) {
				ಬರೆ("Rounding appears to conform to ");
				ಬರೆ("the proposed IEEE standard P");
				ಆದರೆ ((Radix == Two) &&
					 ((Precision - Four * Three * Two) *
					  ( Precision - TwentySeven -
					   TwentySeven + One) == Zero)) 
					ಬರೆ("754");
				ಇಲ್ಲದಿದ್ದರೆ ಬರೆ("854");
				ಆದರೆ (IEEE) ಬರೆ(".\n");
				ಇಲ್ಲದಿದ್ದರೆ {
					ಬರೆ(",\nexcept for possibly Double Rounding");
					ಬರೆ(" during Gradual Underflow.\n");
					}
				}
			ಬರೆ("The arithmetic diagnosed appears to be Excellent!\n");
			}
		}
	ಆದರೆ (fpecount)
		ಬರೆ("\nA total of %d floating point exceptions were registered.\n",
			fpecount);
	ಬರೆ("END OF TEST $\n");
  __asm__("ebreak");
	//return 0;
	}

/*SPLIT subs.c
#include "paranoia.h"
*/

 FLOAT
Sign (FP X)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KR_ಶೀರ್ಷಿಕೆಗಳು
FLOAT X;
#ಆದರೆ_ಅಂತ್ಯ
{ ಹಿಂತಿರುಗಿ X >= 0. ? 1.0 : -1.0; }

 ಶೂನ್ಯ
Pause(VOID)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NOPAUSE
	ಅಕ್ಷರ ch[8];

	ಬರೆ("\nTo continue, press RETURN");
	fflush(stdout);
	ಪಠ(KEYBOARD, ch, 8);
#ಆದರೆ_ಅಂತ್ಯ
	ಬರೆ("\nDiagnosis resumes after milestone Number %d", Milestone);
	ಬರೆ("          Page: %d\n\n", ಪುಟ_No);
	++Milestone;
	++ಪುಟ_No;
	}

 ಶೂನ್ಯ
TstCond (INT K, INT Valid, CHARP T)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KR_ಶೀರ್ಷಿಕೆಗಳು
ಪೂರ್ಣಾಂಕ K, Valid;
ಅಕ್ಷರ *T;
#ಆದರೆ_ಅಂತ್ಯ
{ ಆದರೆ (! Valid) { BadCond(K,T); ಬರೆ(".\n"); } }

 ಶೂನ್ಯ
BadCond(INT K, CHARP T)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KR_ಶೀರ್ಷಿಕೆಗಳು
ಪೂರ್ಣಾಂಕ K;
ಅಕ್ಷರ *T;
#ಆದರೆ_ಅಂತ್ಯ
{
	ಸ್ಥಿರ ಅಕ್ಷರ *ಸಂದೇಶ_2[] = { "FAILURE", "SERIOUS DEFECT", "DEFECT", "FLAW" };

	ErrCnt [K] = ErrCnt [K] + 1;
	ಬರೆ("%s:  %s", ಸಂದೇಶ_2[K], T);
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
	ಹಿಂತಿರುಗಿ(Random1);
	}

 ಶೂನ್ಯ
SqXMinX (INT Err_ಬಗೆ)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KR_ಶೀರ್ಷಿಕೆಗಳು
ಪೂರ್ಣಾಂಕ Err_ಬಗೆ;
#ಆದರೆ_ಅಂತ್ಯ
{
	FLOAT XA, XB;
	
	XB = X * BInvrse;
	XA = X - XB;
	SqEr = ((SQRT(X * X) - XB) - XA) / OneUlp;
	ಆದರೆ (SqEr != Zero) {
		ಆದರೆ (SqEr < MinSqEr) MinSqEr = SqEr;
		ಆದರೆ (SqEr > MaxSqEr) MaxSqEr = SqEr;
		J = J + 1.0;
		BadCond(Err_ಬಗೆ, "\n");
		ಬರೆ("sqrt( %d) - %016x  = %016x\n", X * X, X, OneUlp * SqEr);
		ಬರೆ("\tinstead of correct value 0 .\n");
		}
	}

 ಶೂನ್ಯ
NewD(VOID)
{
	X = Z1 * Q;
	X = FLOOR(Half - X / Radix) * Radix + X;
	Q = (Q - X * Z) / Radix + X * X * (D / Radix);
	Z = Z - Two * X * D;
	ಆದರೆ (Z <= Zero) {
		Z = - Z;
		Z1 = - Z1;
		}
	D = Radix * D;
	}

 ಶೂನ್ಯ
SR3750(VOID)
{
	ಆದರೆ (! ((X - Radix < Z2 - Radix) || (X - Z2 > W - Z2))) {
		I = I + 1;
		X2 = SQRT(X * D);
		Y2 = (X2 - Z2) - (Y - Z2);
		X2 = X8 / (Y - Half);
		X2 = X2 - Half * X2 * X2;
		SqEr = (Y2 + Half) + (Half - X2);
		ಆದರೆ (SqEr < MinSqEr) MinSqEr = SqEr;
		SqEr = Y2 - X2;
		ಆದರೆ (SqEr > MaxSqEr) MaxSqEr = SqEr;
		}
	}

 ಶೂನ್ಯ
IsYeqX(VOID)
{
	ಆದರೆ (Y != X) {
		ಆದರೆ (N <= 0) {
			ಆದರೆ (Z == Zero && Q <= Zero)
				ಬರೆ("WARNING:  computing\n");
			ಇಲ್ಲದಿದ್ದರೆ BadCond(Defect, "computing\n");
			ಬರೆ("\t(%d) ^ (%016x)\n", Z, Q);
			ಬರೆ("\tyielded %d;\n", Y);
			ಬರೆ("\twhich compared unequal to correct %d ;\n",
				X);
			ಬರೆ("\t\tthey differ by %d .\n", Y - X);
			}
		N = N + 1; /* ... count discrepancies. */
		}
	}

 ಶೂನ್ಯ
SR3980(VOID)
{
	ಮಾಡು {
		Q = (FLOAT) I;
		Y = POW(Z, Q);
		IsYeqX();
		ಆದರೆ (++I > M) ನಿಲ್ಲಿಸು;
		X = Z * X;
		} ಆಗ ( X < W );
	}

 ಶೂನ್ಯ
PrintIfNPositive(VOID)
{
	ಆದರೆ (N > 0) ಬರೆ("Similar discrepancies have occurred %d times.\n", N);
	}

 ಶೂನ್ಯ
TstPtUf(VOID)
{
	N = 0;
	ಆದರೆ (Z != Zero) {
		ಬರೆ("Since comparison denies Z = 0, evaluating ");
		ಬರೆ("(Z + Z) / Z should be safe.\n");
		sigsave = sigfpe;
		ಆದರೆ (setjmp(ovfl_buf)) ಹೋಗು very_serious;
		Q9 = (Z + Z) / Z;
		ಬರೆ("What the machine gets for (Z + Z) / Z is  %d .\n",
			Q9);
		ಆದರೆ (FABS(Q9 - Two) < Radix * U2) {
			ಬರೆ("This is O.K., provided Over/Underflow");
			ಬರೆ(" has NOT just been signaled.\n");
			}
		ಇಲ್ಲದಿದ್ದರೆ {
			ಆದರೆ ((Q9 < One) || (Q9 > Two)) {
very_serious:
				N = 1;
				ErrCnt [Serious] = ErrCnt [Serious] + 1;
				ಬರೆ("This is a VERY SERIOUS DEFECT!\n");
				}
			ಇಲ್ಲದಿದ್ದರೆ {
				N = 1;
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				ಬರೆ("This is a DEFECT!\n");
				}
			}
		sigsave = 0;
		V9 = Z * One;
		Random1 = V9;
		V9 = One * Z;
		Random2 = V9;
		V9 = Z / One;
		ಆದರೆ ((Z == Random1) && (Z == Random2) && (Z == V9)) {
			ಆದರೆ (N > 0) Pause();
			}
		ಇಲ್ಲದಿದ್ದರೆ {
			N = 1;
			BadCond(Defect, "What prints as Z = ");
			ಬರೆ("%d\n\tcompares different from  ", Z);
			ಆದರೆ (Z != Random1) ಬರೆ("Z * 1 = %d ", Random1);
			ಆದರೆ (! ((Z == Random2)
				|| (Random2 == Random1)))
				ಬರೆ("1 * Z == %d\n", Random2);
			ಆದರೆ (! (Z == V9)) ಬರೆ("Z / 1 = %d\n", V9);
			ಆದರೆ (Random2 != Random1) {
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				BadCond(Defect, "Multiplication does not commute!\n");
				ಬರೆ("\tComparison alleges that 1 * Z = %d\n",
					Random2);
				ಬರೆ("\tdiffers from Z * 1 = %d\n", Random1);
				}
			Pause();
			}
		}
	}

 ಶೂನ್ಯ
notify(CHARP s)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KR_ಶೀರ್ಷಿಕೆಗಳು
 ಅಕ್ಷರ *s;
#ಆದರೆ_ಅಂತ್ಯ
{
	ಬರೆ("%s test appears to be inconsistent...\n", s);
	ಬರೆ("   PLEASE NOTIFY KARPINKSI!\n");
	}

/*SPLIT msgs.c
#include "paranoia.h"
*/

 ಶೂನ್ಯ
msglist(CHARPP s)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KR_ಶೀರ್ಷಿಕೆಗಳು
ಅಕ್ಷರ **s;
#ಆದರೆ_ಅಂತ್ಯ
{ ಆಗ(*s) ಬರೆ("%s\n", *s++); }

 ಶೂನ್ಯ
Instructions(VOID)
{
  ಸ್ಥಿರ ಅಕ್ಷರ *instr[] = {
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

 ಶೂನ್ಯ
Heading(VOID)
{
  ಸ್ಥಿರ ಅಕ್ಷರ *ತಲೆ[] = {
	"Users are invited to help debug and augment this program so it will",
	"cope with unanticipated and newly uncovered arithmetic pathologies.\n",
	"Please send suggestions and interesting results to",
	"\tRichard Karpinski",
	"\tComputer Center U-76",
	"\tUniversity of California",
	"\tSan Francisco, CA 94143-0704, USA\n",
	"In doing so, please include the following information:",
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ Single
	"\tPrecision:\tsingle;",
#ಇಲ್ಲದಿದ್ದರೆ
	"\tPrecision:\tdouble;",
#ಆದರೆ_ಅಂತ್ಯ
	"\tVersion:\t10 February 1989;",
	"\tComputer:\n",
	"\tCompiler:\n",
	"\tOptimization level:\n",
	"\tOther relevant compiler options:",
	0};

	msglist(ತಲೆ);
	}

 ಶೂನ್ಯ
Characteristics(VOID)
{
	ಸ್ಥಿರ ಅಕ್ಷರ *chars[] = {
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

 ಶೂನ್ಯ
History(VOID)
{ /* History */
 /* Converted from Brian Wichmann's Pascal version to C by Thos Sumner,
	with further massaging by David M. Gay. */

  ಸ್ಥಿರ ಅಕ್ಷರ *hist[] = {
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
