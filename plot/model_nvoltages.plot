#  call using:
#    $ gnuplot -e "filename='data.dat'; outputname='data.pdf'; maxX=<max_x_axis>" model_nvoltages.plot

set terminal pdf size 5in, 1.8in
set output outputname

set multiplot layout 4, 1 

## Nucleus
set title "Nuclei" font ",14"
set lmargin 6
set tmargin 0.5
set bmargin 0.5
unset key
unset xlabel
unset ylabel
set xtics format " " 
set xrange [0:maxX]
set yrange [-80:40]
set ytics -80,40,40
plot filename u ($0/100):6 w l lt rgb "#e36414" #VPD

unset title
set lmargin 6
set tmargin 0.5
set bmargin 0.5
unset xlabel
unset ylabel
set xtics format " " 
set xrange [0:maxX]
set yrange [-80:40]
set ytics -80,40,40
plot filename u ($0/100):7 w l lt rgb "#9a031e" #DP

set lmargin 6
set tmargin 0.5
set bmargin 0.5
unset xlabel
unset ylabel
set xtics format " " 
set xrange [0:maxX]
set yrange [-80:40]
set ytics -80,40,40
plot filename u ($0/100):8 w l lt rgb "#0f4c5c" #PCN

set lmargin 6
set tmargin 0.5
set bmargin 0.5
unset xlabel
unset ylabel
set xtics format " " 
set xrange [0:maxX]
set yrange [-80:40]
set ytics -80,40,40
plot filename u ($0/100):9 w l lt rgb "#5f0f40" #CN

unset multiplot
#pause -1 
