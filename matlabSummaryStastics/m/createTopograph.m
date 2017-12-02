function [  ] = createTopograph( matrix )
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
[xx,yy] = createGrid(matrix);
figure;
surf(xx,yy,matrix);
zlabel('MeanValues');
colorbar;
end

