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

  public slots:
    void updateTime(int Time);
    void updateColorVermell();
    void updateColorGroc();
    void updateColorVioleta();
    void updateColorVerd();
    void updateTorxa1();
    void updateTorxa2();
    void updateTorxa3();
    void updateTorxa4();
    void updateTorxa5();
    void updateTorxa6();
  signals:
		void setTime(int);

  private:
    int horaActual = 14;
    float rotacioFar = 0.0;
    bool estatTorxa[6];
    glm::vec3 colorLlums = glm::vec3(1.0,1.0,0.0);

  public:
    A3GLWidget (QWidget *parent=0);
    ~A3GLWidget ();

  protected:

    void modelTransformFar1();
    void modelTransformFar2();
    void modelTransformVaixell();
    void solTransform();
    void llumFarTransform();
    void llumsVaixellTransform();
    void iniEscena ();
    void carregaShaders();

    virtual void paintGL ( );
    virtual void keyPressEvent (QKeyEvent *event);
    //--------------------------------------------------------------
    // uniform locations
    GLuint normalMatrixLoc, colorLlumLoc, posLlumLoc, llumAmbientLoc, llumsFarLoc[2], colorLlumFarLoc;
    GLint isDrawingSeaLoc;
    GLint llumsVaixellLoc, colorLlumsVaixellLoc;
    //--------------------------------------------------------------
    // Posicions
    glm::vec3 VaixellPos;

    //--------------------------------------------------------------
    // Colors

    //--------------------------------------------------------------
    // MATRIUS DE TRANSFORMACIÓ
    glm::mat4 Vaixell_TG, Far2_TG;

};

