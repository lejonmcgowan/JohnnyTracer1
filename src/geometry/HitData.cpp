//
// Created by lejonmcgowan on 5/19/16.
//

#include "HitData.h"
#include <geometry/Material.h>
HitData::HitData(const Scene *scene)
    : HitData(scene, new Material())
{
}
HitData::HitData(const Scene *scene, Material *initMaterial)
    :
    scene(scene), currentMaterial(initMaterial)
{

}

