//
//  CImage.hpp
//  rt
//
//  Created by Radoslaw Mantiuk on 20/01/2023.
//

#ifndef CImage_hpp
#define CImage_hpp

#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

/// \class CImage
/// \brief Image I/O class.
///
class CImage {
private:
    cv::Mat img; ///< Object with image data.
    
    int width; ///< Horizontal resolution in pixels.
    int height; ///< Vertical resolution in pixels.
    
public:

    CImage() {
        width = 0;
        height = 0;
    }

    CImage(int width, int height) {
        this->width = width;
        this->height = height;
        img = cv::Mat(cvSize(width, height), CV_32FC3, cv::Vec3f(0.1f,0.1f,0.1f)); // 32-bits float RGB image
    }
    
    cv::Mat getImage();
    
    void save(const std::string& fname);
    void save(const std::string& filename, bool is_gamma_correction);
    
    void setPixel(int x, int y, const glm::vec3& rgb);
    
    void plotCalibChart();
    
    void drawCircle(glm::vec3 p, float radius, const glm::vec3& color);
    void drawLine(glm::vec3 p0, glm::vec3 p1, const glm::vec3& color);

    static CImage createTexture(int width, int height);
    static glm::vec3 getTexel(const CImage& img, float x, float y);

private:
    void float2uchar(cv::Mat& img_8bit, bool is_gamma_correction);
    void float2uchar(cv::Mat& img_8bit);
    
    [[nodiscard]] glm::vec3 f2s(const glm::vec3& p) const {
        glm::vec3 mret = glm::vec3(((float)width - (p.x+1)/2*(float)width), ((float)height - (p.y+1)/2*(float)height), p.z);
        return mret;
    }

};


#endif /* CImage_hpp */
