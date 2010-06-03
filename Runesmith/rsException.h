#ifndef RS_EXCEPTION_H
#define RS_EXCEPTION_H

#include <stdexcept>
 
 class RSException : public std::runtime_error {
 public:
   RSException() : std::runtime_error("RSException") { }
 };

#endif