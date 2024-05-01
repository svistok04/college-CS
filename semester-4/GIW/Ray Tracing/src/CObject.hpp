//
//  CObject.hpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#ifndef CObject_hpp
#define CObject_hpp

#include<fstream>
#include<iostream>


/// \class CObject
/// \brief Virtual class with object parameters.
///
class CObject {
public:
    glm::vec3 matAmbient; ///< Ambient material parameter (<0,1> range).
    glm::vec3 matDiffuse; ///< Diffuce material parameter (<0,1> range).
    glm::vec3 matSpecular; ///< Specular material parameter (<0,1> range).
    glm::vec3 color;
    float matShininess; ///< Glossines material parameter ((1,n> range).
    bool isTexture; ///< Set to true for objects with textures.
    CImage texture; ///< Texture data.
    float reflectance; ///< Material reflectance (0 - no reflectance, 1 - full reflectance).
    float transmitance; /// stopien przezroczystosci
    
    CObject() {
        reflectance = 0.0f;
        matAmbient = {0,0,0};
        matDiffuse = {0,0,0};
        matSpecular = {0,0,0};
        color = {0, 0, 0};
        matShininess = 0;
        isTexture = false;
    }
    
    // Intersection with ray.
    virtual float intersect(const CRay& ray) {
        return -1.0f;
    }
    
    // Normal vector at intersection point.
    virtual glm::vec3 normal(const glm::vec3& hit_pos) {
        glm::vec3 mret = glm::vec3(0,0,0);
        return mret;
    }
    
    // Normal vector at intersection point.
    virtual glm::vec3 normal() {
        glm::vec3 mret = glm::vec3(0,0,0);
        return mret;
    }

    // Texture mapping.
    virtual glm::vec2 textureMapping(const glm::vec3& hit_pos) {
        glm::vec2 uv = {0,0};
        return uv;
    }
    
};



/// \class CSphere
/// \brief Sphere object representation.
///
class CSphere : public CObject {
public:
    float r; ///< Sphere radius.
    glm::vec3 pos; ///< Position of the sphere center.
    
    CSphere(const glm::vec3& pos, float r) {
        this->pos = pos;
        this->r = r;
    }
    CSphere() {
        r = 1.0f;
        pos = {0,0,0};
    }
    
    float intersect(const CRay& ray) override; // ray-sphere intersection
    glm::vec3 normal(const glm::vec3& hit_pos) override; //  normal vector
    glm::vec2 textureMapping(const glm::vec3& hit_pos) override;

};


/// \class CTriangle
/// \brief Triangle object representation.
///
class CTriangle : public CObject {
public:
    glm::vec3 v0; ///< Position of the triangle vertex.
    glm::vec3 v1; ///< Position of the triangle vertex.
    glm::vec3 v2; ///< Position of the triangle vertex.
    
    CTriangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) {
        this->v0 = v0;
        this->v1 = v1;
        this->v2 = v2;
    }
    CTriangle() {
        v0 = {0,0,0};
        v1 = {0,0,0};
        v2 = {0,0,0};
    }

    float intersect(const CRay& ray) override; // ray-sphere intersection
    glm::vec3 normal(const glm::vec3& pos) override; //  normal vector
    
};


#endif /* CObject_hpp */
