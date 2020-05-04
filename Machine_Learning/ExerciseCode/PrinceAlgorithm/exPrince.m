%% Machine Learning Exercise: Prince Algorithm
%  Exercise SE | Prince Algorithm
%  2020.05.03 Sun. 1813045

%% Please runing "NormalizePPI.m" before running this script.
%  Make sure the Normalize Matrix already exists for running "NormalizePPI.m" in this folder first.
load('norm_ppi_network_S.mat');


%% Load Data and setting for Calculate. Input DiseasesId here.

% ID=100800;
% ID=103500;
prompt='Please input ID\n';
ID=input(prompt);

topN=10; % Return topN result Gene related with ID.

alpha=0.1;
iter=50;
relatedDiseases=5;

load('g_p_network.mat');
load('phenotype_network.mat');
load('ppi_network.mat');

Y=getTopNSimilarDiseases(ID,phenotype_network,g_p_network,relatedDiseases);

%% Training and Save

result=trainF(iter,alpha,normS,Y);
save(['./prince_phenotype_fold_' num2str(ID) '.mat'],'result');


%% Sort Result.

top=0;
min=1;
minPos=0;
position=zeros(topN);
values=zeros(topN);
relationOfID=result;
coloum=length(relationOfID);
for i=1:coloum
    if top<topN
        position(top+1)=i;
        values(top+1)=relationOfID(i);
        if values(top+1)<min
            min=values(top+1);
            minPos=top+1;
        end
        top=top+1;
    else
        if relationOfID(i)>min
            position(minPos)=i;
            values(minPos)=relationOfID(i);
            min=relationOfID(i);
            for k=1:topN
                if values(k)<min
                    min=values(k);
                    minPos=k;
                end                
            end
        end
    end
end


%% Sort and display result.
for i=1:topN
    for j=1:topN-1
        if values(j)<values(j+1)
            temp=values(j+1);
            values(j+1)=values(j);
            values(j)=temp;
            temp=position(j+1);
            position(j+1)=position(j);
            position(j)=temp;      
        end
    end
end
disp(["Input ID: " ID]);
disp(["Line" 'Name']); % 'Value'
for i=1:topN
   disp([position(i) gene_name(position(i),:)]); % values(i)
end


%% Test Code Area

% save(['./prince_phenotype_fold_' num2str(ID) '.mat'],'result');
% fprintf('Program paused. Press enter to continue.\n');
% pause;


%% Example Output ID and Related Gene.

% alpha = 0.1;
% iters = 50;
% --------------------test1--------------------
% Please input phenotype_id:
% 100800
% Related genes(top10):
%     [129]    'FGFR3'
%     [2108]    'COMP'
%     [6804]    'IDUA'
%     [6120]    'MPP3'
%     [2959]    'C6orf47'
%     [2121]    'COL9A1'
%     [2960]    'GPSM3'
%     [5433]    'FGF23'
%     [2820]    'FGF5'
%     [2956]    'FGF6'

% 
% --------------------test2--------------------
% Please input phenotype_id:
% 103500
% Related genes(top10):
%     [4204]    'MITF'
%     [4493]    'TFEB'
%     [4494]    'TFEC'
%     [4495]    'ZNF278'
%     [6147]    'OTX2'
%     [4087]    'TFE3'
%     [1785]    'LEF1'
%     [3428]    'PAX6'
%     [1759]    'SPI1'
%     [179]    'PIAS3'

