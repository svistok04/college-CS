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

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_00000000000297335681_1550353473_init();
    unisims_ver_m_00000000003317509437_1759035934_init();
    unisims_ver_m_00000000003927721830_1593237687_init();
    unisims_ver_m_00000000000236260522_2449448540_init();
    work_m_00000000003621656134_4182923552_init();
    work_m_00000000000940226879_2110413626_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000000940226879_2110413626");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
