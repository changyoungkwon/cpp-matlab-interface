function output = redim( rawd, target_dim )
% change dimension of rawd as target_dim
% zero padding / remove
L=length(size(rawd));
tmp=size(rawd);
tmp_=zeros(L,1);
for it=1:L 
    if(target_dim(it)~=0)
        fl=(size(rawd,it)>=target_dim(it));
        if(fl==0)
            tmp(it)=(target_dim(it)-size(rawd,it))/2;
            rawd=cat(it,zeros(floor(tmp)),rawd,zeros(ceil(tmp)));
            tmp=size(rawd);
        else
            tmp_(it)=(size(rawd,it)-(target_dim(it)))/2;
        end
    end
end

if(L==1)
    rawd=rawd(floor(tmp_(1))+1:end-ceil(tmp_(1)));
elseif(L==2)
    rawd=rawd(floor(tmp_(1))+1:end-ceil(tmp_(1)),floor(tmp_(2))+1:end-ceil(tmp_(2)));
elseif(L==3)
    rawd=rawd(floor(tmp_(1))+1:end-ceil(tmp_(1)),floor(tmp_(2))+1:end-ceil(tmp_(2)),floor(tmp_(3))+1:end-ceil(tmp_(3)));
elseif(L==4)
    rawd=rawd(floor(tmp_(1))+1:end-ceil(tmp_(1)),floor(tmp_(2))+1:end-ceil(tmp_(2)),floor(tmp_(3))+1:end-ceil(tmp_(3)), ...
        floor(tmp_(4))+1:end-floor(tmp_(4)));
elseif(L==5)
    rawd=rawd(floor(tmp_(1))+1:end-ceil(tmp_(1)),floor(tmp_(2))+1:end-ceil(tmp_(2)),floor(tmp_(3))+1:end-ceil(tmp_(3)), ...
        floor(tmp_(4))+1:end-ceil(tmp_(4)),floor(tmp_(5))+1:end-ceil(tmp_(5)));
else
    disp('out of dimension');
end

output=rawd;
