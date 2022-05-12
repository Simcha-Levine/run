#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 playerPos;
uniform sampler2D texture;
uniform float layer;

void main(){
    vec2 st=gl_FragCoord.xy/u_resolution.xy;
    st.x*=u_resolution.x/u_resolution.y;
    
    vec2 pt=playerPos.xy/u_resolution.xy;
    
    vec2 tc=gl_TexCoord[0].xy;
    
    tc.x=mod(tc.x+(pt.x*layer),1.);
    tc.y=tc.y+(-pt.y*layer*.4);
    
    vec4 color=texture2D(texture,tc).rgba;
    
    gl_FragColor=vec4(color);
}