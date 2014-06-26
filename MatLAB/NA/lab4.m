function [x0]=jacobi1(a,b,error,x0,xtrue)
while (abs(norm(xtrue-x0,inf))>error)
    for i=1:3
        x(i)=1/a(i,i)*(b(i)-(sum(a(i,:).*x0)-a(i,i)*x0(i)));
    end;
    x0=x;  
end;

function [x0]=gaussSeidel(a,b,error,x0,xtrue)
while (abs(norm(xtrue-x0,inf))>error)
    for i=1:3
        x0(i)=1/a(i,i)*(b(i)-(sum(a(i,:).*x0)-a(i,i)*x0(i)));
    end;
end;

function [x0]=SOR(a,b,error,x0,xtrue,omega)
while (abs(norm(xtrue-x0,inf))>error)
    x=x0;
    for i=1:3
        x0(i)=(1-omega)*x(i)+omega/a(i,i)*(b(i)-(sum(a(i,:).*x0)-a(i,i)*x0(i)));
    end;
end;

function system2(n,error)
for i=1:n
    b(i)=1/((n+1)^2);
    x0(i)=0;
   for j=1:n
       a(i,j)=0;
       if(i==j+1 || j==i+1) a(i,j)=-1;
       else if (i==j) a(i,j)=2;
           end;
       end;
   end;
end;
a
b
x0
omega=optimalOmega(n)
disp('Jacobi');
jacobi1(a,b,error,x0,n);
disp('Gauss-Seidel');
gaussSeidel(a,b,error,x0,n);
disp('SOR');
SOR(a,b,error,x0,omega,n);

function [result]=optimalOmega(n)
psi=1-2*(sin(pi/(2*n)))^2;
result=2/(1+(1-psi^2)^.5);

