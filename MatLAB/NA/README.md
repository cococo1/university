NA
==========

Numerical Analysis.

--

**Lab 1**

*Problem 1* Implement the given function and try to evaluate this function for x=10,100,1000. What do you get ? Why ? Find another way to compute this function. Be as precise as possible.

*Problem 2* Implement the following procedures:

``Let t=0.1

for n from 1 to 10 do

e=n/10-n*t

display results

end do``

Notice if anything strange happens. Explain the results.

*Problem 3* Compute the integrals   for k=0,1,2,… . Using integration by parts show that 	
Using your favourite programming system compute for k=0,1,2,…,25. Do you notice anything wrong with your answers ? To analyse this suppose that the only error is in  . Then , if all calculations are exact what is the error in  ? What error you expect if , where u is the unit roundoff ?

*Problem 4* Given two complex numbers :  and c : The sequence of complex numbers   represent the orbit of .
For a given fixed c, most choices of  yield orbits that tend toward infinity : If   , then orbit will tend to infinity. n – escape velocity .
Write a function that returns the escape velocity of a given  and c.
Form a matrix M 500x500 of escape velocities for random values of  and c.

--

**Lab 2**

*Problem 1* Find the root of the function f(x) =  on the interval
[0, 1.2] with error tolerance of .

a) Apply the bisection method starting with a = 0 and b = 1.2;

b) Apply the Newton’s method starting with  = 0.6;

c) Apply the simplified Newton’s method starting with  = 0.6;

d) Apply the secant method with  = 0.6 and = 1;

For each method compute also the absolute errors    for each iterate.

Note: the true zero  = 0.42630275100686; 

Present results in a table. Discuss these results.

*Problem 2* 
Using the programs from previous problem, solve the equation

with an accuracy of .  Experiment with different ways of evaluating f(x); for
example, use (i) the given form, (ii) reverse its order, and (iii) the nested form.
Try various initial intervals (for example [0; 1.5] ; [0.2; 2.0] ; and [0.6; 1.1]) or
initial guesses (for example ,  ; and  = 1.1;  = 10;  = 0.6;
and  = 0.9;). Note that  = 1 is the only root. Discuss your results.

*Problem 3* Apply the Newton Method to compute the roots of  with the accuracy of  .

*Problem 4* Consider the equation

with a nonzero constant c. Denote the nonzero solution by . For what values of c will the iteration   converge? Slowly increase the value of c past the interval found earlier, keeping c< 4. Observe the behaviour. Comment your results.

*Problem 5* Compute the fixed point for the following functions
a)
b)    
c)
Using Aitken extrapolation estimate the error and improve the approximated solution.

*Problem 6* Repeat the previous problem using the active Aitken extrapolation.

*Problem 7* Apply the Newton Method to compute the roots of

Print out the ratios


Repeat the problem for several choices of . Make observations that seem important to the root-finding problem.

--

**Lab 3**

*Problem 1* Write a program that will compute the Newton’s divided differences given the vector x=[] and y=[] . Then, use this program to evaluate the interpolation polynomial at some point . Using this, plot the graph of function f(x)=cos x on interval [0,π] and the interpolation polynomials  with n=4,6,8,10,12 and evenly spaced nodes from [0, π]. Also, plot the errors f(x)-. Comment your results.

*Problem 2* Apply trapezoidal and Simpson’s rules with n=2,4,...,512 for the following functions : 
a)
b)
c)
Also find the errors and the ratios by which the errors decrease.

*Problem 3* Apply Gaussian quadratures with n=2,3,4,5 for computing the integrals from Problem 2. Calculate the errors and compare them with the errors in Problem 2. Begin by tranforming the integrals to the standart interval [-1,1]. Nodes and weights of Gaussian quadrature are given in the following table :

--

**Lab 4**

*Problem 1* Consider the system Ax = b with 
For the given values of b solve the system using Jacobi, Gauss-Seidel and SOR methods. Take initial guess . Iterate until 
  . Look at the ratios of the successive errors. 
a) b= 
b) b= 
c) b= 
Repeat the problem but with stopping criterion 

Comment the behaviour of methods based on the results reported in the table.

*Problem 2* Consider solving the system  with 

and Use Jacobi, Gauss-Seidel and SOR(with optimal ω) methods with Iterate until 

Do the computations with n=10, 100, 1000, and Produce a table of the integer k with which computation is completed. Comment on the behaviour of the methods based on the results reported in the table.

*Problem 3* Repeat the previous problem for the matrix 

and  
True solution is 

--


