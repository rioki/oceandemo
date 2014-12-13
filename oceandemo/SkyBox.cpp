#include "SkyBox.h"

#include <GL/glew.h>

#include "fs.h"
#include "Camera.h"

namespace od
{
    SkyBox::SkyBox() 
    {
        shader.set_vertex_code(fs::readfile("../Assets/Sky/Sky.vert.glsl"));
        shader.set_fragment_code(fs::readfile("../Assets/Sky/Sky.frag.glsl"));
        shader.compile();

        mesh.add_vertex(rgm::vec3(-1, -1, 0), rgm::vec3(0, 0, 1), rgm::vec2(0, 0));
        mesh.add_vertex(rgm::vec3( 1, -1, 0), rgm::vec3(0, 0, 1), rgm::vec2(1, 0));
        mesh.add_vertex(rgm::vec3( 1,  1, 0), rgm::vec3(0, 0, 1), rgm::vec2(1, 1));
        mesh.add_vertex(rgm::vec3(-1,  1, 0), rgm::vec3(0, 0, 1), rgm::vec2(0, 1));
        mesh.add_face(0, 1, 2);
        mesh.add_face(0, 2, 3);

        /*cubemap.load(XPOS, "../Assets/Sky/Morning_XPos.jpg");
        cubemap.load(XNEG, "../Assets/Sky/Morning_XNeg.jpg");
        cubemap.load(YPOS, "../Assets/Sky/Morning_YPos.jpg");
        cubemap.load(YNEG, "../Assets/Sky/Morning_YNeg.jpg");
        cubemap.load(ZPOS, "../Assets/Sky/Morning_ZPos.jpg");
        cubemap.load(ZNEG, "../Assets/Sky/Morning_ZNeg.jpg");*/

        cubemap.load(XPOS, "../Assets/Sky/CloudyAfternoon_XPos.jpg");
        cubemap.load(XNEG, "../Assets/Sky/CloudyAfternoon_XNeg.jpg");
        cubemap.load(YPOS, "../Assets/Sky/CloudyAfternoon_YPos.jpg");
        cubemap.load(YNEG, "../Assets/Sky/CloudyAfternoon_YNeg.jpg");
        cubemap.load(ZPOS, "../Assets/Sky/CloudyAfternoon_ZPos.jpg");
        cubemap.load(ZNEG, "../Assets/Sky/CloudyAfternoon_ZNeg.jpg");
    }

    void SkyBox::draw(Camera& camera) const 
    {
        glDisable(GL_DEPTH_TEST);
        
        shader.bind();

        camera.setup(shader);

        cubemap.bind(0);
        shader.set_uniform("uCubemap", 0);

        mesh.draw(shader);

        glEnable(GL_DEPTH_TEST);
    }    
}