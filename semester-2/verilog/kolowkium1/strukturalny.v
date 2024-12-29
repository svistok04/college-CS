`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:16:13 04/17/2023 
// Design Name: 
// Module Name:    strukturalny 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module strukturalny(iA, iB, iC, iD, oY);


	input iA, iB, iC, iD;
	output oY;
	wire not_b, o1, o2, o3, o4;

	not(not_b, iB);
	xnor (o1, iB, iD);
	xnor(o2, iA, iC);
	or (o3, not_b, iD);
	and (o4, o2, o3);
	or (oY, o1, o4);

endmodule
