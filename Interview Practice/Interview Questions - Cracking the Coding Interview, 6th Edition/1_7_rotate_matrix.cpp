#include <iostream>
#include <ctime>
using namespace std;

void rotate_matrix(int** matrix, int N);

void display_matrix(int** matrix, int N);

void generate_matrix(int** matrix, int N);

int main() {
	int N = 9;

	int **matrix;
	matrix = new int*[N];

	// initialize the matrix
	for(int i = 0; i < N; i++) {
		matrix[i] = new int[N];
	}


	generate_matrix(matrix, N);

	// int matrix[9][9] = {
	// 					{8, 4, 1, 9, 4, 3, 5, 5, 3},
	// 					{9, 1, 3, 4, 1, 0, 3, 4, 6},
	// 					{0, 0, 2, 4, 1, 5, 8, 5, 8}, 
	// 					{9, 9, 0, 1, 1, 0, 3, 8, 5}, 
	// 					{3, 1, 8, 5, 6, 5, 4, 4, 6},
	// 					{9, 4, 3, 1, 0, 1, 0, 1, 0},
	// 					{1, 8, 5, 9, 0, 3, 4, 5, 8},
	// 					{9, 0, 3, 9, 4, 2, 0, 1, 7},
	// 					{8, 1, 9, 3, 2, 4, 7, 4, 2}
	// 				};

	display_matrix(matrix, 9);

	rotate_matrix(matrix, 9);

	return 0;
}


// randomly generate values for an NxN matrix
//		matrix = a 2d square matrix to be generated
//		N = the dimension of the matrix
void generate_matrix(int** matrix, int N) {
	srand(time(NULL));

	// instantiate the matrix
	for(int row = 0; row < N; row++) {
		for(int col = 0; col < N; col++) {
			matrix[row][col] = rand() % 100;
			while(matrix[row][col] < 10) {
				matrix[row][col] = rand() % 100;
			}
		}
	}
}

// NOTE:
// divide the matrix into a coordinate plane, with quadrants as follows:
// q1 = top left sub-square
// q2 = top right sub-square
// q3 = bottom right sub-square 
// q4 = bottom-left sub-square.
// (clockwise)

// We will only iterate over the elements in q1. So that is N^2/2 iterations, which
//		is O(N^2)

// The a's represent the only elements in the matrix that we need to traverse
//		We can derive the indices of the other elements by these values in q1 
// a a a a a 9 0 9 8
// a a a a a 9 0 1 4
// a a a a a 0 2 3 1
// a a a a a 1 4 4 9
// a a a a a 1 1 1 4
// 4 2 3 1 5 0 5 0 3
// 7 0 4 0 4 3 8 3 5
// 4 1 5 1 4 8 5 4 5
// 2 7 8 0 6 5 8 6 3


// a function to rotate a given matrix 90 degrees in place
// @parameters:
//		matrix = a 2d square matrix to be rotated 90 degrees
//		N = the dimension of the matrix
// @return:
// 		a 2d NxN array that is the 90 degrees rotated version of the given array
void rotate_matrix(int** matrix, int N) {
	// when N is even, max_col are: N/2 - 1
	// when N is odd (there is a middle row and middle column), then max_col are: N/2.
	// row_max = col_max-1 because when we are at col_max and rotate it to get the
	//		other quadrants, it will cover the col_max'th row.
	// row max/col_max is the largest index we will iterate through along the rows/cols
	//		of the matrix
	int row_max;
	int col_max;

	// N is even
	if(N % 2 == 0) {
		col_max = N / 2 + 1;
	}
	// N is odd
	else {
		col_max = N / 2;
	}

	row_max = col_max - 1;


	// pseudocode for finding the other indices for a given element. 
	// 	traverse through q1
	// 	q# represents the element in quadrant #
	//  q#_row is the index of the row of the element in quadrant #
	//  q#_col is the index of the column of the element in quadrant #
	// 	q1_row = row
	// 	q1_cor = col
		
	// 	q2_row = col
	// 	q2_col = N - row - 1

	// 	q3_row = q2_col
	// 	q3_col = N - q2_row - 1

	// 	q4_row = q3_col
	// 	q4_col = N - q3_row - 1
	int q1_row;
	int q1_col;

	int q2_row;
	int q2_col;

	int q3_row;
	int q3_col;

	int q4_row;
	int q4_col;


	// temporary storages for values in q1 through q4 to aid swapping
	int q1;
	int q2;
	int q3;
	int q4;


	// iterate through the elements of the matrix in the 1st quadrant only
	// The outer loop is for the rows
	for(int row = 0; row <= row_max; row++) {

		// The inner loop is for the columns
		for(int col = 0; col <= col_max; col++) {
			// use the pseufocode to find the row and column indices of the elements
			//		in the 4 quadrants. Note: the row and col are the indices for the
			//		elements in the 1st quadrant
			q1_row = row;
			q1_col = col;

			q2_row = q1_col;
			q2_col = N - q1_row - 1;

			q3_row = q2_col;
			q3_col = N - q2_row - 1;

			q4_row = q3_col;
			q4_col = N - q3_row - 1;

			// set the temporary variables for each quadrant
			q1 = matrix[q1_row][q1_col];
			q2 = matrix[q2_row][q2_col];
			q3 = matrix[q3_row][q3_col];
			q4 = matrix[q4_row][q4_col];

			// rotate the given values in the 4 quadrants
			matrix[q1_row][q1_col] = q4;
			matrix[q2_row][q2_col] = q1;
			matrix[q3_row][q3_col] = q2;
			matrix[q4_row][q4_col] = q3;
		}
	}

	// display the rotated matrix
	display_matrix(matrix, N);
}



// a helper function to display the matrix
void display_matrix(int** matrix, int N) {
	for(int row = 0; row < N; row++) {
		for(int col = 0; col < N; col++) {
			cout << matrix[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// 8 4 1 9 4 3 5 5
// 9 1 3 4 1 0 3 4
// 0 0 2 4 1 5 8 5
// 9 9 0 1 1 0 3 8
// 3 1 8 5 6 5 4 4
// 9 4 3 1 0 1 0 1
// 1 8 5 9 0 3 4 5
// 9 0 3 9 4 2 0 1

// 9 1 9 3 9 0 9 8
// 0 8 4 1 9 0 1 4
// 3 5 3 8 0 2 3 1
// 9 9 1 5 1 4 4 9
// 4 0 0 6 1 1 1 4
// 2 3 1 5 0 5 0 3
// 0 4 0 4 3 8 3 5
// 1 5 1 4 8 5 4 5

// !!! do the same with N being odd

// 8 4 1 9 4 3 5 5 3
// 9 1 3 4 1 0 3 4 6
// 0 0 2 4 1 5 8 5 8 
// 9 9 0 1 1 0 3 8 5 
// 3 1 8 5 6 5 4 4 6
// 9 4 3 1 0 1 0 1 0
// 1 8 5 9 0 3 4 5 8
// 9 0 3 9 4 2 0 1 7
// 8 1 9 3 2 4 7 4 2

// 8 9 1 9 3 9 0 9 8
// 1 0 8 4 1 9 0 1 4
// 9 3 5 3 8 0 2 3 1
// 3 9 9 1 5 1 4 4 9
// 2 4 0 0 6 1 1 1 4
// 4 2 3 1 5 0 5 0 3
// 7 0 4 0 4 3 8 3 5
// 4 1 5 1 4 8 5 4 5
// 2 7 8 0 6 5 8 6 3






