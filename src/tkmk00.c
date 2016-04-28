#include <string.h>

#include "utils.h"

static i32 t1, t7, t8, t9, s0, s1, s3, s4, s5, s6, s7, v0, v1;

// 0x400 allocated on stack
static u16 rgba_buf[0x40];     // SP[000]-SP[07F] - buffer of 32 RGBA colors
static u16 buffer80_u16[0x3F]; // SP[080]-SP[0FD]
static u16 bufferFE_u16[0x3F]; // SP[0FE]-SP[17B]
                               // SP[17C]-SP[19F] - preserved registers
static u8  byte_buffer[0x20];  // SP[1A0]-SP[1BF] - byte buffer
static u8 *some_ptrs[8];       // SP[1C0]-SP[1DF] - 8 pointers to A0 data read from starting at offset 0xC
static u16 some_u16s[8];       // SP[1E0]-SP[1EF] - 8 u16s, related to some_ptrs
static u32 some_u32s[0x80];    // SP[200]-SP[3F0] - indexes used to initialize buffer80 and bufferFE

static i32 header6;
static int some_offset;
static int some_flags;
static u8 *in_ptr;

static void proc_80040A60(void);
static void proc_80040AC8(void);
static void proc_80040BC0(u32, u32*);
static void proc_80040C54(void);
static void proc_80040C94(void);

// this is needed to to logical shifts on signed data
static i32 SRL(i32 val, int amount)
{
   u32 vU = (u32)val;
   vU >>= amount;
   return (i32)vU;
}

// a0[in]: pointer to TKMK00 data
// a1[out]: pointer to output (1 byte per pixel)
// a2[out]: pointer to output (RGBA16, 2 bytes per pixel)
// a3[in]: RGBA color to set alpha to 0, values observed: 0x01, 0xBE
void tkmk00decode(u8 *a0p, u8 *a1p, u8 *a2p, u32 a3p)  // 800405D0/0411D0
{
   unsigned offset;
   unsigned test_bits;
   int width, height;
   int col, row;
   int pixels;
   int alpha;
   unsigned i;
   u16 rgba0;
   u16 rgba1;
   u8 red0, red1, green0, green1, blue0, blue1;
   
   width = read_u16_be(&a0p[0x8]);
   height = read_u16_be(&a0p[0xA]);
   alpha = a3p;
   header6 = a0p[0x6];
   pixels = width * height;
   memset(rgba_buf, 0xFF, sizeof(rgba_buf));
   memset(a2p, 0x0, 2 * pixels);
   memset(a1p, 0x0, pixels);
   
   for (i = 0; i < 8; i++) {
       offset = read_u32_be(&a0p[0xC + i*4]);
       if (0 == (header6 & (0x1 << i))) {
          offset -= 4;
       }
       some_ptrs[i] = a0p + offset;
   }

   memset(some_u16s, 0, sizeof(some_u16s));
   some_offset = 0x0; // no idea, used in proc_80040A60
   some_flags = read_u32_be(&a0p[0x2C]); // used in proc_80040A60
   in_ptr = &a0p[0x30];
   u32 val = 0x20;
   proc_80040BC0(DIM(some_u32s)-4, &val); // recursive
   
   t1 = v0;
   t7 = 0;

   for (row = 0; row != height; row++) {
      for (col = 0; col != width; col++) {
         t9 = read_u16_be(a2p);
         
         if (t9 == 0) {
            v1 = a1p[0];
         } else {
            s3 = t9 & 0xFFFE;
            t7 = t9;
            if (alpha != s3) {
               goto tkmk00decode_448;
            }
            write_u16_be(a2p, s3);
            t7 = s3;
            goto tkmk00decode_448;
         }
         v1 += 1;
         proc_80040AC8();
         
         if (v0 == 0) {
            write_u16_be(a2p, t7);
            goto tkmk00decode_448;
         }
         
         v1 = 1;
         proc_80040A60();
         
         if (v0 != 0) {
            proc_80040C54();
            
            s0 = s4;
            proc_80040C54();
            
            s1 = s4;
            proc_80040C54();
            
            rgba0 = 0;
            rgba1 = 0;
            if (row != 0) {
               rgba0 = read_u16_be(a2p - (width * 2));
               rgba1 = read_u16_be(a2p - 2);
            } else {
               if (col != 0) {
                  rgba1 = read_u16_be(a2p - 2);
               }
            }

            red0 = (rgba0 & 0x7C0) >> 6;
            red1 = (rgba1 & 0x7C0) >> 6;
            t8 = (red0 + red1) / 2;
            t9 = s0;
            proc_80040C94();
            s0 = t9;
            
            v1 = t9 - t8;
            green0 = (rgba0 & 0xF800) >> 11;
            green1 = (rgba1 & 0xF800) >> 11;
            t8 = v1 + (green0 + green1) / 2;
            if (t8 >= 0x20) {
               t8 = 0x1F;
            } else if (t8 < 0) {
               t8 = 0;
            }
            t9 = s1;
            proc_80040C94();
            s1 = t9;

            blue0 = (rgba0 & 0x3E) >> 1;
            blue1 = (rgba1 & 0x3E) >> 1;
            t8 = v1 + (blue0 + blue1) / 2;
            if (t8 >= 0x20) {
               t8 = 0x1F;
            } else if (t8 < 0) {
               t8 = 0;
            }
            t9 = s4;
            proc_80040C94();

            t7 = (s1 << 11) | (s0 << 6) | (t9 << 1);
            if (t7 != alpha) {
               t7 |= 0x1;
            }
            
            // insert new value by shifting others to right
            for (i = DIM(rgba_buf) - 1; i > 0; i--) {
               rgba_buf[i] = rgba_buf[i - 1];
            }
            rgba_buf[0] = t7;
         } else {
            v1 = 6;
            proc_80040A60();
            t7 = rgba_buf[v0];
            if (v0 != 0) {
               for (i = v0; i > 0; i--) {
                  rgba_buf[i] = rgba_buf[i - 1];
               }
               rgba_buf[0] = t7;
            }
         }
         write_u16_be(a2p, t7);
         test_bits = 0;
         if (col != 0) {
            test_bits |= 0x01;
         }
         s5 = width - 1;
         if (col < s5) {
            test_bits |= 0x02;
         } 
         s6 = width - 2;
         if (col < s6) {
            test_bits |= 0x04;
         }
         s5 = height - 1;
         if (row < s5) {
            test_bits |= 0x08;
         }
         s6 = height - 2;
         if (row < s6) {
            test_bits |= 0x10;
         }

         if (0x2 == (test_bits & 0x2)) {
            a1p[1]++;
         } 
         if (0x4 == (test_bits & 0x4)) {
            a1p[2]++;
         }
         if (0x9 == (test_bits & 0x9))  {
            a1p[width - 1]++;
         }
         if (0x8 == (test_bits & 0x8)) {
            a1p[width]++;
         }
         if (0xA == (test_bits & 0xA)) {
            a1p[width + 1]++;
         }
         if (0x10 == (test_bits & 0x10)) {
            a1p[2*width]++;
         }
         
         v1 = 1;
         proc_80040A60();
         
         if (v0 != 0) {
            u8 *out = a2p;
            s0 = width * 2;
            s3 = t7 | 0x1;
            
            do {
               v1 = 2;
               proc_80040A60();
               if (v0 == 0) {
                  v1 = 1;
                  proc_80040A60();
  
                  if (v0 == 0) {
                     break;
                  } else {
                     v1 = 1;
                     proc_80040A60();
                     out += 4;
                     if (v0 == 0) {
                        out -= 8;
                     }
                  }
               } else if (v0 == 1) {
                  out -= 2;
               } else if (v0 == 3) {
                  out += 2;
               }
               out += s0;
               write_u16_be(out, s3);
            } while (1);
         }
tkmk00decode_448:
         a1p += 1;
         a2p += 2;
      } while (col != width);
   } while (row != height);
}

// inputs: a0, a3, v1, t0
// outputs: a0, a3, t0, t8, t9, v0
static void proc_80040A60(void) // 80040A60/041660
{
   unsigned this_offset;
   this_offset = some_offset + v1;
   t8 = 0x20 - v1;
   v0 = SRL(some_flags, t8); // v0 = t0 >> t8;
   if (this_offset < 0x21) {
      if (this_offset != 0x20) {
         some_flags <<= v1;
         some_offset += v1;
         return;
      } else {
         some_flags = read_u32_be(in_ptr);
         some_offset = 0;
         in_ptr += 4;
         return;
      }
   } else {
      this_offset = 0x40;
      some_flags = read_u32_be(in_ptr);
      this_offset -= v1;
      this_offset -= some_offset;
      some_offset -= t8;
      t8 = SRL(some_flags, this_offset); // t8 = t0 >> t9;
      v0 |= t8;
      in_ptr += 4;
      some_flags <<= some_offset;
      return;
   }
}

// inputs: t2, v1
// outputs: t8, t9, s6, s7, v0
static void proc_80040AC8(void) // 80040AC8/0416C8
{
   u8 *s6ptr;
   t8 = SRL(header6, v1); // t8 = t2 >> v1;
   t9 = t8 & 0x1;
   s7 = some_u16s[v1];
   if (t9 == 0) {
      s6ptr = some_ptrs[v1];
      if (s7 == 0) {
         s6ptr += 4;
         s7 = 0x20;
         some_ptrs[v1] = s6ptr;
      }
      t9 = read_u32_be(s6ptr);
      s7 -= 1;
      some_u16s[v1] = s7;
      v0 = SRL(t9, s7); // v0 = t9 >> s7;
      v0 &= 0x1;
      return;
   }
   s6ptr = some_ptrs[v1];
   if (s7 == 0) {
      s7 = *s6ptr;
      v0 = 0x100;
      v0 <<= v1;
      if ((s7 & 0x80) == 0x00) { // if (s7 >= 0) {
         v0 = ~v0;
         s7 += 3;
         header6 &= v0;
      } else {
         s7 &= 0x7F;
         s7 += 1;
         header6 |= v0;
      }
      v0 = s6ptr[1];
      s6ptr += 2;
      s7 <<= 3;
      byte_buffer[v1] = v0;
      some_ptrs[v1] = s6ptr;
   }
   v0 = byte_buffer[v1];
   s7 -= 1;
   some_u16s[v1] = s7;
   t8 = s7 & 0x7;
   v0 = SRL(v0, t8); // v0 >>= t8;
   v0 &= 0x1;
   if (t8 == 0 && s7 != 0) {
      t8 = 0x100;
      s7 = t8 << v1;
      s7 &= header6;
      if (s7 != 0) {
         s7 = s6ptr[0];
         s6ptr += 1;
         byte_buffer[v1] = s7;
         some_ptrs[v1] = s6ptr;
      }
   }
   return;
}

// inputs: s3, s4
// outputs: v0, v1, s0, s1, s3, s4, s5
static void proc_80040BC0(u32 u32idx, u32 *val) // 80040BC0/0417C0
{
   INFO("idx: %08X, val: %08X, %s\n",
         u32idx, *val, __func__);
   fflush(stdout);
   fflush(stderr);

   u32idx--;
   v1 = 0;
   proc_80040AC8();

   if (v0 != 0) {
      u32 idx;
      some_u32s[u32idx] = *val;
      (*val)++;
      proc_80040BC0(u32idx, val);
      idx = some_u32s[u32idx];
      buffer80_u16[idx] = v0;
      proc_80040BC0(u32idx, val);
      idx = some_u32s[u32idx];
      u32idx++;
      s6 = idx;
      bufferFE_u16[idx] = v0;
      v0 = s6;
      return;
   } else {
      s0 = 0;
   }
   s1 = 5;
   do {
      v1 = 0;
      proc_80040AC8();
      s0 = v0 + s0 * 2;
      s1 -= 1;
   } while (s1 != 0);
   u32idx++;
   v0 = s0;
   return;
}

// inputs: t1
// outputs: s4, v0
static void proc_80040C54(void) // 80040C54/041854
{
   s4 = t1;
   while (s4 >= 0x20) {
      v1 = 0;
      proc_80040AC8();
      if (v0 == 0) {
         s4 = buffer80_u16[s4];
      } else {
         s4 = bufferFE_u16[s4];
      }
   }
}

// inputs: t8, t9
// outputs: v0, t9
static void proc_80040C94(void) // 80040C94/041894
{
   if (t8 >= 0x10) {
      v0 = (0x1F - t8) * 2;
      if (v0 < t9) {
         v0 = 0x1F;
         t9 = v0 - t9;
         return;
      } else {
         v0 = t9 & 0x1;
      }
      t9 = SRL(t9, 1); // t9 >>= 1;
      if (v0 != 0) {
         t9 += t8 + 1;
         return;
      } else {
         t9 = t8 - t9;
         return;
      }
   } else {
      v0 = t8 << 1;
   }
   if (v0 >= t9) {
      v0 = t9 & 0x1;
      t9 = SRL(t9, 1); // t9 >>= 1;
      if (v0 != 0) {
         t9 += t8 + 1;
         return;
      } else {
         t9 = t8 - t9;
         return;
      }
   }
   return;
}
