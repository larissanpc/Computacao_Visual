# Enunciado

Analise o exemplo de código C que usa SDL, OpenGL e GLSL para renderizar um triângulo, disponível em: https://github.com/profkishimoto/HelloGL.

O que deve ser alterado no código original para que o programa exiba um cubo de cores que fica girando em um ou mais eixos sem parar?

No "cubo de cores", a posição (x, y, z) de um vértice é mapeada para uma cor (r, g, b). Assim, um vértice na posição xyz(0, 0, 0) tem a cor preta rgb(0, 0, 0), um vértice na posição xyz(1, 0, 0) tem a cor vermelha rgb(1, 0, 0), e assim por diante.

Como referência do que o programa alterado deve fazer, veja o vídeo disponível no repositório acima.

Descreva as alterações que devem ser realizadas e publique o resultado dessa atividade no blog.

Lembre-se de incluir todas as referências consultadas (livros, links de artigos, vídeos, etc.) e identificar todas as pessoas do grupo.

## Nome e RA
Larissa Rafaela Rodrigues Nepomuceno - RA: 10391039

[Home](README.md)

## Referências
- https://web.engr.oregonstate.edu/~mjb/cs550/PDFs/VertexBuffers.2pp.pdf
- https://docs.gl/gl3/glDrawArrays
- https://www.youtube.com/watch?v=o8Nb3HR4n9c
- https://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/
- https://shankarrajagopal.github.io/DOWNLOAD/CG_LAB_P3.pdf
- https://gamedev.stackexchange.com/questions/147522/what-is-glviewport-for-and-why-it-is-not-necessary-sometimes
- https://www.quora.com/How-do-you-make-a-sphere-rotate-in-3D-using-the-OpenGL-graphics-library
- https://learnopengl.com/book/book_pdf.pdf


# Alterações necessárias no código
- Redefinir os vértices e cores que irão compor o cubo
  
``` C
GLfloat vertices[] = {
    // Frente
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    // Trás
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
};

GLuint indices[] = {
    // Frente
    0, 1, 2,
    2, 3, 0,
    // Cima
    3, 2, 6,
    6, 5, 3,
    // Trás
    5, 6, 7,
    7, 4, 5,
    // Embaixo
    4, 7, 1,
    1, 0, 4,
    // Esquerda
    4, 0, 3,
    3, 5, 4,
    // Direita
    1, 7, 6,
    6, 2, 1,
};

GLfloat colors[] = {
    // Frente
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    // Trás
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
};
```

- EBO (Element Buffer Object) para armazenar os índices dos vértices
  
``` C
GLuint EBO;
glGenBuffers(1, &EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```

- Adequação da lógica de renderização
``` C
// glDrawArrays para glDrawElements
glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
```

- Adicionar a animação de rotação em um eixo
``` C
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

    // Atualiza ângulo de rotação
    angle += 0.01f;
    if (angle > 360.0f) {
        angle -= 360.0f;
    }

    // Adiciona na matriz de modelo
    glm_mat4_identity(modelMatrix);
    glm_rotate(modelMatrix, angle, (vec3){1.0f, 1.0f, 0.0f}); // Rotação em torno dos eixos x e y

    // Matriz MVP
    glm_mat4_mul(projectionMatrix, viewMatrix, MVPMatrix);
    glm_mat4_mul(MVPMatrix, modelMatrix, MVPMatrix);

    // MVP para vertex shader
    glUniformMatrix4fv(u_MVPMatrix, 1, GL_FALSE, (const GLfloat *)MVPMatrix);

    // Limpa buffer com cor preta
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Renderização
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    SDL_GL_SwapWindow(window);
}
```

- Aplicar teste de profundidade
``` C
glEnable(GL_DEPTH_TEST);
```
- Configuração da viewport
``` C
glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
```


## Código
Código completo [aqui](transformacoes.c)
