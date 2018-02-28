
float f = 1.42;
  unsigned int a;
  unsigned int * ptr_tmp = (unsigned int *)(&f);
  a=*ptr_tmp;


  unsigned int tableau[32];
  int machaine[32];
  unsigned int som=1;
  int i;

  for(i=0;i<32;i++)
  {
     tableau[i]=som;
     som=som*2;
  }


  unsigned int  resultat;


 for(i=0;i<=32;i++)
 {
   resultat = a & tableau[i];
   if( resultat == tableau[i] )
   { machaine[i]=1;  }
   else
   { machaine[i]=0;}
 }

   printf("nombre float en binaire est :");
for(i=31;i>=0;i--)
{

  fprintf(stdout,"%d",machaine[i]);

}

printf("\n");
printf("nombre f  : %f\n ",f );
printf("nombre e  : %e\n ",f );
printf("nombre g  : %g\n ",f );
