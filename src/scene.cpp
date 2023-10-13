#include "scene.hpp"

const GLuint Scene::_NB_ELEMENT_PER_VERTICES = VboType::VERTICES
                                     + VboType::COLORS
                                     + VboType::UVS
                                     + VboType::NORMALS;