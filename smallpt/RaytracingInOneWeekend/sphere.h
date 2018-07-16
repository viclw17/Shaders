#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

/* : public hitable表示sphere继承hitable。即：sphere为hitable的子类 */
class sphere : public hitable{
public:
    sphere(){}
    /* 此处为使用 初始化列表(initializer list) 的构造函数来初始化成员变量*/
    sphere(vec3 cen, float r) : center(cen), radius(r) {}// ;???

    /* 必须实现父类的虚函数。在此出声明，后续在sphere.cpp中具体实现 */
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

    // Sphere class 成员变量
    vec3 center;
    float radius;
};
#endif
