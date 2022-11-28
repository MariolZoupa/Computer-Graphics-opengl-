// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>
#include <ctime>
// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/controls.hpp>
#include <common/texture.hpp>
#include <common/objloader.hpp>

#include <glm/gtc/matrix_transform.hpp> 

#include <glm/gtx/transform.hpp>

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}



	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(600, 600, u8"Συγκρουόμενα", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);




	
	//ENABLE TO BLENDING
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);



	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint VertexArrayID2;
	glGenVertexArrays(1, &VertexArrayID2);
	glBindVertexArray(VertexArrayID2);

	// Create and compile our GLSL program from the shaders
	GLuint programID2 = LoadShaders("TransformVertexShader1.vertexshader", "TextureFragmentShader.fragmentshader");
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
	


	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	// Get a handle for our "MVP" uniform
	GLuint MatrixID2 = glGetUniformLocation(programID2, "MVPSP");

	// Load the texture
	GLuint Texture = loadDDS("Stexture.dds");



	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.


	bool res = loadOBJ("sphere.obj", vertices, uvs, normals);



	


	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 6000.0f);
	// Camera matrix
	//glm::mat4 View = glm::lookAt(
		//glm::vec3(4, 3, -3), // Camera is at (4,3,-3), in World Space
		//glm::vec3(0, 0, 0), // and looks at the origin
		//glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	//);

	//arxikopoihsh random diastasewn apo to [1,2...10]
	srand((unsigned)time(NULL));
	float d = (rand() % 10) + 1;
	float d2 = d / 2;

	//arxiki thesi mikroy antikimenou
	glm::vec3 startpos(0, 0, 0);

	//thesi kubou kai sfairas
	glm::vec3 SCpos(50.0, 50.0, 50.0);
	glm::vec3 SPpos(50.0, 50.0, 50.0);
	
	//glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 Model = glm::translate(Model, SCpos);

	//glm::mat4 ModelSP = glm::mat4(1.0f);
	glm::mat4 ModelSP = glm::translate(ModelSP, SPpos);
	
	//glm::mat4 ModelS = glm::mat4(1.0f);
	glm::mat4 ModelS = glm::translate(ModelS, startpos);
	
	
	
	//katefthinsi twn mikrwn antikimenwn random apo to [0.1,...,0.9]
	float x = (rand() % 9) + 1;
	float y = (rand() % 9) + 1;
	float z = (rand() % 9) + 1;
	glm::vec3 direction(x / 10, y / 10, z / 10);



	//vertex buffer me thn random diastasi toy mikrou kubou
	static const GLfloat smallcube_vertex_buffer_data[] = {
		-d,-d,-d,
		-d,-d, d,
		-d, d, d,
		 d, d,-d,
		-d,-d,-d,
		-d, d,-d,
		 d,-d, d,
		-d,-d,-d,
		 d,-d,-d,
		 d, d,-d,
		 d,-d,-d,
		-d,-d,-d,
		-d,-d,-d,
		-d, d, d,
		-d, d,-d,
		 d,-d, d,
		-d,-d, d,
		-d,-d,-d,
		-d, d, d,
		-d,-d, d,
		 d,-d, d,
		 d, d, d,
		 d,-d,-d,
		 d, d,-d,
		 d,-d,-d,
		 d, d, d,
		 d,-d, d,
		 d, d, d,
		 d, d,-d,
		-d, d,-d,
		 d, d, d,
		-d, d,-d,
		-d, d, d,
		 d, d, d,
		-d, d, d,
		 d,-d, d

	};


	//random xrrwma gia ton mikro kubo
	float red1 = (float)rand() / RAND_MAX;
	float green1 = (float)rand() / RAND_MAX;
	float blue1 = (float)rand() / RAND_MAX;

	//xrwmatismos kathe trigwnou me to idio xrwma
	static GLfloat smallcube_color_buffer_data[12 * 3 * 3];
	for (int v = 0; v < 12 * 3; v++) {
		smallcube_color_buffer_data[3 * v + 0] = red1;
		smallcube_color_buffer_data[3 * v + 1] = green1;
		smallcube_color_buffer_data[3 * v + 2] = blue1;

	}

	//vertex buffer me diastaseis (0,0,0) mexri (100,100,100) opws to tutorial tou kyriou Fountou gia ton Scene Cube
	static const GLfloat g_vertex_buffer_data[] = {
		0.0f,0.0f,0.0f,
		100.0f,100.0f,0.0f,
		100.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,100.0f,0.0f,
		100.0f,100.0f,0.0f,
		0.0f,0.0f,0.0f,
		100.0f,0.0f,0.0f,
		100.0f,0.0f,100.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,100.0f,
		100.0f,0.0f,100.0f,
		0.0f,0.0f,0.0f,
		0.0f,100.0f,0.0f,
		0.0f,100.0f,100.0f,
		0.0f,0.0f,0.0f,
		0.0f,100.0f,100.0f,
		0.0f,0.0f,100.0f,
		0.0f,100.0f,100.0f,
		0.0f,0.0f,100.0f,
		100.0f,100.0f,100.0f,
		0.0f,0.0f,100.0f,
		100.0f,0.0f,100.0f,
		100.0f,100.0f,100.0f,
		100.0f,0.0f,0.0f,
		100.0f,100.0f,0.0f,
		100.0f,100.0f,100.0f,
		100.0f,0.0f,0.0f,
		100.0f,0.0f,100.0f,
		100.0f,100.0f,100.0f,
		0.0f,100.0f,0.0f,
		0.0f,100.0f,100.0f,
		100.0f,100.0f,100.0f,
		0.0f,100.0f,0.0f,
		100.0f,100.0f,0.0f,
		100.0f,100.0f,100.0f
	};

	//random xrwmatismos toy SC
	srand((unsigned)time(NULL));
	GLfloat red = (float)rand() / RAND_MAX;
	GLfloat green = (float)rand() / RAND_MAX;
	GLfloat blue = (float)rand() / RAND_MAX;

	bool spacekey = false;
	
	GLfloat alpha2Value = 0.1f;

	// xrwmatismos kathe trigwnou tou SC me extra mia metavliti pou dinei to alpha(diafania)
	static const GLfloat g_color_buffer_data[] = {
		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,
		red , green, blue,  alpha2Value,

		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,

		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,

		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,

		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,

		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,

		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,

		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,

		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,

		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,

		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,

		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value,
		red , green, blue, alpha2Value


	};

	//vertex bind tou SC
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	//color bind tou SC
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	glUseProgram(programID);




	//vertex bind tou Sphere
	GLuint vertexbufferSP;
	glGenBuffers(1, &vertexbufferSP);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferSP);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	//color bind tou Sphere
	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);



	//vertex bind tou mikrou kybou
	GLuint vertexbuffer1;
	glGenBuffers(1, &vertexbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(smallcube_vertex_buffer_data), smallcube_vertex_buffer_data, GL_STATIC_DRAW);

	//color bind tou mikrou kybou
	GLuint colorbuffer1;
	glGenBuffers(1, &colorbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(smallcube_color_buffer_data), smallcube_color_buffer_data, GL_STATIC_DRAW);


	do {

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);
		//glUseProgram(programID2);



		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glm::mat4 MVPSP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glm::mat4 MVPS = ProjectionMatrix * ViewMatrix * ModelMatrix;

	

		
		/************************************************************ SPHERE ****************************************************************/
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVPSP[0][0]);


		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbufferSP);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		/**********************************************************************************************************************************************/




		/************************************************************ SMALL CUBE GENERATOR****************************************************************/
		printf("%f\n", d);
		printf("%f\n", d2);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {

			spacekey = true;
		}



		if (spacekey == true) {

			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVPS[0][0]);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);

			glVertexAttribPointer(
				0,      // shader layout location
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, colorbuffer1);
			glVertexAttribPointer(
				1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);


			glDrawArrays(GL_TRIANGLES, 0, 3);   // draw triangle
			// Draw the triangle !
			glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);

			

		}
		/**********************************************************************************************************************************************/






		/*************************************************************** SCENE CUBE *******************************************************************************/

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			4,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDisable(GL_DEPTH_TEST);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles
		glEnable(GL_DEPTH_TEST);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		/**********************************************************************************************************************************************/





		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &vertexbufferSP);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteProgram(programID);
	glDeleteProgram(programID2);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID2);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}