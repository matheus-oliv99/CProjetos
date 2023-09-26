//Inclui as bibliotecas de recursos
//APS DE LOGICA DE PROGRAMAÇÃO 
//MATHEUS OLIVEIRA, EDINA CARVALHO, GUSTAVO ESTLIN, MATHEUS JACOBSEN
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <iostream>
#include <time.h>
typedef struct Palavra{ //The typedef command is used to create "synonyms" for existing data types.

    char palavra[100];
    struct Palavra *prox;//ponteiro serve para apontar pra um elemento do mesmo tipo.
}
//Esses dois elementos com ponteiro seriam para percorrer essa lista na hora de sortear uma palavra por exemplo.
Palavra;
Palavra *primeiraPalavra;
Palavra *ultimaPalavra;
int tam; //usaremos essa variável para sortear palavra
//criação de funções e procedimentos
void VerificaChances(int cont);//Verifica quantas chances o jogador ainda tem
void MensagemVitoria(char tentativa);//Mostra a msg de vitoria se a tentativa for validada
void DesenhaForca(int cont,int flagInicio);//Mostra o boneco no programa conforme jogador for errando as letras
void MostrarLetrasErradas(int erro1,int erro2,int erro3,int erro4,int erro5,char tentativa,int contador); //Mostra as letras que o jogardor errou
void VerificaTentativa(char qtdCaracter,char tentativa,int *certo,int *contador,char resposta[]);//Verificia se a tentativa do jogador foi valdida
void CapturaLetra(char *tentativa);//Captura a letra digitada
void VerificaSeErrou(char frase[],int qtdCaracter,int *contador,char tentativa,int *erro1,int *erro2,int *erro3,int *erro4,int *erro5,int *n); // Verifica se a letra digitada está incorreta
int MenuPrincipal();
char* BuscarPalavra(char nomeArquivo[]);//Seek the word on gamewords.txt
void CriarListaVazia();
void InseriNaLista(Palavra palavra);
int SorteiaPalavra(int faixa);
void limparLista();
using namespace std;
int main ()
{
    setlocale(LC_ALL, "Portuguese"); //Na hora que aparece o comando para jogar e para sair , aparece um hífen por exemplo: 1-jogar, porém quando  
	//porem quando tiramos isso, no compilador irá aparecer uma letra u com acento circunflexo no lugar do hífen.
	
    int i, cont, n, quantCaracter, erro1, erro2, erro3, erro4, erro5, certo,opcao; //Declaração de variaveis
    char frase[100], resposta[100], tentativ, confirmar, continuar; // declaração de variaveis tipo Char + vetores
    do
    {
        MENU:
        system("cls");//Limpa a tela
        DesenhaForca(cont,1);

        opcao=MenuPrincipal(); //abre as opcoes do menu principal
        if(opcao==0) //se o jogador digitar 0 no menu o programa termina
        {
        exit(0);
        }
        else if(opcao==1) // se o jogador digitar 1, o jogo inicia
        {
            strcpy(frase,BuscarPalavra("gamewords.txt"));//busca o arquivo de palavras
        }else{
            cout<<"\nOpção Invalida tente Novamente";  //msg exibida caso a opção selecionada seja invalida
        }
        confirmar = 'n'; //o confirmar recebe não!!!
        
        while(confirmar != 'S')	//confirmar diferente do SIM.
        {
            certo = 0;//reinicia a contagem de acertos "Limpa a variavel"
            quantCaracter=0;//quantidade de caractéres na palavra
            n = 0;
            i=0;
            cont = 0;
            erro1 = ' ';
            erro2 = ' ';
            erro3 = ' ';
            erro4 = ' ';
            erro5 = ' ';
            tentativ=' ';
            cout<<"O jogo sera iniciado..\n";
            system("PAUSE");
            system("CLS");
            for(i = 0; i < 100; i++){//fill in traces the secret vector
            
                resposta[i]='_';//
			}
            while(cont < 6)//verifique se a letra está dentro da palavra que você digitou, verifique se a letra que você digitou está correta ou errada
            {
                n=0;
                certo=0;
                DesenhaForca(cont,0);

                for(i=0; i < 100; i++)
                {
                    if(frase[i]=='\0')
                    {
                        quantCaracter = i;//Quandtidade de caracteres vai ser igual ao valor de i
                        break;
                    }
                    else{
                        if(frase[i]==' ')
                        {
                            resposta[i]=' ';
                            cout<<resposta[i];
                        }else{
                            if(frase[i]==tentativ)
                            {
                                resposta[i]=frase[i];
                            }
                        }
                    }
                    cout<<resposta[i];
                }

                MostrarLetrasErradas(erro1,erro2,erro3,erro4,erro5,tentativ,cont);//Mostra quais letras das digitadas estão incorretas
                VerificaChances(cont);//Verifica a quantidade de chances
                VerificaTentativa(quantCaracter,tentativ,&certo,&cont,resposta);//Verifica se a tentativa foi valida
                if(certo!=quantCaracter)//Se for valida, executa este evento
                {
                    CapturaLetra(&tentativ);//Captura a letra da palavra sorteada.

                }
                VerificaSeErrou(frase,quantCaracter,&cont,tentativ,&erro1,&erro2,&erro3,&erro4,&erro5,&n);//Verifica se a palavra está esta errada

                system("cls");
            }


            if(cont==6){
                DesenhaForca(cont,0);//serve para mostrar o desenho do boneco
                for(i = 0; i < quantCaracter; i++)
                {
                    if(resposta[i]==frase[i])
                    {
                        cout<<resposta[i];//palavra
                    }
                    else
                    {
                        cout<<frase[i];//frase
                    }
                }
                MostrarLetrasErradas(erro1,erro2,erro3,erro4,erro5,tentativ,cont);//Mostra as letras erradas
                cout<<"\n\n\nVOCE PERDEU !!!!\n";//Mostra na tela a MSG VOCE PERDEU
                system("PAUSE");
            }
            if(cont==7)
            {
               MensagemVitoria(tentativ);//Mostra a msg de vitoria
            }
            confirmar = 'S';
            cout<<"QUER JOGAR DE NOVO (S/N)? ";
            fflush(stdin);//Essa função, com esse argumento aí (stdin), limpa o buffer do teclado.
            continuar = toupper(getchar());//a função toupper converte um caracter para maiúsculo.
        }
    }
    while(continuar=='S');//Enquanto o usuariio digitar "S"
    system("PAUSE");
    return 0;
}

int MenuPrincipal()//Classe menu principal
{
    int opcao;
    cout<<"\n      Digite um comando para prosseguir:                ";
    cout<<"\n                                                        ";
    cout<<"\n        1 – Jogar                                       ";                                  
    cout<<"\n        0 – Sair                                        ";
    cin>>opcao;//Lê qual opção o usuario digitou
    return opcao;//Retorna a opção selecionada
}
void VerificaChances(int contador)
{
    switch(contador)//Mostra quantas chances o jogador tem
    {
    case 0:
        cout<<"\n\nVoce pode errar 5 vezes";
        break;
    case 1:
        cout<<"\n\nVoce pode errar 4 vezes";
        break;
    case 2:
        cout<<"\n\nVoce pode errar 3 vezes";
        break;
    case 3:
        cout<<"\n\nVoce pode errar 2 vezes";
        break;
    case 4:
        cout<<"\n\nVoce pode errar apenas mais uma vez";
        break;
    case 5:
        cout<<"\n\nSe errar agora você perde o jogo!!!!";
    }

}
void MensagemVitoria(char tentativa){//classe de msg de vitoria

cout<<"\nPARABENS, VOCE GANHOU!!!!!!!!!!!!!!!!";//msg de vitoria

    tentativa='_';
}
void DesenhaForca(int contador,int flagInicio){//Classe que desenha o personagem enforcado

    if(flagInicio==0){//Flag de inicio 0 "Inicia no case 0".
        switch(contador)
        {
        case 0:
        	cout<<"_____   \n|.|         |   \n|.|        |\n|.|          \n|.|      \ \n|.|         \n|.| \n|.| \n|.| \n\n";
            break;

        case 1:
            cout<<"_____   \n|.|         |   \n|.|        |\n|.|         O    \n|.|         \n|.|       \n|.| \n|.| \n|.| \n\n";
            break;

        case 2:
            cout<<"_____   \n|.|         |   \n|.|        |\n|.|         O    \n|.|         |    \n|.|         \n|.| \n|.| \n|.| \n\n";
            break;

        case 3:
            cout<<"_____   \n|.|         |   \n|.|        |\n|.|         O    \n|.|        /|    \n|.|         \n|.| \n|.| \n|.| \n\n";
            break;

        case 4:
            cout<<"_____   \n|.|         |   \n|.|        |\n|.|         O    \n|.|        /|\\    \n|.|         \n|.| \n|.| \n|.| \n\n";
            break;

        case 5:
            cout<<"_____   \n|.|         |   \n|.|        |\n|.|         O    \n|.|        /|\\    \n|.|        /  \n|.|  \n|.|  \n|.| \n\n";
            break;
        case 6:
            cout<<"_____   \n|.|         |   \n|.|        |\n|.|         O    \n|.|        /|\\    \n|.|        / \\ \n|.|  \n|.|  \n|.| \n\n";
            break;
        }

	}
}
void MostrarLetrasErradas(int erro1,int erro2,int erro3,int erro4,int erro5,char tentativa, int contador)//Classe q
{
    if(contador==6)
    {
        cout<<"\n\n\n", erro1, erro2, erro3, erro4, erro5, tentativa;
    }
    else
    {
        cout<<"\n\n\n", erro1, erro2, erro3, erro4, erro5;
    }

}
//função que verifica as tentativas que o jogador possui
void VerificaTentativa(char qtdCaracter,char tentativa,int *certo,int *contador,char resposta[])//INSIRA COMENTARIO AQUI!!!
{
    int i;
    for(i = 0; i <= qtdCaracter; i++)
    {
        if(tentativa!=' ')
        {
            if(resposta[i]!='_')
            {
                *certo=*certo+1;
                if(*certo==qtdCaracter)
                {
                    *contador=7;
                    break;
                }
            }
        }
    }

}
void CapturaLetra(char *tentativa)//Captura a letra digitada
{
    char tecla;
    printf("\n\nDigite uma letra: ");
    fflush(stdin);
    scanf("%c",&tecla);
    *tentativa=tecla;
    *tentativa = tolower(*tentativa);
}

void VerificaSeErrou(char frase[],int qtdCaracter,int *contador,char tentativa,int *erro1,int *erro2,int *erro3,int *erro4,int *erro5,int *n)//Verifica se a letra digitada consta na string
{//função que verifica se errou letra, palavra
    int i;
    for(i = 0; i < qtdCaracter; i++)
    {
        if(tentativa!=frase[i])
        {
            *n=*n+1;
            if(*n==qtdCaracter)
            {
                *contador=*contador+1;
                if(*contador==1)
                {
                    *erro1 = tentativa;
                }
                if(*contador==2)
                {
                    *erro2 = tentativa;
                }
                if(*contador==3)
                {
                    *erro3 = tentativa;
                }
                if(*contador==4)
                {
                    *erro4 = tentativa;
                }
                if(*contador==5)
                {
                    *erro5 = tentativa;
                }
            }
        }
    }

}
char* BuscarPalavra(char nomeArquivo[])//Busca uma palavra no arquivo
{
    FILE *pont_arq;//variavel de arquivo com ponteiro
    char linha[1024]; // variável do tipo string
    char palavraSorteada[100];
    Palavra palavra;
    pont_arq = fopen(nomeArquivo, "r");
    if(pont_arq == NULL)//se esse ponteiro for igual a null ira dar um erro de abertura no arquivo.
    {
        cout<<"Erro na abertura do arquivo!";//msg caso o arquivo de palavras não seja encontrada
    }
    int i=0;
    tam=0;
    CriarListaVazia();
    while(fscanf(pont_arq, " %[^\n]s",linha)!=EOF){//ESSE EOF SIGNIFICA END OF FILE, OU SEJA, FIM DE ARQUIVO
    //O FSCANF lê os dados do fluxo e os armazena de acordo com o formato do parâmetro nos locais apontados pelos argumentos adicionais.


        char *ptr;//criação de um ponteiro
        ptr=strtok(linha,";");
        strcpy(palavra.palavra,ptr);//A biblioteca string.h contém uma série de funções para manipular strings. Essa função copia strings nessa linguagem de programação 
        ptr=strtok(NULL,";");//devolve um ponteiro para a próxima palavra na string apontada.  
        InseriNaLista(palavra);
        tam++;

    }
    fclose(pont_arq);//O ponteiro fp passado à função fclose() determina o arquivo a ser fechado. A função retorna zero no caso de sucesso. Fechar um arquivo faz com que qualquer caracter que tenha permanecido no "buffer" associado ao fluxo de saída seja gravado.

    Palavra lista[tam-1];//variavel do tipo palavra
    Palavra *palavraAux;//variavel do tipo palavra com um ponteiro
    palavraAux=primeiraPalavra->prox;
    i=0;
    int numero=SorteiaPalavra(tam-1);//Sorteia a palavra no arquivo
    while(palavraAux!= NULL){
        if(i==numero){
             strcpy( palavraSorteada,palavraAux->palavra);
        }
        palavraAux=palavraAux->prox;
        i++;
    }
    limparLista();
    return palavraSorteada;//Retorna a palavra selecionado do arquivo
}
void CriarListaVazia(){//procedimento sem parâmetros que cria uma lista vazia.
//aloca espaço para um bloco de bytes consecutivos na memória RAM do computador e devolve o endereço desse bloco.
    primeiraPalavra=(Palavra *)malloc(sizeof(Palavra));//funções malloc, realloc e free, estão na biblioteca stdlib. 
	 //sizeoff é uma função É um operador unário de tempo de compilação que pode ser usado para calcular o tamanho de seu operando.
    ultimaPalavra=primeiraPalavra;
}
void InseriNaLista(Palavra palavra){//inseri no programa a palavra selecionada
    Palavra *palavraAux;
    palavraAux = (Palavra *)malloc(sizeof(Palavra));

    strcpy( palavraAux->palavra,palavra.palavra);

    ultimaPalavra->prox=palavraAux;//o operador '->'(seta) deve-se usar em ponteiro.
    ultimaPalavra=ultimaPalavra->prox;//voce deve usar essa seta para o ponteiro apontar para a sua estrutura
    palavraAux->prox=NULL;
}
int SorteiaPalavra(int faixa){//função que serve para sortear palavras do arquivo.
    srand( (unsigned)time(NULL) );//pertencem a biblioteca time.h que selecionará , sorteára palavras aleatórias do gamewords.txt
    return  rand() % faixa;
}

void limparLista()//procedimento sem parametro que serve para limpar a lista
{
    Palavra *no = primeiraPalavra, *aux;
    while (no != NULL)
    {
        aux = no;
        no = no->prox;
        free (aux);//desaloca a porção de memória alocada por malloc. A instrução free (ptr) avisa ao sistema que o bloco de bytes apontado por ptr(ponteiro) está disponível para reciclagem. A próxima invocação de malloc poderá tomar posse desses bytes. 
    }
    primeiraPalavra = NULL;//encerramento do codigo
    ultimaPalavra=NULL;//encerramento do codigo
}
