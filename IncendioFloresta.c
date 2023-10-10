//Autor: Renato Maciel Félix

#include<stdio.h>

#define pA 0.7 // Proporção de árvores no espaço simulado
#define L 100 // Lado da Malha
#define qFogo 1 // Quantidade de foco de incêndio inicial

//Definindo os estados
#define Vazio 0 // Espaço Vazio
#define Arvore 1 
#define Fogo 2
#define Cinza 3

//Variáveis para o processo de número aleatório
#define max 4294967295.0
unsigned s;	//Semente 
unsigned R;	//Raíz
double rn;

int Floresta[L+2][L+2], Futuro[L+2][L+2];

//Gerador de número aleatório
double aleatorio(unsigned *R)
{	*R=*R*s;
	rn=*R/max;

	return rn;
}

// Registra o momento da Floresta naquele tempo
void Imprime(int tempo)
{	int i, j;
	FILE *pM;
	char arq[30];
	
	//Modo de criar a sequência de arquivos com o tempo
	sprintf(arq,"Malha%d.dat", tempo);
	pM = fopen(arq,"w");
	
	//Salvando em um arquivo a malha da população naquele dia.
	for(i=1;i<=L;i++)
	{	for(j=1;j<=L;j++)
		{	fprintf(pM,"%d\t",Floresta[i][j]);
		}
		fprintf(pM,"\n");
	}
	
	fclose(pM);
}

// Retorna a quatidade de fogo na Floresta
int Fogarel()
{	int i, j, cont = 0;
	
	for(i = 0; i <= L; i++)
	{	for(j = 0; j <= L; j++)
		{	if(Floresta[i][j] == Fogo)
				cont++;
		}
	}
	
	return cont;
}

// Inicia o incêndio com o número de focos dado.
void Coloca_fogo()
{	int i, j, k=0;
	
	while(k!=qFogo)
	{	rn = aleatorio(&R);
		i = rn*L + 1;
		rn = aleatorio(&R);
		j = rn*L + 1;
		
		if(Floresta[i][j]==Arvore)
		{	Floresta[i][j] = Fogo;
			k++;
		}
	}
}

// Função que cria as árvores dado a proporção inicial.
int Inicia_Floresta()
{	int x;
	
	rn = aleatorio(&R);

	if(rn<pA)
		x = Arvore; // Temos uma árvore
	else
		x = Vazio; // Temos um espaço vazio
		
	return x;
}

int main()
{	int t = 0, i, j, l, k, A, C;

	R = 893221891;
	s = 888121;
	
	FILE *fp, *tp;
	fp = fopen("Andamento.dat","w");
	fprintf(fp,"#Tempo\tÁrvores\tFogo\tCinza\n");

	tp = fopen("TempoFinal.dat", "w");

	A = 0;
	C = 0;
		
	//Condições de contorno	
	for(i=1;i<=L;i++)
	{	//Fechando as laterais da malha
		Floresta[0][i] = Floresta[0][L];
		Floresta[L+1][i] = Floresta[1][i];
			
		//Fechando a parte de cima com a de baixo
		Floresta[i][0] = Floresta[i][L];
		Floresta[i][L+1] = Floresta[i][1];		
	}
		//Ligando as pontas na malha
		Floresta[0][0] = Floresta[L][L];
		Floresta[0][L+1] = Floresta[L][1];
		Floresta[L+1][L+1] = Floresta[1][1];
		Floresta[L+1][0] = Floresta[1][L];

	for(i = 0; i <= L; i++)//CRIANDO A MALHA
	{	for(j = 0; j <= L; j++)
		{	Floresta[i][j] = Inicia_Floresta();
			
			if(Floresta[i][j]==Arvore)
				A++;
		}
	}
	
	printf("\nTempo %d\nNºÁrvores: %d\tNºFogo: %d\tNºCinzas: %d\n", t, A, Fogarel(Floresta), C);
	Imprime(t); // Função para a criação do gif animado
	fprintf(fp,"%d\t%d\t%d\t%d\n",t,A,Fogarel(Floresta),C);
	
	for(i = 0; i <= L; i++)// Inicializando a matriz Futuro
	{	for(j = 0; j <= L; j++)
			Futuro[i][j] = Floresta[i][j];
	}
	t++;
	
	Coloca_fogo(); // Colocando fogo em uma árvore aleatória
	
	printf("\nTempo %d\nNºÁrvores: %d\tNºFogo: %d\tNºCinzas: %d\n", t, A, Fogarel(Floresta), C);
	Imprime(t); // Função para a criação do gif animado
	fprintf(fp,"%d\t%d\t%d\t%d\n", t, A, Fogarel(Floresta), C);
	
	do
	{	t++;
	
		for(i = 0; i <= L; i++)
		{	for(j = 0; j <= L; j++)
			{	switch(Floresta[i][j]) //VERIFICANDO
				{	case Vazio: //Espaço vazio
						Futuro[i][j] = Floresta[i][j];
					break;
					
					case Arvore	:	for(l=-1;l<=1;l++) // Verifica se os vizinhos da árvore são Fogo 
									{	for(k=-1;k<=1;k++)
										{	if(Floresta[i+l][j+k]==Fogo)
											{	Futuro[i][j] = Fogo;
												break;
											}	
										}
									}
					break;
								
					case Fogo	:	Futuro[i][j] = Cinza;
									C++;
									if(A>0)
										A--;
					break;
								
					case Cinza	:	Futuro[i][j] = Floresta[i][j];
					break;
				}
			}
		}

		for(i=0;i<=L;i++) // Atualizando as mudanças na matriz principal
		{	for(j=0;j<=L;j++)
				Floresta[i][j] = Futuro[i][j];
		}
		
		printf("\nTempo %d\nNºÁrvores: %d\tNºFogo: %d\tNºCinzas: %d\n", t, A,Fogarel(Floresta),C);
		Imprime(t); // Função para a criação do gif animado
		fprintf(fp,"%d\t%d\t%d\t%d\n",t,A,Fogarel(Floresta),C);
		
	}while(Fogarel(Floresta)!=0);
	
	Imprime(t); // Função para a criação do gif animado

	fprintf(tp, "%f", (float)t); // Registra a informação do tempo que levou o incêndio.

	fclose(fp);
	
	if(A!=0)
		printf("\nRestaram %d árvores!\n",A);
	else
		printf("\nNão restaram árvores!!\n");		
}