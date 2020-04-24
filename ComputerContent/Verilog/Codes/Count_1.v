module count(clk,rst_n,count_out);

input clk;//输入时钟信号
input rst_n;//输入复位信号
output reg [7:0] count_out;//计数器输出

always @ ( posedge clk or negedge rst_n )//时钟信号上升沿或复位信号下降沿有效
begin
	if( !rst_n ) begin//同步复位信号
		count_out <= 8'b0;
	end 
	else begin
		count_out <= count_out + 1'b1;//计数
	end
end
endmodule
