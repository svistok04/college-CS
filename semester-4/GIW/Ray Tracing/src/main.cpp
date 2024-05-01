
#include <iostream>
#include "rt.h"

extern void draw_rect(CImage&, const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&);
extern void draw_robot();
extern void draw_triangles();

///
int main (int argc, char * const argv[]) {
    
//    draw_triangles();
//    return 0;
    
    std::cout << "ray tracing ... \n";

    CScene scene;
    scene.create(); // defines sample scene parameters
    if(scene.cam.width == 0) {
        std::cout << "WARNING: scene not defined" << std::endl;
        return -1;
    }
    // draw_triangles();
    // draw_robot();
    CRayTrace rt;
    CRay ray;
    COutput results;
    
    /// computes primary ray matrix, cw. 4
    glm::mat3 ray_matrix;
    CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);
    std::cout << "Camera projection matrix:" << std::endl;
    PRINT_MAT3(ray_matrix);

    /// computes ray direction for sample pixel positions
    ray.pos = scene.cam.eyep;
    // float fx = 0.5f;
    // float fy = 0.5f;
    // cw. 5
    float fx = scene.cam.width/2.0f-1+0.5f;
    float fy = scene.cam.height/2.0f-1+0.5f;
    ray.dir = glm::normalize(ray_matrix * glm::vec3(fx, fy, 1.0f));
    std::cout << "Ray direction for pixel (" << fx << ", " << fy << "): " << ray.dir.x << ", " << ray.dir.y << ", " << ray.dir.z << std::endl;

    /// creates raster image object
    CImage image(scene.cam.width, scene.cam.height);
    // cw. 6
    // for (int i = 0; i < scene.cam.width; ++i) {
    //     for (int j = 0; j < scene.cam.height; ++j) {
    //
    //         float fx = static_cast<float>(i) + 0.5f;
    //         float fy = static_cast<float>(j) + 0.5f;
    //         ray.dir = glm::normalize(ray_matrix * glm::vec3(fx, fy, 1.0f));
    //         glm::vec3 rgb(0.0f, 0.0f,0.0f);
    //         rgb.x = (ray.dir.x + 1.0f) / 2.0f;
    //         image.setPixel(i, j, rgb);
    //
    //         rgb = glm::vec3(0.0f, 0.0f,0.0f);
    //         rgb.y = (ray.dir.y + 1.0f) / 2.0f;
    //         image.setPixel(i, j, rgb);
    //
    //         rgb = glm::vec3(0.0f, 0.0f,0.0f);
    //         rgb.z = (ray.dir.z + 1.0f) / 2.0f;
    //         image.setPixel(i, j, rgb);
    //     }
    // }
    // image.save("../gradient3.png", false);

    // cv::imshow("image", image.getImage());
    // cv::waitKey();

    // cw. 8
    // ray.pos = glm::vec3{0.0f, 0.0f, 10.0f};
    // ray.dir = glm::vec3{0.3f, 0.3, -1.0f};
    // std::cout << "t = " << scene.objectList[0]->intersect(ray);

    // cw. 9-10
    /// main loop
    CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);
    for (int j = 0; j < scene.cam.height; ++j) {
        for (int i = 0; i < scene.cam.width; ++i) {
            float fx = static_cast<float>(i) + 0.5f;
            float fy = static_cast<float>(j) + 0.5f;
            ray.pos = scene.cam.eyep;
            ray.dir = glm::normalize(ray_matrix * glm::vec3(fx, fy, 1.0f));
            results.col = {0, 0, 0};
            results.energy = 1.0;
            results.tree = 0;
            rt.rayTrace(scene, ray, results);
            if (results.col.x > 1 || results.col.y > 1 || results.col.z > 1) {
                results.col = {1, 1, 1};
            }
            image.setPixel(i, j, results.col);
        }
    }
    image.save("../reflectance1.png", false);

    std::cout << std::endl;

    ray.pos = {0, 0, 0};
    ray.dir = {0.5, 0.5, 0.0};
    glm::vec3 n(0, 1.0, 0);
    glm::vec3 pos = {0, 0, 0};
    CRay ray_reflected = CRayTrace::reflectedRay(ray, n, pos);
    std::cout << "ray_reflected.pos = [" << ray_reflected.pos.x << "," << ray_reflected.pos.y << "," << ray_reflected.pos.z << "]" << std::endl;
    std::cout << "ray_reflected.dir = [" << ray_reflected.dir.x << "," << ray_reflected.dir.y << "," << ray_reflected.dir.z << "]" << std::endl;


    /// position of the image point
    // float fx = static_cast<float>(i) + 0.5f;
    // float fy = static_cast<float>(j) + 0.5f;
            /// ...

            /// primary ray
            /// ...

            /// background color
            // results.col = {0,0,0};
            /// secondary ray counter
            // results.tree = 0;
            /// ray energy
            // results.energy = 1.0f;
            
            /// rendering
            /// rt.rayTrace(scene, ray, results);

            /// handles pixel over-saturation
            // if(results.col.x > 1 || results.col.y > 1 || results.col.z > 1) {
            //    results.col = {1,1,1};
            //}

            /// writes pixel to output image
            // image.setPixel(i, j, results.rgb);


    /// writes image to disk file with gamma correction
    // image.save("output.png", true);

    // cv::imshow("image", image.getImage());
    // cv::waitKey();
    
    std::cout << std::endl << std::endl;
    return 0;
}

void draw_rect(CImage& img, const glm::vec3& pp0, const glm::vec3& pp1, const glm::vec3& pp2, const glm::vec3& pp3, const glm::vec3& color) {
    img.drawLine(pp0, pp1, color);
    img.drawLine(pp1, pp2, color);
    img.drawLine(pp2, pp3, color);
    img.drawLine(pp3, pp0, color);
}

/// Draws two trianges
void draw_triangles() {
    CImage img(1000, 1000);
    
    glm::vec3 color1(0.9,0.1,0.1); // red
    glm::vec3 color2(0.1,0.9,0.1); // green
    
    // draw circle
    glm::vec3 pp(0.0,0.0,1.0);
    float radius = 0.1f;
    img.drawCircle(pp, radius, color1);
    
    // triangle vertices
    glm::vec3 pp0(0.4, 0.3, 1);
    glm::vec3 pp1(-0.4, 0.3, 1);
    glm::vec3 pp2(0.4, -0.3, 1);
    std::cout << "(" << pp0.x << ", " << pp0.y << ", " << pp0.z << ")" << std::endl;
    // draws triangle in 2D
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp1, pp2, color1);
    img.drawLine(pp2, pp0, color1);
    
    // translation
    float tX = 0.2f; // OX translation
    float tY = 0.1f; // OY translation
    glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix
    PRINT_MAT3(mTrans);

    // translation of vertices
    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;
    std::cout << "(" << pp0.x << ", " << pp0.y << ", " << pp0.z << ")" << std::endl;

    // draws triangle after translation
    img.drawLine(pp0, pp1, color2);
    img.drawLine(pp1, pp2, color2);
    img.drawLine(pp2, pp0, color2);

    img.save("../triangles.png");
    cv::imshow("TRIANGLES", img.getImage());
    cv::waitKey();

}

/// Draws robot. cw. 2
void draw_robot() {
    CImage img(1000, 1000);
    glm::vec3 color1(1.0,0.7,0.2); // yellow

    glm::vec3 pp(0.0,0.5,1.0);
    float radius = 0.1f;
    img.drawCircle(pp, radius, color1);

    float tYX = 0.15f;

    glm::vec3 rectPP0(tYX, tYX, 1.0); // left-upper
    glm::vec3 rectPP1(-tYX, tYX, 1.0); // right-upper
    glm::vec3 rectPP2(-tYX, -tYX, 1.0); // right-bottom
    glm::vec3 rectPP3(tYX, -tYX, 1.0); // left-bottom
    // torso
    float sX = 1.0f;
    float sY = 2.4f;
    glm::mat3x3 mScale {{sX,0,0}, {0,sY,0}, {0,0,1}}; // make taller
    glm::vec3 torsoPP0 = mScale * rectPP0;
    glm::vec3 torsoPP1 = mScale * rectPP1;
    glm::vec3 torsoPP2 = rectPP2;
    glm::vec3 torsoPP3 = rectPP3;
    draw_rect(img, torsoPP0, torsoPP1, torsoPP2, torsoPP3, color1);
    // arms
    float tX = 0.35f;
    float tY = 0.4f;
    glm::mat3x3 mTrans{{1, 0, 0}, {0, 1, 0}, {tX, tY, 1}};
    glm::mat3x3 mScaleUp = glm::mat3x3{{1.0f,0,0}, {0,0.65f,0}, {0,0,1}};
    glm::mat3x3 mScaleLeft = glm::mat3x3{{1.1f,0,0}, {0,1.0f,0}, {0,0,1}};
    glm::vec3 armPP0 = mScaleLeft * mScaleUp * mTrans * rectPP0;
    glm::vec3 armPP1 = mScaleUp * mTrans * rectPP1;
    glm::vec3 armPP2 = mTrans * rectPP2;
    glm::vec3 armPP3 = mScaleLeft * mTrans * rectPP3;
    draw_rect(img, armPP0, armPP1, armPP2, armPP3, color1);
    glm::mat3x3 mScaleMirror{{-1.0f,0,0}, {0,1.0f,0}, {0,0,1}};
    armPP0 = mScaleMirror * armPP0;
    armPP1 = mScaleMirror * armPP1;
    armPP2 = mScaleMirror * armPP2;
    armPP3 = mScaleMirror * armPP3;
    draw_rect(img, armPP0, armPP1, armPP2, armPP3, color1);
    // legs
    tX = 0.16f;
    tY = -0.4f;
    mTrans = glm::mat3x3{{1, 0, 0}, {0, 1, 0}, {tX, tY, 1}}; // tranpose to the correct position
    mScaleLeft = glm::mat3x3{{0.45f,0,0}, {0,1.0f,0}, {0,0,1}}; // make thinner
    glm::mat3x3 mScaleDown = glm::mat3x3{{1.0f, 0, 0}, {0, 1.15f, 0}, {0, 0, 1}}; // make longer
    float angle = glm::radians(25.0f);
    glm::mat3x3 mRot{{glm::cos(angle), glm::sin(angle), 0}, {-glm::sin(angle), glm::cos(angle), 0}, {0, 0, 1}}; // rotate by 25 degrees
    glm::vec3 legPP0 = mRot * mScaleLeft * mTrans * rectPP0;
    glm::vec3 legPP1 = mRot * mTrans * rectPP1;
    glm::vec3 legPP2 = mRot * mScaleDown * mTrans * rectPP2;
    glm::vec3 legPP3 = mRot * mScaleDown * mScaleLeft * mTrans * rectPP3;
    draw_rect(img, legPP0, legPP1, legPP2, legPP3, color1);
    legPP0 = mScaleMirror * legPP0;
    legPP1 = mScaleMirror * legPP1;
    legPP2 = mScaleMirror * legPP2;
    legPP3 = mScaleMirror * legPP3;
    draw_rect(img, legPP0, legPP1, legPP2, legPP3, color1);

    img.save("../robot.png");
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();
}