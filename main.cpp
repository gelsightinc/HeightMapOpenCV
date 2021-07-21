#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "HeightMapTmd.h"

int main() {
    
    std::string tmdFile("data/japanese-coin.tmd");

    HeightMapTmd hm(tmdFile);

    TmdInfo metadata = hm.GetMetadata();
    auto matImg = hm.GetHeightMap();

    if (matImg.empty()) {
        std::cout << "Couldn't load the image." << std::endl;
        std::system("pause");  
        return -1;
    }

    double minVal, maxVal;
    cv::minMaxIdx(matImg, &minVal, &maxVal);
    std::cout << "min depth = " << minVal <<  " mm, max depth = " << maxVal << " mm" << std::endl;
    cv::Mat dispImg;
    cv::convertScaleAbs(matImg - minVal, dispImg, 255.0 / (maxVal-minVal));

    cv::Mat imgColor;
    cv::applyColorMap(dispImg, imgColor, cv::COLORMAP_PARULA);

    // use cv::WINDOW_FREERATIO so it fits and can be resized
    cv::namedWindow("HeightMap", cv::WINDOW_FREERATIO);
    cv::imshow("HeightMap", imgColor);

    cv::waitKey(0);

    return 0;
}