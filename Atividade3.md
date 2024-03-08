# Atividade 3
Escolha um formato de arquivo de imagem e descreva como o conteúdo do arquivo é organizado. Na descrição, detalhe as principais seções do formato de arquivo de imagem escolhido.

## Nome
Larissa Rafaela Rodrigues Nepomuceno - RA: 10391039

[Home](README.md)

## Formato escolhido: JPEG
JPEG (Joint Photographic Experts Group), é um formato comum para armazenar imagens comprimidas utilizando diversas variações de métodos de compressão lossy.
Em um arquivo de imagem JPEG, a informação é organizada em uma sequência de segmentos, cada seguimento com um marcador. Esse marcador é indicado por um byte inicial (0xFF) seguido de uma bandeira que identifica o tipo de marcador. Cada tipo de marcador possui um conteúdo específico após ele. Alguns marcadores podem conter dados de configuração, enquanto outros podem conter os dados de pixel da imagem. 

Alguns dos tipos comuns de marcadores JPEG incluem marcadores para início de imagem, tabelas de quantização, informações de frame, dados de pixels e marcador de fim de imagem. Esses marcadores são cruciais para interpretar e decodificar corretamente a imagem JPEG.

### Principais seções do formato
- Header
   - SOI: Start of image
   - APP: Application specific
   - DQT: Define Quantization Table(s)
   - SOF: Start of frame
   - DHT: Define Huffman Table(s)
   - COM: Comment
   - RST: Restart
- Frame data: Contém os dados da imagem organizados em unidades chamadas de macroblocos ou blocos de pixels.
- Tabelas de Huffman: Conjuntos de códigos de Huffman usados para comprimir os dados da imagem.
- Color component data: contém os dados dos componentes de cor da imagem, como Y (luminância), Cb (crominância azul) e Cr (crominância vermelha) no espaço de cores YCbCr. Os dados são comprimidos usando as tabelas de Huffman e quantização especificadas nn header.
- End of file: É representado por dois bytes (0xFFD9 em hexadecimal) e indica o final do arquivo.


## Referências:

https://docs.fileformat.com/image/jpeg/

https://www.adobe.com/br/creativecloud/file-types/image/raster/jpeg-file.html#:~:text=Um%20arquivo%20JPEG%20%C3%A9%20compat%C3%ADvel,da%20qualidade%20da%20imagem%20original.

https://vintageapple.org/macbooks/pdf/Graphics_File_Formats_Second_Edition_1996.pdf

HURT; RAUNHEITTI, L. T. M.; Padrão JPEG de compactação de imagens. Revista Mackenzie de Engenharia e Computação. Ano 1 - Número 1. São Paulo, 2000.

https://recoverit.wondershare.com.br/photo-repair/fix-jpeg-header.html
