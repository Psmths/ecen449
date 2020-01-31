//Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2015.2 (lin64) Build 1266856 Fri Jun 26 16:35:25 MDT 2015
//Date        : Thu Jan 30 18:37:27 2020
//Host        : mobile running 64-bit Ubuntu 18.04.3 LTS
//Command     : generate_target led_sw_wrapper.bd
//Design      : led_sw_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module led_sw_wrapper
   (buttons_tri_i,
    clock_rtl,
    led_tri_o);
  input [7:0]buttons_tri_i;
  input clock_rtl;
  output [3:0]led_tri_o;

  wire [7:0]buttons_tri_i;
  wire clock_rtl;
  wire [3:0]led_tri_o;

  led_sw led_sw_i
       (.buttons_tri_i(buttons_tri_i),
        .clock_rtl(clock_rtl),
        .led_tri_o(led_tri_o));
endmodule
