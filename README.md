# Notes
Open in VS, f5 on main file

#Main file
In the main file we start by initialize the window and generate the shaders for the map and shaders.
After that we set colours for the background to be black and colour for the pellets to be blue and this will be reset consistantly. We then compile the shaders and attach them to the program. Then we link them to make them executable and then the program should run and display correctly.  

#Functions for dummies (aka us)
glGetUniformLocation // returns an integer from the shader program

glUseProgram //renders program object

glBindVertexArray //binds the vertex array object with name array

glDrawElements // creates geometrics

glAttachShader // attaches x shader to the program

glLinkProgram // links program objects and creates executables that will run

glGetVertexArrayiv // retrieve ID of buffer object and binds

glGetIntegerv // finds int

glGetVertexAttribiv // reads floating-point values and converts to four integer values