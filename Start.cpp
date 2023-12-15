/**
* Author: Safin Shihab
* Assignment: Student's Choice
* Date due: 2023-12-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#include "Start.h"
#include "Utility.h"

#define LEVEL_WIDTH 30
#define LEVEL_HEIGHT 10

unsigned int START_DATA[] =
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


START::~START()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void START::initialise()
{
    m_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/images/spritesheet.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, START_DATA, map_texture_id, 1.0f, 64, 64);
    
    // Existing
    m_state.player = new Entity();
    m_state.enemies = new Entity[ENEMY_COUNT];
   
        
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/audio/barriers.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME/ 16.0f);
    
    m_state.jump_sfx = Mix_LoadWAV("assets/audio/bounce.wav");
}

void START::update(float delta_time)
{
    return;

}

void START::render(ShaderProgram *program)
{
//    std::cout<<m_state.enemies[0].get_position().x<<std::endl;
    m_state.map->render(program);
    
    
    
}
