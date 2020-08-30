#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "FastNoise.h"
class Mesh {
    std::vector<glm::vec3> mesh;
    void apply_perlin();   // here take a perlin parameter argument
    glm::vec3 p[6];
    void push_coords(float x, float z, int idx);
    FastNoise perlin;

public:
    Mesh();
    ~Mesh() = default;
    void generate_mesh(std::uint64_t size_x,
                       std::uint64_t size_z,
                       bool optimisation);
    void draw();
};
