#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;
uniform mat3 NM;
uniform vec3 colorFocus;
uniform vec4 posFocusSCO;
uniform vec3 llumAmbient;
uniform vec3 colorLlumFar;
uniform vec4 posLlumsFarLoc1;
uniform vec4 posLlumsFarLoc2;
uniform vec4 posFocusTorxes[6];
uniform vec3 colorLlumsVaixell;
uniform int isDrawingSea;

out vec3 fcolor;

out vec4 o_vertex_sco;
out vec3 o_normal_sco;

out vec3 o_matdiff;
out vec3 o_matamb;
out vec3 o_matspec;
out float o_matshin; 

//out vec3 o_colorFocus;
out vec4 o_posFocus;

flat out int DrawWaves;

vec3 Ambient() {
    return llumAmbient * matamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) 
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (matshin == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), matshin);
    return (matspec * colFocus * shine); 
}

void main()
{	
	vec3 La = Ambient();
	
  if(isDrawingSea==1 && normal.y>0.0){
    DrawWaves = 1;
  } else {
    DrawWaves = 0;
  }

	vec3 NormSCO = normalize(NM*normal);
	vec4 vertSCO = view * TG * vec4 (vertex, 1.0);
	vec4 LSCO = normalize(posFocusSCO - vertSCO);
	
	o_vertex_sco = vertSCO;
	o_normal_sco = NormSCO;
	
	o_matamb = matamb;
	o_matdiff = matdiff;
	o_matspec = matspec;
	o_matshin = matshin;
	
	//o_colorFocus = colorFocus;
	//o_llumAmbient = llumAmbient;
	o_posFocus = posFocusSCO;
	
	fcolor = matdiff;
	gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
