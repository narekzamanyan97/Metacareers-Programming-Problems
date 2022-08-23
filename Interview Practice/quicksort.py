# Algorithm for Quicksort: p. 78 (in CS 3310 book)

'''
	array = [15, 22, 13, 27, 12, 10, 20, 25]
	pivot_point = 0
'''

def quicksort(array, low, high):
	# pick the pivot_point index to be the first element of the array of interest
	pivot_point = low

	if high > low:
		# partition updates the pivot_point and the array
		pivot_point = partition(array, low, high, pivot_point)
		
		quicksort(array, low, pivot_point - 1)
		quicksort(array, pivot_point + 1, high)

def partition(array, low, high, pivot_point):
	# get the value at the index pivot_point of array
	pivot_item = array[pivot_point]

	# j = the current value of pivot_point, i.e. the index at which the last
	#		element less than the pivot_item is placed. This will later become
	#		the pivot_point
	j = pivot_point
	
	# adding 1 to high because high is inclusive (high = len(subarray) - 1)
	for i in range(low + 1, high + 1):
		if array[i] < pivot_item:
			# increment the current pivot_point, as more elements are placed to the
			#		right of it
			j += 1

			# exchange array[i] and array[j]
			#	i.e. place the smaller element to the left of pivot_item
			temp_el = array[j]

			array[j] = array[i]
			array[i] = temp_el

	# update the pivot_point with j
	pivot_point = j

	# put pivot_item at pivot_point. i.e. exchange the element at pivot_point
	#		with the pivot_item
	temp_el = array[pivot_point]
	
	array[pivot_point] = array[low]
	array[low] = temp_el


	return pivot_point


array = [15, 22, 13, 27, 12, 10, 20, 25]


low = 0
high = len(array) - 1
quicksort(array, low, high)

print(array)