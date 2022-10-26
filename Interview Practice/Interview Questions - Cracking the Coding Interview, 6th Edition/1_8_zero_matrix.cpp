#include <ctime>
#include <iostream>
using namespace std;


void display_matrix(int** matrix, int rows, int columns);
void generate_matrix(int seed, int** matrix, int rows, int columns);
void zero_matrix(int** matrix, int rows, int columns);

int main() {
	int rows = 9;
	int columns = 9;
	// int matrix[9][9] = {
	// 				{8, 4, 1, 9, 4, 3, 5, 5, 3},
	// 				{9, 1, 3, 4, 1, 0, 3, 4, 6},
	// 				{0, 0, 2, 4, 1, 5, 8, 5, 8}, 
	// 				{9, 9, 0, 1, 1, 0, 3, 8, 5}, 
	// 				{3, 1, 8, 5, 6, 5, 4, 4, 6},
	// 				{9, 4, 3, 1, 0, 1, 0, 1, 0},
	// 				{1, 8, 5, 9, 0, 3, 4, 5, 8},
	// 				{9, 0, 3, 9, 4, 2, 0, 1, 7},
	// 				{8, 1, 9, 3, 2, 4, 7, 4, 2}
	// 			};
	int** matrix;
	matrix = new int*[rows];

	// initialize the matrix
	for(int i = 0; i < rows; i++) {
		matrix[i] = new int[columns];
	}

	generate_matrix(-1, matrix, rows, columns);

	cout << "Initial matrix" << endl;
	display_matrix(matrix, rows, columns);
	cout << "**********************************************" << endl;

	zero_matrix(matrix, rows, columns);
	cout << "**********************************************" << endl;
	display_matrix(matrix, rows, columns);
}


// use the matrix itself as a data storage. 
// An element in the first row will be set to 0 if any value in that column is 0.
// Similarly, an element in the first column will be set to 0 if any element in 
//		that row is 0 
// @parameters
//		matrix = a 2d square matrix 
//		rows = the number of rows of the matrix
//		columns = the number of columns of the matrix
void zero_matrix(int** matrix, int rows, int columns) {
	// since matrix[0][0] is shared for both the first row and first column, we will set
	//		matrix[0][0] to 0 if there is any 0 down the first column.
	// We will use a single variable to set to 0 if any value is 0 along the first row. 
	int first_r_first_c = matrix[0][0];

	// traverse the matrix to find the 0s and reset the elements along the first row
	//		and first column
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < columns; c++) {
			// proceed if the current row is not 0
			if(r != 0) {				
				// if the element in row r and column c is 0, set the value in [0, c] and
				//		[r, 0] to 0
				if(matrix[r][c] == 0) {
					matrix[r][0] = 0;
					matrix[0][c] = 0;
				}
			} 
			else {
			 	// use first_r_first_c if there is any 0 along the first row.
			 	if(matrix[r][c] == 0) {
			 		first_r_first_c = 0;
			 	}
			}
		}
	}

	cout << first_r_first_c << endl;
	display_matrix(matrix, rows, columns);
	cout << "******************************************" << endl;


	// traverse the first column, starting from the second row
	// reset all the elements along row r to 0 if the given el matrix[r][0] is 0
	// use the rows set to 0 in the previous loop to
	//		set all the elements in corresponding columns to 0
	// start from the second row in the first column, and use the variable 
	//		first_r_first_c to deal with the first row.
	for(int r = 1; r < rows; r++) {
		// if we have 0 in the first element, set everything in that column to 0
		if(matrix[r][0] == 0) {
			// loop over all the columns
			for(int c = 0; c < columns; c++) {
				matrix[r][c] = 0;
			}
		}
	}    

	cout << "0 along the rows" << endl;
	display_matrix(matrix, rows, columns);
	cout << "******************************************" << endl;


	// traverse the first row 
	// reset all the elements down column c to 0 if the given el matrix[0][c] is 0
	for(int c = 0; c < columns; c++) {
		// if the element in the current column is 0, set the whole column to 0 
		if(matrix[0][c] == 0) {
			// loop through the entire column and set everything in that column to 0
			for(int r = 0; r < rows; r++) {
				matrix[r][c] = 0;
			}
		}
	}


	cout << "0 down the columns" << endl;
	display_matrix(matrix, rows, columns);
	cout << "******************************************" << endl;

	// if first_r_first_c = 0, reset all the values of first row to 0
	if(first_r_first_c == 0) {
		// traverse through the elements in the first row, and reset them to 0
		for(int c = 0; c < columns; c++) {
			matrix[0][c] = 0;
		}
	}
}



// randomly generate values for an NxN matrix
//		seed = an integer to be used as the seed. if -1, then use a random seed
//		matrix = a 2d square matrix to be generated
//		rows = the number of rows of the matrix
//		columns = the number of columns of the matrix
void generate_matrix(int seed, int** matrix, int rows, int columns) {
	// if rows <= 0 or cols <= 0, set it equal to 5 by default
	if(rows <= 0) {
		rows = 5;
	}

	if(columns <= 0) {
		columns = 5;
	}
	// use a random seed if the given seed = -1
	if(seed == -1) {
		srand(time(NULL));
	}
	else {
		srand(seed);
	}

	// instantiate the matrix
	for(int row = 0; row < rows; row++) {
		for(int col = 0; col < columns; col++) {
			matrix[row][col] = rand() % 10;
		}
	}
}

// a helper function to display the matrix
// @parameters:
//		matrix = a pointer to a pointer to an integer representing the matrix
//		rows = the number of rows of the matrix
//		columns = the number of columns of the matrix
void display_matrix(int** matrix, int rows, int columns) {
	for(int row = 0; row < rows; row++) {
		for(int col = 0; col < columns; col++) {
			cout << matrix[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
}