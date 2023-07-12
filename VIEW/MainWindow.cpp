#include "MainWindow.h"

MainWindow::MainWindow()
: m_pWindow(nullptr),
  m_pRenderer(std::make_shared<Renderer>(this)),
  m_pEventCallback(std::make_shared<EventCallback>(this)),
  m_pRotAni(std::make_shared<RotAni>(this)),
  m_pVS(std::make_shared<MainWindowSink>(this))
{
}

MainWindow::~MainWindow()
{
}

std::shared_ptr<INotification> MainWindow::getSink()
{
    return m_pVS;
}

void MainWindow::setCube(std::shared_ptr<cubes_t> cubes)
{
    m_pCubeData = cubes;
}

void MainWindow::setRSteps(std::shared_ptr<CubeSteps> steps)
{
    m_pRSteps = steps;
}

void MainWindow::setResetHandler(std::shared_ptr<ICommandBase> reset)
{
    m_pResetHandler = reset;
}

void MainWindow::setRandomHandler(std::shared_ptr<ICommandBase> random)
{
    m_pRandomHandler = random;
}

void MainWindow::setRotateHandler(std::shared_ptr<ICommandBase> rotate)
{
    m_pRotateHandler = rotate;
}

void MainWindow::setSaveHandler(std::shared_ptr<ICommandBase> save)
{
    m_pSaveHandler = save;
}

void MainWindow::setLoadHandler(std::shared_ptr<ICommandBase> load)
{
    m_pLoadHandler = load;
}

void MainWindow::setSolveHandler(std::shared_ptr<ICommandBase> solve)
{
    m_pSolveHandler = solve;
}

void MainWindow::setStopHandler(std::shared_ptr<ICommandBase> stop)
{
    m_pStopHandler = stop;
}

void MainWindow::setRotEndHandler(std::shared_ptr<ICommandBase> rotEnd)
{
    m_pRotEndHandler = rotEnd;
}

void MainWindow::show()
{
    // loop until the user closes the window
    while (!glfwWindowShouldClose(m_pWindow)) {
        // window state
        std::string stt(std::string(m_pRenderer->getRenderState(), '@'));
        std::string cmd(m_pEventCallback->getCommandBuffer());
        std::string title(stt + "=Rubic Cube Simulator=" + cmd);
        glfwSetWindowTitle(m_pWindow, title.c_str());
        // get next frame, may do nothing
        m_pRotAni->nextFrame();
        // render, may do nothing
        m_pRenderer->render();
        // poll for and process events
        glfwPollEvents();

        m_pEventCallback->keyboardScan();
        m_pEventCallback->mouseMove();
    }
    glfwTerminate();
}

bool MainWindow::init()
{
    // initialize library
    if(!glfwInit()) return false;
    // enable multi-sampling
    glfwWindowHint(GLFW_SAMPLES, 9);
    // create a windowed mode window and its OpenGL context
    m_pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Rubic Cube Simulator", NULL, NULL);
    if (!m_pWindow) {
        glfwTerminate();
        return false;
    }
    // make the window's context current
    glfwMakeContextCurrent(m_pWindow);
    // set window user pointer to the event handler
    glfwSetWindowUserPointer(m_pWindow, m_pEventCallback.get());
    // initialize event callbacks
    // bind mouse button callback
    auto MouseCallBack =
            [](GLFWwindow *window, int button, int action, int mods) {
                EventCallback* pEventCallback = reinterpret_cast<EventCallback*>(glfwGetWindowUserPointer(window));
                pEventCallback->mouseButtonCallback(window, button, action, mods);
            };
    glfwSetMouseButtonCallback(m_pWindow, MouseCallBack);
    // bind keyboard callback
    auto KeyBoardCallBack =
            [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                EventCallback* pEventCallback = reinterpret_cast<EventCallback*>(glfwGetWindowUserPointer(window));
                pEventCallback->keyboardCallback(window, key, scancode, action, mods);
            };
    glfwSetKeyCallback(m_pWindow, KeyBoardCallBack);
    // bind character callback
    auto CharCallBack =
            [](GLFWwindow *window, unsigned int codepoint) {
                EventCallback* pEventCallback = reinterpret_cast<EventCallback*>(glfwGetWindowUserPointer(window));
                pEventCallback->characterCallback(window, codepoint);
            };
    glfwSetCharCallback(m_pWindow, CharCallBack);
    // initialize OPENGL
    initGL();
    // set swap interval
    glfwSwapInterval(0);
    return true;
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

    // calculate the up vector
    float uNormalized[3] = {
            sNormalized[1] * fNormalized[2] - sNormalized[2] * fNormalized[1],
            sNormalized[2] * fNormalized[0] - sNormalized[0] * fNormalized[2],
            sNormalized[0] * fNormalized[1] - sNormalized[1] * fNormalized[0]
    };

    // build the view matrix
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
    glEnable(GL_DEPTH_TEST); // enable depth testing for 3D rendering
    glDepthFunc(GL_LESS); // specify the depth comparison function
    glPointSize(8); // set the size of rendered points
    glLineWidth(2); // set the width of rendered lines
    glEnable(GL_POINT_SMOOTH); // enable point smoothing for smoother point rendering
    glEnable(GL_LINE_SMOOTH); // enable line smoothing for smoother line rendering
    glEnable(GL_POLYGON_SMOOTH); // enable polygon smoothing for smoother polygon rendering
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // make round points, not square points
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // antialias the lines
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND); // enable blending of colors
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // specify the blending function
    glViewport(0, 0, WIDTH, HEIGHT); // set the viewport size
    glMatrixMode(GL_PROJECTION); // set the matrix mode to projection
    glLoadIdentity(); // load the identity matrix
    GLdouble rFov = 45.0f * 3.14159265 / 180.0; // calculate the vertical field of view in radians
    glFrustum( -0.1f * tan( rFov / 2.0 ) * (float)(WIDTH) / (float)(HEIGHT),
               0.1f * tan( rFov / 2.0 ) * (float)(WIDTH) / (float)(HEIGHT),
               -0.1f * tan( rFov / 2.0 ),
               0.1f * tan( rFov / 2.0 ),
               0.1f, 1000.0f ); // set the frustum perspective projection
    glMatrixMode(GL_MODELVIEW); // set the matrix mode to modelview
    glLoadIdentity(); // load the identity matrix
    GLfloat ff[16];
    createViewMatrix(0.0f, 0.0f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, ff);
    glLoadMatrixf(ff);
}
