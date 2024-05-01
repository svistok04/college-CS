//
//  CObject.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"
#include "CObject.hpp"

// cw. 8
/// \fn intersect(CRay ray)
/// \brief Computes intersection between ray and sphere.
/// \param ray Ray parameters.
/// \return Distance from camera position to the closest intersection point, or negative value.
float CSphere::intersect(const CRay& ray) {
    float A = glm::dot(ray.dir, ray.dir);
    float B = 2.0f * glm::dot(ray.dir, ray.pos - this->pos);
    float C = glm::dot(ray.pos - this->pos, ray.pos - this->pos) - this->r * this->r;
    float delta = B * B - 4 * A * C;
    float t1 = (-B - glm::sqrt(delta)) / (2 * A);
    float t2 = (-B + glm::sqrt(delta)) / (2 * A);
    if (t1 <= 0 && t2 <= 0) {
        return -1;
    }
    if (t1 >= t2) {
        return t2;
    }
    return t1;
}

// cw. 11
/// Normal vector to the sphere surface
/// \fn normal(glm::vec3 hit_pos)
/// \brief Surface normal vector at the intersection point.
/// \param hit_pos Intersection point.
/// \return Normal vector parameters.
glm::vec3 CSphere::normal(const glm::vec3& hit_pos) {
    glm::vec3 n = glm::normalize(hit_pos - this->pos);
    return n;
}
// cw. 13
/// Computes texture mapping coordinates (u,v).
/// \param normal_vec Normalized normal vector at intersection point.
/// \return (u,v) texture coordinates in <0,1> range.
glm::vec2 CSphere::textureMapping(const glm::vec3& normal_vec) {
    glm::vec2 uv = {0,0};
    float u = 0.5 + glm::asin(normal_vec[0])/M_PI;
    float v = 0.5 - glm::asin(normal_vec[1])/M_PI;
    uv[0] = u;
    uv[1] = v;
    return uv;
}


// cw. 10
/// \fn intersect(CRay ray)
/// \brief Computes intersection between triangle and sphere.
/// \param ray Ray parameters.
/// \return Distance from camera position to the closest intersection point, or negative value.
float CTriangle::intersect(const CRay& ray) {
    glm::vec3 baryPosition;
    bool intersects = glm::intersectRayTriangle(ray.pos, ray.dir, this->v0, this->v1, this->v2, baryPosition);

    if (!intersects) {
        return -1.0;
    }
    float t = baryPosition.z;
    if (t <= 0) {
        return -1.0f;
    }

    return t;
}


/// \fn normal(glm::vec3 hit_pos)
/// \brief Surface normal vector at the intersection point.
/// \param hit_pos Intersection point (not used for triangle).
/// \return Normal vector parameters.
///
// cw. 11
glm::vec3 CTriangle::normal(const glm::vec3& hit_pos) {
    glm::vec3 u = this->v1 - this->v0;
    glm::vec3 v = this->v2 - this->v0;
    glm::vec3 n = glm::normalize(glm::cross(u, v));
    return n;
}



