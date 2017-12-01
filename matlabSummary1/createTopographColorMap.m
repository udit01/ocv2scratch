function [  ] = createTopographColorMap( matrix , colorMap )
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
[xx,yy] = createGrid(matrix);
figure;
surf(xx,yy,matrix,colorMap);
zlabel('MeanValues with Skin Highlighted');
shading interp;
colorbar;
end

