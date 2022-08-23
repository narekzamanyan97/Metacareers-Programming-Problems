import math
# Add any extra import statements you may need here


# Add any helper functions you may need here


def rotationalCipher(input, rotation_factor):
  output_string = ''
  
  # Write your code here
  # iterate over the input array
  for ch in input:
    # if the ch is digit or a letter, do the conversion
    if ch.isalpha():
      # wrap around the rotation factor
      # if ch is a letter, wrap around 26
      # while rotation_factor >= 26:
      rotation_factor_letter = rotation_factor % 26
      
      
      # wrap around from Z to A
      # treat uppercase and lowercase letters
      ascii_position = ord(ch)
      
      
      # a = 97
      # A = 65
      # if the letter is uppercase
      if ascii_position < 65 + 26:
        ascii_position = ord(ch) + rotation_factor_letter
        
        # if after rotation, ascii_position >= 97, then convert it back to uppercase
        if ascii_position >= 65 + 26:
          ascii_position -= 26
      # else, the letter is lowercase
      elif ascii_position < 97 + 26:
        ascii_position = ord(ch) + rotation_factor_letter
        
        # if the rotation made the character go beyond the lowercase letters, bring it back
        if ascii_position >= 97 + 26:
          ascii_position -= 26          
          
      
      converted_ch = chr(ascii_position)
      
      
    # elif ch is numeric
    elif ch.isnumeric():
      print(rotation_factor)
      print(rotation_factor % 10)
      rotation_factor_number = rotation_factor % 10
      
      integer_ch = int(ch)
      converted_int_ch = (integer_ch + rotation_factor_number) % 10
      converted_ch = str(converted_int_ch)
    else:
      converted_ch = ch
    
    
    output_string += converted_ch
      
  return output_string











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
  input_1 = "All-convoYs-9-be:Alert1."
  rotation_factor_1 = 4
  expected_1 = "Epp-gsrzsCw-3-fi:Epivx5."
  output_1 = rotationalCipher(input_1, rotation_factor_1)
  check(expected_1, output_1)

  input_2 = "abcdZXYzxy-999.@"
  rotation_factor_2 = 200
  expected_2 = "stuvRPQrpq-999.@"
  output_2 = rotationalCipher(input_2, rotation_factor_2)
  check(expected_2, output_2)

  # Add your own test cases here
  