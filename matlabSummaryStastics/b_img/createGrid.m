function [ meshGX, meshGY ] = createGrid( matrix  )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
 s = size(matrix);
 x = s(2);
 y = s(1);
gridX = zeros(x,1);
gridY = zeros(y,1);
    for i = 1:x
       gridX(i,1) = i;
    end;
    for j = 1:y
       gridY(j,1) = j;
    end;
        
[meshGX,meshGY] = meshgrid(gridX,gridY);
end

