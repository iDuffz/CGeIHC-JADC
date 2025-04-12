//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture dado8Texture;
//lampara
Model Lamp_Text;

Model Kitt_M;
Model Llanta_M;
Model Nissan_Cofre;
Model Microondas;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
PointLight pointLightsM[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotLightsD[MAX_SPOT_LIGHTS];
SpotLight spotLightsR[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};

	unsigned int dado8_indices[] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23
	};

	GLfloat dado8_vertices[]{
		//x			y			z			S		T			NX		NY		NZ
	//Cara superior frontal izquierda
	-0.5f,		0.0f,		0.5f,		0.204f,   0.0f,		0.0f,	0.0f,	-1.0f,	//0
	0.5f,		0.0f,		0.5f,		0.59f,	0.0f,		0.0f,	0.0f,	-1.0f,	//1
	0.0f,		0.6f,		0.0f,		0.4f,	0.325f,		0.0f,	0.0f,	-1.0f,	//2
	//Cara superior frontal derecha
	-0.5f,		0.0f,		-0.5f,		0.608f,   0.0f,		0.0f,	0.0f,	1.0f,	//3
	0.5f,		0.0f,		-0.5f,		0.99f,	0.0f,		0.0f,	0.0f,	1.0f,	//4
	0.0f,		0.6f,		0.0f,		0.803f,	0.322f,		0.0f,	0.0f,	1.0f,	//5
	//Cara superior trasera derecha
	0.5f,		0.0f,		0.5f,		0.402f,   0.33f,	-1.0f,	0.0f,	0.0f,	//6
	0.5f,		0.0f,		-0.5f,		0.8f,	0.33f,		-1.0f,	0.0f,	0.0f,	//7
	0.0f,		0.6f,		0.0f,		0.6f,	0.66f,		-1.0f,	0.0f,	0.0f,	//8
	//Cara superior trasera izquierda
	-0.5f,		0.0f,		0.5f,		0.59f,	0.667f,		1.0f,	0.0f,	0.0f,	//9
	-0.5f,		0.0f,		-0.5f,		0.2f,   0.667f,		1.0f,	0.0f,	0.0f,	//10 
	0.0f,		0.6f,		0.0f,		0.4f,	0.99f,		1.0f,	0.0f,	0.0f,	//11

	//Cara inferior frontal izquierda
	-0.5f,		0.0f,		0.5f,		0.4f,   0.326f,		0.0f,	0.0f,	-1.0f,	//12
	0.5f,		0.0f,		0.5f,		0.798f,	0.326f,		0.0f,	0.0f,	-1.0f,	//13
	0.0f,		-0.6f,		0.0f,		0.602f,	0.0f,		0.0f,	0.0f,	-1.0f,	//14
	//Cara inferior frontal derecha	
	-0.5f,		0.0f,		-0.5f,		0.202f,   0.66f,	0.0f,	0.0f,	1.0f,	//15
	0.5f,		0.0f,		-0.5f,		0.4f,	0.34f,		0.0f,	0.0f,	1.0f,	//16
	0.0f,		-0.6f,		0.0f,		0.59f,	0.66f,		0.0f,	0.0f,	1.0f,	//17 
	//Cara inferior trasera derecha
	0.5f,		0.0f,		0.5f,		0.004f,   0.99f,	-1.0f,	0.0f,	0.0f,	//18
	0.5f,		0.0f,		-0.5f,		0.393f,	0.99f,		-1.0f,	0.0f,	0.0f,	//19
	0.0f,		-0.6f,		0.0f,		0.198f,	0.673f,		-1.0f,	0.0f,	0.0f,	//20
	//Cara inferior trasera izquierda		
	-0.5f,		0.0f,		0.5f,		0.796f,	0.99f,		1.0f,	0.0f,	0.0f,	//21
	-0.5f,		0.0f,		-0.5f,		0.407f,   0.99f,  	1.0f,	0.0f,	0.0f,	//22 
	0.0f,		-0.6f,		0.0f,		0.601f,	0.673f,		1.0f,	0.0f,	0.0f,	//23

	};


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh* dado8 = new Mesh();
	dado8->CreateMesh(dado8_vertices, dado8_indices, 190, 30);
	meshList.push_back(dado8);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();

	//lampara
	Lamp_Text = Model();
	Lamp_Text.LoadModel("Models/lampara_texturizada.obj");

	//Carro
	Kitt_M = Model();
	Kitt_M.LoadModel("Models/Nissan_350Z_chasis.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/Nissan_350Z_RuedaPilot.obj");
	Nissan_Cofre = Model();
	Nissan_Cofre.LoadModel("Models/Nissan_350Z_Cofre.obj");

	//Microondas
	Microondas = Model();
	Microondas.LoadModel("Models/microondas.obj");

	//Dado
	dado8Texture = Texture("Textures/Dado8Texture.png");
	dado8Texture.LoadTextureA();

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 
		0.4f, 0.3f, 
		0.0f, 0.0f, 1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;

	//Declaración de segunda luz puntual
	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,	//Color de la luz (blanca)
		0.5f, 1.0f,			//Radiacion y saturacion
		-0.9f, 2.5f, 0.0f,	//Posicion
		0.3f, 0.2f, 0.1f);	//Ecuacion de segundo grado
	pointLightCount++;

	pointLights[1] = PointLight(1.0f, 1.0f, 0.0f,	//Color de la luz (amarilla)
		0.1f, 0.1f,			//Radiacion y saturacion
		0.0f, 0.4f, 2.8f,	//Posicion
		0.3f, 0.2f, 0.1f);	//Ecuacion de segundo grado
	pointLightCount++;

	unsigned int pointLightCountM = 0;

	pointLightsM[0] = pointLights[1];
	pointLightCountM++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(0.0f, 0.0f, 0.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f); //ángulo
	spotLightCount++;

	//luz fija color amarilla
	spotLights[1] = SpotLight(1.0f, 1.0f, 0.0f,
		0.5f, 0.3f,
		0.0f, 0.0f, 0.0f, //pos
		0.0f, -1.0f, 0.0f, //dir
		1.0f, 0.0f, 0.0f,
		25.0f);//ángulo
	spotLightCount++;

	//luz del cofre roja
	spotLights[2] = SpotLight(1.0f, 0.0f, 0.0f,
		1.0f, 2.0f,
		0.0f, 0.0f, 0.0f, //pos
		-1.0f, 0.0f, 0.0f, //dir
		1.0f, 0.0f, 0.0f,
		50.0f);//ángulo
	spotLightCount++;

	unsigned int spotLightCountD = 0;

	//luz para enfrente azul
	spotLightsD[0] = SpotLight(0.0f, 0.0f, 1.0f,
		0.5f, 0.3f,
		0.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		25.0f); //ángulo
	spotLightCountD++;

	unsigned int spotLightCountR = 0;

	//luz para atras blanca
	spotLightsR[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.3f,
		0.0f, 0.0f, 0.0f, //pos
		1.0f, 0.0f, 0.0f, //dir
		1.0f, 0.0f, 0.0f,
		25.0f);//ángulo
	spotLightCountR++;


	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());



		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		if (mainWindow.getinterruptor() == true && mainWindow.getinterruptor3() == true) {
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		}
		else {
			if (mainWindow.getinterruptor() == true && mainWindow.getinterruptor3() == false) {
				shaderList[0].SetPointLights(pointLights, 1);
			}
			else {
				if (mainWindow.getinterruptor() == false && mainWindow.getinterruptor3() == true) {
					shaderList[0].SetPointLights(pointLightsM, pointLightCountM);
				}
				else {
					shaderList[0].SetPointLights(pointLights, 0);
				}
			}
		}

		if (mainWindow.getinterruptor2() == 1) {
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
		}
		else if (mainWindow.getinterruptor2() == 2) {
			shaderList[0].SetSpotLights(spotLightsR, spotLightCountR);
		}
		else if (mainWindow.getinterruptor2() == 3) {
			shaderList[0].SetSpotLights(spotLightsD, spotLightCountD);
		}
		

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelaux2(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//LAMPARA DE PARQUE
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lamp_Text.RenderModel();

		//Microondas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Microondas.RenderModel();

		//Instancia del coche 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex(), 0.87f, -3.0f));
		spotLightsD[0].SetPos(glm::vec3(-2.0f + mainWindow.getmuevex(), 1.0f, -3.5f));
		spotLightsR[0].SetPos(glm::vec3(2.5f + mainWindow.getmuevex(), 0.5f, -3.0f));
		modelaux = model;
		modelaux2 = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Kitt_M.RenderModel();

		//Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.15f, -1.0f, 1.8f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		color = glm::vec3(0.5f, 0.5f, 0.5f);//llanta con color gris
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(3.05f, -1.0f, 1.8f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.15f, -1.0f, -1.85f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(3.05f, -1.0f, -1.85f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Cofre
		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.95f, 0.5f, -0.03f));
		spotLights[2].SetPos(glm::vec3(-3.0f + mainWindow.getarticulacion() + mainWindow.getmuevex(), 0.8f + mainWindow.getarticulacion(), -3.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion()), glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(0.7f, 0.7f, 0.7f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Nissan_Cofre.RenderModel();

		//Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, 1.0f, -10.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		

		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}