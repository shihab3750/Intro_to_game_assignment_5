#include "Scene.h"

class START : public Scene {
public:
    int ENEMY_COUNT = 1;
    
    ~START();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
