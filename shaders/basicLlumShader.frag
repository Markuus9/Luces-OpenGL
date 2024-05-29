#version 330 core

in vec3 fcolor;

in vec4 o_vertex_sco;
in vec3 o_normal_sco;

in vec3 o_matamb;
in vec3 o_matdiff;
in vec3 o_matspec;
in float o_matshin;

//in vec3 o_colorFocus;
in vec4 o_posFocus;

flat in int DrawWaves;

out vec3 FragColor;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;
uniform mat3 NM;
uniform vec3 colorFocus;
//uniform vec4 posFocusSCO;
uniform vec3 llumAmbient;
uniform vec3 colorLlumFar;
uniform vec4 posLlumsFarLoc1;
uniform vec4 posLlumsFarLoc2;
uniform vec4 posFocusTorxes[6];
uniform vec3 colorLlumsVaixell;
uniform int isDrawingSea;


vec3 Ambient() {
    return llumAmbient * o_matamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) 
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * o_matdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (o_matshin == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), o_matshin);
    return (o_matspec * colFocus * shine); 
}

vec3 WaveNormal(vec2 waveDirNN, float waveLength, vec3 vertex_world, float time){
        float steepness = .5;
	vec2 waveDir = normalize(waveDirNN);
	float wl = 2;
        float f = (2 * 3.14159/waveLength) * (dot(waveDir, vertex_world.xz) - 0.25 * time);

	vec3 B = vec3( 
		     1- (steepness*waveDir.x*waveDir.x * cos(f)) , 
		      waveDir.x * sin(f),
		     -steepness*waveDir.x*waveDir.y * cos(f)
			);
	vec3 T = vec3( 
		     -steepness*waveDir.x*waveDir.y * cos(f) , 
		      waveDir.y * sin(f),
		     1-steepness*waveDir.y*waveDir.y * cos(f)
			);	

	return normalize(cross(normalize(T), normalize(B)));
}

void main()
{	
	vec3 La = Ambient();

 	vec4 posFocusSCO = o_posFocus; 
	vec3 NormSCO = normalize(o_normal_sco);

  //Mar
  if(DrawWaves==1){
    // Calcular la normal de las ondas para este fragmento del mar
    vec3 waveNormal = WaveNormal(vec2(1.0, 1.0), 5.0, o_vertex_sco.xyz, 2.0);
    waveNormal += WaveNormal(vec2(1.0, 0.5), 2.0, o_vertex_sco.xyz, 2.0);
    vec3 waveNormalSCO = normalize(vec3(view * vec4(waveNormal, 0.0)));
    NormSCO = waveNormalSCO;
  }

	vec4 LSCO = normalize(posFocusSCO - o_vertex_sco);
	vec3 Ld = Difus(NormSCO, LSCO.xyz, colorFocus);
	vec3 Le = Especular(NormSCO, LSCO.xyz, o_vertex_sco, colorFocus);
	
  // LlumFar1
  vec4 LSCO2 = posLlumsFarLoc1 - o_vertex_sco;
  vec4 Dir1 = posLlumsFarLoc2 - posLlumsFarLoc1;
  LSCO2 = normalize(LSCO2);
  Dir1 = normalize(Dir1);

  float cosAngle1 = Dir1.x * (-LSCO2.x) + Dir1.y * (-LSCO2.y) + Dir1.z * (-LSCO2.z);
  float atenuacio1 = pow(cosAngle1, 4.0);
  vec3 Ld2 = vec3(0.0f);
  vec3 Le2 = vec3(0.0f);
  if (cosAngle1 > 0.0) {
      Ld2 = Difus(NormSCO, LSCO2.xyz, colorLlumFar) * atenuacio1;
      Le2 = Especular(NormSCO, LSCO2.xyz, o_vertex_sco, colorLlumFar) * atenuacio1;
  }

  // LlumFar2
  vec4 LSCO3 = posLlumsFarLoc2 - o_vertex_sco;
  vec4 Dir2 = posLlumsFarLoc1 - posLlumsFarLoc2;
  LSCO3 = normalize(LSCO3);
  Dir2 = normalize(Dir2);

  float cosAngle2 = Dir2.x * (-LSCO3.x) + Dir2.y * (-LSCO3.y) + Dir2.z * (-LSCO3.z);
  float atenuacio2 = pow(cosAngle2, 4.0);
  vec3 Ld3 = vec3(0.0f);
  vec3 Le3 = vec3(0.0f);
  if (cosAngle2 > 0.0) {
    Ld3 = Difus(NormSCO, LSCO3.xyz, colorLlumFar) * atenuacio2;
    Le3 = Especular(NormSCO, LSCO3.xyz, o_vertex_sco, colorLlumFar) * atenuacio2;
  }

  //LlumsVaixell
  vec3 torchesDiffuse = vec3(0.0f);
  vec3 torchesSpecular = vec3(0.0f);

  for (int i = 0; i < 6; i++) {
      vec3 lightDir = normalize(posFocusTorxes[i].xyz - o_vertex_sco.xyz);
      float distance = length(posFocusTorxes[i].xyz - o_vertex_sco.xyz);
      float attenuation = distance < 3.0 ? 1.0 : exp(-(distance - 3.0));

      torchesDiffuse += Difus(NormSCO, lightDir, colorLlumsVaixell) * attenuation;
      torchesSpecular += Especular(NormSCO, lightDir, o_vertex_sco, colorLlumsVaixell) * attenuation;
  }
  
	FragColor = La + Ld + Le + Ld2 + Le2 + Ld3 + Le3 + torchesDiffuse + torchesSpecular;
}

