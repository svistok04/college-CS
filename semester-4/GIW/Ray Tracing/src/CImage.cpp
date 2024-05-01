//
//  CImage.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 20/01/2023.
//

#include "rt.h"


/// \fn save(std::string fname)
/// \brief Writes image to disk file.
/// \param fname Image file name with extension (e.g., .png).
///
void CImage::save(const std::string& fname) {
    
    save(fname, false);

};


/// \fn save(std::string filename)
/// \brief Writes image to disk file.
/// \param filename Image file name with extension (e.g., .png).
/// \param is_gamma_correction Set to true if gamma correction need to be applied.
///
void CImage::save(const std::string& filename, bool is_gamma_correction) {
    
    cv::Mat img_8bit = cv::Mat(cvSize(width, height), CV_8UC3, cv::Scalar(0,0,0)); // 8-bits RGB image

    float2uchar(img_8bit, is_gamma_correction);
    
    cv::imwrite(filename, img_8bit);
}


/// \fn setPixel(int x, int y, glm::vec3 rgb)
/// \brief Set image pixel value.
/// \param x Horizontal position in image raster.
/// \param y Vertical position in image raster.
/// \param rgb RGB color values in floating point format (<0,1> range).
///
void CImage::setPixel(int x, int y, const glm::vec3& rgb) {

    cv::Vec3f vec(rgb.z, rgb.y, rgb.x); // changed channel orders

    img.at<cv::Vec3f>(cv::Point(x,y)) = vec;
}


/// \fn getImage(void)
/// \brief Returns image object.
cv::Mat CImage::getImage() {
    return img;
}


/// \fn applyGammaCorrection(void)
/// \brief Applies gamma correction to each pixel in the image.
void CImage::float2uchar(cv::Mat& img_8bit, bool is_gamma_correction) {
        
    for(int j = 0; j < img.rows; j++) {
        for(int i = 0; i < img.cols; i++) {

            cv::Vec3f vecf = img.at<cv::Vec3f>(cv::Point(i,j));

            // gamma correction
            if(is_gamma_correction) {
                float gamma = 2.2f;
                vecf[0] = powf(vecf[0], 1.0f/gamma);
                vecf[1] = powf(vecf[1], 1.0f/gamma);
                vecf[2] = powf(vecf[2], 1.0f/gamma);
            }

            vecf = vecf * 255.0f;

            auto r = (uint8_t)vecf[2];
            auto g = (uint8_t)vecf[1];
            auto b = (uint8_t)vecf[0];

            img_8bit.at<cv::Vec3b>(cv::Point(i,j)) = cv::Vec3b(b,g,r);
        }
      }
}

/// \fn float2uchar(void)
/// \brief Applies gamma correction to each pixel in the image.
void CImage::float2uchar(cv::Mat& img_8bit) {
    float2uchar(img_8bit, false);
}


/// \fn plotCalibChart(void)
/// \brief Plots calibration chart in image.
void CImage::plotCalibChart() {
    glm::vec3 color = {1,1,1};
}


/// \fn drawCircle(int x, int y, float radius)
/// \brief Draws circle in image.
void CImage::drawCircle(glm::vec3 p, float radius, const glm::vec3& color) {
    
    p = f2s(p);
    radius = radius/2.0f*(float)width;
    cv::circle(img, cv::Point((int)p.x, (int)p.y), (int)radius, cv::Vec3f(color.z,color.y,color.x), 2);
}


/// \fn drawLine(int x0, int y0, int x1, int y1, glm::vec3 color)
/// \brief Draws line in image.
void CImage::drawLine(glm::vec3 p0, glm::vec3 p1, const glm::vec3& color) {
    
    p0 = f2s(p0);
    p1 = f2s(p1);
    cv::line(img, cv::Point((int)p0.x, (int)p0.y), cv::Point((int)p1.x, (int)p1.y), cv::Vec3f(color.z,color.y,color.x), 2);
}


/// \brief Creates texture image.
/// \param width Width of the image in [pixels].
/// \param height Height of the image in [pixels]
/// \return Returns object of the created image.
CImage CImage::createTexture(int width, int height) {

    CImage image;

    int a = width / 8;
    image.img = cv::Mat::zeros(width, height, CV_8UC3);

    cv::Vec3b col1 = {10,10,10};
    cv::Vec3b col2 = {200,200,200};
    cv::Vec3b col;

    bool bb = true;
    col = col1;
    int cc = 0;
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            image.img.at<cv::Vec3b>(cv::Point(x,y)) = col;
        }
        if(cc >= 20) {
            bb = !bb;
            cc = 0;
            col = bb ? col1 : col2;
        }
        cc++;
    }

    cv::imwrite("texture_stripes.png", image.img);

    return image;
}

/// \brief Returns pixel value.
/// \param image CImage object with image data.
/// \param u Horizontal texture coordinate in <0.1> range.
/// \param v Vertical texture coordinate in <0.1> range.
/// \return Returns pixel color in <0,1> range.
glm::vec3 CImage::getTexel(const CImage& image, float u, float v) {

    cv::Mat img = image.img;
    int x = (int)((float)img.cols * u);
    int y = (int)((float)img.rows * v);

    cv::Vec3b RGB = img.at<cv::Vec3b>(cv::Point(x,y));

    glm::vec3 rgb;
    rgb.x = (float)RGB[2] / 255.0f;
    rgb.y = (float)RGB[1] / 255.0f;
    rgb.z = (float)RGB[0] / 255.0f;

    return rgb;
}