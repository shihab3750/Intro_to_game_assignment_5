#include "LevelC.h"
#include "Utility.h"

#define LEVEL_WIDTH 14
#define LEVEL_HEIGHT 8

unsigned int LEVELC_DATA[] =
{
    2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

LevelC::~LevelC()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelC::initialise()
{
    m_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/images/tileset.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELC_DATA, map_texture_id, 1.0f, 9, 10);
    
    // Code from main.cpp's initialise()
    /**
     George's Stuff
     */
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(5.0f, 0.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.5f);
    m_state.player->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.player->m_texture_id = Utility::load_texture("assets/images/him.png");
    
    // Walking
    m_state.player->m_walking[m_state.player->DOWN]   = new int[4] { 0, 1, 2,  3 };
    m_state.player->m_walking[m_state.player->RIGHT]  = new int[4] { 4, 5, 6, 7 };
    m_state.player->m_walking[m_state.player->LEFT]   = new int[4] { 8, 9, 10, 11 };
    m_state.player->m_walking[m_state.player->UP]     = new int[4] { 12, 13, 14, 15 };

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
    m_state.player->m_animation_frames = 4;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 4;
    m_state.player->m_animation_rows   = 4;
    m_state.player->set_height(0.8f);
    m_state.player->set_width(0.8f);
    
    // Jumping
    m_state.player->m_jumping_power = 7.0f;
    
    /**
     Enemies' stuff */
    GLuint enemy_texture_id = Utility::load_texture("assets/images/Monster.png");

    m_state.enemies = new Entity[ENEMY_COUNT];
    
    m_state.enemies[0].set_entity_type(ENEMY);
    m_state.enemies[0].m_texture_id = enemy_texture_id;
    m_state.enemies[0].set_speed(.5f);
    m_state.enemies[0].set_acceleration(glm::vec3(0.0f, -10.0f, 0.0f));
    m_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_state.enemies[0].set_ai_type(GUARD);
    m_state.enemies[0].set_position(glm::vec3(9.0f, 0.0f, 0.0f));
    
    
        //font
//    g_font_texture_id = load_texture(FONT_FILEPAHT);
        
    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/audio/barriers.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME/ 16.0f);
    
    m_state.jump_sfx = Mix_LoadWAV("assets/audio/bounce.mp3");
}

void LevelC::update(float delta_time)
{
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);

    for (int i = 0; i < ENEMY_COUNT; i++) {
        m_state.enemies[i].update(delta_time, m_state.player, m_state.player, 1, m_state.map);
    }
}

void LevelC::render(ShaderProgram *program)
{
    m_state.player->m_killed_enemies = 0;
    for (int i = 0; i < ENEMY_COUNT; i++){
        if (!m_state.enemies[i].get_is_active()){
            m_state.player->m_killed_enemies += 1;
        }
        else{
            m_state.enemies[i].render(program);
//            std::cout<<"NOT DEAD"<<std::endl;
        }
    }
    std::cout<<m_state.enemies[0].get_position().x<<std::endl;
    m_state.map->render(program);
    if (m_state.player->get_is_active()){
        m_state.player->render(program);
        }
    
}