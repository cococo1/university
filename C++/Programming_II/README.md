Programming in C++
==========

2-nd year course at Computer Science.

--

**Lab 1** 
1. a) Create an abstract data type (a class) – monitor, which has the name of the firm that produces it, the dimension in inches, the number of colors, and the resolution. Define setters and getters, a function for monitors’ comparison. Create the text fields using new operator. Free the memory. In main, simulate the search of a monitor by dimension and other data.
b) Create an abstract data type (a class) – vector, which has a pointer to int and a number of elements. Define the functions : initialization, deleting of vector, setting/modifying the size of the vector, access to vector’s elements and the multiplication of all negative elements. In main, simulate the product of two vectors : element by element.
2. a) Create the class Queue. The fields – number of elements and a pointer for dynamical memory allocation. Define constructors : default constructor, copy constructor  and a general constructor with a parameter  - number of needed elements. Define functions add and get for pushing and popping of an element. Also define the functions isEmpty and isFull for control of the state of queue.
b) Create the class Matrix. This class contains a pointer to int, the number of rows and columns and a variable – error code. Define the constructor without parameters, the constructor with one parameter – for a quadratic matrix and another one with two parameters – for a non-quadratic matrix. Define methods for access : setting and getting the value of an element. Define the function for addition,  subtraction and multiplication between two matrixes. Define a function for multiplication of a matrix with a number. Check the work of the class. In the case of lack of memory, different dimensions of matrixes, matrix bound’s exceeding, assign the corresponding code of error.

--

**Lab 2**

a) Create a class Bool – for the logical variables. Determine the operators : “+” – logical OR ; “*” – logical AND ; “^” – logical XOR  - as class methods and operators “==” , “!=”  as friend functions. Operators should work both with variables of type Bool and int  (if an integer number is different from zero, it is considered true, otherwise false ).
b) Create a class String  that will use dynamic memory. Determine the operators : “+” – for concatenating two strings ; “=” –assign operator , “+=” – for appending to a string  - as class methods and operators “==”,”!=”,”>”,”<”  as friend functions. Operators should work both with String and char* . Determine the operator [] for accessing an element of a string. Overload stream operators.

--

**Lab 3** 

a) Create an hierarchy of inheritance : Air transport, Passenger transport – Boing 747;
b) Create an hierarchy of inheritance : Transport – Air transport, Passenger transport – Boing 747;

--

**Lab 4**

a) To create a template function which changes pairs of an array in the such way: the first element will be equal to the sum of the pair, the second one to the difference. For example: 0 2 3 4 6 goes into 2 -2 7 -1 9 -3.
b) Create a parameterized class Matrix. The class should contain constructors, destructor, getRows and getCols functions, operators [], +, -, *, and stream operators. 

--

