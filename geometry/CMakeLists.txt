add_library(geometry Shape.h Shape.cpp
                    Sphere.cpp Sphere.h
                    Ray.cpp Ray.h
                    HitData.h
                    Plane.cpp Plane.h
                    Box.cpp Box.h
                    Triangle.cpp Triangle.h
                    Transform.cpp Transform.h
                    Material.cpp Material.h
        Color.cpp Color.h BounceData.h HitData.cpp BoundingBox.cpp BoundingBox.h)
target_link_libraries(geometry cameras partitioning)