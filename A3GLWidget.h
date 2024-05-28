#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QMouseEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "model.h"
#include "MyGLWidget.h"

class A3GLWidget : public MyGLWidget
{
  Q_OBJECT

#define NUM_TORXES 6
#define HORA_MIN 8
#define HORA_MAX 20
#define NUM_FOCUS_FAR 2

  private:
    int horaActual = 14;

  public:
    A3GLWidget (QWidget *parent=0);
    ~A3GLWidget ();

  protected:

    void modelTransformFar1();
    void modelTransformFar2();
    void modelTransformVaixell();
    void solTransform();
    void iniEscena ();
    void carregaShaders();

    virtual void paintGL ( );
    virtual void keyPressEvent (QKeyEvent *event);
    //--------------------------------------------------------------
    // uniform locations
    GLuint normalMatrixLoc, colorLlumLoc, posLlumLoc, llumAmbientLoc;
    //--------------------------------------------------------------
    // Posicions
    glm::vec3 VaixellPos;

    //--------------------------------------------------------------
    // Colors

    //--------------------------------------------------------------
    // MATRIUS DE TRANSFORMACIÓ
    glm::mat4 Vaixell_TG, Far2_TG;

};

