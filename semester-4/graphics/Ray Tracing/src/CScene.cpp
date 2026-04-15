//
//  CScene.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"

#include<fstream>

/// \fn create(void)
/// \brief Adds components to the scene.
///
void CScene::create() {
    
    lightList.clear(); // clears vector with the light data
    objectList.clear(); // clears vector of pointers to objects
    
    // add camera, light sources, and objects
    // cw. 3
    cam.up = {0, 1, 0};
    cam.fov = 50.0;
    cam.width = 500;
    cam.height = 400;
    cam.eyep = {0, 0, 10};
    cam.lookp = {0, 0, 0};
    // cam.eyep = {2, 5, 10};
    // cam.lookp = {-2, 1, 0};

    // create two spheres, cw. 7
    // CSphere* sphere1 = new CSphere(glm::vec3{-2.5f, 1.3f, -3.0f}, 1.0f);
    // CSphere* sphere2 = new CSphere(glm::vec3{0.0f, 0.0f, 0.0f}, 1.6f);
    // objectList.push_back(sphere1);
    // objectList.push_back(sphere2);

    // cw. 8
    // CSphere* sphere = new CSphere(glm::vec3{0.0f, 0.0f, 0.0f}, 5);
    // objectList.push_back(sphere);

    // cw. 10
    // CTriangle* triangle1 = new CTriangle(glm::vec3{3.0, 3.0, -5.0},
    //     glm::vec3{-3.0, 3.0, -10.0},
    //     glm::vec3{-3.0, -3.0, -8.0});
    // objectList.push_back(triangle1);

    // cw. 12
//     CLight light1(glm::vec3{-3.0, -2.0, 8.0});
//     light1.color = {0.6, 0.6, 0.6};
//     lightList.push_back(light1);
//     CSphere* sphere = new CSphere(glm::vec3{0.0f, 0.0f, 0.0f}, 1.6);
//     sphere->color = {0.5, 0.0, 0};
    // tabela 1.3
//     sphere->matAmbient = {0.5, 0.0, 0.0};
//     sphere->matDiffuse = {0.0, 0.0, 0.0};
//     sphere->matSpecular = {0.0, 0.0, 0.0};
//     sphere->matShininess = 30.0;
//     sphere->reflectance = 0.0;
//     sphere->isTexture = false;
    // tabela 1.4
    // sphere->matAmbient = {0.0, 0.0, 0.0};
    // sphere->matDiffuse = {0.7, 0.0, 0.0};
    // sphere->matSpecular = {0.0, 0.0, 0.0};
    // sphere->matShininess = 0.0;
    // sphere->reflectance = 0.0;
    // sphere->isTexture = false;
    // tabela 1.5
    // sphere->matAmbient = {0.0, 0.0, 0.0};
    // sphere->matDiffuse = {0.0, 0.0, 0.0};
    // sphere->matSpecular = {0.7, 0.7, 0.7};
    // sphere->matShininess = 30.0;
    // sphere->reflectance = 0.0;
    // sphere->isTexture = false;
    // tabela 1.6-1.7, cw. 13
//     sphere->matAmbient = {0.1, 0.0, 0.0};
//     sphere->matDiffuse = {0.6, 0.0, 0.0};
//     sphere->matSpecular = {0.7, 0.7, 0.7};
//     sphere->matShininess = 30.0;
//     sphere->reflectance = 0.0;
//     sphere->isTexture = true;
//     sphere->texture = CImage::createTexture(400, 400);
//     objectList.push_back(sphere);

    // cw. 14
    // CLight light(glm::vec3{-3.0, -2.0, 8.0});
    // light.color = {0.6, 0.6, 0.6};
    // CSphere* sphere1 = new CSphere(glm::vec3{-1.0, 0.0, 3.0}, 0.4);
    // sphere1->matAmbient = {0.0, 0.1, 0.0};
    // sphere1->matDiffuse = {0.0, 0.6, 0.0};
    // sphere1->matSpecular = {0.7, 0.7, 0.7};
    // sphere1->matShininess = 30.0;
    // sphere1->reflectance = 0.0;
    // CSphere* sphere2 = new CSphere(glm::vec3{0.0, 0.0, 0.0}, 1.6);
    // sphere2->matAmbient = {0.1, 0.0, 0.0};
    // sphere2->matDiffuse = {0.6, 0.0, 0.0};
    // sphere2->matSpecular = {0.7, 0.7, 0.7};
    // sphere2->matShininess = 30.0;
    // sphere2->reflectance = 0.0;
    // CSphere* sphere3 = new CSphere(glm::vec3{-3.0, -2.0, -2.0}, 0.6);
    // sphere3->matAmbient = {0.0, 0.0, 0.1};
    // sphere3->matDiffuse = {0.0, 0.0, 0.6};
    // sphere3->matSpecular = {0.7, 0.7, 0.7};
    // sphere3->matShininess = 30.0;
    // sphere3->reflectance = 0.0;
    // CTriangle* triangle1 = new CTriangle(glm::vec3{5.0, 5.0, -5.0},
    // glm::vec3{-5.0, 5.0, -5.0}, glm::vec3{-5.0, -5.0, -5.0});
    // triangle1->matAmbient = {0.1, 0.1, 0.1};
    // triangle1->matDiffuse = {0.4, 0.4, 0.4};
    // triangle1->matSpecular = {0.0, 0.0, 0.0};
    // triangle1->matShininess = 0.0;
    // triangle1->reflectance = 0.0;
    // CTriangle* triangle2 = new CTriangle(glm::vec3{5.0, 5.0, -5.0},
    // glm::vec3{-5.0, -5.0, -5.0}, glm::vec3{5.0, -5.0, -5.0});
    // triangle2->matAmbient = {0.1, 0.1, 0.1};
    // triangle2->matDiffuse = {0.4, 0.4, 0.4};
    // triangle2->matSpecular = {0.0, 0.0, 0.0};
    // triangle2->matShininess = 0.0;
    // triangle2->reflectance = 0.0;
    // objectList.push_back(triangle1);
    // objectList.push_back(triangle2);
    // objectList.push_back(sphere1);
    // objectList.push_back(sphere2);
    // objectList.push_back(sphere3);
    // lightList.push_back(light);

    // cw. 16
    cam.eyep = {0, -4.0, 10};
    // reflectance1
    CLight light(glm::vec3{-3.0, -2.0, 8.0});
    light.color = {0.6, 0.6, 0.6};
    CSphere* sphere = new CSphere(glm::vec3{0.0, 0.0, 0.0}, 1.6);
    sphere->matAmbient = {0.1, 0.0, 0.0};
    sphere->matDiffuse = {0.6, 0.0, 0.0};
    sphere->matSpecular = {0.7, 0.7, 0.7};
    sphere->matShininess = 30.0;
    sphere->reflectance = 0.0;
    CTriangle* triangle1 = new CTriangle(glm::vec3{5.0, 5.0, -5.0},
    glm::vec3{-5.0, 5.0, -5.0}, glm::vec3{-5.0, -5.0, -5.0});
    triangle1->matAmbient = {0.1, 0.1, 0.1};
    triangle1->matDiffuse = {0.4, 0.4, 0.4};
    triangle1->matSpecular = {0.0, 0.0, 0.0};
    triangle1->matShininess = 0.0;
    triangle1->reflectance = 1.0;
    CTriangle* triangle2 = new CTriangle(glm::vec3{5.0, 5.0, -5.0},
    glm::vec3{-5.0, -5.0, -5.0}, glm::vec3{5.0, -5.0, -5.0});
    triangle2->matAmbient = {0.1, 0.1, 0.1};
    triangle2->matDiffuse = {0.4, 0.4, 0.4};
    triangle2->matSpecular = {0.0, 0.0, 0.0};
    triangle2->matShininess = 0.0;
    triangle2->reflectance = 0.5;
    objectList.push_back(triangle1);
    objectList.push_back(triangle2);
    objectList.push_back(sphere);
    lightList.push_back(light);
    // reflectance2
    // CLight light1(glm::vec3{-3.0, -2.0, 8.0});
    // light1.color = {0.6, 0.6, 0.6};
    // CLight light2(glm::vec3{5.0, -2.0, 8.0});
    // light2.color = {0.3, 0.3, 0.3};
    // CSphere* sphere1 = new CSphere(glm::vec3{-1.0, 0.0, 3.0}, 0.4);
    // sphere1->matAmbient = {0.0, 0.1, 0.0};
    // sphere1->matDiffuse = {0.0, 0.6, 0.0};
    // sphere1->matSpecular = {0.7, 0.7, 0.7};
    // sphere1->matShininess = 30.0;
    // sphere1->reflectance = 0.0;
    // CSphere* sphere2 = new CSphere(glm::vec3{0.0, 0.0, 0.0}, 1.6);
    // sphere2->matAmbient = {0.1, 0.0, 0.0};
    // sphere2->matDiffuse = {0.6, 0.0, 0.0};
    // sphere2->matSpecular = {0.7, 0.7, 0.7};
    // sphere2->matShininess = 30.0;
    // sphere2->reflectance = 0.0;
    // CSphere* sphere3 = new CSphere(glm::vec3{-3.0, -2.0, -2.0}, 0.6);
    // sphere3->matAmbient = {0.0, 0.0, 0.1};
    // sphere3->matDiffuse = {0.0, 0.0, 0.6};
    // sphere3->matSpecular = {0.7, 0.7, 0.7};
    // sphere3->matShininess = 30.0;
    // sphere3->reflectance = 0.0;
    // CTriangle* triangle1 = new CTriangle(glm::vec3{5.0, 5.0, -5.0},
    // glm::vec3{-5.0, 5.0, -5.0}, glm::vec3{-5.0, -5.0, -5.0});
    // triangle1->matAmbient = {0.1, 0.1, 0.1};
    // triangle1->matDiffuse = {0.4, 0.4, 0.4};
    // triangle1->matSpecular = {0.0, 0.0, 0.0};
    // triangle1->matShininess = 0.0;
    // triangle1->reflectance = 1;
    // CTriangle* triangle2 = new CTriangle(glm::vec3{5.0, 5.0, -5.0},
    // glm::vec3{-5.0, -5.0, -5.0}, glm::vec3{5.0, -5.0, -5.0});
    // triangle2->matAmbient = {0.1, 0.1, 0.1};
    // triangle2->matDiffuse = {0.4, 0.4, 0.4};
    // triangle2->matSpecular = {0.0, 0.0, 0.0};
    // triangle2->matShininess = 0.0;
    // triangle2->reflectance = 1;
    // objectList.push_back(triangle1);
    // objectList.push_back(triangle2);
    // objectList.push_back(sphere1);
    // objectList.push_back(sphere2);
    // objectList.push_back(sphere3);
    // lightList.push_back(light1);
    // lightList.push_back(light2);
}

