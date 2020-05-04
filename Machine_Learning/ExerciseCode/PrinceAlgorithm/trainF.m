function [FtP1] = trainF(item,alpha,S,Y)
FtP1=Y;
for i=1:item
    % disp([i "Times\n"]);
    temp=alpha.*S*FtP1+(1-alpha).*Y;
%     FtP1=temp;
    if sum(abs(FtP1-temp))<10^-8
        FtP1=temp;
        break;
    else
        FtP1=temp;
    end
end
end