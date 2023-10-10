<h1> Simulação de um incêndio em uma floresta</h1>

<p>Objetivo: implementar um modelo que simula o andamento de um incêndio em uma floresta. Iniciaremos uma malha quadrada (LxL) que representará o espaço da floresta. Preenchemos esse espaço aleatoriamente com árvores com uma proporção pA dada. Iniciaremos uma quantidade de foco de incêndio dada qFogo. Ao encontrar uma árvore, verificamos se existe algum foco de incêndio nos oito vizinhos próximos, caso verdadeiro, esta árvore é incendiada. Após um tempo computacional, o foco de incêndio se torna cinza. A simulação acaba quando não existe mais nenhum foco de incêndio.</p>

<p>O programa registra o estado em cada tempo de simulação, de modo a podermos visualizar o andamento da simulação. Os parâmetros utlizados serão L=100, pA=0.7 e qFogo=1. Para o processo de geração de número pseudo-aleatório usaremos a raiz R=893221891 e a semente s=888121. O problema foi implementado em linguagem C, e compilado com GCC 9.4.0. </p>

<p>Com os resultados da simulação, geramos um Gif com frames da malha simulada utilizando a ferramenta Gnuplot.</p>
