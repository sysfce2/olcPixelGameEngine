#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#ifdef None
#undef None
#endif

#include "tileson.hpp"

struct Key
{
    olc::vi2d position;
    olc::vi2d size;
    olc::Key key;
};

class DemoKeyboard : public olc::PixelGameEngine
{
public:
    
    DemoKeyboard()
    {
        sAppName = "Demo App";
    }

    bool OnUserCreate() override
    {
        mapKeys["NONE"] = olc::Key::NONE; mapKeys["A"] = olc::Key::A; mapKeys["B"] = olc::Key::B;
        mapKeys["C"] = olc::Key::C; mapKeys["D"] = olc::Key::D; mapKeys["E"] = olc::Key::E;
        mapKeys["F"] = olc::Key::F; mapKeys["G"] = olc::Key::G; mapKeys["H"] = olc::Key::H;
        mapKeys["I"] = olc::Key::I; mapKeys["J"] = olc::Key::J; mapKeys["K"] = olc::Key::K;
        mapKeys["L"] = olc::Key::L; mapKeys["M"] = olc::Key::M; mapKeys["N"] = olc::Key::N;
        mapKeys["O"] = olc::Key::O; mapKeys["P"] = olc::Key::P; mapKeys["Q"] = olc::Key::Q;
        mapKeys["R"] = olc::Key::R; mapKeys["S"] = olc::Key::S; mapKeys["T"] = olc::Key::T;
        mapKeys["U"] = olc::Key::U; mapKeys["V"] = olc::Key::V; mapKeys["W"] = olc::Key::W;
        mapKeys["X"] = olc::Key::X; mapKeys["Y"] = olc::Key::Y; mapKeys["Z"] = olc::Key::Z;

        mapKeys["K0"] = olc::Key::K0; mapKeys["K1"] = olc::Key::K1; mapKeys["K2"] = olc::Key::K2;
        mapKeys["K3"] = olc::Key::K3; mapKeys["K4"] = olc::Key::K4; mapKeys["K5"] = olc::Key::K5;
        mapKeys["K6"] = olc::Key::K6; mapKeys["K7"] = olc::Key::K7; mapKeys["K8"] = olc::Key::K8;
        mapKeys["K9"] = olc::Key::K9;

        mapKeys["F1"] = olc::Key::F1; mapKeys["F2"] = olc::Key::F2; mapKeys["F3"] = olc::Key::F3;
        mapKeys["F4"] = olc::Key::F4; mapKeys["F5"] = olc::Key::F5; mapKeys["F6"] = olc::Key::F6;
        mapKeys["F7"] = olc::Key::F7; mapKeys["F8"] = olc::Key::F8; mapKeys["F9"] = olc::Key::F9;
        mapKeys["F10"] = olc::Key::F10; mapKeys["F11"] = olc::Key::F11; mapKeys["F12"] = olc::Key::F12;

        mapKeys["UP"] = olc::Key::UP; mapKeys["DOWN"] = olc::Key::DOWN; mapKeys["LEFT"] = olc::Key::LEFT; mapKeys["RIGHT"] = olc::Key::RIGHT;

        mapKeys["SPACE"] = olc::Key::SPACE; mapKeys["TAB"] = olc::Key::TAB; mapKeys["SHIFT"] = olc::Key::SHIFT;
        mapKeys["CTRL"] = olc::Key::CTRL; mapKeys["INS"] = olc::Key::INS; mapKeys["DEL"] = olc::Key::DEL;
        mapKeys["HOME"] = olc::Key::HOME; mapKeys["END"] = olc::Key::END; mapKeys["PGUP"] = olc::Key::PGUP;
        mapKeys["PGDN"] = olc::Key::PGDN;

        mapKeys["BACK"] = olc::Key::BACK; mapKeys["ESCAPE"] = olc::Key::ESCAPE; mapKeys["RETURN"] = olc::Key::RETURN;
        mapKeys["ENTER"] = olc::Key::ENTER; mapKeys["PAUSE"] = olc::Key::PAUSE; mapKeys["SCROLL"] = olc::Key::SCROLL;

        mapKeys["NP0"] = olc::Key::NP0; mapKeys["NP1"] = olc::Key::NP1; mapKeys["NP2"] = olc::Key::NP2;
        mapKeys["NP3"] = olc::Key::NP3; mapKeys["NP4"] = olc::Key::NP4; mapKeys["NP5"] = olc::Key::NP5;
        mapKeys["NP6"] = olc::Key::NP6; mapKeys["NP7"] = olc::Key::NP7; mapKeys["NP8"] = olc::Key::NP8;
        mapKeys["NP9"] = olc::Key::NP9; mapKeys["NP_MUL"] = olc::Key::NP_MUL; mapKeys["NP_DIV"] = olc::Key::NP_DIV;
        mapKeys["NP_ADD"] = olc::Key::NP_ADD; mapKeys["NP_SUB"] = olc::Key::NP_SUB; mapKeys["NP_DECIMAL"] = olc::Key::NP_DECIMAL;

        mapKeys["PERIOD"] = olc::Key::PERIOD; mapKeys["EQUALS"] = olc::Key::EQUALS; mapKeys["COMMA"] = olc::Key::COMMA;
        mapKeys["MINUS"] = olc::Key::MINUS;

        mapKeys["OEM_1"] = olc::Key::OEM_1; mapKeys["OEM_2"] = olc::Key::OEM_2; mapKeys["OEM_3"] = olc::Key::OEM_3;
        mapKeys["OEM_4"] = olc::Key::OEM_4; mapKeys["OEM_5"] = olc::Key::OEM_5; mapKeys["OEM_6"] = olc::Key::OEM_6;
        mapKeys["OEM_7"] = olc::Key::OEM_7; mapKeys["OEM_8"] = olc::Key::OEM_8; mapKeys["CAPS_LOCK"] = olc::Key::CAPS_LOCK;
        
        tson::Tileson t;
        std::unique_ptr<tson::Map> map = t.parse("assets/keyboard.tmj");

        tson::Layer* layerKeys = map->getLayer("keys");
        if(layerKeys == nullptr)
        {
            std::cout << "FUCKKKKK\n";
            return false;
        }
        
        for(auto key : layerKeys->getObjects())
        {
            Key tempKey;

            tempKey.position = olc::vi2d{
                key.getPosition().x,
                key.getPosition().y
            };
            
            tempKey.size = olc::vi2d{
                key.getSize().x,
                key.getSize().y
            };

            auto convert = mapKeys.find(key.get<std::string>("Key"));
            if(convert != mapKeys.end())
            {
                tempKey.key = convert->second;
            }
            else
            {
                tempKey.key = olc::Key::NONE;
            }
            vecKeys.push_back(tempKey);
        }

        renKeyboard.Load("assets/keyboard.png");
        
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);
        DrawSprite(0,0, renKeyboard.Sprite());
        for(auto &key : vecKeys)
        {
            if(GetKey(key.key).bHeld)
            {
                FillRect(key.position, key.size, olc::BLUE);
            }
            DrawRect(key.position, key.size, olc::WHITE);
        }
        return true;
    }

    std::map<std::string, olc::Key> mapKeys;
    std::vector<Key> vecKeys;

    olc::Renderable renKeyboard;

};


int main(void)
{
    DemoKeyboard demo;
    
    if(demo.Construct(320,180,4,4))
    {
        demo.Start();
    }
        
    
    return 0;
}