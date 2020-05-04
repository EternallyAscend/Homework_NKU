function [S] = getS(W)
m=length(W(1,:));
D=zeros(m);
for i=1:m
    D(i,i)=sum(W(i,:));
end
D=D.^-0.5;
D(D==inf)=0;
S=D*W*D;
% S=(D.^-0.5).*W.*(D.^-0.5);
end