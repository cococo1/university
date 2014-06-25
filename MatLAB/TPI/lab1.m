function [n1,n2,p1,p2,r1,r2]=problem1(n)
rez=fix(2*rand(1,n));
% We assign n random integer values ( zero or one) to the vector rez;
% n1 - number of heads; n2- number of tails; p1 - proportion of heads; 
% r1-proportion of heads minus 1/2 , r2 – the same for tails .
n1=sum(rez);
n2=n-n1;
p1=n1/n;
p2=n2/n;
r1=p1-1/2;
r2=p2-0.5;

function [percentage]=problem2(n)
% I pick 4 random numbers from [1,6] N times. If there is a number 6 
% in one pick , then the game is won. At the end I divide the number of won
% games to n , multiply with 100 and get the percentage of winnings .
percentage=0;
for i=1:n 
    vector=fix(6*rand(1,4)+1);
    a=find(vector==6);
    if (a>0) percentage=percentage+1; 
    end;
end;
percentage=percentage/n*100;

function [percentage]=problem3(n)
% I pick two random numbers from [1,6] 24 times. If there is a pair of two
% six , then the game is won. I simulate the game n times .
percentage=0;
for i=1:n k=0;
 for j=1:24  
    a=fix(6*rand+1);
    b=fix(6*rand+1);
          if ((a==6)&(b==6)) k=1; break; 
         end;
 end;
 if (k==1) percentage=percentage+1;
 end;
end;
percentage=percentage/n*100;

function [vector,Peter_win]=problem4;
vector=fix(rand(1,40)*2);
Peter_win=sum(vector)-(40-sum(vector));

function [vector_of_wins]=problem4(n);
%We initialize a vector of length 81, for all possible wins 
%Then we simulate the game, compute the win for one game, and increment the
%right position in vector_of_wins
for i=1:81
    vector_of_wins(i)=0;
end;
for i=1:n
    Peter_win=0;
vector=fix(rand(1,40)*2);
Peter_win=Peter_win+sum(vector)-(40-sum(vector));
vector_of_wins(Peter_win+41)=vector_of_wins(Peter_win+41)+1;
end;

function [a,b,c,d]=problem5(n)
a=0; b=0; c=0; d=0;
for i=1:n
    v=fix(rand*100);
    if (v<30) a=a+1; else
        if (v<70) b=b+1; else
            if (v<90) c=c+1; else
                d=d+1;
            end;
        end;
    end;
end;

function [b]=problem6(n)
%We simulate n times the roll of three dice : a,b,c , then sum the
%outcomes. 
%After this, we find how many sums =9 were there, and divide this numeber
%to n, to find proportion .
vector(n)=0;
for i=1:n 
    a=fix(6*rand+1);
    b=fix(6*rand+1);
    c=fix(6*rand+1);
    vector(i)=a+b+c;
end;
a=find(vector==9);
b=length(a)/n;

