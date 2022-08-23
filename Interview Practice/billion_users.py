import math
# Add any extra import statements you may need here

global billion 
billion = 1000000000

# Lower Bound Formula:
#   l^2 + m^2 + h^2 <= h^2 + h^2 + h^2 = 3*(h^2)
#   billion = coef*(l^lowerbound_exp) 
#   use log to find the lowerbound_exp
# Upper Bound Formula
#   l^2 + m^2 + h^2 >= l^2 + l^2 + l^2 = 3*(l^2)
#   billion = coef*(l^upper_bound_exp)
#   use log to find the upper_bound_exp
def get_lower_or_upper_bound_exp(rate, N):
  coef = N
  lower_or_upper_bound_exp = math.log(billion/coef, rate)
  
  lower_or_upper_bound_exp = math.ceil(lower_or_upper_bound_exp)
  
  return lower_or_upper_bound_exp
  
# Add any helper functions you may need here
def recursive_search(growthRates, l, h):
  m = int((l + h)/2)
  
  total_users = 0
  total_users_l = 0
  total_users_h = 0
  
  for rate in growthRates:
    total_users += rate ** m
    total_users_l += rate ** (m - 1)
    total_users_h += rate ** (m + 1)
        
  # base case:
  if total_users >= billion:
    if total_users_l < billion:
      return m
    else:
      return recursive_search(growthRates, l, m-1)
  else:
    if total_users_h > billion:
      return m + 1
    else:
      return recursive_search(growthRates, m+1, h)
  

  

def getBillionUsersDay(growthRates):
  growthRates.sort()
  smallest_rate = growthRates[0]
  highest_rate = growthRates[len(growthRates) - 1]
  
  # exponent = number of days
  upper_bound_exp = get_lower_or_upper_bound_exp(smallest_rate, len(growthRates))
  lower_bound_exp = get_lower_or_upper_bound_exp(highest_rate, len(growthRates))
  
  return recursive_search(growthRates, lower_bound_exp, upper_bound_exp)


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
  test_1 = [1.1, 1.2, 1.3]
  expected_1 = 79
  output_1 = getBillionUsersDay(test_1)
  check(expected_1, output_1)

  test_2 = [1.01, 1.02]
  expected_2 = 1047
  output_2 = getBillionUsersDay(test_2)
  check(expected_2, output_2)

  # Add your own test cases here
  test_3 = [1.22, 1.32, 1.5]
  expected_3 = 52
  output_3 = getBillionUsersDay(test_3)
  check(expected_3, output_3)