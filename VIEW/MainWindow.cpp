#include "MainWindow.h"

MainWindow::MainWindow(CommandHandler* cmdhdl)
    : is_init(false), m_window(nullptr),
      m_renderer(cmdhdl->GetRotateController()), 
      m_eventhandler(cmdhdl)
{
}

MainWindow::~MainWindow()
{
}

bool MainWindow::init()
{
    // Initialize library
    if(!glfwInit()) return false;
    // Enable multi-sampling
    glfwWindowHint(GLFW_SAMPLES, 9);
    // Create a windowed mode window and its OpenGL context
    m_window = glfwCreateWindow(WIDTH, HEIGHT, "Rubic Cube Simulator", NULL, NULL);
    if (!m_window) {
        glfwTerminate();
        return false;
    }
    // Make the window's context current
    glfwMakeContextCurrent(m_window);
    // Set window user pointer to the event handler
    glfwSetWindowUserPointer(m_window, &m_eventhandler);
    // Initialize event handlers
    // Bind mouse button callback
    auto MouseCallBack =
            [](GLFWwindow *window, int button, int action, int mods) {
                EventHandler* pEventHandler = reinterpret_cast<EventHandler*>(glfwGetWindowUserPointer(window));
                pEventHandler->mouseButtonCallback(window, button, action, mods);
            };
    glfwSetMouseButtonCallback(m_window, MouseCallBack);
    // Bind keyboard callback
    auto KeyBoardCallBack =
            [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                EventHandler* pEventHandler = reinterpret_cast<EventHandler*>(glfwGetWindowUserPointer(window));
                pEventHandler->keyboardCallback(window, key, scancode, action, mods);
            };
    glfwSetKeyCallback(m_window, KeyBoardCallBack);
    // Bind character callback
    auto CharCallBack =
            [](GLFWwindow *window, unsigned int codepoint) {
                EventHandler* pEventHandler = reinterpret_cast<EventHandler*>(glfwGetWindowUserPointer(window));
                pEventHandler->characterCallback(window, codepoint);
            };
    glfwSetCharCallback(m_window, CharCallBack);
    // Initialize OPENGL
    initGL();
    // Set swap interval
    glfwSwapInterval(1);
    m_eventhandler.SetWindow(m_window);
    m_eventhandler.SetRenderer(&m_renderer);
    is_init = true;
    return true;
}

void MainWindow::show()
{
    // initialization failed
    if(!is_init && !init()) return;
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(m_window)) {
        m_renderer.GetRotateController()->nextFrame();
        m_renderer.render();

        // Swap front and back buffers
        glfwSwapBuffers(m_window);

        // Poll for and process events
        glfwPollEvents();

        m_eventhandler.keyboardScan();
        m_eventhandler.mouseMove();
    }

    glfwTerminate();
}

void MainWindow::createViewMatrix(float eyeX, float eyeY, float eyeZ,
                      float centerX, float centerY, float centerZ,
                      float upX, float upY, float upZ,
                      float* viewMatrix)
{
    // Calculate the forward vector
    float f[3] = {
            centerX - eyeX,
            centerY - eyeY,
            centerZ - eyeZ
    };
    float fLength = std::sqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);

    // Normalize the forward vector
    float fNormalized[3] = {
            f[0] / fLength,
            f[1] / fLength,
            f[2] / fLength
    };

    // Calculate the right vector
    float u[3] = { upX, upY, upZ };

    float s[3] = {
            fNormalized[1] * u[2] - fNormalized[2] * u[1],
            fNormalized[2] * u[0] - fNormalized[0] * u[2],
            fNormalized[0] * u[1] - fNormalized[1] * u[0]
    };
    float sLength = std::sqrt(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);

    // Normalize the right vector
    float sNormalized[3] = {
            s[0] / sLength,
            s[1] / sLength,
            s[2] / sLength
    };

    // Calculate the up vector
    float uNormalized[3] = {
            sNormalized[1] * fNormalized[2] - sNormalized[2] * fNormalized[1],
            sNormalized[2] * fNormalized[0] - sNormalized[0] * fNormalized[2],
            sNormalized[0] * fNormalized[1] - sNormalized[1] * fNormalized[0]
    };

    // Build the view matrix
    viewMatrix[0] = sNormalized[0];
    viewMatrix[1] = uNormalized[0];
    viewMatrix[2] = -fNormalized[0];
    viewMatrix[3] = 0.0f;

    viewMatrix[4] = sNormalized[1];
    viewMatrix[5] = uNormalized[1];
    viewMatrix[6] = -fNormalized[1];
    viewMatrix[7] = 0.0f;

    viewMatrix[8] = sNormalized[2];
    viewMatrix[9] = uNormalized[2];
    viewMatrix[10] = -fNormalized[2];
    viewMatrix[11] = 0.0f;

    viewMatrix[12] = -(sNormalized[0] * eyeX + sNormalized[1] * eyeY + sNormalized[2] * eyeZ);
    viewMatrix[13] = -(uNormalized[0] * eyeX + uNormalized[1] * eyeY + uNormalized[2] * eyeZ);
    viewMatrix[14] = fNormalized[0] * eyeX + fNormalized[1] * eyeY + fNormalized[2] * eyeZ;
    viewMatrix[15] = 1.0f;
}

void MainWindow::initGL()
{
    // init OpenGL
    glEnable(GL_DEPTH_TEST);// Enable depth testing for 3D rendering
    glDepthFunc(GL_LESS); // Specify the depth comparison function
    glPointSize(8);// Set the size of rendered points
    glLineWidth(2);// Set the width of rendered lines
    glEnable(GL_POINT_SMOOTH);// Enable point smoothing for smoother point rendering
    glEnable(GL_LINE_SMOOTH);// Enable line smoothing for smoother line rendering
    glEnable(GL_POLYGON_SMOOTH);// Enable polygon smoothing for smoother polygon rendering
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);// Enable blending of colors
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// Specify the blending function
    glViewport(0, 0, WIDTH, HEIGHT);// Set the viewport size
    glMatrixMode(GL_PROJECTION);// Set the matrix mode to projection
    glLoadIdentity();// Load the identity matrix
    GLdouble rFov = 45.0f * 3.14159265 / 180.0;// Calculate the vertical field of view in radians
    glFrustum( -0.1f * tan( rFov / 2.0 ) * (float)(WIDTH) / (float)(HEIGHT),
               0.1f * tan( rFov / 2.0 ) * (float)(WIDTH) / (float)(HEIGHT),
               -0.1f * tan( rFov / 2.0 ),
               0.1f * tan( rFov / 2.0 ),
               0.1f, 1000.0f );// Set the frustum perspective projection
    glMatrixMode(GL_MODELVIEW);// Set the matrix mode to modelview
    glLoadIdentity();// Load the identity matrix
    // gluLookAt(0.0f, 0.0f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    GLfloat ff[16];
    createViewMatrix(0.0f, 0.0f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, ff);
    glLoadMatrixf(ff);
}
