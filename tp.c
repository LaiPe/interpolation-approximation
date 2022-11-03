#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//DECLARATION ET INIT
float ** declMatrice(int lignes,int colonnes){
    float ** X=malloc(lignes*sizeof(float*));
    if (X==NULL){return NULL;}
    for (int i=0;i<lignes;i++){
        X[i]=malloc(colonnes*sizeof(float));
        if (X[i]==NULL){
            for(int j=0;j<i;j++){
                free(X[j]);
            }
            free(X);
            return NULL;
        }
    }
    return X;
}
float * declTab(int taille){
    float * X=(float *)malloc(taille * sizeof(float));
    if (X==NULL){return NULL;}
    return X;
}
void initTab(float * tab,float val[],int taille){
    for (int i=0;i<taille;i++){
        tab[i]=val[i];
    }
}
//AFFICHAGE
void afficheTab(float * t,int taille){
    for (int i=0;i<taille;i++){
        printf("%g;",t[i]);
    }
    printf("\n");
}
//ECRITURE FICHIER
int matriceToCSV(float ** mat,int lignes,int colonnes){
    FILE * fd=fopen("./bin/resultats.csv","w");
    for (int i=0;i<lignes;i++){
        for (int j=0;j<colonnes;j++){
            fprintf(fd,"%g",mat[i][j]);
            if (j!=colonnes-1){
                fprintf(fd,",");
            }
        }
        fprintf(fd,"\n");
    }
    fclose(fd);
}
//OUTILS
float puiss(float x,int puiss){
    float result=1;
    if (puiss>=0){
        for (int i=0;i<puiss;i++){
            result=result*x;
        }
    }
    else{
        for (int i=0;i>puiss;i--){
            result=result/x;
        }
    }
    return result;
}
void triCroiss(float * X,float * Y,int taille){
    int i,j,cx,cy;
    for(i=0;i<taille-1;i++){
        for(j=i+1;j<taille;j++){
            if (X[i]>X[j]){
                cx=X[i];
                cy=Y[i];
                X[i]=X[j];
                Y[i]=Y[j];
                X[j]=cx;
                Y[j]=cy;
            }
        }
    }
}

float lagrange(float * X,float * Y,float xentree, int taille){
    float result=0;
    for (int i=0;i<taille;i++){ 
        float Li=1;
        for (int j=0;j<taille;j++){
            if (j!=i){
                Li*=(xentree-X[j])/(X[i]-X[j]);
            }
        }  
        result+=Y[i]*Li;
    }
   
    return result;
}
int conformLagrange(float * X,float * Y, int taille){
    int result=0;
    for (int i=0;i<taille;i++){
        printf("lagrange(%g)==Y[%d]: ",X[i],i);
        if(lagrange(X,Y,X[i],taille)==Y[i]){
            printf("True\n");
        }
        else{
            printf("False\n");
            result++;
        }
    }
    return result;
}
void traceLagrange(float * X,float * Y,int taille,float ecart,float pas){
    float debut=X[0]-ecart;
    float fin=X[taille-1]+ecart;
    int n=((fin-debut)/pas)+1;
    printf("%g,%g,%d\n",debut,fin,n);

    float ** M=declMatrice(2,n);
    for(int i=0;i<=n;i++){
        M[0][i]=debut;
        M[1][i]=lagrange(X,Y,debut,taille);
        debut+=pas;
    }

    matriceToCSV(M,2,n);
}
int main(){

	float * X;
	float * Y;
	int n,i,conti=0,choix;

    while (conti==0){
        printf("Choissez le système pour l'interpolation (1,2,3,4):\n");
 	    scanf("%d", &choix);
        if(choix==1){
            n = 20;
            float Tx[20]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38};
            float Ty[20]={0.99987,0.99997,1.00000,0.99997,0.99988,0.99973,0.99953,0.99927,0.99897,0.999846,0.99805,0.999705,0.99751,0.99705,0.99650,0.99664,0.99533,0.99472,0.99333,0.99326};
            X = declTab(n);
            Y = declTab(n);
            initTab(X,Tx,n);
            initTab(Y,Ty,n);

            conti=1;
        }
        else if(choix==2){
            n = 21;
            float Tx[21]={752,855,871,734,610,582,921,492,569,462,907,643,862,524,679,902,918,828,875,809,894};
            float Ty[21]={85,83,162,79,81,83,281,81,81,80,243,84,84,82,80,226,260,82,186,77,223};
            X = declTab(n);
            Y = declTab(n);
            initTab(X,Tx,n);
            initTab(Y,Ty,n);

            triCroiss(X,Y,n);
            conti=1;
        }
        else if(choix==3){
            n=11;
            float Tx[11]={10,8,13,9,11,14,6,4,12,7,5};
            float Ty[11]={8.04,6.95,7.58,8.81,8.33,9.96,7.24,4.26,10.84,4.82,5.68};
            X = declTab(n);
            Y = declTab(n);
            initTab(X,Tx,n);
            initTab(Y,Ty,n);

            triCroiss(X,Y,n);
            conti=1; 
        }
        else if(choix==4){
            n=7;
            float Tx[7]={20,30,40,50,100,300,500};
            float Ty[7]={352,128,62.3,35.7,6.3,0.4,0.1};
            X = declTab(n);
            Y = declTab(n);
            initTab(X,Tx,n);
            initTab(Y,Ty,n);

            conti=1;
        }		
        else{
            printf("Veillez rentrer un valeur valide.\n");
        }
    }

    //afficheTab(X,n);
    //afficheTab(Y,n);
    //conformLagrange(X,Y,n);
    
    /*float entree;
    printf("x?:");
    scanf("%f",&entree);
    float result=lagrange(X,Y,entree,n);
    printf("y=%g\n",result);*/


    traceLagrange(X,Y,n,0,0.1);

    return 0;
}
