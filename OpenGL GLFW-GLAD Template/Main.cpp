//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <iostream>

#include "Header/Graphics.h"

//Has an example of using the Window2D class
void example2D();
//Has an example of using the Window3D class
void example3D();
//This is for example3D();
void drawCube(const float width, const float length, const float height,
              const float xpos, const float ypos, const float zpos,
              const float r, const float g, const float b, const float a);

int main()
{
    //Has an example of using the Window2D class
    //example2D();

    //Has an example of using the Window3D class
    example3D();

    return 0;
}

/*
            EXAMPLE OF 2D WINDOW
*/
void example2D()
{
    ContextSettings settings;
    settings.decorated = true;
    settings.transparent = true;

    //Create's a window with 300x300 size, titled "Window"
    Window2D window(300, 300, "Window", settings);
    glfwSwapInterval(1);

    //Create a 2D Viewport that has a size of 300x300
    //There is an optional parameter for the position of the view
    View v1(Vec2f(300, 300));
    //Sets the viewport that will be used
    window.setView(&v1);

    //Mouse... Nothing more
    Mouse m;

    while (window.isOpen())
    {
        //EVENTS
        Events event;
        while (window.poll_events(event))
        {
            switch (event.type)
            {
            case Events::EventType::KEY:
                if (event.keys.action == GLFW_PRESS)
                {
                    switch (event.keys.key)
                    {
                    case GLFW_KEY_ESCAPE:
                        window.close();
                        break;
                    }
                }
                break;
            }
        }

        //Clear all drawings that were made to the window
        window.clear(10, 10, 10, 0);

        /* Example Stuff */
        float xpos, ypos;
        xpos = sin(glfwGetTime());
        ypos = cos(glfwGetTime());

        Vec2i pos, size;
        pos = window.getPosition();
        size = window.getSize();
        Vec2i windowCenterPos = Vec2i(pos.x + (size.x / 2), pos.y + (size.y / 2));
        window.move((m.getPosition().x - windowCenterPos.x) / 10 + (xpos * (size.x / 20)),
            (m.getPosition().y - windowCenterPos.y) / 10 + (ypos * (size.y / 20)));

        glBegin(GL_QUADS);
        glColor3d(abs(xpos) / 1.f, abs(ypos) / 1.f, abs(xpos + ypos) / 1.f);
        glVertex2f(100 + (xpos * 100), 100 + (ypos * 100));
        glVertex2f(100 + (xpos * 100), 200 + (ypos * 100));
        glVertex2f(200 + (xpos * 100), 200 + (ypos * 100));
        glVertex2f(200 + (xpos * 100), 100 + (ypos * 100));
        glEnd();
        /* Example Stuff */

        //Displays drawn elements to the window
        window.display();
    }
}


/*
            EXAMPLE OF 3D WINDOW
*/
void example3D()
{
    ContextSettings settings(24, 8, 0, 1, 2);
    settings.transparent = false;
    settings.decorated = true;

    //Create a 3D window with the size of 600x500 thats titled "Window"
    Window3D window(600, 500, "Window", settings);
    glfwSwapInterval(1);

    Vec2i windowSize = window.getSize();
    //Create a camera that has the size of the window
    //There is a optional parameter for the position
    Camera c1(Vec2f(windowSize.x, windowSize.y));
    //Enables depth to be drawn correctly
    c1.enableDepth();
    //Sets the view distance of the camera
    c1.setViewDistance(1, 500);
    //Sets the position of the camera
    c1.setPosition(glm::vec3(-30,0,5));
    //Sets the speed of the camera
    float camSpeed = 1;
    c1.setSpeed(camSpeed);

    //Sets the camera that will be used
    window.setCamera(&c1);

    //Enables transparent drawings
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    //Mouse movement for camera
    Mouse m;
    
    double mouse_lastx = m.getPosition().x;
    double mouse_lasty = m.getPosition().y;

    double last_frame = glfwGetTime();

    /* Lights */
    GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light0_position[] = { 0.0, 0.0, 1.0, 0.0 };
    glShadeModel(GL_SMOOTH);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    /* Lights */

    /* Fun stuff */
    float heightOfCube = 0.1f;
    float cubeAmplitude = 10.f;
    float cubeFrequency = 3.f;
    /* Fun stuff */

    while (window.isOpen())
    {
        //Set delta time
        double dt = glfwGetTime() - last_frame;
        last_frame = glfwGetTime();

        //This is so that the speed of the camera isnt dependent
        //on framerate
        c1.setDeltaTime(dt * 100);

        //EVENTS
        Events event;
        while (window.poll_events(event))
        {
            switch (event.type)
            {
            case Events::EventType::SIZE_CHANGED:
                c1.setSize(Vec2f(event.sizeChanged.width, event.sizeChanged.height));
                break;
            case Events::EventType::KEY:
                if (event.keys.action == GLFW_PRESS)
                {
                    switch (event.keys.key)
                    {
                    case GLFW_KEY_ESCAPE:
                        window.close();
                        break;
                    case GLFW_KEY_LEFT_CONTROL:
                        c1.setSpeed(camSpeed * 2);
                        break;
                    case GLFW_KEY_TAB:
                        c1.setSpeed(camSpeed / 2);
                        break;
                    }
                }
                else if (event.keys.action == GLFW_RELEASE)
                {
                    switch (event.keys.key)
                    {
                    case GLFW_KEY_LEFT_CONTROL:
                        c1.setSpeed(camSpeed);
                        break;
                    case GLFW_KEY_TAB:
                        c1.setSpeed(camSpeed);
                        break;
                    }
                }
                break;
            case Events::EventType::MOUSE_BUTTON:
                if (event.mouseButton.action == GLFW_PRESS)
                {
                    mouse_lastx = m.getPosition().x;
                    mouse_lasty = m.getPosition().y;
                }
                break;
                
            case Events::EventType::DROP:

                for (int i = 0; i < event.drop.count; i++)
                {
                    std::cout << event.drop.paths[i] << std::endl;
                }

                break;
            }
        }

        /* CAMERA MOVEMENT */
        if (glfwGetKey(window.getWindow(), GLFW_KEY_W))
            c1.move(Camera_Movement::FORWARD);
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_S))
            c1.move(Camera_Movement::BACKWARD);
        if (glfwGetKey(window.getWindow(), GLFW_KEY_A))
            c1.move(Camera_Movement::LEFT);
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_D))
            c1.move(Camera_Movement::RIGHT);
        if (glfwGetKey(window.getWindow(), GLFW_KEY_SPACE))
            c1.move(Camera_Movement::UP);
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT_SHIFT))
            c1.move(Camera_Movement::DOWN);
        /* CAMERA MOVEMENT */

        /* Fun Controls */
        if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT))
            heightOfCube -= 0.1f;
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_RIGHT))
            heightOfCube += 0.1f;
        if (glfwGetKey(window.getWindow(), GLFW_KEY_UP))
            cubeAmplitude += 1.f;
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_DOWN))
            cubeAmplitude -= 1.f;
        if (glfwGetKey(window.getWindow(), GLFW_KEY_Q))
            cubeFrequency += 0.1f;
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_E))
            cubeFrequency -= 0.1f;
        /* Fun Controls */

        //Mouse
        if (glfwGetMouseButton(window.getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            double mouse_xpos = m.getPosition().x;
            double mouse_ypos = m.getPosition().y;

            float xoffset = mouse_xpos - mouse_lastx;
            float yoffset = mouse_ypos - mouse_lasty;
            mouse_lastx = mouse_xpos;
            mouse_lasty = mouse_ypos;

            float sensitivity = .5;
            xoffset *= sensitivity;
            yoffset *= sensitivity;

            c1.addYaw(xoffset);
            c1.addPitch(-yoffset);

            if (c1.getPitch() > 89.f)
                c1.setPitch(89.f);
            if (c1.getPitch() < -89.f)
                c1.setPitch(-89.f);
        }

        //Clear all drawings that were made to the window
        window.clear(0, 0, 0, 0);

        /* Draws the cubes to window */
        for (int x = 0; x < 40; x++)
            for (int z = 0; z < 40; z++)
            {
                float y = cos(glfwGetTime() + (float)(x) / cubeFrequency) *
                          sin(glfwGetTime() + (float)(z) / cubeFrequency) * cubeAmplitude;

                drawCube(5, 5, 5, x * 5, y, z * 5,
                         fmod(1 / 40.f * (x), 1) + 0.1, 
                         fmod(1 / (cubeAmplitude == 0 ? 1 : cubeAmplitude) * y, 1) + 0.1,
                         fmod(1 / 40.f * (z), 1) + 0.1, 
                         1);
            }

        //Displays drawn elements to the window
        window.display();
    }
}


/* 
            DRAWS A CUBE TO SCREEN
                (For example3d)
*/
void drawCube(const float width, const float length, const float height, 
              const float xpos, const float ypos, const float zpos,
              const float r, const float g, const float b, const float a)
{
    /* Vertices for the cube. 24 total vertices */
    GLfloat cube[] =
    {
        //Position                                  Color           Normals
        //Front           
         xpos,ypos,zpos,                            r, g, b, a,     0,0,-1, //Bottom left
         width+xpos,ypos,zpos,                      r, g, b, a,     0,0,-1, //Bottom right
         width+xpos,height+ypos,zpos,               r, g, b, a,     0,0,-1, //Top right
         xpos,height+ypos,zpos,                     r, g, b, a,     0,0,-1, //Top left
        //Back                                                      
         xpos,   ypos, zpos+length,                 r, g, b, a,     0,0,1,
         width+xpos,   ypos, zpos+length,           r, g, b, a,     0,0,1,
         width+xpos,  height+ypos, zpos+length,     r, g, b, a,     0,0,1,
         xpos,  height+ypos, zpos+length,           r, g, b, a,     0,0,1,
        //Left                                                      
         xpos,   ypos,   zpos,                      r, g, b, a,     -1,0,0,
         xpos,   ypos, length+zpos,                 r, g, b, a,     -1,0,0,
         xpos,  height+ypos, length+zpos,           r, g, b, a,     -1,0,0,
         xpos,  height+ypos,   zpos,                r, g, b, a,     -1,0,0,
        //Right                                                     
         width+xpos,   ypos,   zpos,                r, g, b, a,     1,0,0,
         width+xpos,   ypos, length+zpos,           r, g, b, a,     1,0,0,
         width+xpos,  height+ypos, length+zpos,     r, g, b, a,     1,0,0,
         width+xpos,  height+ypos,   zpos,          r, g, b, a,     1,0,0,
        //Bottom                                                    
         xpos,   ypos,   zpos,                      r, g, b, a,     0,-1,0,
         xpos,   ypos, length+zpos,                 r, g, b, a,     0,-1,0,
         width+xpos,   ypos, length+zpos,           r, g, b, a,     0,-1,0,
         width+xpos,   ypos,   zpos,                r, g, b, a,     0,-1,0,
        //Top                                                       
         xpos,  height+ypos,   zpos,                r, g, b, a,     0,1,0,
         xpos,  height+ypos, length+zpos,           r, g, b, a,     0,1,0,
         width+xpos,  height+ypos, length+zpos,     r, g, b, a,     0,1,0,
         width+xpos,  height+ypos,   zpos,          r, g, b, a,     0,1,0,
    };
    
    /* Enable vertex, color and normals states */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    /* 
        Sets the size of the ____ (Ex: Color) array, the type of the array
       The total size of the array, multiplied by how many positions, colors, 
       and normals you have for a single point, then the pointer to the array
       (Add an offset if needed) 
    */
    glVertexPointer(3, GL_FLOAT, 10 * sizeof(GLfloat), cube);
    glColorPointer(4, GL_FLOAT, 10 * sizeof(GLfloat), cube + 3);
    glNormalPointer(GL_FLOAT, 10 * sizeof(GLfloat), cube + 7);

    /* Disable texture coordinates */
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    /* Draw the array to screen */
    glDrawArrays(GL_QUADS, 0, 24);
}