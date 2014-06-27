function [J, grad] = costFunctionReg(theta, X, y, lambda)
%COSTFUNCTIONREG Compute cost and gradient for logistic regression with regularization
%   J = COSTFUNCTIONREG(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
grad = zeros(size(theta));

% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta.
%               You should set J to the cost.
%               Compute the partial derivatives and set grad to the partial
%               derivatives of the cost w.r.t. each parameter in theta
n = size(theta,1);

sum1 = 0;
for i = 1: m
    sum1 = sum1 + ( -y(i)*log(sigmoid(X(i,:)*theta)) - (1 - y(i))*log(1 - sigmoid(X(i,:)*theta)));
end;

sum2 = 0;
for i = 2: n
    sum2 = sum2 + theta(i)^2;
end;

J = 1/m * sum1 + lambda/(2*m)*sum2;

for j = 1: n
    sum1 = 0;
    for i = 1:m
        sum1 = sum1 + (sigmoid(X(i,:)*theta) - y(i))*X(i,j);
    end;
    if (j == 1) grad(j) = 1/m * sum1;
    else grad(j) = 1/m * sum1 + lambda/m*theta(j);
    
end;




% =============================================================

end
