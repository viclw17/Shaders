# Sampling techniques
- Uniform
- Random
- Jittered
## Random Sampling
Pick a random point within the area being sampled

# Random reflection direction
## Orthonormal basis
- First, we need to find a set of orthogonormal axes based on the normal. This will be sort of like a “camera”.
- Set the Z axis in our new basis equal to the normal
- Find any X and Y orthogonal to Z and unit length (“orthonormal”)

Remember, cross product returns a vector that is perpendicular to both input vectors
```c
Vector Z = normal;
cross(normal, any vector) //Pick one of (1, 0, 0), (0, 1, 0), (0, 0, 1)
```
- This result will be perpendicular to the normal
- But what if the vector we pick is parallel to the normal? Result will be zero vector

Choose axis with smallest component in normal
```c
if(N.x < N.y && N.x < N.z)
    { axis = vec(1.0f, 0.0f, 0.0f); }
else if (N.y < N.z)
    { axis = vec(0.0f, 1.0f, 0.0f); }
else
    { axis = vec(0.0f, 0.0f, 1.0f); }
 ```
Last axis is cross product of other two
```c
X = normal.cross(axis).normalize()
Y = normal.cross(x)
```
Now we have a new axis system
- X and Y are tangent to the surface
- Z is normal to the surface

# Hemisphere sampling
Pick a random vector on the unit hemisphere defined by our new basis
- Option 1:
    - Define the “hemicube” (half cube) on the surface
    - Randomly pick points inside the cube until we get one that is inside the hemisphere
    - Will be uniformly distributed (actually a bad thing)
- Option 2:
    - Randomly pick points on the unit disc
    - Project out to hemisphere
    - Not uniformly distributed (more later)
