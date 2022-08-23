# Algorithm for mergesort: p. 72 (CS 3310 book)

'''
Start
array = [6, 5, 12, 10, 9, 1]

l = 0
r = 5 (size of array - 1)
m = 2
	
	mergeSort (left)
	array = [6, 5, 12]
	l = 0
	r = 2
	m = 1
		merge_sort (left)
		array = [6, 5]
		l = 0
		r = 1
		m = 0

			merge_sort (left)
			array = [6]
			return [6]

			merge_sort (right)
			array = [5]
			return [5]

			merge([5], [6])
			return [5, 6]

		merge_sort (right)
		array = [12]
		return [12]

		merge([5, 6], [12])
		return [5, 6, 12]

	mergeSort (right)
	array = [10, 9, 1]
	l = 3
	r = 5
	m = 4

		mergeSort (left)
		array = [10, 9]
		l = 3
		r = 4
		m = 3

			mergeSort (left)
			array = [10]
			return [10]

			mergeSort (right)
			array = [9]
			return [9]

			merge([10], [9])
			return [9, 10]
		
		mergeSort (right)
		array = [1]
		return [1]

		merge([9, 10], [1])
		return [1, 9, 10]

	merge([5, 6, 12], [1, 9, 10])
	return [1, 5, 6, 9, 10, 12]
'''

array = [3, 10, 2, 7, 6, 12, 1, 4, 5]
# array = [6, 5, 12, 10, 9, 1]

def merge(array_left, array_right):
	# both left and right arrays are already sorted.

	# initialize the size of each array using len() function
	size_left = len(array_left)
	size_right = len(array_right)

	# set the loop indices to 0 for both arrays to start with
	# l = starting index of the left array
	# r = staring index of the right array
	l = 0
	r = 0

	# merged array
	merged_array = []

	# while the left and right arrays are not empty, compare their elements
	while l < size_left and r < size_right:
		if array_left[l] < array_right[r]:
			merged_array.append(array_left[l])

			l += 1
		else:
			merged_array.append(array_right[r])

			r += 1

	# after the while loop above, either the left or the right array still has
	#		elements
	# iterate over both arrays to make sure all the elements are merged
	if l < size_left:
		while l < size_left:
			merged_array.append(array_left[l])
			l += 1

	if r < size_right:
		while r < size_right:
			merged_array.append(array_right[r])
			r += 1

	return merged_array


def mergeSort(array, l, r):
	# if the left index is less than the right index, proceed with the sort
	if l < r:
		m = int(l/2 + r/2)

		merged_array_left = mergeSort(array, l, m)
		merged_array_right = mergeSort(array, m+1, r)

		merged_array = merge(merged_array_left, merged_array_right)

		return merged_array

	# base case is:
	#	l = r (1 item in the array)
	else:
		array_to_return = []
		array_to_return.append(array[l])

		# return that item
		return array_to_return


def merge2(array, l, m, h):
	# local array used for merging
	merged_arrays = []

	# i = the starting index for the left half array
	i = l
	# j = the starting index for the right half array
	j = m


	# iterate over the original array and merge its items into merged_arrays
	while i <= m and j <= h:
		if array[i] < array[j]:
			merged_arrays.append(array[i])

			i += 1
		else:
			merged_arrays.append(array[j])
			j += 1

	# after the loop above, either of the left/right halves are not completely
	#		used. Find that half and copy its values into merged_arrays
	if i > m:
		while j <= h:
			merged_arrays.append(array[j])

			j += 1
	else:
		while i <= m:
			merged_arrays.append(array[i])

			i += 1


	# move the elements of merged_arrays into the given array, thus saving space
	low = l
	for element in merged_arrays:
		print(low)
		print(array)
		array[low] = element
		low += 1



def mergeSort2(array, l, h):
	# if the left index is less than the right index, proceed with the sort
	if l < h:
		m = int(l/2 + h/2)
		# recursive calls, dividing the array into 2 halves
		mergeSort2(array, l, m)
		mergeSort2(array, m + 1, h)

		merge2(array, l, m, h)

print(array)
mergeSort2(array, 0, len(array) - 1)
print(array)
