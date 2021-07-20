#pragma once
#include <iostream>
#include <opencv2/core/mat.hpp>

//Reads a 3D measurement saved in TMD format

class TmdInfo {

public:
    int32_t     imgW;       // width in pixels
    int32_t     imgH;       // height in pixels
    float       lenXMm;     // length of the xaxis in millimeters
    float       lenYMm;     // length of the yaxis in millimeters
    float       offXMm;     // offset along the x axis in millimeters
    float       offYMm;     // offset along the y axis in millimeters
    double      mmpp;       // resolution millimeters per pixel
    std::string comment;

};

class HeightMapTmd
{
public:

    //reads the 3D surface from the file path specified
    HeightMapTmd(const std::string& path);

    cv::Mat GetHeightMap() { return m_heightMap; };
    TmdInfo GetMetadata() { return m_tmdInfo; };


private:

    TmdInfo GetTmdInfo(std::ifstream& is);
    cv::Mat ReadHeightMap(std::ifstream& is);
    
    cv::Mat m_heightMap;  // 3D surface Z values in millimeters

    TmdInfo m_tmdInfo;    // Image metadata

};

