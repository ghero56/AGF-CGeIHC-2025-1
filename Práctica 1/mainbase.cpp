#include <stdio.h>
#include <glew.h>
#include <glfw3.h>
#include <iostream>

//Dimensiones de la ventana
const int WIDTH = 1280, HEIGHT = 720;
// se puede cambiar en tiempo de ejecución

// esto es extra
using namespace std;

int main() {
	
	//Inicialización de GLFW
	if (!glfwInit()) {
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	
	// Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// ya que soporta vulkan, entre otras APIs
	
	// CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(
							// resolución
								WIDTH, 
								HEIGHT, 
							// opciones extra
								"Primer ventana", // titulo
								NULL, // monitor a mostrar
								NULL // pantalla compartida
							);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}

	// Obtener tamaño de Buffer (tamaño asignado en memoria para almacenar los datos)
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	// asignar el contexto de ventana actual
	glfwMakeContextCurrent(mainWindow);

	// permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	// Asignar Viewport con espacios en X Y y Z
	glViewport(0, 0, BufferWidth, BufferHeight);
	printf("Version de Opengl: %s \n",glGetString(GL_VERSION));
	printf("Marca: %s \n", glGetString(GL_VENDOR));
	printf("Renderer: %s \n", glGetString(GL_RENDERER));
	printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	// propio
	float R = 1.0f, G = 1.0f, B = 1.0f, A = 1.0f;
	int fps = 0;

	// Loop mientras no se cierra la ventana
	// El tiempo del while es de acuerdo al reloj
	// del cpu, lo cual debería ser a la GPU
	while (!glfwWindowShouldClose(mainWindow))
	{
		// propio
		fps++;
		if (fps == 60) {
			cout << fps;
			fps = 0;
			if (G > 0.1f) G -= 0.1f;
			if (G <= 0.1f) R -= 0.1f;
			if (R <= 0.1f) B -= 0.1f;
			if (B <= 0.1f) R = G = B = A;
		}
		
		//Recibir eventos del usuario
		glfwPollEvents();

		// Limpiar la ventana
		// funciona con RGB
		glClearColor(R,G,B,A);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);
	}


	return 0;
}