`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:24:05 05/29/2023 
// Design Name: 
// Module Name:    segment7_855 
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
module segment7_855(
    output reg [2:0] baza,
    output reg [7:0] seg
    );

	always@(*)
		begin 
			case(baza)
				3'b110:
					begin
						seg = 8'b00000001;
					end
				3'b101:
					begin
						seg = 8'b00000001;
					end
				3'b011:
					begin
						seg = 8'b01001001;
					end
			endcase
		end
endmodule
