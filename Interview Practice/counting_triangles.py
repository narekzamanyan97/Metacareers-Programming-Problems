import math
# Add any extra import statements you may need here


# Add any helper functions you may need here
def are_triangles_equal(tuple_1, tuple_2):
  array_1 = list(tuple_1)
  array_2 = list(tuple_2)
  
  # first, sort the triangle sides in ascending order
  array_1.sort()
  array_2.sort()
  
  for i in range(0, 3):
    if array_1[i] != array_2[i]:
      return False
    
  return True
      

def countDistinctTriangles(arr):
  # Write your code here
  num_of_distinct_triangles = 0
  
  for i in range(0, len(arr)):
    duplicate_found = False
    for j in range(i + 1, len(arr)):
      if are_triangles_equal(arr[i], arr[j]):
        duplicate_found = True
    
    if not duplicate_found:
      num_of_distinct_triangles += 1
        
  return num_of_distinct_triangles
  

# These are the tests we use to determine if the solution is correct.
# You can add your own at the bottom.

def printInteger(n):
  print('[', n, ']', sep='', end='')

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
    printInteger(expected)
    print(' Your output: ', end='')
    printInteger(output)
    print()
  test_case_number += 1

if __name__ == "__main__":
  arr_1 = [(7, 6, 5), (5, 7, 6), (8, 2, 9), (2, 3, 4), (2, 4, 3)]
  expected_1 = 3
  output_1 = countDistinctTriangles(arr_1)
  check(expected_1, output_1)

  arr_2 = [(3, 4, 5), (8, 8, 9), (7, 7, 7)]
  expected_2 = 3
  output_2 = countDistinctTriangles(arr_2)
  check(expected_2, output_2)

  # Add your own test cases here
  arr_3 = [(3, 4, 5), (8, 8, 9), (7, 7, 7), (7, 7, 3), (7, 3, 7), (3, 7, 7)]
  expected_3 = 4
  output_3 = countDistinctTriangles(arr_3)
  check(expected_3, output_3)
  
  arr_4 = [(7, 7, 3), (7, 3, 7), (3, 7, 7), (3, 3, 3)]
  expected_4 = 2
  output_4 = countDistinctTriangles(arr_4)
  check(expected_4, output_4)
  