# Matriz esparsa
A matriz esparsa é um tipo abstrato de dados que é útil para representar um conjunto grande de dados que possuem muitos valores nulos. O programa implementa operações básicas de uma matriz esparsa e também resolve sistemas de equações lineares através do método de Gauss-Seidel.

# Compilando o programa
Para compilar o programa é necessário ter o GCC instalado no micro utilizado. Após isso, abra o terminal, vá para o diretório em que os arquivos acima estão salvos e digite o seguinte comando:

$ gcc main.c cell.c matrix.c gaussseidel.c -o main

# Executando o programa
Caso queira executar o programa normalmente, basta digitar no terminal o seguinte comando: 

$ ./main

Esse comando abre um menu que exibe as opções ao usuário. Entretanto, caso queira executar o programa que resolve o sistema linear utilizando Gauss-Seidel:

$ ./main -gaussseidel

# Autor
Ivan Mateus de Lima Azevedo - https://github.com/ivanmateus
