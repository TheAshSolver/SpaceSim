#include<cstdint>

namespace SpaceSim{
    using Length = std::uint64_t;
    using Mass = double;
    using Speed = double;

    struct CelestialBody{
        Length radius{};
        Mass mass{};
    };
    
    class Planet : CelestialBody{
        public:
            Speed rotation_speed{0};
            Speed revolution_speed{0};
            Length star_x{0}, star_y{0}, star_z{0};

            void revolve(){
               
            }

    };

}