// =====================================================================
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================

#ifndef CLUT_H
#define CLUT_H

// === LUT SIZES ===
#define SIN_SIZE 512

// === LUT DECLARATIONS ===
extern const signed short SIN[512];


int32_t sincalcc(float i);
int32_t coscalcc(float i);

typedef struct {
 int32_t x, y;
 } vector_t;

typedef struct {
 int32_t x, y, vel;
 } ball_t;

int ballpos(float *x, float *y, float velx, float vely);
void ball(float x, float y);
void initVector(vector_t *v);
void rotateVector(float x, float y, float angle);


#endif	// CLUT_H
