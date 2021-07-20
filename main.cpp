#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "HeightMapTmd.h"

int main() {
    
    std::string tmdFile("C:/Users/Public/Documents/GelSight/Scans/japanese-coin.tmd");

    HeightMapTmd hm(tmdFile);

    TmdInfo metadata = hm.GetMetadata();
    auto matImage = hm.GetHeightMap();

    if (matImage.empty()) {
        std::cout << "Couldn't load the image." << std::endl;
        std::system("pause");  
        return -1;
    }

    cv::Mat dispImg;
    double minVal, maxVal;
    cv::minMaxIdx(matImage, &minVal, &maxVal);
    std::cout << "min depth = " << minVal <<  " mm, max depth = " << maxVal << " mm" << std::endl;
    cv::convertScaleAbs(matImage, dispImg, 255/maxVal);
    cv::Mat imgColor;
    cv::applyColorMap(dispImg, imgColor, cv::COLORMAP_TURBO);

    // use cv::WINDOW_FREERATIO so it fits and can be resized
    cv::namedWindow("HeightMap", cv::WINDOW_FREERATIO);
    cv::imshow("HeightMap", imgColor);

    cv::waitKey(0);

    return 0;
}