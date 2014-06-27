function [C, sigma] = dataset3Params(X, y, Xval, yval)
%EX6PARAMS returns your choice of C and sigma for Part 3 of the exercise
%where you select the optimal (C, sigma) learning parameters to use for SVM
%with RBF kernel
%   [C, sigma] = EX6PARAMS(X, y, Xval, yval) returns your choice of C and 
%   sigma. You should complete this function to return the optimal C and 
%   sigma based on a cross-validation set.
%

% You need to return the following variables correctly.
C = 1;
sigma = 0.3;

% ====================== YOUR CODE HERE ======================
% Instructions: Fill in this function to return the optimal C and sigma
%               learning parameters found using the cross validation set.
%               You can use svmPredict to predict the labels on the cross
%               validation set. For example, 
%                   predictions = svmPredict(model, Xval);
%               will return the predictions on the cross validation set.
%
%  Note: You can compute the prediction error using 
%        mean(double(predictions ~= yval))
%

%1. Generate all possible combinations of (C, sigma);
%2. For each combination:
%2.1 train the model;
%2.2 get the predictions;
%2.3 compute the error;
%2.4 compare the error: if smaller, save the mest (C, sigma) pair;

cSet = [.01 .03 .1 .3 1 3 10 30];
sigmaSet = cSet;
minimalError = 1000000000;
for possibleC = cSet
    for possibleSigma = sigmaSet
%         possibleC = cSet(i)
%         possibleSigma = sigmaSet(j)
        model = svmTrain(X, y, possibleC, @(x1, x2) gaussianKernel(x1, x2, possibleSigma)); 
        predictions = svmPredict(model, Xval);
        currentError = mean(double(predictions ~= yval));
        if (currentError < minimalError)
            minimalError = currentError;
            C = possibleC;
            sigma = possibleSigma;
        end;
    end;
end;

C
sigma

        





% =========================================================================

end
