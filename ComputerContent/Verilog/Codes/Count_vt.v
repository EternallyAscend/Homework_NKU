module count_vt();

reg clk;
reg rst_n;                                            
wire [7:0]  count_out;
                         
count i1 (
	.clk(clk),
	.count_out(count_out),
	.rst_n(rst_n)
);

initial                                                
begin                                                                           
  clk = 0;
  rst_n= 0;
	
	#20;
	rst_n= 1;
	
	#600;
	$stop;                                            
$display("Running testbench");                       
end    
                                                
always                                                               
begin                                                                       
	#5 clk = ~clk;                                            
end   
                                                 
endmodule
