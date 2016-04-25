tkmk00decode: # begin 800405D0 (0411D0)
  addi  $sp, $sp, -0x400
  sw    $s0, 0x19c($sp)
  sw    $s1, 0x198($sp)
  sw    $s2, 0x194($sp)
  sw    $s3, 0x190($sp)
  sw    $s4, 0x18c($sp)
  sw    $s5, 0x188($sp)
  sw    $s6, 0x184($sp)
  sw    $s7, 0x180($sp)
  sw    $ra, 0x17c($sp)
  lhu   $t4, 8($a0)
  lhu   $t3, 0xa($a0)
  move  $s2, $a3
  lbu   $t2, 6($a0)
  addiu $t8, $zero, -1
  move  $t9, $sp
  addiu $s7, $zero, 0x20
  mult  $t4, $t3
.Ltkmk00decode_48: # 80040618
  addi  $s7, $s7, -1
  sw    $t8, ($t9)
  bnez  $s7, .Ltkmk00decode_48
  addi  $t9, $t9, 4
  mflo  $t0
  move  $s4, $t0
  move  $s6, $a2
.Ltkmk00decode_64: # 80040634
  addi  $s4, $s4, -2
  sw    $zero, ($s6)
  bgtz  $s4, .Ltkmk00decode_64
  addi  $s6, $s6, 4
  move  $s7, $t0
  move  $t8, $a1
.Ltkmk00decode_7C: # 8004064C
  addi  $s7, $s7, -4
  sw    $zero, ($t8)
  bgtz  $s7, .Ltkmk00decode_7C
  addi  $t8, $t8, 4
  addi  $s4, $sp, 0x1c0
  addiu $s6, $zero, 8
  addi  $a3, $a0, 0xc
  move  $s5, $t2
.Ltkmk00decode_9C: # 8004066C
  lw    $s7, ($a3)
  andi  $v0, $s5, 1
  bnez  $v0, .Ltkmk00decode_B0
  add   $s7, $s7, $a0
  addi  $s7, $s7, -4
.Ltkmk00decode_B0: # 80040680
  addi  $s6, $s6, -1
  srl   $s5, $s5, 1
  sw    $s7, ($s4)
  addi  $a3, $a3, 4
  bnez  $s6, .Ltkmk00decode_9C
  addi  $s4, $s4, 4
  sw    $zero, 0x1e0($sp)
  sw    $zero, 0x1e4($sp)
  sw    $zero, 0x1e8($sp)
  sw    $zero, 0x1ec($sp)
  move  $s3, $sp
  move  $a3, $zero
  lw    $t0, 0x2c($a0)
  addi  $a0, $a0, 0x30
  addi  $s3, $s3, 0x3f0
  bal   proc_80040BC0
  addiu $s4, $zero, 0x20
  move  $t1, $v0
  move  $t5, $zero
  move  $t6, $zero
  move  $t7, $zero
.Ltkmk00decode_104: # 800406D4
  lhu   $t9, ($a2)
  beql  $t9, $zero, .Ltkmk00decode_12C
  lb    $v1, ($a1)
  andi  $s3, $t9, 0xfffe
  bne   $s3, $s2, .Ltkmk00decode_448
  move  $t7, $t9
  sh    $s3, ($a2)
  b     .Ltkmk00decode_448
  move  $t7, $s3
  lb    $v1, ($a1)
.Ltkmk00decode_12C: # 800406FC
  bal   proc_80040AC8
  addi  $v1, $v1, 1
  bnez  $v0, .Ltkmk00decode_144
  nop   
  b     .Ltkmk00decode_448
  sh    $t7, ($a2)
.Ltkmk00decode_144: # 80040714
  bal   proc_80040A60
  addiu $v1, $zero, 1
  beqz  $v0, .Ltkmk00decode_290
  nop   
  bal   proc_80040C54
  nop   
  bal   proc_80040C54
  move  $s0, $s4
  bal   proc_80040C54
  move  $s1, $s4
  move  $s5, $zero
  beqz  $t6, .Ltkmk00decode_18C
  move  $s6, $zero
  sll   $s3, $t4, 1
  sub   $t9, $a2, $s3
  lhu   $s5, ($t9)
  b     .Ltkmk00decode_198
  lhu   $s6, -2($a2)
.Ltkmk00decode_18C: # 8004075C
  beql  $t5, $zero, .Ltkmk00decode_19C
  andi  $t8, $s5, 0x7c0
  lhu   $s6, -2($a2)
.Ltkmk00decode_198: # 80040768
  andi  $t8, $s5, 0x7c0
.Ltkmk00decode_19C: # 8004076C
  andi  $t9, $s6, 0x7c0
  srl   $t8, $t8, 6
  srl   $t9, $t9, 6
  add   $t8, $t8, $t9
  srl   $t8, $t8, 1
  bal   proc_80040C94
  move  $t9, $s0
  sub   $v1, $t9, $t8
  move  $s0, $t9
  andi  $t8, $s5, 0xf800
  andi  $t9, $s6, 0xf800
  srl   $t8, $t8, 0xb
  srl   $t9, $t9, 0xb
  add   $t8, $t8, $t9
  srl   $t8, $t8, 1
  add   $t8, $t8, $v1
  slti  $at, $t8, 0x20
  bnez  $at, .Ltkmk00decode_1F0
  nop   
  b     .Ltkmk00decode_1FC
  addiu $t8, $zero, 0x1f
.Ltkmk00decode_1F0: # 800407C0
  bgez  $t8, .Ltkmk00decode_1FC
  nop   
  move  $t8, $zero
.Ltkmk00decode_1FC: # 800407CC
  bal   proc_80040C94
  move  $t9, $s1
  move  $s1, $t9
  andi  $t8, $s5, 0x3e
  andi  $t9, $s6, 0x3e
  srl   $t8, $t8, 1
  srl   $t9, $t9, 1
  add   $t8, $t8, $t9
  srl   $t8, $t8, 1
  add   $t8, $t8, $v1
  slti  $at, $t8, 0x20
  bnez  $at, .Ltkmk00decode_238
  nop   
  b     .Ltkmk00decode_244
  addiu $t8, $zero, 0x1f
.Ltkmk00decode_238: # 80040808
  bgez  $t8, .Ltkmk00decode_244
  nop   
  move  $t8, $zero
.Ltkmk00decode_244: # 80040814
  bal   proc_80040C94
  move  $t9, $s4
  sll   $s0, $s0, 6
  sll   $s1, $s1, 0xb
  sll   $t9, $t9, 1
  or    $t8, $s0, $s1
  or    $t7, $t8, $t9
  beql  $t7, $s2, .Ltkmk00decode_270
  addiu $s5, $zero, 0x3f
  ori   $t7, $t7, 1
  addiu $s5, $zero, 0x3f
.Ltkmk00decode_270: # 80040840
  addi  $s6, $sp, 0x7c
.Ltkmk00decode_274: # 80040844
  lh    $s7, ($s6)
  addi  $s5, $s5, -1
  addi  $s6, $s6, -2
  bnez  $s5, .Ltkmk00decode_274
  sh    $s7, 4($s6)
  b     .Ltkmk00decode_2BC
  sh    $t7, 2($s6)
.Ltkmk00decode_290: # 80040860
  bal   proc_80040A60
  addiu $v1, $zero, 6
  sll   $v0, $v0, 1
  add   $s6, $sp, $v0
  beqz  $v0, .Ltkmk00decode_2BC
  lhu   $t7, ($s6)
.Ltkmk00decode_2A8: # 80040878
  lh    $s7, -2($s6)
  addi  $s6, $s6, -2
  bne   $s6, $sp, .Ltkmk00decode_2A8
  sh    $s7, 2($s6)
  sh    $t7, ($s6)
.Ltkmk00decode_2BC: # 8004088C
  sh    $t7, ($a2)
  beqz  $t5, .Ltkmk00decode_2CC
  move  $t9, $zero
  ori   $t9, $t9, 1
.Ltkmk00decode_2CC: # 8004089C
  addi  $s5, $t4, -1
  slt   $at, $t5, $s5
  beql  $at, $zero, .Ltkmk00decode_2E4
  addi  $s6, $t4, -2
  ori   $t9, $t9, 2
  addi  $s6, $t4, -2
.Ltkmk00decode_2E4: # 800408B4
  slt   $at, $t5, $s6
  beql  $at, $zero, .Ltkmk00decode_2F8
  addi  $s5, $t3, -1
  ori   $t9, $t9, 4
  addi  $s5, $t3, -1
.Ltkmk00decode_2F8: # 800408C8
  slt   $at, $t6, $s5
  beql  $at, $zero, .Ltkmk00decode_30C
  addi  $s6, $t3, -2
  ori   $t9, $t9, 8
  addi  $s6, $t3, -2
.Ltkmk00decode_30C: # 800408DC
  slt   $at, $t6, $s6
  beql  $at, $zero, .Ltkmk00decode_320
  andi  $s7, $t9, 2
  ori   $t9, $t9, 0x10
  andi  $s7, $t9, 2
.Ltkmk00decode_320: # 800408F0
  addiu $at, $zero, 2
  bnel  $s7, $at, .Ltkmk00decode_33C
  andi  $s6, $t9, 4
  lbu   $s4, 1($a1)
  addi  $s4, $s4, 1
  sb    $s4, 1($a1)
  andi  $s6, $t9, 4
.Ltkmk00decode_33C: # 8004090C
  addiu $at, $zero, 4
  bnel  $s6, $at, .Ltkmk00decode_358
  andi  $s7, $t9, 9
  lbu   $s4, 2($a1)
  addi  $s4, $s4, 1
  sb    $s4, 2($a1)
  andi  $s7, $t9, 9
.Ltkmk00decode_358: # 80040928
  addiu $at, $zero, 9
  bne   $s7, $at, .Ltkmk00decode_370
  add   $s5, $a1, $t4
  lbu   $s4, -1($s5)
  addi  $s4, $s4, 1
  sb    $s4, -1($s5)
.Ltkmk00decode_370: # 80040940
  andi  $s6, $t9, 8
  addiu $at, $zero, 8
  bnel  $s6, $at, .Ltkmk00decode_390
  andi  $s7, $t9, 0xa
  lbu   $s4, ($s5)
  addi  $s4, $s4, 1
  sb    $s4, ($s5)
  andi  $s7, $t9, 0xa
.Ltkmk00decode_390: # 80040960
  addiu $at, $zero, 0xa
  bnel  $s7, $at, .Ltkmk00decode_3AC
  andi  $s7, $t9, 0x10
  lbu   $s4, 1($s5)
  addi  $s4, $s4, 1
  sb    $s4, 1($s5)
  andi  $s7, $t9, 0x10
.Ltkmk00decode_3AC: # 8004097C
  addiu $at, $zero, 0x10
  bne   $s7, $at, .Ltkmk00decode_3C4
  add   $s6, $s5, $t4
  lbu   $s4, ($s6)
  addi  $s4, $s4, 1
  sb    $s4, ($s6)
.Ltkmk00decode_3C4: # 80040994
  bal   proc_80040A60
  addiu $v1, $zero, 1
  beql  $v0, $zero, .Ltkmk00decode_44C
  addi  $t5, $t5, 1
  move  $s1, $a2
  sll   $s0, $t4, 1
  ori   $s3, $t7, 1
.Ltkmk00decode_3E0: # 800409B0
  bal   proc_80040A60
  addiu $v1, $zero, 2
  bnezl $v0, .Ltkmk00decode_41C
  addiu $at, $zero, 1
  bal   proc_80040A60
  addiu $v1, $zero, 1
  beql  $v0, $zero, .Ltkmk00decode_44C
  addi  $t5, $t5, 1
  bal   proc_80040A60
  addiu $v1, $zero, 1
  bnez  $v0, .Ltkmk00decode_43C
  addi  $s1, $s1, 4
  b     .Ltkmk00decode_43C
  addi  $s1, $s1, -8
  addiu $at, $zero, 1
.Ltkmk00decode_41C: # 800409EC
  bnel  $v0, $at, .Ltkmk00decode_430
  addiu $at, $zero, 3
  b     .Ltkmk00decode_43C
  addi  $s1, $s1, -2
  addiu $at, $zero, 3
.Ltkmk00decode_430: # 80040A00
  bnel  $v0, $at, .Ltkmk00decode_440
  add   $s1, $s1, $s0
  addi  $s1, $s1, 2
.Ltkmk00decode_43C: # 80040A0C
  add   $s1, $s1, $s0
.Ltkmk00decode_440: # 80040A10
  b     .Ltkmk00decode_3E0
  sh    $s3, ($s1)
.Ltkmk00decode_448: # 80040A18
  addi  $t5, $t5, 1
.Ltkmk00decode_44C: # 80040A1C
  addi  $a1, $a1, 1
  bne   $t5, $t4, .Ltkmk00decode_104
  addi  $a2, $a2, 2
  addi  $t6, $t6, 1
  bne   $t6, $t3, .Ltkmk00decode_104
  move  $t5, $zero
  lw    $ra, 0x17c($sp)
  lw    $s7, 0x180($sp)
  lw    $s6, 0x184($sp)
  lw    $s5, 0x188($sp)
  lw    $s4, 0x18c($sp)
  lw    $s3, 0x190($sp)
  lw    $s2, 0x194($sp)
  lw    $s1, 0x198($sp)
  lw    $s0, 0x19c($sp)
  jr    $ra
  addi  $sp, $sp, 0x400
# end tkmk00decode

proc_80040A60: # begin 80040A60 (041660)
  add   $t9, $a3, $v1
  addiu $t8, $zero, 0x20
  sub   $t8, $t8, $v1
  slti  $at, $t9, 0x21
  beqz  $at, .Lproc_80040A60_40
  srlv  $v0, $t0, $t8
  addiu $at, $zero, 0x20
  beql  $t9, $at, .Lproc_80040A60_34
  lw    $t0, ($a0)
  sllv  $t0, $t0, $v1
  jr    $ra
  add   $a3, $a3, $v1
  lw    $t0, ($a0)
.Lproc_80040A60_34: # 80040A94
  move  $a3, $zero
  jr    $ra
  addi  $a0, $a0, 4
.Lproc_80040A60_40: # 80040AA0
  addiu $t9, $zero, 0x40
  lw    $t0, ($a0)
  sub   $t9, $t9, $v1
  sub   $t9, $t9, $a3
  sub   $a3, $a3, $t8
  srlv  $t8, $t0, $t9
  or    $v0, $v0, $t8
  addi  $a0, $a0, 4
  jr    $ra
  sllv  $t0, $t0, $a3
# end proc_80040A60

proc_80040AC8: # begin 80040AC8 (0416C8)
  srlv  $t8, $t2, $v1
  andi  $t9, $t8, 1
  sll   $s7, $v1, 1
  add   $t8, $sp, $s7
  bnez  $t9, .Lproc_80040AC8_4C
  lhu   $s7, 0x1e0($t8)
  sll   $t9, $v1, 2
  add   $t9, $t9, $sp
  bnez  $s7, .Lproc_80040AC8_34
  lw    $s6, 0x1c0($t9)
  addi  $s6, $s6, 4
  addiu $s7, $zero, 0x20
  sw    $s6, 0x1c0($t9)
.Lproc_80040AC8_34: # 80040AFC
  lw    $t9, ($s6)
  addi  $s7, $s7, -1
  sh    $s7, 0x1e0($t8)
  srlv  $v0, $t9, $s7
  jr    $ra
  andi  $v0, $v0, 1
.Lproc_80040AC8_4C: # 80040B14
  sll   $t9, $v1, 2
  add   $t9, $t9, $sp
  add   $s5, $sp, $v1
  bnez  $s7, .Lproc_80040AC8_A8
  lw    $s6, 0x1c0($t9)
  lb    $s7, ($s6)
  addiu $v0, $zero, 0x100
  bltzl $s7, .Lproc_80040AC8_88
  sllv  $v0, $v0, $v1
  sllv  $v0, $v0, $v1
  not   $v0, $v0
  addi  $s7, $s7, 3
  b     .Lproc_80040AC8_94
  and   $t2, $t2, $v0
  sllv  $v0, $v0, $v1
.Lproc_80040AC8_88: # 80040B50
  andi  $s7, $s7, 0x7f
  addi  $s7, $s7, 1
  or    $t2, $t2, $v0
.Lproc_80040AC8_94: # 80040B5C
  lbu   $v0, 1($s6)
  addi  $s6, $s6, 2
  sll   $s7, $s7, 3
  sb    $v0, 0x1a0($s5)
  sw    $s6, 0x1c0($t9)
.Lproc_80040AC8_A8: # 80040B70
  lbu   $v0, 0x1a0($s5)
  addi  $s7, $s7, -1
  sh    $s7, 0x1e0($t8)
  andi  $t8, $s7, 7
  srlv  $v0, $v0, $t8
  bnez  $t8, .Lproc_80040AC8_F0
  andi  $v0, $v0, 1
  beqz  $s7, .Lproc_80040AC8_F0
  nop   
  addiu $t8, $zero, 0x100
  sllv  $s7, $t8, $v1
  and   $s7, $s7, $t2
  beqz  $s7, .Lproc_80040AC8_F0
  nop   
  lbu   $s7, ($s6)
  addi  $s6, $s6, 1
  sb    $s7, 0x1a0($s5)
  sw    $s6, 0x1c0($t9)
.Lproc_80040AC8_F0: # 80040BB8
  jr    $ra
  nop   
# end proc_80040AC8

proc_80040BC0: # begin 80040BC0 (0417C0)
  sw    $ra, -8($s3)
  addi  $s3, $s3, -8
  bal   proc_80040AC8
  move  $v1, $zero
  beql  $v0, $zero, .Lproc_80040BC0_64
  move  $s0, $zero
  sw    $s4, 4($s3)
  bal   proc_80040BC0
  addi  $s4, $s4, 1
  lw    $s5, 4($s3)
  sll   $s5, $s5, 1
  add   $s5, $s5, $sp
  bal   proc_80040BC0
  sh    $v0, 0x80($s5)
  lw    $s5, 4($s3)
  addi  $s3, $s3, 8
  move  $s6, $s5
  sll   $s5, $s5, 1
  add   $s5, $s5, $sp
  sh    $v0, 0xfe($s5)
  lw    $ra, -8($s3)
  move  $v0, $s6
  jr    $ra
  nop   
  move  $s0, $zero
.Lproc_80040BC0_64: # 80040C24
  addiu $s1, $zero, 5
.Lproc_80040BC0_68: # 80040C28
  bal   proc_80040AC8
  move  $v1, $zero
  sll   $s0, $s0, 1
  addi  $s1, $s1, -1
  bnez  $s1, .Lproc_80040BC0_68
  add   $s0, $s0, $v0
  lw    $ra, ($s3)
  addi  $s3, $s3, 8
  move  $v0, $s0
  jr    $ra
  nop   
# end proc_80040BC0

proc_80040C54: # begin 80040C54 (041854)
  move  $s4, $t1
  move  $s3, $ra
.Lproc_80040C54_8: # 80040C5C
  slti  $at, $s4, 0x20
  bnez  $at, .Lproc_80040C54_38
  nop   
  bal   proc_80040AC8
  move  $v1, $zero
  sll   $v1, $s4, 1
  bnez  $v0, .Lproc_80040C54_30
  add   $t8, $sp, $v1
  b     .Lproc_80040C54_8
  lh    $s4, 0x80($t8)
.Lproc_80040C54_30: # 80040C84
  b     .Lproc_80040C54_8
  lh    $s4, 0xfe($t8)
.Lproc_80040C54_38: # 80040C8C
  jr    $s3
  nop   
# end proc_80040C54

proc_80040C94: # begin 80040C94 (041894)
  slti  $at, $t8, 0x10
  bnezl $at, .Lproc_80040C94_54
  sll   $v0, $t8, 1
  addiu $v0, $zero, 0x1f
  sub   $v0, $v0, $t8
  sll   $v0, $v0, 1
  slt   $at, $v0, $t9
  beql  $at, $zero, .Lproc_80040C94_34
  andi  $v0, $t9, 1
  addiu $v0, $zero, 0x1f
  jr    $ra
  sub   $t9, $v0, $t9
  andi  $v0, $t9, 1
.Lproc_80040C94_34: # 80040CC8
  beqz  $v0, .Lproc_80040C94_48
  srl   $t9, $t9, 1
  add   $t9, $t9, $t8
  jr    $ra
  addi  $t9, $t9, 1
.Lproc_80040C94_48: # 80040CDC
  jr    $ra
  sub   $t9, $t8, $t9
  sll   $v0, $t8, 1
.Lproc_80040C94_54: # 80040CE8
  slt   $at, $v0, $t9
  beql  $at, $zero, .Lproc_80040C94_34
  andi  $v0, $t9, 1
  jr    $ra
  nop   
# end proc_80040C94
