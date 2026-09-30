/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~(x & ~y) & ~(~x & y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int mask = x >> 31;
  return mask & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int byte = (x >> (src << 3)) & 0xFF;
  int shifted = byte << (dst << 3);
  int mask = ~(0xFF << (dst << 3));
  return (x & mask) | shifted;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int shifted = x >> n;
  int mask = ~(((1 << 31) >> n) << 1);
  return shifted & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int low = 0x0F | (0x0F << 8) | (0x0F << 16) | (0x0F << 24);
  return ((x & low) << 4) | ((x >> 4) & low);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int t = x | (x + 1);
  return ~t & (t + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  // 偶数个 1 返回 1，奇数个 1 返回 0 
  return ~x & 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int m = n & 31;
  int s = (32 + ~m + 1) & 31;
  int mask = ~((~0) << s);
  return ((x >> m) & mask) | (x << s);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) { 
  int mask = (1 << n) + ~0; // 构造低 n 位全 1 的掩码，用于取余数
  int half = 1 << (n + ~0); // 计算半程值 2^(n-1)
  int rem = x & mask; // 取出 x 除以 2^n 的余数
  int base = x >> n; // 取出 x 除以 2^n 的商（向下取整）
  int geHalf = ((rem + half) >> n) & 1; // 判断余数是否大于等于半程：是则 1，否则 0
  int tie = !(rem ^ half); // 判断是否恰好在中点：是则 1，否则 0
  int odd = base & 1; // 判断商是否为奇数：奇数则 1，偶数则 0
  int tieMask = ~tie + 1; // 中点时生成全 1 掩码，否则全 0
  int up = (tieMask & odd) | (~tieMask & geHalf); 
  // 决定是否进位：中点看商奇偶，非中点看余数是否过半
  return (base + up) << n; // 进位后的商乘以 2^n，得到最终结果
} 

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int mid = (x & y) + ((x ^ y) >> 1); // 计算 floor((x+y)/2)，不会溢出
  int odd = (x ^ y) & 1;              // 判断 x+y 是否为奇数：奇数则 odd=1
  int sx = x >> 31;                   // 取 x 的符号位：非负为 0，负为 -1（全1）
  int sy = y >> 31;                   // 取 y 的符号位
  int diff = x + ~y + 1;              // 计算 x - y（~y+1 就是 -y）
  int same = ~(sx ^ sy);              // 判断 x、y 是否同号：同号则全1，异号则全0
  int gt = (same & ~(diff >> 31)) | (~same & ~sx); // 计算 x > y 的条件，gt 全1表示 x>y
  return mid + (odd & gt & 1);        
  // 若 x+y 为奇数且 x>y，则中点向上取整（mid+1），否则返回 mid
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) { 
  int ax = a + ~x + 1; // 计算 a - x
  int bx = b + ~x + 1; // 计算 b - x
  int xor_ax = a ^ x; // a 和 x 的异或，用于判断是否异号
  int xor_bx = b ^ x; // b 和 x 的异或
  int sign_ax = ((xor_ax >> 31) & (a >> 31)) | (~(xor_ax >> 31) & (ax >> 31)); 
  // 修正 ax 的真实符号位
  int sign_bx = ((xor_bx >> 31) & (b >> 31)) | (~(xor_bx >> 31) & (bx >> 31)); 
  // 修正 bx 的真实符号位
  int diff = (sign_ax ^ sign_bx) >> 31; // 如果两个符号位不同，diff 为全 1，否则为 0
  int zero = !ax | !bx; // 如果 ax == 0 或 bx == 0，说明 x 等于 a 或 b
  return (diff & 1) | zero; // 符号不同或等于端点时返回 1，否则返回 0
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) { 
  int posLimit = 0x19 | (0x99 << 8) | (0x99 << 16) | (0x19 << 24); 
  // 正溢出阈值 0x19999999
  int negLimit = ~posLimit; 
  // 负溢出阈值相关值 0xE6666666
  int sx = x >> 31; // x 的符号位：0 表示非负，-1 表示负
  int posOvf = ~sx & ~((x + negLimit) >> 31); // 正溢出：x 非负且 x > 0x19999999
  int negOvf = sx & ((x + posLimit) >> 31); // 负溢出：x 为负且 x < 0xE6666667
  int ovf = posOvf | negOvf; // 溢出标志：全 1 表示溢出，全 0 表示未溢出
  int intMax = ~(1 << 31); // INT_MAX = 0x7FFFFFFF
  int intMin = 1 << 31; // INT_MIN = 0x80000000
  int sat = (posOvf & intMax) | (negOvf & intMin); // 根据溢出方向选择饱和值
  int res = (x << 2) + x; // 计算 x*5 的 32 位结果
  return (ovf & sat) | (~ovf & res); // 溢出则返回饱和值，否则返回计算结果
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int s1 = x + y;                                    // x+y 的低 32 位
  int c1 = (((x & y) | ((x | y) & ~s1)) >> 31) & 1;   // x+y 的无符号进位（0 或 1）
  int s2 = s1 + z;                                    // (x+y)+z 的低 32 位
  int c2 = (((s1 & z) | ((s1 | z) & ~s2)) >> 31) & 1;// 第二次加法的无符号进位（0 或 1）
  int sx = x >> 31;                                // x 的符号扩展（0 或 -1）
  int sy = y >> 31;                               // y 的符号扩展
  int sz = z >> 31;                                 // z 的符号扩展
  int hi = sx + sy + sz + c1 + c2;                  // 64 位和的高 32 位
  int hip1 = hi + 1;                     // hi + 1，方便判断 hi == -1 和 hi < -1
  int hiPos = ~(hi >> 31) & !!hi;                    // hi > 0 时为 1
  int hiZero = !hi;                                 // hi == 0 时为 1
  int hiNegOne = !hip1;                             // hi == -1 时为 1
  int hiLtNegOne = (hip1 >> 31) & !!hip1;           // hi < -1 时为 1
  int s2neg = (s2 >> 31) & 1;                        // s2 < 0 时为 1
  int posOvf = hiPos | (hiZero & s2neg);             // 正溢出：hi>0，或 hi==0 且 s2<0
  int negOvf = hiLtNegOne | (hiNegOne & !s2neg);  // 负溢出：hi<-1，或 hi==-1 且 s2>=0
  return posOvf | (negOvf << 31 >> 31);     // 正溢出返回 1，负溢出返回 -1，无溢出返回 0
}
// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000; // 取出符号位
  unsigned exp = (uf >> 23) & 0xFF; // 取出 8 位阶码
  unsigned frac = uf & 0x7FFFFF; // 取出 23 位尾数

  if (exp == 0xFF) return uf; // NaN 或 Inf，直接返回原值
  if (exp == 0 && frac == 0) return uf; // ±0，直接返回原值

  unsigned mant; // 用来保存还原后的尾数
  int e; // 实际指数
  if (exp == 0) { // 非规格化数
    mant = frac; // 尾数就是 frac，没有隐藏的 1
    e = -126; // 非规格化数的实际指数固定为 -126
  } else { // 规格化数
    mant = (1 << 23) | frac; // 加上隐藏的最高位 1
    e = exp - 127; // 实际指数 = 阶码 - 偏移量 127
  }

  unsigned prod = mant * 3; // 先计算 mant * 3
  unsigned q = prod >> 1; // 除以 2 的整数部分
  unsigned r = prod & 1; // 除以 2 的余数（是否丢了 0.5）

  unsigned result; // 舍入后的尾数结果
  int exp_inc = 0; // 指数是否需要加 1

  if (q < (1u << 24)) { // 如果 q 还没超过 24 位
    result = q + (r & q & 1); // round-to-nearest-even：余数为 1 且 q 为奇数时进位
  } else { // q 超过 24 位，需要再右移一位
    unsigned q2 = q >> 1; // 再除以 2 的整数部分
    unsigned r2 = q & 1; // 再除以 2 的余数
    result = (r == 0) ? (q2 + (r2 & q2 & 1)) : (q2 + r2); // 根据 r 分情况舍入
    exp_inc = 1; // 因为右移了一位，指数要加 1
  }

  e += exp_inc; // 更新实际指数

  if (result >= (1u << 23)) { // 如果尾数达到 24 位，说明是规格化数
    exp = e + 127; // 重新计算阶码
    if (exp >= 0xFF) return sign | 0x7F800000; // 阶码上溢，返回无穷
    if (exp <= 0) return sign | result; // 阶码下溢，返回非规格化数形式
    return sign | (exp << 23) | (result & 0x7FFFFF); // 拼回规格化浮点数
  } else { // 否则是非规格化数
    return sign | result; // 直接拼回非规格化浮点数
  }
}
  


// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;

  if (exp == 0xFF) return uf; // NaN 或 Inf，原样返回
  if (exp == 0) return sign;  // 非规格化数，绝对值 < 2^-126，舍入到 0

  int e = exp - 127;
  if (e >= 23) return uf;     // 已经是整数，不需要舍入
  if (e < -1) return sign;    // |v| < 0.5，舍入到 0

  if (e == -1) {
    // v = 0.5 + frac/2^24
    if (frac == 0) return sign;        // 恰好 0.5，舍入到偶数 0
    return sign | 0x3F800000;          // 大于 0.5，舍入到 1.0
  }

  // e >= 0
  int shift = 23 - e;
  unsigned rem = frac & ((1 << shift) - 1);   // 小数部分
  unsigned half = 1 << (shift - 1);           // 半程
  unsigned base = (1 << e) + (frac >> shift); // 整数部分的值（含隐含的 1）

  // 最近偶数舍入
  if (rem > half || (rem == half && (base & 1))) {
    base++;
  }

  if (base == 0) return sign;

  // 将整数 base 重新转换为浮点数
  int k = 31;
  while (!(base & (1 << k))) k--; // 找最高位
  int E = k;
  unsigned new_frac;
  if (k <= 23) {
    new_frac = (base << (23 - k)) & 0x7FFFFF;
  } else {
    new_frac = (base >> (k - 23)) & 0x7FFFFF;
  }
  int new_exp = E + 127;
  if (new_exp >= 0xFF) return sign | 0x7F800000;
  return sign | (new_exp << 23) | new_frac;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  if (x == 0) return 0;
  unsigned sign = (x >> 31) & 0x80000000; // 符号位
  unsigned abs = x;
  if (x < 0) abs = ~x + 1; // 取绝对值，INT_MIN 也正确
  int e = 31;
  while (!(abs & (1 << e))) e--; // 找最高有效位
  unsigned frac;
  if (e <= 23) {
    frac = (abs << (23 - e)) & 0x7FFFFF; // 左移对齐，无需舍入
  } else {
    int shift = e - 23;
    unsigned shifted = abs >> shift; // 保留的高位
    unsigned rem = abs & ((1 << shift) - 1); // 移出的低位
    unsigned half = 1 << (shift - 1); // 半程
    frac = shifted & 0x7FFFFF; // 取低 23 位作为尾数
    // 最近偶数舍入
    if (rem > half || (rem == half && (frac & 1))) {
      frac++;
      if (frac & 0x800000) { // 尾数进位到第 24 位
        frac = 0; // 尾数清零
        e++; // 指数加一
      }
    }
  }
  unsigned exp = e + 127;
  if (exp >= 0xFF) return sign | 0x7F800000; // 溢出为无穷
  return sign | (exp << 23) | frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1 = 0x55 | (0x55 << 8) | (0x55 << 16) | (0x55 << 24);
  int m2 = 0x33 | (0x33 << 8) | (0x33 << 16) | (0x33 << 24);
  int m4 = 0x0F | (0x0F << 8) | (0x0F << 16) | (0x0F << 24);
  int m8 = 0xFF | (0xFF << 16);
  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x & m4) + ((x >> 4) & m4);
  x = (x + (x >> 8)) & m8;
  x = (x + (x >> 16)) & 0x3F;
  return x;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x) {
  int m1 = 0x55 | (0x55 << 8) | (0x55 << 16) | (0x55 << 24); // 0x55555555
  int m2 = 0x33 | (0x33 << 8) | (0x33 << 16) | (0x33 << 24); // 0x33333333
  int m4 = 0x0F | (0x0F << 8) | (0x0F << 16) | (0x0F << 24); // 0x0F0F0F0F
  int m8 = 0xFF | (0xFF << 16);                               // 0x00FF00FF
  int m16 = 0xFF | (0xFF << 8);                               // 0x0000FFFF

  x = ((x >> 1) & m1) | ((x & m1) << 1); // 交换相邻 1 位
  x = ((x >> 2) & m2) | ((x & m2) << 2); // 交换相邻 2 位
  x = ((x >> 4) & m4) | ((x & m4) << 4); // 交换相邻 4 位
  x = ((x >> 8) & m8) | ((x & m8) << 8); // 交换相邻 8 位
  x = (x << 16) | ((x >> 16) & m16);     // 交换高低 16 位，逻辑右移
  return x;
}