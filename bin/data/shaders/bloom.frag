uniform sampler2DRect texture;

void main()
{
    
    vec4 bloom;
    
    vec4 sum = vec4(0);

    vec2 texCoord = gl_TexCoord[0].xy;
    
    int i;
    
    int j;
          
    for (i = -2; i <2; i++){
        for (int j= -2; j < 2; j++){
            sum += texture2DRect(texture, texCoord + vec2(j, i)*0.004) * 0.25;
        }
    }
        
    if(texture2DRect(texture, texCoord).r < 0.3){ 
        bloom = sum*sum*0.012 + texture2DRect(texture, texCoord);
    }
        else{
            if(texture2DRect(texture,texCoord).r<0.5){
               bloom = sum*sum*0.009 + texture2DRect(texture, texCoord);
            }
                else{
                    bloom = sum*sum*0.0075 +  texture2DRect(texture, texCoord);
                }
            }
    
    gl_FragColor = vec4(bloom);
          
      }
