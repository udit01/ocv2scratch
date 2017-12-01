function [] = drawCTCM(img1,img2)
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here
% clear;
mean1 = csvread(strcat( img1, '_mean.csv'));
bool1 = csvread(strcat( img1, '_boolValues.csv'));

mean2 = csvread(strcat( img2, '_mean.csv'));
bool2 = csvread(strcat( img2, '_boolValues.csv'));

createTopographColorMap(mean1,bool1);
createTopographColorMap(mean2,bool2);

end

