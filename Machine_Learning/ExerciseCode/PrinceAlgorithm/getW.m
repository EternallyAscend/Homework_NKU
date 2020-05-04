function [W] = getW(X)
%% exp(-||xi-xj||^2/2theta^2) where i!=j && Wii=0;
sigma=std(X);
sizeX=length(X(:,1));
W=zeros(sizeX);
for i=1:sizeX
    for j=1:sizeX
        if i~=j
            W(i,j)=exp(-(X(i)-X(j))^2/(2*sigma^2));
        end
    end
end     
end