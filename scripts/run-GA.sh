#!/bin/sh

vDir="."
startConfigName="ST"
run="001"
configFile="$vDir/configs/${startConfigName}.yaml"
outputDir="$vDir/ga-results/${startConfigName}_${run}"

mkdir ${outputDir}

GAParameters="G800_N150_P90"
${vDir}/bin/emmodelGAFit -i ${configFile} -g 800 -n 150 -p 90 \
        -s "${outputDir}/${startConfigName}_${run}_${GAParameters}.stats" \
        -o "${outputDir}/${startConfigName}_${run}_${GAParameters}.dat"

# GAParameters="G800_A4p5_B0p005_T0p45_M70"
# ${vDir}/bin/emmodelGAfit -i ${configFile} -g 800 -a 4.5 -b 0.05 -t 0.45 -m 70 \
#         -s "${outputDir}/${startConfigName}_${run}_${GAParameters}.stats" \
#         -o "${outputDir}/${startConfigName}_${run}_${GAParameters}.dat"
