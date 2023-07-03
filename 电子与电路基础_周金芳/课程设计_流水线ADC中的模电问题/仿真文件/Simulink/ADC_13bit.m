clear;

beta=1.01;
Gain=5000;
C=10e-12;
T=300;
k=1.380649e-23;
%Constant Input

fs=1;
ts=1/fs;

fin_pre=0.1;
nfft=2048;
fin=antismear(fin_pre,fs,nfft);

bits_number = 13;

open_system('pipeline_13bit')

sim('pipeline_13bit', 5000*ts);	% Starts Simulink simulation

function fout = antismear(fin,fs,nfft)
 format long;
 ts=1/fs;
 c=primes(nfft*ts*fin);
 maxprimes=max(c);
 fout=maxprimes/(nfft*ts);
end