function [  ] = createTopographColorMap( matrix , colorMap , msg , fileName )
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
[xx,yy] = createGrid(matrix);
figure;
surf(xx,yy,matrix,colorMap);
zlabel(msg);
% shading interp;
colorbar;
savefig(fileName);
end

