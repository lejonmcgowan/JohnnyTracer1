#include <util/SceneContext.h>
#include <iostream>
#include <cameras/Scene.h>
#include <fileparsing/POVParser.h>

int main(int argc, char **argv)
{
    //parse resolution and filepath output
    if(argc < 3)
    {
        std::cout << "Params: [picture width] [picture height] [input file name] " << std::endl;
    }
    else
    {
        SceneContext::windowDims[0] = atoi(argv[1]);
        SceneContext::windowDims[1] = atoi(argv[2]);
        SceneContext::aspect = SceneContext::width() / (float) SceneContext::height();

        auto arg3 = argv[3];
        Scene scene = POVParser::parseFile(std::string(arg3));
        scene.render(scene.getCamera(0));
        scene.renderImage("/home/lejonmcgowan/ClionProjects/RayTracer473/sample.tga");
    }
    return 0;
}