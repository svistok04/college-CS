//
//  rt.h
//  rt
//
//  Created by Radoslaw Mantiuk on 20/01/2023.
//

#ifndef rt_h
#define rt_h

#include <assert.h>
#include <stdio.h>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include "../3rd/glm/glm.hpp"
#include "../3rd/glm/gtx/intersect.hpp"


extern void print_vec3(const std::string& mstr, const glm::vec3& v);

#define PRINT_MAT3(m) (std::cout << m[0][0] << "\t" << m[1][0] << "\t" << m[2][0] << std::endl << m[0][1] << "\t" << m[1][1] << "\t" << m[2][1] << std::endl << m[0][2] << "\t" << m[1][2] << "\t" << m[2][2] << std::endl);

#define PRINT_VEC3(mstr,v) (std::cout << mstr << "(" << v.x << "," << v.y << "," << v.z << ")" << std::endl);


#include "CImage.hpp"
#include "CRay.hpp"
#include "CObject.hpp"
#include "CScene.hpp"
#include "CRayTrace.hpp"



#endif /* rt_h */
