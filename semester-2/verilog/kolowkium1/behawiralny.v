`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:44:17 04/17/2023 
// Design Name: 
// Module Name:    behawiralny 
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
module behawiralny(
    input iA,
    input iB,
    input iC,
    input iD,
    output oY
    );

	assign oY = ~(iB ^ iD) | ~(iA ^ iC)&(~iB | iD);

endmodule
