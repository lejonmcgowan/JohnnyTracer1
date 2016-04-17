// plane test (RIGHT HANDED)

camera {
  location  <0, 5, 16>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<0, 4, 0> color rgb <1.0, 1.0, 1.0>}

//right wall - note distance is along normal thus to move right is negative for this normal
plane {<-1, 0, 0>, -6
      pigment {color rgb <1.0, 0.0, 0.0>}
      finish {ambient 0.4 diffuse 0.8}
}

//bottom
plane {<0, 1, 0>, -6
      pigment {color rgb <0.0 1.0, 0.0>}
      finish {ambient 0.4 diffuse 0.8}
}

//back
plane {<0, 0, 1>, -16
      pigment {color rgb <0.0, 0.0, 1.0>}
      finish {ambient 0.4 diffuse 0.8}
}

//left
plane {<1, 0, 0>, -5
      pigment {color rgb <1.0 1.0, 1.0>}
      finish {ambient 0.4 diffuse 0.8}
}

//left sphere
sphere { <-5, 3, 0>, 4.1
  pigment { color rgb <0.0,1.0,1.0>}
  finish {ambient 0.2 diffuse 0.4}
}