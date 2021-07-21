This demo shows how to read a 3D file in TMD format into an OpenCV matrix. The 3D data will be a cv::Mat of type CV_32F where every pixel is a height value (Z) in millimeters. A test file, japanese-coin.tmd is provided in the data folder.

Instructions
------------
This demo requires OpenCV (https://opencv.org/) and was tested using the release build of OpenCV-4.5.3. This demo and instructions assume Visual Studio 2019 on Windows.

(1) Download the OpenCV installer and run the executable to unpack the library. Copy the opencv folder to the Solution folder of this project.

(2) The include and library paths are specified in the opencv.props property sheet. Confirm that these paths are valid for your installation

(3) Build and run


Outputs
-------

The demo should show the 3D heightmap in a window and print information to the console:

loaded    :data/japanese-coin.tmd
size      : 3162 x 3189 pixels
resolution: 0.00878483 millimeters-per-pixel
min depth : -0.35 mm
max depth : 0.480618 mm
