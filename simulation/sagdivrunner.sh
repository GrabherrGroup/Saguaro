
PATH=$PATH:/home/nagarjun/sagdiv/scripts/
PATH=$PATH:/home/nagarjun/phylip-3.69/src/

scripts="/home/nagarjun/sagdiv/scripts"
sagbin="/home/nagarjun/ryggrad2"
number=100
minlength=50
maxlength=2000
indv=10
output="test"
config="config1"

echo -ne "iteration\tconfig\tgenomelength\tcorrect\twrong\tmissed\tmeanweighteddistance\n" >>$scripts/stats

for configi in {1..11}
do
config=config"$configi"
cd /home/nagarjun/sagdiv

rm "$output" "$output".na 
rm -r simfiles simfasta simcon
mkdir simfiles simfasta simcon

#simulate lengths of regions and define their boundaries
Rscript $scripts/simulate_boundaries.r $number $minlength $maxlength $output

#create files needed to run dawg
perl $scripts/simulatetrees.pl $output $number $config > "$output".na

#run dawg
for i in `seq 1 $number` 
do
echo simfiles/example"$i""$i"iter
$scripts/dawg simfiles/example"$i"
done

#combine output files from dawg
for i in `seq 1 $number`
do
echo simfasta/example"$i".Fasta
perl $scripts/combinefasta.pl simfasta/example"$i".Fasta
done

rm simcon/multigenomes
mv *.genomes simcon

count=0
for i in `cut -f 2 $config`
do
count=`expr $count + 1`
echo $i > simcon/before.tree"$count"
done

cd simcon

for i in `ls -1 *.genomes`
do
echo $i
header=`echo $i|cut -f 1 -d '.'`
echo -e "\n>""$header" >> multigenomes
cat $i >> multigenomes
done

fold multigenomes > fold.multigenomes

$sagbin/Fasta2HMMFeature -i fold.multigenomes -o fold.multigenomes.HMM

for i in {1..24} 25 50 100 150 200
do
#rm -r "$i"iter
#mkdir "$i"iter
$sagbin/Saguaro -f fold.multigenomes.HMM -o "$i"iter -iter "$i"
done

for i in {1..24} 25 50 100 150 200
do
cp "$i"iter/LocalTrees.out "$i".LocalTrees.out
rm -r "$i"iter
done

echo -ne  "Y" > param_file

for i in {1..24} 25 50 100 150 200
do
perl $scripts/parselocaltrees.pl "$i".LocalTrees.out "$i".loc.out $count $indv
done



for i in {1..24} 25 50 100 150 200
do
echo -ne "$i\t$config\t" >> $scripts/stats
perl $scripts/getstats.pl ../"$output".na "$i".loc.out  >> $scripts/stats
done

done

