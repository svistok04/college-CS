// Verilog test fixture created from schematic C:\Studenci\zv53855\kolowkium1\mux8na1_sch.sch - Mon Apr 17 13:45:24 2023

`timescale 1ns / 1ps

module mux8na1_sch_mux8na1_sch_sch_tb();

// Inputs
   reg iD;
   reg iA;
   reg iB;
   reg iC;

// Output
   wire oY;
// Bidirs

// Instantiate the UUT
   mux8na1_sch UUT (
		.oY(oY),
		.iD(iD), 
		.iA(iA), 
		.iB(iB), 
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