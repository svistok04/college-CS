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
static const char *ng0 = "C:/Studenci/zv53855/kolowkium1/mux8na1_sch.vf";
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {1U, 0U};
static unsigned int ng3[] = {2U, 0U};
static unsigned int ng4[] = {3U, 0U};
static unsigned int ng5[] = {4U, 0U};
static unsigned int ng6[] = {5U, 0U};
static unsigned int ng7[] = {6U, 0U};
static unsigned int ng8[] = {7U, 0U};



static void Always_43_0(char *t0)
{
    char t4[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    char *t20;
    int t21;

LAB0:    t1 = (t0 + 4128U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(43, ng0);
    t2 = (t0 + 4448);
    *((int *)t2) = 1;
    t3 = (t0 + 4160);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(44, ng0);

LAB5:    xsi_set_current_line(45, ng0);
    t5 = (t0 + 2328U);
    t6 = *((char **)t5);
    memset(t4, 0, 8);
    t5 = (t6 + 4);
    t7 = *((unsigned int *)t5);
    t8 = (~(t7));
    t9 = *((unsigned int *)t6);
    t10 = (t9 & t8);
    t11 = (t10 & 1U);
    if (t11 != 0)
        goto LAB9;

LAB7:    if (*((unsigned int *)t5) == 0)
        goto LAB6;

LAB8:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;

LAB9:    t13 = (t4 + 4);
    t14 = *((unsigned int *)t13);
    t15 = (~(t14));
    t16 = *((unsigned int *)t4);
    t17 = (t16 & t15);
    t18 = (t17 != 0);
    if (t18 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(48, ng0);

LAB13:    xsi_set_current_line(49, ng0);
    t2 = (t0 + 2488U);
    t3 = *((char **)t2);
    t2 = (t0 + 2648U);
    t5 = *((char **)t2);
    t2 = (t0 + 2808U);
    t6 = *((char **)t2);
    xsi_vlogtype_concat(t4, 3, 3, 3U, t6, 1, t5, 1, t3, 1);

LAB14:    t2 = ((char*)((ng1)));
    t21 = xsi_vlog_unsigned_case_compare(t4, 3, t2, 3);
    if (t21 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng2)));
    t21 = xsi_vlog_unsigned_case_compare(t4, 3, t2, 3);
    if (t21 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng3)));
    t21 = xsi_vlog_unsigned_case_compare(t4, 3, t2, 3);
    if (t21 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng4)));
    t21 = xsi_vlog_unsigned_case_compare(t4, 3, t2, 3);
    if (t21 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng5)));
    t21 = xsi_vlog_unsigned_case_compare(t4, 3, t2, 3);
    if (t21 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng6)));
    t21 = xsi_vlog_unsigned_case_compare(t4, 3, t2, 3);
    if (t21 == 1)
        goto LAB25;

LAB26:    t2 = ((char*)((ng7)));
    t21 = xsi_vlog_unsigned_case_compare(t4, 3, t2, 3);
    if (t21 == 1)
        goto LAB27;

LAB28:    t2 = ((char*)((ng8)));
    t21 = xsi_vlog_unsigned_case_compare(t4, 3, t2, 3);
    if (t21 == 1)
        goto LAB29;

LAB30:
LAB31:
LAB12:    goto LAB2;

LAB6:    *((unsigned int *)t4) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(46, ng0);
    t19 = ((char*)((ng1)));
    t20 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t20, t19, 0, 0, 1, 0LL);
    goto LAB12;

LAB15:    xsi_set_current_line(50, ng0);
    t12 = (t0 + 1048U);
    t13 = *((char **)t12);
    t12 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t12, t13, 0, 0, 1, 0LL);
    goto LAB31;

LAB17:    xsi_set_current_line(51, ng0);
    t3 = (t0 + 1208U);
    t5 = *((char **)t3);
    t3 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 1, 0LL);
    goto LAB31;

LAB19:    xsi_set_current_line(52, ng0);
    t3 = (t0 + 1368U);
    t5 = *((char **)t3);
    t3 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 1, 0LL);
    goto LAB31;

LAB21:    xsi_set_current_line(53, ng0);
    t3 = (t0 + 1528U);
    t5 = *((char **)t3);
    t3 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 1, 0LL);
    goto LAB31;

LAB23:    xsi_set_current_line(54, ng0);
    t3 = (t0 + 1688U);
    t5 = *((char **)t3);
    t3 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 1, 0LL);
    goto LAB31;

LAB25:    xsi_set_current_line(55, ng0);
    t3 = (t0 + 1848U);
    t5 = *((char **)t3);
    t3 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 1, 0LL);
    goto LAB31;

LAB27:    xsi_set_current_line(56, ng0);
    t3 = (t0 + 2008U);
    t5 = *((char **)t3);
    t3 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 1, 0LL);
    goto LAB31;

LAB29:    xsi_set_current_line(57, ng0);
    t3 = (t0 + 2168U);
    t5 = *((char **)t3);
    t3 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 1, 0LL);
    goto LAB31;

}


extern void work_m_00000000000297335681_1550353473_init()
{
	static char *pe[] = {(void *)Always_43_0};
	xsi_register_didat("work_m_00000000000297335681_1550353473", "isim/mux8na1_sch_mux8na1_sch_sch_tb_isim_beh.exe.sim/work/m_00000000000297335681_1550353473.didat");
	xsi_register_executes(pe);
}
