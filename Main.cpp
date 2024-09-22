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
	// �гyVertex Shader Object�A�o�쥦��reference�A�]�N�O�@�ӵL����ơA�Pı���MGPU�n�@�ӪŶ�
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// �N�g�n��Vertex Shader Code(��GLSL�g��) �s���W Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// GPU ���|���Acompile�A�ҥH�٭n�ۤv�sĶ��machine code
	glCompileShader(vertexShader);
	// �H�U3��P�z
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	// �гy Shader Program Object�A���]�O���A�@�ӽs��
	GLuint shaderProgram = glCreateProgram();
	// �N���e�гy�n��Shader Objects �s���W Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// �̫��Shader Program �̪�Shader Objects ���]���@�ӪF��A�ڤ]���T�w�O���O�o�˸���?
	glLinkProgram(shaderProgram);
	
	// ���FShader Program�A���e�гy��Shader Objects�N���ݭn�F�A�i�H��L�̧R��
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
	// ���ŧibuffer��ID�A�]�O�L����ơA���MShader Object ���P�O�A�o�̱N�ѦҬ�i�禡�ק�A�e�̬O�^��
	GLuint VAO, VBO;
	// �p�P�e�������A�ǰѦҡC�M��O�oVAO�n��VBO��generate !!!
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// ��VAO bind�_�ӡA���{�b���b�ϥΪ�Vertex Array Object
	glBindVertexArray(VAO);
	// ��VBO bind�_�ӡA���@�ǰѼƥi�H��A�pGL_ARRAY_BUFFER�A�M��U�@��N�i�H��data���L
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// �o�̴N�OVAO ���W�γ����a��A�i�DGPU�n�p�����VBO �̪���
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

	// �n�O�o�W��Attrib�]���A�٭n�[�H�U��enable��
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// �o��GL_ARRAY_BUFFER �OVBO�A�ҥH�̭����F��Q�л\���F
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW); 


	// �H�W�N��Buffer�̪��ȳ��]�w�n�F�A�w���_���A�i�H��Buffer�MVertex Array��bind��0�A����N���|���p�߭ק��
	// �M��A�o�̪����ǫܭ��n�A��VBO �b VAO !!!
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