function [geneList] = getTopNSimilarDiseases(diseases_ID,diseasesRelation,geneDiseasesRelation,topN)
%% Return the gene relationship of top N most similar diseases;
line=length(diseasesRelation(:,1));
geneListSize=length(geneDiseasesRelation(:,1));
geneList=zeros(geneListSize,1);
currentLine=-1;
for i=1:line
    if strcmp(num2str(diseasesRelation(i,1)),num2str(diseases_ID)) == 1 % disp(diseases_ID);disp(diseasesRelation(i,1)); % pause;
       relationOfID=diseasesRelation(i,2:end); % Drop the ID head here.
       currentLine=i;
       break;
    end
end
if currentLine==-1
   fprintf("Wrong ID");
else
    top=0;
    min=1;
    minPos=0;
%     topN=topN+1; % N include itself.
    position=zeros(topN);
    values=zeros(topN);
    coloum=length(relationOfID);
    for i=1:coloum
%         if i==currentLine
%             continue;
%         end
        if top<topN
            position(top+1)=i;
            values(top+1)=relationOfID(i);
%             value(top)=diseasesRelation(currentLine,i);
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
    % Finished get Top N here.
    % Start to turn into Gene.
    for i=1:topN
%         disp(["Values" values(i) position(i)]);
        geneLine=geneDiseasesRelation(:,position(i));
        geneList=geneList+geneLine.*values(i);
    end
end
end