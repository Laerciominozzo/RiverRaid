void limpa_tela(){
    int i,j;
 
    for(i=0;i<50;i++)
      for(j=0;j<150;j++)
         printf("%c[%d;%df ",27,i,j);
   printf("%c[%d;%df",27,1,1);   //posciona o cursorno canto superior
  
}

void inicializacao(){  
  limpa_tela();

 
  printf("\n\n\n\n\n\n\n\n          qaaaaap    qaa jaa,    _aa, aaaaaaap  aaaaag,         aaaaag,      qaap     aap  qaaaagp\n");
  printf("          ]QQWWWQg,  ]QQ )QQL    jWQ` QQWQWQWf  QQWQWQQp        QQWQWQQp    _QQQQ     QQf  ]QQWWQQmp\n");  
  printf("          ]QQ??$WQ[  ]QQ  4Qm.   mQE  QQP????`  QQP??QQm        QQP??QQm    ]WQQQp    QQf  ]QQ??9QQQc\n"); 
  printf("          ]QQ  -QQf  ]QQ  ]QQp  jQQ[  QQf       QQf  ]QQ        QQf  ]QQ    jQ@WWk    QQf  ]QQ   -4QQ,\n");
  printf("          ]QQ  qQQf  ]QQ  -QQL  jQW'  QQ6aaaa   QQf _dQE        QQf _dQE   .QQf]QQ,   QQf  ]QQ    ]QQ[\n");
  printf("          ]QQQQQW!   ]QQ   4QQ,_QQF   QQQQQWQ   QQQQQQ@'        QQQQQQ@'   ]QQ']QQ[   QQf  ]QQ     QQ[\n");
  printf("          ]QQQQQQc   ]QQ   )WQr]WQf   QQP????   QQQQQQg,        QQQQQQg,   mQD  $Qm   QQf  ]QQ    .QQ[\n");
  printf("          ]QQ )$QQ,  ]QQ    $QkjQ@    QQf       QQf )QQL        QQf )QQL  jQQQQQQQQr  QQf  ]QQ    jWQf\n");
  printf("          ]QQ  ]QQL  ]QQ    ]QQQQf    QQf       QQf  4QQ,       QQf  4QQ, jQQQQQQQQL  QQf  ]QQ  _aWQE\n");
  printf("          ]QQ   4QQ, ]QQ    ]QQQQ'    QQQQQQQf  QQf  ]QQk       QQf  ]QQk QWF    4QQ  QQf  ]QQQQQQQD`\n"); 
  printf("          ]QQ   )QQk ]QQ     $QQE     QQQQQQQf  QQf   4QQp      QQf   4QQaQQ(    ]QQp QQf  ]QQQQWV!\n\n\n          ");
  system("figlet      Carregando.");
 
 

    sleep(3);
  
  limpa_tela();
   
 }

int sair(){
  char resposta;
  limpa_tela();
  printf("%c[%dm",27,34);
  printf("%c[%d;%dfDeseja sair?[S/N]",27,20,60);
  while(resposta!='s'&&resposta!='n')
        scanf("%c",&resposta);
       if(resposta=='s')
            return 1;
       else
            return 0;
  
}


void desenha_moldura(){
     int i,j;
     printf("%c[%dm",27,31);
     for(i=2;i<108;i++)
        for(j=2;j<39;j++)
           printf("%c[%d;%df*",27,j,i);
      printf("%c[%dm",27,0);
}
     
