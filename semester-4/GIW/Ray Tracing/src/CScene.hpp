//
//  CScene.hpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#ifndef CScene_hpp
#define CScene_hpp


/// \class CCamera
/// \brief Class with camera parameters.
///
class CCamera {
public:
    int width = 0; ///< Horizontal resolution in pixels.
    int height = 0; ///< Vertical resolution in pixels.
    float fov = 0; ///< Field-of-view (<0,180) range)
    glm::vec3 eyep = {0,0,0}; ///< Camera position.
    glm::vec3 lookp = {0,0,0}; ///< Camera target point.
    glm::vec3 up = {0,0,0}; ///< Camera orientation.

};


/// \class CLight
/// \brief Class with light source parameters.
///
class CLight  {
public:
    glm::vec3 pos; ///< Light position.
    glm::vec3 color; ///< Light color.
    
    CLight() {
        color = {1,1,1};
    }
    
    explicit CLight(const glm::vec3& pos) {
        this->pos = pos;
    }
};


/// \class CScene
/// \brief Container for the scene components.
///
class CScene {
public:
    CCamera cam; ///< Camera object.
    std::vector<CObject*> objectList; ///< List of geometric objects.
    std::vector<CLight> lightList; ///< List of the light sources.
    
public:
    void create();

};



#endif /* CScene_hpp */
