//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Variables externas -> Ejercicio, no reporte
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
static const char* vShaderR = "shaders/vshaderR.vert";
static const char* fShaderR = "shaders/fshaderR.frag";
static const char* vShaderV = "shaders/vshaderV.vert";
static const char* fShaderV = "shaders/fshaderV.frag";
static const char* vShaderA = "shaders/vshaderA.vert";
static const char* fShaderA = "shaders/fshaderA.frag";
static const char* vShaderC = "shaders/vshaderC.vert";
static const char* fShaderC = "shaders/fshaderC.frag";
static const char* vShaderVO = "shaders/vshaderVO.vert";
static const char* fShaderVO = "shaders/fshaderVO.frag";
//shaders nuevos se crearían acá

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2, //cara frontal
		1,3,2, 
		3,0,2,
		1,0,3 //base
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);

unsigned int cubo2_indices[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3
};

GLfloat cubo2_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh* cubo2 = new Mesh();
cubo2->CreateMesh(cubo2_vertices, cubo2_indices, 24, 36);
meshList.push_back(cubo2);

}

void CrearLetrasyFiguras()
{
	GLfloat vertices_J[] = {
		//X	   Y	Z		R		G		B
		//LETRA J
		-0.85f,0.8f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.4f,0.65f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.85f,0.5f,0.0f,	0.0f,	0.0f,	1.0f,

		-0.4f,0.65f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.85f,0.8f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.4f,0.8f,0.0f,	0.0f,	0.0f,	1.0f,

		-0.4f,0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.85f,0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.4f,0.65f,0.0f,	0.0f,	0.0f,	1.0f,

		//
		-0.7f,-0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.625f,0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.55f,-0.5f,0.0f,	0.0f,	0.0f,	1.0f,

		-0.625f,0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.7f,-0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.7f,0.5f,0.0f,	0.0f,	0.0f,	1.0f,

		-0.55f,0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.55f,-0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.625f,0.5f,0.0f,	0.0f,	0.0f,	1.0f,

		//
		-1.0f,-0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.55f,-0.6f,0.0f,	0.0f,	0.0f,	1.0f,
		-1.0f,-0.7f,0.0f,	0.0f,	0.0f,	1.0f,

		-0.55f,-0.6f,0.0f,	0.0f,	0.0f,	1.0f,
		-1.0f,-0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.55f,-0.5f,0.0f,	0.0f,	0.0f,	1.0f,

		-0.55f,-0.7f,0.0f,	0.0f,	0.0f,	1.0f,
		-1.0f,-0.7f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.55f,-0.6f,0.0f,	0.0f,	0.0f,	1.0f,

		//
		-1.0f,-0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.925f,-0.3f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.85f,-0.5f,0.0f,	0.0f,	0.0f,	1.0f,

		-0.925f,-0.3f,0.0f,	0.0f,	0.0f,	1.0f,
		-1.0f,-0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-1.0f,-0.3f,0.0f,	0.0f,	0.0f,	1.0f,

		-0.85f,-0.3f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.85f,-0.5f,0.0f,	0.0f,	0.0f,	1.0f,
		-0.925f,-0.3f,0.0f,	0.0f,	0.0f,	1.0f
	};

	MeshColor* letras1 = new MeshColor();
	letras1->CreateMeshColor(vertices_J, 216);
	meshColorList.push_back(letras1);
	
	GLfloat vertices_A[] = {
		//LETRA A
		-0.25f,-0.7f,0.0f,	0.0f,	1.0f,	1.0f,
		-0.175f,0.8f,0.0f,	0.0f,	1.0f,	1.0f,
		-0.1f,-0.7f,0.0f,	0.0f,	1.0f,	1.0f,

		-0.175f,0.8f,0.0f,	0.0f,	1.0f,	1.0f,
		-0.25f,-0.7f,0.0f,	0.0f,	1.0f,	1.0f,
		-0.25f,0.8f,0.0f,	0.0f,	1.0f,	1.0f,

		-0.1f,0.8f,0.0f,	0.0f,	1.0f,	1.0f,
		-0.1f,-0.7f,0.0f,	0.0f,	1.0f,	1.0f,
		-0.175f,0.8f,0.0f,	0.0f,	1.0f,	1.0f,

		//
		-0.1f,0.5f,0.0f,	0.0f,	1.0f,	1.0f,
		0.05f,0.8f,0.0,	    0.0f,	1.0f,	1.0f,
		0.2f,0.5f,0.0f,	    0.0f,	1.0f,	1.0f,

		-0.1f,0.5f,0.0f,	0.0f,	1.0f,	1.0f,
		0.05f,0.8f,0.0f,	0.0f,	1.0f,	1.0f,
		-0.1f,0.8f,0.0f,	0.0f,	1.0f,	1.0f,

		0.05f,0.8f,0.0,	    0.0f,	1.0f,	1.0f,
		0.2f,0.8f,0.0f,	    0.0f,	1.0f,	1.0f,
		0.2f,0.5f,0.0f,	    0.0f,	1.0f,	1.0f,

		//
		0.2f,-0.7f,0.0f,	0.0f,	1.0f,	1.0f,
		0.275f,0.8f,0.0f,	0.0f,	1.0f,	1.0f,
		0.35f,-0.7f,0.0f,	0.0f,	1.0f,	1.0f,

		0.275f,0.8f,0.0f,	0.0f,	1.0f,	1.0f,
		0.2f,-0.7f,0.0f,	0.0f,	1.0f,	1.0f,
		0.2f,0.8f,0.0f,	    0.0f,	1.0f,	1.0f,

		0.275f,0.8f,0.0f,	0.0f,	1.0f,	1.0f,
		0.35f,-0.7f,0.0f,	0.0f,	1.0f,	1.0f,
		0.35f,0.8f,0.0f,	0.0f,	1.0f,	1.0f,

		//
		-0.1f,-0.1f,0.0f,	0.0f,	1.0f,	1.0f,
		0.05f,0.2f,0.0f,	0.0f,	1.0f,	1.0f,
		0.2f,-0.1f,0.0f,	0.0f,	1.0f,	1.0f,

		-0.1f,-0.1f,0.0f,	0.0f,	1.0f,	1.0f,
		0.05f,0.2f,0.0f,	0.0f,	1.0f,	1.0f,
		-0.1f,0.2f,0.0f,	0.0f,	1.0f,	1.0f,

		0.05f,0.2f,0.0f,    0.0f,   1.0f,   1.0f,
		0.2f,-0.1f,0.0f,    0.0f,   1.0f,   1.0f,
		0.2f,0.2f,0.0f,     0.0f,   1.0f,   1.0f
	};

	MeshColor* letras2 = new MeshColor();
	letras2->CreateMeshColor(vertices_A, 216);
	meshColorList.push_back(letras2);

	GLfloat vertices_D[] = {
		//LETRA D
		0.45f, -0.7f, 0.0f, 1.0f,   0.0f,   1.0f,
		0.525f, 0.8f, 0.0f, 1.0f,   0.0f,   1.0f,
		0.6f, -0.7f, 0.0f,  1.0f,   0.0f,   1.0f,

		0.525f, 0.8f, 0.0f, 1.0f,   0.0f,   1.0f,
		0.45f, -0.7f, 0.0f, 1.0f,   0.0f,   1.0f,
		0.45f, 0.8f, 0.0f,  1.0f,   0.0f,   1.0f,

		0.6f, 0.8f, 0.0f,   1.0f,   0.0f,   1.0f,
		0.6f, -0.7f, 0.0f,  1.0f,   0.0f,   1.0f,
		0.525f, 0.8f, 0.0f, 1.0f,   0.0f,   1.0f,

		//
		0.6f,0.5f,0.0f,     1.0f,   0.0f,   1.0f,
		0.725f,0.8f,0.0f,   1.0f,   0.0f,   1.0f,
		0.85f,0.5f,0.0f,    1.0f,   0.0f,   1.0f,

		0.6f, 0.5f, 0.0f,   1.0f,   0.0f,   1.0f,
		0.6f, 0.8f,0.0f,    1.0f,   0.0f,   1.0f,
		0.725f,0.8f,0.0f,   1.0f,   0.0f,   1.0f,
		
		0.725f,0.8f,0.0f,   1.0f,   0.0f,   1.0f,
		0.85f,0.8f,0.0f,    1.0f,   0.0f,   1.0f,
		0.85f,0.5f,0.0f,    1.0f,   0.0f,   1.0f,

		//
		0.85f,-0.4f,0.0f,   1.0f,   0.0f,   1.0f,
		0.925f,0.5f,0.0f,   1.0f,   0.0f,   1.0f,
		1.0f,-0.4f,0.0f,    1.0f,   0.0f,   1.0f,

		0.85f,-0.4f,0.0f,   1.0f,   0.0f,   1.0f,
		0.85f,0.5f,0.0f,    1.0f,   0.0f,   1.0f,
		0.925f,0.5f,0.0f,   1.0f,   0.0f,   1.0f,

		0.925f,0.5f,0.0f,   1.0f,   0.0f,   1.0f,
		1.0f,0.5f,0.0f,     1.0f,   0.0f,   1.0f,
		1.0f,-0.4f,0.0f,    1.0f,   0.0f,   1.0f,

		//
		0.6f,-0.7f,0.0f,    1.0f,   0.0f,   1.0f,
		0.725f,-0.4f,0.0f,  1.0f,   0.0f,   1.0f,
		0.85f,-0.7f,0.0f,   1.0f,   0.0f,   1.0f,

		0.6f,-0.7f, 0.0f,   1.0f,   0.0f,   1.0f,
		0.6f,-0.4f,0.0f,    1.0f,   0.0f,   1.0f,
		0.725f,-0.4f,0.0f,  1.0f,   0.0f,   1.0f,
		
		0.725f,-0.4f,0.0f,  1.0f,   0.0f,   1.0f,
		0.85f,-0.4f,0.0f,   1.0f,   0.0f,   1.0f,
		0.85f,-0.7f,0.0f,   1.0f,   0.0f,   1.0f,
	};

	MeshColor* letras3 = new MeshColor();
	letras3->CreateMeshColor(vertices_D, 216);
	meshColorList.push_back(letras3);
	

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		
	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);

}

void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para ROJO
	shader1->CreateFromFiles(vShaderR, fShaderR);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader(); //shader para VERDE
	shader2->CreateFromFiles(vShaderV, fShaderV);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader(); //shader para AZUL
	shader3->CreateFromFiles(vShaderA, fShaderA);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader(); //shader para CAFE
	shader4->CreateFromFiles(vShaderC, fShaderC);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader(); //shader para VERDE OSCURO
	shader5->CreateFromFiles(vShaderVO, fShaderVO);
	shaderList.push_back(*shader5);

	/*Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);*/
}


int main()
{
	mainWindow = Window(800, 800);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f); //left right top bottom near far. No tiene perspectiva
	//glm::mat4 projection = glm::perspective(glm::radians(45.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f); //Rango de apertura de 60 rad (Angulo de vision del ojo)
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
													
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		/*---------INICIALES "JAD"---------

		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		// 
		//--------LLAMANDO A J--------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f)); //Traslacion inicial para que se vean los vértices
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();

		//--------LLAMANDO A A--------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f)); //Traslacion inicial para que se vean los vértices
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();

		//--------LLAMANDO A D--------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f)); //Traslacion inicial para que se vean los vértices
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();
		*/


		//---------CASA 3D---------
		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		shaderList[2].useShader(); 
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.3; //Cambia la velocidad de rotacion
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.7f, -1.0f)); //piramide azul
		model = glm::scale(model, glm::vec3(1.1f, 0.5f, 0.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Llamando al cubo rojo
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(0.0f, -0.05f, -1.0f)); //cubo rojo
		model = glm::scale(model, glm::vec3(0.9f, 1.0f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA 
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Llamando a los cubos verdes
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.2f, 0.2f, -0.9f)); //cubo verde1
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA 
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.2f, 0.2f, -0.9f)); //cubo verde2
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA 
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -0.9f)); //cubo verde3
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA 
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.45f, -0.9f)); //cubo cafe1
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA 
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.15f, -1.0f)); //piramide verde oscura1
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.45f, -0.9f)); //cubo cafe2
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA 
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.15f, -1.0f)); //piramide verde oscura2
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/
