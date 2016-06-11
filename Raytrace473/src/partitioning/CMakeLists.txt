add_library(partitioning Octree.cpp Octree.h BVHTree.cpp BVHTree.h)
target_link_libraries(partitioning util geometry)