// cpe 473 happy valentined day! Transforms are needed
camera { location  <0, 0, 12>
up        <0,  1,  0> 
right     <1.33333, 0,  0> 
look_at   <0, 0, 0>
}

light_source {<-100, 100, 80> color rgb <1.0, 1.0, 1.0>}

sphere { <0, 0, 0>, 2
pigment { color rgb <1.0, 0.321, 0.0>}
finish {ambient 0.2 diffuse 0.4 specular 0.5 roughness 0.05}
scale <1.1, 3, 1.1>
rotate <0, 0, 60>
translate <-3.2, 3 ,-4>
}

sphere { <0, 0, 0>, 2
pigment { color rgb <1.0, 0.321, 0.0>}
finish {ambient 0.2 diffuse 0.4 specular 0.5 roughness 0.05}
scale <1.1, 3, 1.1>
rotate <0, 0, -60>
translate <3.2, 3 ,-4>
}

sphere { <0, 0, 0>, 2
pigment { color rgb <1.0, 0.321, 0.0>}
finish {ambient 0.2 diffuse 0.4 specular 0.5 roughness 0.05}
scale <0.85, 2, 0.85>
rotate <0, 0,120>
translate <-1.2, 0 ,-4>
}

sphere { <0, 0, 0>, 2
pigment { color rgb <1.0, 0.321, 0.0>}
finish {ambient 0.2 diffuse 0.4 specular 0.5 roughness 0.05}
scale <0.85, 2, 0.85>
rotate <0, 0, -120>
translate <1.2, 0 ,-4>
}

sphere { <0, 0, 0>, 2
pigment { color rgb <0.8, 0.8, 0.1>}
finish {ambient 0.2 diffuse 0.4 specular 0.5 roughness 0.05}
scale <0.4, 2.5, 0.4>
translate <0, 1.25 ,-2.8>
}

plane {<0, 1, 0>, -4.0
pigment {color rgb <0.6, 0.2, 1.0>}
finish {ambient 0.3 diffuse 0.8 specular 0.8 roughness 0.001 reflection 0.5}
}

plane {<0, 0, 1>, -15
pigment {color rgb <0.0, 1.0, 1.0>}
finish {ambient 0.3 diffuse 0.8 specular 0.8 roughness 0.001 reflection 0.0}
}
