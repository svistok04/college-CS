
# PlanAhead Launch Script for Post-Synthesis floorplanning, created by Project Navigator

create_project -name lab_12 -dir "C:/Studenci/zv53855/lab_12/planAhead_run_2" -part xc3s50atq144-4
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "C:/Studenci/zv53855/lab_12/zad_2.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {C:/Studenci/zv53855/lab_12} }
set_property target_constrs_file "zad_1.ucf" [current_fileset -constrset]
add_files [list {zad_1.ucf}] -fileset [get_property constrset [current_run]]
link_design
