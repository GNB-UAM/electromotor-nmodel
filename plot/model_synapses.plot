#  call using:
#    $ gnuplot -e "filename='data.dat'; outputname='data.pdf'" model_synapses.plot

set terminal pdf
set output outputname

set offsets graph 0, 0
set multiplot layout 3, 1 title "Synapses" font ",14"
set lmargin 5
set bmargin 3
unset key

# 1=VPD_DP (red) / 2=VPD_PCN (blue)
plot filename u ($0/100):1 w l lt rgb "red", filename u ($0/100):2 w l lt rgb "blue"
# 3=DP_PCN (red) / 4=PCN_CN (blue)
plot filename u ($0/100):3 w l lt rgb "red", filename u ($0/100):4 w l lt rgb "blue"
# 5=CN_VPD
plot filename u ($0/100):5 w l

unset multiplot
#pause -1
