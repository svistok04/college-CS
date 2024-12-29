// Verilog test fixture created from schematic C:\Studenci\zv53855\kolowkium1\behiwiralny_sch.sch - Mon Apr 17 13:05:20 2023

`timescale 1ns / 1ps

Amodule behiwiralny_sch_behiwiralny_sch_sch_tb();

// Inputs
   reg iB;
   reg iD;
   reg iA;
   reg iC;

// Output
   wire oY;

// Bidirs

// Instantiate the UUT
   behiwiralny_sch UUT (
		.oY(oY), 
		.iB(iB), 
		.iD(iD), 
		.iA(iA), 
		.iC(iC)
   );
// Initialize Inputs
initial begin
			
			iA = 0; iB = 0; iC = 0; iD = 0; #10
			iA = 0; iB = 0; iC = 0; iD = 1; #10
			iA = 0; iB = 0; iC = 1; iD = 0; #10
			iA = 0; iB = 0; iC = 1; iD = 1; #10
			iA = 0; iB = 1; iC = 0; iD = 0; #10
			iA = 0; iB = 1; iC = 0; iD = 1; #10
			iA = 0; iB = 1; iC = 1; iD = 0; #10
			iA = 0; iB = 1; iC = 1; iD = 1; #10
			iA = 1; iB = 0; iC = 0; iD = 0; #10
			iA = 1; iB = 0; iC = 0; iD = 1; #10
			iA = 1; iB = 0; iC = 1; iD = 0; #10
			iA = 1; iB = 0; iC = 1; iD = 1; #10
			iA = 1; iB = 1; iC = 0; iD = 0; #10
			iA = 1; iB = 1; iC = 0; iD = 1; #10
			iA = 1; iB = 1; iC = 1; iD = 0; #10
			iA = 1; iB = 1; iC = 1; iD = 1;
			
	end
endmodule
