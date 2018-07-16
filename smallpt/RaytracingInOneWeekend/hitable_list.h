#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

/* : public hitable表示hitable_list继承hitable。即：sphere为hitable的子类 */
class hitable_list : public hitable{
public:
    hitable_list(){}
    hitable_list(hitable **l, int n) {
        list = l;
        list_size = n;
    }

    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

    hitable **list;
    int list_size; /* hitable_list是所有能够被光线撞击的物体的列表/集合 */
};
#endif
