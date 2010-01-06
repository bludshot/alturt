// Q3MIN shaders for texture group 'base'

textures/base/bluegoal
{
{
map textures/base/bluegoal.tga
tcGen environment
blendfunc add
tcMod turb 0 0.25 0 0.05
}
}

textures/base/border11light
{
q3map_surfacelight 1000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base/border11light.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base/border11light.blend.tga
rgbGen wave sin 0.5 0.5 0 .2
blendfunc add
}
}

textures/base/ceil1_3
{
light 1
q3map_surfacelight 5000
{
map $lightmap
rgbGen identity
}
{
map textures/base/ceil1_3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base/ceil1_4
{
light 1
q3map_surfacelight 5000
{
map $lightmap
rgbGen identity
}
{
map textures/base/ceil1_4.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base/ceil1_8
{
light 1
q3map_surfacelight 500
{
map $lightmap
rgbGen identity
}
{
map textures/base/ceil1_8.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base/comp_panel
{
surfaceparm trans
light 1
q3map_surfacelight 500
{
map textures/base/comp_panel.tga
blendfunc blend
}
{
map textures/base/comp_panel.blend.tga
blendfunc add
}
}

textures/base/electricwall
{
light 1
q3map_surfacelight 400
{
map $lightmap
rgbGen identity
}
{
map textures/organics/wire02a_f.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/organics/wire02a_f.blend.tga
blendfunc add
}
{
map textures/base/electric.blend.tga
tcMod scroll 1 1 10 20
rgbGen wave sin 1 2 0 1
blendfunc add
}
}

textures/base/q1met_redpad
{
q3map_surfacelight 1500
{
map $lightmap
rgbGen identity
}
{
map textures/base/q1met_redpad.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base/q1met_redpad.blend.tga
blendfunc add
rgbGen wave sin 0.5 0.5 0 .2
}
}

textures/base/redgoal
{
{
map textures/base/redgoal.tga
tcGen environment
blendfunc add
tcMod turb 0 0.25 0 0.05
}
}

textures/base_button/shootme2
{
qer_editorimage textures/base_button/shootme1.tga
q3map_lightimage textures/base_button/shootme_glow.tga
q3map_surfacelight 1000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_support/metal3_3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_button/shootme_glow.tga
rgbGen wave sin 0.5 1.0 0 .3
blendfunc add
}
}

textures/base_light/btactmach0
{
q3map_surfacelight 1000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/btactmach0.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/btactmach0.blend.tga
rgbGen wave sin 0.5 0.5 0 .2
blendfunc add
}
}

textures/base_floor/clang_floor3blava
{
surfaceparm nolightmap
{
map textures/liquids/protolava2.tga
tcmod scale .2 .2
tcmod scroll .04 .03
tcMod turb 0 .1 0 .01
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_floor/clang_floor3blava.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
}
}

textures/base_floor/clang_floor_ow
{
surfaceparm metalsteps
{
map textures/sfx/proto_zzztblu2.tga
tcMod turb 0 .5 0 9.6
tcmod scale 2 2
tcmod scroll 9 5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_floor/clang_floor_ow.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_floor/clang_floor_ow3
{
surfaceparm metalsteps
{
map textures/sfx/proto_zzztblu2.tga
tcMod turb 0 .5 0 9.6
tcmod scale 2 2
tcmod scroll 9 5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_floor/clang_floor_ow3.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_floor/clang_floorshiny
{
qer_editorimage textures/base_floor/clang_floor.tga
{
map $lightmap
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_floor/clang_floorshiny_alpha.tga
blendFunc GL_ONE GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_floor/clang_floorshiny2
{
qer_editorimage textures/base_floor/clang_floor.tga
{
map $lightmap
tcGen environment
tcmod scale .25 .25
rgbgen identity
}
{
map textures/base_floor/clang_floorshiny_alpha2.tga
blendFunc GL_ONE GL_SRC_ALPHA
alphagen wave triangle .98 .02 0 10
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_floor/clang_floorwet
{
qer_editorimage textures/base_floor/clang_floor.tga
{
map textures/effects/tinfx3.tga
tcGen environment
rgbgen identity
}
{
map textures/base_floor/clang_floorwet.tga
blendFunc GL_ONE GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_floor/clangdark
{
surfaceparm metalsteps
{
map $lightmap
rgbGen identity
}
{
map textures/base_floor/clangdark.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_floor/clangdark_ow
{
surfaceparm metalsteps
{
map $lightmap
rgbGen identity
}
{
map textures/base_floor/clangdark_ow.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_floor/clangdark_ow3
{
surfaceparm metalsteps
{
map textures/sfx/proto_zzztblu2.tga
tcMod turb 0 .5 0 9.6
tcmod scale 2 2
tcmod scroll 9 5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_floor/clangdark_ow3.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_floor/clangdarkspot
{
surfaceparm metalsteps
{
map textures/liquids/proto_grueldark.tga
blendFunc GL_ONE GL_ZERO
tcmod scale 2 2
tcMod scroll .01 .03
tcMod turb 0 0.05 0 .05
}
{
map textures/effects/tinfx3.tga
blendfunc add
tcGen environment
}
{
map textures/base_floor/clangdarkspot.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_floor/clangfloor_noisy
{
qer_editorimage textures/base_floor/clang_floor.tga
surfaceparm metalsteps
{
map $lightmap
rgbGen identity
}
{
map textures/base_floor/clang_floor.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbgen identity
}
}

textures/base_floor/clangspot
{
surfaceparm metalsteps
qer_editorimage textures/base_floor/clangdarkspot.tga
{
map textures/liquids/proto_grueldark.tga
blendFunc GL_ONE GL_ZERO
tcmod scale 2 2
tcMod scroll .01 .03
tcMod turb 0 0.05 0 .05
}
{
map textures/effects/tinfx3.tga
blendfunc add
tcGen environment
}
{
map textures/base_floor/clangspot.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_floor/clangspot2
{
surfaceparm metalsteps
{
map textures/liquids/proto_grueldark.tga
blendFunc GL_ONE GL_ZERO
tcmod scale 2 2
tcMod scroll .01 .03
tcMod turb 0 0.05 0 .05
}
{
map textures/effects/tinfx3.tga
blendfunc add
tcGen environment
}
{
map textures/base_floor/clangspot2.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_floor/concretefloor1
{
{
map textures/base_wall/chrome_env.tga
tcgen environment
rgbgen wave sin .25 0 0 0
}
{
map textures/base_floor/concretefloor1.tga
blendFunc GL_ZERO GL_SRC_ALPHA
tcmod scale .1 .1
rgbgen identity
}
{
map textures/base_floor/concretefloor1.tga
blendFunc GL_ONE GL_SRC_ALPHA
tcmod turb sin .5 1 0 1
rgbgen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbgen identity
}
}

textures/base_floor/cybergrate
{
cull disable
surfaceparm alphashadow
surfaceparm metalsteps
surfaceparm nomarks
{
map textures/base_floor/cybergrate.tga
alphaFunc GT0
depthWrite
rgbGen vertex
}
{
map $lightmap
rgbGen identity
blendFunc filter
depthFunc equal
}
}

textures/base_floor/cybergrate2
{
cull disable
surfaceparm alphashadow
surfaceparm metalsteps
surfaceparm nomarks
{
map textures/base_floor/cybergrate2.tga
alphaFunc GT0
depthWrite
rgbGen vertex
}
{
map $lightmap
rgbGen identity
blendFunc filter
depthFunc equal
}
}

textures/base_floor/cybergrate3
{
cull disable
surfaceparm alphashadow
surfaceparm metalsteps
surfaceparm nomarks
{
map textures/sfx/hologirl.tga
blendFunc gl_one gl_one
tcmod scale 1.2 .5
tcmod scroll 3.1 1.1
}
{
map textures/base_floor/cybergrate3.tga
alphaFunc GT0
depthWrite
}
{
map $lightmap
rgbGen identity
blendFunc filter
depthFunc equal
}
}

textures/base_floor/diamond2c_ow
{
surfaceparm metalsteps
{
map textures/sfx/proto_zzztblu2.tga
tcMod turb 0 .5 0 9.6
tcmod scale 2 2
tcmod scroll 9 5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_floor/diamond2c_ow.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_floor/diamond2cspot
{
surfaceparm metalsteps
{
map textures/liquids/proto_grueldark2.tga
blendFunc GL_ONE GL_ZERO
tcmod scale 2 2
tcMod scroll .01 .03
tcMod turb 0 0.05 0 .05
}
{
map textures/effects/tinfx3.tga
blendfunc add
tcGen environment
}
{
map textures/base_floor/diamond2cspot.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_floor/diamond_dirty
{
qer_editorimage textures/base_floor/diamond2.tga
q3map_globaltexture
surfaceparm metalsteps
{
map $lightmap
rgbGen identity
}
{
map textures/base_floor/grunge2.tga
blendfunc GL_DST_COLOR GL_SRC_COLOR
rgbGen identity
detail
tcMod scale 0.0693 0.0712
}
{
map textures/base_floor/diamond2.tga
tcMod scale 0.5 0.5
blendfunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_floor/diamond_noisy
{
surfaceparm metalsteps
{
map $lightmap
rgbGen identity
}
{
map textures/base_floor/diamond2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_floor/floor3_3dark_ow
{
{
map textures/effects/envmapblue.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 5.6
tcmod scale 1.5 1.5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_floor/floor3_3dark_ow.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc filter
rgbGen identity
}
}

textures/base_floor/glowfloor2
{
q3map_surfacelight 800
q3map_lightimage base_floor/glowfloor2.tga
{
map $lightmap
rgbGen identity
}
{
map textures/base_wall/metalfloor_wall_15.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_floor/glowred1.blend.tga
blendfunc add
rgbGen wave sin 0.5 0.1 1 0.5
}
}

textures/base_floor/glowfloor3
{
q3map_surfacelight 500
{
map $lightmap
rgbGen identity
}
{
map textures/base_floor/diamond2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_floor/glowred1.blend.tga
blendfunc add
rgbGen wave sin 0.5 0.1 1 0.5
}
}

textures/base_floor/hfloor3
{
{
rgbGen identity
map $lightmap
}
{
map textures/base_floor/hfloor3.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
{
map textures/effects/tinfx.tga
tcgen environment
blendfunc add
rgbGen identity
}
{
map textures/base_floor/hfloor3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_floor/kc_grate4b
{
surfaceparm metalsteps
surfaceparm alphashadow
surfaceparm trans
surfaceparm nonsolid
cull none
{
map textures/base_floor/kc_grate4b.tga
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc filter
depthFunc equal
}
}

textures/base_floor/metalbridge04dbroke
{
surfaceparm metalsteps
{
map textures/sfx/proto_zzztblu2.tga
tcMod turb 0 .5 0 9.6
tcmod scale 2 2
tcmod scroll 9 5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_floor/metalbridge04dbroke.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_floor/nomarkstone_1
{
qer_editorimage textures/base_floor/nomarkstone.tga
q3map_lightimage textures/base_floor/smallstone.tga
q3map_globaltexture
surfaceparm nomarks
surfaceparm noimpact
{
map $lightmap
rgbGen identity
}
{
map textures/base_floor/smallstone.tga
tcMod scale 2 2
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_floor/pjgrate1
{
surfaceparm metalsteps
cull none
{
map textures/base_floor/pjgrate1.tga
tcMod scale 2 2
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/pjgrate1kc
{
qer_editorimage textures/base_floor/proto_grate5.tga
surfaceparm metalsteps
cull none
{
map textures/base_floor/proto_grate5.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/pjgrate2
{
surfaceparm metalsteps
cull none
{
map textures/base_floor/pjgrate2.tga
tcMod scale 2.0 2.0
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
rgbGen identity
}
}

textures/base_floor/pool_floor2
{
{
map textures/liquids/pool3d_5e.tga
tcmod scale -.25 -.25
tcmod scroll .025 .025
rgbgen wave sin .75 0 0 0
}
{
map textures/liquids/pool3d_6e.tga
blendfunc add
tcmod scale .25 .25
tcmod scroll .025 .025
rgbgen wave sin .75 0 0 0
}
{
map textures/base_floor/pool_floor2.tga
blendFunc GL_one GL_src_color
rgbgen identity
}
{
rgbGen identity
map $lightmap
blendfunc gl_dst_color gl_zero
}
}

textures/base_floor/pool_floor3
{
qer_editorimage textures/base_wall/patch10rusty5.tga
{
map textures/liquids/pool3d_5e.tga
tcmod scale -.25 -.25
tcmod scroll .025 .025
rgbgen wave sin .75 0 0 0
}
{
map textures/liquids/pool3d_6e.tga
blendfunc add
tcmod scale .25 .25
tcmod scroll .025 .025
rgbgen wave sin .75 0 0 0
}
{
map textures/base_wall/patch10rusty5.tga
blendFunc GL_one GL_src_color
rgbgen identity
}
{
rgbGen identity
map $lightmap
blendfunc gl_dst_color gl_zero
}
}

textures/base_floor/pool_side2
{
{
map textures/liquids/pool3d_5e.tga
tcmod scale -.5 -.25
tcmod scroll .025 .025
rgbgen wave sin .75 0 0 0
}
{
map textures/liquids/pool3d_6e.tga
blendfunc add
tcmod scale .5 .25
tcmod scroll .025 .025
rgbgen wave sin .75 0 0 0
}
{
map textures/base_floor/pool_side2.tga
blendFunc GL_one GL_src_color
tcmod scale .5 .5
rgbgen identity
}
{
rgbGen identity
map $lightmap
blendfunc gl_dst_color gl_zero
}
}

textures/base_floor/pool_side3
{
qer_editorimage textures/base_wall/patch10rusty5.tga
{
map textures/liquids/pool3d_5e.tga
tcmod scale -.5 -.25
tcmod scroll .025 .025
rgbgen wave sin .75 0 0 0
}
{
map textures/liquids/pool3d_6e.tga
blendfunc add
tcmod scale .5 .25
tcmod scroll .025 .025
rgbgen wave sin .75 0 0 0
}
{
map textures/base_wall/patch10rusty5.tga
blendFunc GL_one GL_src_color
tcmod scale .5 .5
rgbgen identity
}
{
rgbGen identity
map $lightmap
blendfunc gl_dst_color gl_zero
}
}

textures/base_floor/proto_grate
{
surfaceparm metalsteps
surfaceparm trans
cull none
nopicmip
{
map textures/base_floor/proto_grate.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/proto_grate2
{
surfaceparm metalsteps
surfaceparm trans
cull none
nopicmip
{
map textures/base_floor/proto_grate2.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/proto_grate3
{
surfaceparm metalsteps
surfaceparm trans
cull none
nopicmip
{
map textures/base_floor/proto_grate3.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/proto_grate4
{
surfaceparm metalsteps
surfaceparm trans
surfaceparm nonsolid
cull none
nopicmip
{
map textures/base_floor/proto_grate4.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/proto_grate5
{
surfaceparm metalsteps
surfaceparm trans
cull none
nopicmip
{
map textures/base_floor/proto_grate5.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/proto_rustygrate
{
surfaceparm metalsteps
surfaceparm trans
surfaceparm alphashadow
cull none
nopicmip
{
map textures/base_floor/proto_rustygrate.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/proto_rustygrate2
{
surfaceparm metalsteps
surfaceparm trans
surfaceparm alphashadow
cull none
nopicmip
{
map textures/base_floor/proto_rustygrate2.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/proto_skullgrate
{
surfaceparm metalsteps
surfaceparm trans
cull none
nopicmip
{
map textures/base_floor/proto_skullgrate.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/rusty_baphograte
{
surfaceparm metalsteps
surfaceparm trans
cull none
nopicmip
{
map textures/base_floor/rusty_baphograte.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
{
map textures/base_floor/rusty_baphograte2.tga
blendfunc add
rgbgen wave inversesawtooth 0 1 .2 .5
}
{
map textures/base_floor/rusty_baphograte3.tga
blendfunc add
rgbgen wave inversesawtooth 0 1 .4 .5
}
}

textures/base_floor/rusty_pentagrate
{
surfaceparm metalsteps
surfaceparm trans
surfaceparm alphashadow
cull none
nopicmip
{
map textures/base_floor/rusty_pentagrate.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/skylight1
{
q3map_lightimage textures/base_floor/skylight1_lm.tga
q3map_surfacelight 100
{
map $lightmap
rgbGen identity
}
{
map textures/base_floor/skylight1.tga
blendfunc gl_dst_color gl_zero
rgbGen identity
}
{
map textures/base_floor/skylight1_lm.tga
blendfunc add
rgbgen wave triangle .2 2 0 7.7
}
{
map textures/base_floor/skylight1_lm.tga
blendfunc add
rgbgen wave triangle .2 5 1 5.1
}
}

textures/base_floor/skylight_spec
{
{
rgbGen identity
map $lightmap
}
{
map textures/base_floor/skylight_spec.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_floor/techfloor
{
surfaceparm metalsteps
{
map textures/sfx/proto_zzztpink.tga
tcMod turb 0 .5 0 9.6
tcmod scale 2 2
tcmod scroll 9 5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
clampmap textures/base_floor/techfloor2.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
tcmod rotate 170
tcMod stretch sin .8 0.2 0 .4
rgbGen identity
}
{
map textures/base_floor/techfloor.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/techfloor2
{
cull disable
surfaceparm nomarks
{
clampmap textures/base_floor/techfloor2.tga
alphaFunc GT0
tcmod rotate 70
tcMod stretch sin .8 0.2 0 .3
rgbGen identity
}
{
clampmap textures/base_floor/techfloor2.tga
alphaFunc GT0
tcmod rotate -50
tcMod stretch sin .8 0.2 0 .2
rgbGen identity
}
{
clampmap textures/base_floor/techfloor2.tga
alphaFunc GT0
tcmod rotate 30
tcMod stretch sin .8 0.2 0 .1
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_floor/tile5_plain
{
qer_editorimage textures/base_floor/tilefloor5.tga
{
rgbGen identity
map $lightmap
}
{
map textures/base_floor/tilefloor5.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_floor/tilefloor5
{
{
rgbGen identity
map $lightmap
}
{
map textures/base_floor/tilefloor5.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_floor/tilefloor7_ow
{
q3map_lightimage textures/base_floor/tilefloor7_owfx.tga
q3map_surfacelight 100
{
map $lightmap
rgbGen identity
}
{
map textures/base_floor/tilefloor7_ow.tga
blendfunc gl_dst_color gl_zero
rgbGen identity
}
{
map textures/base_floor/tilefloor7_owfx.tga
blendfunc add
rgbgen wave triangle 1 2 0 7
}
{
map textures/base_floor/tilefloor7_owfx.tga
blendfunc add
rgbgen wave triangle 1 5 1 3
}
}

textures/base_light/baslt3_1_2K
{
qer_editorimage textures/base_light/baslt3_1.tga
surfaceparm nomarks
q3map_surfacelight 2000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/baslt3_1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/baslt3_1.blend.tga
blendfunc add
}
}

textures/base_light/baslt4_1_2k
{
qer_editorimage textures/base_light/baslt4_1.tga
surfaceparm nomarks
q3map_surfacelight 2000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/baslt4_1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/baslt4_1.blend.tga
blendfunc add
}
}

textures/base_light/baslt4_1_4k
{
qer_editorimage textures/base_light/baslt4_1.tga
surfaceparm nomarks
q3map_surfacelight 4000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/baslt4_1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/baslt4_1.blend.tga
blendfunc add
}
}

textures/base_light/border11light
{
q3map_surfacelight 500
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/border11light.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/border11light.blend.tga
blendfunc add
}
}

textures/base_light/border11light_300
{
qer_editorimage textures/base_light/border11light.tga
q3map_lightimage textures/base_light/border11light.blend.tga
q3map_surfacelight 235
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/border11light.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/border11light.blend.tga
blendfunc add
}
}

textures/base_light/border7_ceil50
{
qer_editorimage textures/base_light/border7_ceil50.tga
q3map_surfacelight 100
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/border7_ceil50.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/border7_ceil50glow.tga
blendfunc add
}
}

textures/base_light/ceil1_2
{
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_2.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_22a
{
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_22a.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_22a.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_22a_8k
{
surfaceparm nomarks
qer_editorimage textures/base_light/ceil1_22a
q3map_surfacelight 8000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_22a.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_22a.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_22a_trans
{
qer_editorimage textures/base_light/ceil1_22a.tga
surfaceparm nomarks
surfaceparm nonsolid
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_22a.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_22a.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_26
{
surfaceparm nomarks
q3map_surfacelight 10000
light1
}

textures/base_light/ceil1_28
{
surfaceparm nomarks
q3map_surfacelight 10000
light1
}

textures/base_light/ceil1_3
{
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_3.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_30
{
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_30.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_30.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_30_8k
{
surfaceparm nomarks
qer_editorimage textures/base_light/ceil1_30
q3map_surfacelight 8000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_30.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_30.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_30_trans
{
qer_editorimage textures/base_light/ceil1_30.tga
surfaceparm nomarks
surfaceparm nonsolid
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_30.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_30.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_31
{
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_31.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_31.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_32
{
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_32.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_32.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_33
{
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_33.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_33.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_34
{
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_34.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_34.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_34_10k
{
qer_editorimage textures/base_light/ceil1_34.tga
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_34.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_34.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_34_1k
{
qer_editorimage textures/base_light/ceil1_34.tga
q3map_lightimage textures/base_light/ceil1_34.blend.tga
surfaceparm nomarks
q3map_surfacelight 1000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_34.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_34.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_34_2k
{
qer_editorimage textures/base_light/ceil1_34.tga
q3map_lightimage textures/base_light/ceil1_34.blend.tga
surfaceparm nomarks
q3map_surfacelight 2000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_34.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_34.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_34_5k
{
qer_editorimage textures/base_light/ceil1_34.tga
surfaceparm nomarks
q3map_surfacelight 5000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_34.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_34.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_35
{
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_35.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_35.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_37
{
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_37.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_37.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_38
{
surfaceparm nomarks
q3map_surfacelight 2500
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_38.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_38.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_38_10k
{
qer_editorimage textures/base_light/ceil1_38.tga
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_38.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_38.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_38_20k
{
qer_editorimage textures/base_light/ceil1_38.tga
surfaceparm nomarks
q3map_surfacelight 20000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_38.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_38.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_38_30k
{
qer_editorimage textures/base_light/ceil1_38.tga
surfaceparm nomarks
q3map_surfacelight 30000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_38.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_38.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_38_40k
{
qer_editorimage textures/base_light/ceil1_38.tga
surfaceparm nomarks
q3map_surfacelight 40000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_38.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_38.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_38_50k
{
qer_editorimage textures/base_light/ceil1_38.tga
surfaceparm nomarks
q3map_surfacelight 50000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_38.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_38.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_38_70k
{
qer_editorimage textures/base_light/ceil1_38.tga
surfaceparm nomarks
q3map_surfacelight 70000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_38.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_38.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_38_90k
{
qer_editorimage textures/base_light/ceil1_38.tga
surfaceparm nomarks
q3map_surfacelight 90000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_38.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_38.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_39
{
surfaceparm nomarks
q3map_surfacelight 7500
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_4
{
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_4.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_4.blend.tga
blendfunc add
}
}

textures/base_light/ceil1_6
{
surfaceparm nomarks
q3map_surfacelight 10000
light1
}

textures/base_light/ceil_white5k
{
qer_editorimage textures/base_light/ceil1_38.tga
surfaceparm nomarks
q3map_surfacelight 5000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_38.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_38.blend.tga
blendfunc add
}
}

textures/base_light/cornerlight
{
q3map_lightimage textures/base_light/cornerlight.glow.tga
surfaceparm nomarks
q3map_surfacelight 2500
{
map textures/base_light/cornerlight.tga
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
{
map textures/base_light/cornerlight.glow.tga
blendfunc add
rgbgen wave sawtooth .6 .1 0 7
}
}

textures/base_light/dm18twr
{
q3map_lightimage textures/base_light/dm18twr_glow.tga
surfaceparm nomarks
q3map_surfacelight 4000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/dm18twr.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
{
map textures/base_light/dm18twr_glow.tga
blendFunc gl_one gl_one
rgbgen wave sin .575 .025 0 10
}
}

textures/base_light/geolight
{
q3map_lightimage textures/base_light/geolight_glow.tga
surfaceparm nomarks
q3map_surfacelight 4000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/geolight.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
{
map textures/base_light/geolight_glow.tga
blendFunc gl_one gl_one
rgbgen wave sin .575 .025 0 10
}
}

textures/base_light/invisi_light1
{
qer_editorimage base_light/ceil1_30.tga
qer_trans 50
surfaceparm nomarks
q3map_surfacelight 50000
light 1
}

textures/base_light/jaildr01_3
{
surfaceparm nomarks
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/jaildr01_3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/jaildr01_3.blend.tga
rgbGen wave sin 0.5 0.5 1 1
blendfunc add
}
}

textures/base_light/jaildr02_3
{
surfaceparm nomarks
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/jaildr02_3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/jaildr02_3.blend.tga
rgbGen wave sin 0.5 0.5 1 1
blendfunc add
}
}

textures/base_light/jaildr03_1
{
surfaceparm nomarks
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/jaildr03_1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/jaildr03_1.tga
rgbGen wave sin 0.5 0.5 1 1
blendfunc add
}
}

textures/base_light/jaildr03_2
{
surfaceparm nomarks
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/jaildr03_2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/jaildr03_2.blend.tga
rgbGen wave sin 0.5 0.5 1 1
blendfunc add
}
}

textures/base_light/jaildr1_3
{
surfaceparm nomarks
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/jaildr1_3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/jaildr1_3.blend.tga
rgbGen wave sin 0.5 0.5 1 1
blendfunc add
}
}

textures/base_light/jaildr2_3
{
surfaceparm nomarks
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/jaildr2_3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/jaildr2_3.blend.tga
blendfunc add
}
}

textures/base_light/light1_1500
{
qer_editorimage textures/base_light/light1.tga
light 1
surfaceparm nomarks
q3map_surfacelight 1500
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light1.blend.tga
blendfunc add
}
}

textures/base_light/light1_3000
{
qer_editorimage textures/base_light/light1.tga
light 1
surfaceparm nomarks
q3map_surfacelight 1500
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light1.blend.tga
blendfunc add
}
}

textures/base_light/light1_5000
{
qer_editorimage textures/base_light/light1.tga
q3map_lightimage textures/base_light/light1.blend.tga
surfaceparm nomarks
q3map_surfacelight 5000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light1.blend.tga
blendfunc add
}
}

textures/base_light/light1blue_1500
{
qer_editorimage textures/base_light/light1blue.tga
q3map_lightimage textures/base_light/light1blue.blend.tga
surfaceparm nomarks
q3map_surfacelight 1500
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light1blue.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light1blue.blend.tga
blendfunc add
}
}

textures/base_light/light1blue_2000
{
qer_editorimage textures/base_light/light1blue.tga
q3map_lightimage textures/base_light/light1blue.blend.tga
surfaceparm nomarks
q3map_surfacelight 2000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light1blue.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light1blue.blend.tga
blendfunc add
}
}

textures/base_light/light1blue_5000
{
qer_editorimage textures/base_light/light1blue.tga
q3map_lightimage textures/base_light/light1blue.blend.tga
surfaceparm nomarks
q3map_surfacelight 5000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light1blue.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light1blue.blend.tga
blendfunc add
}
}

textures/base_light/light1blue_800
{
qer_editorimage textures/base_light/light1blue.tga
q3map_lightimage textures/base_light/light1blue.blend.tga
surfaceparm nomarks
q3map_surfacelight 800
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light1blue.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light1blue.blend.tga
blendfunc add
}
}

textures/base_light/light1dark
{
qer_editorimage textures/base_light/light1.tga
q3map_lightimage textures/base_light/light1.blend.tga
surfaceparm nomarks
q3map_surfacelight 6000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light1.blend.tga
blendfunc add
}
}

textures/base_light/light1red_2000
{
qer_editorimage textures/base_light/light1red.tga
q3map_lightimage textures/base_light/light1red.blend.tga
surfaceparm nomarks
q3map_surfacelight 2000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light1red.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light1red.blend.tga
blendfunc add
}
}

textures/base_light/light1red_5000
{
qer_editorimage textures/base_light/light1red.tga
q3map_lightimage textures/base_light/light1red.blend.tga
surfaceparm nomarks
q3map_surfacelight 5000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light1red.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light1red.blend.tga
blendfunc add
}
}

textures/base_light/light2blue_2500
{
qer_editorimage textures/base_light/light1blue.tga
q3map_lightimage textures/base_light/light1blue1.blend.tga
surfaceparm nomarks
q3map_surfacelight 2500
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light1blue.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light1blue1.blend.tga
blendfunc add
}
}

textures/base_light/light3b_2500
{
qer_editorimage textures/base_light/light3b.tga
light 1
surfaceparm nomarks
q3map_surfacelight 2500
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light3b.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light3b.blend.tga
blendfunc add
}
}

textures/base_light/light4_2500
{
qer_editorimage textures/base_light/light4.tga
light 1
surfaceparm nomarks
q3map_surfacelight 2500
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light4.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light4.blend.tga
rgbGen wave sin 0.5 0.5 0 3
blendfunc add
}
}

textures/base_light/light5_10k
{
qer_editorimage textures/base_light/light5.tga
q3map_lightimage textures/base_light/xlight5.blend.tga
light 1
surfaceparm nomarks
q3map_surfacelight 10000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/xlight5.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/xlight5.blend.tga
blendfunc add
}
}

textures/base_light/light5_15k
{
qer_editorimage textures/base_light/light5.tga
q3map_lightimage textures/base_light/light5.blend.tga
light 1
surfaceparm nomarks
q3map_surfacelight 15000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light5.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light5.tga
blendfunc add
}
}

textures/base_light/light5_20k
{
qer_editorimage textures/base_light/light5.tga
light 1
surfaceparm nomarks
q3map_surfacelight 20000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light5.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light5.blend.tga
blendfunc add
}
}

textures/base_light/light5_3000
{
qer_editorimage textures/base_light/light5.tga
light 1
surfaceparm nomarks
q3map_surfacelight 3000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/xlight5.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/xlight5.blend.tga
blendfunc add
}
}

textures/base_light/light5_5k
{
qer_editorimage textures/base_light/light5.tga
surfaceparm nomarks
surfaceparm nolightmap
q3map_backsplash 0 0
q3map_surfacelight 5000
{
map textures/base_light/light5.tga
rgbGen identity
}
}

textures/base_light/light6_2500
{
qer_editorimage textures/base_light/light6.tga
light 1
surfaceparm nomarks
q3map_surfacelight 2500
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light6.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light6.blend.tga
blendfunc add
}
}

textures/base_light/lightflare_500
{
qer_editorimage textures/base_light/light_flare.tga
deformVertexes autoSprite
q3map_surfacelight 500
surfaceparm trans
surfaceparm nomarks
surfaceparm nolightmap
cull none
{
Map textures/base_light/light_flare.tga
blendfunc add
}
}

textures/base_light/lightflare_wht500
{
qer_editorimage textures/base_light/light_flare.tga
q3map_lightimage textures/base_light/light1.blend.tga
deformVertexes autoSprite
q3map_surfacelight 500
surfaceparm trans
surfaceparm nomarks
surfaceparm nolightmap
cull none
{
Map textures/base_light/light_flare.tga
blendfunc add
}
}

textures/base_light/lt2_2000
{
qer_editorimage textures/base_light/light2.tga
light 1
surfaceparm nomarks
q3map_surfacelight 2000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light2.blend.tga
rgbGen wave sin 0.6 0.1 .1 .1
blendfunc add
}
}

textures/base_light/lt2_4000
{
qer_editorimage textures/base_light/light2.tga
surfaceparm nomarks
q3map_surfacelight 4000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light2.blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/base_light/lt2_8000
{
qer_editorimage textures/base_light/light2.tga
light 1
surfaceparm nomarks
q3map_surfacelight 8000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light2.blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/base_light/lt6_2500
{
qer_editorimage textures/base_light/light6.tga
light 1
surfaceparm nomarks
q3map_surfacelight 2500
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light6.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light6.blend.tga
blendfunc add
}
}

textures/base_light/lt6_2p5k
{
qer_editorimage textures/base_light/light6.tga
light 1
surfaceparm nomarks
q3map_surfacelight 5000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/light6.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/light6.blend.tga
blendfunc add
}
}

textures/base_light/patch10_pj_lite
{
q3map_surfacelight 2500
surfaceparm nomarks
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/patch10_pj_lite.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/patch10_pj_lite.blend.tga
blendfunc add
}
}

textures/base_light/patch10_pj_lite2
{
q3map_surfacelight 2000
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/patch10_pj_lite2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/patch10_pj_lite2.blend.tga
blendfunc add
}
}

textures/base_light/patch10_pj_lite2_1000
{
qer_editorimage textures/base_light/patch10_pj_lite2.tga
q3map_surfacelight 1000
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/patch10_pj_lite2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/patch10_pj_lite2.blend.tga
blendfunc add
}
}

textures/base_light/pj_wstlt1_3k
{
qer_editorimage textures/base_light/wstlt1_5.tga
q3map_lightimage textures/base_light/wstlt1_5.blend.tga
q3map_surfacelight 3000
surfaceparm nomarks
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/wstlt1_5.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/wstlt1_5.blend.tga
blendfunc add
}
}

textures/base_light/pjceil1_39_1K
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 1000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/pjceil1_39_1p5k
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 1500
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/proto_bulb
{
deformVertexes autoSprite2
surfaceparm trans
surfaceparm nomarks
surfaceparm nolightmap
cull none
{
map textures/base_light/proto_bulb.tga
blendfunc add
}
}

textures/base_light/proto_light
{
q3map_lightimage textures/base_light/proto_lightmap.tga
surfaceparm nomarks
q3map_surfacelight 1000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/proto_light.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/proto_lightmap.tga
blendfunc add
rgbGen wave sin .5 0.5 1 .1
}
{
map textures/base_light/proto_light2.tga
blendfunc add
rgbgen wave triangle 1 5 1 3
}
{
map textures/base_light/proto_light2.tga
blendfunc add
tcmod scale -1 -1
rgbgen wave triangle 1 2 0 7
}
}

textures/base_light/proto_light_2k
{
qer_editorimage textures/base_light/proto_light.tga
q3map_lightimage textures/base_light/proto_lightmap.tga
surfaceparm nomarks
q3map_surfacelight 2000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/proto_light.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/proto_lightmap.tga
blendfunc add
rgbGen wave sin .5 0.5 1 .1
}
{
map textures/base_light/proto_light2.tga
blendfunc add
rgbgen wave triangle 1 5 1 3
}
{
map textures/base_light/proto_light2.tga
blendfunc add
tcmod scale -1 -1
rgbgen wave triangle 1 2 0 7
}
}

textures/base_light/proto_lightgreen
{
q3map_lightimage textures/base_light/proto_lightgreen.tga
surfaceparm nomarks
q3map_surfacelight 300
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/proto_lightgreen.tga
blendFunc filter
rgbGen identity
}
{
map textures/base_light/proto_lightgreen.tga
blendFunc gl_one gl_one
}
}

textures/base_light/proto_lightred
{
q3map_lightimage textures/base_light/proto_lightred.tga
surfaceparm nomarks
q3map_surfacelight 300
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/proto_lightred.tga
blendFunc filter
rgbGen identity
}
{
map textures/base_light/proto_lightred.tga
blendFunc gl_one gl_one
}
}

textures/base_light/proto_lightred2
{
q3map_lightimage textures/base_light/proto_lightred.tga
qer_editorimage textures/base_light/proto_lightred.tga
surfaceparm nomarks
q3map_surfacelight 1000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/proto_lightred.tga
blendFunc filter
rgbGen identity
}
{
map textures/base_light/proto_lightred.tga
blendFunc gl_one gl_one
rgbGen wave square .5 .5 0 1
}
}

textures/base_light/runway
{
q3map_lightimage textures/base_light/runway_glow.tga
surfaceparm nomarks
q3map_surfacelight 400
{
map textures/base_light/runway_glow.tga
tcmod scale 1 .25
rgbgen wave square -1 2 .5 8
tcmod scroll 0 .5
}
{
map textures/base_light/runway.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendfunc filter
}
{
map textures/base_light/runwayb.tga
blendFunc gl_one gl_one
rgbGen identity
}
}

textures/base_light/s_proto_light
{
q3map_lightimage textures/base_light/s_proto_lightmap.tga
surfaceparm nomarks
q3map_surfacelight 100
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/proto_light.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/proto_lightmap.tga
blendfunc add
rgbGen wave sin .5 0.5 1 .1
}
{
map textures/base_light/proto_light2.tga
blendfunc add
rgbgen wave triangle 1 5 1 3
}
{
map textures/base_light/proto_light2.tga
blendfunc add
tcmod scale -1 -1
rgbgen wave triangle 1 2 0 7
}
}

textures/base_light/scrolllight
{
q3map_lightimage textures/sfx/scrolllight2.tga
q3map_surfacelight 100
{
map $lightmap
rgbGen identity
}
{
Map textures/base_light/scrolllight.tga
blendfunc gl_dst_color gl_zero
rgbGen identity
}
{
Map textures/base_light/scrolllight2.tga
blendfunc add
tcmod scroll -1 0
}
{
Map textures/base_light/scrolllight2.tga
blendfunc add
tcmod scroll -2 0
}
}

textures/base_light/shi
{
surfaceparm trans
surfaceparm nomarks
surfaceparm nolightmap
cull disable
{
map textures/base_light/shi.tga
blendfunc add
tcmod scale .5 .5
rgbgen wave triangle 1 5.1 1 3
}
{
map textures/base_light/shi.tga
blendfunc add
tcmod scale .5 .5
rgbgen wave triangle 1 2 0 7.3
}
}

textures/base_light/sm_light1blue
{
light 1
surfaceparm nomarks
q3map_surfacelight 2500
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/sm_light1blue.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/sm_light1blue.blend.tga
blendfunc add
}
}

textures/base_light/sm_light1red
{
light 1
surfaceparm nomarks
q3map_surfacelight 2500
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/sm_light1red.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/sm_light1red.blend.tga
blendfunc add
}
}

textures/base_light/steedmetallight
{
q3map_surfacelight 2000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/steedmetallight.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/steedmetallight.blend.tga
rgbGen wave sin 0.5 0.5 0 .2
blendfunc add
}
}

textures/base_light/tlight05
{
surfaceparm nomarks
q3map_surfacelight 5000
light1
}

textures/base_light/trianglelight
{
q3map_lightimage textures/base_light/trianglelight.blend.tga
surfaceparm nomarks
q3map_surfacelight 2500
{
map textures/base_light/trianglelight.tga
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
{
map textures/base_light/trianglelight.blend.tga
blendfunc add
rgbgen wave sawtooth .6 .1 0 7
}
}

textures/base_light/wstlt1_5
{
q3map_surfacelight 2000
surfaceparm nomarks
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/wstlt1_5.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/wstlt1_5.blend.tga
blendfunc add
}
}

textures/base_light/wsupprt1_12
{
surfaceparm nomarks
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/wsupprt1_12.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/wsupprt1_12.blend.jpg
rgbGen wave sin 0.5 0.5 1 1
blendfunc add
}
}

textures/base_light/wsupprt1_12h
{
surfaceparm nomarks
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/wsupprt1_12h.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/wsupprt1_12h.blend.tga
rgbGen wave sin 0.5 0.5 1 1
blendfunc add
}
}

textures/base_light/xceil1_39
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 20000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_1
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_10k
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 10000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_110k
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 110000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_15k
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 15000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_20k
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 20000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_2k
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 2000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_30k
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 30000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_500k
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 500000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_50k
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 50000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_5k
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 5000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_70k
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 70000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_90k
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 90000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_a
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 30000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_light/xceil1_39_b
{
qer_editorimage textures/base_light/ceil1_39.tga
surfaceparm nomarks
q3map_surfacelight 40000
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_light/ceil1_39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_light/ceil1_39.blend.tga
blendfunc add
}
}

textures/base_object/boxQ3_1
{
{
map $lightmap
rgbGen identity
}
{
map textures/base_object/boxQ3_1.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_object/boxQ3_2
{
q3map_surfacelight 200
{
map $lightmap
rgbGen identity
}
{
map textures/base_object/boxQ3_2.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
{
map textures/base_object/boxQ3_2.blend.tga
blendfunc add
rgbGen wave sin 0.5 0.5 0 .2
}
}

textures/base_object/boxQ3_3
{
{
map $lightmap
rgbGen identity
}
{
map textures/base_object/boxQ3_3.tga
rgbGen identity
alphaGen lightingSpecular
blendFunc GL_DST_COLOR GL_SRC_ALPHA
}
}

textures/base_object/boxq3_4
{
{
map $lightmap
rgbGen identity
}
{
map textures/base_object/boxq3_4.tga
rgbGen identity
alphaGen lightingSpecular
blendFunc GL_DST_COLOR GL_SRC_ALPHA
}
}

textures/base_object/hastesign_1
{
qer_editorimage base_object/hastesign1.tga
q3map_lightimage textures/base_object/hastesign1.blend.tga
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/base_object/hastesign1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_object/hastesign1.blend.tga
rgbGen wave triangle 0.5 0.5 0.5 0.15
blendfunc add
}
}

textures/base_object/plasmalogo_1
{
q3map_lightimage textures/base_object/plasmalogo.tga
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/base_object/plasmalogo_1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_object/plasmalogo.tga
rgbGen wave triangle 0.5 0.5 0.5 0.15
blendfunc add
}
}

textures/base_object/quadsign_1
{
qer_editorimage base_object/quadsign1.tga
q3map_lightimage textures/base_object/quadsign1.blend.tga
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/base_object/quadsign1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_object/quadsign1.blend.tga
rgbGen wave triangle 0.5 0.5 0.5 0.15
blendfunc add
}
}

textures/base_support/cable_trans
{
surfaceparm nonsolid
{
map $lightmap
rgbGen identity
}
{
map textures/base_support/cable_trans.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_support/grate1_3
{
{
map $lightmap
rgbgen identity
}
{
map textures/base_support/grate1_3.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
alphaGen lightingSpecular
rgbGen identity
}
}

textures/base_support/metal1_5
{
surfaceparm metalsteps
}

textures/base_support/pj_metal14_1
{
surfaceparm metalsteps
{
map $lightmap
rgbGen identity
}
{
map textures/base_support/metal14_1.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_support/shinysupport1
{
{
map $lightmap
tcgen environment
tcmod scale .25 .25
rgbgen identity
}
{
map textures/base_support/shinysupport1.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_support/shinysupport2
{
{
map textures/base_wall/chrome_env.tga
rgbgen identity
}
{
map textures/base_support/shinysupport2.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
alphaGen lightingSpecular
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbgen identity
}
}

textures/base_support/support1rust
{
{
rgbGen identity
map $lightmap
}
{
map textures/base_support/support1rust.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
{
map textures/base_trim/tinfx.tga
tcgen environment
blendfunc add
rgbGen identity
}
{
map textures/base_support/support1rust.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_support/support1shiny
{
{
map textures/effects/tinfx.tga
tcGen environment
rgbGen identity
}
{
map textures/base_support/support1shiny.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_support/support2rust
{
qer_editorimage textures/base_support/support1rust.tga
{
rgbGen identity
map $lightmap
}
{
map textures/base_support/support1rust.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_support/x_support
{
surfaceparm metalsteps
surfaceparm trans
surfaceparm alphashadow
surfaceparm nomarks
cull none
nopicmip
{
map textures/base_support/x_support.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_support/x_support2
{
surfaceparm metalsteps
surfaceparm trans
surfaceparm alphashadow
surfaceparm playerclip
surfaceparm nonsolid
surfaceparm nomarks
cull none
nopicmip
{
map textures/base_support/x_support2.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_support/x_support3
{
surfaceparm metalsteps
surfaceparm trans
surfaceparm alphashadow
surfaceparm nomarks
cull none
nopicmip
{
map textures/base_support/x_support3.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_support/x_support4
{
surfaceparm metalsteps
surfaceparm trans
surfaceparm alphashadow
surfaceparm nomarks
cull none
nopicmip
{
map textures/base_support/x_support4.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_support/z_support
{
surfaceparm metalsteps
surfaceparm trans
surfaceparm alphashadow
surfaceparm nomarks
cull none
nopicmip
{
map textures/base_support/z_support.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_trim/border11_250
{
qer_editorimage textures/base_trim/border11light.tga
q3map_surfacelight 250
q3map_lightimage textures/base_trim/border11light.glow.tga
{
map $lightmap
rgbGen identity
}
{
map textures/base_trim/border11light.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/base_trim/border11light.glow.tga
blendfunc add
rgbgen wave sin .9 .1 0 10
}
}

textures/base_trim/border11light
{
q3map_surfacelight 500
Q3map_lightimage textures/base_trim/border11light.glow.tga
{
map $lightmap
rgbGen identity
}
{
map textures/base_trim/border11light.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/base_trim/border11light.glow.tga
blendfunc add
rgbgen wave sin .9 .1 0 10
}
}

textures/base_trim/border12b
{
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/base_trim/border12b.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/base_trim/border12bfx.tga
blendfunc add
}
}

textures/base_trim/border12b_pj
{
qer_editorimage textures/base_trim/border12b.tga
q3map_surfacelight 150
q3map_lightimage textures/base_trim/border12bfx.tga
{
map $lightmap
rgbGen identity
}
{
map textures/base_trim/border12b.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/base_trim/border12bfx.tga
blendfunc add
}
}

textures/base_trim/dark_tin
{
{
rgbGen identity
map $lightmap
}
{
map textures/base_trim/dark_tin.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
{
map textures/base_trim/tinfx.tga
tcgen environment
blendfunc add
rgbGen identity
}
{
map textures/base_trim/dark_tin.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_trim/dark_tin2
{
{
map textures/effects/tinfx.tga
tcGen environment
rgbGen vertex
}
{
map textures/base_trim/dark_tin2.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_trim/dark_tin2_trans
{
qer_editorimage textures/base_trim/dark_tin2
surfaceparm nonsolid
{
map textures/effects/tinfx.tga
tcGen environment
rgbGen vertex
}
{
map textures/base_trim/dark_tin2.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_trim/deeprust_trans
{
qer_editorimage textures/base_trim/deeprust.tga
surfaceparm nonsolid
{
map $lightmap
rgbGen identity
}
{
map textures/base_trim/deeprust.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_trim/drag_glass1
{
surfaceparm trans
surfaceparm nolightmap
{
map textures/base_trim/drag_glass1.tga
blendFunc GL_ONE_MINUS_DST_COLOR GL_ZERO
}
{
map textures/base_trim/drag_glass1.tga
alphaFunc LT128
blendfunc GL_DST_COLOR GL_ONE
}
}

textures/base_trim/electric_blue
{
qer_editorimage textures/base_trim/electricwall_blue.tga
q3map_lightimage textures/sfx/electric2.blend.tga
q3map_globaltexture
q3map_surfacelight 200
{
map $lightmap
rgbGen identity
}
{
map textures/base_trim/electricwall_blue.tga
tcMod scale 0.5 0.5
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/base_trim/electricwall_blue.tga
blendfunc add
}
{
map textures/sfx/electric2.blend.tga
rgbGen wave sin 0.6 1 0 2
tcMod scale 0.5 0.5
tcMod rotate 54
tcMod scroll 0.53 0.43
blendfunc add
}
}

textures/base_trim/electricwall
{
qer_editorimage textures/organics/wire02a_f.tga
light 1
q3map_surfacelight 400
{
map $lightmap
rgbGen identity
}
{
map textures/organics/wire02a_f.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/organics/wire02a_f.tga
blendfunc add
}
{
map textures/sfx/electric2.blend.tga
rgbGen wave sin 0.6 1 0 2
tcMod scroll 0.53 0.43
blendfunc add
}
}

textures/base_trim/panel_glo
{
{
map textures/sfx/firegorre2.tga
tcMod turb 0 .6 0 0.06
tcmod scale .53 .61
tcmod scroll 0 4
blendFunc GL_ONE GL_ZERO
rgbGen wave sin 1 1 0 .1
}
{
map textures/base_trim/panel_glo.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_trim/panel_shiny
{
{
map textures/effects/tinfx.tga
tcGen environment
rgbGen identity
}
{
map textures/base_trim/panel_shiny.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_trim/panelbrn010w
{
q3map_lightimage textures/base_trim/panelbrn010wfx.tga
{
map textures/base_trim/panelbrn010w.tga
}
{
map textures/sfx/hologirl2.tga
tcmod scale .4 .4
tcmod scroll 6 2
blendfunc add
rgbGen identity
}
{
map textures/base_trim/panelbrn010w.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
}
{
map $lightmap
rgbGen identity
blendFunc filter
}
}

textures/base_trim/pewter_nonsolid
{
qer_editorimage textures/base_trim/dirty_pewter.tga
surfaceparm nonsolid
{
map $lightmap
rgbGen identity
}
{
map textures/base_trim/dirty_pewter.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_trim/pewter_shiney
{
{
map textures/effects/tinfx.tga
tcGen environment
rgbGen identity
}
{
map textures/base_trim/pewter_shiney.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_trim/pewter_spec
{
{
rgbGen identity
map $lightmap
}
{
map textures/base_trim/pewter_spec.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_trim/pj_launcher
{
{
map textures/base_trim/pj_launcher2.tga
tcmod scroll 0 2
rgbGen identity
}
{
map textures/base_trim/pj_launcher.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc filter
rgbGen identity
}
}

textures/base_trim/proto_comp
{
{
map textures/base_trim/proto_comp2.tga
tcmod scroll 0 -.2
rgbGen wave sin .5 .5 0 3
rgbGen identity
}
{
clampmap textures/sfx/console03.tga
tcmod rotate -33
tcMod stretch sin .8 0 0 0
blendFunc gl_one gl_one
rgbGen wave sin .6 0 0 0
}
{
clampmap textures/sfx/console02.tga
tcmod rotate -333
tcMod stretch sin .8 0 0 0
blendFunc gl_one gl_one
rgbGen wave sin .3 0 0 0
}
{
map textures/effects/tinfx2c.tga
tcGen environment
blendFunc gl_one gl_one
rgbGen identity
}
{
map textures/base_trim/proto_comp.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
}
{
map $lightmap
blendFunc filter
rgbGen identity
}
}

textures/base_trim/proto_fence
{
surfaceparm trans
cull none
nopicmip
{
map textures/base_trim/proto_fence.tga
tcMod scale 3 3
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_trim/skull_monitor
{
{
map textures/base_trim/skull_monitor.tga
tcMod turb 0 .05 0 .2
rgbGen identity
}
{
map textures/sfx/text.tga
blendfunc add
tcmod scroll 1 0
rgbGen identity
}
{
map textures/effects/tinfx2.tga
blendfunc add
tcGen environment
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_trim/spiderbit
{
q3map_lightimage textures/base_trim/spiderbit_fx.tga
q3map_surfacelight 100
{
map $lightmap
rgbGen identity
}
{
map textures/base_trim/spiderbit.tga
blendfunc gl_dst_color gl_zero
rgbGen identity
}
{
map textures/base_trim/spiderbit_fx.tga
blendfunc add
rgbgen wave triangle .1 .5 0 7
}
}

textures/base_trim/spiderbite
{
{
map textures/sfx/proto_zzztblu2.tga
tcMod turb 0 .3 0 .2
tcmod scroll 6 .7
tcmod scale .4 1
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_trim/spiderbite.tga
blendfunc blend
tcMod stretch sin .8 0.4 0 .2
tcmod scroll .3 0
rgbGen identity
}
{
map textures/base_trim/spiderbite.tga
blendfunc blend
tcMod stretch sin .8 0.2 0 .1
tcmod scroll -.5 0
rgbGen identity
}
{
map textures/base_trim/spiderbite.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_trim/spidertrim3
{
{
map textures/effects/tinfx.tga
tcGen environment
rgbGen identity
}
{
map textures/base_trim/spidertrim3.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_trim/spidertrim4
{
{
map textures/effects/tinfx.tga
tcGen environment
rgbGen identity
}
{
map textures/base_trim/spidertrim4.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_trim/techborder
{
q3map_surfacelight 300
q3map_lightimage textures/base_trim/techborder_fx.tga
{
map $lightmap
rgbGen identity
}
{
map textures/base_trim/techborder.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/base_trim/techborder_fx.tga
tcmod scroll .1 0
blendfunc add
}
{
map textures/base_trim/techborder_fx.tga
tcmod scale .1 1
tcmod scroll .1 0
blendfunc add
}
}

textures/base_trim/tin
{
{
rgbGen identity
map $lightmap
}
{
map textures/base_trim/tin.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
{
map textures/base_trim/tinfx.tga
tcgen environment
blendfunc add
rgbGen identity
}
{
map textures/base_trim/tin.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_trim/wires01
{
cull disable
surfaceparm alphashadow
deformVertexes autoSprite2
surfaceparm trans
{
map textures/base_trim/wires01.tga
alphaFunc GT0
depthWrite
rgbGen vertex
}
{
map $lightmap
rgbGen identity
blendFunc filter
depthFunc equal
}
}

textures/base_trim/wires01_ass
{
cull disable
surfaceparm alphashadow
deformVertexes autoSprite2
{
map textures/base_trim/wires01_ass.tga
alphaFunc GT0
depthWrite
rgbGen vertex
}
{
map $lightmap
rgbGen identity
blendFunc filter
depthFunc equal
}
}

textures/base_trim/wires02
{
cull disable
surfaceparm alphashadow
surfaceparm trans
{
map textures/base_trim/wires02.tga
alphaFunc GT0
depthWrite
rgbGen vertex
}
{
map $lightmap
rgbGen identity
blendFunc filter
depthFunc equal
}
}

textures/base_trim/xborder12b
{
qer_editorimage textures/base_trim/border12b.tga
q3map_surfacelight 100
q3map_lightimage textures/base_trim/border12bfx.tga
{
map $lightmap
rgbGen identity
}
{
map textures/base_trim/border12b.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/base_trim/border12bfx.tga
blendfunc add
}
}

textures/base_trim/yellow_rustc
{
{
map textures/base_wall/chrome_env.tga
tcgen environment
tcmod scale .25 .25
rgbGen identity
}
{
map textures/base_trim/yellow_rustc.tga
blendFunc gl_one_minus_src_alpha gl_src_alpha
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
}

textures/base_door/shinymetaldoor
{
{
map textures/base_wall/chrome_env.tga
tcGen environment
tcmod scale .25 .25
rgbGen identity
}
{
map textures/base_door/shinymetaldoor.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map textures/base_door/quake3sign.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_door/shinymetaldoor_outside
{
{
map textures/base_wall/chrome_env.tga
tcGen environment
tcmod scale .25 .25
rgbGen identity
}
{
map textures/base_door/shinymetaldoor_outside.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map textures/base_door/quake3sign_outside.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_door/shinymetaldoor_outside3a
{
{
map textures/base_wall/chrome_env.tga
tcGen environment
tcmod scale .25 .25
rgbGen identity
}
{
map textures/base_door/shinymetaldoor_outside3a.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_door/shinymetaldoor_outside3a2
{
{
map textures/base_wall/chrome_env.tga
tcGen environment
tcmod scale .25 .25
rgbGen identity
}
{
map textures/base_door/shinymetaldoor_outside3a2.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc filter
}
{
map textures/base_door/shinymetaldoor_outside3glow.tga
blendFunc gl_one gl_one
rgbGen wave sin .9 .1 0 5
}
}

textures/base_door/shinymetaldoor_outside3b
{
{
map textures/base_wall/chrome_env.tga
tcGen environment
tcmod scale .25 .25
rgbGen identity
}
{
map textures/base_door/shinymetaldoor_outside3b.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_wall/atech1_alpha
{
{
map textures/sfx/hologirl.tga
tcmod scale 2 .4
tcmod scroll 6 .6
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_wall/atech1_alpha.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc filter
}
}

textures/base_wall/atechengine_ax
{
q3map_lightimage textures/base_wall/atechengine_ax2.tga
q3map_surfacelight 300
{
map textures/sfx/proto_zzztpink.tga
tcmod rotate 60
tcMod turb 0 .5 0 9.6
tcmod scale 2 2
tcmod scroll 9 5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_wall/atechengine_ax.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_wall/basewall01_ow
{
q3map_lightimage textures/base_wall/basewall01_owfx.tga
{
map $lightmap
rgbGen identity
}
{
map textures/base_wall/basewall01_ow.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_wall/basewall01_owfx.tga
blendfunc add
rgbGen wave sin .5 0.5 0 .5
}
}

textures/base_wall/basewall01bit
{
q3map_lightimage textures/base_wall/basewall01bitfx.tga
q3map_surfacelight 300
{
map textures/base_wall/basewall01bit.tga
rgbGen identity
}
{
map textures/base_wall/basewall01bitfx.tga
blendfunc add
tcmod scroll 3.3 1
rgbGen wave sin .5 0.5 0 5
}
{
map textures/effects/envmap2.tga
tcGen environment
tcmod scale 4 4
blendfunc add
rgbGen identity
}
{
map textures/base_wall/basewall01bit.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_wall/bloodstain
{
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/bloodstain.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_wall/bluecover
{
{
map $lightmap
tcgen environment
tcmod scale .25 .25
rgbgen identity
}
{
map textures/base_wall/bluecover.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbgen identity
}
}

textures/base_wall/bluemetal1b_chrome
{
qer_editorimage textures/base_wall/bluemetal1b.tga
{
map textures/base_wall/chrome_env2.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetal1b_shiny.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
}

textures/base_wall/bluemetal1b_shiny
{
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/bluemetal1b_shiny.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_wall/bluemetal1c
{
{
map textures/base_wall/chrome_env2.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetal1c.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
}

textures/base_wall/bluemetal1light
{
q3map_surfacelight 1000
q3map_lightimage textures/base_wall/bluemetal1light_bl.tga
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_wall/bluemetal1light.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_wall/bluemetal1light_bl.tga
rgbGen wave sin 0.5 0.1 1 0.5
blendfunc add
}
}

textures/base_wall/bluemetal2_noisy
{
qer_editorimage textures/base_wall/bluemetal2_shiny
surfaceparm metalsteps
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/bluemetal2_shiny.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_wall/bluemetal2_shiny
{
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/bluemetal2_shiny.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_wall/bluemetal2_shiny_trans
{
qer_editorimage textures/base_wall/bluemetal2_shiny.tga
surfaceparm nonsolid
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/bluemetal2_shiny.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_wall/bluemetalsupport2
{
{
map textures/base_wall/chrome_env2.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
}

textures/base_wall/bluemetalsupport2b
{
q3map_surfacelight 100
q3map_lightimage textures/base_wall/bluemetalsupport2bglow.tga
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2b.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
{
map textures/base_wall/bluemetalsupport2bglow.tga
blendfunc add
rgbGen wave sin 0.5 0.5 0 .2
}
}

textures/base_wall/bluemetalsupport2c
{
{
map textures/base_wall/chrome_env2.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2c.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
}

textures/base_wall/bluemetalsupport2c_1
{
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2c_1.tga
blendFunc blend
rgbGen identity
}
{
map $lightmap
blendfunc filter
rgbGen identity
}
}

textures/base_wall/bluemetalsupport2c_1vent
{
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2c_1vent.tga
blendFunc blend
rgbGen identity
}
{
map $lightmap
blendfunc filter
rgbGen identity
}
}

textures/base_wall/bluemetalsupport2clight
{
surfaceparm nomarks
q3map_surfacelight 500
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2clight.tga
blendFunc blend
rgbGen identity
}
{
map $lightmap
blendfunc filter
rgbGen identity
}
{
map textures/base_wall/bluemetalsupport2clight.glow.tga
blendFunc gl_one gl_one
rgbgen wave sawtooth .6 .1 0 4
}
}

textures/base_wall/bluemetalsupport2d_1
{
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2d_1.tga
blendFunc blend
rgbGen identity
}
{
map $lightmap
blendfunc filter
rgbGen identity
}
}

textures/base_wall/bluemetalsupport2e
{
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2e.tga
blendFunc blend
rgbGen identity
}
{
map $lightmap
blendfunc filter
rgbGen identity
}
}

textures/base_wall/bluemetalsupport2e2
{
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2e2.tga
blendFunc blend
rgbGen identity
}
{
map $lightmap
blendfunc filter
rgbGen identity
}
}

textures/base_wall/bluemetalsupport2eye
{
surfaceparm nomarks
q3map_surfacelight 300
q3map_lightimage textures/base_wall/bluemetalsupport2eyel.tga
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2eye.tga
blendFunc blend
rgbGen identity
}
{
map $lightmap
blendfunc filter
rgbGen identity
}
{
map textures/base_wall/bluemetalsupport2eyel.tga
blendfunc add
rgbgen wave triangle .5 .5 0 .5
}
}

textures/base_wall/bluemetalsupport2f
{
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2f.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
}

textures/base_wall/bluemetalsupport2fline
{
q3map_surfacelight 100
q3map_lightimage textures/base_wall/bluemetalsupport2fline_glow.tga
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2fline.tga
blendFunc blend
rgbGen identity
}
{
map $lightmap
blendfunc filter
rgbGen identity
}
{
map textures/base_wall/bluemetalsupport2fline_glow.tga
blendFunc add
rgbGen wave sin .5 .5 0 1
}
}

textures/base_wall/bluemetalsupport2ftv
{
q3map_surfacelight 100
q3map_lightimage textures/base_wall/bluemetalsupport2ftv_glow.tga
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport2ftv.tga
blendFunc blend
rgbGen identity
}
{
map $lightmap
blendfunc filter
rgbGen identity
}
{
map textures/base_wall/bluemetalsupport2ftv_glow.tga
blendFunc add
rgbGen wave sawtooth .4 .05 0 10
}
}

textures/base_wall/bluemetalsupport_shiny
{
{
map textures/base_wall/chrome_env2.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/bluemetalsupport_shiny.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
}

textures/base_wall/blumtlspt2b
{
q3map_surfacelight 100
q3map_lightimage textures/base_wall/blumtlspt2bglow.tga
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/blumtlspt2b.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
{
map textures/base_wall/bluemetalsupport2bglow.tga
blendfunc add
rgbGen wave sin 0.5 0.5 0 .2
}
}

textures/base_wall/blupaintedmetal
{
{
map $lightmap
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/blupaintedmetal.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_wall/blupaintedmetalcomp
{
{
map $lightmap
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/blupaintedmetalcomp.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_wall/chrome_metal
{
{
map textures/base_wall/chrome_env.tga
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/chrome_metal.tga
blendfunc add
detail
tcMod scale 0.0693 0.0712
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_wall/comp3
{
q3map_lightimage textures/base_wall/comp3env.tga
q3map_surfacelight 1000
{
map textures/base_wall/comp3text.tga
rgbGen identity
tcmod scroll 3 1
}
{
map textures/base_wall/comp3env.tga
tcGen environment
blendfunc add
rgbGen wave sin .98 .02 0 5
}
{
map $lightmap
tcGen environment
blendFunc GL_DST_COLOR GL_ONE
}
{
map textures/base_wall/comp3.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_wall/comp3b
{
q3map_lightimage textures/base_wall/comp3textb.tga
q3map_surfacelight 1000
{
map textures/base_wall/comp3textb.tga
rgbGen identity
tcmod scroll 3 3
}
{
map textures/base_wall/comp3env.tga
tcGen environment
blendfunc add
rgbGen wave sin .98 .02 0 5
}
{
map $lightmap
tcGen environment
blendFunc GL_DST_COLOR GL_ONE
}
{
map textures/base_wall/comp3b.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_wall/comp3b_dark
{
q3map_lightimage textures/base_wall/comp3textb.tga
q3map_surfacelight 1
{
map textures/base_wall/comp3textb.tga
rgbGen identity
tcmod scroll 3 3
}
{
map textures/base_wall/comp3env.tga
tcGen environment
blendfunc add
rgbGen wave sin .98 .02 0 5
}
{
map $lightmap
tcGen environment
blendFunc GL_DST_COLOR GL_ONE
}
{
map textures/base_wall/comp3b.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_wall/comp3c
{
{
map textures/base_wall/comp3env.tga
rgbGen identity
tcGen environment
}
{
map $lightmap
tcGen environment
blendfunc add
}
{
map textures/base_wall/comp3c.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_wall/concrete4
{
{
map textures/liquids/protolava2.tga
tcmod scale .2 .2
tcmod scroll .04 .03
tcMod turb 0 .1 0 .01
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_wall/concrete4.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc filter
}
}

textures/base_wall/concrete_ow
{
{
map textures/sfx/proto_zzztblu2.tga
tcMod turb 0 .5 0 9.6
tcmod scale 2 2
tcmod scroll 9 5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_wall/concrete_ow.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_wall/dooreye
{
surfaceparm nomarks
q3map_surfacelight 300
q3map_lightimage textures/base_wall/dooreyelight.tga
{
map $lightmap
rgbGen identity
}
{
map textures/base_wall/dooreye.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_wall/dooreyelight.tga
blendfunc add
rgbgen wave triangle .5 .5 0 .5
}
}

textures/base_wall/dooreye2
{
surfaceparm nomarks
q3map_surfacelight 300
q3map_lightimage textures/base_wall/dooreyelight.tga
{
map $lightmap
rgbGen identity
}
{
map textures/base_wall/dooreye2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_wall/dooreyelight.tga
blendfunc add
rgbgen wave triangle .5 .5 0 .5
}
}

textures/base_wall/dooreye3
{
surfaceparm nomarks
q3map_surfacelight 300
q3map_lightimage textures/base_wall/dooreyelight.tga
{
map $lightmap
rgbGen identity
}
{
map textures/base_wall/dooreye3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/base_wall/dooreyelight.tga
blendfunc add
rgbgen wave triangle .5 .5 0 .5
}
}

textures/base_wall/future9light
{
q3map_lightimage textures/base_wall/future9light.color.tga
q3map_surfacelight 400
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_wall/future9light.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/base_wall/future9light.blend.tga
rgbGen wave sin 0.5 0.1 1 0.5
blendfunc add
}
}

textures/base_wall/girders1i_yellofin
{
surfaceparm metalsteps
surfaceparm trans
surfaceparm alphashadow
surfaceparm playerclip
surfaceparm nonsolid
surfaceparm nomarks
cull none
nopicmip
{
map textures/base_wall/girders1i_yellodark_fin.tga
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_wall/glass01
{
surfaceparm trans
cull none
qer_trans 0.5
{
map textures/effects/tinfx.tga
tcgen environment
blendfunc add
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc filter
}
}

textures/base_wall/glass_frame
{
cull none
surfaceparm alphashadow
{
map textures/effects/tinfx2.tga
blendfunc add
tcgen environment
rgbGen identity
}
{
map textures/base_wall/glass_frame.tga
alphaFunc GT0
depthWrite
}
{
map $lightmap
rgbGen identity
blendFunc filter
}
}

textures/base_wall/green_con04
{
{
map textures/sfx/specular.tga
tcGen environment
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_wall/green_con04.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc filter
}
}

textures/base_wall/green_contrim_noisey
{
qer_editorimage textures/base_wall/green_contrim.tga
surfaceparm metalsteps
{
map $lightmap
rgbGen identity
}
{
map textures/base_wall/green_contrim.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_wall/grill
{
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/grill.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
}

textures/base_wall/grill2
{
{
rgbGen identity
map $lightmap
}
{
map textures/base_wall/grill2.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
{
map textures/effects/tinfx.tga
tcgen environment
blendfunc add
rgbGen identity
}
{
map textures/base_wall/grill2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_wall/kcgrate1
{
cull disable
{
map textures/base_wall/kcgrate1.tga
tcMod scale 2 2
blendFunc GL_ONE GL_ZERO
alphaFunc GT0
depthWrite
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/base_wall/main_q3abanner
{
q3map_lightimage textures/base_wall/main_q3abanner.tga
q3map_surfacelight 100
{
map textures/base_wall/main_q3abanner.tga
rgbGen wave square 0 1 0 .5
}
{
map textures/base_wall/comp3text.tga
blendFunc gl_one gl_one
rgbGen identity
tcmod scroll 3 3
}
{
map textures/base_wall/comp3textb.tga
blendFunc gl_one gl_one
rgbGen identity
tcmod scroll 3 3
}
{
map $lightmap
rgbGen identity
blendfunc gl_dst_color gl_zero
}
{
map $lightmap
tcgen environment
tcmod scale .5 .5
rgbGen wave sin .25 0 0 0
blendFunc gl_one gl_one
}
}

textures/base_wall/medal_impressive
{
qer_editorimage textures/base_wall/medal_impressive.tga
q3map_surfacelight 100
{
animMap .25 textures/base_wall/medal_impressive.tga textures/base_wall/medal_gauntlet.tga textures/base_wall/medal_excellent.tga textures/base_wall/medal_accuracy.tga textures/base_wall/medal_victory.tga textures/base_wall/medal_frags.tga
rgbGen wave sawtooth 0 1 0 .25
}
{
map textures/base_wall/comp3textd.tga
blendFunc gl_one gl_one
tcmod scroll 5 .25
rgbGen wave inversesawtooth 0 1 0 .25
}
{
map textures/base_wall/chrome_env.tga
tcgen environment
tcmod scale .5 .5
blendFunc gl_one gl_one
rgbgen wave triangle .5 .05 0 10
}
{
map textures/base_wall/comp3frame.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbgen identity
}
{
map $lightmap
rgbGen identity
blendfunc gl_dst_color gl_zero
}
}

textures/base_wall/metalfloor_wall_14_specular
{
qer_editorimage textures/base_wall/metalfloor_wall_14_specular.tga
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/metalfloor_wall_14_specular.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_wall/metalfloor_wall_15ow
{
{
map textures/base_wall/metalfloor_wall_15ow.tga
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/sfx/hologirl.tga
tcmod scale 2 .4
tcmod scroll 6 .6
blendfunc add
rgbGen identity
}
{
map textures/base_wall/metalfloor_wall_15ow.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc filter
}
}

textures/base_wall/metaltechgeomtrn
{
{
map textures/sfx/fire_ctfblue.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 1.6
tcmod scale 2 2
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/base_wall/metaltechgeomtrn.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
tcmod rotate 30
tcMod stretch sin .8 0.2 0 .2
rgbGen identity
}
{
map textures/base_wall/metaltechgeomtrn2.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
tcmod rotate 20
tcMod stretch sin .8 0.2 0 .1
rgbGen identity
}
{
map textures/base_wall/metaltechgeomtrn.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/base_wall/patch10_beat4_drip
{
qer_editorimage textures/base_wall/patch10_beatup4_stain.tga
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/waterdrip.tga
blendFunc GL_ONE gl_src_alpha
tcmod scroll 0 -.001
}
{
map textures/base_wall/patch10_beatup4_stain.tga
blendFunc GL_ONE GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendfunc gl_dst_color gl_zero
}
}

textures/base_wall/patch10_beatup4_shiny2
{
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/patch10_beatup4_shiny2.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_wall/patch10shiny
{
qer_editorimage textures/base_wall/patch10_beatup4_alpha.tga
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/patch10_beatup4_alpha.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_wall/patch10shiny_trans
{
qer_editorimage textures/base_wall/patch10_beatup4_alpha.tga
surfaceparm nonsolid
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/patch10_beatup4_alpha.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_wall/patch11_shiny
{
qer_editorimage textures/base_wall/patch11_shiny.tga
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/patch11_shiny.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_wall/pjrock18
{
qer_editorimage textures/stone/pjrock18.tga
{
map $lightmap
tcgen environment
tcmod scale .25 .25
rgbgen identity
}
{
map textures/stone/pjrock18.tga
blendFunc GL_ONE GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_wall/protobanner
{
cull disable
surfaceparm alphashadow
surfaceparm trans
surfaceparm nomarks
tessSize 64
deformVertexes wave 30 sin 0 3 0 .2
deformVertexes wave 100 sin 0 3 0 .7
{
map textures/base_wall/protobanner.tga
alphaFunc GT0
depthWrite
rgbGen vertex
}
{
map $lightmap
rgbGen identity
blendFunc filter
depthFunc equal
}
}

textures/base_wall/protobanner_ow
{
cull disable
surfaceparm alphashadow
surfaceparm trans
surfaceparm nomarks
deformVertexes wave 100 sin 0 1 0 .1
deformVertexes wave 100 sin 0 1 0 .2
{
map textures/base_wall/protobanner_ow.tga
alphaFunc GT0
depthWrite
rgbGen vertex
}
{
map $lightmap
rgbGen identity
blendFunc filter
depthFunc equal
}
}

textures/base_wall/protobanner_still
{
qer_editorimage textures/base_wall/protobanner.tga
cull disable
surfaceparm alphashadow
surfaceparm trans
surfaceparm nomarks
tessSize 64
{
map textures/base_wall/protobanner.tga
alphaFunc GT0
depthWrite
rgbGen vertex
}
{
map $lightmap
rgbGen identity
blendFunc filter
depthFunc equal
}
}

textures/base_wall/q3tourneyscreen
{
qer_editorimage textures/base_wall/q3tourney1.tga
q3map_surfacelight 100
{
animMap .25 textures/base_wall/q3tourney1.tga textures/base_wall/q3tourney2.tga textures/base_wall/q3tourney3.tga textures/base_wall/q3tourney4.tga textures/base_wall/q3tourney5.tga
rgbGen wave sawtooth 0 1 0 .25
}
{
map textures/base_wall/comp3textd.tga
blendFunc gl_one gl_one
rgbGen wave inversesawtooth 0 1 0 .25
tcmod scroll 5 .25
}
{
map textures/base_wall/chrome_env.tga
tcgen environment
tcmod scale .5 .5
blendFunc gl_one gl_one
rgbgen wave triangle .5 .05 0 10
}
{
map textures/base_wall/comp3frame.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbgen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbgen identity
}
}

textures/base_wall/shinybluemetal1
{
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/shinybluemetal1.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_wall/shinybluemetal1b
{
{
map textures/base_wall/chrome_env.tga
tcgen environment
tcmod scale .25 .25
rgbgen identity
}
{
map textures/base_wall/shinybluemetal1b.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbgen identity
}
}

textures/base_wall/shinygrate1_4
{
{
map $lightmap
tcgen environment
tcmod scale .25 .25
rgbgen identity
}
{
map textures/base_wall/shinygrate1_4.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/base_wall/shinygrate1_4_glow
{
q3map_lightimage textures/base_wall/shinygrate1_4_glow_light2.tga
q3map_surfacelight 100
q3map_lightsubdivide 32
{
map textures/sfx/electricslime.tga
rgbGen wave sin .5 .5 0 1
tcmod scale .25 .25
tcMod scroll -10 -1
}
{
map textures/base_wall/shinygrate1_4_glow.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/base_wall/shinygrate1_4_glow_light2.tga
blendfunc add
rgbGen wave triangle .2 .01 0 10
}
}

textures/base_wall/shinymetal2
{
{
map $lightmap
tcGen environment
tcmod scale .25 .25
}
{
map $lightmap
rgbgen identity
blendFunc GL_ONE GL_SRC_COLOR
}
{
map textures/base_wall/shinymetal2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/base_wall/steed1gd
{
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/steed1gd.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
}

textures/base_wall/steed1gf
{
{
map $lightmap
rgbgen identity
}
{
map textures/base_wall/steed1gf.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/base_wall/steedmetal2
{
{
map textures/base_wall/chrome_env.tga
rgbGen identity
tcGen environment
tcmod scale .25 .25
}
{
map textures/base_wall/steedmetal2.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbGen identity
}
}

textures/base_wall/symbol_bluelt1
{
q3map_lightimage textures/base_wall/symbol_bluelt1_mask.tga
q3map_surfacelight 100
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/base_wall/symbol_bluelt1.tga
blendfunc filter
rgbgen identity
}
{
map textures/base_wall/symbol_bluelt1_mask.tga
blendFunc gl_one gl_one
rgbgen wave sawtooth .2 .05 0 7
}
}

textures/base_wall/train1
{
{
map textures/base_wall/chrome_env.tga
tcGen environment
tcmod scale .25 .1
rgbGen identity
}
{
map textures/base_wall/train1.tga
blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
rgbGen identity
}
{
map $lightmap
rgbgen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}
