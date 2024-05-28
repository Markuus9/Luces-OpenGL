#include "A3GLWidget.h"

#include <iostream>

A3GLWidget::A3GLWidget (QWidget* parent) : MyGLWidget(parent)
{
}

A3GLWidget::~A3GLWidget()
{
}


void A3GLWidget::iniEscena ()
{
	creaBuffersModels();

	VaixellPos = glm::vec3(-10, 0.0, 0.0);


	//--------------------------------------------------
	centreEsc = glm::vec3 (0, 0, 0);

	radiEsc = 20;// Tret de la màniga :-P
	
  glm::vec3 llumAmbient = glm::vec3(0.1,0.1,0.1);
  glUniform3fv(llumAmbientLoc, 1, &llumAmbient[0]);
  
  glm::vec3 colorLlum = glm::vec3(0.6,0.6,0.6);
  glUniform3fv(colorLlumLoc, 1, &colorLlum[0]);
  
}


void A3GLWidget::paintGL ()
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#endif

	// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
	// useu els paràmetres que considereu (els que hi ha són els de per defecte)
	//  glViewport (0, 0, ample, alt);


	projectTransform ();
	viewTransform ();
	solTransform();
	llumFarTransform();
	// Esborrem el frame-buffer i el depth-buffer

	glClearColor(0.8f, 0.8f, 1.0f, 1.f);

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//--------------------------------------------------------
	// Activem el VAO per a pintar el vaixell
	glBindVertexArray (VAO_models[VAIXELL]);
	// Transformació geometrica
	modelTransformVaixell();
	// pintem el vaixell
	glDrawArrays(GL_TRIANGLES, 0, models[VAIXELL].faces().size()*3);
	//--------------------------------------------------------
	// Activem el VAO per a pintar el moll
	glBindVertexArray (VAO_models[MOLL]);
	// pintem les espelmes, cadascuna amb el seu transform
	modelTransformMoll();
	glDrawArrays(GL_TRIANGLES, 0, models[MOLL].faces().size()*3);
	//--------------------------------------------------------
	// Activem el VAO per a pintar el far (primera part)
	glBindVertexArray (VAO_models[FAR_1]);
	// pintem les espelmes, cadascuna amb el seu transform
	modelTransformFar1();
	glDrawArrays(GL_TRIANGLES, 0, models[FAR_1].faces().size()*3);
	//--------------------------------------------------------
	// Activem el VAO per a pintar el far (segona part)
	glBindVertexArray (VAO_models[FAR_2]);
	// pintem les espelmes, cadascuna amb el seu transform
	modelTransformFar2();
	glDrawArrays(GL_TRIANGLES, 0, models[FAR_2].faces().size()*3);
	//------------------------------------------------------------
	//Pintem terra
	glBindVertexArray (VAO_Terra);
	modelTransformTerra();
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Pintem Mar
	glBindVertexArray (VAO_Mar);
	modelTransformMar();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//--------------------------------------------------------

	glBindVertexArray(0);
}

void A3GLWidget::solTransform()
{
  float rotacio = (14.0f-float(horaActual))*15.0f;
  glm::mat4 TG = glm::mat4(1.0f);
  TG = glm::rotate(TG, glm::radians(rotacio), glm::vec3(0,0,1));
  glm::vec4 pSol = View * TG * glm::vec4(0.0f, 40.0f, 0.0f, 1.0f);
  glUniform4fv(posLlumLoc, 1, &pSol[0]);
}

void A3GLWidget::llumFarTransform(){
  glm::vec4 llum1 = View * Far2_TG * glm::vec4(0.363f,4.695f,0.357f, 1.0f);
  glm::vec4 llum2 = View * Far2_TG * glm::vec4(-0.357f,4.695f,-0.348f, 1.0f);
  glm::vec3 colorLlum = glm::vec3(1.0,1.0,1.0);
  glUniform3fv(colorLlumFarLoc, 1, &colorLlum[0]);
  glUniform4fv(llumsFarLoc[0], 1, &llum1[0]);
  glUniform4fv(llumsFarLoc[1], 1, &llum2[0]);
}


void A3GLWidget::modelTransformFar1()
{
	// Codi per a la TG necessària
	glm::mat4 TG = glm::mat4(1.0f);
	TG = glm::translate(TG, glm::vec3(2, 1, 4));
	TG = glm::scale(TG, glm::vec3(escalaModels[FAR_1]) );
	TG = glm::translate(TG, -centreBaseModels[FAR_1]);
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
	
	glm::mat3 NormalMatrix = glm::inverse(glm::transpose(glm::mat3(View*TG)));
  glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &NormalMatrix[0][0]);
	
}

void A3GLWidget::modelTransformFar2()
{
	// Codi per a la TG necessària
	Far2_TG = glm::mat4(1.0f);
	Far2_TG = glm::translate(Far2_TG, glm::vec3(2, 1, 4));
	Far2_TG = glm::scale(Far2_TG, glm::vec3(escalaModels[FAR_1]) );
	Far2_TG = glm::rotate(Far2_TG, glm::radians(rotacioFar), glm::vec3(0,1,0));
	Far2_TG = glm::translate(Far2_TG, -centreBaseModels[FAR_1]);
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, &Far2_TG[0][0]);
	
	glm::mat3 NormalMatrix = glm::inverse(glm::transpose(glm::mat3(View*Far2_TG)));
  glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &NormalMatrix[0][0]);
	
}


void A3GLWidget::modelTransformVaixell()
{
	// Codi per a la TG necessària
	Vaixell_TG = glm::mat4(1.0f);
	Vaixell_TG = glm::translate(Vaixell_TG, VaixellPos);
	Vaixell_TG = glm::scale(Vaixell_TG, glm::vec3(escalaModels[VAIXELL]) );
	Vaixell_TG = glm::translate(Vaixell_TG,
		                -glm::vec3(centreBaseModels[VAIXELL].x,
		                           0,
		                           centreBaseModels[VAIXELL].z)); // el vaixell ja esta a la línia de flotació....no toquem en alçada
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, &Vaixell_TG[0][0]);
	
	glm::mat3 NormalMatrix = glm::inverse(glm::transpose(glm::mat3(View*Vaixell_TG)));
  glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &NormalMatrix[0][0]);
}

void A3GLWidget::updateTime(int Time){
	makeCurrent();
	horaActual = Time;
	emit setTime(horaActual);
	update();
}

void A3GLWidget::keyPressEvent(QKeyEvent* event)
{
	makeCurrent();

	switch (event->key()) {
		case Qt::Key_A: {
			rotacioFar += 10;
			break;
		}
		case Qt::Key_D: {
			rotacioFar -= 10;
			break;
		}
		case Qt::Key_S: {
			VaixellPos[2]+=1;break;
		}
		case Qt::Key_W: {
			VaixellPos[2]-=1;break;
		}
		case Qt::Key_Up:
			if (horaActual < 20) {
				horaActual++;
				emit setTime(horaActual);
			}
			break;
		case Qt::Key_Down:
			if (horaActual > 8) {
				horaActual--;
				emit setTime(horaActual);
			}
		break;
	default: event->ignore(); break;
	}
	update();
}


void A3GLWidget::carregaShaders()
{
	// Creem els shaders per al fragment shader i el vertex shader
	QOpenGLShader fs (QOpenGLShader::Fragment, this);
	QOpenGLShader vs (QOpenGLShader::Vertex, this);
	// Carreguem el codi dels fitxers i els compilem
	fs.compileSourceFile("./shaders/basicLlumShader.frag");
	vs.compileSourceFile("./shaders/basicLlumShader.vert");
	// Creem el program
	program = new QOpenGLShaderProgram(this);
	// Li afegim els shaders corresponents
	program->addShader(&fs);
	program->addShader(&vs);
	// Linkem el program
	program->link();
	// Indiquem que aquest és el program que volem usar
	program->bind();

	// Obtenim identificador per a l'atribut “vertex” del vertex shader
	vertexLoc = glGetAttribLocation (program->programId(), "vertex");
	// Obtenim identificador per a l'atribut “normal” del vertex shader
	normalLoc = glGetAttribLocation (program->programId(), "normal");
	// Obtenim identificador per a l'atribut “matamb” del vertex shader
	matambLoc = glGetAttribLocation (program->programId(), "matamb");
	// Obtenim identificador per a l'atribut “matdiff” del vertex shader
	matdiffLoc = glGetAttribLocation (program->programId(), "matdiff");
	// Obtenim identificador per a l'atribut “matspec” del vertex shader
	matspecLoc = glGetAttribLocation (program->programId(), "matspec");
	// Obtenim identificador per a l'atribut “matshin” del vertex shader
	matshinLoc = glGetAttribLocation (program->programId(), "matshin");

	// Demanem identificadors per als uniforms del vertex shader
	transLoc = glGetUniformLocation (program->programId(), "TG");
	projLoc = glGetUniformLocation (program->programId(), "proj");
	viewLoc = glGetUniformLocation (program->programId(), "view");
	normalMatrixLoc = glGetUniformLocation (program->programId(), "NM");
	colorLlumLoc = glGetUniformLocation (program->programId(), "colorFocus");
  	posLlumLoc = glGetUniformLocation (program->programId(), "posFocusSCO");
  	llumAmbientLoc = glGetUniformLocation (program->programId(), "llumAmbient");
	llumsFarLoc[0] = glGetUniformLocation (program->programId(), "posLlumsFarLoc1");
	llumsFarLoc[1] = glGetUniformLocation (program->programId(), "posLlumsFarLoc2");
	colorLlumFarLoc = glGetUniformLocation (program->programId(), "colorLlumFar");

	// Bloc d'uniforms
	// .... Enjoy !
}
