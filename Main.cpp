#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 color;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 proj;\n"
"void main()\n"
"{\n"
"   gl_Position = proj * view * model * vec4(aPos, 1.0);\n"
"   color = aColor;\n"
"}\n";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 color;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(color, 1.0f);\n"
"}\n";

int main()
{
	// Initialize GLFW
	glfwInit();
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	
	
	// Shader ------------------------------------------------------
	// 創造Vertex Shader Object，得到它的reference，也就是一個無號整數，感覺像和GPU要一個空間
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 將寫好的Vertex Shader Code(用GLSL寫的) 連結上 Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// GPU 不會幫你compile，所以還要自己編譯成machine code
	glCompileShader(vertexShader);
	// 以下3行同理
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	// 創造 Shader Program Object，它也是給你一個編號
	GLuint shaderProgram = glCreateProgram();
	// 將之前創造好的Shader Objects 連結上 Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// 最後把Shader Program 裡的Shader Objects 打包成一個東西，我也不確定是不是這樣解釋?
	glLinkProgram(shaderProgram);
	
	// 有了Shader Program，之前創造的Shader Objects就不需要了，可以把他們刪掉
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// -------------------------------------------------------------

/*	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    1.0f, 0.0f, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     0.0f, 1.0f, 0.0f,// Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  0.0f, 0.0f, 1.0f// Upper corner
	};
*/
	GLfloat vertices[] =
	{
		-0.5f,  0.0f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.0f,  0.5f,  1.0f,  1.0f,  0.0f,
		 0.0f,  0.8f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.0f,  0.8f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		 -0.5f,  0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		 0.0f,  0.8f,  0.0f,  0.0f,  0.0f,  1.0f,

		 0.5f,  0.0f,  0.5f,  1.0f,  0.0f,  1.0f,
		 0.5f,  0.0f, -0.5f,  1.0f,  0.0f,  1.0f,
		 0.0f,  0.8f,  0.0f,  1.0f,  0.0f,  1.0f,
	};

	GLfloat vertices2[] =
	{
		-0.8f,  0.8f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.8f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		 0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

		
	};

	// Buffer ---------------------------------------------------------
	// 先宣告buffer的ID，也是無號整數，但和Shader Object 不同是，這裡將參考穿進函式修改，前者是回傳
	GLuint VAO, VBO;
	// 如同前面講的，傳參考。然後記得VAO要比VBO早generate !!!
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// 把VAO bind起來，指現在正在使用的Vertex Array Object
	glBindVertexArray(VAO);
	// 把VBO bind起來，有一些參數可以選，如GL_ARRAY_BUFFER，然後下一行就可以傳data給他
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// 這裡就是VAO 派上用場的地方，告訴GPU要如何解釋VBO 裡的值
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

	// 要記得上面Attrib設完，還要加以下來enable它
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// 這裡GL_ARRAY_BUFFER 是VBO，所以裡面的東西被覆蓋掉了
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW); 


	// 以上就把Buffer裡的值都設定好了，安全起見，可以把Buffer和Vertex Array都bind到0，之後就不會不小心修改到
	// 然後，這裡的順序很重要，先VBO 在 VAO !!!
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	

	// -------------------------------------------------------------
	
	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// Timer
	float rotation = 0.0f;
	double prevTime = glfwGetTime();



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);


		// Timer
		double crntTime = glfwGetTime();
		if ((crntTime - prevTime) >= 1 / 60) {
			rotation += 0.1f;
			prevTime = crntTime;
			std::cout << rotation << std::endl;
		}

		// model 
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 1.0f, -5.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(800 / 800), 0.1f, 100.0f);
		int modelLoc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projlLoc = glGetUniformLocation(shaderProgram, "proj");
		glUniformMatrix4fv(projlLoc, 1, GL_FALSE, glm::value_ptr(proj));



		
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 12);
		glfwSwapBuffers(window);
	 
		
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete -------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	// --------------------------------------------------

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}