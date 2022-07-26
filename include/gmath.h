typedef float vec2[2];
typedef float vec3[3];
typedef float hvec[4];
typedef hvec tform[4];

void tfid(tform out);
void tfrotx(tform t, float deg, tform out);
void tfrotz(tform t, float deg, tform out);
void tfroty(tform t, float deg, tform out);
void tfpersp(float fov, float aspect, float near, float far, tform out);
void tftranz(float z, tform out);
void tfscale(tform t, float s, tform out);
void tftran(tform t, vec3 v, tform out);
void tfcam(vec3 e, vec3 g, vec3 t, tform out);
void tfmul(tform a, tform b, tform out);
void tfframe(vec3 u, vec3 v, vec3 w, vec3 e, tform out);
void tfframeinv(tform frame, tform out);
void tfprint(tform m);

void vec3unit(vec3 v, vec3 out);
void vec3neg(vec3 v, vec3 out);
float vec3norm(vec3 v);
void vec3cross(vec3 a, vec3 b, vec3 out);
