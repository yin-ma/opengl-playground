#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vertex.h"
#include "shader.h"
#include "camera.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include <vector>


class PointLight
{
public:
    glm::vec3 position;
    glm::vec3 color;
    float vertices[3 * 6 * 6];
    unsigned int indices[3 * 12];
    VAO vao;


    PointLight(glm::vec3 pos, glm::vec3 clr)
        : position(pos), 
            color(clr), 
            vertices 
            {
                // positions         
                -0.3f, -0.3f, -0.3f,
                0.3f, -0.3f, -0.3f,
                0.3f,  0.3f, -0.3f,
                0.3f,  0.3f, -0.3f,
                -0.3f,  0.3f, -0.3f,
                -0.3f, -0.3f, -0.3f,

                -0.3f, -0.3f,  0.3f,
                0.3f, -0.3f,  0.3f,
                0.3f,  0.3f,  0.3f,
                0.3f,  0.3f,  0.3f,
                -0.3f,  0.3f,  0.3f,
                -0.3f, -0.3f,  0.3f,

                -0.3f,  0.3f,  0.3f,
                -0.3f,  0.3f, -0.3f,
                -0.3f, -0.3f, -0.3f,
                -0.3f, -0.3f, -0.3f,
                -0.3f, -0.3f,  0.3f,
                -0.3f,  0.3f,  0.3f,

                0.3f,  0.3f,  0.3f,
                0.3f,  0.3f, -0.3f,
                0.3f, -0.3f, -0.3f,
                0.3f, -0.3f, -0.3f,
                0.3f, -0.3f,  0.3f,
                0.3f,  0.3f,  0.3f,

                -0.3f, -0.3f, -0.3f,
                0.3f, -0.3f, -0.3f,
                0.3f, -0.3f,  0.3f,
                0.3f, -0.3f,  0.3f,
                -0.3f, -0.3f,  0.3f,
                -0.3f, -0.3f, -0.3f,

                -0.3f,  0.3f, -0.3f,
                0.3f,  0.3f, -0.3f,
                0.3f,  0.3f,  0.3f,
                0.3f,  0.3f,  0.3f,
                -0.3f,  0.3f,  0.3f,
                -0.3f,  0.3f, -0.3f,
            },
            indices
            {
                0, 1, 2,
                3, 4, 5,
                6, 7, 8,
                9, 10, 11,
                12, 13, 14,
                15, 16, 17,
                18, 19, 20,
                21, 22, 23,
                24, 25, 26,
                27, 28, 29,
                30, 31, 32,
                33, 34, 35
            }
    {
        vao.bind();

        VBO vbo(vertices, sizeof(vertices));
        EBO ebo(indices, sizeof(indices));

        vbo.bind();
        vbo.setLayoutf(0, 3, 3 * sizeof(float), 0);
        ebo.bind();

        vao.unbind();
        vbo.unbind();
        ebo.unbind();
    }

    void draw(Shader& shader, Camera& camera)
    {
        vao.bind();
        shader.bind();
        glm::mat4 model = glm::translate(position);
        shader.setUniformMatrix4fv("model", glm::value_ptr(model));
        shader.setUniformMatrix4fv("cameraMatrix", glm::value_ptr(camera.getMatrix()));

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        shader.unbind();
    }
};