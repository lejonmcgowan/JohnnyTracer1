add_library(cameras Camera.cpp Camera.h PinholeCamera.cpp PinholeCamera.h Scene.cpp Scene.h)
target_link_libraries(cameras geometry)