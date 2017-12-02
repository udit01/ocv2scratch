function [] = h5plot( colImg , irImg , maskImg)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
img = imread(colImg);
irImage = imread(irImg);
maskImage = imread(maskImg);

red = img(:,:,1); % Red channel
green = img(:,:,2); % Green channel
blue = img(:,:,3); % Blue channel

gray = rgb2gray(img);

a = zeros(size(img, 1), size(img, 2));
%because the the channels don't only contain the RGB they contain a liner
%combination of them

% just_red = cat(3, red, a, a);
% just_green = cat(3, a, green, a);
% just_blue = cat(3, a, a, blue);

% back_to_original_img = cat(3, red, green, blue);
% figure, imshow(img), title('Original image')
% figure, imshow(just_red), title('Red channel')
% figure, imshow(just_green), title('Green channel')
% figure, imshow(just_blue), title('Blue channel')
% figure, imshow(back_to_original_img), title('Back to original image')
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Extract the individual red, green, and blue color channels.
% redChannel = rgbImage(:, :, 1);
% greenChannel = rgbImage(:, :, 2);
% blueChannel = rgbImage(:, :, 3);
% 
% z = zeros(size(rgbImage), class(rgbImage));
% redImage = z; redImage(:,:,1) = redChannel;
% greenImage = z; greenImage(:,:,2) = greenChannel;
% blueImage = z; blueImage(:,:,3) = blueChannel;
% 
% subplot(2,2,1); image(rgbImage);
% subplot(2,2,2); image(redImage);
% subplot(2,2,3); image(greenImage);
% subplot(2,2,4); image(blueImage);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Display them all.
% subplot(3, 3, 2);
% imshow(rgbImage);
% fontSize = 20;
% title('Original RGB Image', 'FontSize', fontSize)
% subplot(3, 3, 4);
% imshow(just_red);
% title('Red Channel in Red', 'FontSize', fontSize)
% subplot(3, 3, 5);
% imshow(just_green)
% title('Green Channel in Green', 'FontSize', fontSize)
% subplot(3, 3, 6);
% imshow(just_blue);
% title('Blue Channel in Blue', 'FontSize', fontSize)
% subplot(3, 3, 8);
% imshow(recombinedRGBImage);
% title('Recombined to Form Original RGB Image Again', 'FontSize', fontSize)
% 
% % Set up figure properties:
% % Enlarge figure to full screen.
% set(gcf, 'Units', 'Normalized', 'OuterPosition', [0, 0, 1, 1]);
% % Get rid of tool bar and pulldown menus that are along top of figure.
% % set(gcf, 'Toolbar', 'none', 'Menu', 'none');
% % Give a name to the title bar.
% set(gcf, 'Name', 'Demo by ImageAnalyst', 'NumberTitle', 'Off') 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%  https://in.mathworks.com/help/matlab/ref/histogram.html
%histogram plotting through Categorial images could be done too ...

% Growable array will take a lot of time so to do what ? first count the
% pixeils with such data
count = 0;
% I get confused in row and column
sizeMask = size(maskImage);% is two dimensional .. in this case
for i = 1:sizeMask(1)
    for j = 1:sizeMask(2)
        if maskImage(i,j)>0
            count = count +1;
        end
    end
end

ch1Arr = zeros(count,1);
ch2Arr = zeros(count,1);
ch3Arr = zeros(count,1);
grayArr = zeros(count,1);
irArr = zeros(count,1);

t = 1;
for i = 1:sizeMask(1)
    for j = 1:sizeMask(2)
        if maskImage(i,j)>0
%             disp(i);disp(j);
            ch1Arr(t) = red(i,j);
            ch2Arr(t) = green(i,j);
            ch3Arr(t) = blue(i,j);
            grayArr(t) = gray(i,j);
            irArr(t) = irImage(i,j,1);
            t = t+1;
        end
    end
end

figure;
histogram(ch1Arr);
ylabel('channel1 Histogram of skin pixels');
savefig('ch1.fig');
saveas(gcf,'ch1.bmp');

figure;
histogram(ch2Arr);
ylabel('channel2 Histogram of skin pixels');
savefig('ch2.fig');
saveas(gcf,'ch2.bmp');

figure;
histogram(ch3Arr);
ylabel('channel3 Histogram of skin pixels');
savefig('ch3.fig');
saveas(gcf,'ch3.bmp');

figure;
histogram(grayArr);
ylabel('grayImage Histogram of skin pixels');
savefig('gray.fig');
saveas(gcf,'gray.bmp');

figure;
histogram(irArr);
ylabel('ir image Histogram of skin pixels');
savefig('irHist.fig');
saveas(gcf,'irHist.bmp');



end

