set terminal png size 500,500
set output 'output.png'

set format x ""
set format y ""

set style line 1 \
    linecolor rgb '#0060ad' \
    linetype 1 linewidth 2 \
    pointtype 7 pointsize 1.5

plot 'output.dat' with linespoints linestyle 1 notitle