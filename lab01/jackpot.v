`timescale 1ns / 1ps
module jackpot(
    input [3:0] SWITCHES,
    output [3:0] LEDS,
    input CLOCK
    );
    

    
    reg [23:0] divider;
    reg[3:0] outs;
    reg won = 1'b0;
    
    
    
    always@(posedge CLOCK) begin
    
        if (won) begin
            if (divider[20]) begin
                    outs <= 4'b1111;
            end
            else begin
                outs <= 4'b0000;
            end
        end
    
        divider <= divider + 1;
        
        if (won == 1'b0 & divider == 4'hFFF) begin
            outs <= outs << 1;
        end
        
        if(won == 1'b0 & outs == 4'b0000) outs = 4'b0001;
        
    end
    
    always@(posedge SWITCHES) begin
        if((outs & SWITCHES) > 0) begin
            won <= 1'b1;
        end
    end
    
    assign LEDS[3:0] = outs[3:0];
endmodule
