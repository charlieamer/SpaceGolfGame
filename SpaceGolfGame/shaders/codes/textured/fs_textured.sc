$input v_color0, v_texcoord0

#include "bgfx_shader.sh"
SAMPLER2D(s_texture0, 0);

/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

void main()
{
	gl_FragColor = v_color0 * texture2D(s_texture0, v_texcoord0);
}
