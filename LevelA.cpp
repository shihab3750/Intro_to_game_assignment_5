/**
* Author: Safin Shihab
* Assignment: Student's Choice
* Date due: 2023-12-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 30
#define LEVEL_HEIGHT 10
using namespace std;


//unsigned int LEVELB_DATA[] =
//{
//        5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
//};

unsigned int LEVELA_DATA[] =
{
    258, 209, 209, 209, 209, 209, 208, 209, 209, 209, 210, 209, 208, 209, 209, 209, 210, 209, 208, 209,  209,   209,   210, 209, 208, 209,  209,  209,   210, 258,
    258, 258, 1, 1, 1, 1, 272, 19,  20,  21,  274, 1, 272, 403, 404, 405, 274, 1, 272, 787,  788,   789,   274, 1, 272, 1171, 1172, 1173,   274, 258,
    258, 258, 1, 1, 1, 1, 272, 83,  84,  85,  274, 1, 272, 467, 468, 469, 274, 1, 272, 851,  852,   853,   274, 1, 272, 1235, 1236, 1237,   274, 258,
    258, 258, 1, 1, 1, 1, 272, 147, 148, 149, 274, 1, 272, 531, 532, 533, 274, 1, 272, 915,  916,   917,   274, 1, 272, 1299, 1300, 1301,   274, 258,
    258, 258, 1, 1, 1, 1, 272, 211, 212, 213, 274, 1, 272, 595, 596, 597, 274, 1, 272, 979,  980,   981,   274, 1, 272, 1363, 1364, 1365,   274, 258,
    258, 258, 1, 1, 1, 1, 272, 275, 278, 277, 274, 1, 272, 659, 662, 661, 274, 1, 272, 1043, 1046,  1045,  274, 1, 272, 1427, 1430, 1429,  274, 258,
    258, 258, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 258,
    258, 258, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 258,
    258, 258, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 258,
    258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258,
};


LevelA::~LevelA()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelA::initialise()
{
    m_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/images/spritesheet.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 1, 64, 64);
    
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(5.0f, -1.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.5f);
    m_state.player->m_texture_id = Utility::load_texture("assets/images/him.png");
    
    // Walking
    m_state.player->m_walking[m_state.player->DOWN]   = new int[4] { 0, 1, 2,  3 };
    m_state.player->m_walking[m_state.player->RIGHT]  = new int[4] { 4, 5, 6, 7 };
    m_state.player->m_walking[m_state.player->LEFT]   = new int[4] { 8, 9, 10, 11 };
    m_state.player->m_walking[m_state.player->UP]     = new int[4] { 12, 13, 14, 15 };

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking RIGHT
    m_state.player->m_animation_frames = 4;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 4;
    m_state.player->m_animation_rows   = 4;
    m_state.player->set_height(0.8f);
    m_state.player->set_width(.8f);
    
    // Jumping
//    m_state.player->m_jumping_power = 7.0f;
    
    //keys
    // Existing
    m_state.keys = new Entity[KEY_COUNT];
    for (int i=0; i< KEY_COUNT; ++i){
        m_state.keys[i].set_entity_type(KEYS);
        m_state.keys[i].m_texture_id = Utility::load_texture("assets/images/key.png");
        m_state.keys[i].set_movement(glm::vec3(0.0f));
    }
    
    m_state.keys[0].set_position(glm::vec3(10.97f, -2.5f, 0.0f));
    m_state.keys[1].set_position(glm::vec3(5, -5.75, 0.0f));
    m_state.keys[2].set_position(glm::vec3(5, -3.1f, 0.0f));
    m_state.keys[3].set_position(glm::vec3(13.0f, -5.0f, 0.0f));
    m_state.keys[4].set_position(glm::vec3(29.0f, -6.0f, 0.0f));
        
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    m_state.bgm = Mix_LoadMUS("assets/audio/barriers.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME/ 16.0f);
    
    m_state.jump_sfx = Mix_LoadWAV("assets/audio/bounce.mp3");
}

void LevelA::update(float delta_time)
{
    m_state.player->update(delta_time, m_state.player, m_state.keys, KEY_COUNT, m_state.map);

    for (int i = 0; i < KEY_COUNT; i++) {
        m_state.keys[i].update(delta_time, m_state.player, m_state.player, KEY_COUNT, m_state.map);
    }
    cout << m_state.player->get_position().x << ','<<  m_state.player->get_position().y << endl;
    if (m_state.player->get_position().x >= 7.94f && m_state.player->get_position().x <= 8.01f && m_state.player->get_position().y == -5.9f) {
        std::cout << "Time to switch" << std::endl;
    }
    
}

void LevelA::render(ShaderProgram *program)
{
//    m_state.player->m_killed_enemies = 0;
//    for (int i = 0; i < ENEMY_COUNT; i++){
//        if (!m_state.enemies[i].get_is_active()){
//            m_state.player->m_killed_enemies += 1;
//        }
//        else{
//            m_state.enemies[i].render(program);
////            std::cout<<"NOT DEAD"<<std::endl;
//        }
//    }
    m_state.map->render(program);
    
    m_state.player->m_key_count = 0;
    for (int i = 0; i < KEY_COUNT; i++){
        if (!m_state.keys[i].get_is_active()){
            m_state.player->m_key_count += 1;
        }
        else{
            m_state.keys[i].render(program);
        }
    }
    
    if (m_state.player->get_is_active()){
        m_state.player->render(program);
    }
    
}
