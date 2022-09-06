#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <random>
#include <chrono>
using namespace std;

#define HORIZONTAL true
#define VERTICAL false

// structures to represent horizontal and vertical lines.
//						horizontal lines --------------- vertical lines
//		coord =		 		y_coord 		 				coord
//		min_endpoint =		left_endpoint                   bottom_endpoint
//		max_endpoint = 		right_endpoint 					top_endpoint
struct line{
	int coord;
	int min_endpoint;
	int max_endpoint;
};

// declare the functions used in this program
long long getPlusSignCount(int, vector<int>, string);

long long getPlusSignCount2(int, vector<int>, string);

long long getPlusSignCount3(int, vector<int>, string);

void merge_lines(vector<int>& lines, vector<std::array<int, 2>>& endpoints);

void display_lines(vector<int> lines, vector<std::array<int, 2>> endpoints, bool is_horizontal);

int count_plus_signs(vector<int> h_lines, vector<int> v_lines, vector<std::array<int, 2>> h_endpoints, vector<std::array<int, 2>> v_endpoints);

string generate_directions(int number_of_moves);

char digit_to_dir_conv(int digit);

vector<int> generate_lengths(int number_of_moves, int max_move_size);

int* find_index(bool is_vertical, vector<int>& lines, int coord);

void insert_coord_and_endpoints(int index, int type, vector<int>& lines, vector<vector<std::array<int, 2>>>& endpoints, int coordinate, int* min_max_endpoints);




int main(){
	int N = 100;
	int L_i = 2;

	// string D;
	// vector<int> L;
	// L = generate_lengths(N, L_i);
	// D = generate_directions(N);
	// cout << D.size() << endl;;

	// vector<int> L = {6, 3, 4, 5, 1, 6, 3, 3, 4};
	// string D = "ULDRULURD";

	// vector<int> L = {6, 4, 5, 6, 2, 4, 3, 3, 3, 3, 3, 2, 1, 7, 2, 2};
	// string D = "RULDRURULDLURRDL";


	// vector<int> L = {1, 1, 1, 1, 1, 1, 1, 1};
	// string D = "RDLUULDR";

	// vector<int> L = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 1};
	// string D = "RURDRDLULDRLURRD";
	
	// vector<int> L = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 9, 10};
	// string D = "RLRLRLRLRLRLRLRLR";

	// vector<int> L = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 9, 10};
	// string D = "UDUDUDUDUDUDUDUDU";

	vector<int> L ={2,6,1,6,1,6,1,1,1,3,1,4,1,4,1,4,1,4,1,4,6,4,6,3,1,3,2,1,3,10,2,12,1,11,5};
	string D = "RULDLURRDLDRDLDRDLDRULDULLURDRULURD";

	// vector<int> L = {8, 4, 4, 4, 2, 8, 2, 4, 10, 2, 4, 1, 2};
	// string D = "RLULURDLRUDUR";

	// vector<int> L = {4,4,4,4,4,4,4,8,4,8,6,2,1,2,3,2};
	// string D = "RUDRULLRDLURDUDL";

	// vector<int> L = {1,2,3,1,2,1,2,1,1,1,2,1,1,2,1,2};
	// string D = "RURLULDLURURDULR";


	int coordinate;
	int* index_and_type;
	int index;
	int min_endpoint;
	int max_endpoint;
	int min_max_endpoints[2] = {0, 0};
	vector<int> lines;
	vector<vector<std::array<int, 2>>> endpoints;


	for(int i = 0; i < 10; i++) {
		cout << "Type a coordinate: ";
		cin >> coordinate;
		cout << endl;
		cout << "Type a min endpoint: ";
		cin >> min_endpoint;
		cout << "Type a max endpoint: ";
		cin >> max_endpoint;
		min_max_endpoints[0] = min_endpoint;
		min_max_endpoints[1] = max_endpoint;
		index_and_type = find_index(true, lines, coordinate);
		cout << index_and_type[0] << ", " << index_and_type[1] << endl;

		// insert_coord_and_endpoints(int index, 			int type,		 vector<int>& lines, vector<std::array<int, 2>>& endpoints, int coordinate, int* min_max_endpoints) {

		insert_coord_and_endpoints(index_and_type[0], index_and_type[1], lines, endpoints, coordinate, min_max_endpoints);
		// if(index_and_type[1] == -2) {
		// 	lines.insert(lines.begin(), coordinate);
		// 	cout << "0" << endl;
		// } else if (index_and_type[1] == -1) {
		// 	cout << "1" << endl;
		// 	lines.insert(lines.begin(), coordinate);
		// } else if(index_and_type[1] == 0) {
		// 	cout << "2" << endl;
		// 	lines.insert(lines.begin() + index_and_type[0], coordinate);
		// } else if(index_and_type[1] == 1) {
		// 	cout << "3" << endl;
		// 	lines.insert(lines.begin() + index_and_type[0], coordinate);
		// } else {
		// 	cout << "4" << endl;
		// 	lines.push_back(coordinate);
		// }

		int ix = 0;
		for(auto it = lines.begin(); it != lines.cend(); it++) {
			cout << *it << "     " << endpoints.at(ix).size();;
			for(auto inner_it = endpoints.at(ix).begin(); inner_it != endpoints.at(ix).cend(); inner_it++) {
				cout << "[" << (*inner_it)[0] << "," << (*inner_it)[1] << "],  ";
			}
			cout << endl;
			ix++;
		}
		cout << "**********************" << endl;
	}

	// lines.at(index) = 1;

	// getPlusSignCount3(N, L, D);

	// delete the dynamic array
	// delete [] array_of_lengths;
	return 0;
}

// inserts the coordinate at the appropriate index in a vector.
//		the index and type parameters are returned from find_index() function
//void insert_coord_and_endpoints(int index, int type, vector<int>& lines, vector<std::array<int, 2>>& endpoints, int coordinate, int* min_max_endpoints) {
void insert_coord_and_endpoints(int index, int type, vector<int>& lines, vector<vector<std::array<int, 2>>>& endpoints, int coordinate, int* min_max_endpoints) {
	// will encapsulate the endpoint array in case the line is not found.
	vector<std::array<int, 2>> new_entry; 

	if(type == -2) {
		lines.insert(lines.begin(), coordinate);
		new_entry.push_back({min_max_endpoints[0], min_max_endpoints[1]});
		endpoints.insert(endpoints.begin(), new_entry);
	} else if (type == -1) {
		lines.insert(lines.begin(), coordinate);
		new_entry.push_back({min_max_endpoints[0], min_max_endpoints[1]});
		endpoints.insert(endpoints.begin(), new_entry);
	} else if(type == 0) {
		lines.insert(lines.begin() + index, coordinate);
		new_entry.push_back({min_max_endpoints[0], min_max_endpoints[1]});
		endpoints.insert(endpoints.begin() + index, new_entry);
	} else if(type == 1) {
		// !!! this is an exact match. Merge this line with an already existing line if 
		//		possible		
		int min_endpoint;
		int max_endpoint;
		bool merge = false;

		// it holds the inner vector that corresponds to the given coordinate
	    auto it = endpoints.begin() + index;

		// cout << "size = " <<  (*it).size();
		// iterate over the inner vector holding the lines with the same coord.
	    for(auto inner_it = (*it).begin(); inner_it != (*it).cend(); inner_it++) {
	    	min_endpoint = (*inner_it)[0];
			max_endpoint = (*inner_it)[1];
			
			// cout << "*********************" << endl;
			// cout << min_max_endpoints[0] << ", " << min_max_endpoints[1] << endl;
			// cout << (*inner_it)[0] << ", " << (*inner_it)[1] << endl;
			// cout << "*********************" << endl;

			// !!! see if the lines overlap
			// min1/max1 = min_max_endpoints[0]/[1] refer to the new endpoints 
			// min2/max2 = min_/max_endpoint refer to the endpoints being iterated
			// case 1: min1 <= min 2 && max1 >= min2
			if(min_max_endpoints[0] <= min_endpoint && min_max_endpoints[1] >= min_endpoint) {
				merge = true;
				if(min_max_endpoints[1] > max_endpoint) {
					(*inner_it)[0] = min_max_endpoints[0];
					(*inner_it)[1] = min_max_endpoints[1];
				} else {
					(*inner_it)[0] = min_max_endpoints[0];
				}
			}
			// case 2: max1 >= max2 && min1 <= max2 
			else if(min_max_endpoints[1] >= max_endpoint && min_max_endpoints[0] <= max_endpoint) {
				merge = true;
				if(min_max_endpoints[0] < min_endpoint) {
					(*inner_it)[0] = min_max_endpoints[0];
					(*inner_it)[1] = min_max_endpoints[1];
				} else {
					(*inner_it)[1] = min_max_endpoints[1];
				}
			}
			// case 3: min1 >= min2 && max1 <= max2
			else if(min_max_endpoints[0] >= min_endpoint && min_max_endpoints[1] <= max_endpoint) {
				merge = true;
				// do not need to modify the endpoints
			}

	    }


	    // an iterator pointing to the inner vector that holds the endpoints for the 
	    //		given coord.
	    it = endpoints.begin() + index;
    	// do not insert unless merge does not happen
		if(!merge) {
		    cout << "no merge" << endl;
			// lines.insert(lines.begin() + index, coordinate);
			// new_entry.push_back({min_max_endpoints[0], min_max_endpoints[1]});

			(*it).push_back({min_max_endpoints[0], min_max_endpoints[1]});
			// endpoints.insert((endpoints.begin() + index).begin(), new_entry.back());	
		} else {
			// // reset merge to be used inside the loops below
			// merge = false;

			// merge the endpoints inside the inner vector one by one, as one merge 
			//		might connect multiple lines along the same coordinate.
			auto inner_it = (*it).begin();
			auto inner_it_2 = inner_it;
			while(inner_it != (*it).cend()) {
				inner_it_2 = inner_it + 1;
				while(inner_it_2 != (*it).cend()) {
					// cout << inner_it[0] << endl; 
					cout << "=================================================\n";
					cout << "[" << (*inner_it)[0] << ", " << (*inner_it)[1] << "]" << endl; 
					cout << "[" << (*inner_it_2)[0] << ", " << (*inner_it_2)[1] << "]" << endl; 
					cout << "=================================================\n";
					// case 1 (see notebook)
					if((*inner_it)[0] <= (*inner_it_2)[0] && (*inner_it)[1] >= (*inner_it_2)[0]) {
						if((*inner_it)[1] < (*inner_it_2)[1]) {
							// merge the lines
							(*inner_it)[1] = (*inner_it_2)[1];
						}

						// remove the 2nd inner line from the vector
						inner_it_2 = (*it).erase(inner_it_2);

						cout << "erase" << endl;
					// case 2 (see notebook)
					} else if((*inner_it)[1] >= (*inner_it_2)[1] && (*inner_it)[0] <= (*inner_it_2)[1]) {
						if((*inner_it)[0] > (*inner_it_2)[0]) {
							(*inner_it)[0] = (*inner_it_2)[0];
						}

						// remove the 2nd inner line from the vector
						inner_it_2 = (*it).erase(inner_it_2);

						cout << "erase" << endl;
					} else if((*inner_it)[0] >= (*inner_it_2)[0] && (*inner_it)[1] <= (*inner_it_2)[1]){ 
						if((*inner_it)[0] > (*inner_it_2)[0]) {
							(*inner_it)[0] = (*inner_it_2)[0];
						}
						if((*inner_it)[1] < (*inner_it_2)[1]) {
							(*inner_it)[1] = (*inner_it_2)[1];
						}

						// remove the 2nd inner line from the vector
						inner_it_2 = (*it).erase(inner_it_2);

						cout << "erase" << endl;
					}
					else {
						inner_it_2++;
					}
				}
				inner_it++;
			}
		}

	} else {
		lines.push_back(coordinate);
		new_entry.push_back({min_max_endpoints[0], min_max_endpoints[1]});
		endpoints.push_back(new_entry);
	}
}

// // inserts the coordinate at the appropriate index in a vector.
// //		the index and type parameters are returned from find_index() function
// void insert_endpoints(int index, int type, vector<int>& endpoints, int* endpoints) {
// 	if(type == -2) {
// 		lines.insert(lines.begin(), coordinate);
// 		cout << "0" << endl;
// 	} else if (type == -1) {
// 		cout << "1" << endl;
// 		lines.insert(lines.begin(), coordinate);
// 	} else if(type == 0) {
// 		cout << "2" << endl;
// 		lines.insert(lines.begin() + index, coordinate);
// 	} else if(type == 1) {
// 		cout << "3" << endl;
// 		lines.insert(lines.begin() + index, coordinate);
// 	} else {
// 		cout << "4" << endl;
// 		lines.push_back(coordinate);
// 	}
// }

long long getPlusSignCount3(int N, vector<int> L, string D) {
	// keeps track of the running total of the number of pluses
	int number_of_pluses = 0;

	// keeps track of the current coordinate of the brush, [x, y]
	int current_coordinate[2] = {0, 0};

	// keeps track of the previous coordinate of the brush, [x, y], before moving it
	//		by L
	int previous_coordinate[2] = {0, 0};


	// keeps all the y-coordinates of horizontal lines
	vector<int> horizontal_lines;
	// the left and right (on x-axis) endpoints of horizontal lines
	vector<vector<std::array<int, 2>>> h_endpoints;

	// keeps all the x-coordinates of vertical lines
	vector<int> vertical_lines;
	// the top and bottom (on y-axis) endpoints of horizontal lines
	vector<vector<std::array<int, 2>>> v_endpoints;

	// count the index to be used to access elements of D while iterating over the 
	//		elements of L
	int  index = 0;

	// stores the direction of the move
	char direction;

	// keep track of the previous direction.
	char previous_direction;

	// added for readability
	int left_endpoint = 0;
	int right_endpoint = 0;
	int top_endpoint = 0;
	int bottom_endpoint = 0;

	// will hold the given min and max endpoints
	int min_max_endpoints[2] = {0, 0};

	// will hold the array returned by find_index function
	int* index_and_type;

	for(auto it = L.begin(); it != L.cend(); it++) {
		direction = D.at(index);

		previous_coordinate[0] = current_coordinate[0];
		previous_coordinate[1] = current_coordinate[1];

		switch(direction) {
			case 'L':
				// update the current cooridnate after moving the brush
				current_coordinate[0] -= *it;

					
				// set the variables to be used later
				left_endpoint = current_coordinate[0];
				right_endpoint = previous_coordinate[0];

				if(current_coordinate[1] == 5) {
					cout << left_endpoint << ", " << right_endpoint << endl;
				}

				// if the previous direction was along the same line, then
				//		merge it with this line
				if (previous_direction == 'L' || previous_direction == 'R') {
					// update the left endpoint of the merged line if it is less than
					//		the left endpoint of the previous line.
					if(h_endpoints.back().back()[0] > left_endpoint) {
						h_endpoints.back().back()[0] = left_endpoint;
					}
				} else {
					// find the index to insert the new line at.


					min_max_endpoints[0] = left_endpoint;
					min_max_endpoints[1] = right_endpoint;
					index_and_type = find_index(true, horizontal_lines, current_coordinate[1]);

					insert_coord_and_endpoints(index_and_type[0], index_and_type[1], horizontal_lines, h_endpoints, current_coordinate[1], min_max_endpoints);
				
					// // add a horizontal line, i.e. its y-coordinate
					// // !!! remove duplicates from horizontal_lines
					// horizontal_lines.push_back(current_coordinate[1]);

					// // add the two endpoints (left and right) of the newly drawn line to
					// //		the h_endpoints
					// h_endpoints.push_back({left_endpoint, right_endpoint});					
				}

				break;
			case 'R':
				current_coordinate[0] += *it;

				left_endpoint = previous_coordinate[0];
				right_endpoint = current_coordinate[0];


				if(current_coordinate[1] == 5) {
					cout << left_endpoint << ", " << right_endpoint << endl;
				}

				// if the most recent line is identical to the previous line.
				if(previous_direction == 'L' || previous_direction == 'R') {
					// check if the new right_endpoint is larger than the previous right
					//		endpoint 
					if(h_endpoints.back().back()[1] < right_endpoint) {
						h_endpoints.back().back()[1] = right_endpoint;
					}
				} else {

					min_max_endpoints[0] = left_endpoint;
					min_max_endpoints[1] = right_endpoint;
					index_and_type = find_index(true, horizontal_lines, current_coordinate[1]);

					insert_coord_and_endpoints(index_and_type[0], index_and_type[1], horizontal_lines, h_endpoints, current_coordinate[1], min_max_endpoints);

					// horizontal_lines.push_back(current_coordinate[1]);
					// h_endpoints.push_back({left_endpoint, right_endpoint});
				}

				break;
			case 'U':
				// update the current cooridnate after moving the brush
				current_coordinate[1] += *it;

				top_endpoint = current_coordinate[1];
				bottom_endpoint = previous_coordinate[1];
		
				// if the previous direction was along the same line, then
				//		merge it with this line
				if(previous_direction == 'U' || previous_direction == 'D') {
					// update the top endpoint of the previous line, if it is less than
					//		the new top endpoint
					if(v_endpoints.back().back()[1] < top_endpoint) {
						v_endpoints.back().back()[1] = top_endpoint;
					}
				} else {

					min_max_endpoints[0] = bottom_endpoint;
					min_max_endpoints[1] = top_endpoint;
					index_and_type = find_index(true, vertical_lines, current_coordinate[0]);

					insert_coord_and_endpoints(index_and_type[0], index_and_type[1], vertical_lines, v_endpoints, current_coordinate[0], min_max_endpoints);					
					// // add the two endpoints (bottom and top) of the newly drawn line to
					// //		the v_endpoints
					// v_endpoints.push_back({bottom_endpoint, top_endpoint});

					// // add a vertical line, i.e. its x-coordinate
					// // !!! remove duplicates from vertical_lines
					// vertical_lines.push_back(current_coordinate[0]);					
				}


				break;
			case 'D':
				current_coordinate[1] -= *it;				


				top_endpoint = previous_coordinate[1];
				bottom_endpoint = current_coordinate[1];

				// if the previous direction was along the same line, then
				//		merge it with this line
				if(previous_direction == 'U' || previous_direction == 'D') {
					// update the bottom endpoint of the previous line, if it is greater
					//		than the new bottom endpoint
					if(v_endpoints.back().back()[0] > bottom_endpoint) {
						v_endpoints.back().back()[0] = bottom_endpoint;
					}
				} else {
					min_max_endpoints[0] = bottom_endpoint;
					min_max_endpoints[1] = top_endpoint;
					index_and_type = find_index(true, vertical_lines, current_coordinate[0]);

					insert_coord_and_endpoints(index_and_type[0], index_and_type[1], vertical_lines, v_endpoints, current_coordinate[0], min_max_endpoints);	

					// v_endpoints.push_back({bottom_endpoint, top_endpoint});
					// vertical_lines.push_back(current_coordinate[0]);
				}

				break;
		}


		previous_direction = direction;
		index++;
		int ix = 0;
		for(auto it = horizontal_lines.begin(); it != horizontal_lines.cend(); it++) {
			cout << *it << "     ";
			for(auto inner_it = h_endpoints.at(ix).begin(); inner_it != h_endpoints.at(ix).cend(); inner_it++) {
				cout << "[" << (*inner_it)[0] << "," << (*inner_it)[1] << "],  ";
			}
			cout << endl;
			ix++;
		}
		cout << "**********************" << endl;
	}

	// index = 0;
	// cout << "**********************";

	// for(auto it = horizontal_lines.begin(); it != horizontal_lines.cend(); it++) {
	// 	cout << *it << endl;
	// 	for(auto inner_it = h_endpoints.at(index).begin(); inner_it != h_endpoints.at(index).cend(); inner_it++) {
	// 		cout << ": [" << (*inner_it)[0] << "," << (*inner_it)[1] << "],  ";
	// 	}
	// 	cout << endl;
	// 	index++;
	// }
	// cout << endl;

	// index = 0;
	// for(auto it = vertical_lines.begin(); it != vertical_lines.cend(); it++) {
	// 	cout << *it << ": [" << v_endpoints.at(index)[0] << "," << v_endpoints.at(index)[1] << "]" << endl;
	// 	index++;
	// }
}


// finds the index of a sorted vector based on the coordinate (coord) of the line.
// @parameters:
//		lines = either a vector of horizontal or vertical lines, that hold the structure
//			horizontal_line or vertical_line, respectively.
//		coord = either the y_coord or the x_coord of the line represented by the vector
//			lines.
//	@return
//		a 2-element array containing:
//		current_index = the index at which the vector holds a line with the same coord. 
//		exact_index_found:
//		0 = If that line does not exist, and the current_index represents an int between 
//			the left and right neighboring indices. 
//		1 = if the coord was found, and current_index represents the exact index where
//			the coord is found
//		-1 = coord is not found, and courd < all the other coords in the vector. So it
//			should be inserted at the front of the vector.
//		2 =  coord is not found, and coord > all the other coords in the vector. So it
//			should be inserted at the back of the vector.
//		-2 = when the vector is empty.
//	Note: we assume the lines<> vector is already sorted by either y_coord or
// 		or x_coord, for horizontal or vertical lines, respectively. 
int* find_index(bool is_vertical, vector<int>& lines, int coord) {
	int size_of_vector = lines.size();

	// hold the low and high indices, which are used to split the vector, speeding up
	//		the search. 
	int low = 0;
	int high = size_of_vector - 1;

	// we start by splitting the vector and checking the middle element
	int current_index = (low + high)/2;

	int current_coord;

	if(size_of_vector != 0) {
		// the value of the x_coord/y_coord of the vertical/horizontal line for the current
		//		vector element (line) being observer.
		current_coord = lines.at(current_index);
	}
		
	// true if the index is found, whether the index points to the line with the exact
	//		coord or to a position in between two other indices.
	// used to terminate the while loop that searches for the index.
	bool index_found = false;

	// true if a line with the same coord is found. false otherwise.
	int exact_index_found;


	static int return_arr[2] = {0, 0};
	
	// search based on coord, then on min_endpoint.
	while(!index_found) {
		// if the vector is empty, return 0
		if(size_of_vector == 0) {
			return_arr[0] = 0;
			return_arr[1] = -2;
			return return_arr;
		} else {
			// sorting by the coord
			if(current_coord < coord) {
				// the coord at the current index is < the given coord. shift the index
				//		to the right
				low = current_index + 1;
				if(low > high) {
					// to get out of the loop
					index_found = true;

				
					// set the current_index to be the index of low 
					current_index = low;
					
					// if the coord is larger than all the other coords in the vector
					if(low >= size_of_vector) {							
						// set the value of the 2nd element of the return array.
						// means the coord should be pushed at the back of the vector.
						exact_index_found = 2;
						
					} else {
						// if the coord is in between two coords in the vector.
						exact_index_found = 0;
					}

				} else {
					// update the current index
					current_index = (low + high)/2;
					current_coord = lines.at(current_index);
				}
			} else if(current_coord > coord) {
				// the coord at the current index is > the given coord. So divide the
				//		vector further, shifting the index to the left, between the
				//		low and the current_index. the latter becomes the high.
				high = current_index - 1;

				if(high < low) {
					// to get out of the loop
					index_found = true;

					if(high < 0) {
						// means the coord should be pushed at the front of the vector.
						exact_index_found = -1;
						// set the current_index to be the index of the first element in the
						//		vector.
						current_index = 0;						
					} else {
						// if the coord is in between two coords in the vector
						current_index = low;
						exact_index_found = 0;
					}

				} else {
					// update the current index
					current_index = (low + high)/2;
					current_coord = lines.at(current_index);
				}
			} else {
				// found a line with the same coordinate
				index_found = true;
				exact_index_found = 1;
			}
		}
	}

	return_arr[0] = current_index;
	return_arr[1] = exact_index_found;
	return return_arr;
}
// look for 4
	// {0, 3, 6}
 // 	 ^  ^  ^
 // 	 	   ^
 // 	 	   ^
 // 	 	   ^

 // 	 	^  ^
 // 	 	h  l 		high > low, return low  		
// look for 2
	// {0, 3, 6}
 // 	 ^  ^  ^
 // 	 ^
 // 	 ^
 // 	 ^

 // 	 ^  ^	
 // 	 h  l 			low > high, return low 
// look for -1
//  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
//   ^			  ^	  			 ^
//   ^  ^     ^	 
//   ^   
// ^ ^		high < low			return high (-1) (high > low), -1
// ________________________________________________
// look for 10
//  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
//   ^           ^              ^    4 < 10
//                  ^     ^     ^    7 < 10
//                           ^  ^    current_index = 8     8 < 10
//                           ^

//                           	 ^
//                           	 ^
//                           	 ^	
//                           	   	    current_index = 9 = low = high    9 < 10
//                           	 ^ ^ 	return low (10) (low > high), 2

// ________________________________________________
// look for 3.5
//  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
//   ^           ^              ^
//   ^	^     ^
//         ^  ^
//         ^						current_index = 2 = low
        
//            ^
//            ^
//            ^
//            						current_index = 3 = low = high 
//            ^ ^					return low (4), 0
//			  h l
// ________________________________________________
// look for 4.5
//  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
//   ^           ^              ^
//                  ^     ^     ^

//                  ^  ^
//                  ^

//               ^  ^				current_index = 4 = high < low (5), 
//               h  l				return low (4), 0
// ________________________________________________
// look for 0.5
//  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
//   ^           ^              ^		current_index = 4, 4 > 0.5
//   ^  ^     ^						current_index = 1, 1 > 0.5

//   ^
//   ^
//   ^									current_index = 0, 0 < 0.5

//   ^
//      ^								low = 1 > 0 = high
//      								return low, 0
// sorting by the min_endpoint
// !!! the endpoints should be compared in a different fashion, because
//		merging lines do not have to have the same min endpoints.
//	!!! maybe not. the idea above is not true. We just have to insert
//		the given line at an index so that its min endpoint will be
//		in between the min endpoints of its next and previous neighbors.
//		So instead of looking for an equality of min endpoints, we must
//		find two consecutive lines, the earlier of which has a 
//		min_endpoint less than the min_endpoint of the given line, and the
//		later of which has a min_endpoint greater than the min_endpoint of
//		the given endpoint. 
int find_endpoint_index() {

}

long long getPlusSignCount2(int N, vector<int> L, string D) {
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

	// count the index to be used to access elements of D while iterating over the 
	//		elements of L
	int  index = 0;

	// index for iterating over the horizontal lines and their endpoints.
	int h_index = 0;

	// index for iterating over vertical lines and their endpoints.
	int v_index;


	// stores the direction of the move
	char direction;

	// keep track of the previous direction.
	char previous_direction;

	// added for readability
	int left_endpoint = 0;
	int right_endpoint = 0;
	int top_endpoint = 0;
	int bottom_endpoint = 0;

	// stores a pending plus sign, like the one shown below
	// case 1: half_plus
	//			1.1)
	//						|
	//						|
	//			____________
	//  	or  1.2)
	//			____________
	//						| 
	//						|
	//	 	or  1.3)
	//			|
	//			|
	//			 ___________
	//		or 	1.4)
	//			 ___________
	//			|
	//			|
	//
	//	case 2: three_quarter_plus
	//			2.1)
	//				|
	//				|
	//		________
	//				|
	//				|
	//		or 2.2)
	//				|
	//				|
	//				 _______
	//				|
	//				|
	//		or 2.3)
	//				|
	//				|
	//				|
	//				|
	//		________________
	//		or 2.4)
	//		________________
	//				|
	//				|
	//				|
	//				|
	//	case 3:  plus
	//				|
	//				|
	//				|
	//		________________
	//				|
	//				|
	//				|
	// vector<std::array<int, 2>> pending_1;

	// these vectors store the coordinates of partial pluses of type 1.1 - 2.4
	//		as defined above.
	vector<std::array<int, 2>> type_1_1;
	vector<std::array<int, 2>> type_1_2;
	vector<std::array<int, 2>> type_1_3;
	vector<std::array<int, 2>> type_1_4;
	vector<std::array<int, 2>> type_2_1;
	vector<std::array<int, 2>> type_2_2;
	vector<std::array<int, 2>> type_2_3;
	vector<std::array<int, 2>> type_2_4;

	for(auto it = L.begin(); it != L.cend(); it++) {
		direction = D.at(index);

		previous_coordinate[0] = current_coordinate[0];
		previous_coordinate[1] = current_coordinate[1];

		switch(direction) {
			case 'L':
				// update the current cooridnate after moving the brush
				current_coordinate[0] -= *it;

					
				// set the variables to be used later
				left_endpoint = current_coordinate[0];
				right_endpoint = previous_coordinate[0];

				// if the previous direction was along the same line, then
				//		merge it with this line
				if (previous_direction == 'L' || previous_direction == 'R') {
					// update the left endpoint of the merged line if it is less than
					//		the left endpoint of the previous line.
					if(h_endpoints.back()[0] > left_endpoint) {
						h_endpoints.back()[0] = left_endpoint;
					}
				} else {
					// add a horizontal line, i.e. its y-coordinate
					// !!! remove duplicates from horizontal_lines
					horizontal_lines.push_back(current_coordinate[1]);

					// add the two endpoints (left and right) of the newly drawn line to
					//		the h_endpoints
					h_endpoints.push_back({left_endpoint, right_endpoint});					
				}

				break;
			case 'R':
				current_coordinate[0] += *it;

				left_endpoint = previous_coordinate[0];
				right_endpoint = current_coordinate[0];

				// if the most recent line is identical to the previous line.
				if(previous_direction == 'L' || previous_direction == 'R') {
					// check if the new right_endpoint is larger than the previous right
					//		endpoint 
					if(h_endpoints.back()[1] < right_endpoint) {
						h_endpoints.back()[1] = right_endpoint;
					}
				} else {
					horizontal_lines.push_back(current_coordinate[1]);
					h_endpoints.push_back({left_endpoint, right_endpoint});
				}

				break;
			case 'U':
				// update the current cooridnate after moving the brush
				current_coordinate[1] += *it;

				top_endpoint = current_coordinate[1];
				bottom_endpoint = previous_coordinate[1];
		
				// if the previous direction was along the same line, then
				//		merge it with this line
				if(previous_direction == 'U' || previous_direction == 'D') {
					// update the top endpoint of the previous line, if it is less than
					//		the new top endpoint
					if(v_endpoints.back()[1] < top_endpoint) {
						v_endpoints.back()[1] = top_endpoint;
					}
				} else {
					// add the two endpoints (bottom and top) of the newly drawn line to
					//		the v_endpoints
					v_endpoints.push_back({bottom_endpoint, top_endpoint});

					// add a vertical line, i.e. its x-coordinate
					// !!! remove duplicates from vertical_lines
					vertical_lines.push_back(current_coordinate[0]);					
				}


				break;
			case 'D':
				current_coordinate[1] -= *it;				


				top_endpoint = previous_coordinate[1];
				bottom_endpoint = current_coordinate[1];

				// if the previous direction was along the same line, then
				//		merge it with this line
				if(previous_direction == 'U' || previous_direction == 'D') {
					// update the bottom endpoint of the previous line, if it is greater
					//		than the new bottom endpoint
					if(v_endpoints.back()[0] > bottom_endpoint) {
						v_endpoints.back()[0] = bottom_endpoint;
					}
				} else {
					v_endpoints.push_back({bottom_endpoint, top_endpoint});
					vertical_lines.push_back(current_coordinate[0]);
				}

				break;
		}




		// if movement is sideways, iterate over the vertical lines and look for 
		//		crossings (pluses)
		if (direction == 'L' || direction == 'R') {
			// cout << "(" << current_coordinate[0] << "," << current_coordinate[1] << ")" << endl;

			v_index = 0;

			// iterate over the vertical lines
			for(auto x_coord_it_v = vertical_lines.begin(); x_coord_it_v != vertical_lines.cend(); x_coord_it_v++) {
				// Note: current_coordinate[1] == the y_coord of the h_line
				if(*x_coord_it_v > left_endpoint && *x_coord_it_v < right_endpoint) {
					if(v_endpoints.at(v_index)[0] < current_coordinate[1] && v_endpoints.at(v_index)[1] > current_coordinate[1]) {
						// case 3
						// we found a plus sign. increment the running total of plus signs
						number_of_pluses++;
						cout << "plus at: ("; 
					} else if (v_endpoints.at(v_index)[0] == current_coordinate[1]) {
						// case 2.3
						cout << "case 2.3 at (";
					} else if(v_endpoints.at(v_index)[1] == current_coordinate[1]) {
						// cases 2.4
						cout << "case 2.4 at (";
					}
				} else if(*x_coord_it_v == left_endpoint || *x_coord_it_v == right_endpoint) {
					// a partial plus sign is being formed. 
					if(v_endpoints.at(v_index)[0] < current_coordinate[1] && v_endpoints.at(v_index)[1] > current_coordinate[1]) {
						// cases 2.1 || 2.2
						if(*x_coord_it_v == right_endpoint) {
							// case 2.1
							cout << "case 2.1 at (";
						} else {
							// case 2.2
							cout << "case 2.2 at (";
						}
					} else if(v_endpoints.at(v_index)[0] == current_coordinate[1] || v_endpoints.at(v_index)[1] == current_coordinate[1]) {
						// cases 1.1 || 1.2 || 1.3 || 1.4
						if(v_endpoints.at(v_index)[0] == current_coordinate[1]) {
							if(*x_coord_it_v == right_endpoint) {
								//case 1.1
								cout << "case 1.1 at (";
							} else {
								// case 1.3
								cout << "case 1.3 at (";
							}
						} else if(v_endpoints.at(v_index)[1] == current_coordinate[1]) {
							if(*x_coord_it_v == right_endpoint) {
								// case 1.2
								cout << "case 1.2 at (";
							} else {
								// case 1.4
								cout << "case 1.4 at (";
							}
						}
					}
				}

				cout  << *x_coord_it_v << "," << current_coordinate[1] << ")" << endl;

				// increment the v_index
				v_index++;

			}

		}
		// else if the movement is up and down, iterate over the horizontal lines looking
		// 		for crossings (pluses)
		// dir == 'U' || dir == 'D'
		else {
			h_index = 0;

			// iterate over the horizontal lines
			for(auto y_coord_it_h = horizontal_lines.begin(); y_coord_it_h != horizontal_lines.cend(); y_coord_it_h++) {
				// Note: current_coordinate[0] == the x_coord of the v_line

				// for readability
				left_endpoint = h_endpoints.at(h_index)[0];
				right_endpoint = h_endpoints.at(h_index)[1];

				if(*y_coord_it_h > bottom_endpoint && *y_coord_it_h < top_endpoint) {
					if(left_endpoint < current_coordinate[0] && right_endpoint > current_coordinate[0]) {
						// case 3
						// we found a plus sign. increment the running total of plus signs
						number_of_pluses++;
						cout << "plus at: ("; 
					} else if (right_endpoint == current_coordinate[0]) {
						// case 2.1
						cout << "case 2.1 at (";
					} else if(left_endpoint == current_coordinate[0]) {
						// cases 2.2
						cout << "case 2.2 at (";
					}
				} else if(*y_coord_it_h == bottom_endpoint || *y_coord_it_h == top_endpoint) {
					// a partial plus sign is being formed. 
					if(left_endpoint < current_coordinate[0] && right_endpoint > current_coordinate[0]) {
						// cases 2.3 || 2.4
						if(*y_coord_it_h == bottom_endpoint) {
							// case 2.3
							cout << "case 2.3 at (";
						} else {
							// case 2.4
							cout << "case 2.4 at (";
						}
					} else if(left_endpoint == current_coordinate[0] || right_endpoint == current_coordinate[1]) {
						// cases 1.1 || 1.2 || 1.3 || 1.4
						if(right_endpoint == current_coordinate[0]) {
							if(*y_coord_it_h == bottom_endpoint) {
								//case 1.1
								cout << "case 1.1 at (";
							} else {
								// case 1.2
								cout << "case 1.2 at (";
							}
						} else if(left_endpoint == current_coordinate[0]) {
							if(*y_coord_it_h == bottom_endpoint) {
								// case 1.3
								cout << "case 1.3 at (";
							} else {
								// case 1.4
								cout << "case 1.4 at (";
							}
						}
					}
				}

				cout << current_coordinate[0] << "," << *y_coord_it_h << ")" << endl;

				// increment the v_index
				v_index++;

			}
		}

		previous_direction = direction;
		index++;
	}
	cout << endl << endl;

	cout << "***************************************************************";
	cout << horizontal_lines.size() + vertical_lines.size() << endl;
	int temp_index = 0;
	// for(auto it = horizontal_lines.begin(); it != horizontal_lines.cend(); it++) {
	// 	cout << *it << ": (" << h_endpoints.at(temp_index)[0] << "," << h_endpoints.at(temp_index)[1] << ")" << endl;
	// 	temp_index++;
	// }
	// cout << "***************************************************************";
	// temp_index = 0;
	// for(auto it = vertical_lines.begin(); it != vertical_lines.cend(); it++) {
	// 	cout << *it << ": (" << v_endpoints.at(temp_index)[0] << "," << v_endpoints.at(temp_index)[1] << ")" << endl;
	// 	temp_index++;
	// }
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

	char dir;

	// iterate over the line segments
	for(auto i = L.begin(); i != L.cend(); i++) {
		dir = D.at(counter);

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
		// cout << D.at(counter) << " ";
		// cout << endl;
		counter++;
	}


	// uncomment the following lines
	// // display horizontal and vertical lines
	// display_lines(vertical_lines, v_endpoints, VERTICAL);
	// display_lines(horizontal_lines, h_endpoints, HORIZONTAL);

	// // merge lines
	// merge_lines(horizontal_lines, h_endpoints);
	// merge_lines(vertical_lines, v_endpoints);

	// // display merged lines
	// display_lines(vertical_lines, v_endpoints, VERTICAL);
	// display_lines(horizontal_lines, h_endpoints, HORIZONTAL);



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

	int count = count_plus_signs(horizontal_lines, vertical_lines, h_endpoints, v_endpoints);
	cout << "==================================" << endl; 
	cout << "count = " << count;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//							function for merge lines
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
			// cout << *ln_it << " --- " << *ln_it_2 << endl;
			// cout << "-----------------------------" << endl;
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
							// cout << "******" << *ln_it << endl;
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

// !!! first of all, merge consecutive moves if they have the same direction
//		e.g. if D contains "RRUDLL", then the first two Rs and the last two Ls can be
//		merged without iterating over the entire vector.

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//							function for displaying lines (with endpoints)
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


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//						function for counting plus signs
// @return the number of plus signs present on the graph represented by the parameters
//		lines and endpoints.
// @parameters
//		h_lines = a vector containing the y_axis of the horizontal lines
//		v_lines = a vector containing the x_axis of the vertical lines
//		h_endpoints = a vector of 2-element arrays containing the left and right endpoints 
//			of the horizontal lines represented by h_lines
//		v_endpoints = a vector of 2-element arrays containing the bottom and top endpoints
//			of the vertical lines represented by v_lines
int count_plus_signs(vector<int> h_lines, vector<int> v_lines, vector<std::array<int, 2>> h_endpoints, vector<std::array<int, 2>> v_endpoints) {
	// initialize outer and inner (horizontal and vertical, respectively) line iterators
	auto h_ln_it = h_lines.begin();
	auto v_ln_it = v_lines.begin();

	// initialize counters for endpoints
	int h_index = 0;
	int v_index = 0;

	// declare left and right endpoints for the horizontal lines to be used in the loops.
	int h_left_endpoint;
	int h_right_endpoint;


	// declare left and right endpoints for the vertical lines to be used in the loops.
	int v_bottom_endpoint;
	int v_top_endpoint;

	// declare the y_axis varialbe for horizontal lines
	int h_y_axis;

	// declare the x_axis varialbe for vertical lines
	int v_x_axis;

	// running total of the number of plus signs found
	int total_plus_signs = 0;



	// iterate over the horizontal lines
	while(h_ln_it != h_lines.cend()) {
		v_ln_it = v_lines.begin();
		v_index = 0;

		// set the left and right endpoint variables using the horizontal endpoint vector
		//		for readability
		h_left_endpoint = h_endpoints[h_index][0];
		h_right_endpoint = h_endpoints[h_index][1];

		// set the y-axis of the horizontal line (to make the if statements more
		//		readable)
		h_y_axis = *h_ln_it;

		while(v_ln_it != v_lines.cend()) {
			// set the bottom and top endpoint variables using the vertical endpoint vector
			//		for readability			
			v_bottom_endpoint = v_endpoints[v_index][0];
			v_top_endpoint = v_endpoints[v_index][1];

			// set the x-axis of the vertical line (to make the if statements more
			//		readable)
			v_x_axis = *v_ln_it;
			
			if(v_x_axis > h_left_endpoint && v_x_axis < h_right_endpoint) {
				if(h_y_axis > v_bottom_endpoint && h_y_axis < v_top_endpoint) {
					// cout << "plus is at (" << v_x_axis << "," << h_y_axis << ")" << endl;
					total_plus_signs++;
				}
			}

			v_ln_it++;
			v_index++;
		}

		h_ln_it++;
		h_index++;
	}

	return total_plus_signs;
}

// !!! different implementation
//	count the pluses while drawing the lines. then remove duplicate pluses.


// !!! generate random L and D (large number of them) and use them to run the program
//			and see it's performance on larger values.
///////////////////////////////////////////////////////////////////////////////////////
//							random D generator
// randomly generates a string of direction characters with length equal to 
//		number_of_moves. The chars in the string can be U, R, D, or L.
// 2 <= number_of_moves <= 2,000,000
string generate_directions(int number_of_moves) {
	srand((unsigned) time(NULL));

	int random;
	char dir;

	string direction_string = "";

	for(int i = 0; i < number_of_moves; i++) {
		random = rand() % 4;
		
		dir = digit_to_dir_conv(random);

		direction_string += dir;

		cout << dir;
	}

	// cout << direction_string << endl;
	return direction_string;
}

// helper function to convert a number representing one of four directions (Up Right Down 
//		and Left) to its respective character (0 == Up == U, 1 == Right == R,
//		2 == Down == D, 3 == Left = L)
char digit_to_dir_conv(int digit) {
	if(digit == 0) {
		return 'U';
	} else if(digit == 1) {
		return 'R';
	} else if(digit == 2) {
		return 'D';
	} else if(digit == 3) {
		return 'L';
	} else {
		cout << "Wrong digit." << endl;
		return 'W';
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//							random L generator
// 1 <= Li <= 1,000,000,000
// generate an array of integers, with a size of number_of_moves. The integers can be
//	from 1 to 1,000,000,000
vector<int> generate_lengths(int number_of_moves, int max_move_size) {
	int random_int;

	// int *array_of_lengths = new int(number_of_moves);
	vector<int> vector_of_lengths;

	// will be used to obtain a seed for the random number engine	
	std::mt19937 generator(time(NULL));
	std::uniform_int_distribution<int> distribution(1, max_move_size);

	for(int i = 0; i < number_of_moves; i++) {
		random_int = distribution(generator);

		vector_of_lengths.push_back(random_int);
		// cout << vector_of_lengths.at(i) << endl;
	}

	return vector_of_lengths;
} 

// !!! if both versions of the program yield the same result for randomly generated
//		sets, and if they also work correctly for smaller ones, then they most likely
//		work.


