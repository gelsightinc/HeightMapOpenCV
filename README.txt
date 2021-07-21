This demo shows how to read a 3D file in TMD format into an OpenCV matrix. The 3D data will be a cv::Mat of type CV_32F where every pixel is a height value (Z) in millimeters. A test file, japanese-coin.tmd is provided in the data folder.

Instructions
------------
This demo requires OpenCV (https://opencv.org/) and was tested using the release build of OpenCV-4.5.3. This demo and instructions assume Visual Studio 2019 on Windows.

(1) Download the OpenCV installer and run the executable to unpack the library. Copy the opencv folder to the Solution folder of this project.

(2) The include and library paths are specified in the opencv.props property sheet. Confirm that these paths are valid for your installation

(3) Build and run

