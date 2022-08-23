#include <bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;

#define HORIZONTAL true
#define VERTICAL false

// declare the functions used in this program
long long getPlusSignCount(int, vector<int>, string);

void merge_lines(vector<int>& lines, vector<std::array<int, 2>>& endpoints);

void display_lines(vector<int> lines, vector<std::array<int, 2>> endpoints, bool is_horizontal);



int main(){
	int N = 10;
	
	//vector<int> L = {6, 3, 4, 5, 1, 6, 3, 3, 4};
	// string D = "ULDRULURD";

	// vector<int> L = {6, 4, 5, 6, 2, 4, 3, 3, 3, 3, 3, 2, 1, 7, 2, 2};
	// string D = "RULDRURULDLURRDL";


	// vector<int> L = {1, 1, 1, 1, 1, 1, 1, 1};
	// string D = "RDLUULDR";

	// vector<int> L = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 1};
	// string D = "RURDRDLULDRLURRD";
	
	// vector<int> L = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 9, 10};
	// string D = "RLRLRLRLRLRLRLRLR";

	vector<int> L = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 9, 10};
	string D = "UDUDUDUDUDUDUDUDU";


	getPlusSignCount(N, L, D);

	return 0;
}

long long getPlusSignCount(int N, vector<int> L, string D) {
	// keeps track of the running total of the number of pluses
	int number_of_pluses = 0;

	// keeps track of the coordinates of plus signs
	vector<std::array<int, 2>> plus_sign_coord;

	// keeps all the y-coordinates of horizontal lines
	vector<int> horizontal_lines;
	// the left and right (on x-axis) endpoints of horizontal lines
	vector<std::array<int, 2>> h_endpoints;

	// keeps all the x-coordinates of vertical lines
	vector<int> vertical_lines;
	// the top and bottom (on y-axis) endpoints of horizontal lines
	vector<std::array<int, 2>> v_endpoints;

	// keeps track of the current coordinate of the brush, [x, y]
	int current_coordinate[2] = {0, 0};

	// keeps track of the previous coordinate of the brush, [x, y], before moving it
	//		by L
	int previous_coordinate[2] = {0, 0};

	int counter = 0;

	// iterate over the line segments
	for(auto i = L.begin(); i != L.cend(); i++) {
		char dir = D.at(counter);

		previous_coordinate[0] = current_coordinate[0];
		previous_coordinate[1] = current_coordinate[1];

		switch(dir) {
			case 'L':
				// update the current cooridnate after moving the brush
				current_coordinate[0] -= *i;
				// add a horizontal line, i.e. its y-coordinate
				// !!! remove duplicates from horizontal_lines
				horizontal_lines.push_back(current_coordinate[1]);
				// add the two endpoints (left and right) of the newly drawn line to
				//		the h_endpoints
				h_endpoints.push_back({current_coordinate[0], previous_coordinate[0]});



				break;
			case 'R':
				current_coordinate[0] += *i;
				horizontal_lines.push_back(current_coordinate[1]);
				h_endpoints.push_back({previous_coordinate[0], current_coordinate[0]});
				break;
			case 'U':
				// update the current cooridnate after moving the brush
				current_coordinate[1] += *i;
				// add a vertical line, i.e. its x-coordinate
				// !!! remove duplicates from vertical_lines
				vertical_lines.push_back(current_coordinate[0]);
				// add the two endpoints (bottom and top) of the newly drawn line to
				//		the v_endpoints
				v_endpoints.push_back({previous_coordinate[1], current_coordinate[1]});

				break;
			case 'D':
				current_coordinate[1] -= *i;				
				vertical_lines.push_back(current_coordinate[0]);
				v_endpoints.push_back({current_coordinate[1], previous_coordinate[1]});
				break;
		}
		cout << D.at(counter) << " ";
		cout << endl;
		counter++;
	}


	// display horizontal and vertical lines
	display_lines(vertical_lines, v_endpoints, VERTICAL);
	display_lines(horizontal_lines, h_endpoints, HORIZONTAL);

	// merge lines
	merge_lines(horizontal_lines, h_endpoints);
	merge_lines(vertical_lines, v_endpoints);

	// display merged lines
	display_lines(vertical_lines, v_endpoints, VERTICAL);

	display_lines(horizontal_lines, h_endpoints, HORIZONTAL);

	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	// 								find pluses
	// if the given horizontal line has a line above/below it that is connected to it,
	//		then set top_exists/bottom_exists to true, respectively. 
	bool top_exists = false;
	bool bottom_exists = false;

	// for each horizontal line, iterate through all the vertical lines and determine
	//		if they form a plus sign
	// for (auto i = horizontal_lines.begin(); i != horizontal_lines.cend(); i++) {

	// } 


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//							merge lines
// merge the adjacent lines found in lines vector, using the endpoints vector.
//		remove the merged lines from the vectors. So this function modifies the original
//		parameters.
// @parameters:
//		vector references to lines and their endpoints
void merge_lines(vector<int>& lines, vector<std::array<int, 2>>& endpoints) {
	// keeps track of the index of the first (outer loop) horizontal line
	int ln_outer = 0;
	// keeps track of the index of the second (inner loop) horizontal line. starts at 1
	//		plus the outer index
	int ln_inner = ln_outer + 1;
	
	// if at least one merge took place, repead the iteration
	bool did_merge_happen = true;

	// use this value to replace the endpoints inside the inner while loop.
	bool did_merge_happen_inner = true;


	// store the left and right coordinate values of the line formed by merging the
	//		lines.
	int new_left_coord = 0;
	int new_right_coord = 0;

	auto ln_it = lines.begin();

	// iterate over the horizontal lines
	while (ln_it != lines.cend()) {
		did_merge_happen = false;

		// iterate over the subsequent horizontal lines to compare with the first 
		//		iteration's horizontal line
		//for(auto ln_it_2 = ln_it + 1; ln_it_2 != horizontal_lines.cend(); ln_it_2++) {
		auto ln_it_2 = ln_it + 1;
		while(ln_it_2 != lines.cend()) {
			did_merge_happen_inner = false;
			cout << *ln_it << " --- " << *ln_it_2 << endl;
			cout << "-----------------------------" << endl;
			// if the lines are on the same y-coordinate
			if (*ln_it == *ln_it_2) {
				// check if the lines should be merged
				// the following 2 if statements check if the outer loop line is to the
				//		right of the inner loop line.
				if(endpoints[ln_outer][0] >= endpoints[ln_inner][0]) {
					if(endpoints[ln_outer][0] <= endpoints[ln_inner][1]) {
						
						// if outer right coordinate is more than the inner right coordinate
						if(endpoints[ln_outer][1] > endpoints[ln_inner][1]) {
							// case 1:
							// 		___________
							//  __________
							// case 2:
							//			_________
							//	________
							cout << "******" << *ln_it << endl;
							new_left_coord = endpoints[ln_inner][0];
							new_right_coord = endpoints[ln_outer][1];
							did_merge_happen = true;
							did_merge_happen_inner = true;
						} else {
							// case 3:
							// 		___________
							//  __________________
							new_left_coord = endpoints[ln_inner][0];
							new_right_coord = endpoints[ln_inner][1];
							did_merge_happen = true;
							did_merge_happen_inner = true;
						}
					} else {
						// case -1:
						//				____________
						//	_______
						// don't merge
					}
				} else {
					if(endpoints[ln_outer][1] >= endpoints[ln_inner][0]) {
						new_left_coord = endpoints[ln_outer][0];
						if(endpoints[ln_outer][1] <= endpoints[ln_inner][1]){
							// case 4:
							//		___________
							//			___________
							// case 5:
							//		____________
							//					____________
							new_right_coord = endpoints[ln_inner][1];
							did_merge_happen = true;
							did_merge_happen_inner = true;
						} else {
							// case 6:
							//		________________
							//		 ________
							new_right_coord = endpoints[ln_outer][1];
							did_merge_happen = true;
							did_merge_happen_inner = true;
						}
					} else {
						// case -2:
						//	_________
						//				____________
						// don't merge
					}
				}
			}

			// merge the lines. 
			if(did_merge_happen_inner) {
				endpoints[ln_outer][0] = new_left_coord;
				endpoints[ln_outer][1] = new_right_coord;

				///////////////////////////////////////////////////////////////////////
				//				 remove already merged line
				lines.erase(lines.begin() + ln_inner);
				endpoints.erase(endpoints.begin() + ln_inner);

				// do not increment the index and the iterators for the inner lines as
				//		erasing an element from a vector automatically sets the iterator
				//		to the next element
			} else {		
				// increment the index of the inner horizontal line
				ln_inner++;

				// increment for the inner while loop			
				ln_it_2++;
			}
		}
		cout << "************************************" << endl;

		


		// if a merge took place for the outer line segment, go back and iterate over
		//		again
		if(did_merge_happen) {			
			// reset the index of the outer horizontal line
			ln_outer = 0;
			ln_inner = ln_outer + 1;
			ln_it = lines.begin();
		} else{		
			// increment the index of the outer horizontal line
			ln_outer++;
			ln_inner = ln_outer + 1;
			// increment for the inner while loop
			ln_it++;
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//									display lines (with endpoints)
// display the lines in the following format:
//	for horizontal lines:
//			y-axis: (left_endpoint, right_endpoint)
//  for vertical lines:
//			x-axis: (bottom_endpoint, top_endpoint)
// iterate over the vertical lines and display their y-axis and endpoints
void display_lines(vector<int> lines, vector<std::array<int, 2>> endpoints, bool is_horizontal) {
	if(is_horizontal) {
		cout << "********************************\n";
		cout << "Horizontal Lines: \n";
	} else {
		cout << "********************************\n";
		cout << "Vertical Lines: \n";
	}

	int row_counter = 0;

	for (auto ln_it = lines.begin(); ln_it != lines.cend(); ln_it++) {
		cout << *ln_it << ": (" << endpoints[row_counter][0] << "," << endpoints[row_counter][1] << ")";
		cout << endl;
		row_counter++;
	}	
}
