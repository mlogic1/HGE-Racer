#include <hge.h>
#include <hgesprite.h>
#include <iostream>

#include "button.h"
#include "SinglePlayerGame.h"



HGE *hge = 0;
// Mouse Location(x,y) used for buttons
float mouseX = 0;
float mouseY = 0;



// Buttons
Button *Play;
hgeVector PlayLoc;
Button *Help;
hgeVector HelpLoc;
Button *ExitGame;
hgeVector ExitGameLoc;

//sound object for menu buttons
HEFFECT clicksound;

//Quit game button bool
bool quitgame = false;




void RenderButtons(){
    Play->RenderButton();
    Help->RenderButton();
    ExitGame->RenderButton();
}

void SendMouseCordsToButtons(){
    Play->MouseIn(mouseX, mouseY);
    Play->MouseOut(mouseX, mouseY);
    Help->MouseIn(mouseX, mouseY);
    Help->MouseOut(mouseX, mouseY);
    ExitGame->MouseIn(mouseX, mouseY);
    ExitGame->MouseOut(mouseX, mouseY);
}


void StartNewGame(){
    hge->Effect_Play(clicksound);

    //StartSinglePlayerGame(hge);
    StartSinglePlayerGame(hge);


}

bool MenuFrameFunc()
{
    if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
    if(quitgame) return true;

    hge->Input_GetMousePos(&mouseX, &mouseY);
    SendMouseCordsToButtons();



    if(hge->Input_KeyDown(HGEK_LBUTTON))
        {
                if(Play->GetState()){
                    StartNewGame();
                }else if(Help->GetState()){
                    //Stand_Down();
                }else if(ExitGame->GetState()){
                    return true;
                }else{
                    // Do nothing, player didn't click a button
                }
        }



      return false;
}

bool MenuRenderFunc(){
    hge->Gfx_BeginScene();
    hge->Gfx_Clear(0);

    /*RENDER GOES HERE*/

    RenderButtons();


    hge->Gfx_EndScene();

    return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    //Set up the engine
    hge = hgeCreate(HGE_VERSION);
    hge->System_SetState(HGE_FRAMEFUNC, MenuFrameFunc);
    hge->System_SetState(HGE_SHOWSPLASH, false);
    hge->System_SetState(HGE_WINDOWED, true);
    hge->System_SetState(HGE_USESOUND, true);
    hge->System_SetState(HGE_TITLE, "Racer Game");
    hge->System_SetState(HGE_RENDERFUNC, MenuRenderFunc);
    hge->System_SetState(HGE_SCREENWIDTH, 1024);
    hge->System_SetState(HGE_SCREENHEIGHT, 768);
    hge->System_SetState(HGE_HIDEMOUSE, false);






    if(hge->System_Initiate())
    {

        // Buttons
        PlayLoc.x = 425;
        PlayLoc.y = 300;
        Play = new Button(hge, PlayLoc, "Textures\\Buttons\\play.png", "Textures\\Buttons\\play_hover.png", 1, clicksound);

        HelpLoc.x = 425;
        HelpLoc.y = 400;
        Help = new Button(hge, HelpLoc, "Textures\\Buttons\\help.png", "Textures\\Buttons\\help_hover.png", 2, clicksound);

        ExitGameLoc.x = 425;
        ExitGameLoc.y = 500;
        ExitGame = new Button(hge, ExitGameLoc, "Textures\\Buttons\\quit.png", "Textures\\Buttons\\quit_hover.png", 3, clicksound);

        //Button sounds
        std::cout<<"Loading clicksound"<<std::endl;
        clicksound = hge->Effect_Load("Sounds\\menuclick.wav");

        hge->System_Start();



                    /* Release resources */

        Play->~Button();
        Help->~Button();
        ExitGame->~Button();
        hge->Effect_Free(clicksound);




    }
    else
    {
        MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
    hge->System_Shutdown();
    hge->Release();

    return 0;
}
