#include "myfuncs.h"

int main()
{
    struct data_struct data;
    data.x = 5;
    data.y = "hello";
    func1(10, 20);
    int result = func2(&data);
    return 0;
}
