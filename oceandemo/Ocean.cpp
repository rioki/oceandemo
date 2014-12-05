
#include "Ocean.h"

#include <tchar.h>
#include <windows.h>

#include "resource.h"

namespace od
{    
    const char* LoadTextResource(HMODULE hModule, LPTSTR sGroup, WORD nId) 
    {
        HRSRC hRsrc = FindResource(hModule, MAKEINTRESOURCE(nId), sGroup);
        HGLOBAL hGlobal = LoadResource(hModule, hRsrc);
        return (const char*)LockResource(hGlobal);
    }

    Ocean::Ocean()
    {
        HMODULE hModule = GetModuleHandle(_T("oceandemo.exe"));

        shader.set_vertex_code(LoadTextResource(hModule, _T("GLSL"), IDR_GLSL_OCEAN_VERT));
        shader.set_fragment_code(LoadTextResource(hModule, _T("GLSL"), IDR_GLSL_OCEAN_FRAG));
        shader.compile();

        plane.add_vertex(Vector3(-100.0f, -100.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
        plane.add_vertex(Vector3( 100.0f, -100.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f));
        plane.add_vertex(Vector3( 100.0f,  100.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f));
        plane.add_vertex(Vector3(-100.0f,  100.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f));
        plane.add_face(0, 1, 2);
        plane.add_face(0, 2, 3);
    }

    Ocean::~Ocean() {}

    void Ocean::draw(Camera& camera) 
    {
        shader.bind();
        
        camera.setup(shader);

        plane.draw(shader);
    }
}
