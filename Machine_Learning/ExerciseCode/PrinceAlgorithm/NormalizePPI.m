%% First running this script and save the normalize matrix as a mat file.
load('ppi_network.mat');
X=ppi_network;
coloum=length(X(1,:));
line=length(X(:,1));
norm_ppi_network=X;
for i=1:line
   counter=0;
   for j=1:coloum
      if X(i,j)==1
          counter=counter+1;
      end
   end
   for j=1:coloum
       if X(i,j)==1
           norm_ppi_network(i,j)=1/counter;
       end
   end
end
save(['./norm_ppi_network.mat'],'norm_ppi_network');
normS=getS(X);
save(['./norm_ppi_network_S.mat'],'normS');