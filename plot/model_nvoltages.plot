#  call using:
#    $ gnuplot -e "filename='data.dat'; outputname='data.pdf'" model_nvoltages.plot

set terminal pdf
set output outputname

set multiplot layout 4, 1 title "Neural model pattern" font ",14"
set lmargin 5
set bmargin 3
unset key
unset xlabel
unset ylabel
unset ytics

plot filename u 6 w l #VPD
plot filename u 7 w l #DP
plot filename u 8 w l #PCN
plot filename u 9 w l #CN
unset multiplot
#pause -1 
