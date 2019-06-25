/* 
 * CS:APP Data Lab 
 * 
 * <Summer Thompson, SUTH9598>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
    /*inverse both variables then combine, return the inverse of that*/
    int varx=~x;
    int vary=~y;
    int z = varx&vary;
    return ~z;
}
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
    /* create two bits of all even number bits set to one and shift it to form a full word*/
    int p= 0x55;
    return (p<<24)+(p<<16)+(p<<8)+(p);
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
    int x = 0;
  return (~x);
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
    /*create mask of number with all even bits set to 1, or it with x, return not the inverse to tell if true or false*/
    int z=0xAA;
    int y= (z<<24)+(z<<16)+(z<<8)+z; /*num with even bits set to 1*/
    int q=(x|y); /*even bits of x that were 1 */
    int p=~q; /*will be all 0s if even bits were 1*/
    return !p;
   
}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
    /*create word of all odd bits set to one, and with x, and use double logical not to tell if any of the odd bits were true*/
    int z = 0xAA;
    int y= (z<<24)+(z<<16)+(z<<8)+z; /*num with odd bits set to 1*/
    int l=!!(x&y);
    return l;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    /*isolate bytes to be swapped, move them to complementary position, and with x and mask to get result*/
    int sn=n<<3; 
    int sm=m<<3;
    int p = (x>>sn)&0xff;
    int q = (x>>sm)&0xff;
    int r = ~((0xff<<sn)|(0xff<<sm)); /*all ff except spots to swap*/
    return ((x&r)|(q<<sn)|(p<<sm));
    
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
    /*check most significant bytes of numbers with a mask, compare with actual sum of numbers, return if msbs and sum match or if not*/
    int mask= 1<<31; /*mask to check msb*/
    int q=!((x&mask)^(y&mask));/*same sign would yeild 1000 <<31, different would yeild 0000*/
    int sum = x+y; /*find actual sum*/
    int p=!!((sum&mask)^(x&mask));/*check if sum has same sign as x.  return 1 if yes, 0 if no*/
    return !(q&p);  /* if both q is 0, meaning x&y have different signs regardless of result of p, return 1, or if q and p are both true, result will be 0*/
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*if x is non zero, return y else return z*/
    int xt = !!x; /*return 1 if x is true, 0 if false*/
    int q= ~xt+1; /*~1 = -2+1 = -1 ie mask of all 1s if x is true, ~0=-1 + 1= 0 ie mask of all 0s if x is false*/
    return (y&q)|(z&~q);
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    /*check x against upper and lower bounds using not +num, combine these results with mask to check against upper and lower bounds and return the and of these two varialbles*/
    int high, low, cHigh, cLow;
    int mask = 1;
    mask<<=31;//first we make a mask that's all 1s
    high = ~x+58;//we make a variable for our upper bound, the result should be greater than 0. 58 because it's 1+0x39
    low = ~x+48;/*create lower limit value*/
    cHigh = !(high&mask);//first we use & to see if the sign of our high value and the sign of our mask. We use ! to get a 0 or 1. A return of true should be 1 since we only have a single !
    cLow = !!(low&mask);//we do the same operation except on we use 2 !! so that the value will be 1 if true
    return (cHigh&cLow);
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
    /*create mask over n bit, move new bit to that position, use and to combine x and mask and or to combine with new masked byte*/
    int sn=n<<3;
    int p = x&~(0xff<<sn); /*create mask over n bit */
    int cp = c<<sn; /*move c over to n position*/
    return (x&p)|cp;
    
}
/* reverseBits - reverse the bits in a 32-bit integer,
              i.e. b0 swaps with b31, b1 with b30, etc
 *  Examples: reverseBits(0x11111111) = 0x88888888
 *            reverseBits(0xdeadbeef) = 0xf77db57b
 *            reverseBits(0x88888888) = 0x11111111
 *            reverseBits(0)  = 0
 *            reverseBits(-1) = -1
 *            reverseBits(0x9) = 0x90000000
 *  Legal ops: ! ~ & ^ | + << >> and unsigned int type
 *  Max ops: 90
 *  Rating: 4
 */
int reverseBits(int x) {
    /*use series of masks to swap and shift bits over and reverse */
    int word =x; /* first we swap odd and even bits by using 0x55555555 = 10101010.... and shifting all the bits to the right first and masking, then shifting to the left and mask and then take the | of the two so that they are all swapped*/
    word = ((word>>1) & 0x55555555) | ((word&0x55555555) <<1); /*next swap pairs of bits in the same way, using 0x33333333 = 0011001100110011. then shift over 2 so that we swap all the pairs of bits */
    word = ((word>>2) & 0x33333333) | ((word&0x33333333) <<2); 
    /*now swap sets of 4 bits using 0x0F0F0F0F = 0000111100001111 */
    word = ((word>>4) & 0x0F0F0F0F) | ((word&0x0F0F0F0F) <<4); /*now we swap the bytes with 0x00FF00FF = 0000000011111111 */
    word = ((word>>8) & 0x00FF00FF) | ((word&0x00FF00FF) <<8);
    /*finally we swap the first half with the second half using 0xffff = 1111111111111111 */
    word = ((word>>16) & 0xffff) | ((word&0xffff) <<16);
    return word;
}
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
    /*compare actual sum with the two variables and compare with og x and y and combine.  Then check msb to see what the numbers were and return mins or maxes accordingly*/
    int sum = x+y;/*first we hold the sum of x and y to compare later*/
	int check=(sum^x)&(sum^y);/*checks whether the sign of the sum is the same as the sign of x. If the signs are different then we should get all 1s. We do the same with y and the we check if both these values have the same sign with one more & operator*/
    check = check>>31;/*shift this number over so we just have a single sign bit*/
	return (sum>>(check & 31)) + (check <<31);/*if there is no overflow 'sum' should be 0 so we will just return the sum of the two numbers like normal. If there is overflow the 'sum' will be all 1s we shift over by 31 bits and add all 1s. If we have negative overflow the sum will be a positive, in that case we will return the minimum value of 0*/

}
/*
 * Extra credit
 */
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  return 2;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  return 2;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  return 2;
}
