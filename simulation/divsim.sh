
concount=0
for i in 0.0002 0.0005 0.0008 0.001 0.002 0.005 0.008 0.01 0.02 0.05 0.06
do
concount=`expr $concount + 1`
v1=$i
v2=`echo 7 \* "$i"|bc| awk '{printf "%f", $0}'`
v3=`echo 16 \* $i|bc| awk '{printf "%f", $0}'`
echo -ne "0.5\t((((P1:$v1,P2:$v1):$v2,(S1:$v1,S2:$v1):$v2):$v2,((G1:$v1,G2:$v1):$v2,(E1:$v1,E2:$v1):$v2):$v2):$v2,(A1:$v1,A2:$v1):$v3);\n" >> config"$concount"
echo -ne "0.25\t((((P1:$v1,P2:$v1):$v2,(S1:$v1,S2:$v1):$v2):$v2,((G1:$v1,G2:$v1):$v2,(A1:$v1,A2:$v1):$v2):$v2):$v2,(E1:$v1,E2:$v1):$v3);\n">> config"$concount"
echo -ne "0.14\t((((P1:$v1,P2:$v1):$v2,(G1:$v1,G2:$v1):$v2):$v2,((S1:$v1,S2:$v1):$v2,(A1:$v1,A2:$v1):$v2):$v2):$v2,(E1:$v1,E2:$v1):$v3);\n">> config"$concount"
echo -ne "0.11\t((((P1:$v1,P2:$v1):$v2,(G1:$v1,G2:$v1):$v2):$v2,((E1:$v1,E2:$v1):$v2,(A1:$v1,A2:$v1):$v2):$v2):$v2,(S1:$v1,S2:$v1):$v3);\n">> config"$concount"
done

