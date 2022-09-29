#! /bin/bash
g++ -g -o chache main.cpp
cat inputs/400.perlbench-41B.trace.txt | ./cache 128 16 64 l
cat inputs/401.bzip2-226B.trace.txt | ./cache 128 16 64 l
cat inputs/403.gcc-16B.trace.txt | ./cache 128 16 64 l
cat inputs/410.bwaves-1963B.trace.txt | ./cache 128 16 64 l
cat inputs/416.gamess-875B.trace.txt | ./cache 128 16 64 l
cat inputs/429.mcf-184B.trace.txt | ./cache 128 16 64 l
cat inputs/433.milc-127B.trace.txt | ./cache 128 16 64 l
cat inputs/435.gromacs-111B.trace.txt | ./cache 128 16 64 l
cat inputs/436.cactusADM-1804B.trace.txt | ./cache 128 16 64 l
cat inputs/437.leslie3d-134B.trace.txt | ./cache 128 16 64 l
cat inputs/444.namd-120B.trace.txt | ./cache 128 16 64 l
cat inputs/445.gobmk-17B.trace.txt | ./cache 128 16 64 l
cat inputs/447.dealII-3B.trace.txt | ./cache 128 16 64 l
cat inputs/450.soplex-247B.trace.txt | ./cache 128 16 64 l
cat inputs/453.povray-887B.trace.txt | ./cache 128 16 64 l
cat inputs/454.calculix-104B.trace.txt | ./cache 128 16 64 l
cat inputs/456.hmmer-191B.trace.txt | ./cache 128 16 64 l
cat inputs/458.sjeng-1088B.trace.txt | ./cache 128 16 64 l
cat inputs/459.GemsFDTD-1169B.trace.txt | ./cache 128 16 64 l
cat inputs/462.libquantum-1343B.trace.txt | ./cache 128 16 64 l
cat inputs/464.h264ref-30B.trace.txt | ./cache 128 16 64 l
cat inputs/465.tonto-1769B.trace.txt | ./cache 128 16 64 l
cat inputs/470.lbm-1274B.trace.txt | ./cache 128 16 64 l
cat inputs/471.omnetpp-188B.trace.txt | ./cache 128 16 64 l
cat inputs/473.astar-153B.trace.txt | ./cache 128 16 64 l
cat inputs/481.wrf-1170B.trace.txt | ./cache 128 16 64 l
cat inputs/482.sphinx3-1100B.trace.txt | ./cache 128 16 64 l
cat inputs/483.xalancbmk-127B.trace.txt | ./cache 128 16 64 l