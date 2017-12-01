function [] = drawCTCM(img)
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here
% clear;
meanCol = csvread(strcat( img , '_mean_color.csv'));
stdDevCol =  csvread(strcat( img , '_stdDev_color.csv'));
bool = csvread(strcat( img , '_boolValues.csv'));

meanIr = csvread(strcat( img, '_mean_ir.csv'));
stdDevIr =  csvread(strcat( img , '_stdDev_ir.csv'));

createTopographColorMap(meanCol,bool,'Mean of Colored Image with skin highlighted','colorMean.fig');
createTopographColorMap(meanIr,bool,'Mean of IR Image with skin highlighted','colorStdDev.fig');
createTopographColorMap(stdDevCol,bool,'Std Dev of Colored Image with skin highlighted','irMean.fig');
createTopographColorMap(stdDevIr,bool,'Std Dev of IR Image with skin highlighted','irStdDev.fig');

end

