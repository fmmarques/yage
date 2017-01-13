let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/src/yage
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +38 ~/src/alien-armada/main.cpp
badd +1 ~/src/alien-armada/include/logic/game.h
badd +10 ~/src/alien-armada/include/logic/state.h
badd +1 include/logic/game/state.h
badd +1 ~/.vimrc
badd +44 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/hive.h
badd +520 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/hive.cc
badd +28 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/frame_calc.h
badd +93 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/frame_calc.cpp
badd +62 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/part4.cl
badd +11 ~/src/image-processing-on-gpu-clusters/.gitignore
badd +43 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/part3.cl
badd +63 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/frame.h
badd +86 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/frame.cc
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/histogram.h
badd +40 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/workqueue.h
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/sbdxml_encoder.h
badd +88 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/sbdxml_encoder.cc
badd +19 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/sbd_vidprocess.h
badd +55 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/sbd_vidprocess.cc
badd +264 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/videoprocessing.cpp
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/.gitignore
badd +88 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/part4.mod.cl
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/vidprocess.h
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/vidprocess.cc
badd +34 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/VidProcessNode.cpp
badd +5 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/include/options.h
badd +1 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/results.txt
badd +292 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/src/mpeg_decoder.cc
badd +232 ~/src/image-processing-on-gpu-clusters/hive2_GPU_queue/CMakeLists.txt
badd +15 ~/src/arkanoid/include/arkanoid.h
badd +1 ~/src/arkanoid/src/arkanoid.cpp
badd +18 ~/src/arkanoid/Makefile
badd +1 Makefile
badd +0 include/events/event_manager.h
badd +0 tests/graphics/graphics_manager.unit.cpp
silent! argdel *
edit Makefile
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 39 - ((38 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
39
normal! 0
tabedit tests/graphics/graphics_manager.unit.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 88 + 87) / 174)
exe 'vert 2resize ' . ((&columns * 85 + 87) / 174)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 020l
wincmd w
argglobal
edit tests/graphics/graphics_manager.unit.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 7 - ((6 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
7
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 88 + 87) / 174)
exe 'vert 2resize ' . ((&columns * 85 + 87) / 174)
tabedit include/events/event_manager.h
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 9 - ((8 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
9
normal! 020l
tabnext 2
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
