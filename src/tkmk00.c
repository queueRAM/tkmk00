#include "utils.h"

static i32 a0, a1, a2, a3, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, s0, s1, s2, s3, s4, s5, s6, s7, v0, v1, sp;

static int proc_80040A60(void);
static int proc_80040AC8(void);
static int proc_80040BC0(void);
static void proc_80040C54(void);
static int proc_80040C94(void);

// a0[in]: pointer to TKMK00 data
// a1[out]: pointer to output (a0->h8*a0->hA words)
// a2[out]: pointer to output (a0->h8*a0->hA*2 words)
// a3[in]: byte? values observed: 0x01, 0xBE
void tkmk00decode(u8 *a0p, u8 *a1p, u8 *a2p, u32 a3p)  // 800405D0/0411D0
{
   // 0x400 allocated on stack
   //   000-07F: 0x20 words
   //   080-11F: ?
   //   120-13F: 8 words
   //   140-1DF: ?
   //   1E0-1EF: 4 words addressed individually
   //   1F0-3FF: ?
   u8 sp000[0x400];
   
   // assign globals to params
   sp = (i32)&sp000;
   a0 = (i32)a0p;
   a1 = (i32)a1p;
   a2 = (i32)a2p;
   a3 = a3p;

   t4 = read_u16_be(a0 + 0x8);
   t3 = read_u16_be(a0 + 0xA);
   s2 = a3;
   t2 = *(u8*)(a0 + 0x6);
   t8 = -1;
   t9 = sp;
   s7 = 0x20;
   t0 = t4 * t3;
   while (s7 != 0) { // .Ltkmk00decode_48: # 80040618
      s7 -= 1;
      write_u32_be(t9, t8);
      t9 += 4;
   }
   
   s4 = t0;
   s6 = a2;
   while (s4 > 0) { // .Ltkmk00decode_64: # 80040634
      s4 -= 2;
      write_u32_be(s6, 0x0);
      s6 += 4;
   }
   
   s7 = t0;
   t8 = a1;
   while (s7 > 0) { // .Ltkmk00decode_7C: # 8004064C
      s7 -= 4;
      write_u32_be(t8, 0x0);
      t8 += 4;
   }
  
   s4 = sp + 0x1C0;
   s6 = 8;
   a3 = a0 + 0xC;
   s5 = t2; // above: t2 = (u8)(a0 + 0x6)
   do { // Ltkmk00decode_9C
       s7 = read_u32_be(a3);
       v0 = s5 & 1;
       s7 += a0;
       if (v0 == 0) {
          s7 -= 4;
       }
       s6 -= 1;
       s5 >>= 1;
       write_u32_be(s4, s7);
       a3 += 4;
       s4 += 4;
   } while (s6 != 0);

   write_u32_be(sp + 0x1E0, 0x0);
   write_u32_be(sp + 0x1E4, 0x0);
   write_u32_be(sp + 0x1E8, 0x0);
   write_u32_be(sp + 0x1EC, 0x0);
   s3 = sp;
   a3 = 0x0;
   t0 = read_u32_be(a0 + 0x2C);
   a0 += 0x30;
   s3 += 0x3F0;
   s4 = 0x20;
   v0 = proc_80040BC0();  // stores increments of s4 to s3. recursive
   
   t1 = v0;
   t5 = 0;
   t6 = 0;
   t7 = 0;

   do {
      do  { // .Ltkmk00decode_104: # 800406D4
         t9 = read_u16_be(a2);
         
         if (t9 == 0) {
            v1 = *(u8*)a1; // likely BDS
         } else {
            s3 = t9 & 0xFFFE;
            t7 = t9;
            if (s2 != s3) {
               goto tkmk00decode_448;
            }
            write_u16_be(a2, s3);
            t7 = s3;
            goto tkmk00decode_448;
         } // Ltkmk00decode_12C
         v1 += 1;
         v0 = proc_80040AC8();
         
         if (v0 == 0) {
            write_u16_be(a2, t7);
            goto tkmk00decode_448;
         } // Ltkmk00decode_144
         
         v1 = 1;
         v0 = proc_80040A60();
         
         if (v0 != 0) {
            proc_80040C54();
            
            s0 = s4;
            proc_80040C54();
            
            s1 = s4;
            proc_80040C54();
            
            s5 = 0;
            s6 = 0;
            if (t6 != 0) {
               s3 = t4 << 1;
               t9 = a2 - s3;
               s5 = read_u16_be(t9);
               s6 = read_u16_be(a2 - 2);
            } else { // .Ltkmk00decode_18C: # 8004075C
               if (t5 != 0) {
                  s6 = read_u16_be(a2 - 2);
               }
            } // .Ltkmk00decode_198: # 80040768
            t8 = s5 & 0x7C0; // this is also performed in beql at Ltkmk00decode_18C
            t9 = s6 & 0x7C0;
            t8 >>= 6;
            t9 >>= 6;
            t8 += t9;
            t8 >>= 1;
            t9 = s0;
            proc_80040C94();
            
            v1 = t9 - t8;
            s0 = t9;
            t8 = s5 & 0xF800;
            t9 = s6 & 0xF800;
            t8 >>= 11;
            t9 >>= 11;
            t8 += t9;
            t8 >>= 1;
            t8 += v1;
            if (t8 >= 0x20) {
               t8 = 0x1F;
            } else if (t8 < 0) {
               t8 = 0;
            }
            t9 = s1;
            proc_80040C94();
            s1 = t9;
            t8 = s5 & 0x3E;
            t9 = s6 & 0x3E;
            t8 >>= 1;
            t9 >>= 1;
            t8 += t9;
            t8 >>= 1;
            t8 += v1;
            
            if (t8 >= 0x20) {
               t8 = 0x1F;
            } else if (t8 < 0) {
               t8 = 0;
            }
            t9 = s4;
            proc_80040C94();
            
            s0 <<= 6;
            s1 <<= 11;
            t9 <<= 1;
            t8 = s0 | s1;
            t7 = t8 | t9;
            
            s5 = 0x3F; // likely BDS and below
            if (t7 != s2) {
               t7 |= 0x1;
            } // .Ltkmk00decode_270: # 80040840
            s6 = sp + 0x7C;
            
            // like an overlapped memmove, shifting everything by two bytes right
            do {
               s7 = read_u16_be(s6);
               s5 -= 1;
               s6 -= 2;
               write_u16_be(s6 + 4, s7);
            } while (s5 != 0);
            write_u16_be(s6 + 2, t7);
         } else { // .Ltkmk00decode_290: # 80040860
            v1 = 6;
            v0 = proc_80040A60();
            v0 <<= 1;
            s6 = sp + v0; // s6 = sp + v0
            t7 = read_u16_be(s6);
            if (v0 != 0) {
               do { // .Ltkmk00decode_2A8: # 80040878
                  s7 = read_u16_be(s6 - 2);
                  s6 -= 2;
                  write_u16_be(s6 + 2, s7);
               } while (s6 != sp);
               write_u16_be(s6, t7);
            }
         } // .Ltkmk00decode_2BC: # 8004088C
         write_u16_be(a2, t7);
         t9 = 0;
         if (t5 != 0) {
            t9 |= 0x01;
         }
         s5 = t4 - 1;
         if (t5 < s5) { // .Ltkmk00decode_2CC: # 8004089C
            t9 |= 0x02;
         } 
         s6 = t4 - 2;
         if (t5 < s6) { // .Ltkmk00decode_2E4: # 800408B4
            t9 |= 0x04;
         }
         s5 = t3 - 1;
         if (t6 < s5) { // .Ltkmk00decode_2F8: # 800408C8
            t9 |= 0x08;
         }
         s6 = t3 - 2;
         if (t6 < s6) { // .Ltkmk00decode_30C: # 800408DC
            t9 |= 0x10;
         } // .Ltkmk00decode_320: # 800408F0

         s7 = t9 & 0x2;
         if (s7 == 2) {
            s4 = *(u8*)(a1 + 1);
            s4 += 1;
            *(u8*)(a1 + 1) = s4;
         } 

         s6 = t9 & 0x4;
         if (s6 == 4) { // .Ltkmk00decode_33C: # 8004090C
            s4 = *(u8*)(a1 + 2);
            s4 += 1;
            *(u8*)(a1 + 2) = s4;
         }
         
         s7 = t9 & 0x9;
         s5 = a1 + t4;
         if (s7 == 9)  {
            s4 = *(u8*)(s5 - 1);
            s4 += 1;
            *(u8*)(s5 - 1) = s4;
         }
         
         // .Ltkmk00decode_370: # 80040940
         s6 = t9 & 0x8;
         if (s6 == 8) {
            s4 = *(u8*)(s5);
            s4 += 1;
            *(u8*)(s5) = s4;
         }
         
         s7 = t9 & 0xA;
         if (s7 == 0xA) { // .Ltkmk00decode_390: # 80040960
            s4 = *(u8*)(s5 + 1);
            s4 += 1;
            *(u8*)(s5 + 1) = s4;
         }
         
         s7 = t9 & 0x10;
         s6 = s5 + t4;
         if (s7 == 0x10) { // .Ltkmk00decode_3AC: # 8004097C
            s4 = *(u8*)(s6);
            s4 += 1;
            *(u8*)(s6) = s4;
         } // .Ltkmk00decode_3C4: # 80040994
         
         v1 = 1;
         v0 = proc_80040A60();
         
         if (v0 != 0) {
            s1 = a2;
            s0 = t4 << 1;
            s3 = t7 | 0x1;
            
            do { // .Ltkmk00decode_3E0: # 800409B0
               v1 = 2;
               v0 = proc_80040A60();
               if (v0 == 0) { // bnezl $v0, .Ltkmk00decode_41C
                  v1 = 1;
                  v0 = proc_80040A60();
  
                  if (v0 == 0) {
                     break; // beql  $v0, $zero, .Ltkmk00decode_44C
                  } else {
                     v1 = 1;
                     v0 = proc_80040A60();
                     s1 += 4;
                     if (v0 == 0) {
                        s1 -= 8;
                     }
                     // b     .Ltkmk00decode_43C
                  }
               } else if (v0 == 1) { // .Ltkmk00decode_41C: # 800409EC
                  s1 -= 2;
                  // b     .Ltkmk00decode_43C
               } else if (v0 == 3) { // .Ltkmk00decode_430: # 80040A00
                  s1 += 2;
               } // .Ltkmk00decode_43C: # 80040A0C
               s1 += s0;
               write_u16_be(s1, s3);
            } while (1); // b     .Ltkmk00decode_3E0
         }
tkmk00decode_448:
         t5 += 1; // likely BDS
         a1 += 1;
         a2 += 2;
      } while (t5 != t4);
      t6 += 1;
      t5 = 0;
   } while (t6 != t3);
} // tkmk00decode

// inputs: a0, a3, v1, t0
// outputs: a0, a3, t0, t8, t9, v0
static int proc_80040A60(void) // 80040A60/041660
{
   t9 = a3 + v1;
   t8 = 0x20;
   t8 -= v1;
   v0 = t0 >> t8;
   if (t9 < 0x21) {
      if (t9 != 0x20) {
         t0 <<= v1;
         a3 += v1;
         return v0;
      } else { // .Lproc_80040A60_34: # 80040A94
         t0 = read_u32_be(a0); // likely BDS
         a3 = 0;
         a0 += 4;
         return v0;
      }
   } else { // .Lproc_80040A60_40: # 80040AA0
      t9 = 0x40;
      t0 = read_u32_be(a0);
      t9 -= v1;
      t9 -= a3;
      a3 -= t8;
      t8 = t0 >> t9;
      v0 |= t8;
      a0 += 4;
      t0 <<= a3;
      return v0;
   }
} // proc_80040A60

// inputs: t2, v1
// outputs: t8, t9, s6, s7, v0
static int proc_80040AC8(void) // 80040AC8/0416C8
{
   t8 = t2 >> v1;
   t9 = t8 & 0x1;
   s7 = v1 << 1;
   t8 = sp + s7;
   s7 = read_u16_be(t8 + 0x1E0);
   if (t9 == 0) {
      t9 = v1 << 2;
      t9 += sp;
      s6 = read_u32_be(t9 + 0x1C0);
      if (s7 == 0) {
         s6 += 4;
         s7 = 0x20;
         write_u32_be(t9 + 0x1C0, s6);
      } // Lproc_80040AC8_34
      t9 = read_u32_be(s6);
      s7 -= 1;
      write_u16_be(t8 + 0x1E0, s7);
      v0 = t9 >> s7;
      v0 &= 0x1;
      return v0;
   } // Lproc_80040AC8_4C
   t9 = v1 << 2;
   t9 += sp;
   s5 = sp + v1;
   s6 = read_u32_be(t9 + 0x1C0);
   if (s7 == 0) {
      s7 = *(i8*)s6;
      v0 = 0x100;
      v0 <<= v1; // likely BDS
      if ((s7 & 0x80) == 0x00) { // if (s7 >= 0) {
         v0 = ~v0;
         s7 += 3;
         t2 &= v0;
      } else { // .Lproc_80040AC8_88: # 80040B50
         s7 &= 0x7F;
         s7 += 1;
         t2 |= v0;
      } // .Lproc_80040AC8_94: # 80040B5C
      v0 = *(u8*)(s6 + 1);
      s6 += 2;
      s7 <<= 3;
      *(u8*)(s5 + 0x1A0) = v0;
      write_u32_be(t9 + 0x1C0, s6);
   } // .Lproc_80040AC8_A8: # 80040B70
   v0 = *(u8*)(s5 + 0x1A0);
   s7 -= 1;
   write_u16_be(t8 + 0x1E0, s7);
   t8 = s7 & 0x7;
   v0 >>= t8;
   v0 &= 0x1;
   if (t8 == 0 && s7 != 0) {
      t8 = 0x100;
      s7 = t8 << v1;
      s7 &= t2;
      if (s7 != 0) {
         s7 = *(u8*)(s6);
         s6 += 1;
         *(u8*)(s5 + 0x1A0) = s7;
         write_u32_be(t9 + 0x1C0, s6);
      }
   } // .Lproc_80040AC8_F0: # 80040BB8
   return v0;
} // proc_80040AC8

// inputs: s3, s4
// outputs: v0, v1, s0, s1, s3, s4, s5
static int proc_80040BC0(void) // 80040BC0/0417C0
{
   // s3 used like stack
   // save RA
   s3 -= 8;
   v1 = 0;
   v0 = proc_80040AC8();

   s0 = 0;
   if (v0 != 0) {
      write_u32_be(s3 + 4, s4);
      s4 += 1;
      proc_80040BC0();
      s5 = read_u32_be(s3 + 4);
      s5 <<= 1;
      s5 += sp;
      write_u16_be(s5 + 0x80, v0);
      proc_80040BC0();
      s5 = read_u32_be(s3 + 4);
      s3 += 8;
      s6 = s5;
      s5 <<= 1;
      s5 += sp;
      write_u16_be(s5 + 0xFE, v0);

      // restore RA
      v0 = s6;
      return v0;
   }
   s1 = 5;
   do {
      v1 = 0;
      proc_80040AC8();
      s0 <<= 1;
      s1 -= 1;
      s0 += v0;
   } while (s1 != 0);
   // restore RA
   s3 += 8;
   v0 = s0;
   return v0;
} // proc_80040BC0

// inputs: t1
// outputs: s4, v0
static void proc_80040C54(void) // 80040C54/041854
{
   s4 = t1;
   while (s4 < 0x20) {
      v1 = 0;
      v0 = proc_80040AC8();
      v1 = s4 << 1;
      t8 = sp + v1;
      // TODO: read_s16_be ?
      if (v0 == 0) {
         s4 = read_u16_be(t8 + 0x80);
      } else {
         s4 = read_u16_be(t8 + 0xFE);
      }
   }
} // proc_80040C54

// inputs: t8, t9
// outputs: v0, t9
static int proc_80040C94(void) // 80040C94/041894
{
   if (t8 >= 0x10) {
      v0 = 0x1F;
      v0 -= t8;
      v0 <<= 1;
      if (v0 < t9) {
         v0 = t9 & 0x1; // BDS
         v0 = 0x1F;
         t9 = v0 - t9;
         return v0;
      } // .Lproc_80040C94_34: # 80040CC8
Lproc_80040C94_34:
      if (v0 != 0) {
         t9 >>= 1;
         t9 += t8;
         t9 += 1;
         return v0;
      } // .Lproc_80040C94_48: # 80040CDC
      t9 = t8 - t9;
      return v0;
   } // .Lproc_80040C94_54: # 80040CE8
   v0 = t8 << 1; // from BDS
   if (v0 >= t9) {
      v0 = t9 & 0x1;
      goto Lproc_80040C94_34;
   }
   return v0;
} // proc_80040C94
