#include "Bodies.h"


namespace SpaceSim{
    void Planet::revolve(double dt){
       position += velocity*dt;
    }
   
    Planet::Planet(int _id, Mass _mass, Length _radius,Vector<Coordinate> _positions, Vector<Coordinate> _velocity, Angle _angle): CelestialBody(_id, _mass, _radius, _positions, _velocity), orbital_tilt(_angle){
    }
     std::vector<Coordinate> center_of_mass(std::vector<CelestialBody>& bodies){
        Mass total_mass = std::ranges::fold_left(bodies, 0, [](auto x, auto body){ return x+body.mass; });
        Coordinate com_x = std::ranges::fold_left(bodies, 0, [](auto x, auto body){ return x+body.mass*body.position.x; })/total_mass;
        Coordinate com_y = std::ranges::fold_left(bodies, 0, [](auto x, auto body){ return x+body.mass*body.position.y; })/total_mass;
        Coordinate com_z = std::ranges::fold_left(bodies, 0, [](auto x, auto body){ return x+body.mass*body.position.z; })/total_mass;
        return {com_x, com_y, com_z};
    }
}