Tomaz Canabrava
Marcelo aconselho tomar um pouco de cuidado com o git, voce dicionou arquivo de swap ai .mandelbrot.bas.swp
e claro, utilizar um sistema de build melhor que makefile feito na mao, como esta usando C, eu aconselho o meson ou cmake.
nao utilize #define TRUE / FALSE, use #include <stdbool.h> pra tratar de booleans.
o seu padrao de endentação de código tá meio unico em projetos C, eu recomendo rodar o clang-format em cima.
alguns metodos tao muito grandes, como o for_next, uma dica, voce ta comentando o que o codigo faz, isso nao eh muito util, deeria comentar o que o codigo deve fazer. for_next tem 100 linhas  com bastante aritimetica de ponteiro, uma programador nao quer perder o tempo tentando descobrir o que ta acontecendo ali, extrair em funcoes menores  ; comentar mais.
'cont()' nao eh um bom nome pra funcao, ele conta, ele continua, ele retorna um valor?
recomendo nao usar palavras reservadas de outras linguagens de programacao, pra evitar possiveis desentendimentos de leitura no codigo (por exemplo, remover o comando 'new()'
fora isso, ta bem bom o projeto - nao parei pra testar mas acabei de ler o codigo inteiro.
eu removeria os *codigos* comentados, eles dificultam a leitura e o entendimento do projeto, comentaria mais, removeria os trechos em portugues.
mas ta ficando bem bacana


Marcelo Pinheiro
Xará, parabéns pelo projeto. Uma sugestão é melhorar o ReadMe e procurar explicar como instalar, como usar, etc. Fique a vontade para se inspirar em um ReadMe que eu criei para um projetinho que eu escrevi: https://github.com/mpinheir/estados
