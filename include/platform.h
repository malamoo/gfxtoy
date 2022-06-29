// type aliases
typedef unsigned char uchar;
// GLFW
GLFWwindow *glfwinit();
// file system
size_t freads(FILE *fin, char *s, size_t max);
// error wrapping
void setprogname(char *str);
char *progname(void);
char *estrdup(char *s);
void eprintf(char *fmt, ...);
void weprintf(char *fmt, ...);
void *emalloc(size_t n);
void *erealloc(void *p, size_t n);