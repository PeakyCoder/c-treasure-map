#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


int findPath(int** mapMatrix, int** keyMatrix, int row, int col, int rowEdge, int colEdge, int keyValue, FILE* outputFile){
	
	int i, j, mode5;
	int result = 0;
	
	// Multiplying matrix
	for(i = row; i < row+keyValue; i++){
		for(j = col; j < col+keyValue; j++){
			result += (mapMatrix[i][j]*keyMatrix[i-row][j-col]); 
		}
	} 
	
	// take mode 5 to result
	mode5 = result % 5;
	
	// Recursive Part
	if(mode5 == 0){
		fprintf(outputFile, "%d,%d:%d\n", row+(keyValue/2), col+(keyValue/2), result);
		return 0;
	}
	else if(mode5 == 1){
		fprintf(outputFile, "%d,%d:%d\n", row+(keyValue/2), col+(keyValue/2), result);
		if(row == 0){
			findPath(mapMatrix, keyMatrix, row+keyValue, col, rowEdge, colEdge, keyValue, outputFile);	
		}
		else{
			findPath(mapMatrix, keyMatrix, row-keyValue, col, rowEdge, colEdge, keyValue, outputFile);	
		}
	}
	else if(mode5 == 2){
		fprintf(outputFile, "%d,%d:%d\n", row+(keyValue/2), col+(keyValue/2), result);
		if(row == rowEdge-keyValue){
			findPath(mapMatrix, keyMatrix, row-keyValue, col, rowEdge, colEdge, keyValue, outputFile);	
		}
		else{
			findPath(mapMatrix, keyMatrix, row+keyValue, col, rowEdge, colEdge, keyValue, outputFile);	
		}
	}
	else if(mode5 == 3){
		fprintf(outputFile, "%d,%d:%d\n", row+(keyValue/2), col+(keyValue/2), result);
		if(col == colEdge-keyValue){
			findPath(mapMatrix, keyMatrix, row, col-keyValue, rowEdge, colEdge, keyValue, outputFile);	
		}
		else{
			findPath(mapMatrix, keyMatrix, row, col+keyValue, rowEdge, colEdge, keyValue, outputFile);	
		}
	}
	else if(mode5 == 4){
		fprintf(outputFile, "%d,%d:%d\n", row+(keyValue/2), col+(keyValue/2), result);
		if(col == 0){
			findPath(mapMatrix, keyMatrix, row, col+keyValue, rowEdge, colEdge, keyValue, outputFile);	
		}
		else{
			findPath(mapMatrix, keyMatrix, row, col-keyValue, rowEdge, colEdge, keyValue, outputFile);	
		}
	}	

}


int main(int argc, char *argv[]){

	int i, j;
	int keyValue = atoi(argv[2]);
	
	// Find map size
	char* mapSize = argv[1];
	char* size = strtok(mapSize, "x");
	int rowSize = atoi(size);
	size = strtok(NULL, "x");
	int colSize = atoi(size);
	
	
	// Map Matrix
	int** map = (int**)malloc(rowSize * sizeof(int*));
	for(i=0; i<colSize; i++){
		*(map+i) = (int*)malloc(colSize * sizeof(int));
	}
	
	// Key Matrix
	int** key = (int**)malloc(keyValue * sizeof(int*));
	for(i=0; i<keyValue; i++){
		*(key+i) = (int*)malloc(keyValue * sizeof(int));
	}
	

	//Reading File
	FILE *mapFile, *keyFile, *outputFile;
	mapFile = fopen(argv[3], "r");
	keyFile = fopen(argv[4], "r");
 	outputFile = fopen(argv[5], "w");

	// Adding values to map matrix
	for(i=0; i<rowSize; i++){
		for(j=0; j<colSize; j++){
			if(!fscanf(mapFile, "%d", &map[i][j])){
				break;
			}

		}
	}
	
	// Adding values to key matrix
	for(i=0; i<keyValue; i++){
		for(j=0; j<keyValue; j++){
			if(!fscanf(keyFile, "%d", &key[i][j])){
				break;
			}

		}
	}

	// Call Recursive Function	
	findPath(map, key, 0, 0, rowSize, colSize, keyValue, outputFile);

	// Closing file in the end
	fclose(mapFile);
	fclose(keyFile);
	fclose(outputFile);
	
	// Free memory allocation
	free(map);
	free(key);

	return 0;
}


