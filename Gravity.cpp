#include <vector>
#include <math>

#define Field_Size 100000;
#define infi_time 0.001;
//Define Field Size and initialize

int Field[Field_Size][Field_Size][Field_Size]={0};

std::vector En_diff(Body i,std::vector in)
{
    //Scan function for maximum energy difference between itself and neighbouring points
    return std::vector fn;                  //Final direction vector for potential graient
}

std::vector update(Body i,std::vector fn)
{
    std::vector dir = En_diff(i,in);
    int abs=0;
    for (std::vector<int>::iterator it = fn.begin(); it != fn.end(); ++it)
    {
        abs+=pow(it,2);
    }
    abs = pow(abs,(1/2));
    vel = 2*sqrt(pot(fn) - pot(in))/(i.mass);        //potential function to be made.
    i.pos = i.pos + vel*(fn/abs);
    return i.pos;
}
