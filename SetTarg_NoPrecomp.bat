set location=C:\U4L\Snip\Core
set projectname=ProjCoreStr
set projectdirname=ProjCoreStr
set projectdir=%location%\%projectdirname%
set sniploc=C:\U4L\snip\
set TargUtil=%sniploc%SetTargUtil.bat
set ModePostfix=_NoPrecomp
start /B %TargUtil% %projectname% %projectdir% %ModePostfix%
