#ifndef GLERROR_H
#define GLERROR_H


///
/// Usage
/// [... some opengl calls]
/// glCheckError();
///
#if defined(_DEBUG)
void _check_gl_error(const char *file, int line);
#define check_gl_error() _check_gl_error(__FILE__,__LINE__)
#else
#define check_gl_error() void(0)
#endif

#endif // GLERROR_H