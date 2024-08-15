/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Studenci/zv53855/kolowkium1/behawiralny.v";



static void Cont_29_0(char *t0)
{
    char t3[8];
    char t6[8];
    char t36[8];
    char t40[8];
    char t70[8];
    char t91[8];
    char t118[8];
    char t150[8];
    char *t1;
    char *t2;
    char *t4;
    char *t5;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    char *t10;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    char *t25;
    char *t26;
    char *t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    char *t37;
    char *t38;
    char *t39;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    char *t44;
    char *t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    char *t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    char *t59;
    char *t60;
    char *t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    char *t71;
    char *t72;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    char *t78;
    char *t79;
    char *t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    unsigned int t84;
    unsigned int t85;
    unsigned int t86;
    unsigned int t87;
    unsigned int t88;
    char *t89;
    char *t90;
    unsigned int t92;
    unsigned int t93;
    unsigned int t94;
    char *t95;
    char *t96;
    unsigned int t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    unsigned int t101;
    unsigned int t102;
    unsigned int t103;
    char *t104;
    char *t105;
    unsigned int t106;
    unsigned int t107;
    unsigned int t108;
    int t109;
    unsigned int t110;
    unsigned int t111;
    unsigned int t112;
    int t113;
    unsigned int t114;
    unsigned int t115;
    unsigned int t116;
    unsigned int t117;
    unsigned int t119;
    unsigned int t120;
    unsigned int t121;
    char *t122;
    char *t123;
    char *t124;
    unsigned int t125;
    unsigned int t126;
    unsigned int t127;
    unsigned int t128;
    unsigned int t129;
    unsigned int t130;
    unsigned int t131;
    char *t132;
    char *t133;
    unsigned int t134;
    unsigned int t135;
    unsigned int t136;
    unsigned int t137;
    unsigned int t138;
    unsigned int t139;
    unsigned int t140;
    unsigned int t141;
    int t142;
    int t143;
    unsigned int t144;
    unsigned int t145;
    unsigned int t146;
    unsigned int t147;
    unsigned int t148;
    unsigned int t149;
    unsigned int t151;
    unsigned int t152;
    unsigned int t153;
    char *t154;
    char *t155;
    char *t156;
    unsigned int t157;
    unsigned int t158;
    unsigned int t159;
    unsigned int t160;
    unsigned int t161;
    unsigned int t162;
    unsigned int t163;
    char *t164;
    char *t165;
    unsigned int t166;
    unsigned int t167;
    unsigned int t168;
    int t169;
    unsigned int t170;
    unsigned int t171;
    unsigned int t172;
    int t173;
    unsigned int t174;
    unsigned int t175;
    unsigned int t176;
    unsigned int t177;
    char *t178;
    char *t179;
    char *t180;
    char *t181;
    char *t182;
    unsigned int t183;
    unsigned int t184;
    char *t185;
    unsigned int t186;
    unsigned int t187;
    char *t188;
    unsigned int t189;
    unsigned int t190;
    char *t191;

LAB0:    t1 = (t0 + 2848U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(29, ng0);
    t2 = (t0 + 1208U);
    t4 = *((char **)t2);
    t2 = (t0 + 1528U);
    t5 = *((char **)t2);
    t7 = *((unsigned int *)t4);
    t8 = *((unsigned int *)t5);
    t9 = (t7 ^ t8);
    *((unsigned int *)t6) = t9;
    t2 = (t4 + 4);
    t10 = (t5 + 4);
    t11 = (t6 + 4);
    t12 = *((unsigned int *)t2);
    t13 = *((unsigned int *)t10);
    t14 = (t12 | t13);
    *((unsigned int *)t11) = t14;
    t15 = *((unsigned int *)t11);
    t16 = (t15 != 0);
    if (t16 == 1)
        goto LAB4;

LAB5:
LAB6:    memset(t3, 0, 8);
    t19 = (t6 + 4);
    t20 = *((unsigned int *)t19);
    t21 = (~(t20));
    t22 = *((unsigned int *)t6);
    t23 = (t22 & t21);
    t24 = (t23 & 1U);
    if (t24 != 0)
        goto LAB10;

LAB8:    if (*((unsigned int *)t19) == 0)
        goto LAB7;

LAB9:    t25 = (t3 + 4);
    *((unsigned int *)t3) = 1;
    *((unsigned int *)t25) = 1;

LAB10:    t26 = (t3 + 4);
    t27 = (t6 + 4);
    t28 = *((unsigned int *)t6);
    t29 = (~(t28));
    *((unsigned int *)t3) = t29;
    *((unsigned int *)t26) = 0;
    if (*((unsigned int *)t27) != 0)
        goto LAB12;

LAB11:    t34 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t34 & 1U);
    t35 = *((unsigned int *)t26);
    *((unsigned int *)t26) = (t35 & 1U);
    t37 = (t0 + 1048U);
    t38 = *((char **)t37);
    t37 = (t0 + 1368U);
    t39 = *((char **)t37);
    t41 = *((unsigned int *)t38);
    t42 = *((unsigned int *)t39);
    t43 = (t41 ^ t42);
    *((unsigned int *)t40) = t43;
    t37 = (t38 + 4);
    t44 = (t39 + 4);
    t45 = (t40 + 4);
    t46 = *((unsigned int *)t37);
    t47 = *((unsigned int *)t44);
    t48 = (t46 | t47);
    *((unsigned int *)t45) = t48;
    t49 = *((unsigned int *)t45);
    t50 = (t49 != 0);
    if (t50 == 1)
        goto LAB13;

LAB14:
LAB15:    memset(t36, 0, 8);
    t53 = (t40 + 4);
    t54 = *((unsigned int *)t53);
    t55 = (~(t54));
    t56 = *((unsigned int *)t40);
    t57 = (t56 & t55);
    t58 = (t57 & 1U);
    if (t58 != 0)
        goto LAB19;

LAB17:    if (*((unsigned int *)t53) == 0)
        goto LAB16;

LAB18:    t59 = (t36 + 4);
    *((unsigned int *)t36) = 1;
    *((unsigned int *)t59) = 1;

LAB19:    t60 = (t36 + 4);
    t61 = (t40 + 4);
    t62 = *((unsigned int *)t40);
    t63 = (~(t62));
    *((unsigned int *)t36) = t63;
    *((unsigned int *)t60) = 0;
    if (*((unsigned int *)t61) != 0)
        goto LAB21;

LAB20:    t68 = *((unsigned int *)t36);
    *((unsigned int *)t36) = (t68 & 1U);
    t69 = *((unsigned int *)t60);
    *((unsigned int *)t60) = (t69 & 1U);
    t71 = (t0 + 1208U);
    t72 = *((char **)t71);
    memset(t70, 0, 8);
    t71 = (t72 + 4);
    t73 = *((unsigned int *)t71);
    t74 = (~(t73));
    t75 = *((unsigned int *)t72);
    t76 = (t75 & t74);
    t77 = (t76 & 1U);
    if (t77 != 0)
        goto LAB25;

LAB23:    if (*((unsigned int *)t71) == 0)
        goto LAB22;

LAB24:    t78 = (t70 + 4);
    *((unsigned int *)t70) = 1;
    *((unsigned int *)t78) = 1;

LAB25:    t79 = (t70 + 4);
    t80 = (t72 + 4);
    t81 = *((unsigned int *)t72);
    t82 = (~(t81));
    *((unsigned int *)t70) = t82;
    *((unsigned int *)t79) = 0;
    if (*((unsigned int *)t80) != 0)
        goto LAB27;

LAB26:    t87 = *((unsigned int *)t70);
    *((unsigned int *)t70) = (t87 & 1U);
    t88 = *((unsigned int *)t79);
    *((unsigned int *)t79) = (t88 & 1U);
    t89 = (t0 + 1528U);
    t90 = *((char **)t89);
    t92 = *((unsigned int *)t70);
    t93 = *((unsigned int *)t90);
    t94 = (t92 | t93);
    *((unsigned int *)t91) = t94;
    t89 = (t70 + 4);
    t95 = (t90 + 4);
    t96 = (t91 + 4);
    t97 = *((unsigned int *)t89);
    t98 = *((unsigned int *)t95);
    t99 = (t97 | t98);
    *((unsigned int *)t96) = t99;
    t100 = *((unsigned int *)t96);
    t101 = (t100 != 0);
    if (t101 == 1)
        goto LAB28;

LAB29:
LAB30:    t119 = *((unsigned int *)t36);
    t120 = *((unsigned int *)t91);
    t121 = (t119 & t120);
    *((unsigned int *)t118) = t121;
    t122 = (t36 + 4);
    t123 = (t91 + 4);
    t124 = (t118 + 4);
    t125 = *((unsigned int *)t122);
    t126 = *((unsigned int *)t123);
    t127 = (t125 | t126);
    *((unsigned int *)t124) = t127;
    t128 = *((unsigned int *)t124);
    t129 = (t128 != 0);
    if (t129 == 1)
        goto LAB31;

LAB32:
LAB33:    t151 = *((unsigned int *)t3);
    t152 = *((unsigned int *)t118);
    t153 = (t151 | t152);
    *((unsigned int *)t150) = t153;
    t154 = (t3 + 4);
    t155 = (t118 + 4);
    t156 = (t150 + 4);
    t157 = *((unsigned int *)t154);
    t158 = *((unsigned int *)t155);
    t159 = (t157 | t158);
    *((unsigned int *)t156) = t159;
    t160 = *((unsigned int *)t156);
    t161 = (t160 != 0);
    if (t161 == 1)
        goto LAB34;

LAB35:
LAB36:    t178 = (t0 + 3248);
    t179 = (t178 + 56U);
    t180 = *((char **)t179);
    t181 = (t180 + 56U);
    t182 = *((char **)t181);
    memset(t182, 0, 8);
    t183 = 1U;
    t184 = t183;
    t185 = (t150 + 4);
    t186 = *((unsigned int *)t150);
    t183 = (t183 & t186);
    t187 = *((unsigned int *)t185);
    t184 = (t184 & t187);
    t188 = (t182 + 4);
    t189 = *((unsigned int *)t182);
    *((unsigned int *)t182) = (t189 | t183);
    t190 = *((unsigned int *)t188);
    *((unsigned int *)t188) = (t190 | t184);
    xsi_driver_vfirst_trans(t178, 0, 0);
    t191 = (t0 + 3168);
    *((int *)t191) = 1;

LAB1:    return;
LAB4:    t17 = *((unsigned int *)t6);
    t18 = *((unsigned int *)t11);
    *((unsigned int *)t6) = (t17 | t18);
    goto LAB6;

LAB7:    *((unsigned int *)t3) = 1;
    goto LAB10;

LAB12:    t30 = *((unsigned int *)t3);
    t31 = *((unsigned int *)t27);
    *((unsigned int *)t3) = (t30 | t31);
    t32 = *((unsigned int *)t26);
    t33 = *((unsigned int *)t27);
    *((unsigned int *)t26) = (t32 | t33);
    goto LAB11;

LAB13:    t51 = *((unsigned int *)t40);
    t52 = *((unsigned int *)t45);
    *((unsigned int *)t40) = (t51 | t52);
    goto LAB15;

LAB16:    *((unsigned int *)t36) = 1;
    goto LAB19;

LAB21:    t64 = *((unsigned int *)t36);
    t65 = *((unsigned int *)t61);
    *((unsigned int *)t36) = (t64 | t65);
    t66 = *((unsigned int *)t60);
    t67 = *((unsigned int *)t61);
    *((unsigned int *)t60) = (t66 | t67);
    goto LAB20;

LAB22:    *((unsigned int *)t70) = 1;
    goto LAB25;

LAB27:    t83 = *((unsigned int *)t70);
    t84 = *((unsigned int *)t80);
    *((unsigned int *)t70) = (t83 | t84);
    t85 = *((unsigned int *)t79);
    t86 = *((unsigned int *)t80);
    *((unsigned int *)t79) = (t85 | t86);
    goto LAB26;

LAB28:    t102 = *((unsigned int *)t91);
    t103 = *((unsigned int *)t96);
    *((unsigned int *)t91) = (t102 | t103);
    t104 = (t70 + 4);
    t105 = (t90 + 4);
    t106 = *((unsigned int *)t104);
    t107 = (~(t106));
    t108 = *((unsigned int *)t70);
    t109 = (t108 & t107);
    t110 = *((unsigned int *)t105);
    t111 = (~(t110));
    t112 = *((unsigned int *)t90);
    t113 = (t112 & t111);
    t114 = (~(t109));
    t115 = (~(t113));
    t116 = *((unsigned int *)t96);
    *((unsigned int *)t96) = (t116 & t114);
    t117 = *((unsigned int *)t96);
    *((unsigned int *)t96) = (t117 & t115);
    goto LAB30;

LAB31:    t130 = *((unsigned int *)t118);
    t131 = *((unsigned int *)t124);
    *((unsigned int *)t118) = (t130 | t131);
    t132 = (t36 + 4);
    t133 = (t91 + 4);
    t134 = *((unsigned int *)t36);
    t135 = (~(t134));
    t136 = *((unsigned int *)t132);
    t137 = (~(t136));
    t138 = *((unsigned int *)t91);
    t139 = (~(t138));
    t140 = *((unsigned int *)t133);
    t141 = (~(t140));
    t142 = (t135 & t137);
    t143 = (t139 & t141);
    t144 = (~(t142));
    t145 = (~(t143));
    t146 = *((unsigned int *)t124);
    *((unsigned int *)t124) = (t146 & t144);
    t147 = *((unsigned int *)t124);
    *((unsigned int *)t124) = (t147 & t145);
    t148 = *((unsigned int *)t118);
    *((unsigned int *)t118) = (t148 & t144);
    t149 = *((unsigned int *)t118);
    *((unsigned int *)t118) = (t149 & t145);
    goto LAB33;

LAB34:    t162 = *((unsigned int *)t150);
    t163 = *((unsigned int *)t156);
    *((unsigned int *)t150) = (t162 | t163);
    t164 = (t3 + 4);
    t165 = (t118 + 4);
    t166 = *((unsigned int *)t164);
    t167 = (~(t166));
    t168 = *((unsigned int *)t3);
    t169 = (t168 & t167);
    t170 = *((unsigned int *)t165);
    t171 = (~(t170));
    t172 = *((unsigned int *)t118);
    t173 = (t172 & t171);
    t174 = (~(t169));
    t175 = (~(t173));
    t176 = *((unsigned int *)t156);
    *((unsigned int *)t156) = (t176 & t174);
    t177 = *((unsigned int *)t156);
    *((unsigned int *)t156) = (t177 & t175);
    goto LAB36;

}


extern void work_m_00000000003714288676_1920715291_init()
{
	static char *pe[] = {(void *)Cont_29_0};
	xsi_register_didat("work_m_00000000003714288676_1920715291", "isim/behawiralny_tb_isim_beh.exe.sim/work/m_00000000003714288676_1920715291.didat");
	xsi_register_executes(pe);
}
