
#include <math.h>

typedef struct vector
{
    float x1;
    float x2;
    float x3;
} vec;

vector vec_add(vector a,vector b)                       //Use this for both addition and subtraction
{
    vector c;
    c.x1 = a.x1 + b.x1;
    c.x2 = a.x2 + b.x2;
    c.x3 = a.x3 + b.x3;

    return c;
}

vector vec_scale(float z, vector a)
{
    vector d;
    d.x1 = a.x1 * z;
    d.x2 = a.x2 * z;
    d.x3 = a.x3 * z;
}

float vec_abs(vector a)
{
    return (float)pow(pow((double)a.x1,2)+pow((double)a.x2,2)+pow((double)a.x3,2),1/2);
}

vector dirn(vector a)
{
    float n = vec_abs(a);
    return vec_scale((1/n),a);
}
