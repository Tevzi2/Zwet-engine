#pragma once

#include <core.h>
#include <utils.h>
#include <log.h>
#include <structs.h>
#include <mesh.h>
#include <frameBuffer.h>
#include <vertexBuffer.h>
#include <shader.h>
#include <texture.h>
#include <drawer.h>
#include <keyInput.h>
#include <camera.h>

namespace ZWET
{
    class Entity;

    // vsi podatki potrebni za ustvaritev nove entety klase
    struct entityData
    {
        std::string name;
        //object position and rotation
        vec3 position;
        vec3 staticRotation;
        vec3 dynamicRotation;

        //color
        rgb color = { 1.0f, 1.0f, 1.0f };

        //rendering stuff
        std::string texturePath;
        std::string modelLocation;
        std::vector<ShaderData> shaderData;
        FrameBufferSettings frameBufferSettings;

        //physics
        bool physicsObject = false;
        float weight = 1.0f;
        vec3 velocity = { 0.0f, 0.0f, 0.0f };
    };

    // mapa entetijev, ki se uporabi v upravljalniku scene za rokovanje z entitiji (to je samo krajsava da ni potrebno vsega veckrat pisat)
    using EntityMap = tsl::hopscotch_map<int, SharedPtr<Entity>>;

    // klasa entity se uporabi ob risanju za pridobivanje podatkov o 3d modelu, ki je vezan na njega, za krmiljenje kamere,
    // otroka te klase lahko razvijalec igre uporabi v svojem programu, da ji doda obnasanje, to naredi s tem da implementira
    // virtualne funkcije napisane v tem programu in v njih napise, kako se naj entity premika ob stisku tipk na tipkovnici npr.

    class Entity
    {
        public:
            vec3 position;
            vec3 dynamicRotation;
            int entityId;
            std::string family;
            SharedPtr<VertexBuffer> vertexBuffer;
            SharedPtr<FrameBuffer> frameBuffer;
            SharedPtr<Shader> shader;
            SharedPtr<Texture> texture;
            SharedPtr<Drawer> drawer;

            virtual ~Entity() {};

            // virtualne funkcije, ki jih mora razvijalec dodati v otroka te klase, da doda entitiju obnasanje
            virtual std::string getFamilyName() { return family; };
            
            virtual void createFun(EntityMap& entityMap, SharedPtr<Camera>& cam) {};

            virtual void stepStart(EntityMap& entityMap, SharedPtr<Camera>& cam, double delta) {};

            virtual void step(EntityMap& entityMap, SharedPtr<Camera>& cam, double delta) {};

            virtual void stepEnd(EntityMap& entityMap, SharedPtr<Camera>& cam, double delta) {};

            void newMesh(mesh newMesh);

            void setMesh(mesh prMesh);

            void setEntityData(entityData data);

            void setKeyInput(SharedPtr<KeyboardInput> keyInput);
            
        protected:
            SharedPtr<KeyboardInput> keyBoard;

            entityData data;
            bool physicsEnabled;
            vec3 velocity;
            float weight;
            bool presetMesh = false;

            mesh entityMesh;
            std::vector<float> convretMesh;
    };
}