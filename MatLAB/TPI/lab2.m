function [prob]=birthday(n,people)
%Computes the probability of the same birthday for n=people people n times
prob=0;
for i=1:n  
    x=fix(365*rand(1,people))+1;
    succes=0;
    x=sort(x); 
      for j=1:people-1
           if  x(j)==x(j+1)     %length( find(x==x(j)) )>=2
                 succes=1; break;
            end
      end
    prob=prob+succes;
end
prob=prob/n;

function perm(x,p)
n=length(x);
if p>n disp(x); %when p reaches n , it is the time to stop recursion and display the results .
else for i=p:n
        %aux is an auxiliar variable, for swaping 2 values .
        aux=x(i);
        x(i)=x(p);
        x(p)=aux;
        %we call recursively this function :
        perm(x,p+1);
         aux=x(i);
        x(i)=x(p);
        x(p)=aux;
    end
end

function combine(n,m)
%Initialize these two vectors :
x=[1:1:n];
x1=[1:1:m];
%Calculate n choose m (number of subsets I need to show)
nfact=prod(x);
mfact=prod(1:m);
nmfact=prod(1:n-m);
numb=nfact/(mfact*nmfact);

for i=1:(numb) 
    a(i,1:m)=x1;  %This is the matrix that will store all the subsets that have been shown
   disp(x1);
    t=0;
     
    if (i==numb) break;
    end;
    
    while t==0  % This loop runs until a new subset is find .
       x=randperm(n);
       for j=1:m
           x1(j)=x(j);
       end
       x1=sort(x1); % for comparing this subset with other, stored in matrix a 
       t=1;                 % t will remain 1 if this subset in not yet in matrix .This means the loop will stop .
       for j=1:i 
           if (x1==a(j,1:m))  t=0; 
               if (t==0) break;   
               end
           end
       end
    end
end


function [z]=choose(n,k)
nfact=(sqrt(2*pi))*(n^(n+1/2))*(exp(-n));
kfact=(sqrt(2*pi))*(k^(k+1/2))*(exp(-k));
nk=n-k;
nkfact=(sqrt(2*pi))*(nk^(nk+1/2))*(exp(-nk));
z=nfact/(kfact*nkfact);

function [b]=binomialp(n,p,j)
q=1-p;
nfact=prod(1:n);
mfact=prod(1:j);
nmfact=prod(1:n-j);
b= nfact*p^j*q^(n-j) / ( mfact*nmfact );

function [p]=tossing(a,b,n)
% a and b are the bounds for interval, n indicates times of simulation
c=0; k=0;
for i=1:n
    x=fix(rand(1,100)+0.5);
    c=sum(x);
    if (c>=a) & (c<=b) k=k+1;
    end
end;
p=k/n;

function [k]=root(n)
k=1/sqrt(pi*n);

