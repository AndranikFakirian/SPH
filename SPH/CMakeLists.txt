cmake_minimum_required(VERSION 2.8)

project(SPH)

set(MAIN Kelvin-Helmholtz\ Instability.cpp)

set(CLASS_LIB SPH\ library/Classes&Structures/particle.cpp SPH\ library/Classes&Structures/ppair.cpp SPH\ library/Classes&Structures/Additional\ functions/getParticles.cpp)
set(CONSTRUCT_LIB SPH\ library/Constructor/Liquid_Constructor.cpp SPH\ library/Constructor/Particles_Constructor.cpp SPH\ library/Constructor/Additional\ functions/randomizer.cpp SPH\ library/allincluded.cpp)
set(VISUAL_LIB SPH\ library/Visualizer/Environment_Parameters.cpp SPH\ library/Visualizer/Visualizer.cpp)
set(SOLVER_LIB SPH\ library/Solver/kerfunc.cpp SPH\ library/Solver/Liquid.cpp SPH\ library/Solver/Solver.cpp SPH\ library/Solver/SPHfunc.cpp SPH\ library/Solver/Starting.cpp SPH\ library/Solver/Additional\ functions/distancefunc.cpp SPH\ library/Solver/Additional\ functions/scalar.cpp SPH\ library/Solver/Additional\ functions/reflector.cpp)

add_library(visual SHARED ${VISUAL_LIB})
add_library(construct SHARED ${CONSTRUCT_LIB})
add_library(solver SHARED ${SOLVER_LIB})
add_library(class SHARED ${CLASS_LIB})

add_executable(main ${MAIN})

target_link_libraries(main visual construct solver class)


