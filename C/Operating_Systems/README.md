Operating Systems
==========

3-st year course at Computer Science. Makefiles and .asm files are not included.

--

**Lab 1**: 

Set up build environment;

Launch hello world OS with the message successfully displayed on the screen;

--

**Lab 2**: 

Using the given libraries, which make the function getchar available, implement a simple command prompt:

Implement the input and output of strings;

Create some commands;

Manage the case when the cursor reaches the end of the line or of the screen.

--

**Lab 3**: 

Integrate the code for longjmp.c and setjmp.asm in your project, so that you can use these functions;

Show a working example of setjmp and longjmp (+20 EXP).

--
**Lab 4**: 

Have a simple multitasking implemented;

Implement the following functions:

``void sched_add_task(void* func_ptr)'' – add a task to scheduler by giving a function pointer;

``void yield(void)'' – give control to scheduler in a task;

``void sched_run(void)'' – start the scheduler.

--