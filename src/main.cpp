#include <hge.h>
#include <hgesprite.h>
#include <hgefont.h>
#include <iostream>

HGE *hge = nullptr;
hgeFont *text = nullptr;


bool Update()
{
    if(hge->Input_KeyDown(HGEK_ESCAPE))
		return true;
    
    return false;
}

bool Render(){
    hge->Gfx_BeginScene();
    hge->Gfx_Clear(0);

    /*RENDER GOES HERE*/
	text->printf(512, 384, HGETEXT_RIGHT, "HGE Racer");

    hge->Gfx_EndScene();

    return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    //Set up the engine
    hge = hgeCreate(HGE_VERSION);
    hge->System_SetState(HGE_FRAMEFUNC, Update);
    hge->System_SetState(HGE_SHOWSPLASH, false);
    hge->System_SetState(HGE_WINDOWED, true);
    hge->System_SetState(HGE_USESOUND, true);
    hge->System_SetState(HGE_TITLE, "Highway Racer");
    hge->System_SetState(HGE_RENDERFUNC, Render);
    hge->System_SetState(HGE_SCREENWIDTH, 1024);
    hge->System_SetState(HGE_SCREENHEIGHT, 768);
    //hge->System_SetState(HGE_FPS, 60);        //check this later
    hge->System_SetState(HGE_HIDEMOUSE, false);


    if(hge->System_Initiate())
	{
		text = new hgeFont("Fonts/font1.fnt");
        hge->System_Start();
    }
    else
    {
        MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
	/* Release resources */
    hge->System_Shutdown();
    hge->Release();

    return 0;
}
