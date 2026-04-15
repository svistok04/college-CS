//
//  CRayTrace.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"
#include "CRayTrace.hpp"

const int MAX_RAY_TREE = 1;
const float MIN_RAY_ENERGY = 0.01;

/// \fn compPrimaryRayMatrix(CCamera cam, glm::mat3& m)
/// \brief Computation of the projection matrix.
/// \param cam Camera parameters.
/// \param m Output projection matrix.
///
bool CRayTrace::compPrimaryRayMatrix(const CCamera& cam, glm::mat3& m) {
    // Calculate normalized direction vectors
    glm::vec3 look = cam.lookp - cam.eyep;
    glm::vec3 u = glm::cross(cam.up, look) / glm::length(glm::cross(cam.up, look));
    glm::vec3 v = glm::cross(u, look) / glm::length(glm::cross(u, look));

    glm::vec3 o = look / glm::length(look) * static_cast<float>(cam.width) / (2.0f * glm::tan(glm::radians(cam.fov) / 2.0f)) -
        (cam.width / 2.0f * u + cam.height / 2.0f * v);

    m[0] = u;
    m[1] = v;
    m[2] = o;

    return true;
}




/// \fn rayTrace(CScene scene, CRay& ray, COutput& out)
/// \brief Traces single ray.
/// \param scene Object with all scene components including a camera.
/// \param ray Ray parameter (primary and secondary rays).
/// \param out Object with output color and parameters used in recursion.
///
bool CRayTrace::rayTrace(const CScene& scene, CRay& ray, COutput& res) {
    /// looks for the closest object along the ray path
    /// returns false if there are no intersections
    /// cw. 9
    float tmin = std::numeric_limits<float>::max();
    bool isIntersection = false;
    CObject* hitObj = nullptr;
    for (auto* object : scene.objectList) {
        float t = object->intersect(ray);
        if (t > 0.001 && t < tmin) {
            tmin = t;
            isIntersection = true;
            hitObj = object;
        }
    }

    if (!isIntersection) {
        return false;
    }

    res.col = hitObj->color;
    /// computes 3D position of the intersection point
    glm::vec3 p = ray.pos + tmin * ray.dir;
    /// computes normal vector at intersection point
    glm::vec3 n = hitObj->normal(p);
    // cw. 12
    /// for each light source defined in the scene
    for (const auto& light : scene.lightList) {
        /// computes ambient color component
        res.col += res.energy * light.color * hitObj->matAmbient;
        /// computes vector from p to light position
        glm::vec3 L = glm::normalize(light.pos - p);
        // compute normalized shadow ray from the intersection points towards the light source
        CRay rayShadow;
        rayShadow.pos = p;
        rayShadow.dir = glm::normalize(light.pos - p);
        /// computes if the intersection point is in the shadows
        bool inShadow = false;
        for (auto *object: scene.objectList) {
            if (object != hitObj) {
                float tShadow = object->intersect(rayShadow);
                if (tShadow > 0.001f && tShadow < glm::length(light.pos - p)) {
                    inShadow = true;
                    break;
                }
            }
        }
        if (!inShadow) {
            // computes angle between normal and light vector
            float cos_angle = glm::dot(n, L);
            /// if the surface is reflective
            if (cos_angle > 0.001) {
                // compute and add diffuse color component
                res.col += res.energy * light.color * hitObj->matDiffuse * cos_angle;
                // compute half angle vector h
                glm::vec3 V = -ray.dir;
                glm::vec3 h = glm::normalize(L + V);
                // compute angle between n and h
                float cos_beta = glm::dot(n, h);
                if (cos_beta > 0.001) {
                    // compute and add specular color component
                    res.col += res.energy * light.color * hitObj->matSpecular * glm::pow(cos_beta, hitObj->matShininess);
                }
            }
        }
        // computes the secondary ray parameters (reflected ray)
        if (hitObj->reflectance > 0 && res.tree < MAX_RAY_TREE && res.energy > MIN_RAY_ENERGY) {
            ++res.tree;
            res.energy *= hitObj->reflectance;
            CRay secondaryRay = reflectedRay(ray, n, p);
            rayTrace(scene, secondaryRay, res);
        }
    }
        // adds texture for textured spheres
        if (hitObj->isTexture) {
            glm::vec2 uv = hitObj->textureMapping(n);
            glm::vec3 texCol = CImage::getTexel(hitObj->texture, uv.x, uv.y);
            res.col *= texCol;
        }
    return true;
}


/// \fn reflectedRay(CRay ray, glm::vec3 n, glm::vec3 pos)
/// \brief Computes parameters of the ray reflected at the surface point with given normal vector.
/// \param ray Input ray.
/// \param n Surface normal vector.
/// \param pos Position of reflection point.
/// \return Reflected ray.
///
CRay CRayTrace::reflectedRay(const CRay& ray, const glm::vec3& n, const glm::vec3& pos) {
    CRay reflected_ray;
    glm::vec3 v = ray.dir;
    glm::vec3 r = v - 2 * glm::dot(v, n) * n;
    reflected_ray.pos = pos;
    reflected_ray.dir = glm::normalize(r);
    return reflected_ray;
}

