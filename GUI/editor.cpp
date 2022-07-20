#include "editor.h"
#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#endif
#include "iostream"
#include "shaderGlobal.h"
#include "transform.h"
void Editor::genTextureInit() {
    glGenTextures(1, &raw_image_texture);
    glBindTexture(GL_TEXTURE_2D, raw_image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif

}
bool Editor::loadTextureFromMemory(){

    // Load from file
    raw_image_width = ShaderGlobal::current_drawer->get_width();
    raw_image_height = ShaderGlobal::current_drawer->get_height();
    image_data = ShaderGlobal::current_drawer -> data;

    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image_data);

    image_texture = raw_image_texture;
    image_width = raw_image_width;
    image_height = raw_image_height;
    return true;
}
void Editor::nextFrame() {
    //render next frame.
    TGAColor white = TGAColor(255,255,255,255);
    std::fill(zbuffer,zbuffer+image_width*image_height,1e18);
    memset(drawer->data,0,sizeof(drawer));
    for(int i = 0;i < image_width;i++){
        for(int j = 0;j < image_height;j++)drawer -> set(i,j,white);
    }
    ShaderGlobal::model = model;
    Mat4f M_model = Mat<4,float>::I();
    M_model[0][0] = M_model[1][1] = M_model[2][2] = 1000;//multiply .obj's coordinate by 500
    M_model[0][3] = 1000,M_model[1][3] = 1000;
    M_model[2][3] = -1000;
    M_model[3][3] = 1;
    int near = -300,far = -10000;
    //camera
    Vec3f t(0,1,0);//Up direction
    Mat4f M_view = ViewTrans(camera_position, view_center, t);
    Mat4f M_perse = PerspTrans(0,image_width,0,image_height,far,near);
    Mat4f M_viewport = ViewportTrans(image_width,image_height);
    Mat4f M = M_viewport * M_view;
    ShaderGlobal::M = M;
    //    Matrix<float> M = M_viewport * M_perse * M_view * M_model;
//    cout << M_view << endl;
//    cout << M_perse << endl;
//    cout << M_viewport << endl;
//    cout << M;
    Shader * shader = new Bling_Phong();
    ShaderGlobal::light_intensity = 2.3e8;
    ShaderGlobal::light_position = Vec3f(10000,3000,10000);
    for (int i=0; i<model->nfaces(); i++) {
        shader -> vertex(i);
        drawer -> Triangle(i,shader,zbuffer);
    }
    drawer -> flip_vertically(); // i want to have the origin at the left bottom corner of the image
//    drawer -> write_tga_file("output.tga");
    ShaderGlobal::current_drawer = drawer;
}

int Editor::run() {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    bool show_image = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    genTextureInit();
    nextFrame();
  // Main loop

    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if(show_image){
            ImGui::Begin("Render result");
            ImGui::Text("Texture pointer = %p", image_texture);
            ImGui::Text("size = %d x %d", image_width, image_height);
            ImGui::SliderFloat("View Position x", &view_center.x, 0.0f, 1.0f);
            ImGui::SliderFloat("View Position y", &view_center.y, 0.0f, 1.0f);
            ImGui::SliderFloat("View Position z", &view_center.z, 0.0f, 1.0f);
            ImGui::SliderFloat("Camera Position x", &camera_position.x, -1e5f, 1e5f);
            ImGui::SliderFloat("Camera Position y", &camera_position.y, -1e5f, 1e5f);
            ImGui::SliderFloat("Camera Position z", &camera_position.z, -1e5f, 1e5f);
//            view_center.normalize();
            nextFrame();
            loadTextureFromMemory();
            ImGui::Image((void*)(intptr_t)image_texture, ImVec2(image_width, image_height));
            ImGui::End();
        }

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}