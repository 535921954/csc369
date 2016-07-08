#!/bin/bash

for alg in rand fifo lru clock opt
do
    for trf in tr-simpleloop.ref tr-blocked.ref tr-matmul.ref
    do
        for mem in 50 100 150 200
        do
            fname=logs/$trf-m$mem-$alg.log
            if [ ! -f $fname ]; then
                echo running $fname
                ./sim -f traceprogs/$trf -m $mem -s 10000 -a $alg &> $fname
            else
                echo skipping $fname
            fi
        done
    done
done

for trf in tr-simpleloop.ref tr-blocked.ref tr-matmul.ref
do
    for mem in 50 100 150 200
    do
        echo " "
        echo "## " TABLE $trf MEMORY SIZE:$mem
        echo "ALGO , HIT RATE , HIT COUNT , MISS COUNT , OVERALL EVICT CNT , CLEAN EVICT CNT , DIRTY EVICT CNT"

        for alg in rand fifo lru clock opt
        do
            fname=logs/$trf-m$mem-$alg.log
            hr=$(tail $fname | grep "Hit rate" | cut -f3 -d' ')
            hc=$(tail $fname | grep "Hit count" | cut -f3 -d' ')
            mc=$(tail $fname | grep "Miss count" | cut -f3 -d' ')
            cce=$(tail $fname | grep "Clean evictions" | cut -f3 -d' ')
            dec=$(tail $fname | grep "Dirty evictions" | cut -f3 -d' ')
            oec=$((cce + dec))
            echo "$alg, $hr, $hc, $mc, $oec, $cce, $dec"
        done
    done
done
