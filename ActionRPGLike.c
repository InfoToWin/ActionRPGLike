#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>


void prepareDisplayMatrix(int,int,char displaymatrix[][30]);
void preparePlacementMatrix(int,int,int,int,char placementmatrix[][30]);
void prepareTheGame(int,int,int,int,char displaymatrix[][30],char placementmatrix[][30]);
void update(int,int,int ,char displaymatrix[][30],char placementmatrix[][30]);
void fightWithTheEnemy(int,int,int *,char,char placematrix[][30]);
void updateDisplayMatrix(int,int,char,char displaymatrix[][30],char placementmatrix[][30]);
void display(int,int,char displaymatrix[][30]);
void displayGodMode(int,int,char displaymatrix[][30],char placementmatrix[][30]);


char P[2];


int main(){
	
	int Enemy_count=10,Tree_count=10,ROW=20,COL=30,storeenemy;
	char DisplayMatrix[20][30],PlacementMatrix[20][30];
	
	srand(time(0));
	
	prepareTheGame(ROW,COL,Enemy_count,Tree_count,DisplayMatrix,PlacementMatrix);
	update(ROW,COL,storeenemy,DisplayMatrix,PlacementMatrix);

	
	system("pause");
	return 0;
	
}


void prepareTheGame(int Row,int Col,int enemycount,int treecount,char displaymatrix[][30],char placementmatrix[][30]){
	
	prepareDisplayMatrix(Row,Col,displaymatrix);
	preparePlacementMatrix(Row,Col,enemycount,treecount,placementmatrix);
}


void prepareDisplayMatrix(int Row,int Col,char displaymatrix[][30]){
	
	int i,j;
	
	for(i=0;i<Row;i++){
		for(j=0;j<Col;j++){
			
			if(i==0 && j==0){
				displaymatrix[0][0]='P';
			}
			else{
				displaymatrix[i][j]=-78;
			}
		}
	}
}


void preparePlacementMatrix(int Row,int Col,int enemycount,int treecount,char placementmatrix[][30]){
	int i,j,iRand_E,jRand_E,iRand_T,jRand_T;
	
		
	for(i=0;i<Row;i++){
		for(j=0;j<Col;j++){
			
			placementmatrix[i][j]=' ';	
		}
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			
			placementmatrix[i][j]=-80;	
		}
	}

	for(i=0;i<enemycount;i++){
		
		iRand_E=rand()%20;
		jRand_E=rand()%30;
		
		if(placementmatrix[iRand_E][jRand_E]==' '){
			placementmatrix[iRand_E][jRand_E]='E';
		}
	}
	
	for(i=0;i<treecount;i++){
		
		iRand_T=rand()%20;
		jRand_T=rand()%30;
		
		if(placementmatrix[iRand_T][jRand_T]==' '){
			placementmatrix[iRand_T][jRand_T]='T';
		}
	}
}


void update(int Row,int Col,int storeenemy,char displaymatrix[][30],char placementmatrix[][30]){
	
	char Char;
	int enemy=storeenemy;
	
	
	do{
		
		system("cls");
		
		updateDisplayMatrix(Row,Col,Char,displaymatrix,placementmatrix);
		display(Row,Col,displaymatrix);
		Char=getch();
		
		if(Char=='c' || Char=='C'){
			
			do{
				
				system("cls");
				
				displayGodMode(Row,Col,displaymatrix,placementmatrix);
				Char=getch();
				fightWithTheEnemy(Row,Col,&enemy,Char,placementmatrix);
				updateDisplayMatrix(Row,Col,Char,displaymatrix,placementmatrix);
			 		
			}while(!((Char=='c') || (Char=='C') || (Char=='q') || (enemy==10)));	
		}
		else{

			fightWithTheEnemy(Row,Col,&enemy,Char,placementmatrix);		
	    }			    
	}while(!((Char=='q') || (enemy==10)));
	
}


void fightWithTheEnemy(int Row,int Col,int *enemy,char Char,char placementmatrix[][30]){
	
	int i,flag=0;
	int around_P[8][2]={{P[0]-1,P[1]-1} , {P[0]-1,P[1]} , {P[0]-1,P[1]+1} , {P[0],P[1]-1} , {P[0],P[1]+1} , {P[0]+1,P[1]-1} , {P[0]+1,P[1]} , {P[0]+1,P[1]+1}};
  
	if(Char=='h' || Char == 'H'){
			
		for(i=0;i<8;i++){
			
			if(flag){
				break;	
			}
			if(placementmatrix[around_P[i][0]][around_P[i][1]]=='E'){
					
				placementmatrix[around_P[i][0]][around_P[i][1]]=' ';
				*enemy+=1;	
				flag=1;	
			}
		}
	}
}


void updateDisplayMatrix(int Row,int Col,char Char,char displaymatrix[][30],char placementmatrix[][30]){

	int i,j,PP[2]={P[0],P[1]};
	
	displaymatrix[PP[0]][PP[1]]=-80;
		
	
	switch(Char){
		
		case 'w':
		case 'W':
			if(!((placementmatrix[P[0]-1][P[1]]=='E') || (placementmatrix[P[0]-1][P[1]]=='T')) && (P[0]-1>=0)){
				P[0]-=1;
			}
		break;
		case 'a':
		case 'A':
			if(!((placementmatrix[P[0]][P[1]-1]=='E') || (placementmatrix[P[0]][P[1]-1]=='T')) && (P[1]-1>=0)){
				P[1]-=1;
			}
		break;
		
		case 's':
		case 'S':
			if(!((placementmatrix[P[0]+1][P[1]]=='E') || (placementmatrix[P[0]+1][P[1]]=='T')) && (P[0]+1<20)){
				P[0]+=1;
			}
		break;	
		case 'd':
		case 'D':
			if(!((placementmatrix[P[0]][P[1]+1]=='E') || (placementmatrix[P[0]][P[1]+1]=='T')) && (P[1]+1<30)){
				P[1]+=1;
			}	
		break;
	} 
	
	int around_P[8][2]={{P[0]-1,P[1]-1} , {P[0]-1,P[1]} , {P[0]-1,P[1]+1} , {P[0],P[1]-1} , {P[0],P[1]+1} , {P[0]+1,P[1]-1} , {P[0]+1,P[1]} , {P[0]+1,P[1]+1}};
	
	displaymatrix[P[0]][P[1]]='P';
	
	for(i=0;i<8;i++){

		if(around_P[i][0]>=0 && around_P[i][1]>=0 && around_P[i][1]<30){
				
			if(placementmatrix[(around_P[i][0])][around_P[i][1]]=='E' || placementmatrix[(around_P[i][0])][around_P[i][1]]=='T'){
				displaymatrix[(around_P[i][0])][around_P[i][1]] = placementmatrix[(around_P[i][0])][around_P[i][1]];
			}
			else{
				displaymatrix[(around_P[i][0])][around_P[i][1]]=-80;
			}
		}				
	}						
}


void display(int Row,int Col,char displaymatrix[][30]){
	
	int i,j;
	
	for(i=0;i<Row;i++){
		for(j=0;j<Col;j++){
			
			printf("%c",displaymatrix[i][j]);
		}
		
		printf("\n");
	}
}
	

void displayGodMode(int Row,int Col,char displaymatrix[][30],char placementmatrix[][30]){
	
	int i,j;
	
	for(i=0;i<Row;i++){
		for(j=0;j<Col;j++){
			
			if(displaymatrix[i][j]==-78){
				
				if(placementmatrix[i][j]==' '){
					printf("%c",-80);
				}
				else{
					printf("%c",placementmatrix[i][j]);
				}
			}
			else{
				printf("%c",displaymatrix[i][j]);
			}
		}
		printf("\n");
	}
}

