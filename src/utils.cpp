#include "utils.hpp"

/**
 * Display a 3D vector
 * @param vector The vector to display
 * @param stream The stream where to display it
 */
void utils::displayVector3(const glm::vec3& vector, FILE *__restrict stream) {
    fprintf(stream, "%f, %f, %f", vector.x, vector.y, vector.z);
}

/**
 * Display a 4D vector
 * @param vector The vector to display
 * @param stream The stream where to display it
 */
void utils::displayVector4(const glm::vec4& vector, FILE *__restrict stream) {
    fprintf(stream, "%f, %f, %f, %f", vector.x, vector.y, vector.z, vector.w);
}

/**
 * Display a 3x3 matrix
 * @param matrix The matrix to display
 * @param stream The stream where to display it
 */
void utils::displayMatrix3(const glm::mat3& matrix, FILE *__restrict stream) {
    for (int i = 0; i < 3; i++) {
        fprintf(stream, "%f, %f, %f\n", matrix[i][0], matrix[i][1], matrix[i][2]);
    }
}

/**
 * Display a 4x4 matrix
 * @param matrix The matrix to display
 * @param stream The stream where to display it
 */
void utils::displayMatrix4(const glm::mat4& matrix, FILE *__restrict stream) {
    for (int i = 0; i < 4; i++) {
        fprintf(stream, "%f, %f, %f, %f\n", matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
    }
}