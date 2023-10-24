#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <fstream>
#include <glm/glm.hpp>


namespace utils{

/**
 * Display a 3D vector
 * @param vector The vector to display
 * @param stream The stream where to display it
 */
void displayVector3(const glm::vec3& vector, FILE *__restrict stream);

/**
 * Display a 4D vector
 * @param vector The vector to display
 * @param stream The stream where to display it
 */
void displayVector4(const glm::vec4& vector, FILE *__restrict stream);

/**
 * Display a 3x3 matrix
 * @param matrix The matrix to display
 * @param stream The stream where to display it
 */
void displayMatrix3(const glm::mat3& matrix, FILE *__restrict stream);

/**
 * Display a 4x4 matrix
 * @param matrix The matrix to display
 * @param stream The stream where to display it
 */
void displayMatrix4(const glm::mat4& matrix, FILE *__restrict stream);

};

#endif