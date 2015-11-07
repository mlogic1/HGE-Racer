#include <hgesprite.h>
#include <hgevector.h>




/* ID's Explained:
1 - Play
2 - Help
3 - Exit Game
*/

class Button{

private:
    HTEXTURE BTexture;
    HTEXTURE BTextureMouseIn;
    hgeVector location;
    hgeSprite *Sprite;
    HEFFECT SoundOnHover;
    HGE *hgep;
    int id;



    // Texturechanged also says if the mouse is inside button
    bool TextureChanged;

public:
    Button(HGE *hge, hgeVector loc, const char* Texture1, const char* Texture2, int _id, HEFFECT HoverSound){
        hgep = hge;
        TextureChanged = false;
        location = loc;
        id = _id;
        std::cout<<"Loading "<<Texture1<<std::endl;
        BTexture = hgep->Texture_Load(Texture1);
        std::cout<<"Loading "<<Texture2<<std::endl;
        BTextureMouseIn = hgep->Texture_Load(Texture2);
        Sprite = new hgeSprite(BTexture, 0, 0, 174, 52);
        SoundOnHover = HoverSound;
    }


    void MouseIn(float mouseX, float mouseY){
        if(mouseX >= location.x && mouseX <= location.x + 174  && mouseY >= location.y && mouseY <= location.y + 52){
            if(!TextureChanged){
                Sprite->SetTexture(BTextureMouseIn);
                TextureChanged = true;
            }
        }
    }

    void MouseOut(float mouseX, float mouseY){
        if(mouseX < location.x || mouseX > location.x + 174  || mouseY < location.y || mouseY > location.y + 52){
            if(TextureChanged){
                Sprite->SetTexture(BTexture);
                TextureChanged = false;
            }
        }
    }

    int GetID(){
        return id;
    }

    bool GetState(){
        return TextureChanged;
    }


    ~Button(){
        hgep->Texture_Free(BTexture);
        hgep->Texture_Free(BTextureMouseIn);
        delete Sprite;
    }

    void RenderButton(){
        Sprite->Render(location.x, location.y);
    }
};
