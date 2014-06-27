function idx = findClosestCentroids(X, centroids)
%FINDCLOSESTCENTROIDS computes the centroid memberships for every example
%   idx = FINDCLOSESTCENTROIDS (X, centroids) returns the closest centroids
%   in idx for a dataset X where each row is a single example. idx = m x 1 
%   vector of centroid assignments (i.e. each entry in range [1..K])
%

% Set K
K = size(centroids, 1);

% You need to return the following variables correctly.
idx = zeros(size(X,1), 1);

% ====================== YOUR CODE HERE ======================
% Instructions: Go over every example, find its closest centroid, and store
%               the index inside idx at the appropriate location.
%               Concretely, idx(i) should contain the index of the centroid
%               closest to example i. Hence, it should be a value in the 
%               range 1..K
%
% Note: You can use a for-loop over the examples to compute this.
%

% 1. for each input:
% 1.1 set distance to some value;
% 1.1 for each centroid;
% 1.1.1 compute the distance;
% 1.1.2 compare the distance with the minimal one;
% 1.2 set the index for input.

m = size(idx);
for i = 1:m
    minimalDistance = -1;
    centroid = -1;
    for j = 1:K
        someDistance = norm(X(i,:) - centroids(j,:))^2;
        if (minimalDistance < 0)
            minimalDistance = someDistance;
            centroid = j;
        end;
        if (minimalDistance > someDistance)
            minimalDistance = someDistance;
            centroid = j;
        end;
    end;
    idx(i) = centroid;
end;







% =============================================================

end

