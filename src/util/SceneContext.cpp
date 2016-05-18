//
// Created by lejonmcgowan on 4/12/16.
//

#include "SceneContext.h"

Eigen::Vector2i SceneContext::windowDims = Eigen::Vector2i(-1,-1);
Color SceneContext::backgroundColor = Color();
float SceneContext::aspect = 0;

int SceneContext::numSamples = 1;

int SceneContext::numBounces = 5;