import math
# Add any extra import statements you may need here

# Add any helper functions you may need here
def find_3_largest_elements(arr, last_index):
  subarray = []
  
  for i in range(0, last_index + 1):
    subarray.append(arr[i])
    
  subarray.sort(reverse=True)
  
  el_1 = subarray[0]
  el_2 = subarray[1]
  el_3 = subarray[2]
  
  return el_1, el_2, el_3
  
def findMaxProduct(arr):
  size_of_array = len(arr)
  
  products_array = [0] * size_of_array
  
  for i in range(0, len(arr)):
    if i == 0 or i == 1:
      products_array[i] = -1
    else:
      el_1, el_2, el_3 = find_3_largest_elements(arr, i)
      
      products_array[i] = el_1 * el_2 * el_3
  
  return products_array

# These are the tests we use to determine if the solution is correct.
# You can add your own at the bottom.

def printInteger(n):
  print('[', n, ']', sep='', end='')

def printIntegerList(array):
  size = len(array)
  print('[', end='')
  for i in range(size):
    if i != 0:
      print(', ', end='')
    print(array[i], end='')
  print(']', end='')

test_case_number = 1

def check(expected, output):
  global test_case_number
  expected_size = len(expected)
  output_size = len(output)
  result = True
  if expected_size != output_size:
    result = False
  for i in range(min(expected_size, output_size)):
    result &= (output[i] == expected[i])
  rightTick = '\u2713'
  wrongTick = '\u2717'
  if result:
    print(rightTick, 'Test #', test_case_number, sep='')
  else:
    print(wrongTick, 'Test #', test_case_number, ': Expected ', sep='', end='')
    printIntegerList(expected)
    print(' Your output: ', end='')
    printIntegerList(output)
    print()
  test_case_number += 1

if __name__ == "__main__":
  arr_1 = [1, 2, 3, 4, 5]
  expected_1 = [-1, -1, 6, 24, 60]
  output_1 = findMaxProduct(arr_1)
  check(expected_1, output_1)

  arr_2 = [2, 4, 7, 1, 5, 3]
  expected_2 = [-1, -1, 56, 56, 140, 140]
  output_2 = findMaxProduct(arr_2)
  check(expected_2, output_2)


  # Add your own test cases here
  