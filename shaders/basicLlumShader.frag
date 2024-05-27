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

out vec4 FragColor;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;
uniform mat3 NM;
uniform vec3 colorFocus;
//uniform vec4 posFocusSCO;
uniform vec3 llumAmbient;

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
	
	vec4 posFocusSCO = o_posFocus; // posar view * vec4 (o_posFocus, 1.0) si la llum no prové de l'observador
	vec3 NormSCO = normalize(o_normal_sco);
	vec4 LSCO = normalize(posFocusSCO - o_vertex_sco);
	vec3 Ld = Difus(NormSCO, LSCO.xyz, colorFocus);
	
	vec3 Le = Especular(NormSCO, LSCO.xyz, o_vertex_sco, colorFocus);
	
	//FragColor = vec4(fcolor,1);
	FragColor = vec4(La + Ld + Le, 1);

}

