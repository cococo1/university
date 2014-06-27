function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);
         
% You need to return the following variables correctly 
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%


K = num_labels;
X = [ones(m, 1) X];
s = 0;

size(X);
size(y);
size(Theta1);
size(Theta2);

z2 = Theta1 * X';
a2 = sigmoid(z2);
a2 = [ones(m,1) a2'];
a2 = a2';
%     size(a2);
z3 = Theta2 * a2;
a3 = sigmoid(z3);
a3 = a3';

for i = 1: m
    s1  = 0;
    
    modifiedY = [1:K] == y(i);
%     if (y(i) == 0)
%         modifiedY(K) = 1;
%     end;
%     [a,hTheta] = max (a3(i) , [], 2);



    hTheta = a3(i,:);
    %     for k = 1: K
    % 
    %         s1 = s1 + -modifiedY(k)*log(hTheta(k)) - (1 - modifiedY(k))*log(1 - hTheta(k));
    %     end;
    %     s = s + s1;
    s =s - log(hTheta)*modifiedY' - log(1 - hTheta)*(1 - modifiedY)';
    

end;

    
J = 1/m * s;

% Regularization: b = lambda / (2*m)*sum(theta(2:end).^2);
% s = 0;
% size(Theta1,1);
% size(Theta1,2);
% Theta1(1,1);
J = J + lambda/(2*m)*( sum(sum(Theta1(:,2:end).^2)) + sum(sum(Theta2(:,2:end).^2)) );
% for i = 1:size(Theta1,1)
% %     for j = 2:size(Theta1,2)
% %         s = s + Theta1(i,j)^2;
% %     end;
% % end;
% 
% J = J + lambda/(2*m)*s;
% 
% s = 0;
% for i = 1:size(Theta2,1)
%     for j = 2:size(Theta2,2)
%         s = s + Theta2(i,j)^2;
%     end;
% end;
% J = J + lambda/(2*m)*s;




% Gradient:

delta1 = zeros(size(Theta1));
delta2 = zeros(size(Theta2));
for t = 1:m
    %Step 1:
    a1 = X(t,:);
%     a1 = [1; a1'];
%     a1 = a1';
    z2 = Theta1 * a1';
    a2 = sigmoid(z2);
    a2 = [1; a2];
%     a2 = a2';
    %     size(a2);
    z3 = Theta2 * a2;
    a3 = sigmoid(z3);
    a3 = a3';
    
%     Step 2:
    modifiedY = [1:K] == y(t);
    deltaSmall3 = a3 - modifiedY;
    deltaSmall3 = deltaSmall3';
    
    
%     Step 3:
    deltaSmall2 = Theta2'*deltaSmall3;
    %z2 has one element less... in the end, we would not count
    %deltaSmall0... so, just add one element for z2...
    z2 = [1; z2];
    sg = sigmoidGradient(z2);
    deltaSmall2 = deltaSmall2.*sg;
    
%     Step 4:
    deltaSmall2 = deltaSmall2(2:end); %skip the first, biased element
    delta1 = delta1 + deltaSmall2*a1;
    delta2 = delta2 + deltaSmall3*a2';

end;

% Step 5:
Theta1_grad = 1/m*delta1; 
Theta2_grad = 1/m*delta2; % + lambda/m*Theta2(:,2:end);
for i = 1:size(Theta1,1)
    for j = 2:size(Theta1,2)
        Theta1_grad(i,j) = Theta1_grad(i,j) + lambda/m*Theta1(i,j);
    end;
end;
    
for i = 1:size(Theta2,1)
    for j = 2:size(Theta2,2)
        Theta2_grad(i,j) = Theta2_grad(i,j) + lambda/m*Theta2(i,j);
    end;
end;















% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end
