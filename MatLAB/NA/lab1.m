function [result]=tannh(x)
result=(exp(x)-exp(-x))/(exp(x)+exp(-x));

function problem2;
t=0.1;
for n=1:10 
    e=n/10-n*t;
    disp(e);
end;

function [result]=integral(k)
int0=1-exp(-1);
int1=int0;
for i=1:k 
    int1=i*int0-exp(-1);
    int0=int1;
end;
result=int1;

function [result]=EscVel(Z0,c,N)
n=0;
while (n<N) 
    n=n+1;
   Zn=Z0^2+c; %recurent formula
   absZn=sqrt(real(Zn)^2+imag(Zn)^2); %computing the absolute value of Z
   if (absZn>2) break; %escape velocity found
   end;
   Z0=Zn;
end;
result=n;

function [result]=JuliaSet(Zmax,c,N)
M=0;

for j=1:500
% first for indicates 500 lines from our matrix
%second for is for random values for real part of 500 complex numbers    
for ind=1:500
    sign1=rand(1);
    newZreal(ind)=rand(1)*Zmax;
    if (sign1<0.5)
        newZreal(ind)=-newZreal(ind);
    end;
end;

%using linspace to obtain imaginary part
newZimag=i*linspace(-imag(Zmax),imag(Zmax),500);

%our complex number:
newZ=newZreal+newZimag;

%computing the escape value
for ind=1:500
M(j,ind)=EscVel(newZ(ind),c,N);
end;

end; %end of the first for

result=M;

