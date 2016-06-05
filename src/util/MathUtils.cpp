//
// Created by lejonmcgowan on 4/21/16.
//

#include "MathUtils.h"

std::ostream& operator<<(std::ostream& ostream, const Eigen::Vector3f vec3)
{
    return ostream << "(" << vec3[0] << "," << vec3[1] << "," << vec3[2] << ")";
}
