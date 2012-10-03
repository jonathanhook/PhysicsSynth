//
//  Shader.fsh
//  SoundClash
//
//  Created by Jonathan Hook on 03/10/2012.
//  Copyright (c) 2012 Jonathan Hook. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
