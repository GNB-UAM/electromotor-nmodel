#!/bin/sh

vDir="."
modelName="ST"

configFile="$vDir/configs/${modelName}.yaml"
outputDir="$vDir/results/${modelName}"

mkdir ${outputDir}

$vDir/bin/emmodel -i $configFile -o $outputDir/emmodel_nVolt

echo "-- Extracting IPIs..."
python $vDir/scripts/IPIs.py $outputDir/emmodel_nVolt_sca > $outputDir/scallopTest.IPIs
python $vDir/scripts/IPIs.py $outputDir/emmodel_nVolt_acc > $outputDir/accelerationTest.IPIs
python $vDir/scripts/IPIs.py $outputDir/emmodel_nVolt_rasp > $outputDir/raspTest.IPIs
python $vDir/scripts/IPIs.py $outputDir/emmodel_nVolt_cess > $outputDir/cessationTest.IPIs
echo " DONE\n"

echo "-- Printing charts..."
gnuplot -e "filename='$outputDir/scallopTest.IPIs'; outputname='$outputDir/scallopTest_IPIs.pdf'; maxX=1200" $vDir/plot/IPIs_time.plot
gnuplot -e "filename='$outputDir/emmodel_nVolt_sca'; outputname='$outputDir/scallopTest_nvoltages.pdf'; maxX=1200" $vDir/plot/model_nvoltages.plot
gnuplot -e "filename='$outputDir/emmodel_nVolt_sca'; outputname='$outputDir/scallopTest_synapses.pdf'; maxX=1200" $vDir/plot/model_synapses.plot

gnuplot -e "filename='$outputDir/accelerationTest.IPIs'; outputname='$outputDir/accelerationTest_IPIs.pdf'; maxX=2000" $vDir/plot/IPIs_time.plot
gnuplot -e "filename='$outputDir/emmodel_nVolt_acc'; outputname='$outputDir/accelerationTest_nvoltages.pdf'; maxX=2000" $vDir/plot/model_nvoltages.plot
gnuplot -e "filename='$outputDir/emmodel_nVolt_acc'; outputname='$outputDir/accelerationTest_synapses.pdf'; maxX=2000" $vDir/plot/model_synapses.plot

gnuplot -e "filename='$outputDir/raspTest.IPIs'; outputname='$outputDir/raspTest_IPIs.pdf'; maxX=1400" $vDir/plot/IPIs_time.plot
gnuplot -e "filename='$outputDir/emmodel_nVolt_rasp'; outputname='$outputDir/raspTest_nvoltages.pdf'; maxX=1400" $vDir/plot/model_nvoltages.plot
gnuplot -e "filename='$outputDir/emmodel_nVolt_rasp'; outputname='$outputDir/raspTest_synapses.pdf'; maxX=1400" $vDir/plot/model_synapses.plot

gnuplot -e "filename='$outputDir/cessationTest.IPIs'; outputname='$outputDir/cessationTest_IPIs.pdf'; maxX=1000" $vDir/plot/IPIs_time.plot
gnuplot -e "filename='$outputDir/emmodel_nVolt_cess'; outputname='$outputDir/cessationTest_nvoltages.pdf'; maxX=1000" $vDir/plot/model_nvoltages.plot
gnuplot -e "filename='$outputDir/emmodel_nVolt_cess'; outputname='$outputDir/cessationTest_synapses.pdf'; maxX=1000" $vDir/plot/model_synapses.plot
echo " DONE"