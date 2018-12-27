function [rawd, im_mask, k_mask, k_norm, header, recon_option] = mrxg_pre( filename )

% parsing
h=mapVBVD(filename);
hsize=h.image.sqzSize;
header=h.hdr;


if(findstr(header.Dicom.tProtocolName,'mrxg'))
    if(findstr(header.Dicom.tProtocolName,'flair')||findstr(h.Dicom.tProtocolName,'FLAIR')||findstr(h.Dicom.tProtocolName,'Flair'))
        recon_option=sprintf('flair%d',header.Dicom.lAccelFactPE);
    else
        recon_option=sprintf('t2%d',header.Dicom.lAccelFactPE);
    end
else
    recon_option='-1';
end

% make 4-D rawdata (x, y, z, c)
if(length(hsize)==6)
    rawd=zeros(hsize(1), hsize(2), hsize(3), hsize(4), hsize(5));
    for it=1:hsize(6)
        rawd=rawd+h.image{:,:,:,:,:,it};
    end
    rawd=rawd(:,:,:,:,1); % select the first volume from sequential average mode
else
    rawd=zeros(hsize(1), hsize(2), hsize(3), hsize(4));
    for it=1:hsize(5)
        rawd=rawd+h.image{:,:,:,:,it};
    end
end
rawd=permute(single(rawd),[1,3,4,2]);

ref=h.refscan{:,:,:,:,:};
ref=sum(ref,5);
ref=permute(single(ref),[1,3,4,2]);

for it=(round(size(rawd,2)/2)-3):(round(size(rawd,2)/2)+4)
    for it_=1:size(ref,2)
        if(corr(abs(ref(:,it_,1,1)),abs(rawd(:,it,1,1)))>0.96)
            flg=it-it_+1;
        end
    end
end
rawd(:,flg:flg+size(ref,2)-1,:,:)=ref;

if(header.Config.PhaseResolution<1)
    indx=(1/h.hdr.Config.PhaseResolution-1)*size(rawd,2)/2;
    rawd=cat(2,zeros(size(rawd,1),floor(indx),size(rawd,3),size(rawd,4)),rawd,zeros(size(rawd,1),ceil(indx),size(rawd,3),size(rawd,4)));
else
    indx=0;
end

% k-space normalize
[xres yres zres cres] = size(rawd);
k_tmp = abs(rawd).^2;
k_norm = squeeze(sqrt(sum(sum(sum(k_tmp,1),2),4)));
for zit=1:zres
    rawd(:,:,zit,:)=single(rawd(:,:,zit,:)/k_norm(zit));
end

% generate mask
[xres yres zres cres] = size(rawd);
k_mask=1-(sum(rawd,4)==0);
mask_filt=repmat(k_mask,1,1,1,cres);
mask_filt(:,1:(flg+floor(indx)-1),:,:)=0;
mask_filt(:,flg+size(ref,2)+floor(indx):end,:,:)=0;
tmp=sqrt(sum(abs(ifft3c(rawd.*mask_filt,3)).^2,4));
im_mask=tmp>(mean(tmp(:)));

for it=1:size(im_mask,3);
    tmp_=bwlabel(imerode(im_mask(:,:,it),strel('disk',5)),4);
    im_mask(:,:,it)=(tmp_==mode(tmp_(tmp_>0)));
    im_mask(:,:,it)=(im_mask(:,:,it)+(tmp(:,:,it)>(mean(tmp(:))*2)))>0;
    im_mask=redim(im_mask,[xres+40,yres+40,zres,cres]);
    im_mask(:,:,it)=imdilate(medfilt2(imfill(imdilate(im_mask(:,:,it),strel('disk',5)),'holes'),[3,3]),strel('disk',10));
    im_mask(:,:,it)=imerode(imfill(im_mask(:,:,it),'holes'),strel('disk',8));
    im_mask=redim(im_mask,[xres,yres,zres,cres]);
end
im_mask=im_mask>0;
save('output.mat', 'rawd', 'im_mask', 'k_mask', 'k_norm', 'header', 'recon_option');
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% matlab
%%%%%%%%%%%%%%%%%% parsing *.dat %%%%%%%%%%%%%%%%%% mrxg_pre
%%%%%%%%%%%%%%%%%% input : *.dat %%%%%%%%%%%%%%%%%%
% output : rawd, im_mask, k_mask, k_norm, header, %
%%%%%%%%%% recon_option %%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% c
%%%%%%%%%%%%%%%%%%%%%   bart  %%%%%%%%%%%%%%%%%%%%% file i/o
%%%%%%%%%% input : rawd, im_mask, k_mask %%%%%%%%%%
%%%%%%%%%% output : csm                  %%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% c
%%%%%%%%%%%%%%%%%%%%%   bart  %%%%%%%%%%%%%%%%%%%%% file i/o
%%%%%%%%%% input : rawd, csm             %%%%%%%%%%
%%%%%%%%%% output : cgsense              %%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% python
%%%%%%%%%%%%%%%%%%%%% g-factor %%%%%%%%%%%%%%%%%%%%
%%%%%%%%%% input : rawd, im_mask, csm    %%%%%%%%%%
%%%%%%%%% output : g-factor              %%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% python
%%%%%%%%%%%%%%%% make network input %%%%%%%%%%%%%%%
%%%%%%%%%% input : rawd, csm, g-factor %%%%%%%%%%%%
%%%%%%% output : sens_in, g-fact_in, im_in %%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% python
%%%%%%%%%%% mrxg network forwarding YJY %%%%%%%%%%%
%%%% input : sens_in, g-fact_in, im_in, header %%%%
%%%%%%%%%%%%%%%%% output : im_out %%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% python
%%%%%%%%%%% mrxg network forwarding KJG %%%%%%%%%%%
%%%%%%%%% input : im_out, cgsense, header %%%%%%%%%
%%%%%%%%%%%%%% output : im_out_filt %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% python
%%%%%%%%%%%%% mrxg_post: dicom write %%%%%%%%%%%%%% mrxg_post
%%%%%% input : im_out_filt, header, k_norm %%%%%%%%
%%%%%%%%%% output : (doing dicom write) %%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%





