#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
//#include "SFML/Audio.hpp"
//#include "SFML/Network.hpp"

using namespace sf;

int main()
{
    ContextSettings contextSettings;
    contextSettings.depthBits = 24;

    RenderWindow window(VideoMode(800, 600), "SFML-3D", Style::Close, contextSettings);

    window.setActive();
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glViewport(0, 0, window.getSize().x, window.getSize().y);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

    GLfloat cube[] =
    {
        -75, -50, -75,  0, 0, 1, 1,
        -50,  50, -50,  0, 0, 1, 1,
        -75, -50,  75,  0, 0, 1, 1,
        -75, -50,  75,  0, 0, 1, 1,
        -50,  50, -50,  0, 0, 1, 1,
        -50,  50,  50,  0, 0, 1, 1,

         75, -50, -75,  0, 1, 0, 1,
         50,  50, -50,  0, 1, 0, 1,
         75, -50,  75,  0, 1, 0, 1,
         75, -50,  75,  0, 1, 0, 1,
         50,  50, -50,  0, 1, 0, 1,
         50,  50,  50,  0, 1, 0, 1,

        -75, -50, -75,  1, 0, 0, 1,
         75, -50, -75,  1, 0, 0, 1,
        -75, -50,  75,  1, 0, 0, 1,
        -75, -50,  75,  1, 0, 0, 1,
         75, -50, -75,  1, 0, 0, 1,
         75, -50,  75,  1, 0, 0, 1,

        -50,  50, -50,  0, 1, 1, 1,
         50,  50, -50,  0, 1, 1, 1,
        -50,  50,  50,  0, 1, 1, 1,
        -50,  50,  50,  0, 1, 1, 1,
         50,  50, -50,  0, 1, 1, 1,
         50,  50,  50,  0, 1, 1, 1,

        -75, -50, -75,  1, 0, 1, 1,
         75, -50, -75,  1, 0, 1, 1,
        -50,  50, -50,  1, 0, 1, 1,
        -50,  50, -50,  1, 0, 1, 1,
         75, -50, -75,  1, 0, 1, 1,
         50,  50, -50,  1, 0, 1, 1,

        -75, -50,  75,  1, 1, 0, 1,
         75, -50,  75,  1, 1, 0, 1,
        -50,  50,  50,  1, 1, 0, 1,
        -50,  50,  50,  1, 1, 0, 1,
         75, -50,  75,  1, 1, 0, 1,
         50,  50,  50,  1, 1, 0, 1,
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 7 * sizeof(GLfloat), cube);
    glColorPointer(4, GL_FLOAT, 7 * sizeof(GLfloat), cube + 3);

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    Clock c;

    Event event;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);
        glRotatef(c.getElapsedTime().asSeconds() * 100, 0.f, 1.f, 0.5f);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        window.display();
    }

    return EXIT_SUCCESS;
}