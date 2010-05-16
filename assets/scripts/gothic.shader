// Q3MIN - shaders for texture group 'gothic'

textures/gothic_block/blocks11ct
{
surfaceparm trans
{
map textures/gothic_block/blocks11c.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/gothic_block/blocks15_ow
{
{
map textures/liquids/proto_grueldark.tga
tcmod scroll 0 -.05
tcmod scale 4 4
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/liquids/proto_grueldark.tga
tcmod scroll 0.01 -.02
tcmod scale 4 4
blendfunc add
rgbGen identity
}
{
map textures/gothic_block/blocks15_ow.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_block/blocks15_sandy
{
qer_editorimage textures/gothic_block/blocks15.tga
q3map_globaltexture
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_block/sand2.tga
blendfunc GL_DST_COLOR GL_SRC_COLOR
rgbGen identity
detail
tcMod scale 2.90 2.234
}
{
map textures/gothic_block/blocks15.tga
tcMod scale 0.25 0.25
blendfunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/gothic_block/blocks15cgeomtrn
{
{
map textures/sfx/firegorre.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 1.6
tcmod scale 2 2
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/gothic_block/blocks18cgeomtrn2.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
tcmod rotate 30
tcMod stretch sin .8 0.2 0 .2
rgbGen identity
}
{
map textures/gothic_block/blocks18cgeomtrn2.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
tcmod rotate 20
tcMod stretch sin .8 0.2 0 .1
rgbGen identity
}
{
map textures/gothic_block/blocks15cgeomtrn.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_block/blocks17_ow
{
{
map textures/sfx/firegorre.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 5.6
tcmod scale 1.5 1.5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/gothic_block/blocks17_ow.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc filter
rgbGen identity
}
}

textures/gothic_block/blocks17_sandy
{
qer_editorimage textures/gothic_block/blocks17.tga
q3map_globaltexture
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_block/sand2.tga
blendfunc GL_DST_COLOR GL_SRC_COLOR
rgbGen identity
detail
tcMod scale 2.90 2.234
}
{
map textures/gothic_block/blocks17.tga
tcMod scale 0.25 0.25
blendfunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/gothic_block/blocks17bloody
{
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
map textures/gothic_block/blocks17bloody.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc filter
rgbGen identity
}
}

textures/gothic_block/blocks17g_ow
{
{
map textures/sfx/firegorre.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 5.6
tcmod scale 1.5 1.5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/gothic_block/blocks17g_ow.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc filter
rgbGen identity
}
}

textures/gothic_block/blocks17gwater
{
{ map textures/gothic_block/blocks17gwater.tga
blendfunc GL_dst_color GL_one
alphafunc GT0
depthwrite
}
{ map $lightmap
blendfunc gl_dst_color gl_one
tcgen environment
depthfunc equal
}
}

textures/gothic_block/blocks18b_ow
{
{
map textures/sfx/firegorre.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 5.6
tcmod scale 1.5 1.5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/gothic_block/blocks18b_ow.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc filter
rgbGen identity
}
}

textures/gothic_block/blocks18cgeomtrn
{
{
map textures/sfx/firegorre.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 1.6
tcmod scale 2 2
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/gothic_block/blocks18cgeomtrn2.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
tcmod rotate 30
tcMod stretch sin .8 0.2 0 .2
rgbGen identity
}
{
map textures/gothic_block/blocks18cgeomtrn2.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
tcmod rotate 20
tcMod stretch sin .8 0.2 0 .1
rgbGen identity
}
{
map textures/gothic_block/blocks18cgeomtrn.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_block/blocks18cgeomtrn2
{
cull disable
surfaceparm alphashadow
{
clampmap textures/gothic_block/blocks18cgeomtrn2.tga
alphaFunc GT0
tcmod rotate 40
tcMod stretch sin .8 0.2 0 .3
rgbGen identity
}
{
clampmap textures/gothic_block/blocks18cgeomtrn2.tga
alphaFunc GT0
tcmod rotate 30
tcMod stretch sin .8 0.2 0 .2
rgbGen identity
}
{
clampmap textures/gothic_block/blocks18cgeomtrn2.tga
alphaFunc GT0
tcmod rotate 20
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

textures/gothic_block/blocks18cgeomtrnx
{
{
map textures/sfx/fireswirl2blue.tga
tcMod stretch sin .8 0.3 0 9.7
tcmod rotate 333
rgbGen identity
}
{
map textures/gothic_block/blocks18cgeomtrn2.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
tcmod rotate 30
tcMod stretch sin .8 0.2 0 .2
rgbGen identity
}
{
map textures/gothic_block/blocks18cgeomtrn2.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
tcmod rotate 20
tcMod stretch sin .8 0.2 0 .1
rgbGen identity
}
{
map textures/gothic_block/blocks18cgeomtrnx.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_block/blocks18d_trans
{
qer_editorimage textures/gothic_block/blocks18d.tga
surfaceparm nonsolid
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_block/blocks18d.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/gothic_block/demon_block15fx
{
{
map textures/sfx/firegorre.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 1.6
tcmod scale 4 4
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/gothic_block/demon_block15fx.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_block/electrohell
{
qer_editorimage textures/gothic_block/gkc14c.tga
q3map_surfacelight 400
{
rgbGen identity
map $lightmap
}
{
map textures/gothic_block/gkc14c.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/gothic_block/gkc14c.tga
blendfunc add
}
{
map textures/sfx/electro2.tga
rgbGen wave sin .7 .7 0 2
tcMod rotate 1
tcMod turb 0 0.2 0 0.4
tcMod stretch sin 1 .5 0 .1
tcMod scroll .2 .2
blendfunc add
}
}

textures/gothic_block/evil_e3bwindow
{
qer_editorimage textures/gothic_block/windowevil2c_killblock.tga
q3map_lightimage textures/gothic_block/evil2ckillblockglow.tga
q3map_surfacelight 200
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_block/windowevil2c_killblock.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_block/evil2ckillblockglow.tga
blendfunc add
}
}

textures/gothic_block/evil_e3window
{
qer_editorimage textures/gothic_block/windowevil2c_block18c.tga
q3map_lightimage textures/gothic_block/evil2cglow.tga
q3map_surfacelight 1000
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_block/windowevil2c_block18c.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_block/evil2cglow.tga
blendfunc add
}
}

textures/gothic_block/evil_e3window_dark
{
qer_editorimage textures/gothic_block/windowevil2c_block18c.tga
q3map_lightimage textures/gothic_block/evil2cglow.tga
q3map_surfacelight 100
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_block/windowevil2c_block18c.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_block/evil2cglow.tga
blendfunc add
}
}

textures/gothic_block/flicker_blocks10
{
qer_editorimage textures/gothic_block/blocks10.tga
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_block/blocks10.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen wave noise 0.75 0.25 0 10
}
}

textures/gothic_block/gkc17d
{
{
rgbGen identity
map $lightmap
}
{
map textures/gothic_block/gkc17d.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_block/gkcspinemove
{
qer_editorimage textures/gothic_block/gkc17d.tga
tessSize 128
deformVertexes bulge 3 10 1
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_block/gkc17d.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_block/killblockgeomtrn
{
{
map textures/sfx/firegorre.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 1.6
tcmod scale 2 2
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/gothic_block/blocks18cgeomtrn2.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
tcmod rotate 30
tcMod stretch sin .8 0.2 0 .2
rgbGen identity
}
{
map textures/gothic_block/blocks18cgeomtrn2.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
tcmod rotate 20
tcMod stretch sin .8 0.2 0 .1
rgbGen identity
}
{
map textures/gothic_block/killblockgeomtrn.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_block/largerblock3blood
{
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
map textures/gothic_block/largerblock3blood.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc filter
rgbGen identity
}
}

textures/gothic_block/mkc_evil_e3window
{
qer_editorimage textures/gothic_block/windowevil2c_block18c.tga
q3map_lightimage textures/gothic_block/evil2cglow.tga
q3map_surfacelight 400
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_block/windowevil2c_block18c.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_block/evil2cglow.tga
blendfunc add
}
}

textures/gothic_block/wetwall
{
{
map textures/gothic_block/wetwall.tga
rgbGen identity
}
{
map textures/gothic_block/wetwallfx.tga
tcmod scroll 0 -.1
tcmod scale 2 .6
blendfunc add
rgbGen identity
}
{
map textures/gothic_block/wetwall.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_block/xblocks17i_shiney
{
qer_editorimage textures/gothic_block/xblocks17i_alpha.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_block/xblocks17i_alpha.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_door/skullarch_b
{
{
map textures/sfx/firegorre.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 5.6
tcmod scale 1.5 1.5
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/gothic_door/skullarch_b.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc filter
rgbGen identity
}
}

textures/gothic_light/flicker_light15k
{
qer_editorimage textures/gothic_light/gothic_light3.tga
q3map_lightimage textures/gothic_light/gothic_light2_blend.tga
q3map_surfacelight 15000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen wave noise 0.75 0.25 0 10
}
{
map textures/gothic_light/gothic_light3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
blendfunc add
rgbGen wave noise 0.75 0.25 0 10
}
}

textures/gothic_floor/center2trn
{
{
map textures/sfx/fireswirl2.tga
tcmod rotate 333
tcMod stretch sin .8 0.2 0 9.7
rgbGen identity
}
{
map textures/gothic_floor/center2trn.tga
blendfunc blend
tcmod rotate 30
tcMod stretch sin .8 0.2 0 .2
rgbGen identity
}
{
map textures/gothic_floor/center2trn.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_floor/fireblocks17floor3
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
map textures/gothic_floor/fireblocks17floor3.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
}
{
map $lightmap
blendfunc filter
}
}

textures/gothic_floor/glowfloor1
{
q3map_lightimage textures/gothicfloor/glowfloor1.tga
q3map_surfacelight 600
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_block/blocks17g.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_floor/glowred2.blend.tga
blendfunc add
rgbGen wave sin 0.5 0.1 1 0.5
}
}

textures/gothic_floor/largerblock3b_ow
{
{
map textures/sfx/firegorre.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 1.6
tcmod scale 4 4
blendFunc GL_ONE GL_ZERO
rgbGen identity
}
{
map textures/gothic_floor/largerblock3b_ow.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_floor/metalbridge06brokeb
{
{
map textures/sfx/kenelectric.tga
tcmod scale 2 2
tcMod turb 0 .2 0 .3
tcmod scroll 3 5
rgbGen identity
}
{
map textures/gothic_floor/metalbridge06brokeb.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_floor/pent_metalbridge02
{
q3map_lightimage textures/gothic_floor/pent_glow.tga
q3map_surfacelight 500
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_floor/pent_metalbridge02.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_floor/pent_glow.tga
blendfunc add
rgbGen wave sin .5 .5 0 0.5
}
}

textures/gothic_floor/pent_metalbridge06
{
q3map_lightimage textures/gothic_floor/pent_glow.tga
q3map_surfacelight 500
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_floor/pent_metalbridge06.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_floor/pent_glow.tga
blendfunc add
rgbGen wave sin .5 .5 0 0.5
}
}

textures/gothic_floor/pent_metalbridge06b
{
q3map_lightimage textures/gothic_floor/pent_glow.tga
q3map_surfacelight 500
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_floor/pent_metalbridge06b.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_floor/pent_glow.tga
blendfunc add
rgbGen wave sin .5 .5 0 0.5
}
}

textures/gothic_floor/q1metal7_97redow
{
{
map textures/gothic_floor/q1metal7_97redow.tga
rgbGen identity
}
{
map textures/sfx/fire_ctfblue.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 1.6
tcmod scale 4 4
blendfunc add
rgbGen identity
}
{
map textures/gothic_floor/q1metal7_97redow.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_floor/q1metal7_98blueow
{
{
map textures/gothic_floor/q1metal7_98blueow.tga
rgbGen identity
}
{
map textures/sfx/fire_ctfred.tga
tcmod scroll 0 1
tcMod turb 0 .25 0 1.6
tcmod scale 4 4
blendfunc add
rgbGen identity
}
{
map textures/gothic_floor/q1metal7_98blueow.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_floor/q1metal7_99spot
{
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
map textures/gothic_floor/q1metal7_99spot.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc filter
rgbGen identity
}
}

textures/gothic_floor/xlargeblockfloor5_pent
{
{
map textures/gothic_floor/xlargeblockfloor5_pent.tga
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendfunc gl_dst_color gl_zero
}
{
map textures/sfx/pentfloor_256_glow.tga
blendfunc add
rgbGen wave sin .5 .5 0 .5
depthfunc equal
}
}

textures/gothic_floor/xlargeblockfloor5_pent_offset
{
{
map textures/gothic_floor/xlargeblockfloor5_pent_offset.tga
rgbGen identity
}
{
map $lightmap
rgbGen identity
blendfunc gl_dst_color gl_zero
}
{
map textures/sfx/pentfloor_256_glow.tga
blendfunc add
rgbGen wave sin .5 .5 0 .5
depthfunc equal
}
}

textures/gothic_floor/xq1metalbig_ow
{
{
map textures/gothic_floor/xq1metalbig_ow.tga
rgbGen identity
}
{
map textures/sfx/specular.tga
tcGen environment
tcmod scale 3 3
tcMod turb 0 .25 0 .05
blendfunc add
rgbGen identity
}
{
map textures/gothic_floor/xq1metalbig_ow.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_floor/xstepborder3_shiney
{
qer_editorimage textures/gothic_floor/xstepborder3_alpha.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_floor/xstepborder3_alpha.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_light/border7_ceil22a
{
qer_editorimage textures/gothic_light/border7_ceil22a.tga
q3map_lightimage textures/gothic_light/border_ceil22a.blend.tga
q3map_surfacelight 200
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/border7_ceil22a.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/border_ceil22a.blend.tga
blendfunc add
}
}

textures/gothic_light/border7_ceil30
{
qer_editorimage textures/gothic_light/border7_ceil30.tga
q3map_lightimage textures/gothic_light/border_ceil30.blend.tga
q3map_surfacelight 200
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/border7_ceil30.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/border_ceil30.blend.tga
blendfunc add
}
}

textures/gothic_light/border7_ceil39_6k
{
qer_editorimage textures/gothic_light/border7_ceil39.tga
q3map_surfacelight 3700
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/border7_ceil39.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/border_ceil39.blend.tga
blendfunc add
}
}

textures/gothic_light/border7_ceil39b_10k
{
qer_editorimage textures/gothic_light/border7_ceil39b.tga
q3map_surfacelight 3000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/border7_ceil39b.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/border7_ceil39b.blend.tga
blendfunc add
}
}

textures/gothic_light/crosslt1
{
light 1
q3map_surfacelight 3250
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/crosslt1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/crosslt1.blend.tga
rgbGen wave sin 0.5 0.5 0 .2
blendfunc add
}
}

textures/gothic_light/goth_lt2_lrg2k
{
qer_editorimage textures/gothic_light/gothic_light2_lrg.tga
q3map_surfacelight 2000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_lrg.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
blendfunc add
}
}

textures/gothic_light/gothic_light2_1k
{
qer_editorimage textures/gothic_light/gothic_light2.tga
q3map_surfacelight 1000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light2_2K
{
qer_editorimage textures/gothic_light/gothic_light2.tga
q3map_surfacelight 2000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light2_4K
{
qer_editorimage textures/gothic_light/gothic_light2.tga
q3map_surfacelight 4000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light2_lrg_1k
{
qer_editorimage textures/gothic_light/gothic_light2_lrg.tga
q3map_surfacelight 1000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_lrg.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
blendfunc add
}
}

textures/gothic_light/gothic_light2_lrg_200
{
qer_editorimage textures/gothic_light/gothic_light2_lrg.tga
q3map_surfacelight 200
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_lrg.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
blendfunc add
}
}

textures/gothic_light/gothic_light2_lrg_2k
{
qer_editorimage textures/gothic_light/gothic_light2_lrg.tga
q3map_surfacelight 2000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_lrg.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
blendfunc add
}
}

textures/gothic_light/gothic_light2_lrg_500
{
qer_editorimage textures/gothic_light/gothic_light2_lrg.tga
q3map_surfacelight 500
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_lrg.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
blendfunc add
}
}

textures/gothic_light/gothic_light3_10K
{
qer_editorimage textures/gothic_light/gothic_light3.tga
q3map_lightimage textures/gothic_light/gothic_light2_blend.tga
q3map_surfacelight 10000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light3_15K
{
qer_editorimage textures/gothic_light/gothic_light3.tga
q3map_lightimage textures/gothic_light/gothic_light2_blend.tga
q3map_surfacelight 15000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light3_1K
{
qer_editorimage textures/gothic_light/gothic_light3.tga
q3map_lightimage textures/gothic_light/gothic_light2_blend.tga
q3map_surfacelight 1000
surfaceparm nomarks
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light3_20K
{
qer_editorimage textures/gothic_light/gothic_light3.tga
q3map_lightimage textures/gothic_light/gothic_light2_blend.tga
q3map_surfacelight 20000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light3_2K
{
qer_editorimage textures/gothic_light/gothic_light3.tga
q3map_lightimage textures/gothic_light/gothic_light2_blend.tga
q3map_surfacelight 2000
surfaceparm nomarks
light 1
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light3_3k
{
qer_editorimage textures/gothic_light/gothic_light3.tga
q3map_lightimage textures/gothic_light/gothic_light2_blend.tga
q3map_surfacelight 3000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light3_4K
{
qer_editorimage textures/gothic_light/gothic_light3.tga
q3map_lightimage textures/gothic_light/gothic_light2_blend.tga
q3map_surfacelight 4000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light3_5K
{
qer_editorimage textures/gothic_light/gothic_light3.tga
q3map_lightimage textures/gothic_light/gothic_light2_blend.tga
q3map_surfacelight 5000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light3_6K
{
qer_editorimage textures/gothic_light/gothic_light3.tga
q3map_lightimage textures/gothic_light/gothic_light2_blend.tga
q3map_surfacelight 6000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light3_7K
{
qer_editorimage textures/gothic_light/gothic_light3.tga
q3map_lightimage textures/gothic_light/gothic_light2_blend.tga
q3map_surfacelight 7000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/gothic_light3_8K
{
qer_editorimage textures/gothic_light/gothic_light3.tga
q3map_lightimage textures/gothic_light/gothic_light2_blend.tga
q3map_surfacelight 8000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/gothic_light3.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/gothic_light2_blend.tga
rgbGen wave sin .6 .1 .1 .1
blendfunc add
}
}

textures/gothic_light/ironcrosslt1_1000
{
qer_editorimage textures/gothic_light/ironcrosslt1.tga
q3map_lightimage textures/gothic_light/ironcrosslt1.blend.tga
q3map_surfacelight 1000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt1_10000
{
qer_editorimage textures/gothic_light/ironcrosslt1.tga
q3map_lightimage textures/gothic_light/ironcrosslt1.blend.tga
q3map_surfacelight 10000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt1_120000
{
qer_editorimage textures/gothic_light/ironcrosslt1.tga
q3map_lightimage textures/gothic_light/ironcrosslt1.blend.tga
q3map_surfacelight 120000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt1_2000
{
qer_editorimage textures/gothic_light/ironcrosslt1.tga
q3map_lightimage textures/gothic_light/ironcrosslt1.blend.tga
q3map_surfacelight 2000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt1_20000
{
qer_editorimage textures/gothic_light/ironcrosslt1.tga
q3map_lightimage textures/gothic_light/ironcrosslt1.blend.tga
q3map_surfacelight 20000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/gothic_light/ironcrosslt1.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt1_2500
{
qer_editorimage textures/gothic_light/ironcrosslt1.tga
q3map_lightimage textures/gothic_light/ironcrosslt1.blend.tga
q3map_surfacelight 3500
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt1_3000
{
qer_editorimage textures/gothic_light/ironcrosslt1.tga
q3map_lightimage textures/gothic_light/ironcrosslt1.blend.tga
q3map_surfacelight 3000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt1_30000
{
qer_editorimage textures/gothic_light/ironcrosslt1.tga
q3map_lightimage textures/gothic_light/ironcrosslt1.blend.tga
q3map_surfacelight 30000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt1_4000
{
qer_editorimage textures/gothic_light/ironcrosslt1.tga
q3map_lightimage textures/gothic_light/ironcrosslt1.blend.tga
q3map_surfacelight 4000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/gothic_light/ironcrosslt1.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt1_40000
{
qer_editorimage textures/gothic_light/ironcrosslt1.tga
q3map_lightimage textures/gothic_light/ironcrosslt1.blend.tga
q3map_surfacelight 40000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt1_5000
{
qer_editorimage textures/gothic_light/ironcrosslt1.tga
q3map_lightimage textures/gothic_light/ironcrosslt1.blend.tga
q3map_surfacelight 5000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt1_500000
{
qer_editorimage textures/gothic_light/ironcrosslt1.tga
q3map_lightimage textures/gothic_light/ironcrosslt1.blend.tga
q3map_surfacelight 500000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt1.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt2_1000
{
qer_editorimage textures/gothic_light/ironcrosslt2.tga
q3map_lightimage textures/gothic_light/ironcrosslt2.blend.tga
q3map_surfacelight 1000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt2_10000
{
qer_editorimage textures/gothic_light/ironcrosslt2.tga
q3map_lightimage textures/gothic_light/ironcrosslt2.blend.tga
q3map_surfacelight 10000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt2_2000
{
qer_editorimage textures/gothic_light/ironcrosslt2.tga
q3map_lightimage textures/gothic_light/ironcrosslt2.blend.tga
q3map_surfacelight 2000
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt2_20000
{
qer_editorimage textures/gothic_light/ironcrosslt2.tga
q3map_lightimage textures/gothic_light/ironcrosslt2.blend.tga
q3map_surfacelight 20000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt2_2500
{
qer_editorimage textures/gothic_light/ironcrosslt2.tga
q3map_lightimage textures/gothic_light/ironcrosslt2.blend.tga
q3map_surfacelight 2500
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt2_3000
{
qer_editorimage textures/gothic_light/ironcrosslt2.tga
q3map_lightimage textures/gothic_light/ironcrosslt2.blend.tga
q3map_surfacelight 3000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt2_30000
{
qer_editorimage textures/gothic_light/ironcrosslt2.tga
q3map_lightimage textures/gothic_light/ironcrosslt2.blend.tga
q3map_surfacelight 30000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt2_4000
{
qer_editorimage textures/gothic_light/ironcrosslt2.tga
q3map_lightimage textures/gothic_light/ironcrosslt2.blend.tga
q3map_surfacelight 4000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt2_40000
{
qer_editorimage textures/gothic_light/ironcrosslt2.tga
q3map_lightimage textures/gothic_light/ironcrosslt2.blend.tga
q3map_surfacelight 40000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrosslt2_5000
{
qer_editorimage textures/gothic_light/ironcrosslt2.tga
q3map_lightimage textures/gothic_light/ironcrosslt2.blend.tga
q3map_surfacelight 5000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrosslt2.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltblue_10000
{
qer_editorimage textures/gothic_light/ironcrossltblue.tga
q3map_lightimage textures/gothic_light/ironcrossltblue.blend.tga
q3map_surfacelight 10000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltblue_2000
{
qer_editorimage textures/gothic_light/ironcrossltblue.tga
q3map_lightimage textures/gothic_light/ironcrossltblue.blend.tga
q3map_surfacelight 2000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
{
map textures/gothic_light/ironcrossltblue.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltblue_20000
{
qer_editorimage textures/gothic_light/ironcrossltblue.tga
q3map_lightimage textures/gothic_light/ironcrossltblue.blend.tga
q3map_surfacelight 20000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltblue_3000
{
qer_editorimage textures/gothic_light/ironcrossltblue.tga
q3map_lightimage textures/gothic_light/ironcrossltblue.blend.tga
q3map_surfacelight 3000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltblue_30000
{
qer_editorimage textures/gothic_light/ironcrossltblue.tga
q3map_lightimage textures/gothic_light/ironcrossltblue.blend.tga
q3map_surfacelight 30000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltblue_4000
{
qer_editorimage textures/gothic_light/ironcrossltblue.tga
q3map_lightimage textures/gothic_light/ironcrossltblue.blend.tga
q3map_surfacelight 4000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltblue_5000
{
qer_editorimage textures/gothic_light/ironcrossltblue.tga
q3map_lightimage textures/gothic_light/ironcrossltblue.blend.tga
q3map_surfacelight 5000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltblue.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltred_10000
{
qer_editorimage textures/gothic_light/ironcrossltred.tga
q3map_lightimage textures/gothic_light/ironcrossltred.blend.tga
q3map_surfacelight 10000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltred_2000
{
qer_editorimage textures/gothic_light/ironcrossltred.tga
q3map_lightimage textures/gothic_light/ironcrossltred.blend.tga
q3map_surfacelight 2000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltred_20000
{
qer_editorimage textures/gothic_light/ironcrossltred.tga
q3map_lightimage textures/gothic_light/ironcrossltred.blend.tga
q3map_surfacelight 20000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltred_3000
{
qer_editorimage textures/gothic_light/ironcrossltred.tga
q3map_lightimage textures/gothic_light/ironcrossltred.blend.tga
q3map_surfacelight 3000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltred_30000
{
qer_editorimage textures/gothic_light/ironcrossltred.tga
q3map_lightimage textures/gothic_light/ironcrossltred.blend.tga
q3map_surfacelight 30000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltred_4000
{
qer_editorimage textures/gothic_light/ironcrossltred.tga
q3map_lightimage textures/gothic_light/ironcrossltred.blend.tga
q3map_surfacelight 4000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.blend.tga
blendfunc add
}
}

textures/gothic_light/ironcrossltred_5000
{
qer_editorimage textures/gothic_light/ironcrossltred.tga
q3map_lightimage textures/gothic_light/ironcrossltred.blend.tga
q3map_surfacelight 5000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/ironcrossltred.blend.tga
blendfunc add
}
}

textures/gothic_light/light1_4Kgothic
{
qer_editorimage textures/base_light/light1.tga
q3map_lightimage textures/base_light/light1.blend.tga
q3map_surfacelight 4000
light 1
surfaceparm nomarks
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
rgbGen wave sin 0.25 0.25 0 .2
blendfunc add
}
}

textures/gothic_light/light1_6Kgothic
{
qer_editorimage textures/base_light/light1.tga
q3map_lightimage textures/base_light/light1.blend.tga
q3map_surfacelight 6000
light 1
surfaceparm nomarks
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
rgbGen wave sin 0.25 0.25 0 .2
blendfunc add
}
}

textures/gothic_light/light1_6Kgothicred
{
qer_editorimage textures/base_light/light1red.tga
q3map_lightimage textures/base_light/light1red.blend.tga
q3map_surfacelight 4000
light 1
surfaceparm nomarks
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
rgbGen wave sin 0.25 0.25 0 .2
blendfunc add
}
}

textures/gothic_light/pentagram_light1_10K
{
qer_editorimage textures/gothic_light/pentagram_light1.tga
q3map_surfacelight 10000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1_blend.tga
blendfunc add
rgbGen wave sin .8 .2 0 1
}
}

textures/gothic_light/pentagram_light1_15K
{
qer_editorimage textures/gothic_light/pentagram_light1.tga
q3map_surfacelight 15000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1_blend.tga
blendfunc add
rgbGen wave sin .8 .2 0 1
}
}

textures/gothic_light/pentagram_light1_1K
{
qer_editorimage textures/gothic_light/pentagram_light1.tga
q3map_surfacelight 1000
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1_blend.tga
blendfunc add
rgbGen wave sin .8 .2 0 1
}
}

textures/gothic_light/pentagram_light1_2K
{
qer_editorimage textures/gothic_light/pentagram_light1.tga
q3map_surfacelight 2000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1_blend.tga
blendfunc add
rgbGen wave sin .8 .2 0 1
}
}

textures/gothic_light/pentagram_light1_3K
{
qer_editorimage textures/gothic_light/pentagram_light1.tga
q3map_surfacelight 3000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1_blend.tga
blendfunc add
rgbGen wave sin .8 .2 0 1
}
}

textures/gothic_light/pentagram_light1_4K
{
qer_editorimage textures/gothic_light/pentagram_light1.tga
q3map_surfacelight 4000
light 1
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1_blend.tga
blendfunc add
rgbGen wave sin .8 .2 0 1
}
}

textures/gothic_light/pentagram_light1_5K
{
qer_editorimage textures/gothic_light/pentagram_light1.tga
q3map_surfacelight 5000
q3map_flare flareShader
surfaceparm nomarks
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_light/pentagram_light1_blend.tga
blendfunc add
rgbGen wave sin .8 .2 0 1
}
}

textures/gothic_block/killtrim_trans
{
qer_editorimage textures/gothic_block/killtrim.tga
surfaceparm nonsolid
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_block/killtrim.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/gothic_button/timbutton
{
q3map_lightimage textures/gothic_button/timbutton2.tga
q3map_surfacelight 10
{
map textures/gothic_button/timbutton.tga
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbgen identity
}
{
map textures/gothic_button/timbutton2.tga
blendfunc add
rgbgen wave sin .5 .5 0 1
}
}

textures/gothic_trim/barbedwire
{
surfaceparm trans
cull disable
{
map textures/gothic_trim/barbedwire.tga
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

textures/gothic_trim/baseboard09_p_shiny
{
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_trim/baseboard09_p_shiny.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
alphagen lightingspecular
rgbGen identity
}
}

textures/gothic_trim/border6_trans
{
qer_editorimage textures/gothic_trim/border6.tga
surfaceparm nonsolid
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_trim/border6.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/gothic_trim/chrome_rivet
{
{
map textures/effects/tinfx.tga
tcGen environment
rgbGen identity
}
{
map textures/gothic_trim/chrome_rivet.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_trim/column2c_trans
{
qer_editorimage textures/gothic_trim/column2c_test.tga
surfaceparm nonsolid
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_trim/column2c_test.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/gothic_trim/gothgrate2
{
surfaceparm metalsteps
cull none
{
map textures/gothic_trim/gothgrate2.tga
blendFunc GL_ONE GL_ZERO
rgbGen identity
alphaFunc GT0
depthWrite
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
depthFunc equal
}
}

textures/gothic_trim/gothgrate3
{
surfaceparm metalsteps
cull none
{
map textures/gothic_trim/gothgrate3.tga
blendFunc GL_ONE GL_ZERO
rgbGen identity
alphaFunc GT0
depthWrite
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
depthFunc equal
}
}

textures/gothic_trim/km_arena1tower4_shiny
{
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_trim/km_arena1tower4_shiny.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_trim/km_arena1tower4fx
{
{
map textures/effects/tinfx.tga
tcGen environment
rgbGen identity
}
{
map textures/gothic_trim/km_arena1tower4fx.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_trim/km_arena1towerblue
{
{
map textures/effects/tinfx.tga
tcGen environment
rgbGen identity
}
{
map textures/gothic_trim/km_arena1towerblue.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_trim/metalbase02b_iron
{
qer_editorimage textures/gothic_trim/metalbase02_b.tga
{
map textures/gothic_wall/iron01_e.tga
rgbGen identity
}
{
map textures/gothic_trim/metalbase02_b.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendfunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/gothic_trim/metalbase02c_iron
{
qer_editorimage textures/gothic_trim/metalbase02_c.tga
{
map textures/gothic_wall/iron01_e.tga
rgbGen identity
}
{
map textures/gothic_trim/metalbase02_c.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendfunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/gothic_trim/metalbase03a_brick
{
qer_editorimage textures/gothic_trim/metalbase03_a.tga
{
map textures/gothic_wall/streetbricks10.tga
tcMod scale 2 2
rgbGen identity
}
{
map textures/gothic_trim/metalbase03_a.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendfunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/gothic_trim/metalbase03b_iron
{
qer_editorimage textures/gothic_trim/metalbase03_b.tga
{
map textures/gothic_wall/iron01_e.tga
rgbGen identity
}
{
map textures/gothic_trim/metalbase03_b.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendfunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/gothic_trim/metalbase03c_iron
{
qer_editorimage textures/gothic_trim/metalbase03_c.tga
{
map textures/gothic_wall/iron01_e.tga
rgbGen identity
}
{
map textures/gothic_trim/metalbase03_c.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendfunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/gothic_trim/metalbase03d_iron
{
qer_editorimage textures/gothic_trim/metalbase03_d.tga
{
map textures/gothic_wall/iron01_e.tga
rgbGen identity
}
{
map textures/gothic_trim/metalbase03_d.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendfunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/gothic_trim/metalbase09b_iron
{
qer_editorimage textures/gothic_trim/metalbase09_b.tga
{
map textures/gothic_wall/iron01_e.tga
rgbGen identity
}
{
map textures/gothic_trim/metalbase09_b.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendfunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
}

textures/gothic_trim/metalbase09d_iron
{
qer_editorimage textures/gothic_trim/metalbase09_d.tga
{
map textures/gothic_wall/iron01_e.tga
rgbGen identity
}
{
map textures/gothic_trim/metalbase09_d.tga
rgbGen identity
blendfunc blend
}
{
map $lightmap
rgbGen identity
blendfunc GL_DST_COLOR GL_ZERO
}
}

textures/gothic_trim/metalbase09e_iron
{
qer_editorimage textures/gothic_trim/metalbase09_e.tga
{
map textures/gothic_wall/iron01_e.tga
rgbGen identity
}
{
map textures/gothic_trim/metalbase09_e.tga
rgbGen identity
blendfunc blend
}
{
map $lightmap
rgbGen identity
blendfunc GL_DST_COLOR GL_ZERO
}
}

textures/gothic_trim/metalsupport4b_trans
{
qer_editorimage textures/gothic_trim/metalsupport4b.tga
surfaceparm nonsolid
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_trim/metalsupport4b.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/gothic_trim/metalsupport4h_shiny
{
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_trim/metalsupport4h_shiny.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_trim/metalsupport4h_trans
{
qer_editorimage textures/gothic_trim/metalsupport4h_shiny
surfaceparm nonsolid
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_trim/metalsupport4h_shiny.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_trim/metalsupport4j_trans
{
qer_editorimage textures/gothic_trim/metalsupport4j.tga
surfaceparm nonsolid
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_trim/metalsupport4j.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/gothic_trim/metlsupport4i_shiney
{
qer_editorimage textures/gothic_trim/xmetalsupport4i_alpha.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_trim/xmetalsupport4i_alpha.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_trim/pitted_rust2_trans
{
qer_editorimage textures/gothic_trim/pitted_rust2.tga
surfaceparm nonsolid
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_trim/pitted_rust2.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/gothic_trim/pitted_rust3_trans
{
qer_editorimage textures/gothic_trim/pitted_rust3.tga
surfaceparm nonsolid
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_trim/pitted_rust3.tga
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
}
}

textures/gothic_trim/supportborderside_shiney
{
qer_editorimage textures/gothic_trim/xsupportborderside_shiney.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_trim/xsupportborderside_shiney.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_trim/tongue_bone
{
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_trim/tongue_bone.tga
blendFunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_trim/tongue_bone.blend.tga
blendfunc add
rgbGen wave sin 0.5 0.5 0 0.2
}
}

textures/gothic_trim/x_noblight
{
q3map_lightimage textures/gothic_trim/x_noblightfx.tga
q3map_surfacelight 100
{
map textures/sfx/firegorre2.tga
tcmod scroll .1 1
tcmod scale 1 1
}
{
map textures/gothic_trim/x_noblight.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
{
map textures/gothic_trim/x_noblightfx.tga
blendFunc gl_one gl_one
rgbGen wave sin .5 .5 0 .1
}
}

textures/gothic_trim/zinc_shiny
{
{
map textures/effects/tinfx.tga
tcGen environment
rgbGen identity
}
{
map textures/gothic_trim/zinc_shiny.tga
blendfunc blend
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}

textures/gothic_wall/glass_stained1
{
surfaceparm trans
qer_editorimage textures/gothic_wall/glass_stained1.tga
{
map textures/gothic_wall/glass_stained1.tga
blendfunc blend
rgbGen identity
}
}

textures/gothic_wall/window_evil6a
{
q3map_lightimage textures/gothic_wall/window_evil6a_glow.tga
q3map_surfacelight 50
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_wall/window_evil6a.tga
blendfunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_wall/window_evil6a_glow.tga
blendfunc add
rgbGen identity
}
}

textures/gothic_wall/window_evil7
{
q3map_lightimage textures/gothic_wall/window_evil7_glow.tga
q3map_surfacelight 300
{
map $lightmap
rgbGen identity
}
{
map textures/gothic_wall/window_evil7.tga
blendfunc GL_DST_COLOR GL_ZERO
rgbGen identity
}
{
map textures/gothic_wall/window_evil7_glow.tga
blendfunc add
rgbGen identity
}
}

textures/gothic_door/door02_i_ornate5_fin
{
qer_editorimage textures/gothic_door/door02_i_ornate5_fin.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_door/door02_i_ornate5_fin.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_f
{
qer_editorimage textures/gothic_wall/iron01_f.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_f.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_f2
{
qer_editorimage textures/gothic_wall/iron01_f2.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_f2.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_k
{
qer_editorimage textures/gothic_wall/iron01_k.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_k.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_l
{
qer_editorimage textures/gothic_wall/iron01_l.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_l.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_l2
{
qer_editorimage textures/gothic_wall/iron01_l2.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_l2.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_l4
{
qer_editorimage textures/gothic_wall/iron01_l4.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_l4.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_m
{
qer_editorimage textures/gothic_wall/iron01_m.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_m.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_m2
{
qer_editorimage textures/gothic_wall/iron01_m2.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_m2.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_m3
{
qer_editorimage textures/gothic_wall/iron01_m3.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_m3.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_m_circles
{
qer_editorimage textures/gothic_wall/iron01_m_circles.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_m_circles.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_mtech2
{
qer_editorimage textures/gothic_wall/iron01_mtech2.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_mtech2.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_mthin
{
qer_editorimage textures/gothic_wall/iron01_mthin.tga
{
map $lightmap
rgbgen identity
}
{
map ttextures/gothic_wall/iron01_mthin.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_n
{
qer_editorimage textures/gothic_wall/iron01_n.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_n.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_n_circles
{
qer_editorimage textures/gothic_wall/iron01_n_circles.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_n_circles.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_ndark
{
qer_editorimage textures/gothic_wall/iron01_ndark.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_ndark.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_ndark_circles
{
qer_editorimage textures/gothic_wall/iron01_ndark_circles.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_ndark_circles.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_ntech
{
qer_editorimage textures/gothic_wall/iron01_ntech.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_ntech.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/iron01_ntech2
{
qer_editorimage textures/gothic_wall/iron01_ntech2.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/iron01_ntech2.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/streetbricks10_shiny
{
q3map_globaltexture
sort opaque
{
map $lightmap
tcmod turb sin .1 .1 0 0
tcmod scale 2 2
rgbgen identity
}
{
map textures/gothic_wall/streetbricks11.tga
rgbGen identity
blendfunc gl_one gl_src_color
}
{
map $lightmap
blendfunc gl_dst_color gl_zero
rgbgen identity
}
}

textures/gothic_wall/xoct20c_shiney
{
qer_editorimage textures/gothic_wall/xoct20c_shiney.tga
{
map $lightmap
rgbgen identity
}
{
map textures/gothic_wall/xoct20c_shiney.tga
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen identity
alphaGen lightingSpecular
}
}

textures/gothic_wall/xpipecolumn_gray_shiny
{
{
map textures/effects/tinfx.tga
tcGen environment
rgbGen identity
}
{
map textures/gothic_wall/xpipecolumn_gray_shiny.tga
blendFunc gl_src_alpha gl_one_minus_src_alpha
rgbGen identity
}
{
map $lightmap
blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
rgbGen identity
}
}
