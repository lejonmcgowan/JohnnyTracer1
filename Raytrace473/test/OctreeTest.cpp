//
// Created by lejonmcgowan on 5/22/16.
//

#include <Eigen/Dense>
#include <include/gtest/gtest.h>
#include <partitioning/Octree.h>
#include <geometry/Box.h>
using namespace std;

std::ostream& operator<<(std::ostream& ostream, const Eigen::Vector3f vec3)
{
    return ostream << "(" << vec3[0] << "," << vec3[1] << "," << vec3[2] << ")";
}

TEST(OctreeTest, splitTest)
{
    Octree octree(0, Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(1, 1, 1));
    octree.split();
    EXPECT_EQ(octree.nodes[0]->minBounds, Eigen::Vector3f(0, 0, 0));
    EXPECT_EQ(octree.nodes[0]->maxBounds, Eigen::Vector3f(0.5f, 0.5f, 0.5f));

    EXPECT_EQ(octree.nodes[1]->minBounds, Eigen::Vector3f(0, 0, 0.5f));
    EXPECT_EQ(octree.nodes[1]->maxBounds, Eigen::Vector3f(0.5f, 0.5f, 1.0f));

    EXPECT_EQ(octree.nodes[2]->minBounds, Eigen::Vector3f(0, 0.5f, 0));
    EXPECT_EQ(octree.nodes[2]->maxBounds, Eigen::Vector3f(0.5f, 1.0f, 0.5f));

    EXPECT_EQ(octree.nodes[3]->minBounds, Eigen::Vector3f(0, 0.5f, 0.5f));
    EXPECT_EQ(octree.nodes[3]->maxBounds, Eigen::Vector3f(0.5f, 1.0f, 1.0f));

    EXPECT_EQ(octree.nodes[4]->minBounds, Eigen::Vector3f(0.5f, 0, 0));
    EXPECT_EQ(octree.nodes[4]->maxBounds, Eigen::Vector3f(1.0f, 0.5f, 0.5f));

    EXPECT_EQ(octree.nodes[5]->minBounds, Eigen::Vector3f(0.5f, 0, 0.5f));
    EXPECT_EQ(octree.nodes[5]->maxBounds, Eigen::Vector3f(1.0f, 0.5f, 1.0f));

    EXPECT_EQ(octree.nodes[6]->minBounds, Eigen::Vector3f(0.5f, 0.5f, 0));
    EXPECT_EQ(octree.nodes[6]->maxBounds, Eigen::Vector3f(1.0f, 1.0f, 0.5f));

    EXPECT_EQ(octree.nodes[7]->minBounds, Eigen::Vector3f(0.5f, 0.5f, 0.5f));
    EXPECT_EQ(octree.nodes[7]->maxBounds, Eigen::Vector3f(1.0f, 1.0f, 1.0f));
}

TEST(OctreeTest, selfSplitTest)
{
    Octree::MAX_SHAPES = 4;
    Octree::MAX_LEVEL = 5;

    Octree octree(0, Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(1, 1, 1));
    //because I'm lazy and don't want to calulate the bounds again myself
    Octree octree2(0, Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(1, 1, 1));
    octree2.split();
    std::vector<std::shared_ptr<Box>> boxes;
    for (int i = 0; i < 8; i++)
    {
        Eigen::Vector3f origMin = octree2.nodes[i]->minBounds;
        Eigen::Vector3f origMax = octree2.nodes[i]->maxBounds;

        Eigen::Vector3f min = origMin + 0.25f * (origMax - origMin);
        Eigen::Vector3f max = origMax - 0.25f * (origMax - origMin);
        //  cout << min << " " << max << endl;
        auto box = std::make_shared<Box>(min, max);
        boxes.push_back(box);
        octree.addShape(box);
    }

    EXPECT_NE(octree.nodes[0], nullptr);

    EXPECT_EQ(octree.objects.size(), 0);

    for (int i = 0; i < 8; i++)
    {
        EXPECT_TRUE(octree.inTree(boxes[i]));
        EXPECT_EQ(1, octree.nodes[i]->objects.size());
    }
}

TEST(OctreeTest, inTreeTest)
{
    Octree::MAX_SHAPES = 10;
    Octree::MAX_LEVEL = 5;

    Octree octree(0, Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(1, 1, 1));
    octree.split();
    std::vector<std::shared_ptr<Box>> boxes;
    for (int i = 0; i < 8; i++)
    {
        Eigen::Vector3f origMin = octree.nodes[i]->minBounds;
        Eigen::Vector3f origMax = octree.nodes[i]->maxBounds;
        Eigen::Vector3f length = origMax - origMin;

        Eigen::Vector3f min = origMin + 0.25f * (origMax - origMin);
        Eigen::Vector3f max = origMax - 0.25f * (origMax - origMin);
        //  cout << min << " " << max << endl;
        auto box = std::make_shared<Box>(min, max);
        boxes.push_back(box);
        octree.addShape(box);
    }

    EXPECT_EQ(octree.objects.size(), 0);

    for (int i = 0; i < 8; i++)
    {
        EXPECT_TRUE(octree.inTree(boxes[i]));
        EXPECT_EQ(1, octree.nodes[i]->objects.size());
    }

    //add a box which misses the tree entirely
    auto box = std::make_shared<Box>(Eigen::Vector3f(1, 1, 1), Eigen::Vector3f(1.5f, 1.5f, 1.5f));
    octree.addShape(box);

    EXPECT_EQ(octree.objects.size(), 0);

    EXPECT_FALSE(octree.inTree(box));

    //add a box which patrially is in root tree
    box = std::make_shared<Box>(Eigen::Vector3f(0.75, 0.75, 0.75), Eigen::Vector3f(1.5f, 1.5f, 1.5f));
    octree.addShape(box);

    EXPECT_EQ(octree.objects.size(), 1);

    EXPECT_TRUE(octree.inTree(box));

    for (int i = 0; i < 8; i++)
        EXPECT_EQ(1, octree.nodes[i]->objects.size());

}

TEST(OctreeTest, indexTest)
{
    Octree::MAX_SHAPES = 10;
    Octree::MAX_LEVEL = 5;

    Octree octree(0, Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(1, 1, 1));
    octree.split();
    std::vector<std::shared_ptr<Box>> boxes;
    for (int i = 0; i < 8; i++)
    {
        Eigen::Vector3f origMin = octree.nodes[i]->minBounds;
        Eigen::Vector3f origMax = octree.nodes[i]->maxBounds;

        Eigen::Vector3f min;
        Eigen::Vector3f max;
        //cout << origMin << " " << origMax << " -> ";
        min = origMin + 0.25f * (origMax - origMin);
        max = origMax - 0.25f * (origMax - origMin);
        //  cout << min << " " << max << endl;
        auto box = std::make_shared<Box>(min, max);
        boxes.push_back(box);
        octree.addShape(box);
    }

    EXPECT_EQ(octree.objects.size(), 0);

    for (int i = 0; i < 8; i++)
    {
        EXPECT_EQ(i, octree.getIndices(boxes[i]));
    }
}

TEST(OctreeTest, simpleRay)
{
    Octree octree(0, Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(1, 1, 1));
    octree.split();
    octree.nodes[0]->split();
    Ray ray(Eigen::Vector3f(0.25, 0.25, 0.25), Eigen::Vector3f(0, 1, 0));
    octree.getShapes(ray);
}

std::ostream& ::MathHelper::operator<<(std::ostream& ostream, const Eigen::Vector3f vec3)
{
    return ostream << "(" << vec3[0] << "," << vec3[1] << "," << vec3[2] << ")";
}