#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"windows.h"
#include"efeito.c"

#define linhas 1000
#define colunas 100          // define o tamanho da matriz
#define quantinimigo linhas/10  //quantidade de inimigos
#define quantcombustivel linhas/15 ////quantidade de combustivel


  struct vjogo{
       int posicao;         //indica o lugar da matriz levado em consideração
       char sair;             // indica se o jogo acabou
       int velocidade;      //determina a velocidade de andamento do jogo.
       int pontes;   //contador de pontes
  };

  struct vperson{
       int posicao;       //posição do personagem (colunas)
       int posicaotiroc;  //posição tiro (colunas)
       int posicaotirol;  //posição tiro (linhas)
       int posicaoponte;  //posição para reiniciar
       int vidas;         //vidas do personagem
       int pontos;       //pontuacao do jogo
       int combustivel;  //quantidade de combustivel do personagem
  };

  struct vinimigo{
       int posicaol;     //posição (linha)
       int posicaoc;     //posição (coluna)
       char tipo;        //tipo de inimigo
       int pontos;       //pontuação que ele vale
       char direcao;     //direção que se movimenta
       int visivel;      //se aparece
  };

  struct vcombustivel{ 
       int linha;      
       int coluna;
  };


   int cont=0;              //controlador da velocidade do programa
   struct vjogo jogo;        //estrutura para jogo.
   struct vperson personagem;   //estrutura para personagem e tiro;
   struct vinimigo inimigo[quantinimigo];  //estrutura para inimigos
   struct vcombustivel combustivel[quantcombustivel];    //estrutura para combustivel
   int i,j;                  //contadores(auxiliares)
    char esc;
  
   char mapa[linhas][colunas]; //grid
//----------------------------------------------------------------------------------------------------------------------------------------------------
void cria_grid(){                //cria o grid

     int borda=25,bordailha=0,liberacaoponte=0;
     int aleatorio=0,aleatorioilha=0;
    
     for(i=0;i<linhas;i++)
         for(j=0;j<colunas;j++)       //Limpa a matriz
             mapa[i][j]=32;

     srand(time(NULL));               //Determina valores aleatorios.

  for(i=0;i<linhas;i++){               //loop para construção da matriz
   
     switch(aleatorio){
          case 0:aleatorio=rand()%15;break;                   //joga um valor aleatorio 

          case 1:aleatorio=-1;break;                          //maior borda possivel 43
          case 2:if(borda>40)aleatorio=-2;else aleatorio=-3;break; // borda=40
          case 3:if(borda>35)aleatorio=-4;else aleatorio=-5;break; // borda=35               PARA AUMENTARA DIFICULDADEAUMENTAS OS CASE
          case 4:if(borda>30)aleatorio=-6;else aleatorio=-7;break; // borda=30               SEM BREAK
          case 5:if(borda>25)aleatorio=-8;else aleatorio=-9;break; // borda=25

          case 6:                                                  // 2 vezes mais probabilidade de montar uma ilha
          case 7:if(borda<35&&i>10)aleatorio=-11;else aleatorio=0;break; // construir ilha apartir da 10ª linha

          case -1:if(borda!=43)borda++;else aleatorio=-10;break;      //       OBS: a ponte esta aqui!!!!!!!!
          case -2:if(borda!=40)borda--;else aleatorio=0;break;
          case -3:if(borda!=40)borda++;else aleatorio=0;break;
          case -4:if(borda!=35)borda--;else aleatorio=0;break;
          case -5:if(borda!=35)borda++;else aleatorio=0;break;            //faz com que a borda vique do tamanho exato
          case -6:if(borda!=30)borda--;else aleatorio=0;break;
          case -7:if(borda!=30)borda++;else aleatorio=0;break;
          case -8:if(borda!=25)borda--;else aleatorio=0;break;
          case -9:if(borda!=25)borda++;else aleatorio=0;break;
          case -10:if(liberacaoponte==1)
                        for(j=43;j<57;j++)                                     //monta a ponte
                              mapa[i][j]='P';liberacaoponte=0;aleatorio=0;break;  

          case -11:switch(aleatorioilha){                                                    //montagem da ilha
                        case 0:aleatorioilha=rand()%13;break;                                // aleatorio para ilha.

                        case 1:if(bordailha<2)aleatorioilha=-1;else aleatorioilha=-2;break;  //borda da ilha=2
                        case 2:if(bordailha<5)aleatorioilha=-3;else aleatorioilha=-4;break;  //borda da ilha=5
                        case 3:if(bordailha<10)aleatorioilha=-5;else aleatorioilha=-6;break; //borda da ilha=10
                        case 4:if(bordailha<15)aleatorioilha=-7;else aleatorioilha=0;break;  // borda da ilha=15
                        case 5:
                        case 6:if(bordailha>0)bordailha--;else{aleatorio=0;aleatorioilha=0;}break; //termina a ilha

                        case -1:if(bordailha!=2)bordailha++;else aleatorioilha=0;          break;
                        case -2:if(bordailha!=2)bordailha--;else aleatorioilha=0;          break;
                        case -3:if(bordailha!=5&&borda<40)bordailha++;else aleatorioilha=0;break;  //faz o tamanho da ilha
                        case -4:if(bordailha!=5)bordailha--;else aleatorioilha=0;          break;
                        case -5:if(bordailha!=10&&borda<35)bordailha++;else aleatorioilha=0;   break;
                        case -6:if(bordailha!=10)bordailha--;else aleatorioilha=0;         break;
                        case -7:if(bordailha!=15&&borda<30)bordailha++;else aleatorioilha=0;break;
  
                        default:aleatorioilha=0;  //joga outro aleatorio para ilha
           } break;//fim do swich da ilha            
       
          default:aleatorio=0;               //para o resto dos resultados. jogar outro aleatório
     } // fim do switch principal

     for(j=0;j<borda;j++)
           {                                //monta as bordas
                 mapa[i][j]='m';                  //esquerda           (em relação ao usuario)
                 mapa[i][colunas-j-1]='m';          //direita
           }

     for(j=0;j<bordailha;j++)
          {                                //monta a ilha
                 mapa[i][j+50]='m';
                 mapa[i][50-j-1]='m';
          }

     if((i+1)%(linhas/4)==0)liberacaoponte=1;  //determina a distancia das pontes
 }//fim do looping

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void jogo_status(){
     if(mapa[jogo.posicao+5][personagem.posicao]=='m'){jogo.sair=1;personagem.vidas--;}   //se bateu na motanha
     if(mapa[jogo.posicao+5][personagem.posicao]=='P'){jogo.sair=1;personagem.vidas--;}  //se bateu na ponte
     for(i=0;i<quantinimigo;i++)
         if(inimigo[i].posicaol==jogo.posicao+5&&(inimigo[i].posicaoc==personagem.posicao||inimigo[i].posicaoc-1==personagem.posicao||inimigo[i].posicaoc+1==personagem.posicao)&&inimigo[i].visivel){jogo.sair=1;personagem.vidas--;}       //se bateu no inimigo
       
     for(i=0;i<quantinimigo;i++)  
         if(personagem.posicaotirol==inimigo[i].posicaol&&(personagem.posicaotiroc==inimigo[i].posicaoc||personagem.posicaotiroc==inimigo[i].posicaoc-1||personagem.posicaotiroc==inimigo[i].posicaoc+1)&&inimigo[i].visivel)    //se acertou inimigo
         {
         	inimigo[i].visivel=0;                                               //deixa invisivel
         	personagem.pontos+=inimigo[i].pontos;                            //soma os pontos 
         	personagem.posicaotirol=0;                                       //libera tiro                   
         }

     if(mapa[personagem.posicaotirol][personagem.posicaotiroc]=='F')       //se acertou os combustiveis
     {
        personagem.pontos+=80;                                            //acrescenta os pontos
        for(i=personagem.posicaotirol-3;i<personagem.posicaotirol+3;i++)
            if(mapa[i][personagem.posicaotiroc]=='F')                      //apaga o combustivel
                mapa[i][personagem.posicaotiroc]=32;

        personagem.posicaotirol=0;                  //libera tiro
     }

     if(mapa[personagem.posicaotirol][personagem.posicaotiroc]=='P')               //se acertou a ponte
     {
     	    for(j=43;j<57;j++)                            //desmonta a ponte
                    mapa[personagem.posicaotirol][j]=' ';  
          personagem.posicaoponte=personagem.posicaotirol;     // determina local para reinicio
          personagem.posicaotirol=0;                      //libera tiro
          jogo.pontes*=2;                    //acrecenta pontes
     }
     
     if(mapa[personagem.posicaotirol][personagem.posicaotiroc]=='m')          //se atirar na montanha
           personagem.posicaotirol=0;   


     if(personagem.combustivel<1)                             // se acabou o combustivel
     {
       jogo.sair=1;
       personagem.vidas--;
     }

     if(jogo.posicao+33>linhas)      //se ganhou
     {
         esc=2;
         limpa_tela();
         system("figlet Parabéns voce ganhou");
     }
 
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void atualiza_tela(){           //printa a matriz na tela
     printf("%c[%dm",27,32); 
     for(i=jogo.posicao;i<jogo.posicao+33;i++)
          for(j=0;j<colunas;j++)
                 printf("%c[%d;%df%c",27,36-(i-jogo.posicao),j+5,mapa[i][j]);     //imprime a matriz

      printf("%c[%dm",27,37);
      printf("%c[%d;%dfA",27,31,personagem.posicao+5);         // printa ao personagem

       printf("%c[%dm",27,33);
      for(i=0;i<quantinimigo;i++)
             if(inimigo[i].posicaol>jogo.posicao&&inimigo[i].posicaol<jogo.posicao+33&&inimigo[i].visivel==1) // se inimigo asta na posicao que aparece na tela
                   switch(inimigo[i].tipo)                     //ve qual inimigo é 
                   {
                        case 't':printf("%c[%d;%dfTTT",27,36-(inimigo[i].posicaol-jogo.posicao),inimigo[i].posicaoc+4);break;
                        case 'h':printf("%c[%d;%dfHHH",27,36-(inimigo[i].posicaol-jogo.posicao),inimigo[i].posicaoc+4);break;
                        case 'j':printf("%c[%d;%dfJJJ",27,36-(inimigo[i].posicaol-jogo.posicao),inimigo[i].posicaoc+4);break;
                        case 'b':printf("%c[%d;%dfBBB",27,36-(inimigo[i].posicaol-jogo.posicao),inimigo[i].posicaoc+4);break;
                   }
       
      printf("%c[%dm",27,35);         
      printf("%c[%d;%dfPontos: %d",27,4,120,personagem.pontos);   //mostra os pontos
      printf("%c[%d;%dfVidas: %d",27,6,120,personagem.vidas);     //mostra vidas
      printf("%c[%d;%dfFase: %d",27,8,120,jogo.pontes);     //mostra vidas
      printf("%c[%d;%dfCombustivel: |         |%c[%d;%df",27,10,114,27,10,128);      //apaga o combustivel
      for(i=0;i<personagem.combustivel;i++)                    //coloca o nivel de combustivel
            printf("#");
      printf("%c[%d;%dfDesenvolvido por: Laercio Minozzo",27,34,110);
      printf("%c[%d;%df",27,1,1);//posiciona o cursor no canto.
       printf("%c[%dm",27,0);
 }

//----------------------------------------------------------------------------------------------------------------------------------------------------
void movimenta_tiro(){
    if(personagem.posicaotirol!=0&&cont%20000==0){                                           // <-- determina a velocidade da bala
                    printf("%c[%dm",27,31); 
                    printf("%c[%d;%df ",27,36-(personagem.posicaotirol-jogo.posicao),personagem.posicaotiroc+5);    //apaga o tiro
                    personagem.posicaotirol++;                                                  //movimenta a bala.

                    printf("%c[%d;%df.%c[%d;%df",27,36-(personagem.posicaotirol-jogo.posicao),personagem.posicaotiroc+5,27,1,1);    //printa o tiro
                   
                    if(personagem.posicaotirol-jogo.posicao>31)
                          personagem.posicaotirol=0;
                    printf("%c[%dm",27,0); 
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void inicializa_inimigo(){

    int aleatorio,aux,b;

    j=0;                                   //j = contador de inimigos e i = contador de linhas
    for(i=7;i<linhas&&j<quantinimigo;i++)  // distribui inimigos nas linhas iniciada na linha 7
    {
         aleatorio=rand()%8;        //proporção 1/8
        
         if(aleatorio==0&&mapa[i][50]!='P')   //nao printa inimigo na ponte
         {
               inimigo[j].posicaol=i;     //determina o inimigo na quela linha
               j++;                   //muda inimigo
         }
    }
   

         //caso não foram usados todos os inimigos...                               determina linhas
        for(i=linhas-1;i>7&&j<quantinimigo;i--)   //...distribui ao contrario
        {
               b=0;
               aleatorio=rand()%3;        //proporção 1/3
               
               for(aux=0;aux<=quantinimigo;aux++)     //testa se ja tem inimigo na linha
                       if(inimigo[aux].posicaol==i)
                               b=1;

               if(aleatorio==0&&mapa[i][50]!='P'&&!b)   //nao printa inimigo na ponte e nem se ja tem outro inimigo
               {
                    inimigo[j].posicaol=i;     //determina o inimigo na quela linha
                    j++;                   //muda inimigo
               }
 
        }
        

    i=0;
    while(i<quantinimigo)
    {
          aleatorio=rand()%colunas;       //sorteia uma posicao
        
          if(mapa[inimigo[i].posicaol][aleatorio-2]==32&&mapa[inimigo[i].posicaol][aleatorio+2]==32){  // se for dentro do rio    determina a coluna

                 inimigo[i].posicaoc=aleatorio;          // posiciona
                 i++;
          }
    }

    for(i=0;i<quantinimigo;i++)           //determina o tipo de inimigo
    {
        aleatorio=rand()%4;
  
        switch(aleatorio)
        {
             case 0:inimigo[i].tipo='t';
                    inimigo[i].pontos=30;break;
             case 1:inimigo[i].tipo='h';
                    inimigo[i].pontos=60;break;
             case 2:inimigo[i].tipo='j';
                    inimigo[i].pontos=100;break;
             case 3:inimigo[i].tipo='b';
                    inimigo[i].pontos=60;
         }
    }

    for(i=0;i<quantinimigo;i++){     //determina a doreção que o inimigo va dse movimentar
         aleatorio=rand()%3;
         
         inimigo[i].direcao=aleatorio-1;     //a dereção vai ser somada -1 0 1
    }

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void movimenta_inimigo(){
	int aleatorio;
	
	for(i=0;i<quantinimigo;i++){       //repete para todos inimigos
	
			aleatorio=random()%4-1;     //joga aleatorio
			
			if(aleatorio<2)
			inimigo[i].direcao=aleatorio;   //retorna a nova direção
			
			if((inimigo[i].direcao==1&&mapa[inimigo[i].posicaol][inimigo[i].posicaoc+2]==32)||(inimigo[i].direcao==-1&&mapa[inimigo[i].posicaol][inimigo[i].posicaoc-2]==32))
			inimigo[i].posicaoc+=inimigo[i].direcao;   //se possivel movimenta
		
	    
    }
   
    
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void inicializa_combustivel(){

   int aleatorio;

   j=0;
   for(i=10;(i<linhas-1&&j<quantcombustivel)||i%25==0;i++)  //percorre ttodas as linhas  iniciada na 10 e finalizada na penultima ou acabou combustvel
   {
       aleatorio=rand()%15;   //proporção 1/15
       if(aleatorio==0&&mapa[i][50]!='P'&&mapa[i+1][50]!='P'&&mapa[i-1][50]!='P')  //se liberou a construção do fuel e não tem ponte 
       {
             while(mapa[i+1][aleatorio]!=32||mapa[i-1][aleatorio]!=32)  //enquanto não encontra uma boa posição 
                  aleatorio=rand()%100;                                 //joga uma nova posição

              combustivel[j].linha=i;
              combustivel[j].coluna=aleatorio;                       //posiciona o combustivel
       
              mapa[i+1][aleatorio]='F';
              mapa[i][aleatorio]='F';                                      //desenha o combustivel
              mapa[i-1][aleatorio]='F';
          
             j++;                                        //muda combustivel
       }
   }

    //se não foram usados 
   for(;i>10&&j<quantcombustivel;i--)  //percorre ttodas as linhas  iniciada na penultima e finalizada na 10 ou acabou combustvel
   {
       aleatorio=rand()%15;   //proporção 1/15
       if(aleatorio==0&&mapa[i][50]!='P'&&mapa[i+1][50]!='P'&&mapa[i-1][50]!='P')  //se liberou a construção do fuel e não tem ponte 
       {
             while(mapa[i+1][aleatorio]!=32||mapa[i-1][aleatorio]!=32)  //enquanto não encontra uma boa posição 
                  aleatorio=rand()%100;                                 //joga uma nova posição

              combustivel[j].linha=i;
              combustivel[j].coluna=aleatorio;                       //posiciona o combustivel
       
              mapa[i+1][aleatorio]='F';
              mapa[i][aleatorio]='F';                                      //desenha o combustivel
              mapa[i-1][aleatorio]='F';
          
             j++;                                        //muda combustivel
       }
   }
       
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
  
        //auxiliares para main
 do{
     
    esc=0;              //inicia variaveis
    jogo.velocidade=100000;
    jogo.pontes=0;    

    personagem.posicaotirol=0;           //posição do tiro =0 para indicar que  o tiro esta liberado.
    personagem.posicaoponte=0;           //posição de inicio depois d morrer
    personagem.vidas=5;

    cria_grid();       //constroi a matriz
    inicializa_combustivel();  //distribui os combustiveis
    inicializa_inimigo();   //atribui os valores iniciais para os inimigos
 
    inicializacao();      //cria o efeito de iniciar
    desenha_moldura();
    while(personagem.vidas>0&&!esc) 
    {
        jogo.posicao=personagem.posicaoponte;   //determina posicao de inicio
        personagem.posicao=50;   //posição do personagem =50
        jogo.sair=0;    //sair =falso
        personagem.combustivel=9;  //enche o tanque
        for(i=0;i<quantinimigo;i++)
                   inimigo[i].visivel=1;     //deixa inimigos visivvel
        for(i=0;i<quantcombustivel;i++)
        {   
                    mapa[combustivel[i].linha-1][combustivel[i].coluna]='F'; //deixa combustiveis visivvel
                    mapa[combustivel[i].linha][combustivel[i].coluna]='F';
                    mapa[combustivel[i].linha+1][combustivel[i].coluna]='F';
        }
        while(!jogo.sair&&!esc)      //looping principal do jogo
        { 
          if(kbhit())          //leitura das teclas
             switch(getch())
             {
                  case 27:if(kbhit()&&getch()==91){switch(getch())   // leitura das teclas especiais
                                                  {
                                                      case 68:personagem.posicao--;break;            // <--
                                                      case 67:personagem.posicao++;break;             //-->
                                                  }atualiza_tela();
                            }else
                             {                                     //case esc
                                if(sair())               //se apertar esc pede se sai
                                      esc=1;
                                
                             }break;

                  case 32:if(personagem.posicaotirol==0)                       //" "
                          {
                                personagem.posicaotirol=jogo.posicao+6;           //determina a posicao do tiro como
                                personagem.posicaotiroc=personagem.posicao;   //sendo a do personagem +1 na matriz.
                          }break;

                  case 'p':getch();                            // pausa o jogo
             }

          movimenta_tiro();                  //ve dos tiro
          if (cont>jogo.velocidade-(jogo.pontes*20000))
          {                                 //determina a velocidade de andamento do jogo
                        cont=0;
                        jogo.posicao++;  
                        movimenta_inimigo();   //ve da movimentação dos inimigos
                        atualiza_tela();
                        if(jogo.posicao%10==0)                      //diminui combustivel
                                 personagem.combustivel--;
                        if(mapa[jogo.posicao+5][personagem.posicao]=='F'&&personagem.combustivel<9)             //se passou por combustivel
                        {
                                 printf("\a");
                                 personagem.combustivel++;
                        }
          }
          jogo_status();       //testa se fodeo
          cont++;
   
    }
  }
   if(personagem.vidas==0)
   {
        limpa_tela();
        printf("%c[%d;%df Voce perdeu !! :/   [precione qualquer tecla]",27,10,10);
        getch();
   }
 }while(!sair()&&esc==0);

 printf("%c[%dm",27,0); 
return 0;
}
