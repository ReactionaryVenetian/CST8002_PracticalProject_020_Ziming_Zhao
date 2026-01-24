# Author: Ziming Zhao
# Brave new world towards the defense industries.
# Sources: 
# Install: https://code.visualstudio.com/docs/python/python-tutorial
# Basic syntax and structure: https://earthdatascience.org/courses/intro-to-earth-data-science/write-efficient-python-code/intro-to-clean-code/python-pep-8-style-guide/
# Comments & Hello World: https://www.w3schools.com/python/python_comments.asp
# Printing Version: https://stackoverflow.com/questions/1252163/printing-python-version-in-output
#
#

class CamelCaseExample():

    """
    Docstring for CamelCaseExample
    Prints basic 8002 assignment info.
    """
    
import sys

# Prints out stuff after white line space    
print("Hello Tuna Fish!")
print(sys.version)
print("Ziming Zhao")


"""
Hello Tuna Fish!
Traceback (most recent call last):
  File "/home/repl910/main.py", line 20, in <module>
    print(sys.version)
          ^^^
NameError: name 'sys' is not defined. Did you forget to import 'sys'?


** Process exited - Return Code: 1 **
oops, forgot to import the module
"""