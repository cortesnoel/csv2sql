# csv2sql
This program is a C-based command-line tool for constructing basic DML SQL queries from .csv.

# Motivation
My main motivation for building this tool was to learn the basics of the C programming language in a practical way.
It also doesn't hurt to have a tool that can build testable mock data sets quickly.

# Installation
1. Clone csv2sql repository into local directory
![Alt text](/img/clone.jpg?raw=true "Cloning Repository")
2. Run cmd in directory containing cloned csv2sql repository
![Alt text](/img/cmd.jpg?raw=true "Running Command Line")
3. Enter command in terminal to generate program executable: gcc main.c -o csv2sql.exe
![Alt text](/img/compile.jpg?raw=true "Compiling csv2sql Tool")
4. Enter command in terminal to run csv2sql program: csv2sql                          
![Alt text](/img/run.jpg?raw=true "Running csv2sql Tool")
 
# Formatting Rules & Examples:
INSERT Query
1. I,-,table,-,value,-
2. I,-,table,-,value1,value2,-
3. I,-,table,-,column1,column2,-,value1,value2,-

UPDATE Query
1. U,-,table,-,column,-,value,-,refColumn,-,refValue,-

DELETE Query
1. D,-,table,-,refColumn,-,refValue,-

In addition to above examples:
1. There should be no empty lines between data rows
2. Data within row should be sepereated by ‘-‘ character
2. Datatype must be specified in .csv (example: 'dataExample')

# Testing
*See example files in csv2sql Test directory*
1. To test csv2sql.exe with bigger sample, enter command in terminal: **csv2sql < test/test_input.csv**
2. To test using your own data, please follow directions below.

# How to use?
1. Install csv2sql tool (see installation directions)
3. Verify your input file only contains accepted .csv data format (see formatting rules above)
2. Run command to generate .sql file from .csv: **csv2sql < your_input_file.csv > your_output_file.sql**
3. Verify output .sql file in your local directory

# Contribute
If you wish to contribute to this project, please generate a pull request for review. Comments are also always much welcomed. Thank you!
