function [result]=bisect1(a,b,eps)
%if there is no root in this interval, the bound of interval is returned
result=a; 
iterations=0;
if (myF(a)*myF(b)<0) %checking to see if the root is present
    c=(a+b)/2;
      disp(c-0.42630275100686); %computing the relative error
    while (abs(b-c)>eps)               
        if (myF(a)*myF(c)<0) b=c;
        else   a=c;
        end;
        c=(a+b)/2;
        disp(c-0.42630275100686);
    end;
    result=c;
end;

function [result]=myF(x)
result=sqrt(x)-exp(-x);

function [result]=newton1(x0,eps)
if (myF(x0)~=0) %if myF(x0)=0, then we already have the root
    x1=x0-myF(x0)/mydF(x0);
    disp(x1-0.426030275100686); % relative error
    while (abs(x1-x0)>eps)
        x0=x1;
        x1=x0-myF(x0)/mydF(x0);
        disp(x1-0.42630275100686);
    end;
    result=x1;
else result=x0;
end;

function [result]=newton2(x0,eps)
if (myF(x0)~=0) %if myF(x0)=0, then we already have the root
    D=(myF(x0+myF(x0))-myF(x0))/myF(x0); %instead of derivative we use D
    x1=x0-myF(x0)/D;
    iterations=0;
    disp(abs(x1-0.426030275100686)); % relative error
    while (abs(x1-x0)>eps)
         D=(myF(x0+myF(x0))-myF(x0))/myF(x0);
        x1=x0-myF(x0)/D;
        x0=x1;
        disp(abs(x1-0.42630275100686));
    end;
    result=x1;
else result=x0;
end;

function [result]=secant1(x0,x1,eps)
x=x1-(myF(x1)*(x1-x0))/(myF(x1)-myF(x0));
disp(abs(x-0.42630275100686));
while(abs(x-x1)>eps)
    x0=x1;
    x1=x;
    x=x1-(myF(x1)*(x1-x0))/(myF(x1)-myF(x0));
    disp(abs(x-0.42630275100686));
end;
result=x;

