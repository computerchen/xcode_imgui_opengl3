//#include <GLFW/glfw3.h>
//
//int main(int argc, const char * argv[]) {
//    GLFWwindow* win;
//    if(!glfwInit()){
//        return -1;
//    }
//    win = glfwCreateWindow(640, 480, "OpenGL Base Project", NULL, NULL);
//    if(!win)
//    {
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(win);
//    while(!glfwWindowShouldClose(win)){
//        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//        glBegin(GL_TRIANGLES);
//        {
//            glColor3f(1.0,0.0,0.0);
//            glVertex2f(0, .5);
//            glColor3f(0.0,1.0,0.0);
//            glVertex2f(-.5,-.5);
//            glColor3f(0.0, 0.0, 1.0);
//            glVertex2f(.5, -.5);
//        }
//        glEnd();
//        glfwSwapBuffers(win);
//        glfwPollEvents();
//    }
//    glfwTerminate();
//    return 0;
//}

#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// ImGUI includes
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"


// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main() {
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);


    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(window, true);

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    bool show_test_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        ImGui_ImplGlfwGL3_NewFrame();

        // 1. Show a simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
        {
            static float f = 0.0f;
            ImGui::Text("Hello, chen!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("Test Window")) show_test_window ^= 1;
            if (ImGui::Button("Another Window")) show_another_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }


        // 2. Show another simple window, this time using an explicit Begin/End pair
        if (show_another_window) {
            ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello");
            ImGui::End();
        }

        // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
        if (show_test_window) {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
            ImGui::ShowTestWindow(&show_test_window);
        }

        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();

        // 检查事件，调用相应的回调函数，如下文的key_callback函数
        glfwPollEvents();

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }


    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

