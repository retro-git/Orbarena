#include "objecttype.h"
#include "ode/ode.h"
#include "ofApp.h"
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

/* This class wraps an ODE physics entity and its graphics elements
 * together into a single game object.
 */
class GameObject
{
public:
  /* ODE objects */
  dBodyID m_body;
  dMass m_mass;
  dGeomID m_geom;
  dTriMeshDataID m_data;

  /* The 3D model */
  ofxAssimpModelLoader m_model;

  /* Attributes of this object */
  glm::vec3 pos;
  glm::vec3 accel{};
  ofQuaternion m_rotation;

  void setPosition(glm::vec3 pos);
  virtual void update() = 0;
  virtual void draw();
  virtual void init(glm::vec3 pos,
                    glm::vec3 rot,
                    glm::vec3 scale,
                    string modelName,
                    dWorldID w,
                    dSpaceID s);

  std::vector<std::vector<glm::vec3>> vertices;
  std::vector<std::vector<uint>> indices;

  ObjectType type;

  bool debug_draw = false;
};
#endif // GAMEOBJECT_H
