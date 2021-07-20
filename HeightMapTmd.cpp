#include "HeightMapTmd.h"
#include <filesystem>
#include <fstream>

#define TMD_HEADER "Binary TrueMap Data File v2.0"

HeightMapTmd::HeightMapTmd(const std::string& path)
{  
    std::ifstream fin;
    fin.open(path, std::ios::binary);

    if (!fin)
    {
        std::cout << "Error File Not Found " << path << std::endl;
        exit(1);
    }

    m_tmdInfo = GetTmdInfo(fin);
    m_heightMap = ReadHeightMap(fin);


}


TmdInfo HeightMapTmd::GetTmdInfo(std::ifstream& is)
{
    TmdInfo ti;

    // Set stream exception mask to throw on bad bit or on failure.

    // Read header
    char header[32];

    if (!is.read(header, 32))
    {
        std::cout << "Error reading header" << std::endl;
        exit;
    }

    // Check header
    char testid[30] = TMD_HEADER;
    if (strncmp(testid, header, 29) != 0)
    {
        std::cout << "Error reading header" << std::endl;
        exit;
    }

    char commentbuffer[2048];

    // Read comments
    if (!is.read(&commentbuffer[0], 1))
    {
        std::cout << "Error reading comment buffer" << std::endl;
        exit;
    }

    for (int ii = 1; ii < 2048 && commentbuffer[ii - 1] != 0; ++ii)
    {
        if (!is.read(&commentbuffer[ii], 1))
        {
            std::cout << "Error reading comment" << std::endl;
            exit;
        }
    }


    // Read image size
    int32_t imW;
    int32_t imH;
    if (!is.read(reinterpret_cast<char*>(&imW), sizeof(int32_t)))
    {
        std::cout << "Error reading data" << std::endl;
    }

    if (!is.read(reinterpret_cast<char*>(&imH), sizeof(int32_t)))
    {
        std::cout << "Error reading height info" << std::endl;
    }

    float offsetx, offsety, lengthx, lengthy;
    if (!is.read(reinterpret_cast<char*>(&lengthx), sizeof(float)))
    {
        std::cout << "Error reading length" << std::endl;
        exit;
    }
    if (!is.read(reinterpret_cast<char*>(&lengthy), sizeof(float)))
    {
        std::cout << "Error reading length" << std::endl;
        exit;
    }
    if (!is.read(reinterpret_cast<char*>(&offsetx), sizeof(float))) 
    {
        std::cout << "Error reading length" << std::endl;
        exit;
    }
    if (!is.read(reinterpret_cast<char*>(&offsety), sizeof(float)))
    {
        std::cout << "Error reading length" << std::endl;
        exit;
    }

    ti.mmpp = lengthx / static_cast<double>(imW);
    ti.lenXMm = lengthx;
    ti.lenYMm = lengthy;
    ti.offXMm = offsetx;
    ti.offYMm = offsety;
    ti.imgW = imW;
    ti.imgH = imH;

    return ti;

}




cv::Mat HeightMapTmd::ReadHeightMap(std::ifstream& is)
{
    const auto pxOffX = static_cast<int32_t>(std::round(m_tmdInfo.offXMm / m_tmdInfo.mmpp));
    const auto pxOffY = static_cast<int32_t>(std::round(m_tmdInfo.offYMm / m_tmdInfo.mmpp));
    const auto fullW = m_tmdInfo.imgW + pxOffX;
    const auto fullH = m_tmdInfo.imgH + pxOffY;

    cv::Mat heightMap(fullW, fullH, CV_32F);

    for (std::remove_const<decltype(m_tmdInfo.imgH)>::type y = 0; y < m_tmdInfo.imgH; ++y)
    {
        is.read(reinterpret_cast<char*>(heightMap.ptr(y + pxOffY) + pxOffX), sizeof(float)*m_tmdInfo.imgW);
    }

    m_heightMap = heightMap.clone();
    return heightMap;

}
