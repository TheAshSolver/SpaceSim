#include<cstdint>
#include<vector>
#include<algorithm>
#include "utilities/Vector.h"
#include<ranges>
#pragma once
namespace SpaceSim{
    using Length = std::uint64_t;
    using Mass = double;
    using Energy = double;
    using Angle = double;
    using Coordinate = double;
    struct CelestialBody{
        Length radius;
        Vector<Coordinate> position;
        Mass mass;
        Vector<Coordinate> velocity;
     CelestialBody(Mass m, Length r, const Vector<Coordinate>& p, const Vector<Coordinate>& v)
        : radius(r), 
          position(p), 
          mass(m),     
          velocity(v)  
    {}
    };
    class Planet : CelestialBody{
            public:
                Coordinate rotation_speed;
                Angle orbital_tilt;
                Vector<Coordinate> velocity;
                void revolve(double dt);
                Planet(Mass _mass, Length _radius, Vector<Coordinate> _positions, Vector<Coordinate> _velocity,  Angle _angle=0);

        };
    std::vector<Coordinate> center_of_mass(std::vector<CelestialBody>& bodies);
}