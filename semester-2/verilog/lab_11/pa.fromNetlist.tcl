
# PlanAhead Launch Script for Post-Synthesis floorplanning, created by Project Navigator

create_project -name lab_11 -dir "C:/Studenci/zv53855/lab_11/planAhead_run_1" -part xc3s50atq144-4
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "C:/Studenci/zv53855/lab_11/segment7_855.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {C:/Studenci/zv53855/lab_11} }
set_property target_constrs_file "segment7_855.ucf" [current_fileset -constrset]
add_files [list {segment7_855.ucf}] -fileset [get_property constrset [current_run]]
link_design
