## Atividade 8 - Enunciado
Faça uma pesquisa sobre APIs gráficas e elabore um texto descrevendo os resultados da pesquisa.

O seu texto deve conter:

- Uma breve descrição da API gráfica que você selecionou para a pesquisa;
- Como a pipeline é documentada pelos desenvolvedores da API;
- Quais linguagens de shading (shaders) são suportadas pela API;
- Um exemplo de código que demonstra o uso da API (pode ser um “Hello, World!” gráfico – renderizar um triângulo na tela);
- Um exemplo de código de shader suportado pela API;
- A descrição de um exemplo de aplicação que usa a API.

## Nome e RA
Larissa Rafaela Rodrigues Nepomuceno - RA: 10391039

## Referências
- https://blog.2amgaming.com/2019/09/o-que-e-api-grafica/
- https://www.khronos.org/blog/reducing-draw-time-hitching-with-vk-ext-graphics-pipeline-library
- https://www.adrenaline.com.br/amd/entenda-o-que-e-a-vulkan-e-porque-ela-pode-mudar-o-mercado-de-games-para-pc/
- https://registry.khronos.org/SPIR-V/
- https://github.com/KhronosGroup/Vulkan-Samples
- https://docs.vulkan.org/spec/latest/chapters/pipelines.html
- https://vulkan-tutorial.com/en/Drawing_a_triangle/Graphics_pipeline_basics/Shader_modules#page_Loading-a-shader
- https://docs.vulkan.org/spec/latest/appendices/spirvenv.html
- https://profkishimoto.github.io/compvis07g-2024-1/conteudo/semana-12/Shaders.pdf

# API gráfica - Vulkan
- Descrição
 
  A Vulkan é uma API focada em instruções de baixo nível mantida pelo Khronos Group, mas  baseado no Mantle da AMD em parceria com a DICE. Ela garante uma grande vantagem em termos de desempenho, trazendo otimizações que ajudam os desenvolvedores a diminuir os gargalos causados pelo processador.
- Pipeline

  A extensão VK_EXT_graphics_pipeline_library oferece uma visão detalhada da biblioteca de pipeline gráfica do Vulkan. Ela quebra o PSO (Pipeline State Object) em quatro estágios individuais em vez de um pipeline monolítico:

  - Interface de Entrada de Vértices: Contém informações normalmente fornecidas ao objeto de estado completo do pipeline por VkPipelineVertexInputStateCreateInfo e VkPipelineInputAssemblyStateCreateInfo. Essas informações são desconhecidas até o momento do desenho, então um pipeline para este estágio é criado rapidamente pelo driver, já que não possui o código de shader envolvido.
  - Pré-Shaders de Pré-Rasterização: Contém os estágios de shader de vértice, tesselação e geometria, juntamente com o estado associado ao pipeline de viewport, rasterização, tesselação e renderização. Combinando as bibliotecas de pipeline com extensões de estado dinâmico, apenas o código SPIR-V e o layout do pipeline são necessários para criar esse estágio, permitindo ao driver fazer a maior parte do trabalho de compilação para instruções de hardware.
  - Shader de Fragmentos: Contém o shader de fragmento junto com o estado de profundidade e renderização. Assim como no estágio de pré-rasterização, a criação do pipeline de shader de fragmento requer apenas o código SPIR-V e o layout do pipeline, facilitando a compilação para instruções de hardware.
  - Interface de Saída de Fragmentos: Contém o estado de mesclagem de cores, amostragem múltipla e renderização. Assim como na Interface de Entrada de Vértices, esse estágio requer informações desconhecidas até o desenho, então o pipeline é criado rapidamente pelo driver em tempo real.
    
  Ao criar esses quatro estágios da biblioteca de pipeline, uma aplicação pode fazer uma ligação final para obter um pipeline completo, o que é esperado ser muito rápido, pois o driver já compilou os shaders individuais e pode fazer a ligação no momento do desenho. Isso evita atrasos indesejados e melhora significativamente o desempenho da renderização.
- Shaders (linguagens)

  Vulkan suporta shaders escritos em SPIR-V (Standard Portable Intermediate Representation - Vulkan), formato binário intermediário independente de linguagem. Isso permite que os desenvolvedores usem linguagens como HLSL, GLSL, ou C/C++ para escrever shaders, que depois são compilados para SPIR-V.
  
- Renderizando um triângulo
- Código shader

'''vertex

https://gist.githubusercontent.com/larissanpc/24358455d46b5bf2a3eac2c99b85b1fe/raw/67630bc158c849a4711a960a2bba47d5b7ade842/shader.vert
  
- Exemplo de aplicação
