#include <util/SceneContext.h>
#include <iostream>
#include <cameras/scenes/Scene.h>
#include <fileparsing/POVParser.h>
#include <antialiasing/Jittered.h>
#include <stdlib.h>
#include <chrono>

int main(int argc, char **argv)
{
    //parse resolution and filepath output
    if (argc < 4)
    {
        std::cout << "Params: [picture width] [picture height] [input file name] [optional: anti-aliasing (0 = off "
            "(default), 1 = on)]" <<
            std::endl;
    }
    else
    {
        SceneContext::windowDims[0] = atoi(argv[1]);
        SceneContext::windowDims[1] = atoi(argv[2]);
        SceneContext::aspect = SceneContext::width() / (float) SceneContext::height();

        auto arg3 = argv[3];
        if (argc > 4 && atoi(argv[4]) == 1)
            SceneContext::numSamples = 9;

        Scene *scene = POVParser::parseFile(std::string(arg3));
        auto sampler = std::make_shared<Jittered>();
        scene->getCamera(0)->setSampler(sampler);
        scene->init();

        auto start = std::chrono::system_clock::now();
        scene->render(*scene->getCamera(0));
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time)
            << "elapsed time: " << elapsed_seconds.count() << "s\n";

        std::string inputFilePath = argv[3];
        inputFilePath = inputFilePath.substr(0,inputFilePath.find_last_of('/') + 1);
        inputFilePath = "/home/lejonmcgowan/ClionProjects/RayTracer473/";
        scene->renderImage(inputFilePath + "sample.tga");

        std::cout <<"image made in " << inputFilePath + "sample.tga" << std::endl;

    }
    return 0;
}