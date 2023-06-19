#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_BUFFER 5
#define BLOCK_LENGTH 8
#define PI 3.141592653589793
#define LIMIT 40
#define SCALE 320

void dataInput();
void dataOutput();
void dctMatrixGenerate(float* arr, int size);
void transposeMatrix(float* arr, float* out, int size);
void matrixProduct(float* arrA, float* arrB, float* output, int size);
void compress(float* arr, int lengthBuffer, int limit);
void prepareDataToInput(int* in, float* out, int lengthBuffer);
void prepareDataToOutput(float* in, int* out, int lengthBuffer);

void main() {
    int inputArr[BLOCK_LENGTH * BLOCK_LENGTH];
	int outputArr[BLOCK_LENGTH * BLOCK_LENGTH];
	
	int count = 0;
	float arr[BLOCK_LENGTH * BLOCK_LENGTH];
    float dctMatrix[BLOCK_LENGTH * BLOCK_LENGTH];
    float dctMatrixTrans[BLOCK_LENGTH * BLOCK_LENGTH];
    float outputTemp[BLOCK_LENGTH * BLOCK_LENGTH];
    float output[BLOCK_LENGTH * BLOCK_LENGTH];

    dctMatrixGenerate(dctMatrix, BLOCK_LENGTH);
    transposeMatrix(dctMatrix, dctMatrixTrans, BLOCK_LENGTH);

    while(count != SCALE * SCALE) {
        dataInput();
		
		prepareDataToInput(inputArr, arr, BLOCK_LENGTH * BLOCK_LENGTH);

        matrixProduct(dctMatrix, arr, outputTemp, BLOCK_LENGTH);
        matrixProduct(outputTemp, dctMatrixTrans, output, BLOCK_LENGTH);
        //compress image
        compress(output, BLOCK_LENGTH * BLOCK_LENGTH, LIMIT);
        //reverse
        matrixProduct(dctMatrixTrans, output, outputTemp, BLOCK_LENGTH);
        matrixProduct(outputTemp, dctMatrix, output, BLOCK_LENGTH);
		
		prepareDataToOutput(output, outputArr, BLOCK_LENGTH * BLOCK_LENGTH);

		dataOutput();

		count += BLOCK_LENGTH * BLOCK_LENGTH;
    }
}

void dataInput() {
	return;
}

void dataOutput() {
	return;
}

void prepareDataToInput(int* in, float* out, int lengthBuffer) {
	int i;
	for(i = 0; i < lengthBuffer; i++) {
		out[i] = 0 + in[i];
	}
}

void prepareDataToOutput(float* in, int* out, int lengthBuffer) {
	int i;
	for(i = 0; i < lengthBuffer; i++) {
		out[i] = (int)in[i];
	}
}


void dctMatrixGenerate(float* arr, int size) {
    int row;
    int col;
    for(row = 0; row < size; row++) {
        for(col = 0; col < size; col++) {
            if(row == 0) {
                arr[row * size + col] = 1 / sqrt(size);
                arr[row * size + col] *= cos((2 * col + 1) * row * PI / (2 * size));
            } else {
                arr[row * size + col] = sqrt(2.0 / size);
                arr[row * size + col] *= cos((2 * col + 1) * row * PI / (2 * size));
            }
        }
    }
}

void transposeMatrix(float* arr, float* out, int size) {
    int row;
    int col;
    for(row = 0; row < size; row++) {
        for(col = 0; col < size; col++) {
            out[col * size + row] = arr[row * size + col];
        }
    }
}

void matrixProduct(float* arrA, float* arrB, float* output, int size) {
    int row;
    int col;
    int k;
    for(row = 0; row < size; row++) {
        for(col = 0; col < size; col++) {
            output[row * size + col] = 0;
            for(k = 0; k < size; k++) {
                output[row * size + col] += arrA[row * size + k] * arrB[k * size + col];
            }
        }
    }
}

void compress(float* arr, int lengthBuffer, int limit) {
    int count;
    for(count = limit; count < lengthBuffer; count++) {
        arr[count] = 0;
    }
}