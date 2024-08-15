`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:37:24 03/27/2023 
// Design Name: 
// Module Name:    mainMUL2BitsGates 
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
module TruthTable2BitsMUL(
    output [3:0] oY,
    input [1:0] iA,
    input [1:0] iB
    );

assign oY[0] = iA[0] & iB[0];
assign oY[1] = (iA[0] & iB[1] & (~iA[1] | ~iB[0])) | (iA[1] & iB[0] & (~iA[0] | ~iB[1]));
assign oY[2] = (iA[1] & iB[1] & (~iA[0] | ~iB[0]));
assign oY[3] = iA[0] & iA[1] & iB[0] & iB[1];


endmodule
