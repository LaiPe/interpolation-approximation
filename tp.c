#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//DECLA TAB
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
//AFFICHE TAB
void afficheTab(float * t,int taille){
    for (int i=0;i<taille;i++){
        printf("%g;",t[i]);
    }
    printf("\n");
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
int main(){

	float * X;
	float * Y;
	int choix;
	printf("Choissez le système pour l'interpolation (1,2,3,4):\n");
 	scanf("%d", &choix);

	int n,i;
	if(choix==1){
		n = 20;
		int Tx[20]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38};
		float Ty[20]={0.99987,0.99997,1.00000,0.99997,0.99988,0.99973,0.99953,0.99927,0.99897,0.999846,0.99805,0.999705,0.99751,0.99705,0.99650,0.99664,0.99533,0.99472,0.99333,0.99326};
		X = (float *)malloc(n * sizeof(float));
        Y = (float *)malloc(n * sizeof(float));
		for(i = 0; i < n; i++){
            X[i] = Tx[i];
            Y[i] = Ty[i];
        }
	
	}
	else if(choix==2){
		n = 21;
		int Tx[21]={752,855,871,734,610,582,921,492,569,462,907,643,862,524,679,902,918,828,875,809,894};
		float Ty[21]={85,83,162,79,81,83,281,81,81,80,243,84,84,82,80,226,260,82,186,77,223};
		X = (float *)malloc(n * sizeof(float));
        Y = (float *)malloc(n * sizeof(float));
		for(i = 0; i < n; i++){
            X[i] = Tx[i];
            Y[i] = Ty[i];
        }
	}
	else if(choix==3){
	}
	else if(choix==4){
	}		
	else{
        printf("erreur\n");
        exit(-1);
	}

    afficheTab(X,n);
    afficheTab(Y,n);
    //conformLagrange(X,Y,n);
    
    float entree;
    printf("x?:");
    scanf("%f",&entree);
    float result=lagrange(X,Y,entree,n); //! n !!!!!
    printf("y=%g\n",result);

    return 0;
}
