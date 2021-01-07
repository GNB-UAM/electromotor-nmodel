#  call using:
#    $ gnuplot -e "filename='data.dat'; outputname='data.pdf'; maxX=<max_x_axis>" model_synapses.plot

set terminal pdf size 5in, 1.4in
set output outputname

set offsets graph 0, 0
set multiplot layout 3, 1 title "Synapsis" font ",14"
unset key

set lmargin 6
set tmargin 0.5
set bmargin 0.5
unset xlabel
set xtics format " " 
set xrange [0:maxX]
set yrange [-20:0]
set ytics -20,10,0
# 1=VPD_DP (red) / 2=VPD_PCN (blue)
plot filename u ($0/100):1 w l lt rgb "#9a031e", filename u ($0/100):2 w l lt rgb "#0f4c5c"

unset title
set tmargin 0.5
set bmargin 0.5
unset xlabel
set xtics format " " 
set xrange [0:maxX]
set yrange [0:20]
set ytics 0,10,20
# 3=DP_PCN (red) / 4=PCN_CN (blue)
plot filename u ($0/100):3 w l lt rgb "#9a031e", filename u ($0/100):4 w l lt rgb "#0f4c5c"

set tmargin 0.5
set bmargin 0.5
unset xlabel
set xtics format " " 
set xrange [0:maxX]
set yrange [0:40]
set ytics 0,20,40
# 5=CN_VPD
plot filename u ($0/100):5 w l lt rgb "#5f0f40"

unset multiplot
#pause -1
