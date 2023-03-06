#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 100

FILE *arquivo;
char nomeArquivo[100] = "disciplinas.txt";
int w[7]={8,10,7,7,59,5,12}; //Usado para configurar espaçamento das colunas

typedef struct
{
	int cursoCod;//4
	char cursoNome[10];//10
	int periodo;//1
	char codDisc[7];//7
	char nomeDisc[59];//59
	int numVagas;//2
	int cargaHor;//2
	//tamanho máximo da linha -> 4+10+1+7+59+2+2=85 
	
} disciplina;

void addSpaces(char *dest, int size){
	int len = strlen(dest);
	int numSpaces = size - len -1;
	memset(dest+len, ' ', numSpaces);
	dest[len+numSpaces]= '\0';
}

void cabecalho(){
 	printf("|%*s|%*s|%*s|%*s|%-*s|%*s|%*s|\n",w[0],"CODCURSO",w[1],"NOMECURSO",w[2],"PERIODO",w[3],"CODDISC",w[4],"NOMEDISC",
	w[5],"VAGAS",w[6],"CARGAHORARIA");
}

disciplina carregaRegistro(){
	disciplina disc;
	char temp; 

	if ((arquivo = fopen (nomeArquivo,"a")) == NULL) {
			
		printf("ERRO! O arquivo n�o foi aberto!\n");
	} else {
		printf("Codigo do Curso: ");
		scanf("%d", &disc.cursoCod);
		scanf("%c",&temp);
		
		printf("Nome do Curso: ");
		scanf("%[^\n]", disc.cursoNome);
		
		printf("Periodo: ");
		scanf("%d", &disc.periodo);
		scanf("%c",&temp);

		printf("Codigo da Disciplina: ");
		scanf("%[^\n]s", disc.codDisc);
		scanf("%c",&temp);

		printf("Nome da Disciplina: ");
		scanf("%[^\n]s", disc.nomeDisc);

		printf("Numero de Vagas: ");
		scanf("%d", &disc.numVagas);
	
		printf("Carga Horaria: ");
		scanf("%d", &disc.cargaHor);

		fclose(arquivo);

		return disc;
	}
}

//Essa função coleta dados para o registro e os insere no arquivo disciplina.txt

void inserirDisciplina(disciplina disc){
	char temp; 
	// A variável temp serve para pegar os enter '\n' para ele não ir para outra variável


	if ((arquivo = fopen (nomeArquivo,"a")) == NULL){
			
		printf("ERRO! O arquivo n�o foi aberto!\n");
	} else {

		fprintf (arquivo, "%d,%s,%d,%s,%s,%d,%d\n", disc.cursoCod, disc.cursoNome, disc.periodo, disc.codDisc, disc.nomeDisc, disc.numVagas, disc.cargaHor);
		
		fclose(arquivo);
		
		printf("Disciplina registrada com sucesso!\n");
			
	}
}
//Essa função vai pegar um id que indica o índice da linha que queremos acessar
//E vai retornar um registro com informações dessa linha

disciplina mostraLinha(int numLinha){
	char linha[MAXLEN];
	int linhaAtual=0;	
	disciplina rec;

	if ((arquivo = fopen (nomeArquivo,"r")) == NULL){
		printf("ERRO! O arquivo n�o foi aberto!\n");
	}
	else
	{	
		while(fgets(linha,MAXLEN,arquivo)){
			sscanf(linha,"%d,%[^,],%d,%[^,],%[^,],%d,%d\n", &rec.cursoCod, rec.cursoNome, &rec.periodo,
			rec.codDisc, rec.nomeDisc, &rec.numVagas, &rec.cargaHor);
			if(linhaAtual == numLinha){
				fclose(arquivo);
				return rec;
			}
			linhaAtual++;
		}
		disciplina naoAchou = {-1};
		fclose(arquivo);
		return naoAchou;
	} //continuar
			
}

//Essa funcao recebe o numero de uma linha começando em 0, e atualiza a linha com os valores
// do registro que foi passado via parâmetro
// na variavel opcao passamos o valor 1 se quisermos atuliazar valor da linha, ou 0 para excluir
void atualizaLinha(int numLinha, disciplina novoReg, int opcao){
	int linhaAtual = 0, achou = 0;
	char linha[MAXLEN];
	disciplina rec;

	if((arquivo = fopen(nomeArquivo, "r")) == NULL){
		printf("ERRO! O arquivo n�o foi aberto!\n");
	} else {

		while((fscanf(arquivo,"%d,%[^,],%d,%[^,],%[^,],%d,%d\n",&rec.cursoCod, rec.cursoNome, &rec.periodo,
			rec.codDisc, rec.nomeDisc, &rec.numVagas, &rec.cargaHor))!= EOF){
			if(linhaAtual == numLinha){
				achou = 1;
				break;
			}
			linhaAtual++;
		}

		fclose(arquivo);
		
		if(!achou){
			printf("Registro não encontrado!\n");
			return;
		}

		arquivo = fopen(nomeArquivo,"r");
		FILE* arqTemp = fopen("disciplinas_tmp.txt","w");

		linhaAtual = 0;

		while(fgets(linha,MAXLEN,arquivo) != NULL){
			if( linhaAtual == numLinha){
				if(opcao == 1){
					fprintf (arqTemp, "%d,%s,%d,%s,%s,%d,%d\n", novoReg.cursoCod, novoReg.cursoNome, novoReg.periodo,
				 	novoReg.codDisc, novoReg.nomeDisc, novoReg.numVagas, novoReg.cargaHor);
				} 
			} else {
				fprintf(arqTemp,"%s",linha);
			}
			linhaAtual++;
		}
		fclose(arquivo);
		fclose(arqTemp);

		remove(nomeArquivo);
		rename("disciplinas_tmp.txt",nomeArquivo);
		if(opcao == 1){
			printf("\nLinha Atualizada com sucesso!\n");
		} else {
			printf("\nLinha Excluida com sucesso!\n");
		}
	}
}

// Mostra todos as linhas do arquivo, de 10 em 10;

void mostraTodasLinhas(){
	char linha[MAXLEN],tmp;
	int contaLinha=0;
	disciplina rec;
	if((arquivo = fopen(nomeArquivo, "r")) == NULL){
		printf("ERRO! O arquivo n�o foi aberto!\n");
	} else {
		cabecalho();
		while((fscanf(arquivo,"%d,%[^,],%d,%[^,],%[^,],%d,%d\n",&rec.cursoCod, rec.cursoNome, &rec.periodo,
			rec.codDisc, rec.nomeDisc, &rec.numVagas, &rec.cargaHor)) != EOF){
				printf("|%*d|%*s|%*d|%*s|%-*s|%*d|%*d|\n",w[0],rec.cursoCod,w[1],rec.cursoNome,w[2], rec.periodo,
				 w[3],rec.codDisc,w[4],rec.nomeDisc,w[5], rec.numVagas,w[6], rec.cargaHor);
				if(contaLinha == 10){
					scanf("%c",&tmp);
					printf("Press Enter to Continue\n");
					while(tmp = getchar() != '\n' );
					system("clear");
					contaLinha = 0;
					cabecalho();
				}
				contaLinha++;
			}
	}
}

int main (int argc, char *argv []) 
{
	char tmp;
	int opcao;
	disciplina reg;
	char linha[100];
	int idLinha=-1, atualiza;
	
	do {
	printf("\nSelecione uma das opcoes a seguir:\n 1 - Inserir\n 2 - Listar Uma \n 3 - Listar Todas em forma de relatorio\n 4 - Atualizar\n 5 - Remover\n 6 - Encerrar\n");
	scanf("%d", &opcao);
	
	switch (opcao)
	{
		case 1:
			reg = carregaRegistro();
			inserirDisciplina(reg);
		break;
		
		case 2:
			do
			{
				printf("\nInsira o numero da linha que deseja acessar [O índice começa em 0]: ");
				scanf("%d", &idLinha);
			} while ( idLinha < 0 );
			reg = mostraLinha(idLinha);
			if(reg.cursoCod !=-1){
				cabecalho();
				printf("|%*d|%*s|%*d|%*s|%-*s|%*d|%*d|\n",w[0],reg.cursoCod,w[1],reg.cursoNome,w[2], reg.periodo,
				w[3],reg.codDisc,w[4],reg.nomeDisc,w[5], reg.numVagas,w[6], reg.cargaHor);			
			} else {
				printf("\nLinha não encontrada. \n");
			};
		break;
		
		case 3:
			mostraTodasLinhas();
		break;
		
		case 4:	
			atualiza = 1;
			printf("\nInsira o numero da linha que seja atualizar o conteudo [O índice começa em 0]:");
			scanf("%d", &idLinha);
			scanf("%c", &tmp);
			printf("\nAgora insira os novos valores do registro: \n");
			reg = carregaRegistro();
			atualizaLinha(idLinha,reg,atualiza);
		break;

		case 5:
			atualiza = 0;
			disciplina regVazio = {-1};
			printf("\nInsira o numero da linha que seja atualizar o conteudo [O índice começa em 0]: ");
			scanf("%d",&idLinha);
			scanf("%c", &tmp);
			atualizaLinha(idLinha, regVazio, atualiza);
		break;

		case 6:	
			exit;
		break;
		
		Default: 
		printf("Valor Invalido\n");
	}
	getchar();
	//trocar essas duas linhas se estiver no windows
	printf("Press Enter to Continue");
	while(tmp = getchar() != '\n' );    
	system("clear");
	
	} while (opcao != 6);
}
