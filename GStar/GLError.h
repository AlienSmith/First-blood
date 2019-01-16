#ifndef GLERROR_H
#define GLERROR_H

void _check_gl_error(const char *file, int line);

///
/// Usage
/// [... some opengl calls]
/// glCheckError();
///
#if defined(_DEBUG)
#define check_gl_error() _check_gl_error(__FILE__,__LINE__)
#else
#define check_gl_error() void(0)
#endif

#endif // GLERROR_H