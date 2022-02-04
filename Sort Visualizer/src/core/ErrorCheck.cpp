#include "ErrorCheck.h"
#include <iostream>

void glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGl error] (" << std::hex << "0x..." << error << ") "
            << function << " " << file << " : Line - " << line << std::endl;
        return false;
    }
    return true;
}
