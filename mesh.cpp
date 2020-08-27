#include "mesh.hpp"
#include <stdint.h>
#include <stdlib.h> 
#include <time.h> 
#include "shader.hpp"
#include "FastNoise.h"
#include <glad/glad.h>
float perlinize(float x, float z)
{
    float r;
    FastNoise perlin;
    perlin.SetFrequency(0.003);
    perlin.SetSeed(rand() % 10000);
    perlin.SetNoiseType(FastNoise::Perlin); 

    r = perlin.GetNoise(x,z);
    return r;
}
glm::vec3 random_color()
{
    int x1,x2,x3;
    float x,y,z;
    x1 = rand() % 100;
    x2 = rand() % 100;
    x3 = rand() % 100;

    x = x1 / 100.0f;
    y = x2 / 100.0f;
    z = x3 / 100.0f;
    return glm::vec3(x,y,z);
}
void Mesh::generate_mesh(std::uint64_t x, std::uint64_t z, bool optimisation)
{            
    //-1 1   |\
    //1 -1   | \
    //-1 -1  |__\

    //-1 1    ___
    //1 1     \ |
    //1 -1     \|

    //1 1          /|
    //1 -1        / |
    //-1 -1      /__|

    //-1 1      ___
    //1 1       | /
    //-1 -1     |/

    if(optimisation)
    {
        for(int i = 1; i <= x; i += 2)
        {
            for(int j = 1; j <= z; j += 2)
            {
             
                std::uint64_t y = perlinize(x,z); 
                float param = 0.5;
                glm::vec3 color = random_color();

                //this will be a func uwu
                mesh.push_back(glm::vec3(x - param, y, z + param));
                mesh.push_back(color);
                
                mesh.push_back(glm::vec3(x + param, y, z - param));
                mesh.push_back(color);

                mesh.push_back(glm::vec3(x - param, y, z - param));
                mesh.push_back(color);


                //triangle 2
                mesh.push_back(glm::vec3(x - param, y, z + param));
                mesh.push_back(color);

                mesh.push_back(glm::vec3(x + param, y, z + param));
                mesh.push_back(color);

                mesh.push_back(glm::vec3(x + param, y, z  - param));
                mesh.push_back(color);


                //triangle 3
                mesh.push_back(glm::vec3((x + 1) + param, y, (z + 1) + param));
                mesh.push_back(color);

                mesh.push_back(glm::vec3((x + 1) + param, y, (z + 1) - param));
                mesh.push_back(color);

                mesh.push_back(glm::vec3((x + 1) - param, y, (z + 1) - param));
                mesh.push_back(color);


                //triangle 4
                mesh.push_back(glm::vec3((x + 1) - param, y, (z + 1) + param));
                mesh.push_back(color);

                mesh.push_back(glm::vec3((x + 1) + param, y, (z + 1) + param));
                mesh.push_back(color);

                mesh.push_back(glm::vec3((x + 1) - param, y, (z + 1) - param));
                mesh.push_back(color);
            }
        }
    }
    else
    {
        for(int i = 1; i <= x; ++i)
        {
            for(int j = 1; j <= z; ++j);
            {
                std::uint64_t y = perlinize(x,z); //perlined
                float param = 0.5;
                glm::vec3 color = random_color();

                //this will be a func uwu
                //triangle 1
                mesh.push_back(glm::vec3(x - param, y, z + param));
                mesh.push_back(color);
                
                mesh.push_back(glm::vec3(x + param, y, z - param));
                mesh.push_back(color);

                mesh.push_back(glm::vec3(x - param, y, z - param));
                mesh.push_back(color);


                //triangle 2
                mesh.push_back(glm::vec3(x - param, y, z + param));
                mesh.push_back(color);

                mesh.push_back(glm::vec3(x + param, y, z + param));
                mesh.push_back(color);

                mesh.push_back(glm::vec3(x + param, y, z  - param));
                mesh.push_back(color);
            }
        }
    }
    
}

void Mesh::draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, mesh.size());
}

Mesh::Mesh()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glDepthRange(-100,100);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glEnable(GL_DEPTH_TEST);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(float) * 3, mesh.data(), GL_STATIC_DRAW);
    Shader sh;
}