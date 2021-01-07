#  call using:
#    $ gnuplot -e "filename='data.IPIs'; outputname='data.pdf'; maxX=<max_x_axis>" IPIs_time.plot

set terminal pdf
set output outputname
unset key
set yrange [0:]
set xrange [0:maxX]
set xlabel "time (ms)"
set ylabel "IPI (ms)"
plot filename u 1:2 w lp ls 7 lt rgb "#5f0f40"


