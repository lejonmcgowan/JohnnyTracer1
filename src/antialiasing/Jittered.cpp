//
// Created by lejonmcgowan on 5/15/16.
//

#include <util/SceneContext.h>
#include "Jittered.h"

void Jittered::makeSamples()
{
    int n = std::sqrt(SceneContext::numSamples);
    for (int set = 0; set < Sampler::NUM_SETS; set++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                float num1 = (i + std::rand()) / static_cast<float>(RAND_MAX) / (float) n;
                float num2 = (j + std::rand()) / static_cast<float>(RAND_MAX) / (float) n;
                samplePoints.push_back(Eigen::Vector2f(num1, num2));
            }
        }
    }
}