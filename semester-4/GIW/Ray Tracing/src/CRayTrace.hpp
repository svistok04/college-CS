//
//  CRayTrace.hpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#ifndef CRayTrace_hpp
#define CRayTrace_hpp

/// \class COutput
/// \brief Class with output structure.
///
class COutput {
public:
    float energy; ///< Ray energy.
    int tree; ///< Ray tree counter.
    glm::vec3 col; ///< Color associated with the ray

};




/// \class CRayTrace
/// \brief Main ray tracer class.
///
class CRayTrace {

public:
    static bool compPrimaryRayMatrix(const CCamera& cam, glm::mat3& mat);
    bool rayTrace(const CScene& scene, CRay &ray, COutput& res);
    static CRay reflectedRay(const CRay& ray, const glm::vec3& n, const glm::vec3& pos);
    
};



#endif /* CRayTrace_hpp */
