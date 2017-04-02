#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Espacio para las variables globales de la ventana
float gl_ancho = 2.0, gl_alto = 2.0, gl_cerca = 2.0, gl_lejos = 10.0; //cambiar seg�n el proyecto
int w_ancho = 500, w_alto = 500;


// Espacio para otras variables globales
float angulo = 0.0f, paso = 1.0f;
int pasos_segundo = 20;

// Espacio para la declaración de funciones
void InitGlew();

void InitGL();

void Display();

void ReshapeSize(int ancho, int alto);

void Timer(int v);

//main
int main(int argc, char *argv[]) {

    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(w_ancho, w_alto);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("OpenGL Practica 5, tarea 1");
    InitGlew(); // despues de crear la primera ventana
    InitGL();
    glutDisplayFunc(Display); // registra la funcion de rendering
    glutReshapeFunc(ReshapeSize);
    glutTimerFunc(100, Timer, 0);

    glutMainLoop(); // bucle principal

    return 0;
}

void Timer(int v) {
    angulo += paso;
    if (angulo > 360) angulo -= 360;
    glutPostRedisplay();
    glutTimerFunc((unsigned int) (1000 / pasos_segundo), Timer, v);
}

void InitGlew() {

    // para poder utilizar trasnparentemente todas las extensiones de OpenGL

    GLenum glew_init = glewInit();
    if (glew_init != GLEW_OK) {
        // Problem: glewInit failed, something is seriously wrong.
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_init));
    } else
        fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void InitGL() {

    if (gl_ancho / w_ancho != gl_alto / w_alto) {
        fprintf(stderr, "La relación de aspecto no es correcta\n");
    }

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    // para cambiar el criterio de lo que se ve. LESS es el de defecto: se ve lo que tiene menor profundidad
    //glDepthFunc(GL_LESS);
    // TO DO

    //glViewport(0, 0, w_ancho, w_alto); // por defecto ya se establece así en la inicialización
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-gl_ancho / 2.0, gl_ancho / 2.0, -gl_alto / 2.0, gl_alto / 2.0, gl_cerca, gl_lejos); // espacio de trabajo
    glMatrixMode(GL_MODELVIEW); // las futuras operaciones se refieren a las coordenadas de los modelos
}


// cambio de dimensiones de la ventana, manteniendo la dimension de los objetos
void ReshapeSize(int ancho, int alto) {

    float dx = gl_ancho;
    float dy = gl_alto;

    dx *= (float) ancho / (float) w_ancho;
    dy *= (float) alto / (float) w_alto;

    glViewport(0, 0, ancho, alto); // utiliza la totalidad de la ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-dx / 2.0, dx / 2.0, -dy / 2.0, dy / 2.0, gl_cerca, gl_lejos); // espacio de trabajo
    glMatrixMode(GL_MODELVIEW); // futuras operaciones se refieren a modelos
    glutPostRedisplay();
}

// función de gestion de ventana
void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // a partir de aquí empieza a poner modelos y transformarlos.

    // Se traslada el eje de coordenadas hacia el centro del frustum, para que las cosas que se coloquen se puedan ver
    glTranslatef(0.0f, 0.0f, -5.0f);
    //Se rota el eje de coordenadas por el eje x para que se vean los objetos un poco "desde arriba"
    glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
    //Se rota el eje de coordenadas por el eje z para crear la sensación de rotación
    glRotatef(angulo, 0.0f, 0.0f, 1.0f);
    //Se dibuja la esfera
    glutWireSphere(2.0f, 20, 20);

    glFlush(); // actualiza el framebuffer
    glutSwapBuffers(); // en caso de animacion
}