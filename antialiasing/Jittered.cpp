//
// Created by lejonmcgowan on 5/15/16.
//

#include <util/SceneContext.h>
#include <util/Constants.h>
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

void Jittered::mapToHemisphere()
{
    hemiPoints.reserve(SceneContext::numSamples * Sampler::NUM_SETS);

    for(int i = 0; i < SceneContext::numSamples; i++)
    {
        float cos_phi = std::cos(2.0f * Constants::PI * samplePoints[i][0]);
        float sin_phi = std::sin(2.0f * Constants::PI * samplePoints[i][0]);
        float cos_theta = std::pow(1.0f - samplePoints[i][1], 1.0f / (1.0f + 1.0f)); //e is one for now
        float sin_theta = std::sqrt(1 - cos_theta * cos_theta);
        hemiPoints.push_back(Eigen::Vector3f(sin_theta * cos_phi,sin_theta * sin_phi,cos_theta));
    }
}