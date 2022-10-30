#include <stdio.h>
#include <stdlib.h>

#define N 3
#define M 20

//DECLA MATRICES
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
    float * X=malloc(taille*sizeof(float));
    if (X==NULL){return NULL;}
    return X;
}
void initTab(float * tab,float val[],int taille){
    for (int i=0;i<taille;i++){
        tab[i]=val[i];
    }
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
float * foncAffine(int taille){
    float * affin=declTab(taille);
    for (int i=0;i<taille;i++){
        affin[i]=i;
    }
    return affin;
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
int main(){
    float * X=declTab(N);
    float * A=declTab(N);
    float * Y=declTab(N);
    
    //Jeux d'essais 4.1
    float X_a[M]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38};
    float Y_a[M]={0.99987,0.99997,1.00000,0.99997,0.99953,0.99927,0.99897,0.99846,0.99805,0.999751,0.99705,0.99650,0.99664,0.99533,0.99472,0.99472,0.99333,0.99326};

    //Jeux d'essais 4.2
    

    initTab(X,X_a,N);
    initTab(Y,Y_a,N);

    /*float * affin=foncAffine(N);
    printf("{");
    for (int i=0;i<N;i++){
        printf("%g ",affin[i]);
    }
    printf("}\n");*/


    float entree;
    printf("x?:");
    scanf("%f",&entree);
    float result=lagrange(X,Y,entree,N);
    printf("y=%g\n",result);
    return 0;
}