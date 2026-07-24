# SpaceSim

An accurate simulation of a rocket launched from one planet to another — built to learn numerical simulation, computational physics, rocket science, and eventually real-time graphics.

The C++ simulation core is **hand-written** (non-AI). A few supporting files are temporary exceptions; see [Authorship](#authorship).

## Scope

Long-term goal: model a spacecraft transferring between bodies in the solar system with physically meaningful gravity, time stepping, and (later) propulsion and visualization.

Work is staged in phases. Each phase deepens the physics or the tooling before the next layer is added.

| Phase | Focus | Status |
|-------|--------|--------|
| **1** | Solar-system scaffolding: celestial bodies, N-body gravity, stable integration, data I/O | **In progress** |
| Later | Rockets / thrust, transfer trajectories, richer body models | Not started |
| Later | Real-time visualizer (Unity preferred; C++/OpenGL unlikely) | Not started |

### Phase 1 targets

- Interfaces and data for the Sun, the planets, and Earth's Moon (plus extra bodies used for testing)
- Sun-centered coordinates, axes aligned with Earth's orbital plane
- Newtonian mutual gravity and a long-running orbit integration
- Export of trajectories for offline inspection

3D OpenGL spheres were an early Phase 1 idea; visualization is deferred to a dedicated Unity (or, less likely, C++ OpenGL) frontend.

## Current status

What exists today is a **headless N-body solar-system simulator** with real ephemeris initial conditions and offline plotting.

### Implemented

- **Celestial body model** — mass, radius, position, velocity, rotation rate, orbital tilt (`src/Space/Bodies.*`)
- **JSON load** of initial state from `data/solar_system.json`
- **Newtonian gravity** between all pairs, computed in parallel (`src/Space/Forces.h`)
- **Leapfrog (kick–drift–kick)** integration in `src/main.cpp` for long, energy-friendly runs
- **CSV trajectory dump** → `data/simulation_output.csv`
- **Physical constants** in km / kg / s (`src/utilities/constants.h`)
- **3D vector math** (`src/utilities/Vector.h`)
- **Makefile** build (C++23) → `.bin/spacesim`

### Temporary tooling (to be replaced)

| File | Role |
|------|------|
| `fetch_bodies.py` | Pulls state vectors from [JPL Horizons](https://ssd.jpl.nasa.gov/api/horizons.api) and writes `data/solar_system.json` |
| `visualise.py` | Plotly 2D orbit plot from the CSV → `data/orbits.html` |

These scripts are stopgaps. The intended visualizer is **Unity**, or possibly a C++ OpenGL app (unlikely). Body fetching may move into the C++ toolchain later.

### Bodies in the current dataset

Horizons epoch **2000-01-01**, barycentric state vectors. Includes the Sun, Mercury–Neptune, Moon, Pluto, selected dwarf planets, and a few comets (bodies with invalid/zero mass are skipped by the fetcher).

### Not done yet

- Rocket / spacecraft dynamics, thrust, guidance
- Atmosphere, drag, or non-gravitational forces
- Real-time 3D rendering
- In-engine (or C++) replacement for Horizons fetch and Plotly viz

## How to run

```bash
# Optional: refresh initial conditions from Horizons
python fetch_bodies.py

# Build and run the simulator
make
./.bin/spacesim

# Optional: offline orbit plot
python visualise.py
```

Simulation parameters (in `main.cpp`): timestep = 1 day; duration = 1000 years of steps. Output: `data/simulation_output.csv`.

## Layout

```
SpaceSim/
├── src/
│   ├── main.cpp              # Integration loop, CSV output
│   ├── Space/
│   │   ├── Bodies.h/.cpp     # CelestialBody, load, center of mass
│   │   └── Forces.h          # Gravity
│   ├── utilities/
│   │   ├── Vector.h
│   │   └── constants.h
│   └── nlohmann/json.hpp     # Vendored JSON parser
├── data/
│   ├── solar_system.json     # Initial conditions
│   ├── simulation_output.csv # Written by the sim
│   └── orbits.html           # Written by visualise.py
├── fetch_bodies.py           # Temporary Horizons fetcher
├── visualise.py              # Temporary Plotly visualizer
└── Makefile
```

## Authorship

The project is meant to be a **non-AI-written codebase**.

**Exceptions (allowed AI assistance):**

- This `README.md`
- `fetch_bodies.py` (temporary)
- `visualise.py` (temporary)

Everything else under `src/` and the build setup should be written and maintained by hand. When the Unity (or other) visualizer and a proper data pipeline land, the two Python scripts above should go away.
