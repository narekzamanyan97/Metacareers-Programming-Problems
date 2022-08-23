import math
# Add any extra import statements you may need here


# Add any helper functions you may need here
def reverse_subarray(arr, start_index, end_index):
  return_array = arr.copy()
  
  reversed_subarray = []
  
  index = end_index
  
  while index >= start_index:
    reversed_subarray.append(return_array[index])
    
    index -= 1
  
  index_for_reversed_array = 0
  
  while start_index <= end_index:
    return_array[start_index] = reversed_subarray[index_for_reversed_array]
    
    
    index_for_reversed_array += 1
    start_index += 1
  
  return return_array
  

def are_they_equal(array_a, array_b):
  # Write your code here
  
  for index_1 in range(0, len(array_b)):
    for index_2 in range(index_1 + 1, len(array_b)):
      reversed_array = reverse_subarray(array_b, index_1, index_2)
      
      if array_a == reversed_array:
        return True

  return False









# These are the tests we use to determine if the solution is correct.
# You can add your own at the bottom.
def printString(string):
  print('[\"', string, '\"]', sep='', end='')

test_case_number = 1

def check(expected, output):
  global test_case_number
  result = False
  if expected == output:
    result = True
  rightTick = '\u2713'
  wrongTick = '\u2717'
  if result:
    print(rightTick, 'Test #', test_case_number, sep='')
  else:
    print(wrongTick, 'Test #', test_case_number, ': Expected ', sep='', end='')
    printString(expected)
    print(' Your output: ', end='')
    printString(output)
    print()
  test_case_number += 1

if __name__ == "__main__":
  n_1 = 4
  a_1 = [1, 2, 3, 4]
  b_1 = [1, 4, 3, 2]
  expected_1 = True
  output_1 = are_they_equal(a_1, b_1)
  check(expected_1, output_1)

  n_2 = 4
  a_2 = [1, 2, 3, 4]
  b_2 = [1, 2, 3, 5]  
  expected_2 = False
  output_2 = are_they_equal(a_2, b_2)
  check(expected_2, output_2)

  # Add your own test cases here
  n_3 = 6
  a_3 = [3, 5, 7, 9, 11, 13]
  b_3 = [3, 11, 9, 7, 5, 13]
  expected_3 = True
  output_3 = are_they_equal(a_3, b_3)
  check(expected_3, output_3)
  