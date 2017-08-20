#ifndef MODEL_ROBOT_MICROBEE_H
#define MODEL_ROBOT_MICROBEE_H

#include <cstdint>

class model_robot_microbee_c {
    public:
        model_robot_microbee_c(void);
        void update(void);
        int encode_info2string(uint8_t*);
        // attributes
        int type;
        int id;
        // states
        float pos[3];
        float att[3];
        float pos_ref[3];
        float heading_ref;
};

#endif
