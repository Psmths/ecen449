`timescale 1ns / 1ps
module counter(
    input BTN0,
    input BTN1,
    input CLOCK,
    input RESET,
    output [3:0] LEDS
    );
    
    //Counter will act as a clock
    //divider
    reg [31:0] counter;
    
    
    always@(posedge CLOCK) begin
    
        //If user is holding down BTN0,
        //count up
        if (BTN0) begin
            counter <= counter + 1;
        end
        
        //If user is holding down BTN1,
        //count down
        if(BTN1) begin
            counter <= counter - 1;
        end
        
        //If user presses RESET, reset
        //the counter
        if(RESET) begin
            counter <= 4'h0000;
        end
        
    end
    //Only display the MSBs of the counter
    assign LEDS[3:0] = counter[31:28];
endmodule
