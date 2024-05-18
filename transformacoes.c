#include <stdio.h>
#include <stdbool.h>
#include <GL/glew.h>    // GLEW: The OpenGL Extension Wrangler Library.
#include <SDL2/SDL.h>   // Simple DirectMedia Layer.
#include "cglm/cglm.h"  // OpenGL Mathematics (glm) for C.

// Código do vertex shader.
const char *VERTEX_SHADER_CODE =
    "#version 330 core\n"
    "layout(location = 0) in vec3 a_Pos;\n"
    "layout(location = 1) in vec3 a_Color;\n"
    "out vec3 v_FragColor;\n"
    "uniform mat4 u_MVPMatrix;\n"
    "void main() {\n"
    "   gl_Position = u_MVPMatrix * vec4(a_Pos, 1.0);\n"
    "   v_FragColor = a_Color;\n"
    "}\0";

// Código do fragment shader.
const char *FRAG_SHADER_CODE =
    "#version 330 core\n"
    "in vec3 v_FragColor;\n"
    "out vec4 f_Color;\n"
    "void main() {\n"
    "   f_Color = vec4(v_FragColor, 1.0);\n"
    "}\0";

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erro ao iniciar o SDL: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Hello, OpenGL",
                            0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!window)
    {
        fprintf(stderr, "Erro ao criar a janela: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context)
    {
        fprintf(stderr, "Erro ao criar o contexto OpenGL: %s\n", SDL_GetError());
        return -1;
    }

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        fprintf(stderr, "Erro ao iniciar o GLEW: %s\n", glewGetErrorString(err));
        return -1;
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VERTEX_SHADER_CODE, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FRAG_SHADER_CODE, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint u_MVPMatrix = glGetUniformLocation(shaderProgram, "u_MVPMatrix");
    if (u_MVPMatrix == -1)
    {
        fprintf(stderr, "Erro ao obter a localização da variável uniform 'u_MVPMatrix' do vertex shader.\n");
        return -1;
    }

    GLfloat vertices[] = {
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,
        3, 2, 6,
        6, 5, 3,
        5, 6, 7,
        7, 4, 5,
        4, 7, 1,
        1, 0, 4,
        4, 0, 3,
        3, 5, 4,
        1, 7, 6,
        6, 2, 1,
    };

    GLfloat colors[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
    };

    GLuint VAO, VBO, EBO, CBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &CBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    mat4 modelMatrix, viewMatrix, projectionMatrix, MVPMatrix;
    glm_mat4_identity(modelMatrix);
    glm_translate(viewMatrix, (vec3){0.0f, 0.0f, -2.0f});
    glm_perspective(glm_rad(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f, projectionMatrix);

    glEnable(GL_DEPTH_TEST);

    float angle = 0.0f;

    SDL_Event event;
    bool isRunning = true;
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        angle += 0.01f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }

        glm_mat4_identity(modelMatrix);
        glm_rotate(modelMatrix, angle, (vec3){1.0f, 1.0f, 0.0f});

        glm_mat4_mul(projectionMatrix, viewMatrix, MVPMatrix);
        glm_mat4_mul(MVPMatrix, modelMatrix, MVPMatrix);

        glUniformMatrix4fv(u_MVPMatrix, 1, GL_FALSE, (const GLfloat *)MVPMatrix);

        glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        SDL_GL_SwapWindow(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &CBO);

    glDeleteProgram(shaderProgram);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
