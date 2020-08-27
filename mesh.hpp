#pragma once

#include <vector>
#include <glm.hpp>

class Mesh
{
    std::vector<glm::vec3> mesh;
    void apply_perlin();//here take a perlin parameter argument
public:
    Mesh();
    ~Mesh() = default;
    void generate_mesh(std::uint64_t size_x, std::uint64_t size_z, bool optimisation);
    void draw();
};

