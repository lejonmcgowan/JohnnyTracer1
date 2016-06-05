add_library(cameras Camera.cpp Camera.h PinholeCamera.cpp PinholeCamera.h scenes/Scene.cpp scenes/Scene.h scenes/OctreeScene.cpp scenes/OctreeScene.h scenes/BVHScene.cpp scenes/BVHScene.h)
target_link_libraries(cameras geometry antialiasing partitioning)
