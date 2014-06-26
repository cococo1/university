unction [result]=productOfDifferences(n,xPoints,x);
%simply computes the product of (x-x0)...(x-xn-1)
result=1;
for i=1:n-1
    result=result*(x-xPoints(i));
end;

function [result]=dividedDifference(n,xPoints,yPoints)
%recursive function: stops when n=1; (array index 2)
%else computes the subarray of (x1...xn) and (y1...yn) 
% and (x0...xn-1) and (y0...yn-1) and calls itself on n-1
if (n==2) result=(yPoints(2)-yPoints(1))/(xPoints(2)-xPoints(1));
else
    rightXPoints=xPoints;
    rightXPoints(1)=rightXPoints(n);
    rightYPoints=yPoints;
    rightYPoints(1)=rightYPoints(n);
    result=(dividedDifference(n-1,rightXPoints,rightYPoints)-dividedDifference(n-1,xPoints,yPoints))/(xPoints(n)-xPoints(1));
end;

function [result]=newtonDividedDifference(n,xPoints,yPoints,x)
%recursive function : stops when n=1 (array index 2)
% n - number of elements in array
%xPoints - array of x values
%yPoints - array of y values
%x - value of X0 where we want to compute the polynomial
if (n==2) 
    result=yPoints(1)+dividedDifference(2,xPoints,yPoints)*productOfDifferences(2,xPoints,x);
else
    result=newtonDividedDifference(n-1,xPoints,yPoints,x)+dividedDifference(n,xPoints,yPoints)*productOfDifferences(n,xPoints,x);
end;

function [result]=trapezoidal(a,b,n)
h=(b-a)/n;
xPoints=[a:h:b];
result=0;
    for i=1:n+1
        f=myF(xPoints(i));
        if (i==1 | i==n+1) f=f*0.5;
        end;
        result=result+f;
    end;
    result=result*h;

function [result]=simpson(a,b,n)
h=(b-a)/n;
xPoints=[a:h:b];
    result=0;
    k=1;
    for i=1:n+1
        f=k*myF(xPoints(i));
        if (i==n)
            k=1;
        else if (i==1 | k==2) 
                k=4;
            else if (k==4) 
                    k=2;
                end;
            end;
        end;
        result=result+f; 
    end;
    result=result*(h/3);

function [result]=myF(x)
result=exp(x)*cos(4*x);

function [result]=controlFunction
i=2;
j=1;
previousError=0;
while (i<=512)
    res(j)=trapezoidal(0,pi,i);
    error(j)=(exp(pi)-1)/17-res(j);%atan(5-pi)+atan(pi)-res(j);
    i=i*2;
    ratio(j)=previousError/error(j);
    previousError=error(j);
    j=j+1;
end;
error;
ratio
result=1;

function [result]=quadrature(n,omega,xPoints)
result=0;
for i=1:n
    result=result+omega(i)*myF(xPoints(i));
end;
result=result*(pi/2);
error=(exp(pi)-1)/17-result


