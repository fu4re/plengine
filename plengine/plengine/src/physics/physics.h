typedef struct postition{
    float x, y;
}postition_t;

typedef struct rigidbody{
    int mass;
    postition_t current_postition;
    float velocity;
    
}rigidbody_t;