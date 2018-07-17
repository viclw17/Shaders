<!-- https://blog.csdn.net/libing_zeng/article/details/72599041
https://blog.csdn.net/libing_zeng/article/details/54428306 -->
# Diffuse Material
Note that in RTIOW we separate geometry from material and treat them as 2 unlinked classes.

## Diffuse (Matte) Material
Object with a diffuse material doesn't emit light but take on the colors from the surroundings, and _modulate (alter the amplitude or frequency of (an electromagnetic wave or other oscillation) in accordance with the variations of a second signal, typically one of a lower frequency)_ the colors with its own intrinsic color.

> The visibility of objects, excluding light-emitting ones, is primarily caused by diffuse reflection of light: it is diffusely-scattered light that forms the image of the object in the observer's eye.

The light that reflects off a diffuse surface has its direction randomized, and also got absorbed a lot rather than reflected. The darker the surface is the more light-absorption (eg. [Vantablack](https://en.wikipedia.org/wiki/Vantablack)).

> Diffuse reflection is the reflection of light from a surface such that a ray incident on the surface is scattered at many angles rather than at just one angle as in the case of specular reflection.

<img src="https://upload.wikimedia.org/wikipedia/commons/b/bd/Lambert2.gif
" width="320"  style="display:block; margin:auto;">
>⬆️ _The rays represent luminous intensity, which varies according to Lambert's cosine law for an ideal diffuse reflector._

In RTIOW we are using a simple algorithm to approximate mathematically ideal [Lambertian reflection](https://en.wikipedia.org/wiki/Lambertian_reflectance).

> An ideal diffuse reflecting surface is said to exhibit , meaning that there is equal luminance when viewed from all directions lying in the half-space adjacent to the surface.

# Algorithm
From the point $P$ where ray hit on the sphere, we need to form a unit sphere that is tangent to this hitpoint. We can get the center position of this sphere by $P+N$ where $N$ is the surface normal at point $P$.

Then we pick a random point $S$ in this unit sphere, and send a ray from $P$ to $S$ to build a random diffuse reflection vector $\overrightarrow{PS}$

Next we need to form another unit sphere centered at ray(view) origin, and pick a random point in it to cast a ray. To do this we are using a **rejection method**.
