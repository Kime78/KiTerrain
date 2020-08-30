#include "mesh.hpp"

#include "FastNoise.h"
#include "glad.h"
#include "shader.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
float perlinize(float x, float z, FastNoise& perlin) {
    float r;
    r = perlin.GetNoise(x, z);
    return r * 5;
}
glm::vec3 random_color() {
    int x1, x2, x3;
    float x, y, z;
    x1 = rand() % 100;
    x2 = rand() % 100;
    x3 = rand() % 100;

    x = x1 / 100.0f;
    y = x2 / 100.0f;
    z = x3 / 100.0f;
    return glm::vec3(x, y, z);
}
void Mesh::push_coords(float x, float z, int idx) {
    float y;
    y = perlinize(x, z, perlin);

    mesh.push_back(glm::vec3(x, y, z));
    glm::vec3 color = {0.2f, y / 5, 0.6f};
    mesh.push_back(color);
}
void Mesh::generate_mesh(std::uint64_t x_size,
                         std::uint64_t z_size,
                         bool optimisation) {
    if (optimisation) {
        for (int x = 1; x <= x_size; x += 2) {
            for (int z = 1; z <= z_size; z += 2) {
                float y         = perlinize(x, z, perlin);
                float param     = 0.5;
                glm::vec3 color = random_color();

                // this will be a func uwu
                mesh.push_back(glm::vec3(x - param, y, z + param));
                //mesh.push_back(color);

                y = perlinize(x, z, perlin);
                mesh.push_back(glm::vec3(x + param, y, z - param));
                //mesh.push_back(color);

                y = perlinize(x, z, perlin);
                mesh.push_back(glm::vec3(x - param, y, z - param));
                //mesh.push_back(color);

                color = random_color();
                // triangle 2

                y = perlinize(x, z, perlin);
                mesh.push_back(glm::vec3(x - param, y, z + param));
                //mesh.push_back(color);

                y = perlinize(x, z, perlin);
                mesh.push_back(glm::vec3(x + param, y, z + param));
                //mesh.push_back(color);

                y = perlinize(x, z, perlin);
                mesh.push_back(glm::vec3(x + param, y, z - param));
                //mesh.push_back(color);

                color = random_color();
                // triangle 3
                y = perlinize(x, z, perlin);
                mesh.push_back(glm::vec3((x + 1) + param, y, (z + 1) + param));
                //mesh.push_back(color);

                y = perlinize(x, z, perlin);
                mesh.push_back(glm::vec3((x + 1) + param, y, (z + 1) - param));
                //mesh.push_back(color);

                y = perlinize(x, z, perlin);
                mesh.push_back(glm::vec3((x + 1) - param, y, (z + 1) - param));
                //mesh.push_back(color);

                color = random_color();
                // triangle 4
                y = perlinize(x, z, perlin);
                mesh.push_back(glm::vec3((x + 1) - param, y, (z + 1) + param));
                //mesh.push_back(color);

                y = perlinize(x, z, perlin);
                mesh.push_back(glm::vec3((x + 1) + param, y, (z + 1) + param));
                //mesh.push_back(color);

                y = perlinize(x, z, perlin);
                mesh.push_back(glm::vec3((x + 1) - param, y, (z + 1) - param));
                //mesh.push_back(color);
            }
        }
    } else {
        for (int x = 1; x <= x_size; ++x) {
            for (int z = 1; z <= z_size; ++z) {
                float param     = 0.5;
                glm::vec3 color = random_color();

                // this will be a func uwu
                // triangle 1

                push_coords(x - param, z + param, 1);
                //mesh.push_back(color);

                push_coords(x + param, z - param, 2);
                //mesh.push_back(color);

                push_coords(x - param, z - param, 3);
                //mesh.push_back(color);

                // triangle 2
                //color = random_color();

                push_coords(x - param, z + param, 4);
                //mesh.push_back(color);

                push_coords(x + param, z + param, 5);
                //mesh.push_back(color);

                push_coords(x + param, z - param, 6);
                //mesh.push_back(color);
            }
        }
    }
}

void Mesh::draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, mesh.size());
}

Mesh::Mesh() {
    perlin.SetFrequency(0.03);
    perlin.SetSeed(rand() % 32000);
    perlin.SetNoiseType(FastNoise::Simplex);

    this->generate_mesh(100, 100, 0);
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glDepthRange(-100, 100);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glEnable(GL_DEPTH_TEST);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(float) * 3, mesh.data(),
                 GL_STATIC_DRAW);
    Shader sh;
}